# arm9:0200ca98:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200ca98.c
SHA256: 5b0d3f8d02addf6630a7a6f0103b3a79ce4a536bed6ca371a52d83ac2e422f5c
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 44, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. spin until memory-mapped register 0x02FFFC3C changes from the value sampled before the loop; byte-exact"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
