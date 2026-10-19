# arm9:0207aff0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/initial-leaves/0207aff0.c
SHA256: e095d3d70bbdaf87887be056d6d980c70ba5cb879d2b3e31b71bffdb69133e1b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 30, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner/field semantics and behavior not validated; instruction or size discrepancy remains
Failed hypotheses: ["Model only the observed operation with raw opaque pointer/word offsets; preserve unknown owner and field meanings. Measured X; see preserved worker evidence."]
Next hypothesis: Use a switch over the unknown +0x24 word with cases 21 and 46 returning one, preserving the unknown owner/field interpretation.
Behavior evidence (separate): {"status": "not tested; observed source shape is not behavioral validation"}
