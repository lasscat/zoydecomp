# arm9:0200e04c:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/0200e04c.c
SHA256: fa0418fae9aba5f35018c30d80c9020d97215773265dc5b8b2fb08b4cd623e82
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 148; mode: arm
Metrics: {"candidate_size": 156, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 135, "target_size": 148, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["7 isolated hypotheses; best tier X. Validates a 4-word date record (year<100, month 1..12, day 1..31, weekday<7, month re-checked) then returns year*365 + table[month] + day-1 (+1 if month>=3 and year%4==0) + (year+3)/4, else -1. X: byte size matches exactly (148) and the control flow matches, but the reviewed MWCC allocates year/month/day to r12/r3/r2 where the original used r3/r2/r1, so 23 instructions differ in register fields on"]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
