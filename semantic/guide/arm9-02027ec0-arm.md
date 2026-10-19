# arm9:02027ec0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/02027ec0.c
SHA256: 489cba9eb81bc8b94bfce7b08ad0989f578c1790ce04ea881f5cd283c9519a5d
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 22, "target_size": 24, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Bounds-checked 16-byte-stride table accessor: returns entries + index*16 when index < count else NULL. Clang if-converts the branch (hoists mov r0,#0, uses cmp r1,r3 / ldrlo / addlo) giving 28 bytes vs 24; operand/register order and the zero materialization differ from the original ldrhi/addhi/movls form."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
