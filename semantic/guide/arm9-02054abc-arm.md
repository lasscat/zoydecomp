# arm9:02054abc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02054abc.c
SHA256: 65732d6eb9c8ae1bc343afa70f509c5e5d24fe731049a40ccdd02f9684a4f05a
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Returns (this->f6c + 3u) > 1u. Target emits add #3 / cmp #1 / movhi / movls; clang23 canonicalizes to add #1 / cmn #2 / movlo (4 instructions differ, 9 differing bytes) - near miss N."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
