# arm9:020b96ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b96ac.c
SHA256: 831d2cd6bdeb156bca17e0b610da2eece80f685c3c3e07757eaa002b71ff3b42
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 44, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 25, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["1 isolated hypotheses; best tier X. Writes a packed word to the I/O register at 0x040004A4: a | b<<4 | c<<6 | f | e<<16 | d<<24 (e, f from the stack). The original ORs the shifted operands in place and pool-loads the address; clang builds the value in a different order and keeps its pool word inside .text (44 B vs 40 B)."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
