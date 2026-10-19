# arm9:0202efcc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202efcc.c
SHA256: e83999d8fbaa49174299e90cea0a31ab55c8f44eeb4cbae955509b5cde6ba95c
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 28, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier S. clears **p and then *p when *p is non-null; the volatile-qualified pointer slot reproduces the original's two independent loads of *p (documented reconstruction device, object data itself is not volatile)"]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
