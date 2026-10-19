# arm9:020b1af8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b1af8.c
SHA256: 96bc36ba2380631d55cbfca4a8f3ce985736b22aae92ef1edcdcb1f11df106af
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 17, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. copies the two signed bytes of the argument to +8 and +9 of 0x02108970; clang folds +8/+9 into the pool constant, uses non-sign-extending ldrb and interleaves load/store (28 vs 24 bytes)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
