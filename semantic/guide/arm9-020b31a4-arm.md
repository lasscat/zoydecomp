# arm9:020b31a4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b31a4.c
SHA256: cf7a739d2a0b809ee325767e29e7bd13e608c19219cb59fc29a3a1a106c5a3b4
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 72; mode: arm
Metrics: {"candidate_size": 80, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 66, "target_size": 72, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["27 isolated hypotheses; best tier X. bounds-checked 2-D grid fetch (rows at +0x08, cols at +0x0C, cells at +0x14, index col * rows + row) reporting the cell through *out; non-S because the reviewed profile branches on the null cell-pointer test where the original predicated it (ldrne/cmpne) and shared one failure exit, giving 76 vs 72 bytes"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
