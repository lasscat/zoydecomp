# Reconstruction for understanding, mods and ports

Choose a connected system and a concrete question about its behavior before choosing
function IDs. Favor useful state transitions, data ownership and interfaces over a
count of trivial matches. Keep natural ASCII C/C++ readable: meaningful operation
names, named fields, explicit widths and short explanations of invariants. Use
address-qualified unknown names and documented padding where identity/layout is
uncertain. Do not promote reference desktop layouts, types or vtable slots to DS facts.
A matching build preserves original bugs; a proposed fix belongs in a separate mod.
Portability is a goal, not a claim that partially inferred C already runs elsewhere.

Each system dossier records DS entry points/callers, target hashes, reviewed
boundaries, observed fields/offsets, uncertain signatures, ownership/lifetime,
constants/control flow, reference mapping/license, useful interfaces and open questions.
State what a mod could safely change and what still needs investigation. Explain
source assumptions, aliasing, alignment, integer wrap/shift and host/DS differences.
Keep binary evidence separate from names and behavioral hypotheses.

## Three independent forms of evidence

| Evidence | What it establishes | What it does not establish |
| --- | --- | --- |
| Strict B | Formatted complete C block, linked and accepted by the coordinator after complete immutable-ROM equality | Correct names/types, portability, absence of original bugs |
| Behavior tested | Specific saved inputs/transitions agree with original DS instructions for listed outputs/memory effects | All inputs/states, hardware equivalence, S tier or formal proof |
| Instruction similarity S/N/X | Actual comparator/profile measurements of an unresolved draft | Logic correctness or strict acceptance |

B and B union saved S retain the same versioned function/code denominators. Report
behavior-tested functions and case/transition counts alongside them as a separate
field. A function may be X and behavior tested. Do not sum these categories.
Unknown totals and percentage-point deltas remain unavailable. A bar must name its
scope and denominator; no filled whole-game percentage without a reviewed census.

## Work loop

1. Select a useful system and write one evidence-backed hypothesis. Review existing
   drafts/probes first. Do not extend a disconnected leaf sweep to meet a quota.
2. Infer DS representation and write readable natural C. Record uncertainty and
   reference provenance, including independent DS correspondence evidence.
3. Where feasible, compare saved C with original DS instructions in a reproducible
   harness: return values, output buffers, complete relevant memory, guard regions,
   boundary inputs, state transitions and applicable ABI invariants. Save exact
   source/target/compiler/harness hashes, cases, observations and diagnostics.
4. Describe mapped memory, alignment/aliasing, arithmetic, CPU/emulator model,
   initial state, exclusions and untested behavior. Unknown instructions/accesses
   and tool failures stop the check. A host compile is not a DS execution proof.
5. Measure instruction similarity with the actual shared driver. Reuse unchanged
   hash-bound reports. A further attempt needs a new hypothesis supported by binary,
   ABI, compiler or behavior evidence. After six nonimproving focused attempts,
   stop matching, preserve the best result and review the approach.
6. Bank useful unresolved source, tests, profiles, provenance and failed/next
   hypotheses on wip/semantic. Each saved source needs hash-bound metadata, even
   when it fails to compile; errors receive no similarity tier or progress credit.
7. Only the coordinator selects individual strict reconstructions, formats first,
   runs tests and the complete-ROM gate, then stages explicit paths. A local exact
   comparison is only a prefilter. Never merge the research branch wholesale.

Current runnable behavior coverage is documented in Track B's semantic/BEHAVIOR.md.
It uses a restricted ARM interpreter, not validated DS hardware/full emulation.
New models require focused model tests and a precise description of their limits.
