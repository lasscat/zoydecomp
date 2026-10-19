# DS RNG state lifecycle: first connected reconstruction target

Question: how do seeding, zero-seed rejection, next-index and refill transitions
interact in the DS game, and which callers own that state? This system is useful to
reproducible simulation/mod tests, but whole-game determinism is not established.

Observed ARM9 seed entry: arm9:02034f40:arm, complete 84-byte block (80 code bytes
plus pool). Next entry: arm9:02034fc0:arm, reviewed 296-byte block (280 code bytes).
Their exact hashes, ROM offsets and boundaries are in config/BWBE-r0/functions-v2.json.
The inventory remains incomplete. Do not guess other function boundaries from names.

Ownership evidence (separate DS analysis, observations unless flagged): all eleven
reviewed mt_seed BL callers pass r0 = "this"+constant, an MT state embedded inside
the calling object, and r1 = the low 32 bits of the value returned by arm9
0x02005d48, a 64-bit system-time getter built from the 16-bit timer word at
0x04000100 plus a 48-bit software counter at 0x020fd6e4 (+8/+0xc). No caller reads
or branches on the seed return, so the zero-seed rejection path is never observed at
these sites (real seeds are time values). State offsets differ per object (e.g.
this+0x55c, this+0x5a0, this+0xc28, this+0xafd4); at least two streams can coexist in
one function, so these are per-object states, not one shared global. The only direct
user of the global pointer at 0x02105dfc is the tail-call helper at 0x02034f94, which
defaults r0 to that global when the caller passes zero; the 31-bit wrapper at
0x02034fb0 clears bit 31 and is called from many overlay sites. A separate scan of
all 65 reachable wrapper call sites (6 in ov001, 59 in ov002) found that every one
passes an explicit per-object state pointer; none passes r0 = 0, and the helper
address is never stored as a function pointer, so the global-default branch appears
unreachable. A byte scan of the whole ROM finds the literal 0x02105dfc only in the
helper's own pool, and no writer of that BSS word was located, consistent with the
default path never being exercised. Whether distinct "this" bases alias remains
unproven; the containing overlay functions have no direct BL callers (invoked through
function-pointer/vtable tables), so base provenance is not resolvable from BL scans.

Seed-then-consume pairs are observed: the same object+offset is seeded by mt_seed in
an init/transition routine and later consumed through the 31-bit wrapper (e.g.
this+0xc28 seeded at ov002 0x021df3ec and read at 0x021df610/0x021df6a0;
this+0x59c seeded at 0x021de838 and read via the direct helper at 0x021df00c), so one
object can carry several independent RNG streams.

The seed draft has explicit 32-bit fields: +0 remaining, +4 next_address, +8 an array
of 624 words. These names are hypotheses about use, not a desktop class identity.
Nonzero input stores the seed, applies the 1812433253 recurrence, stores +0 = 1,
and returns 1. Zero returns 0 without changing the mapped state. The +4 word is
untouched by this function. Native tests use a raw 32-bit address placeholder to
preserve DS offsets. Struct size is asserted as 2504 bytes for the tested harness.

The next draft (semantic/src/mt_next.c) is the raw 32-bit temper/refill function,
written against the two-loop DS twist (offsets +397 then -227 words, final word
words[396]) with an explicit +4 next-word address. It matches the restricted ARM
interpreter and the compiled native C on 655 sampled calls, including two complete
twist reloads (626 consecutive calls) and a reseed transition. The DS returns the
unmasked 32-bit value; the 31-bit masking lives in the separate wrapper, unlike the
reference which masks inside NextNoAssert. Isolated Clang comparison is X (276 versus
296 bytes), so this draft earns no S/N credit; behavior samples never change the tier.

Donor algorithm correspondence: ruslan831/PlantsVsZombies-decompilation commit
325b2229a7225d73870bb69322eefcda3a45bf8d, SexyAppFramework/MTRand.cpp,
MTRand::SRand(unsigned long) and MTRand::NextNoAssert(). Independent DS recurrence
constants/control flow are recorded in docs/donors.md. DS zero-seed rejection and the
split raw/masked output differ. Root MIT plus the Matsumoto/Nishimura file notice
apply; see semantic/NOTICE-MT.txt. Static review only.

Current evidence: 41 sampled seed calls (36 scenarios, four transition sequences) and
655 sampled next/reseed calls (6 scenarios, two reloads). Returns, all state/guards,
original preserved registers/SP agree under a restricted ARM model versus native
compiled saved C; the next harness maps the state at its real ARM address so the +4
cursor address compares byte-exactly. See semantic/BEHAVIOR.md for exact cases,
assumptions and exclusions. Both drafts remain X for instruction similarity; sample
behavior checks do not improve the tier, and no full-game/hardware equivalence is
proven.

Next: identify which per-object owner first triggers a reload and whether any caller
uses the raw unmasked value; add reproducible differential transition checks that span
seed -> many nexts -> reseed. Unsupported interpreter instructions must fail until
implemented and tested; do not replace original execution with donor behavior as the
oracle. Preserve the seed's tests while mapping which fields a mod/port can safely
expose. Avoid further seed/next code-shape or flag permutations without new evidence.

## Supplemental four-entry lifecycle oracle

`systems/rng_lifecycle.c` restates the four operations as readable research C. Its
source/profile/model/harness bindings and original target hashes are recorded in
`behavior/rng-lifecycle.json`; this is separate from the 644 canonical comparison
drafts. The default and 31-bit wrapper intervals remain behavior-only entries, not
new strict inventory or B credit. The original comparison drafts and their hashes
have not been overwritten.

```sh
python3 -B -m unittest discover -s semantic/tests -p test_arm_call_cluster.py -v
python3 -B semantic/tools/rng_lifecycle_check.py --rom /absolute/legal/pvz.nds
python3 -B semantic/tools/rng_lifecycle_check.py --status
python3 -B -m unittest discover -s semantic/tests -v
```

The saved run passes **1263 top-level original/native calls** spanning all four entry
points, including **626 paired masked/raw draws** on two interleaved objects, refill
boundaries, rejection of seed zero before/after consumption, reseeding a live stream,
and a controlled null/default path. Each call checks both complete 2504-byte states
and 128 guard bytes per state, the controlled global page, original callee-saved
registers/SP and stack guards. Raw/masked relations compare payload and cursor
offsets across the two objects; each object's original/native address and memory
comparison remains exact. Compiled wrong-return and wrong-memory controls are
detected. Do not add these repeated samples to the older suite as unique inputs.

Six focused synthetic tests cover the new bounded BL extension: signed forward/back
targets, conditional taken/not-taken behavior, LR/flags, stack returns, undeclared or
unmapped targets, and rejected BLX/Thumb. Only the measured original edge
`0x02034fb4 -> 0x02034f94` is authorized in this oracle; the base interpreter is
unchanged. This remains a restricted CPU model, not DS hardware/full emulation.

Preserved research failures: the initial run stopped at the base model's deliberate
`nested BL call outside bounded harness` rejection. The extension was tested before
resuming. An early cross-object assertion also wrongly compared absolute cursor
values/guard patterns between distinct addresses; per-object original/native checks
were already exact. The paired check now compares within-object cursor offsets and
MT payload, without weakening any original/native memory or guard comparison.

The null/default BSS word is an artificial initialized test input; real callers still
appear to pass explicit per-object states. Ownership/initialization of that global,
untested seeds/invalid cursors, interrupts, timing and whole-game behavior remain
unknown. Native/ARM ABI equivalence and all-state correctness are not established.

Strict completion is **blocked**, not earned by these tests: canonical seed/next
compiler outputs still mismatch, the helper tail branch is outside the BL prototype,
and this four-operation restatement has no S/N/X measurement. Five cached seed/next
comparisons were reviewed without repeating them. Next evidence should address the
specific compiler scheduling/ABI and tail-call scope, not another unchanged probe.
