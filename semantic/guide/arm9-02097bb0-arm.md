# arm9:02097bb0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02097bb0.c
SHA256: cbaf8f409a18ba75c0c755194e6f8c79a560d4d19ac4d67d62256b8b276e5335
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 21, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Signed test whether the counter at +0x5e8 has reached 2500. X: clang rewrites >= 2500 into > 2499 and builds the threshold with mov+orr plus a pre-zeroed result register (28 vs 24 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
