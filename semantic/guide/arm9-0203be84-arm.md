# arm9:0203be84:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203be84.c
SHA256: 4ca87ac06adb89f39853b63d9a58edb74a1f769110b4b981ac2f59a38556ec6a
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 48; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 11, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 34, "target_size": 48, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Tagged-list node read: tag bit 0 clear -> returns the 7-bit payload packed in byte 0 (bits 1..7) and advances the cursor one byte; tag set -> returns word +4 and stores word +8 to the cursor. Non-S: the same 48 bytes are emitted, but the payload extraction uses r3 as the shift intermediate and the indirect path schedules the +4 load before the +8 store (4 instructions, 8 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
