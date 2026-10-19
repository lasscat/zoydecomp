# arm9:020247ec:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020247ec.c
SHA256: f7867475b2f416a6216e80d65e89deb3743a7c3ece4d6c16d5a3deb187aa5a5d
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 132; mode: arm
Metrics: {"candidate_size": 148, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 138, "target_size": 132, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Variable-length integer reader: low bits of byte0 give the length; writes the value to *out and returns the advanced pointer. X: clang replaces the original ldrsb + byte loads with ldrb plus mvn/and mask sequences and reorders the byte merge (37 instrs vs 33)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
