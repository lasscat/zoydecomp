# arm9:0203f7c8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203f7c8.c
SHA256: 479bf8e2aedc4444e8029c2ae4e8f64a2210cc49c62f5b7456dbfd8dc239a57e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 44; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 24, "target_size": 44, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["11 isolated hypotheses; best tier X. write the 3x3 identity over nine floats (diagonal 1.0f, rest 0.0f); X because the size, instruction sequence and merged stm match but this compiler materialises 1.0f just before its first use instead of hoisting it next to 0.0f, shifting 5 of 11 instruction positions"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
