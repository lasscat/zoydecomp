# arm9:0203ba04:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203ba04.c
SHA256: e9f1a04cf144ad88c6f89ce61a6d33b6884a91b7ee20611e9a1506f995a1cab1
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 36; mode: arm
Metrics: {"candidate_size": 36, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 4, "target_size": 36, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier N. Copies a 16-byte four-word block from the second argument to the first, all loads before all stores. N: only the register choice for the first and third word differs (original ip, clang r2), four bytes in total."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
