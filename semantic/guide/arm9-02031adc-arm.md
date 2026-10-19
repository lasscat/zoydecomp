# arm9:02031adc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02031adc.c
SHA256: 412702510a2e06271afa4cca569be68458463e3c36e4bb52546ff7c9bb8dfbe1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 7, "target_size": 28, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Sets bit 2 of the flag word at +0x118 of the object referenced by the holder slot, when non-null. N: the original loads the holder slot twice; with volatile both loads appear, but clang swaps r0/r1 in the last four instructions (4 instructions / 7 bytes differ)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
