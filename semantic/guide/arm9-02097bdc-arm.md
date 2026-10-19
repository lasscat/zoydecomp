# arm9:02097bdc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02097bdc.c
SHA256: f73672cca29341488b40a98ea1bc092b86a0aaa85c6590679ca20711b99a9c36
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 23, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Bit-array test: bit `index` of the byte array starting 0x5EC bytes into self. The original forms 1<<bit and uses tst/moveq; clang folds the test to an AND with a shifted register (24 B vs 28 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
