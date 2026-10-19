# arm9:020b8e80:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b8e80.c
SHA256: e46f42c06ad77638957b1ff3efa98bc9a7bbbde61c4dce853141add178032e28
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 72, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 68, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. If dst is non-null copy the 12-byte default record at 0x02108db4 into it; return bit 0 of that record's first word. X: clang23 branches instead of the original conditional ldm/stm and folds the three record words into separate pool constants."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
