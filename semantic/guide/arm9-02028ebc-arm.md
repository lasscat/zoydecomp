# arm9:02028ebc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02028ebc.c
SHA256: 90c913d08ae2a9e8968606c7bf3c8e85733e8d8da4cdf176d6b621d46edb3660
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 23, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["8 isolated hypotheses; best tier X. Sets the first three words of the array to all-ones. Non-S: clang fully unrolls the 3-iteration loop into three stores; the original keeps a rolled loop with mvn/str/add/cmp/blt."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
