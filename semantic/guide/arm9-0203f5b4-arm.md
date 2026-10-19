# arm9:0203f5b4:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0203f5b4.c
SHA256: 5ad6d365b3eb420d98d9f8a3b063516694e128a9507c768f4cf69aef317420ee
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 20; mode: arm
Metrics: {"candidate_size": 12, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 18, "target_size": 20, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["2 isolated hypotheses; best tier X. Stores the last argument at +0 and the second at +4. The target brackets the two stores with push {r2,r3} / pop {r2,r3}; that pair is a fingerprint of the original toolchain (6 occurrences in ARM9, e.g. 0x02044bf8 and 0x0211370c, also in two-argument functions) and no natural C form makes clang emit it, so the candidate is 12 bytes vs 20. The argument pattern matches a (pointer, int, long long) si"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
