# arm9:020b64b8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b64b8.c
SHA256: d2368defc114174198b6416deabc029c01215ba3408d409de76cf94b2989e2bf
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 3, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 20, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Programs a three-word block: 10 goes to +0x564 and value_a/value_b to +0x56c/+0x570. Same 20 B; clang materialises 10 lazily into r1 instead of hoisting it into r3 (3 instructions, 9 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
