# arm9:0205de40:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0205de40.c
SHA256: 81034f52b84e2e4aa4b4c952c7a17ee930200174c534ff1b9a1e9f5e15c669d3
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 100; mode: arm
Metrics: {"candidate_size": 320, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 301, "target_size": 100, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. Fills a 5x5 block of 12-byte table entries (id 4..8, index 0..4, value 10000) appended through the table->count field at +0x288; reconstructed exactly with two nested do/while loops (tier S)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
