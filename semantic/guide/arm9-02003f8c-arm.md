# arm9:02003f8c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003f8c.c
SHA256: 10641eb12f7d2769f427ac8f07d052735bc0efc07266ccffc20a3c1ffd37fb2c
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 48; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 30, "target_size": 48, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. Save IE(0x04000208), mask it off, clear IF(0x04000210) bits, re-read IE (unused), restore IE. Non-S: clang materializes 0x04000208 with mov+orr (original used a pool load) and emits bic instead of the original mvn+and."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
