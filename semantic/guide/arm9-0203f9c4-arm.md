# arm9:0203f9c4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203f9c4.c
SHA256: 444d14300e6906f25f55244004e8bc90879f74413bd295c86d94f6d1600047c0
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 56; mode: arm
Metrics: {"candidate_size": 52, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 49, "target_size": 56, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. saturating counter at 0x02105F10+0x18 (0 raises, non-zero lowers but not below 0); this profile hoists the literal and speculates the load (48B vs 56B); MWCC 1.2 reproduces the exact control flow with base/value registers swapped, implying a different compiler revision"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
