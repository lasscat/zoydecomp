# arm9:020bb568:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020bb568.c
SHA256: 95a8f0933e01161a31d3d47cbe8f959806d4dabf8c1fc291fcc14e0b9670d11b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 60; mode: arm
Metrics: {"candidate_size": 64, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 53, "target_size": 60, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Packs three arguments into a hardware block write at 0x040004c0/0x040004c4 and 0x040004a4/0x040004a8 (0x4210ffff and its >>16). X: clang picks the lowest address 0x040004a4 as base and folds the >>16 constant."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
