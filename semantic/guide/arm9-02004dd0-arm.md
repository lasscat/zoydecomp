# arm9:02004dd0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02004dd0.c
SHA256: e63383b9b86e2508ddf60c7c0f27ddb3d337008b70e8a4441dc513a99b2ac92b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 108; mode: arm
Metrics: {"candidate_size": 100, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 81, "target_size": 108, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Stream context init: cursor = base + 4, total = size, avail = size - 0x40 (rounded down to a multiple of 4), mode = 0x3f/0x1f from the cursor parity, then clears the 14 remaining words."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
