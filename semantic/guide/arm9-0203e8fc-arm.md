# arm9:0203e8fc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203e8fc.c
SHA256: 9d6b753b0e8243e426ef415745cf970fa1b34d6a7eec24f99779bd17c87c558a
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 16; mode: arm
Metrics: {"candidate_size": 16, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 16, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier S. Zero two words at r0 (p[0]=p[1]=0)."]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
