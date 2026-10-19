# arm9:0201d5a4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0201d5a4.c
SHA256: 7f652b427568bff0c81e9bbf854226c487c0bf775cea312d2147ad171d93e69c
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 200; mode: arm
Metrics: {"candidate_size": 264, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 238, "target_size": 200, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. String copy: copies the NUL-terminated string at src to dst and returns dst, using word copies while dst and src share 4-byte alignment and costed byte copies otherwise. X: size 124 vs the 200-byte original; the original aligns with a counted byte loop and a peeled NUL loop using pre-increment stores, which the reviewed MWCC expresses as post-increment loops."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
