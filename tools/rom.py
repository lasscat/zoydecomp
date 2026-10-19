"""Lossless component repacker. Opaque original bytes receive no C reconstruction credit."""
import struct
from project import GateError, ORIGINAL_SHA1, ORIGINAL_SHA256, REVISION, ROOT
from project import original, read_json, sha256, write_json, isolation


def crc16(data):
    value = 0xFFFF
    for byte in data:
        value ^= byte
        for _ in range(8):
            value = (value >> 1) ^ (0xA001 if value & 1 else 0)
    return value


def inventory(data):
    def u(offset):
        return struct.unpack_from("<I", data, offset)[0]

    def extent(start, size):
        if start < 0 or size < 0 or start + size > len(data):
            raise GateError("component outside ROM")
        return start, start + size

    named = [("header-and-secure-gap", *extent(0, u(0x84)))]
    modules = []
    for name, h in (("arm9", 0x20), ("arm7", 0x30)):
        start, end = extent(u(h), u(h + 12))
        named.append((name, start, end))
        modules.append({"module": name, "rom_offset": start, "stored_size": end - start,
                        "load_address": u(h + 8), "entry_address": u(h + 4),
                        "sha256": sha256(data[start:end]),
                        "executable_regions": "mixed code/data; see discovery baseline"})
    for name, h in (("fnt", 0x40), ("fat", 0x48), ("arm9-overlay-table", 0x50),
                    ("arm7-overlay-table", 0x58)):
        if u(h + 4):
            named.append((name, *extent(u(h), u(h + 4))))
    fat_start, fat_end = extent(u(0x48), u(0x4c))
    if (fat_end - fat_start) % 8:
        raise GateError("invalid FAT size")
    files = []
    for off in range(fat_start, fat_end, 8):
        a, b = struct.unpack_from("<II", data, off)
        if b < a:
            raise GateError("negative FAT range")
        extent(a, b - a)
        fid = len(files)
        files.append({"id": fid, "rom_offset": a, "size": b - a,
                      "sha256": sha256(data[a:b]), "path": None})
        if a != b:
            named.append((f"file-{fid:04d}", a, b))
    # Nitro FNT: directory entries, subdirectory IDs and first file IDs.
    fnt, fnt_size = u(0x40), u(0x44)
    visited = set()

    def directory(did, prefix):
        index = did - 0xF000
        if index in visited or index < 0 or 8 * (index + 1) > fnt_size:
            raise GateError("invalid/cyclic FNT directory")
        visited.add(index)
        pos, fid = struct.unpack_from("<IH", data, fnt + 8 * index)
        pos += fnt
        while True:
            if not fnt <= pos < fnt + fnt_size:
                raise GateError("FNT entry outside table")
            length = data[pos]
            pos += 1
            if not length:
                break
            n = length & 127
            if pos + n + (2 if length & 128 else 0) > fnt + fnt_size:
                raise GateError("truncated FNT entry")
            name = data[pos:pos + n].decode("ascii")
            pos += n
            if name in (".", "..") or "/" in name or "\\" in name:
                raise GateError("unsafe FNT path")
            if length & 128:
                child = struct.unpack_from("<H", data, pos)[0]
                pos += 2
                directory(child, prefix + name + "/")
            else:
                if fid >= len(files) or files[fid]["path"] is not None:
                    raise GateError("FNT file alias/out-of-range")
                files[fid]["path"] = prefix + name
                fid += 1

    directory(0xF000, "")
    overlays = []
    for cpu, h in (("arm9", 0x50), ("arm7", 0x58)):
        if u(h + 4) % 32:
            raise GateError("invalid overlay table size")
        for off in range(u(h), u(h) + u(h + 4), 32):
            oid, ram, size, bss, cs, ce, fid, flags = struct.unpack_from("<8I", data, off)
            if fid >= len(files):
                raise GateError("overlay file outside FAT")
            overlays.append({"module": f"{cpu}/ov{oid:03d}", "address": ram, "ram_size": size,
                             "bss_size": bss, "ctor_start": cs, "ctor_end": ce, "file_id": fid,
                             "compressed": bool(flags & 0x1000000), "flags": flags,
                             "stored_size": files[fid]["size"], "rom_offset": files[fid]["rom_offset"]})
    banner = u(0x68)
    if banner:
        version = struct.unpack_from("<H", data, banner)[0]
        sizes = {1: 0x840, 2: 0x940, 3: 0xA40, 0x103: 0x23C0}
        if version not in sizes:
            raise GateError("unrecognized banner version")
        named.append(("banner", *extent(banner, sizes[version])))
    named.sort(key=lambda n: (n[1], n[2]))
    cursor, chunks = 0, []
    for name, start, end in named:
        if start < cursor:
            raise GateError("overlapping ROM components require explicit analysis")
        if start > cursor:
            chunks.append({"name": f"gap-{cursor:08x}", "start": cursor, "end": start})
        chunks.append({"name": name, "start": start, "end": end})
        cursor = end
    if cursor < len(data):
        chunks.append({"name": "rom-tail-padding", "start": cursor, "end": len(data)})
    for chunk in chunks:
        chunk["sha256"] = sha256(data[chunk["start"]:chunk["end"]])
        chunk["file"] = f"{chunk['start']:08x}-{chunk['name']}.bin"
    return {"schema": 1, "game_code": data[12:16].decode(), "revision": data[30],
            "size": len(data), "sha1": ORIGINAL_SHA1, "sha256": ORIGINAL_SHA256,
            "header_crc16_valid": crc16(data[:0x15E]) == struct.unpack_from("<H", data, 0x15E)[0],
            "modules": modules, "overlays": overlays, "filesystem": files, "chunks": chunks,
            "compression": "overlays flagged as stored; main binaries separately analyzed by dsd"}


def prepare(rom_path, root=ROOT):
    data = original(rom_path)
    actual = inventory(data)
    expected = read_json(root / "config" / REVISION / "rom-layout.json")
    if actual != expected:
        raise GateError("target component layout differs from frozen baseline")
    for chunk in expected["chunks"]:
        path = root / "extract" / REVISION / "chunks" / chunk["file"]
        payload = data[chunk["start"]:chunk["end"]]
        path.parent.mkdir(parents=True, exist_ok=True)
        if path.exists() and path.read_bytes() != payload:
            raise GateError("preserving altered extracted input: " + str(path))
        path.write_bytes(payload)
    write_json(root / "extract" / REVISION / "prepared.json", {"original_sha256": ORIGINAL_SHA256})


def build(root=ROOT):
    isolation(root)
    plan = read_json(root / "config" / REVISION / "rom-layout.json")
    output = root / "build" / REVISION / "pvz.nds"
    output.parent.mkdir(parents=True, exist_ok=True)
    temp = output.with_suffix(".tmp")
    from link_backend import linked_modules
    linked = linked_modules(root)
    cursor = 0
    try:
        with temp.open("wb") as stream:
            for chunk in plan["chunks"]:
                data = (root / "extract" / REVISION / "chunks" / chunk["file"]).read_bytes()
                if chunk["start"] != cursor or len(data) != chunk["end"] - cursor:
                    raise GateError("non-contiguous/truncated baseline component")
                if sha256(data) != chunk["sha256"]:
                    raise GateError("changed target component: " + chunk["name"])
                replacement = linked.get(chunk['name'], data)
                if len(replacement) != len(data):
                    raise GateError('linked module changed stored extent')
                stream.write(replacement)
                cursor = chunk["end"]
        # Compare actual produced bytes to immutable identity, not just plan metadata.
        original(temp)
        temp.replace(output)
    finally:
        temp.unlink(missing_ok=True)
    return output


def verify(rom_path, root=ROOT):
    source = original(rom_path)
    output = build(root)
    actual = output.read_bytes()
    if actual != source:
        raise GateError("full-ROM byte comparison failed")
    return output
