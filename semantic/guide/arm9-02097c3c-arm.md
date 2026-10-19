# arm9:02097c3c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02097c3c.c
SHA256: bf8e767e25103310aed89fb89060cbf442ab206a577952835a0d957a0da60dbb
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 37, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. sets bit `bit` in the flag-byte array at p+0x5ED; clang hoists the byte index into the address instead of recomputing `lsr #3` for both the load and the store, and needs one add instead of the original add #0xed + add #0x500 (28 vs 40 bytes)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
