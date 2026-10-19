# arm9:02027ed8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02027ed8.c
SHA256: c0541bba8c15c7e0aa395e14da62a706f5c4ea7d98617003af1cec5b99873e15
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 32, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 27, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Entry pointer = table base at p+4 plus count(p+0) scaled by 16 when bit 0 of the halfword at p+2 is set, else by 8. X: clang23 uses a shift-by-register select (mov 4 / movne 3 / lsl r2) instead of the original's conditional adds."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
