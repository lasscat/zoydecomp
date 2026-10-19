# arm9:0201d66c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0201d66c.c
SHA256: 762559611f94c76254bf3da0dbeaa1af823d74d4adba595ab3b325759b1b7d64
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 80; mode: arm
Metrics: {"candidate_size": 80, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 20, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 69, "target_size": 80, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Bounded copy of at most n bytes from src to dst, stopping after a copied NUL and NUL-padding the rest. Non-S: original keeps a load of the just-stored byte and post-index stores; clang restructures to index form and drops the reload."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
