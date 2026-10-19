# arm9:0203ef58:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203ef58.c
SHA256: 620bfbf3924a22c336863f4a7caa4981846ea77adf44859ec117c06acbb8e9c8
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 12, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 14, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. true when bit 0 of the word at +8 is set; the original uses tst+movne/moveq, clang folds the 0/1 select into `and #1` (12 vs 20 bytes) - every equivalent spelling tried (!(v&1), !!(v&1), v<<31, ==1) folds the same way"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
