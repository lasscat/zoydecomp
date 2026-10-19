# arm9:020013ec:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020013ec.c
SHA256: 8c3ce19cef4a57630d1dd334ff3210873071129679bb2869fe07189d633009df
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 160; mode: arm
Metrics: {"candidate_size": 132, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 148, "target_size": 160, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Fixed-point transform setup: packs the truncated 20-bit coefficients into two words and shifts the translated origin into place."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
