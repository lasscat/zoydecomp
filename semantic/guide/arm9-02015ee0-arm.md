# arm9:02015ee0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02015ee0.c
SHA256: 2593ce57a0d22be6d9abbc8a2cfc6c0f339d6f862f6f89d817fd4b22af3e7f37
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Clears the five byte counters at +0x25..+0x29 of the global record at 0x02100B50. clang emits the same five stores but keeps the address pool word inside .text, 36 B vs 32 B."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
