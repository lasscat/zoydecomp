# arm9:0207afe0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/initial-leaves/0207afe0.c
SHA256: 2a2d8ec0488ad7e167d305f4271bb6ca0641f19607b2b91d5d4ace42f1911aa0
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 3, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 16, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner/field semantics and behavior not validated; instruction or size discrepancy remains
Failed hypotheses: ["Model only the observed operation with raw opaque pointer/word offsets; preserve unknown owner and field meanings. Measured N; see preserved worker evidence."]
Next hypothesis: Correct the signature to a single unsigned scalar argument; the target compares r0 directly, while the first draft incorrectly introduced an unused first parameter and moved the value to r1.
Behavior evidence (separate): {"status": "not tested; observed source shape is not behavioral validation"}
