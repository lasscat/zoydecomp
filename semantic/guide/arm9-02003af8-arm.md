# arm9:02003af8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003af8.c
SHA256: ecf616890b1b229697834bcb68350a0063507cbbbe4958ba323a81b083bcfb17
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Halfword getter for 0x020FD346 (base 0x020FD340 + 6). The original loads the base from a literal pool and uses ldrh [r0,#6]; clang folds base+6 into its own pool word and emits ldrh [r0], and keeps the pool word inside .text (16 B vs 12 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
