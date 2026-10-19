# arm9:0200b52c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200b52c.c
SHA256: a8fde340d85fef527171c29617696693435b7fdef432c4d7222a1331594d2c0f
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 6, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 18, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. writes inner(+0x04 of arg r1)->+0x08 minus ->+0x04 to *out and returns 0; the record arrives in r1 so the first argument is unused; clang materialises the zero last and picks other registers (28/28, 6 instructions differ)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
