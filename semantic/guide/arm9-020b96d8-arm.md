# arm9:020b96d8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b96d8.c
SHA256: 63ef203cbdea2f3068ef7da9a21f8f03eb03a3b758d8411c4be6135ec7c8e7de
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 64; mode: arm
Metrics: {"candidate_size": 64, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 14, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 47, "target_size": 64, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Packs eight fields into one word and stores it to 0x040004a8. X: size matches (64) but clang's Reassociate canonicalises the OR chain (b<<30 first, h>>3 last); four different written orders produced byte-identical output, so the original a<<26,h>>3,b<<30,... order is unreachable (14 instr diffs)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
