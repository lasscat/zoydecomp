# arm9:0200df60:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200df60.c
SHA256: 232446b297b515524bb082b0a2159b16d7fc13e6cd39fa955b9562bb45238d77
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 104; mode: arm
Metrics: {"candidate_size": 96, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 86, "target_size": 104, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Validates 8 packed decimal nibbles then accumulates their value; non-S: original keeps two naive count-up loops, clang rewrites the digit test to a masked comparison and stride-4 induction with a different constant/test form."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
