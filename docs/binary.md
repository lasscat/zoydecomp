# Binary baseline and discovery limits

Identity is frozen in tools/project.py and config/BWBE-r0/rom-layout.json.
Header: title PVZ, game BWBE, maker PQ, unit 0 (DS), ROM version 0, game-code suffix
E (North America); header CRC16 validates. Do not assume a different regional ROM
matches these addresses. No external ROM database was used to label a revision.

| Module | ROM offset | Stored size | Load / entry |
| --- | --- | --- | --- |
| ARM9 stored image | 0x4000 | 0x101838 | 0x02000000 / 0x02000800 ARM |
| ARM7 stored image | 0x18b800 | 0x2642c | 0x02380000 / 0x02380000 ARM |
| ARM9 overlay 0 | 0x105c00 | 0x20860 | 0x021de5e0 |
| ARM9 overlay 1 | 0x126600 | 0x3dfe0 | 0x021de5e0 |
| ARM9 overlay 2 | 0x164600 | 0x27020 | 0x021de5e0 |

The overlay ROM offsets and sizes in rom-layout.json are authoritative; overlays
reuse runtime addresses but have distinct identities. Overlay tables declare no
compression for these three modules; each stored size equals declared RAM size.
Their BSS sizes are 192, 1216, 2368 bytes. Constructor table extents are preserved.
ARM9 build metadata has compression-end field zero, and dsd extracts it as
uncompressed/unencrypted. ARM7 compression/section details need separate analysis;
the repacker never decompresses or regenerates either executable.

ARM9 main loaded extent is 0x02000000-0x020fd300. Autoload payload follows, with
table at 0x02101820-0x02101838: ITCM base 0x01ff8000, 0x44c0 initialized bytes;
DTCM base 0x027e0000, 0x60 initialized bytes and 0x20 BSS bytes. Main BSS is
0x020fd300-0x021de5e0. These are load extents, not claims that every byte is code.
No complete ARM/Thumb region map, relocation graph, literal-pool map, vtable map
or function universe is established yet. Interworking targets and unreviewed
alignment/section boundaries remain discovery tasks. Known sized ARM code/pool
extents are recorded separately in functions-v1.json.

FNT offset 0x1b1e00, size 0x199; FAT offset 0x1b2000, size 0xb0. Twenty-two FAT
files include the three overlays and nineteen named assets. Full paths, extents,
per-file hashes and all gaps are tracked as metadata in rom-layout.json. Contents
stay ignored. Named assets include data packs, a childrom/main.srl executable,
interface resources, six manual .blz files, a Mobiclip movie and two SDAT banks.
Suffix .blz is a compression hint, not a validated decoder result. Internal pack
compression, child executable modules and asset formats are not yet inventoried;
all remain opaque and receive zero code credit. Embedded child-ROM analysis must
use a distinct module namespace and version the denominator before counting it.

Discovery attempt: dsd init aborts at the shared-tail branch described in
compiler.md. Inventory v1 therefore freezes only four supported identities, two
with sized blocks. It is explicitly incomplete; total functions, total sized code
and percentages are unavailable. Adding discovery results requires v2 plus an
audit mapping aliases/overlaps/old-to-new boundaries. Never relabel the four entries
as the total universe or count a call into a function suffix twice.

dsd's original repack differs by four bytes only: 0x6c-0x6d (secure-area CRC16)
and 0x15e-0x15f (dependent header CRC). The original secure-area CRC is 0x7348;
dsd emits zero. The adjacent secure-area delay 0x051e is unchanged. The field
interpretation was cross-checked against the installed ndspy ROM parser/serializer.
docs/dsd-repack-diff.json records
the extents. We did not patch the generated ROM or mask those bytes. The baseline
builder serializes the original header as an opaque complete component and
preserves its original CRC/padding. This verifies a binary baseline, not C linking.
