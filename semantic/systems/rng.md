# DS RNG state lifecycle: first connected reconstruction target

Question: how do seeding, zero-seed rejection, next-index and refill transitions
interact in the DS game, and which callers own that state? This system is useful to
reproducible simulation/mod tests, but whole-game determinism is not established.

Observed ARM9 seed entry: arm9:02034f40:arm, complete 84-byte block (80 code bytes
plus pool). Next entry: arm9:02034fc0:arm, reviewed 296-byte block (280 code bytes).
Their exact hashes, ROM offsets and boundaries are in config/BWBE-r0/functions-v2.json.
The inventory remains incomplete. Do not guess other function boundaries from names.

The seed draft has explicit 32-bit fields: +0 remaining, +4 next_address, +8 an array
of 624 words. These names are hypotheses about use, not a desktop class identity.
Nonzero input stores the seed, applies the 1812433253 recurrence, stores +0 = 1,
and returns 1. Zero returns 0 without changing the mapped state. The +4 word is
untouched by this function. Native tests use a raw 32-bit address placeholder to
preserve DS offsets. Struct size is asserted as 2504 bytes for the tested harness.
Ownership/lifetime and which next/refill states are legal still need caller evidence.

Donor algorithm correspondence: ruslan831/PlantsVsZombies-decompilation commit
325b2229a7225d73870bb69322eefcda3a45bf8d, SexyAppFramework/MTRand.cpp,
MTRand::SRand(unsigned long). Independent DS recurrence constants/control flow are
recorded in docs/donors.md. DS zero-seed rejection differs. Root MIT plus the
Matsumoto/Nishimura file notice apply; see semantic/NOTICE-MT.txt. Static review only.

Current evidence: 41 sampled seed calls, 36 scenarios, four transition sequences.
Returns, all state/guards, original preserved registers/SP agree under a restricted
ARM model versus native compiled saved C. See semantic/BEHAVIOR.md for exact cases,
assumptions and exclusions. The seed remains X for instruction similarity; sample
behavior checks do not improve its tier. No full-game/hardware equivalence is proven.

Next: inspect next/refill callers and +0/+4 accesses, record legal state transitions,
then draft natural C for mt_next and extend reproducible differential transition
checks. Unsupported interpreter instructions must fail until implemented and tested;
do not replace original execution with donor behavior as the oracle. Preserve the
seed's tests while mapping which fields a mod/port can safely expose. Avoid further
seed code-shape/flag permutations without new evidence.
