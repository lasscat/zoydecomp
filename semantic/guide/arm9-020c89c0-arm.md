# arm9:020c89c0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c89c0.c
SHA256: 860851f05bb0d0a91c44f04e4d67a3e705c4666e47497698f8a1be0ead37d5a1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Returns the byte at +2 of the fixed global object 0x021de480. Literal inside .text makes the candidate 16 bytes vs 12."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
