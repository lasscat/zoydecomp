# arm9:020cc634:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020cc634.c
SHA256: e0487df796e3137a2e57874b51000aed3562ba0b27ee6633ddf0e4d56e8e76c1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 38, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Read-modify-write of the 16-bit register at 0x0400100c: keeps bits 0, 1 and 6 and inserts four argument fields at bit positions 14, 7, 8 and 2. X: clang allocates a frame (push {fp,lr}), builds the address with mov+orr and merges the orrs differently (48 vs 40 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
