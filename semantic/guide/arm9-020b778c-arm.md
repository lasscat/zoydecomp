# arm9:020b778c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b778c.c
SHA256: bbbd77e8b233bb4b5607240745274619156c93406ac719031e4b0c923f14a2ac
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 2, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 6, "target_size": 20, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Returns the word at +4 when the word at +8 is non-zero, else 0. Size exact; clang emits the predicated load before the zero materialization where the target emits moveq first (2 differing instructions). A pointer-typed draft (020b778c_h2.c) gives the same order."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
