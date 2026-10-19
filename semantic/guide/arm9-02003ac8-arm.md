# arm9:02003ac8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003ac8.c
SHA256: 2f4f113e3a58989ce54a3020a4b101a44e57a3c1594989f1330c76e26352b1b7
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 12; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 5, "target_size": 12, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Returns the 16-bit word at 0x020fd348. X: the pc-relative load needs a literal-pool word that lies outside the recorded 12-byte extent (candidate 16 bytes); clang also folds the +8 field offset into the pooled address."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
