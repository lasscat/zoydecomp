# arm9:02005c3c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02005c3c.c
SHA256: 4089b19916ffe9fb0277163050324528da8110e3599ed0dfb2e2f13a1cc12c2b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 22, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Sets bit (1<<index) in the 16-bit control register at 0x020FD6E0. The original narrows the shifted bit with lsl #16/lsr #16 and loads the register address from a literal pool (8 instrs, 32 B); clang drops the truncation the following strh makes redundant and folds the shift into the ORR (6 instrs + pool word = 28 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
