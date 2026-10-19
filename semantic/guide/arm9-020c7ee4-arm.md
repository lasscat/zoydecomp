# arm9:020c7ee4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c7ee4.c
SHA256: d942448a4c18044cba2335b59525cf783b3589658aabb38ebd7535fd7fc7a23f
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 52, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 5, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 6, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. blocked: extent is three consecutive entries (two indirect tail-jump thunks with bx ip plus one pool-backed store); MWCC emits a returning indirect call and one .text section per function, so natural C cannot reproduce the extent"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
