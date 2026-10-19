# arm9:0200f2f8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200f2f8.c
SHA256: 36a8b1084f0d89d85733ed8c80ee47f9326ec853bdf2bc4705c22c92e17b2088
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 128; mode: arm
Metrics: {"candidate_size": 88, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 118, "target_size": 128, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier X. AUXSPI write: spins on the busy bit, sets the 32-bit transfer bits in the control register and stores two big-endian command words."]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
