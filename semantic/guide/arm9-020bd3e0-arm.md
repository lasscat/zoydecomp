# arm9:020bd3e0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020bd3e0.c
SHA256: 0f8707aac854952b9cc5ffc74ce77ade66a00dfdc74dbc59f142134c643057db
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 38, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. writes four packed fields into the 16-bit register at 0x0400100C keeping the bits outside mask 0x43; clang saves fp instead of r3, computes the argument contributions before reading the register and needs the pool (48 vs 40 bytes)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
