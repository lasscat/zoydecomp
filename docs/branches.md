# Branches and working directories

| Branch | Purpose |
| --- | --- |
| decomp/strict | Verified reconstructions and the full-ROM build pipeline |
| wip/semantic | Unfinished reconstructions, behavior checks and comparison results |

Keep the branches in separate working directories. Only the verified worktree runs
full ROM preparation, builds, verification and integration. Research compiles isolated
functions and cannot change the verified ROM or its accepted-code counts.

For a fresh clone in `decomp/strict`, create the research worktree with:

```sh
git worktree add -b wip/semantic ../../wip/semantic origin/wip/semantic
```

If that local branch already exists, inspect `git worktree list` before adding or
moving anything. Keep existing edits and branch work. Never merge the research
branch wholesale into the verified branch.

Use `Reconstruct N additional <module> functions as matching C` only after the full
verification gate passes. Keep progress updates separate. Use explicit unknown-total
wording when percentages cannot be calculated. Research commits describe drafts and
measurements without claiming acceptance.

`strict/8funcs` identifies eight verified functions. Tags describe measured results;
retained original binary data never receives reconstructed-code credit.

The public repository starts with a reviewed source snapshot and separate research
commit. Private development history, local notes and machine-specific setup are not
part of that public history. Subsequent public work uses ordinary commits and pushes.
See [publication instructions](publishing.md).
