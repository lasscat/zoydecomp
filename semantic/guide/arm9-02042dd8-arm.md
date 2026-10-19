# arm9:02042dd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02042dd8.c
SHA256: 75af67fe64b6c49c0f0713376ed0407c9bf37c68d26270e4b3e7b4e12e9a409d
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 7, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Initialise a node: two zero words plus a pointer at +0xc to the word at +4. N: clang23 sinks the address calculation after the two zero stores and swaps the zero/address registers; 4 of 6 instructions differ (same size, same effect). volatile keeps the stores separate (clang would otherwise merge them into STM)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
