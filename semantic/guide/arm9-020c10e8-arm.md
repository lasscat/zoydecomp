# arm9:020c10e8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c10e8.c
SHA256: 2afa1711a19fd0df0a5c3c15da517b75f5069ba50fe43b924db118c846a33bea
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 17, "target_size": 16, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Returns *(int *)table[index] for the fixed pointer table 0x020f58d0. clang cannot use its literal-loaded base with scaled-index addressing, so it emits lsl plus a register-offset load instead of the target's single ldr (24 vs 16)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
