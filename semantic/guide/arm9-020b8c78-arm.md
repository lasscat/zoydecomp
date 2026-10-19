# arm9:020b8c78:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b8c78.c
SHA256: b66608d4d8dd3dbf26948e648346638313c3151dfd42a29da265cc3195e0da49
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 27, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Returns (value & ~0xff)>>8 when the nibble (value>>4)&0xf is below 4, else 0. X: original keeps bic+lsr and predicated moves; clang23 proves the test equals 'bits 6-7 clear' and folds to tst #0xc0 / lsreq (candidate 20 vs target 32 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
