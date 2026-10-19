# arm9:020bdb78:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020bdb78.c
SHA256: 9995475d260d57eaae1184f0dc95f153ec2642df1526dc48cd6806ff028e2584
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 20, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Registers a callback pair in the fixed two-word slot at 0x020f3ae4 and substitutes the defaults 0x020d77a4 / 0x020d778c when fn or data is NULL. Same instruction shape, but clang's three 32-bit literals are inside .text (48 vs 40) and it reuses one literal with an add for the second default."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
