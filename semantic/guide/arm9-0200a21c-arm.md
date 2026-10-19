# arm9:0200a21c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200a21c.c
SHA256: 5cbc61bfeb9ab26cc39362a2068f393689ceadb8edf8752f64890850520e0fd7
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 20, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 22, "target_size": 28, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. Reads word at self+0x1c; if bit 24 set returns low-24 bits (v<<8>>8), else returns word at self+8. Target emits lsr r2,r1,#24 / tst r2,#1 / lsl+lsr mask; clang -O2 always folds these to 'tst r1,#0x1000000' + 'bic r0,r1,#0xff000000' (5 insns/20B). Tried raw bit-test, 24-bit bitfield struct, byte-tag temp, pointer-typed mask; all fold identically. Semantic match only; not S/N."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
