# arm9:021006bc:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/021006bc.c
SHA256: 3039b33e054c0d6b5c90ba860891f30c4b9709366db2010e2f1c7374c350de04
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 212; mode: arm
Metrics: {"candidate_size": 212, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 47, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 185, "target_size": 212, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Card read: builds the 0xb7 command from a 0x200-aligned address, polls ROMCTRL (0x040001a4) for busy, then copies CARD_DATA (0x04100010) into out until len, advancing 0x200 per block; returns early when already past the end. Exact match under the reviewed profile."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
