# arm9:02015bf4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02015bf4.c
SHA256: 2b17d4423694646ea6153d1d672e26f3a2d075801ae5f8926a37471c4dbbdeae
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 76; mode: arm
Metrics: {"candidate_size": 76, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 18, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 63, "target_size": 76, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["4 isolated hypotheses; best tier X. one's-complement 16-bit fold of count/2 halfwords, returns (low+high folded) ^ 0xffff; exact"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
