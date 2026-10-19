# arm9:02097bf8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02097bf8.c
SHA256: 511bb633b91f00edb3d0886ad9bd9b04440865426c9959de682cee549a2fa46a
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 37, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Sets bit (n & 7) of byte (n >> 3) of the bit array at this+0x5ec (formed as +0x1ec then +0x400). Not S: clang folds both offsets into the load/store addressing mode, shifts by the register in the address computation and drops the original's redundant and #0xff (28 vs 40)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
