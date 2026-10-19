# arm9:0203bb58:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203bb58.c
SHA256: 4ae78d098bb454fd8c7b5702858766741837a20fb60b00db4c94b71d0f06815b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 88; mode: arm
Metrics: {"candidate_size": 88, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 19, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 67, "target_size": 88, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Default-initialise an object's fields; non-S: clang reorders the stores and materializes the -1/0x7fff/0x2a2 constants differently (19 instruction diffs)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
