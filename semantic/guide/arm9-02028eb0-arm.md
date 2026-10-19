# arm9:02028eb0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02028eb0.c
SHA256: 3ba71bef8031d6f7429a7d3bed033f8a59d922de71806490232dd4cffa0a1283
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 12, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 2, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier N. indexed 16-bit table read; N: clang folds the scaled index into the base (add+ldrh) instead of lsl + ldrh [r0,r1]"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
