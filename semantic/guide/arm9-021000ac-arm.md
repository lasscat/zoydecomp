# arm9:021000ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/021000ac.c
SHA256: 84bc0427190ad29b8b287699f8bc1e9f1d950619b4fc04f6af4ac8863a2d5b2c
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 52; mode: arm
Metrics: {"candidate_size": 52, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 11, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 51, "target_size": 52, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. spins on DIVCNT bit15 then returns (64-bit DIV_RESULT + 0x80000) >> 20; X: the original fetches the result register pair with one ldm r1,{r0,r1}, MWCC issues two ldr (56B vs 52B); the rest of the sequence is identical"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
