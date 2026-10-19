# arm9:020cacd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020cacd8.c
SHA256: 33a6b75e29cae818aa210d7ac985ab280765db751d454cef3e145a17eb224454
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 10, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Predicate: the word at +0x10 of the global object at 0x021DE53C is non-zero. Same 24 B; clang omits the original's explicit moveq r0,#0 (r0 is already 0 on that path) and keeps its pool word inside .text (4 instructions, 10 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
