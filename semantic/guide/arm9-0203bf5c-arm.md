# arm9:0203bf5c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203bf5c.c
SHA256: fb542e32dd8937e52bff0e249175b30bc363286343e70250bfcfa059a17b3d2a
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 32; mode: arm
Metrics: {"candidate_size": 24, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 27, "target_size": 32, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["5 isolated hypotheses; best tier X. Tagged-record accessor: the word at +0 carries a 1-bit flag (bit 0) and a 7-bit kind (bits 1..7); flag set returns the payload at +4, otherwise the kind. The original extracts the flag with lsl #31/lsrs #31 and reloads the tag byte (ldrb) for the kind; clang tests the bit directly and reuses the already loaded word for the kind, 24 B vs 32 B."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
