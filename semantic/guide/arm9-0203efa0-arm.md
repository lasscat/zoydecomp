# arm9:0203efa0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203efa0.c
SHA256: 3ae4d625a0f00c88e8e028a25e2f434158f5df3d0a52d73a4db783d6df9727d4
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 1, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 2, "target_size": 20, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Sets bits [31:1] of *record to value while preserving bit 0. Only the ORR operand order differs (commutative): candidate orr r1,r2,r1 vs target orr r1,r1,r2; 1 instruction / 2 bytes. Multiple source spellings and a 1-bit-bitfield form all produced the same order."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
