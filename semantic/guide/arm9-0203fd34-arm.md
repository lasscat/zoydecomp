# arm9:0203fd34:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203fd34.c
SHA256: 91bdef50ead18fab247d6bb21ffa4252497f6e95a6465f1dbfc120a22c2ca04c
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 23, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Element accessor for a buffer that keeps short payloads inline: bit 0 of the first word selects the inline data at self+2 or the pointer at +8, then index*2. X: clang narrows the load to ldrb and folds the single-bit test into tst (24 vs 28 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
