# arm9:02068fd8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/initial-leaves/02068fd8.c
SHA256: f7941e58192d6ddfe4de9b4df9f226a64c6499cca8793fb9415c5dbb5b581bec
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 24; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 4, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 8, "target_size": 24, "tier": "N"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner/field semantics and behavior not validated; instruction or size discrepancy remains
Failed hypotheses: ["Model only the observed operation with raw opaque pointer/word offsets; preserve unknown owner and field meanings. Measured N; see preserved worker evidence."]
Next hypothesis: Replace unsigned delta comparison with explicit inclusive bounds (1 <= value && value <= 3) over the same unknown word at +0x5c.
Behavior evidence (separate): {"report": "semantic/behavior/predicate-02068fd8.json", "report_sha256": "6adc32d8b813a1eff3c6bec9b71aaba7fb5fc865e4c0b2092ed470096659f44f", "semantic_equivalence_proven": false, "status": "313 sampled return/full-owner/guard checks; boundary and deterministic fields; no game-state equivalence proof"}
