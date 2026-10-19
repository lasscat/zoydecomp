# arm9:020395dc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020395dc.c
SHA256: 3e863a4f89b6cc7f8ffbcacf41d12318e56fecdd835a53079dd75abdd99beb4e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 36; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 36, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["5 isolated hypotheses; best tier N. Copies a 16-byte record as four independent word moves. N: same size and access order, but clang assigns r2/ip differently from the original's ip/r3/r2/r1 (4 instructions / 4 bytes differ). volatile prevents clang's ldm/stm merge."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
