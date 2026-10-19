# arm9:02047dd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02047dd8.c
SHA256: 5ec9c817eab59d8b1c35461f85de3062dc8e1f621ca4721c3a57f94ab8e27761
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 17, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Applies a (set,clear) mask pair to *target: target = (target | ops->set) & ~ops->clear. Clang always fuses and-with-complement into bic (28-byte candidate vs 32-byte target with mvn+and) and swaps load order; explicit-complement, xor-0xffffffff and subtraction spellings all lowered to bic."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
