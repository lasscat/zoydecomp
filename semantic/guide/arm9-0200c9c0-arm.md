# arm9:0200c9c0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200c9c0.c
SHA256: 73a8c264345473f1804e981225faef9df29e0f5e5c04dfbd2000059ea4d0558d
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 3, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["6 isolated hypotheses; best tier N. empty busy-wait: re-read the global word at 0x020ff5e0 while it holds 1; N because the address goes to r1 here and to ip in the original (2 instructions differ), four source shapes all give r1"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
