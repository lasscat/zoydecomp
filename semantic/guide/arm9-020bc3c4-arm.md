# arm9:020bc3c4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020bc3c4.c
SHA256: f3e93f542eff4085c13076e801f009083862a8ddcd93560645d4a1bb74d75567
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 68; mode: arm
Metrics: {"candidate_size": 68, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 14, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 23, "target_size": 68, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Seeds a 624-entry table: table[0] = seed, table[i] = 1812433253 * (table[i-1] ^ (table[i-1] >> 30)) + i for i = 1..623, then sets trailer words 624, 625 and 626 to 0, 1, 0 and word 629 to 0. Non-S: the 'mov r1,#1' materialising the 625 trailer constant is scheduled after the 624 store instead of before it (2 instructions, 8 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
