# arm9:020c85a8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c85a8.c
SHA256: 24b448ede828c3349609c1c544a881cb5146bcfe67dd718b3a9f4cd8cbed21d3
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 32, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 8, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. clears the words at +0x18/+0x10/+0xC and the byte at +1 of 0x021DE480; clang keeps the pool but rebases it to 0x021DE481 so every store offset shifts by one and .text grows by 4 bytes (32 vs 28 bytes)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
