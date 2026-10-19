# arm9:02005ebc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02005ebc.c
SHA256: 002d62bedc8b7c6d4f5a4bbcad55a65e5cbff9dc08f94efec18dc2bed491d94e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 16, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier S. Clears the words at +0 and +8. Byte-exact once the two stores are volatile (this compiler otherwise emits +8 before +0, tier N); the non-volatile draft is kept as 02005ebc_h1.c."]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
