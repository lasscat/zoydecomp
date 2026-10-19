# arm9:02067c3c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02067c3c.c
SHA256: 3d916bdd76c7bcf8c0e279788787d98082d45ef76c86569eb2f747a02c8de594
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 9, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. zero-fills seven words with word 5 set to 1; same size and store order, but clang allocates the zero constant to r1 and the one to r2 where the original uses r2/r1, so all 9 store/load words differ"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
