# arm9:02003f5c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02003f5c.c
SHA256: e4499ba36f33ead66a0ff2627ecff0b36e5102b96d4ee9aae267848d673be927
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 48; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 29, "target_size": 48, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Interrupt guard that disables IME, merges a mask into IE and returns the old IE; non-S: clang materializes 0x04000208 with mov+orr instead of a pool load and drops the original's redundant IME re-read (44B vs 48B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
