# arm9:02067db4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02067db4.c
SHA256: 992d545df2a591cbc2eac2e8c1dd8640433d57d5e93e03e8b746a74bdee6416b
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 40; mode: arm
Metrics: {"candidate_size": 40, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 9, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 9, "target_size": 40, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["5 isolated hypotheses; best tier X. init seven words, field 5 = 1; X: instruction sequence identical but clang swaps the zero/one registers (r2=0,r1=1 target vs r1=0,r2=1)"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
