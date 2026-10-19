# arm9:0204f7e8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0204f7e8.c
SHA256: e7e69df41c6ce86b9a30d29f026c79883bd55642985a32d6c283729f583f7440
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 68; mode: arm
Metrics: {"candidate_size": 68, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 15, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 38, "target_size": 68, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Structure initialiser: eight 0xc61c4000 (-10000.0f) words at 0..0x1c, zero at 0x24/0x20, pointer 0x020e3058 at 0x28. X: clang synthesises 0xc61c4000 with mov+orr instead of loading it from a pool word and allocates the constant/zero differently."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
