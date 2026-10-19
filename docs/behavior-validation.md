# Behavior validation record template

Use this for each connected reconstruction on wip/semantic. Readable source and
measured instruction similarity do not establish logic by themselves. Where an
executable comparison is infeasible, record `not tested` or `blocked` with a concrete
reason and next evidence; never invent passing tests. Candidate validation requires
an explicit behavior status. Unsupported equivalence claims are rejected.

- System question and module/address/mode; original ROM and target-block hashes.
- Source/profile/compiler/runner identities; native/DS ABI and integer/layout assumptions.
- DS oracle: legally supplied original instructions, supported emulator/model and exact harness hashes.
- Observable contract: return/output values, full relevant memory and guards, state transitions and applicable preserved registers/stack.
- Cases: normal and boundary inputs, signed/unsigned wrap limits, zero/null only where valid, repeated calls, reinitialization and relevant state transitions.
- Failure controls: deliberately wrong compiled C return and memory effects must be detected; unsupported instructions/unmapped memory fail closed.
- Coverage: exact executed cases and source hash; sampled agreement or failing case, never all-state correctness by implication.
- Unknowns: ownership, aliasing/alignment, valid states, hardware/timing/concurrency and unexecuted paths.
- Reproduction command; failed hypotheses; next evidence-backed hypothesis; separate S/N/X metrics and B status.

From Track B, run the existing cases and negative-control tests:

```sh
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/legal/pvz.nds
python3 -B semantic/tools/semantic_progress.py --rom /absolute/legal/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
python3 -B semantic/tools/semantic_progress.py --status
```

Five drafts currently pass 1293 sampled calls: seed 41, four connected +0x5c
predicates 313 each. Seed checks include four true persistent-state reseed/rejection
sequences. Predicate checks include 299 boundary/deterministic values and 14
controlled field-value inputs per function; actual game transitions/owner remain
unknown. All five still have N/X similarity, demonstrating that evidence axes differ.
The restricted ARM model has focused tests but no hardware/full-emulator validation.
No formal equivalence proof exists. Strict ROM verification never imports this harness.
