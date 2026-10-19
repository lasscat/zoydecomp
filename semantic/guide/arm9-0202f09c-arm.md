# arm9:0202f09c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202f09c.c
SHA256: 4ec3d2f82d76f88ac33fad7b297669565e0f32996926f50f0a97c75ba6bf31b5
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 20, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier S. Writes a byte at +0x41 of *self when *self is non-NULL. Byte-exact; the volatile pointer object reproduces the original's two independent reads of *self."]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
