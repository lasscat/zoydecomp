# arm9:0206ee14:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0206ee14.c
SHA256: 77dd060f438d0f17d0a1983c7fd256411077a8a1ec7c489802a4cc01fc114c53
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 8; mode: arm
Metrics: {"candidate_size": 8, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 8, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier S. Word getter at +0x208 of the object passed in r1; the leading argument register r0 is never read, so the source keeps a leading unused parameter. Byte-exact."]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
