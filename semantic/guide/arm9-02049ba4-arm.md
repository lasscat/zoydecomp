# arm9:02049ba4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02049ba4.c
SHA256: 0e332c4ccb03115922a0296227fd2e3378f56dca133d19a8252f1467e291764b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 48; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 44, "target_size": 48, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. 20-byte record copy; X: the original loads all five words into lr,ip,r3,r2,r1 then stores them, MWCC merges the copy into ldm/stm writeback pairs (32B vs 48B)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
