# ghidra/ — shared Ghidra tooling (the projects moved to tasks/)

**Important**: as of the 2026-05-23 explore-umbrella reorg, the Ghidra
**projects** no longer live here. They moved into the RE tasks that own
them:

| Was | Is now |
|---|---|
| `ghidra/project/h3600_vmlinux.{gpr,rep}` | `tasks/00.10.01.re-vmlinux/ghidra/h3600_vmlinux.{gpr,rep}` |
| `ghidra/project_ko/h3600_kmods.{gpr,rep}` | `tasks/00.10.02.re-stock-kmods/ghidra/h3600_kmods.{gpr,rep}` |
| `ghidra/project_uboot/h3600_uboot.{gpr,rep}` | `tasks/00.10.03.re-uboot/ghidra/h3600_uboot.{gpr,rep}` |

(Plus task-local: `tasks/00.05.01.rop-no-uart/ghidra/GHydra_ROP.{gpr,rep}`)

## What stayed here

Shared **tooling that operates on those projects**:

| File / dir | Purpose |
|---|---|
| `dump_*.py` | Ghidra headless scripts to extract specific data (function lists, decompiled bodies, register access patterns, etc.) |
| `force_func_decompile.py` | Force-decompile a specific function (useful when Ghidra's auto-analyze missed it) |
| `run_decompile_ko.sh` | Batch-decompile all functions in the kmods project to text logs |
| `output*/` | Cached outputs from prior dump runs (regenerable; can be wiped) |
| `*.log` | Logs from past Ghidra headless runs |

These scripts work against any Ghidra project — invoke them with the
project path as an argument (or run them inside Ghidra's Script Manager
after opening the project).

## Invoking a dump script against a per-task project

Ghidra headless example:
```sh
/path/to/ghidra/support/analyzeHeadless \
    /home/ubuntu/Projects/MYSELF/ZTE/zxic/tasks/00.10.01.re-vmlinux/ghidra \
    h3600_vmlinux \
    -process h3600_vmlinux.bin \
    -postScript /home/ubuntu/Projects/MYSELF/ZTE/zxic/ghidra/dump_one_func.py chip_tm_init
```

(Adjust `analyzeHeadless` path to wherever your Ghidra install lives.)

`run_decompile_ko.sh` is currently hardcoded to point at
`tasks/00.10.02.re-stock-kmods/ghidra` — update if you move the project.

## Why scripts stayed shared (vs moving each per-project)

These scripts are **operations**, not project content. Same script can
be pointed at any project (vmlinux, kmods, uboot, httpd, future RE
work). Keeping them shared avoids duplication.

If a script ever becomes specific to a single project (e.g. a heuristic
only meaningful for stock kmod structure), promote it INTO that task's
folder — same rule as `tools/` vs `tasks/X/scripts/` (see CLAUDE.md
"Script promotion criteria").

## See also

- `tasks/00.10.explore/README.md` — umbrella for all RE tasks, rules of engagement
- `CLAUDE.md` "Ghidra project ownership" — when to keep task-local vs promote
