"""Compile complete C blocks and link whole modules with opaque retained sections.

Retained original bytes are binary inputs, never reconstructed source or credit.
LLD performs section placement; this tool never patches generated instructions.
The current production scope is standalone ARM9 leaf functions without text relocs.
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
    configured, sources, intervals = set(), set(), []
    for item in plan['functions']:
        fn = identities.get(item['id'])
        if fn is None or fn.get('size') is None or fn['module'] != 'arm9' or fn['mode'] != 'arm':
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
        if not item.get('evidence') or not item.get('provenance'):
            raise GateError('missing reconstruction evidence/provenance')
        a, b = fn['address'], fn['address'] + fn['size']
        if any(a < y and x < b for x, y in intervals):
            raise GateError('overlapping reconstruction credit')
        intervals.append((a, b))
    actual_sources = {str(p.relative_to(root)) for p in (root / 'src').rglob('*')
                      if p.suffix.lower() in ('.c', '.cpp', '.cc', '.cxx') and p.is_file()}
    if sources != actual_sources:
        raise GateError('unconfigured or missing strict C sources')
    return plan, universe


def inspect_object(data, fn, symbol):
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
    text_index = elf.get_section_index('.text')
    if fn['address'] % max(1, text['sh_addralign']):
        raise GateError('compiled function alignment does not fit measured VMA')
    for sec in elf.iter_sections():
        if sec['sh_flags'] & 2 and sec['sh_size'] and sec.name not in ('.text', '.ARM.exidx'):
            raise GateError('unaccounted allocated compiler section: ' + sec.name)
        if isinstance(sec, RelocationSection) and sec.num_relocations():
            target = elf.get_section(sec['sh_info'])
            if target.name != '.ARM.exidx':
                raise GateError('strict leaf backend rejects unresolved/text relocation: ' + sec.name)
            # Only the compiler's non-runtime unwind descriptor is discarded.
            if any(rel['r_info_type'] != 42 for rel in sec.iter_relocations()):
                raise GateError('unsupported relocation in discarded unwind descriptor')
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


def link_module(original, base, blocks, linker, output_dir):
    from elftools.elf.elffile import ELFFile
    executable = Path(linker['executable'])
    if sha256(executable.read_bytes()) != linker['executable_sha256']:
        raise GateError('linker executable identity changed')
    version = subprocess.run([str(executable), '--version'], capture_output=True,
                             text=True, timeout=20, check=False)
    if version.returncode or version.stdout.strip() != linker['version']:
        raise GateError('linker version probe failed or changed')
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
        text = inspect_object(obj, fn, symbol)
        target = original[fn['address'] - base:fn['address'] - base + fn['size']]
        if sha256(target) != fn['target_sha256']:
            raise GateError('wrong original target bytes for declared function')
        if text != target:
            raise GateError('local unmasked compiled-byte prefilter failed: ' + fn['id'])
        name = f'.fn{index:04d}'
        object_name = f'candidate{index:04d}.o'
        objects.append((object_name, obj))
        expected.append((name, fn['address'], text))
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
    with tempfile.TemporaryDirectory(prefix='pvz-module-link-') as td:
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
            raise GateError('module linker failure: ' + result.stderr[:3000])
        elf_bytes = (work / 'module.elf').read_bytes()
        elf = ELFFile(BytesIO(elf_bytes))
        if (elf.elfclass != 32 or not elf.little_endian or elf['e_machine'] != 'EM_ARM'
                or elf['e_type'] != 'ET_EXEC'):
            raise GateError('wrong linked output target/type')
        alloc = sorted([(s.name, s['sh_addr'], s.data()) for s in elf.iter_sections()
                        if s['sh_flags'] & 2 and s['sh_size']], key=lambda row: row[1])
        if alloc != expected:
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


def linked_modules(root=ROOT):
    plan, universe = validate_declaration(root)
    if not plan['functions']:
        return {}
    identities = {f['id']: f for f in universe['functions']}
    layout = read_json(root / 'config' / REVISION / 'rom-layout.json')
    module = next(m for m in layout['modules'] if m['module'] == 'arm9')
    chunk = next(c for c in layout['chunks'] if c['name'] == 'arm9')
    original = (root / 'extract' / REVISION / 'chunks' / chunk['file']).read_bytes()
    if sha256(original) != module['sha256']:
        raise GateError('wrong original ARM9 module input')
    blocks = []
    for item in plan['functions']:
        fn = identities[item['id']]
        if fn['rom_offset'] != module['rom_offset'] + fn['address'] - module['load_address']:
            raise GateError('function ROM/VMA mapping mismatch')
        source = root / item['source']
        source_before = source.read_bytes()
        profile_path = root / item['profile']
        profile_before = profile_path.read_bytes()
        if sha256(source_before) != item['source_sha256'] or sha256(profile_before) != item['profile_sha256']:
            raise GateError('declared source/profile changed before compilation')
        profile = json.loads(profile_before)
        if profile['symbol_values']:
            raise GateError('external symbol resolution outside current strict leaf backend')
        obj, _ = compile_bytes(source_before, profile)
        if source.read_bytes() != source_before or profile_path.read_bytes() != profile_before:
            raise GateError('source/profile changed during strict compilation')
        blocks.append((fn, obj, item['symbol']))
    linker_path = checked_path(root, plan['linker'], 'config')
    linker_bytes = linker_path.read_bytes()
    if sha256(linker_bytes) != plan['linker_sha256']:
        raise GateError('stale linker profile declaration')
    image = link_module(original, module['load_address'], blocks, json.loads(linker_bytes),
                        root / 'build' / REVISION / 'linked' / 'arm9')
    return {'arm9': image}
