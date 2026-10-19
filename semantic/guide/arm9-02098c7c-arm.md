# arm9:02098c7c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02098c7c.c
SHA256: 0b5e9c0be0c5c854ea95a6fd5e76a5ab5a38ca6fa5c3666110ebfb6cba8e5469
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Tests bits 3, 5 and 6 of the 16-bit field at +0x60 and normalises the result to 0/1. X: clang folds the test into ands + movne (16 vs 20 bytes) where the original uses tst + movne/moveq."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
