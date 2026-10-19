# arm9:0203de44:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203de44.c
SHA256: 7b6da0d9092fd874a6051edc7db80eabeaa1db042978d38e65ebab95d46e0cd0
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 64; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 58, "target_size": 64, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. 32-byte record copy; X: the original loads all eight words then stores them (mixed ldm/stm and ldr/str), MWCC copies in 8-byte ldm/stm blocks (32B vs 64B)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
