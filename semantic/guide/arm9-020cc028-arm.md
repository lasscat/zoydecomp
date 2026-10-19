# arm9:020cc028:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020cc028.c
SHA256: 76ccff0c87218aa3a0417b239acef7ba53d7b1616f6a65c6b640ca055e9b4d21
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 38, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Read-modify-writes the 16-bit register at 0x0400100e: keeps bits 0,1,6 and inserts four fields at bit 14, bit 7, bit 8 and bit 2. X: clang materialises the base inline, reassociates the OR chain and keeps the frame register in fp (48 vs 40 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
