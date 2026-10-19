# arm9:020b2c00:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b2c00.c
SHA256: f2849530812edd72c8bcbdd89212ef72ec3e8a1536b2c0ddf3ca45e7126efcd9
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 31, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Push value into the per-index buffer: counts[] at +0xe8, blocks at +0x104 with a 0x200 stride, entries at the start of each block. X: clang23 keeps the loaded count in a register (struct-member TBAA) instead of re-reading it for the increment and folds the count base as t+i*4+0xe8."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
