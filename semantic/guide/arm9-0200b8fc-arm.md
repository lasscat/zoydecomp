# arm9:0200b8fc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200b8fc.c
SHA256: 10384d50c67f48b9f1bcf433852c2b931a2bd198420b63cf4dadbf434ae818ca
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 15, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Tests bit 2 of the 32-bit field at +0x14 and returns 0/1. Clang never emits the original tst/movne/moveq; it recognizes a single-bit test and folds to and/lsx (16-byte candidate vs 20-byte target). No twin body in the current 68-function universe."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
