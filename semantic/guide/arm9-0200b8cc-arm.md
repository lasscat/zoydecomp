# arm9:0200b8cc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200b8cc.c
SHA256: df9f7a82e37dd912e49cea423ae3a197d87b93ae8ca9b6b0f1f66100de3879c2
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 32, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 7, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 14, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Stores two values at +0x54/+0x58 keeping them mutually exclusive (b==0 clears a; else a==0 clears b). X: original branches (cmp/moveq/beq), clang23 if-converts both assignments into movne selects; same 32-byte size, 7 instruction diffs."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
