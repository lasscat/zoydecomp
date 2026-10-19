# arm9:020526ac:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/leaves/020526ac.c
SHA256: 147253dddf77bbb1d60210ea0efe52a16913bf5a424d6da866176ef9aaf6d6b5
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 28; mode: arm
Metrics: {"candidate_size": 28, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": 0, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 0, "target_size": 28, "tier": "S"}
Donor: {"adaptation": "Independent DS binary reconstruction; no donor adaptation or gameplay name asserted."}
Blocker: Local comparison only; owner, field meanings and behavior not validated; strict integration gate pending
Failed hypotheses: ["3 isolated hypotheses; best tier S. Zero-initializes a fixed record: u32 at 0x00/0x04/0x0c/0x10 and byte at 0x08, stores in ascending address order. Byte-exact (S) with volatile-forced ordering; clang otherwise reorders to 0x0c,0x10,0x08,0x00,0x04 (N, 4 instruction diffs). Caller 0x020526c8 zeroes a 0xa0-byte 0x14-stride array with this helper. No twin body in the current universe."]
Next hypothesis: Select for the strict full-ROM gate and add differential behavior/ownership checks.
Behavior evidence (separate): {"status": "not tested; isolated unmasked comparison only, no behavior evidence"}
