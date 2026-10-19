# Preparing a public release

The public repository must contain source, documentation and reproducible technical
evidence only. ROMs, game assets, extracted/build output, proprietary tools,
credentials, private notes and machine-specific setup stay outside Git.

Before publishing, run the read-only audit:

```sh
python3 -B tools/publication_audit.py
```

It checks both branches and reachable history for prohibited paths, binary content
and recognizable credential patterns. Current files must not contain personal home
paths. The report never prints matched credential values. This is a bounded check,
not a guarantee that every private detail or secret can be recognized.

For the initial public release, use a fresh repository created from the cleaned
files. Keep the earlier repository private as a separate archive. Deleting files
or force-pushing new branches into a repository does not reliably make its earlier
objects inaccessible. Do not change the archive's visibility to public.

The release-preparation tool copies only tracked text files, creates new verified
and research history, and leaves the original repository and local inputs intact.
It refuses an existing destination. The research commit descends from the new
verified snapshot. Audit and reproduce the prepared copy before uploading it.

After the initial release, develop in a fresh public clone and use ordinary commits
and pushes. Do not rebuild public history for routine updates. Review both branches,
run the relevant tests and the complete-ROM gate for strict changes, and stage
explicit paths. Publish only with maintainer authorization. Never upload compiler
files, generated ROMs or private archive data.
