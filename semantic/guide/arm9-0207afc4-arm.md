# arm9:0207afc4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0207afc4.c
SHA256: b3159bd82d009937608e18cc3df18a52c45de75425ad1a75aecd4bc52771e22b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 60, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 53, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Membership test against the constants 0x10, 0x13, 0x18 and 0x2b, returning 0 or 1. X: clang turns the || chain into a bitmap probe with branches (60 vs 28 bytes); it never emits the original's cmpne chain."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
