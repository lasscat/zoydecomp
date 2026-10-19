# arm9:020c0fe0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c0fe0.c
SHA256: 763ccf724be0758df1ce0af0b3b54b1f9c1f35ab4b617223106e5930160e4283
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 120; mode: arm
Metrics: {"candidate_size": 92, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 104, "target_size": 120, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. copy table[row][0..4] (5 halves) from 0x020F6358, 0 unless row<674; original materialises five column base addresses, clang folds them to one base plus offsets."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
