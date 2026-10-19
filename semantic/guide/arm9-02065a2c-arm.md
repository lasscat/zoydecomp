# arm9:02065a2c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02065a2c.c
SHA256: c18f3a0275a1edcdd8517e6a477641e74f5f461c04ab3459302e19a505c734f5
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 32, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 26, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. True when the state word at p+0x5ae4 is 4 or 5 (unsigned v-4 <= 1). X: clang23 materialises the offset as mov/orr instead of the original add #0x5000 + ldr #0xae4 and lowers the boolean as bic/clz/lsr instead of cmp/movls/movhi."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
