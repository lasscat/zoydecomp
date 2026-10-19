# arm9:0206ee1c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0206ee1c.c
SHA256: 81825e730e91a8bcf208470f0b1dfe7be4339ed225b6fe46d2602714100ecd8a
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 31, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["7 isolated hypotheses; best tier X. indexed 0x20c-byte record lookup; X: clang masks the 16-bit index with mov/orr/and instead of lsl/lsr, 36 vs 32 bytes"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
