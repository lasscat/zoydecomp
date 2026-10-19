# arm9:02046db4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02046db4.c
SHA256: 91f6e44c3ec56c8a6dba6d8d11d65e4cd3776602b95ad15b2a8433bf5b482c74
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 6, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 8, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Doubly linked list splice x=*a; y=b[1]; x->next=y; y->prev=x. Target re-reads *a and b[1] for the second store (7 instructions). Volatile pointer-to-pointer args reproduce the size and instruction shape; remaining difference is physical register allocation only (candidate r2/r3 vs target r3/r2), which the unmasked comparator counts as 6 differing instructions."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
