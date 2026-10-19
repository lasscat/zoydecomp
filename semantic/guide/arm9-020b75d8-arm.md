# arm9:020b75d8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b75d8.c
SHA256: a68bd26b58d3bc41135d8da555c58400413b0635a7cdd1d0804500839ff4f78e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 144; mode: arm
Metrics: {"candidate_size": 112, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 127, "target_size": 144, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Bit-buffer byte read: checks the byte limit, then returns the byte at the bit cursor, splicing two bytes when the cursor is not byte aligned."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
