# arm9:0203de10:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203de10.c
SHA256: 6ff5e4a7838a9e08501b10e3b5178e1d4ae8662734ba89c1df15e1ae260ee1c0
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 38, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["5 isolated hypotheses; best tier X. stores eight words into dst[0..7] from one pointer plus seven values; X: natural C makes MWCC interleave load/store pairs and reuse r1/r2 (14 insns) where the original batches all five stack loads into r4-r6/ip/lr (13 insns)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
