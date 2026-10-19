# arm9:020b93b0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020b93b0.c
SHA256: bf10987353578fd0e9debb3cfffe5f573bed6ed8a91c067ca1d46a93d437e21e
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 56; mode: arm
Metrics: {"candidate_size": 48, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 49, "target_size": 56, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Sets or clears a sub-object flag and stores/omits a handle depending on whether the handle is -1; non-S: original predicates both arms and reloads self+0xb8/self+0xc0 after the store, clang merges the common load and selects the operation."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
