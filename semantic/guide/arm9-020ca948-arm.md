# arm9:020ca948:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020ca948.c
SHA256: 304bd69b709915a214aca1fc8588ef0c8831e1d275942d8725bebb56552bf0c1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 16, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Sets the byte at 0x021de53e to 1. X: the instruction shape matches, but clang folds the +2 offset into its own pool word (20 vs 16 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
