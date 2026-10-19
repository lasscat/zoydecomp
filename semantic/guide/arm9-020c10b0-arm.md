# arm9:020c10b0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c10b0.c
SHA256: d6056ef0ee836e8dffb3fc80cc6dd36ecfd79a16f87feac5c8854e08e2fc98ee
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 15, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Returns word `index` of the global table at 0x020DBF94. The original uses ldr r0,[r1,r0,lsl #2]; clang pre-shifts the index and keeps its pool word inside .text, 20 B vs 12 B."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
