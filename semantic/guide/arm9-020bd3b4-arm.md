# arm9:020bd3b4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020bd3b4.c
SHA256: da1e4994df1fae2d63ed8078b062e7fd1ccf10d320324e96629abe8393b56b5d
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 41, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Read-modify-write of the 16-bit register at 0x0400000c: keeps bits 0/1/6 and inserts four fields. Not S: clang computes the merged word before the read, uses a frame pointer, and needs a pool word for the register address (48 vs 40 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
