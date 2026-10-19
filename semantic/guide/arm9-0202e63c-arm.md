# arm9:0202e63c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0202e63c.c
SHA256: 76724b480f0121cb755b93b04fcae2ac215c03e90c1b29e6d2e334400454c7e9
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 144; mode: arm
Metrics: {"candidate_size": 164, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 142, "target_size": 144, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. Selects LCD transfer block sizes: reads the top 2 bits of a per-engine halfword from the pointer table at 0x020D48E0, reads the engine display-control mode (0x04000000 when index<=3, else 0x04001000) & 7, then writes 0x10<<bits to both outputs for engines 2/3 in the fast modes, otherwise 0x40/0x20 selected by the two field bits. X: 168 vs 144 bytes. The original's 'ldrgt' references a second pool "]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
