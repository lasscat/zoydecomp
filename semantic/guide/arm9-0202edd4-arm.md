# arm9:0202edd4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202edd4.c
SHA256: 615309ae70d213e4632cf55515dae1ba6eb15528e89b2fc487e30883059d8642
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Clears the three leading words of the global record at 0x021037f0 in the emitted order +0x08, +0x00, +0x04. X: the code is byte-identical, clang only appends its own literal-pool word (28 vs 24 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
