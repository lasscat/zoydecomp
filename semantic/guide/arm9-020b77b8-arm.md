# arm9:020b77b8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b77b8.c
SHA256: 909f3a57e3e8e55bdcd29dbef4c90d7b109c63b37f5743ac4478a79bee752fb4
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 5, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. signed test limit(+0x14) >= current(+0x10); X: clang zero-initialises the result register, swaps the operand order and moves the loads (5 instructions differ)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
