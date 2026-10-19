# arm9:0203ef6c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203ef6c.c
SHA256: 06765d96ae89bf5321a8e4b9b9dd9dfb08d2195ebbb8b7fe6cd1a8d8f155dea7
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 5, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 15, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Sets or clears bit 0 of the 32-bit word at +8 according to the flag argument. X: original is cmp;ldr;orrne;biceq, clang23 schedules ldr before the cmp and clears first (bic then orrne); same 24-byte size, 5 instruction diffs (below N's 4-instruction bound)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
