# arm9:0202ca74:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202ca74.c
SHA256: cf52ed5929dd4fd091089fb54c2a9bebb65975bf25b8ca1fc1985f00cb9f6b85
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 14, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["7 isolated hypotheses; best tier X. Tests bit 1 of the 32-bit state word at +0x24. clang canonicalises the test to mov r1,#1 / and r0,r1,r0,lsr #1 (16 B) where the original uses tst/movne/moveq (20 B); value-equivalent, sizes differ."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
