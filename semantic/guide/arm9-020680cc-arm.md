# arm9:020680cc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020680cc.c
SHA256: 2d59ffb569c9188984711c476c2ce8b8cdcbd55b354d7337e29395b8f811b023
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 9, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Initialise a 7-word record (words 0..4 zero, word 5 one, word 6 zero); identical target hash to arm9:020531b8, so the same source. X: register names of the 0/1 constants differ."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
