# arm9:02003ab8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003ab8.c
SHA256: 6a1fb3281b12d018036404486d2290d87dcad7089c646aef984f9a0b708b2ce4
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Read halfword field at fixed global 0x020fd340 + 0x10. X: fixed address is materialised from a literal pool whose 4 bytes are appended to .text (the original's pool word lies outside the declared function size); clang also folds +0x10 into the pool constant."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
