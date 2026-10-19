# arm9:0200d93c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200d93c.c
SHA256: 2a469baf9dad76683fc98a7f18accc3fdde130f83c467be0a8c98e2ec9235d88
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 15, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Copies the global word at 0x02fffc3c into the field at +8 of the object based at 0x020ff5fc. Both operands need 32-bit literals; the target keeps two 4-byte literals outside its 20-byte extent while clang's 8-byte pool is inside .text (28 bytes)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
