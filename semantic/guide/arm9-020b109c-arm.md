# arm9:020b109c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b109c.c
SHA256: fa7b333c71326642d20832c3ebec9d3bcb394e53111e5b931e775b1da02e0262
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 36; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 7, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 16, "target_size": 36, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. true while (object->[0x2c] - owner->[0x688]->[0x18c]) < 0xe10. X: clang hoists the zero materialisation and uses different registers for the load chain (7 diffs, same size)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
