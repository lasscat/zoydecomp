# arm9:02034fc0:arm

Research only; no semantic proof or B acceptance.

Source: semantic/src/mt_next.c
SHA256: 9af075f7def36e404be866e8a3e7c966f172669b85581430737949580cda63fb
Profile: semantic/profiles/clang23-arm946-o2.json
Profile SHA256: 2fe818c453f15e7996dacf75d77d2f4dcd580d761f875f1507f301db7b5095fc
Target size: 296; mode: arm
Metrics: {"candidate_size": 276, "comparator": "unmasked-capstone5-instruction-boundaries-v1", "instruction_differences": null, "masked_fields": [], "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "registers_normalized": false, "resolved_byte_differences": 274, "target_size": 296, "tier": "X"}
Donor: {"adaptation": "independent DS binary reconstruction with attributed MT algorithm reference; DS keeps the raw 32-bit value while the reference masks to 31 bits in NextNoAssert; DS stores an explicit next-word address", "commit": "325b2229a7225d73870bb69322eefcda3a45bf8d", "function": "MTRand::NextNoAssert()", "license": "MIT root plus file-specific Matsumoto/Nishimura notice; see semantic/NOTICE-MT.txt", "path": "SexyAppFramework/MTRand.cpp", "repository": "ruslan831/PlantsVsZombies-decompilation"}
Blocker: Modern clang output is 276 bytes versus the 296-byte target; the refill/temper structure does not match the DS scheduling. Readable connected draft; no B acceptance.
Failed hypotheses: ["Natural two-loop twist with an explicit 32-bit next-word address compiled to 276 bytes versus the 296-byte target; instruction scheduling differs, so the draft is X, not S/N."]
Next hypothesis: Map which of the eleven per-object seed owners first calls the reload path and whether any caller depends on the raw (unmasked) 32-bit value; keep the connected behavior transitions instead of chasing code shape.
Behavior evidence (separate): {"report": "semantic/behavior/mt_next.json", "report_sha256": "e5414e13ab112e8e96fab5a74e1943fe43704e74ebbf0afafed8976c2679c639", "semantic_equivalence_proven": false, "status": "655 sampled calls across 6 seed/next/reseed scenarios including two twist reloads; not an equivalence proof"}
