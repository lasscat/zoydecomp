# arm9:0207af90:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0207af90.c
SHA256: 967710c0625e53dd2a9dd0138988da1f4229606f6115ec372ca2ad4a57f93951
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 52, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 12, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 42, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. true when the code is one of {8,0x18,9,0xa,0xc,0xf,0xe,0x1f,0xd,0x2a}; X: the original is a straight predicated cmpne chain, MWCC converts the OR-chain into a shifted mask bit test (60B vs 52B)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
