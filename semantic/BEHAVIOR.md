# What the logic check establishes

The MT seed draft passed 41 sampled differential calls across 36 scenarios. The harness executes the
legally supplied original DS instructions in a small restricted ARM interpreter,
and separately compiles the saved C to a native host library with the same pinned
clang executable. It compares the return value, all 2504 state bytes and 128 guard
bytes for identical inputs. The original execution also checks preserved r4-r11
and restored SP. Zero seed must leave state unchanged and return zero; nonzero
seeds initialize the recurrence and remaining field. The original 32 independent seed cases are retained. Four extra transition
sequences test [1, 0], [4357, 1], [0xffffffff, 0x80000000] and [623, 623, 0] with
persistent state between calls, covering reseeding, repeated seeds and zero rejection
after initialization. Each call records before/after state-and-guard hashes.
All executed cases are saved
in behavior/mt_seed.json, bound to source, target, compiler and harness hashes.

These are sampled behavior results, not an equivalence proof. The interpreter is
not a general DS emulator: only its explicit ARM subset and mapped memory are
supported. Unknown instructions/accesses, Thumb transitions, nested calls, byte
transfers and instruction-limit overruns stop with an error. No undefined opcode
becomes a no-op. The CPU model itself could be wrong; focused tests cover CMP flags,
signed conditions, readonly memory and unsupported instructions. It has not been
validated against real DS hardware or a complete reference emulator.

Assumptions include word-aligned accessible nonaliasing state/code/stack and 32-bit
unsigned arithmetic. The source's explicit raw-address field keeps native test
layout equal to the inferred DS field offsets. The native/ARM ABIs themselves,
hardware timing, interrupts, whole-game effects and untested states are not proven
equivalent. Formal analysis, broader property/fuzz checks or real-emulator differential
tests could provide stronger evidence later. They must report their own assumptions
and unknowns; passing this check alone never earns S or B credit.

Reproduce from the Track-B root (no ROM build):

```sh
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/legal/pvz.nds
python3 -B semantic/tools/semantic_progress.py --rom /absolute/legal/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
```

Reports are validated against the target, source/profile/compiler and current
harness/interpreter hashes, case counts and explicit scope. Missing/stale reports
never earn behavior coverage. Status reports five tested functions and 1293 sampled
calls separately; the seed still has X instruction similarity and no B credit.
These checks cover seed state transitions, not next/refill or gameplay transitions.
No automatic conversion from sampled tests into S or strict acceptance exists.

## Connected +0x5c predicate checks

Four adjacent drafts at ARM9 0x02068fd8, 0x02068ff0, 0x02069008 and 0x0206901c
are tested against original DS instructions. Each passes 313 calls: 299 unique
values (0..35, signed/unsigned boundaries and 256 deterministic 32-bit values) plus
14 ordered controlled field values. This is 1252 calls, plus 41 seed calls = 1293.
Checks compare boolean returns, all 96 owner bytes plus 128 guard bytes, and original
preserved registers/SP. The predicates must leave memory unchanged. No modeled
gameplay transition is claimed: the +0x5c owner and valid states remain unknown.

The source's volatile loads remain a hypothesis; stable single-threaded aligned
readable memory is assumed. Native ABI, asynchronous changes, MMIO, hardware timing,
all other values/states and game-wide behavior are untested. Each per-function JSON
report pins the target/source/profile/compiler/harness/interpreter and exact cases.
All four remain N instruction similarity; behavior samples never change that tier.

Fourteen semantic boundary tests now include deliberately incorrect **compiled C**
returns and memory writes. Both negative controls are detected against a synthetic
ARM oracle. Other tests reject absent behavior status, stale harness/target/source,
incorrect case counts/counters, unsupported instructions/accesses and instruction
limits. A synthetic negative control tests the checker, not a game reconstruction.
Use docs/behavior-validation.md as the required record for new candidates.
