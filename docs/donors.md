# Reference source and attribution

The desktop [Plants vs. Zombies reference source](https://github.com/ruslan831/PlantsVsZombies-decompilation)
helps investigate algorithms and behavior. The reviewed revision is
`325b2229a7225d73870bb69322eefcda3a45bf8d`; exact file identities are recorded in
[donor-lock.json](donor-lock.json). The reference README identifies Windows version
1.0.0.1051, while its repository description identifies 0.9.9.1029. That difference
is unresolved. This is public decompiled code, not authenticated original source.

To make a local reference checkout in an ignored directory:

```sh
python3 -B tools/bootstrap_reference.py --destination reference/PlantsVsZombies-decompilation
```

Use it for static source review only. Its AGENTS.md prohibits compiling, building
or linking that repository. Do not import its assets, binaries or SDK material.
No CONTRIBUTING file was found at the reviewed revision; this project does not
submit changes upstream.

The reference has a root MIT notice with placeholder copyright fields. Individual
files can have different terms. MTRand.cpp carries the Matsumoto/Nishimura 1997-2002
notice, retained with the research seed draft in `semantic/NOTICE-MT.txt`. Preserve
all applicable notices. Public access and a repository license do not establish
ownership of every included component; see [NOTICE.md](../NOTICE.md).

## Independently checked DS correspondences

| Reference | DS evidence | Limits |
| --- | --- | --- |
| SexyAppFramework/MTRand.cpp, MTRand::SRand | ARM9 0x02034f40: 624 words, multiplier 1812433253, shift 30, recurrence and loop flow | Algorithm correspondence only. DS rejects zero seed; the reference substitutes 4357. DS offsets and ownership come from its binary. |
| Same file, MTRand::NextNoAssert | ARM9 0x02034fc0: state count 624, offset 397, twist 0x9908b0df, masks 0x9d2c5680/0xefc60000 and shifts 11/7/15/18 | Supports MT19937 identification, not desktop class layout, calling convention or whole-function correctness. |
| Positive-result wrapper | ARM9 0x02034fb0..0x02034fc0 calls a wrapper and clears bit 31 | Supporting call evidence; not separately credited as reconstructed code. |

No Plant, Board or Zombie class mapping is established. Names and similar gameplay
are insufficient. Rendering, input, audio, memory ownership, timing and networking
need DS-specific evidence. The seed draft is independently reconstructed from DS
instructions with attributed algorithm reference; its sampled behavior tests and
instruction comparison remain separate results.
