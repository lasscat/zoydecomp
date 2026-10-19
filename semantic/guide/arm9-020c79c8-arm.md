# arm9:020c79c8:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020c79c8.c
SHA256: 2044e2855a121732096bc04b33feb0ead0cbf1b2ccbdd5b1be76134e0baafc48
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 140; mode: arm
Metrics: {"candidate_size": 88, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 126, "target_size": 140, "tier": "X"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["9 isolated hypotheses; best tier X. One-shot init: if state bit0 is set and bits 5 and 2 are clear/ set, it fills a 2-entry pointer table at 0x021DE25C from 0x021DE340+i*0x30+0x10 (or zero) keyed on a byte at 0x021DE300+0xD0+i, then sets state bit5. Non-S: this profile derives the 0x021DE2xx/0x021DE3xx constants from the 0x021DE250 pool word via `add` chains and uses r3 for the frame instead of r4, so 148 bytes vs 140; the original "]
Next hypothesis: Map DS callers/ownership, then add behavior checks or a new binary-backed shape hypothesis.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
