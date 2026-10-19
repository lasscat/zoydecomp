# arm9:02028aa0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02028aa0.c
SHA256: ddc0429ac0288497ad5dc9504816a34a14f215d3ed27bc4af9f0de1a4467c5b7
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 188; mode: arm
Metrics: {"candidate_size": 156, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 163, "target_size": 188, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Appends one 4-halfword record: derives free space from a[5..7], returns 0xfffe when there is none, else stores b[0..3]>>4 into the 0x30-stride table at 0x02101824 + idx*0x540 and returns the previous a[7]. Non-S: MWCC if-converts the inner test (ldrhls/cmpls) and picks a different register set; 42 instruction diffs at matching size."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
