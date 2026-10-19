"""Compile complete C blocks and link whole modules with opaque retained sections.

Retained original bytes are binary inputs, never reconstructed source or credit.
LLD performs section placement; this tool never patches generated instructions.
The reviewed scope is complete ARM functions in ARM9 and uncompressed ov000.
Explicit same-module call edges are resolved by LLD, never by byte patching.
"""
from io import BytesIO
import json
from pathlib import Path
import re
import struct
import subprocess
import tempfile

from project import GateError, ROOT, REVISION, read_json, sha256, validate_universe
from wip_support import compile_bytes


def checked_path(root, name, prefix):
    path = root / name
    if path.is_symlink() or not path.is_file() or not path.resolve().is_relative_to(root / prefix):
        raise GateError('unsafe/missing declared input: ' + name)
    return path


def declaration(root=ROOT):
    path = root / 'config' / REVISION / 'build.json'
    if not path.exists():
        return {'functions': [], 'inventory': 'functions-v1.json'}
    plan = read_json(path)
    if plan.get('schema') != 1 or plan['inventory'] not in ('functions-v1.json', 'functions-v2.json', 'functions-v3.json', 'functions-v4.json', 'functions-v5.json'):
        raise GateError('unsupported strict build schema/inventory')
    return plan


def validate_declaration(root=ROOT):
    plan = declaration(root)
    universe = read_json(root / 'config' / REVISION / plan['inventory'])
    validate_universe(universe)
    identities = {f['id']: f for f in universe['functions']}
    configured, sources, symbols, intervals = set(), set(), set(), {}
    for item in plan['functions']:
        fn = identities.get(item['id'])
        if (fn is None or fn.get('size') is None
                or fn['module'] not in ('arm9', 'arm9/ov000') or fn['mode'] != 'arm'):
            raise GateError('unsupported/unbounded strict function')
        if item['id'] in configured:
            raise GateError('duplicate reconstruction credit')
        configured.add(item['id'])
        source = checked_path(root, item['source'], 'src/auto')
        if source.suffix != '.c' or item['source'] in sources:
            raise GateError('one standalone C source required per complete function')
        sources.add(item['source'])
        if sha256(source.read_bytes()) != item['source_sha256']:
            raise GateError('stale strict source: ' + item['source'])
        profile_path = checked_path(root, item['profile'], 'config')
        if sha256(profile_path.read_bytes()) != item['profile_sha256']:
            raise GateError('stale strict compiler profile')
        if not re.fullmatch(r'[A-Za-z_]\w*', item['symbol'], flags=re.ASCII):
            raise GateError('invalid reconstructed function symbol')
        if item['symbol'] in symbols:
            raise GateError('duplicate reconstructed function symbol')
        symbols.add(item['symbol'])
        if not item.get('evidence') or not item.get('provenance'):
            raise GateError('missing reconstruction evidence/provenance')
        a, b = fn['address'], fn['address'] + fn['size']
        group = intervals.setdefault(fn['module'], [])
        if any(a < y and x < b for x, y in group):
            raise GateError('overlapping reconstruction credit')
        group.append((a, b))
    for item in plan['functions']:
        calls = item.get('calls', [])
        if not isinstance(calls, list) or not all(isinstance(key, str) for key in calls):
            raise GateError('explicit configured call IDs required')
        if len(calls) != len(set(calls)):
            raise GateError('duplicate configured call edge')
        for key in calls:
            if key not in configured or identities[key]['module'] != identities[item['id']]['module']:
                raise GateError('call target must be configured in the same module')
    actual_sources = {str(p.relative_to(root)) for p in (root / 'src').rglob('*')
                      if p.suffix.lower() in ('.c', '.cpp', '.cc', '.cxx') and p.is_file()}
    if sources != actual_sources:
        raise GateError('unconfigured or missing strict C sources')
    return plan, universe


def inspect_object(data, fn, symbol, call_targets=None):
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
    from elftools.elf.sections import SymbolTableSection
    elf = ELFFile(BytesIO(data))
    if (elf.elfclass != 32 or not elf.little_endian or elf['e_machine'] != 'EM_ARM'
            or elf['e_type'] != 'ET_REL'):
        raise GateError('wrong target ELF; ARM32 little-endian relocatable required')
    text = elf.get_section_by_name('.text')
    if text is None or text['sh_size'] != fn['size']:
        raise GateError('complete compiled function size mismatch')
    if fn['size'] % 4 or fn['code_size'] % 4:
        raise GateError('complete ARM block/code extent must be word aligned')
    if text['sh_type'] != 'SHT_PROGBITS' or text['sh_flags'] & 6 != 6:
        raise GateError('allocated executable .text required')
    text_index = elf.get_section_index('.text')
    call_targets = {} if call_targets is None else call_targets
    used_calls, call_offsets = set(), set()
    if fn['address'] % max(1, text['sh_addralign']):
        raise GateError('compiled function alignment does not fit measured VMA')
    for sec in elf.iter_sections():
        if sec['sh_flags'] & 2 and sec['sh_size'] and sec.name not in ('.text', '.ARM.exidx'):
            raise GateError('unaccounted allocated compiler section: ' + sec.name)
        if isinstance(sec, RelocationSection) and sec.num_relocations():
            target = elf.get_section(sec['sh_info'])
            if target.name == '.text' and call_targets:
                if sec.is_RELA() or sec['sh_type'] != 'SHT_REL':
                    raise GateError('call relocations require SHT_REL')
                table = elf.get_section(sec['sh_link'])
                for rel in sec.iter_relocations():
                    off = rel['r_offset']
                    if (rel['r_info_type'] not in (1, 28) or off % 4
                            or off < 0 or off + 4 > fn['code_size'] or off in call_offsets):
                        raise GateError('unsupported/overlapping ARM call relocation')
                    call_offsets.add(off)
                    # The reviewed REL form is an unconditional BL with addend
                    # -8. Reject B, BLX, conditions and interior addends.
                    if int.from_bytes(text.data()[off:off + 4], 'little') != 0xebfffffe:
                        raise GateError('call relocation requires ARM BL with entry addend -8')
                    callee = table.get_symbol(rel['r_info_sym'])
                    dest = call_targets.get(callee.name)
                    if (dest is None or callee['st_shndx'] != 'SHN_UNDEF'
                            or callee['st_info']['bind'] != 'STB_GLOBAL'
                            or callee['st_info']['type'] not in ('STT_NOTYPE', 'STT_FUNC')
                            or callee['st_value'] != 0 or callee['st_size'] != 0
                            or callee['st_other']['visibility'] != 'STV_DEFAULT'):
                        raise GateError('call relocation target is not an explicit external function entry')
                    if (dest['module'] != fn['module'] or dest['mode'] != 'arm'
                            or dest['address'] % 4):
                        raise GateError('call target must be same-module ARM')
                    delta = dest['address'] - (fn['address'] + off + 8)
                    if not -0x2000000 <= delta <= 0x1fffffc:
                        raise GateError('call target outside ARM BL range; veneers forbidden')
                    used_calls.add(callee.name)
                continue
            if target.name != '.ARM.exidx':
                raise GateError('strict leaf backend rejects unresolved/text relocation: ' + sec.name)
            # Only the compiler's non-runtime unwind descriptor is discarded.
            if sec.is_RELA() or any(rel['r_info_type'] != 42 for rel in sec.iter_relocations()):
                raise GateError('unsupported relocation in discarded unwind descriptor')
    if used_calls != set(call_targets):
        raise GateError('declared call edges differ from compiled call relocations')
    for off in range(0, fn['code_size'], 4):
        word = int.from_bytes(text.data()[off:off + 4], 'little')
        if word & 0xfe000000 == 0xfa000000 or word & 0x0ffffff0 == 0x012fff30:
            raise GateError('BLX/indirect calls require separate scope review')
        if word >> 28 != 15 and word & 0x0f000000 == 0x0b000000 and off not in call_offsets:
            raise GateError('ARM BL must have an explicit configured call relocation')
        if word >> 28 != 15 and word & 0x0f000000 == 0x0a000000:
            displacement = (word & 0xffffff) << 2
            if displacement & 0x2000000:
                displacement -= 0x4000000
            target_offset = off + 8 + displacement
            if not 0 <= target_offset < fn['code_size']:
                raise GateError('external tail branch requires separate scope review')
    functions, mappings = [], []
    for table in elf.iter_sections():
        if not isinstance(table, SymbolTableSection):
            continue
        for sym in table.iter_symbols():
            if sym['st_shndx'] == text_index:
                if sym.name.startswith(('$a', '$t', '$d')):
                    mappings.append(sym)
                elif sym['st_info']['type'] == 'STT_FUNC':
                    functions.append(sym)
            if sym['st_info']['type'] == 'STT_OBJECT' and sym['st_shndx'] != 'SHN_UNDEF':
                raise GateError('extra compiler-generated object requires reviewed data layout')
    if (len(functions) != 1 or functions[0].name != symbol
            or functions[0]['st_value'] != 0 or functions[0]['st_size'] != fn['size']):
        raise GateError('function symbol does not exactly cover the complete compiled block')
    if not any(s.name.startswith('$a') and s['st_value'] == 0 for s in mappings):
        raise GateError('missing ARM mapping at function entry')
    if any(s.name.startswith('$t') for s in mappings):
        raise GateError('wrong instruction mode in ARM function')
    if any(s.name.startswith('$d') and s['st_value'] < fn['code_size'] for s in mappings):
        raise GateError('literal data inside claimed executable code')
    return text.data()


def retained_object(sections):
    """ELF32 opaque input sections; this never interprets or generates instructions."""
    names = [name for name, _ in sections] + ['.shstrtab']
    strings, offsets = bytearray(b'\0'), {}
    for name in names:
        offsets[name] = len(strings)
        strings.extend(name.encode('ascii') + b'\0')
    ident = b'\x7fELF' + bytes([1, 1, 1, 0]) + bytes(8)
    data = bytearray(struct.pack('<16sHHIIIIIHHHHHH', ident, 1, 40, 1, 0, 0, 0,
                                 0x05000000, 52, 0, 0, 40, len(names) + 1, len(names)))
    headers = [(0,) * 10]
    for name, payload in sections:
        offset = len(data)
        data.extend(payload)
        headers.append((offsets[name], 1, 2, 0, offset, len(payload), 0, 0, 1, 0))
    offset = len(data)
    data.extend(strings)
    headers.append((offsets['.shstrtab'], 3, 0, 0, offset, len(strings), 0, 0, 1, 0))
    while len(data) % 4:
        data.append(0)
    struct.pack_into('<I', data, 32, len(data))
    for header in headers:
        data.extend(struct.pack('<10I', *header))
    return bytes(data)


def link_module(original, base, blocks, linker, output_dir, call_edges=None):
    from elftools.elf.elffile import ELFFile
    executable = Path(linker['executable'])
    if sha256(executable.read_bytes()) != linker['executable_sha256']:
        raise GateError('linker executable identity changed')
    version = subprocess.run([str(executable), '--version'], capture_output=True,
                             text=True, timeout=20, check=False)
    if version.returncode or version.stdout.strip() != linker['version']:
        raise GateError('linker version probe failed or changed')
    by_id, symbols = {}, set()
    for fn, obj, symbol in blocks:
        if fn['id'] in by_id or symbol in symbols:
            raise GateError('duplicate function identity/symbol in linked module')
        by_id[fn['id']] = (fn, symbol)
        symbols.add(symbol)
    call_edges = {} if call_edges is None else call_edges
    if not set(call_edges) <= by_id.keys():
        raise GateError('call caller is not configured')
    for keys in call_edges.values():
        if (not isinstance(keys, list) or len(keys) != len(set(keys))
                or not set(keys) <= by_id.keys()):
            raise GateError('call target is not configured or is duplicated')
    sections, script, expected = [], ['OUTPUT_FORMAT(elf32-littlearm)', 'OUTPUT_ARCH(arm)', 'SECTIONS {'], []
    cursor, objects = base, []
    for index, (fn, obj, symbol) in enumerate(sorted(blocks, key=lambda row: row[0]['address'])):
        if fn['address'] < cursor or fn['address'] + fn['size'] > base + len(original):
            raise GateError('overlapping/out-of-module complete function block')
        name = f'.retain{index:04d}'
        if fn['address'] > cursor:
            payload = original[cursor - base:fn['address'] - base]
            sections.append((name, payload))
            expected.append((name, cursor, payload))
            script.append(f'{name} 0x{cursor:x} : {{ KEEP(retained.o({name})) }}')
        targets = {by_id[key][1]: by_id[key][0] for key in call_edges.get(fn['id'], [])}
        text = inspect_object(obj, fn, symbol, targets)
        target = original[fn['address'] - base:fn['address'] - base + fn['size']]
        if sha256(target) != fn['target_sha256']:
            raise GateError('wrong original target bytes for declared function')
        if not targets and text != target:
            raise GateError('local unmasked compiled-byte prefilter failed: ' + fn['id'])
        name = f'.fn{index:04d}'
        object_name = f'candidate{index:04d}.o'
        objects.append((object_name, obj))
        # Relocatable call fields are checked only after LLD has resolved them.
        # Every linked byte, including the call instruction, must equal target.
        expected.append((name, fn['address'], target))
        script.extend([f'{name} 0x{fn["address"]:x} : {{ KEEP({object_name}(.text)) }}',
                       f'ASSERT(SIZEOF({name}) == {fn["size"]}, "complete function size")'])
        cursor = fn['address'] + fn['size']
    if cursor < base + len(original):
        name, payload = '.retain_tail', original[cursor - base:]
        sections.append((name, payload))
        expected.append((name, cursor, payload))
        script.append(f'{name} 0x{cursor:x} : {{ KEEP(retained.o({name})) }}')
    script.extend(['/DISCARD/ : { *(.ARM.exidx) *(.ARM.attributes) *(.comment) *(.note*) }', '}'])
    output_dir.mkdir(parents=True, exist_ok=True)
    script_text = '\n'.join(script) + '\n'
    with tempfile.TemporaryDirectory(prefix='pvz-module-link-', dir=output_dir) as td:
        work = Path(td)
        (work / 'retained.o').write_bytes(retained_object(sections))
        for name, obj in objects:
            (work / name).write_bytes(obj)
        (work / 'module.ld').write_text(script_text)
        result = subprocess.run([str(executable), '--no-undefined', '-T', 'module.ld',
                                 '-Map=module.map', '-o', 'module.elf', 'retained.o',
                                 *[name for name, _ in objects]], cwd=work, capture_output=True,
                                text=True, timeout=30, check=False)
        if result.returncode:
            (output_dir / 'failed-link.ld').write_text(script_text)
            (output_dir / 'failed-link.log').write_text(result.stdout + result.stderr)
            raise GateError('module linker failure: ' + result.stderr[:3000])
        elf_bytes = (work / 'module.elf').read_bytes()
        elf = ELFFile(BytesIO(elf_bytes))
        if (elf.elfclass != 32 or not elf.little_endian or elf['e_machine'] != 'EM_ARM'
                or elf['e_type'] != 'ET_EXEC'):
            raise GateError('wrong linked output target/type')
        alloc = sorted([(s.name, s['sh_addr'], s.data()) for s in elf.iter_sections()
                        if s['sh_flags'] & 2 and s['sh_size']], key=lambda row: row[1])
        if alloc != expected:
            (output_dir / 'failed-link.ld').write_text(script_text)
            (output_dir / 'failed-link.map').write_bytes((work / 'module.map').read_bytes())
            (output_dir / 'failed-link.elf').write_bytes(elf_bytes)
            raise GateError('linked sections differ from declared original/C section plan')
        cursor, image = base, bytearray()
        for name, address, data in alloc:
            if address != cursor:
                raise GateError('linked module gap/overlap: ' + name)
            image.extend(data)
            cursor += len(data)
        if bytes(image) != original:
            raise GateError('complete linked module differs from immutable original input')
        (output_dir / 'module.elf').write_bytes(elf_bytes)
        (output_dir / 'module.ld').write_text(script_text)
        (output_dir / 'module.map').write_bytes((work / 'module.map').read_bytes())
        (output_dir / 'module.bin').write_bytes(image)
        return bytes(image)


def module_input(layout, name):
    """Map only the reviewed stored modules to one exact immutable ROM chunk."""
    def unique(rows, key, value):
        matches = [row for row in rows if row[key] == value]
        if len(matches) != 1:
            raise GateError('missing/duplicate module mapping: ' + str(value))
        return matches[0]

    if name == 'arm9':
        module = unique(layout['modules'], 'module', name)
        chunk = unique(layout['chunks'], 'name', name)
    elif name == 'arm9/ov000':
        overlay = unique(layout['overlays'], 'module', name)
        if (overlay['compressed'] is not False or overlay['flags'] != 0
                or overlay['ram_size'] != overlay['stored_size']):
            raise GateError('only uncompressed unchanged-size ov000 is reviewed')
        file = unique(layout['filesystem'], 'id', overlay['file_id'])
        chunk = unique(layout['chunks'], 'name', f'file-{file["id"]:04d}')
        if file['rom_offset'] != overlay['rom_offset'] or file['size'] != overlay['stored_size']:
            raise GateError('overlay/FAT mapping mismatch')
        module = dict(overlay, load_address=overlay['address'], sha256=file['sha256'])
        end = module['load_address'] + module['stored_size']
        if not module['load_address'] <= overlay['ctor_start'] <= overlay['ctor_end'] <= end:
            raise GateError('overlay constructors outside stored image')
    else:
        raise GateError('unreviewed strict module')
    if (chunk['start'] != module['rom_offset']
            or chunk['end'] - chunk['start'] != module['stored_size']
            or chunk['sha256'] != module['sha256']):
        raise GateError('module/chunk mapping mismatch')
    return module, chunk


def linked_modules(root=ROOT):
    plan, universe = validate_declaration(root)
    if not plan['functions']:
        return {}
    identities = {f['id']: f for f in universe['functions']}
    layout = read_json(root / 'config' / REVISION / 'rom-layout.json')
    groups, edges = {}, {}
    for item in plan['functions']:
        fn = identities[item['id']]
        source = root / item['source']
        source_before = source.read_bytes()
        profile_path = root / item['profile']
        profile_before = profile_path.read_bytes()
        if sha256(source_before) != item['source_sha256'] or sha256(profile_before) != item['profile_sha256']:
            raise GateError('declared source/profile changed before compilation')
        profile = json.loads(profile_before)
        if profile['symbol_values']:
            raise GateError('profile symbol addresses forbidden; configure complete call targets')
        obj, _ = compile_bytes(source_before, profile)
        if source.read_bytes() != source_before or profile_path.read_bytes() != profile_before:
            raise GateError('source/profile changed during strict compilation')
        groups.setdefault(fn['module'], []).append((fn, obj, item['symbol']))
        edges[item['id']] = item.get('calls', [])
    linker_path = checked_path(root, plan['linker'], 'config')
    linker_bytes = linker_path.read_bytes()
    if sha256(linker_bytes) != plan['linker_sha256']:
        raise GateError('stale linker profile declaration')
    replacements = {}
    for name, blocks in sorted(groups.items()):
        module, chunk = module_input(layout, name)
        original = (root / 'extract' / REVISION / 'chunks' / chunk['file']).read_bytes()
        if len(original) != module['stored_size'] or sha256(original) != module['sha256']:
            raise GateError('wrong original module input: ' + name)
        for fn, obj, symbol in blocks:
            if fn['rom_offset'] != module['rom_offset'] + fn['address'] - module['load_address']:
                raise GateError('function ROM/VMA mapping mismatch')
            if name == 'arm9/ov000' and fn['address'] + fn['size'] > module['ctor_start']:
                raise GateError('overlay function overlaps retained constructor table/trailer')
        replacements[chunk['name']] = link_module(
            original, module['load_address'], blocks, json.loads(linker_bytes),
            root / 'build' / REVISION / 'linked' / name,
            {fn['id']: edges[fn['id']] for fn, obj, symbol in blocks})
    return replacements
