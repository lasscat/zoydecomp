# arm9:0200bbd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200bbd8.c
SHA256: 1cf0c7a6d9b5ecfe50ce0bee0d4a9062741db4bd05547df05cf397e0c410e065
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Returns the global word at 0x020FF59C. The instruction block matches the original byte for byte; only the literal-pool word (kept in the inter-function gap after bx lr by the original) is extra inside .text, 16 B vs 12 B."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
