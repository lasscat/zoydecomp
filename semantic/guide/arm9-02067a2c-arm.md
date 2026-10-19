# arm9:02067a2c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02067a2c.c
SHA256: 13e867f415eb74ee9a51c1101fcf3a6d8cb58cefa9db292817e2fc4d31a25835
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 9, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Zero-initialises a 7-word record with the word at +0x14 set to 1. Same 40 B / 10 instructions, but clang assigns the two constants to the opposite scratch registers (0->r1, 1->r2) than the original (0->r2, 1->r1), so 9 register fields differ."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
