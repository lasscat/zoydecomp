# arm9:02097cc4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02097cc4.c
SHA256: 75fef72f73ba992c0a488c84ded3d3c601601d24657407b2c31fdde849d204f2
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 37, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Sets bit (index & 7) of byte (index >> 3) in the bitmap at self+0x5ef. Target splits the offset into add #0xef plus add #0x500 and keeps a byte mask; clang folds the base and the shifted index into one register-offset access and drops the mask (7 instructions, 28 bytes vs 10, 40)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
