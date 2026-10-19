# arm9:0209bdcc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0209bdcc.c
SHA256: 9e60d021b55ba90770adb1144ffcd773e85fe9dbdd2d3a5522b52caed7386704
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 92; mode: arm
Metrics: {"candidate_size": 400, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 383, "target_size": 92, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. clear a 0x18c-byte record's three tables (0x35, 4 and 0x25 words) and seed +0x188 from the global at 0x021069f4; S exact"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
