# arm9:0203bbb0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203bbb0.c
SHA256: 26635027a5816745bcd7dcf6250fd4e431b884f1479e0d1ccef607776e4c263b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 88; mode: arm
Metrics: {"candidate_size": 88, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 20, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 67, "target_size": 88, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Initialise a 28+ byte state block (pointer 0x020E17D4, ones, 0x2A2, zero, -1, 0x7FFF, 0x1F). Non-S: clang merges adjacent stores (stmib), materialises -1 with mvn and 0x7FFF with mov+orr, and loads both pool constants differently from the original sub/rsb + two back-to-back pool loads."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
