# arm9:0201a9b0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0201a9b0.c
SHA256: 568117e5d5ba05fc892b49fa14b48a6fe7028b351b51deee6d7da0cd00d923e0
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 8, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 15, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Copies field +0x1c to +0x24, stores +0x20 - (+0x18 & +0x2c) at +0x28 and caches +0x18 at +0x34. X: clang hoists the +0x34 store and picks a different register assignment; 8 of 10 instructions differ."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
