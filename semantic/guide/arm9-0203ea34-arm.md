# arm9:0203ea34:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203ea34.c
SHA256: d3a25fe6f46c9fbc781727215c37f04919624459cf45334af6943059b8090837
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 5, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 10, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Doubly-linked-list unlink: (*a)->next = n->next; n->next->prev = *a (prev@0, next@4). H1 plain source CSE'd to 24 bytes. H2/H3 force the two memory reloads (volatile next field, then volatile *a too), reproducing the target's 7-instruction shape and 28-byte size, but clang's register allocator assigns r2/r3 (vs r3/r2) and r0/r1 (vs r2/r0); 5 of 7 words differ, so X. Not reducible below the N thres"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
