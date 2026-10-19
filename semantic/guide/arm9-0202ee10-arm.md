# arm9:0202ee10:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202ee10.c
SHA256: 723957676546e4fcf7467faf96579358ff8163676d98151ac390e19cd5f50ecb
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 14, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Stores value into slot `index` of the global table at 0x02103C70, slots 0x24 bytes apart. The original uses mov #0x24 + mul; clang expands *0x24 into add+lsl #2 and keeps the table pool word inside .text (24 B vs 20 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
