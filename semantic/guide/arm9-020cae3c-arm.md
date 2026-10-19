# arm9:020cae3c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020cae3c.c
SHA256: 4c348b63132fbce106815e556e4dc19b7372b9c37dcf1b5794293507883e0eb0
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 6, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Clear byte 3 then byte 1 of the fixed global record at 0x021de53c. X: literal pool appended to .text and clang23 shifts the base by one byte and clears bytes 0/2 of base+1 (same bytes, different encoding)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
