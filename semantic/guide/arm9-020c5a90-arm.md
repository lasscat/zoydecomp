# arm9:020c5a90:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c5a90.c
SHA256: 49489ac6486f085e6559ee8a8127dc80780218556a34079105d279a079a499a4
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Getter for the 32-bit field at +0x1c of the global object at 0x021DB040. Instructions match; clang keeps its pool word inside .text, 16 B vs 12 B."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
