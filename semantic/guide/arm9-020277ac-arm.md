# arm9:020277ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020277ac.c
SHA256: 81b82ce4e843c7b1a0e2073f8ae9cbb80b21045778ef80e28094bba2e1567a74
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 24, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier S. Clears a 12-byte record (words +0,+4; halfword +8) then stores the caller halfword at +0xa. Exactly matches the target with a volatile-qualified record pointer, which forces increasing-offset store order; emitted opcodes are plain str/strh."]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
