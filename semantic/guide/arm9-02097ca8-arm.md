# arm9:02097ca8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/initial-leaves/02097ca8.c
SHA256: 897aff67c1789c6cd52f439f7c9a27492c02746aa794670c6d4a394f410ce142
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 23, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner/field semantics and behavior not validated; instruction or size discrepancy remains
Failed hypotheses: ["Model only the observed operation with raw opaque pointer/word offsets; preserve unknown owner and field meanings. Measured X; see preserved worker evidence."]
Next hypothesis: Express the result as (byte >> (bit_index & 7)) & 1, rather than a mask-and-compare boolean, while retaining the observed byte offset calculation.
Behavior evidence (separate): {"status": "not tested; observed source shape is not behavioral validation"}
