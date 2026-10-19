# arm9:0200dfd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200dfd8.c
SHA256: 0e6f9eaa683e05bac3477f1ad6ee9e06f92a9263b0ffbd6747775929d160f2f1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 3, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Spins while the word at 0x020FF63C equals 1. Non-S: the literal-pool pointer is allocated to r1 instead of the original ip/r12, so the first two instructions differ only in their register fields (2 instructions, 2 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
