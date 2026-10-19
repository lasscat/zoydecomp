# arm9:02068ff0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/initial-leaves/02068ff0.c
SHA256: 433a5e23dfe367d047b43a9c2187b82c01a3106f08825feb5148a79dd0482fbe
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 8, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner/field semantics and behavior not validated; instruction or size discrepancy remains
Failed hypotheses: ["Model only the observed operation with raw opaque pointer/word offsets; preserve unknown owner and field meanings. Measured N; see preserved worker evidence."]
Next hypothesis: Replace unsigned delta comparison with explicit inclusive bounds (4 <= value && value <= 6) over the same unknown word at +0x5c.
Behavior evidence (separate): {"report": "semantic/behavior/predicate-02068ff0.json", "report_sha256": "8f46a5987cd0c364b6b3a62070539ae6bfb0070a0b86d29904146bf2f434040d", "semantic_equivalence_proven": false, "status": "313 sampled return/full-owner/guard checks; boundary and deterministic fields; no game-state equivalence proof"}
