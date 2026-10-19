# arm9:02028efc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02028efc.c
SHA256: a15f72e3ab67ee90de829efe7435c8ac290b9d69e330bf8f0bebbc8de5466457
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 29, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Clears the three 32-bit words at +8, +0xC, +0x10 to -1. X: original kept the 3-iteration counted loop (add/cmp/blt); clang23 fully unrolls it to three stores even with a volatile pointer (candidate 20 vs target 32 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
