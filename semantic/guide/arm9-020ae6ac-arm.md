# arm9:020ae6ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020ae6ac.c
SHA256: 2f4dc0747975e5fab2e9d2f2f7b6464606b58f8ef7be0933545ea1cd5e606108
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 1, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 1, "target_size": 40, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Returns 1 when the signed 64-bit stamp (record+0x30:record+0x2c) minus other->field_0x10 is below 300. N: 1 instruction / 1 byte differs - clang folds the zero high half of the 64-bit constant into sbcs r1,r2,#0."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
