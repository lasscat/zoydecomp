# arm9:02067d8c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02067d8c.c
SHA256: 645d122cb210af4b5ed6879ed988df2a8e818c24eb3a119931f512aca077ccf3
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 32, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 34, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Exchanges the low 16 bits of the words at self+0xc and other+0x44, then decrements self+0x10. Target loads a full word and zero-extends it with lsl/lsr (10 instructions, 40 bytes); clang narrows that load to ldrh and drops the masking (8 instructions, 32 bytes). A volatile variant that keeps the word load is kept as 02067d8c_h2.c but clang then builds 0xffff with mov+orr/and (44 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
