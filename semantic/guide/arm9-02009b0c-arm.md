# arm9:02009b0c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02009b0c.c
SHA256: 2c11d86bab65afa9c065ddfcb99ae936188239cd5dd9210e4a5d89c31fdbbb13
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 1, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 2, "target_size": 16, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Returns *(int *)self when the signed byte flag at +3 is non-zero, otherwise the self pointer (the original never materializes zero). Size exact; the only differing instruction is the flag load: target ldrsb (sign-extending) vs clang ldrb, because only a zero test consumes the value and the extension is provably dead. Both a value-returning and a branch-shaped draft (02009b0c_h2.c) give the same ld"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
