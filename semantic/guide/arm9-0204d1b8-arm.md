# arm9:0204d1b8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0204d1b8.c
SHA256: beced1fa923dc002f4a8ad93e3dace91cc1e611870c469c33d2ba322f09b0ffe
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 36; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 36, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Copy four words with four independent loads then four independent stores. volatile reproduces the separate accesses (clang23 would merge into LDM/STM). N: only the register names of the first and third word differ (r2/ip swapped)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
