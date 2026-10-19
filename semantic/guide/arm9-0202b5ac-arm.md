# arm9:0202b5ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202b5ac.c
SHA256: cea4132bbf6e4db041e1959b6aa243e45249732e0d5b64c56bb5f88ec30a192e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 64; mode: arm
Metrics: {"candidate_size": 72, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 65, "target_size": 64, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Scans four 6-byte table entries for the first whose two 16-bit fields bound the requested coordinates; non-S: original keeps the mul/add index loop, clang inverts to a down-counting loop with fp and a guard branch."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
