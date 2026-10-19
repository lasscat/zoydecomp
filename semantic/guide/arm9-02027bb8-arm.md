# arm9:02027bb8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02027bb8.c
SHA256: 630e0af45c3570951fb1f7ef7b4d36d2dbe1fbe00e7387faab1da8af651fa9ce
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 44; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 6, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 8, "target_size": 44, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. Publish a shared value to every node of a list and then to the owner; non-S: clang assigns node/value to the opposite registers and folds the first node load (6 instruction diffs); the volatile read was kept to reproduce the original's independent reloads."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
