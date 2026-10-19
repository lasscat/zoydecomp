# arm9:02003ad8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003ad8.c
SHA256: d89c684884f96eb6b28f5d994d4edcfabae30374a2227d9830aa8579ba4df7e1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Reads the unsigned 16-bit field at +0x0a of the global record at 0x020fd340 (unknown record). X: the original's pool word (0x020fd340) sits outside the recorded extent and it offsets the load with #0xa; clang folds the offset into its own in-text pool word; 16 vs 12 bytes."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
