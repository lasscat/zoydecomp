# arm9:0203be48:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203be48.c
SHA256: 019cea52b5471941648ed7fdaf7cb94c871f58e521c42959f9662a5ec9a74466
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 7, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier N. Structure init: field(+0x0)=0, field(+0x4)=0, field(+0xc)=&field4 (field +0x8 untouched). 4 instr / 7 byte differences only from register choice (r1 vs r2) and add scheduling (target computes &field4 before the zero stores)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
