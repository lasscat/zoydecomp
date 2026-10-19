# arm9:0200c4dc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200c4dc.c
SHA256: a5f07bdb56084deb7a578ba8374a45e1681d7c223ff43ce93bab015519e521ba
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 2, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Polls a hardware flag halfword at 0x020ff5a0+0x3a while (flag & mask) is set. Non-S: this MWCC profile assigns the pool base to r2 and the loaded value to r1, while the original uses r1 for the base and r2 for the value (3 insns / 4 bytes); identical layout across 25 source and allocation shapes tried (struct, pointer, inline address, do-while, named locals, mask types)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
