# arm9:020044dc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020044dc.c
SHA256: 4f2da724e4e9f6ad43f25b6d3167f490840e9e8b19b688a3b346d9d96ce65c0b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 56, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 46, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Pops the head of a doubly linked list; non-S: original keeps the list pointer in r0 and the popped node in r2 with one shared epilogue, clang re-allocates (node in r0, early bx lr), 4 bytes larger."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
