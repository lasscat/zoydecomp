# arm9:0202ded0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202ded0.c
SHA256: 604510a8b451e7e896163a5410343fcb5fd2267413b93a4a586878ae06707ecf
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 92; mode: arm
Metrics: {"candidate_size": 80, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 82, "target_size": 92, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Fills a width x height halfword rectangle with base+i | ((attr&0xf)<<12) advancing by stride. X: clang hoists the width guard into the entry test, counts the loops down, and turns the original (attr<<12) truncation into a single lsl (20 instrs vs 23)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
