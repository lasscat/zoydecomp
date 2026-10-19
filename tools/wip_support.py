"""Isolated single-function compiler driver, shared by probes and Track B."""
from io import BytesIO
from pathlib import Path
import re
import subprocess
import tempfile
from project import GateError, sha256


def compile_object(source, profile):
    return compile_bytes(Path(source).read_bytes(), profile)


def compile_bytes(raw, profile):
    """Compile the immutable, hash-checked snapshot supplied by the caller."""
    try:
        text = raw.decode("ascii")
    except UnicodeDecodeError as exc:
        raise GateError("source must be ASCII") from exc
    if re.search(r"\b(__asm__|__asm|asm)\b|^\s*#\s*(include|embed)", text, re.M):
        raise GateError("standalone natural C required; asm/includes/embed need separate review")
    if profile['driver'] == 'mwcc-standalone-c-v1':
        from mwcc_support import compile_bytes as compile_mwcc
        return compile_mwcc(raw, profile)
    executable = Path(profile["executable"])
    if sha256(executable.read_bytes()) != profile["executable_sha256"]:
        raise GateError("compiler identity changed")
    version = subprocess.run([str(executable), "--version"], capture_output=True, text=True,
                             timeout=20, check=False)
    if version.returncode or version.stdout.strip() != profile["version"]:
        raise GateError("compiler version probe failed or differs")
    if profile["driver"] != "clang-standalone-c-v1":
        raise GateError("unsupported compiler driver")
    flags = profile["flags"]
    if not all(isinstance(f, str) for f in flags) or any(
            f.startswith(("@", "-o", "-include", "-I", "-L", "-fplugin", "-Xclang")) for f in flags):
        raise GateError("unsupported compiler option requires driver review")
    with tempfile.TemporaryDirectory(prefix="pvz-function-") as temporary:
        work = Path(temporary)
        (work / "candidate.c").write_bytes(raw)
        result = subprocess.run([str(executable), *flags, "-c", "candidate.c", "-o", "candidate.o"],
                                cwd=work, capture_output=True, text=True, timeout=30, check=False)
        if result.returncode:
            raise GateError("compiler failure: " + result.stderr[:3000])
        obj = (work / "candidate.o").read_bytes()
    return obj, result.stderr


def compile_function(source, profile):
    obj, diagnostics = compile_object(source, profile)
    return extract_text(obj, profile["symbol_values"]), diagnostics


def extract_text(obj, symbol_values):
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
    elf = ELFFile(BytesIO(obj))
    if elf['e_machine'] != "EM_ARM" or not elf.little_endian or elf.elfclass != 32:
        raise GateError("wrong target object: ARM32 little-endian required")
    section = elf.get_section_by_name(".text")
    if section is None or not section.data():
        raise GateError("compiler emitted no .text")
    text_index = elf.get_section_index(".text")
    for sec in elf.iter_sections():
        if sec.name != ".text" and sec['sh_flags'] & 4 and sec['sh_size']:
            raise GateError("extra executable section requires reviewed layout")
    data = bytearray(section.data())
    for relsec in elf.iter_sections():
        if not isinstance(relsec, RelocationSection) or relsec['sh_info'] != text_index:
            continue
        symbols = elf.get_section(relsec['sh_link'])
        for rel in relsec.iter_relocations():
            name = symbols.get_symbol(rel['r_info_sym']).name
            kind, off = rel['r_info_type'], rel['r_offset']
            if kind != 2 or relsec.is_RELA():
                raise GateError(f"unsupported relocation {kind} for {name}; never masked")
            if name not in symbol_values:
                raise GateError("unresolved relocation symbol: " + name)
            if off < 0 or off + 4 > len(data):
                raise GateError("relocation outside .text")
            addend = int.from_bytes(data[off:off + 4], "little")
            value = (int(symbol_values[name]) + addend) & 0xFFFFFFFF
            data[off:off + 4] = value.to_bytes(4, "little")
    return bytes(data)
