# arm9:020c713c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c713c.c
SHA256: cf9b4cf35daf901a6e084f8b421dfbf3bb66fc418b20d4f01b6dc52a4a623800
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 18, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Reads the 16-bit register at 0x04000208, writes 1 and returns the previous value. X: clang builds the register address with mov+orr instead of a pool load (24 vs 20 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
