# arm9:0205daf4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0205daf4.c
SHA256: 05d30f18400bcb5421e60719cf4cd0b1c2dd65bfa836ff82c957b58fd23c4b68
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 16, "target_size": 16, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. stores 1000 at +0x5BAC; clang materialises the whole offset in a register (mov+orr) and uses a register-indexed store instead of the original add #0x5000 + str [r0,#0xbac] (20 vs 16 bytes)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
