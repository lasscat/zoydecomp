# arm9:020b8c60:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/initial-leaves/020b8c60.c
SHA256: 722dc5bb4c853801b8bbf2498cfb84e97bc68a6870e06aa7aff9f1170e2055d4
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 3, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 7, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner/field semantics and behavior not validated; instruction or size discrepancy remains
Failed hypotheses: ["Model only the observed operation with raw opaque pointer/word offsets; preserve unknown owner and field meanings. Measured N; see preserved worker evidence."]
Next hypothesis: Use a signed int view for the extracted nibble comparison, because the target uses the signed GE condition; retain -1 for values at least four.
Behavior evidence (separate): {"status": "not tested; observed source shape is not behavioral validation"}
