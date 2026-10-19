# arm9:020b384c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b384c.c
SHA256: fa48da2f525905162c3b7d6c97e0afd56ac29e31def50e62c805a7dcaf4353d8
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 56, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 45, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Writes halfword register 0x0400100A: keeps bits 0x43 and inserts five fields at bits 14,7,8,2,13. Non-S: clang reassociates the OR chain into a tree and copies the 5th argument with a different register/frame shape than the original linear orr chain."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
