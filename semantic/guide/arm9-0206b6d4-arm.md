# arm9:0206b6d4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0206b6d4.c
SHA256: 75144f0fba980338aee916fae81df80fd91a952ba9396e273d4304719af8bf35
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 80; mode: arm
Metrics: {"candidate_size": 76, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 49, "target_size": 80, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Initialises an object from a global pointer table (zeroes fields, sets 1/-1/400000 and copies two fields of the global); non-S: original loads 400000 from a literal pool and uses lr as a zero temp with push/pop, clang folds the constant to mov+orr and reorders the zero stores."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
