# arm9:020019ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020019ac.c
SHA256: 4ab0ad732440f186191dabd1f8b65dfd84c137bb2d78cebe268647fa560efc35
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 88; mode: arm
Metrics: {"candidate_size": 88, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 21, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 70, "target_size": 88, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. display mode / BG0 char-base tile address; same 88B size but clang if-converts/reorders the guard branches (3rd arg kept)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
