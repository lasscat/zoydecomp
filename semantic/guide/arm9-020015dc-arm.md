# arm9:020015dc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020015dc.c
SHA256: 734628fa3f1c4ae8c52eb809423367d0d84fb399fcb76295bf7a47b52e71d4d3
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 45, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Screen/map base from DISPCNT(0x04000000) bits27-29 and BG0CNT(0x04000008) bits8-12. Non-S: this clang materializes 0x04000008 with mov+orr (no pool), folds the field shift into 'and r1,r2,r1,lsr#11' and uses orr instead of the original pool load + 'and then lsr/asr' + add chain."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
