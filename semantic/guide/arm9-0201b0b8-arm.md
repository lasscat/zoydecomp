# arm9:0201b0b8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0201b0b8.c
SHA256: a7b1e47e32051607bc2f276cc336b1e44ddf92b75b444b5794aa889944b2e1d6
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 64; mode: arm
Metrics: {"candidate_size": 68, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 57, "target_size": 64, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. n-limited byte compare returning -1/1/0; original stays leaf in r0-r3/ip, clang reserves r0 for the result and pushes fp/lr."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
