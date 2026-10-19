# arm9:020100bc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020100bc.c
SHA256: 4230b709a9ac834e79c46b1ccd0a07996c2ff0bd423faf6f670051b95f7ac096
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 8, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Returns 3 when the 16-bit word at 0x020fffec is zero, else 0. X: clang pre-zeroes r0 and reads into r1 (the original predicates movne r0,#0 / moveq r0,#3); the pool word is also outside the extent (28 vs 24)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
