# arm9:020c768c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c768c.c
SHA256: ab9e806ace81ea31a17cdc0e29bcd61e2cbde8c91bab7da9d7301478898d115d
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 164; mode: arm
Metrics: {"candidate_size": 136, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 146, "target_size": 164, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Output-table setup: for each of two slots whose byte at 0x021de3d0 is non-zero, copies the first two halfwords of the 0x30-byte record at 0x021de340 into the 16-byte record array at 0x021de298 with the last two words zeroed, then sets bit 1 of the state word at 0x021de250. X: the reviewed MWCC rematerialises the absolute table addresses as immediate add chains instead of hoisting them into registe"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
