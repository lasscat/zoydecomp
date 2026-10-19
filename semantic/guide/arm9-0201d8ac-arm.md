# arm9:0201d8ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0201d8ac.c
SHA256: d986e8b6503d46bd3faa4a5cfa09f6d95324b017e3b625d42fb4aefa685535b2
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 108; mode: arm
Metrics: {"candidate_size": 128, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 103, "target_size": 108, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. strstr-style search: NULL/empty pattern returns the haystack, otherwise returns a pointer to the first occurrence or 0. X: original is a tight two-loop form with pre-indexed post-increment loads; clang23 restructures the guards and inner loop (candidate 128 vs target 108 bytes, extra prologue branch and push {fp,lr})."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
