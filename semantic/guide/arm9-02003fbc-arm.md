# arm9:02003fbc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003fbc.c
SHA256: 233c2618e233dd9262bcef283ffb4bd435fadcf70fa5aafe8e296f3f02fb7da7
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 29, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Swaps the 32-bit word at 0x04000214 while clearing and restoring the 16-bit enable at 0x04000208, returning the previous word (a third, unused read of the enable register is preserved). X: clang builds 0x04000208 with mov+orr instead of a pool load; 44 vs 40 bytes."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
