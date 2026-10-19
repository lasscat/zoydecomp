# Understanding the results

The project records three different kinds of evidence. They must not be added
together or described as proofs of the same thing.

| Result | Meaning |
| --- | --- |
| Verified reconstruction (B) | A complete C block passed formatting, compilation, linking and comparison of the entire rebuilt ROM with the original. |
| Behavior tested | The draft agreed with original DS instructions for the recorded inputs, outputs, memory effects and transitions. Untested behavior remains unknown. |
| Draft comparison (S/N/X) | A measurement of isolated compiled code. It does not establish logical correctness or strict acceptance. |

S means equal size with zero instruction and resolved-byte differences. N means
equal size with at most four differing instructions and sixteen differing bytes.
X covers larger differences, including a size mismatch. Registers, literal values
and instruction order are not ignored. Tool failures receive no tier.

The RNG seed draft is X but passes its saved behavior cases. Four nearby predicates
are N and also pass saved behavior cases. A changed instruction can still alter
logic; closeness alone is not enough. The restricted ARM model has focused tests
but has not been validated against DS hardware or a complete emulator.

Status, progress documents and handoffs report verified code and verified-plus-local
exact drafts over the same function/code totals. Those totals remain unknown while
discovery is incomplete. ROM size is not code size. No full-game percentage or
all-state equivalence claim is made.
