# arm9:0203ffc0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203ffc0.c
SHA256: d218e726cf974a9eaa4be2aeec9504f1907de80ed5aa82b70f6da30d04d6319e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 7, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier N. Range/head record init: start=0, end=0, third word = self+4. The record is modelled volatile so the three word stores stay separate and in order (a plain record lets clang merge the first two into one stmib); clang then schedules the add after the two zero stores (4 instructions, 24 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
