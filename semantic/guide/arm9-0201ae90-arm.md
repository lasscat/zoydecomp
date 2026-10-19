# arm9:0201ae90:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0201ae90.c
SHA256: 33b45be7cddd19f9f61ee809a8b0bd9fcb9719ae19d1164f3aeaeb7cf77fe868
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 112; mode: arm
Metrics: {"candidate_size": 92, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 90, "target_size": 112, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["15 isolated hypotheses; best tier X. Classifies an IEEE-754 double bit pattern (two-word struct passed by value -> 16-byte frame) and returns 1 (exp=0x7FF, mantissa/lo non-zero), 2 (exp=0x7FF, mantissa and lo zero), 3 (exp=0, all zero), 4 (other exponent) or 5 (exp=0, some bit set). Non-S: this profile tail-merges the three returns into one epilogue (`b` + shared `add sp,#0x10/bx lr`), 104 bytes vs the original 112, where each return"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
