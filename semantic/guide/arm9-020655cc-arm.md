# arm9:020655cc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020655cc.c
SHA256: d53a69fef4de1fa31b82574e9c853f47226ada009d5068a5771f933da690d8f1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 35, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["5 isolated hypotheses; best tier X. consume amount from counter at p+0x5000+0xb00; X: clang folds the two offsets into p+0x5b00 and uses branchy GE form, 40 vs 32 bytes"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
