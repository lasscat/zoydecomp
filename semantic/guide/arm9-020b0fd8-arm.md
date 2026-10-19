# arm9:020b0fd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b0fd8.c
SHA256: d08dce0754d06c50431bf043145852da454667dc42f0a4af5b317572f3135901
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 18, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Non-zero test on the signed 16-bit field 0x100 bytes into the object found at +0x688 of *handle. X: clang narrows the load to ldrh, materialises 0x100 in a register and drops the moveq branch target (28 vs 32 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
