# arm9:020b82e0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b82e0.c
SHA256: 605cbf1c8b8aa73ea2dd9538a02ef4cd798fc1a7f3635a0196d75630ef3ccbc9
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 5, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 10, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Stores a value at +0x08, sets the byte at +0x04 and returns the previous content of +0x0c. X: clang materialises the constant 1 late (between the two stores, in r1) and parks the old value in r2, where the original uses r2 for the 1 and r3 for the old value; five of six instructions differ."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
