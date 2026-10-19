# arm9:02068fc0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02068fc0.c
SHA256: cec1297ab9b5fc6dce092e80dd9dcaed667ad4c6a378395870cdd76b7dde6383
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 22, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Clamps value into 0..0x1f and stores it as the halfword at self+0xd0. clang folds the lower clamp into the smax idiom bic r1,r1,r1,asr #31 and needs one instruction less, 20 B vs 24 B."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
