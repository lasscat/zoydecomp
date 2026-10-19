# arm9:02039eac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02039eac.c
SHA256: 29f4e5650b93db2073354eb2648e7f5a08c174acb2b6fd1b335ca97ba4e02c58
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 38, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Repack three signed words (+0,+4,+8) into (a>>3)<<5 | x>>3 | (b>>3)<<10 truncated to 16 bits. X: clang23 masks each field (mvn/and/orr with 0x1f8, 0xff00) instead of the original shift-or-then-truncate form, and merges two loads into ldm."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
