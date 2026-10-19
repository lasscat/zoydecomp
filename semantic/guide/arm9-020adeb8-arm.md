# arm9:020adeb8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020adeb8.c
SHA256: abd245807ff2358d85a16083ecce7911fe9c5cf20125bd508166b9df18bc4b45
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 8, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 16, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. True when the 64-bit deadline at p+0x2c is less than 0xe10 past the now stamp at q+0xc. X: clang23 uses immediate-zero sbcs and movlo instead of the original register-zero sbcs and movlt (signed compare)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
