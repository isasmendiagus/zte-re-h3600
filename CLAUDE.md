# CLAUDE.md — Project conventions for the ZTE H3600 reverse-engineering work

This file tells Claude (and humans) how to organize new code and where to
put things. **Read this before creating new files.**

---

## TL;DR — the migration rule

**When you touch any file, move it to its new home.** Don't bulk-move
preexisting code; migrate opportunistically as you edit. The goal is a
gradual consolidation into the structure below without a disruptive
big-bang refactor.

---

## Target folder structure

```
zxic/
├── CLAUDE.md                          ← this file (conventions)
├── README.md                          ← project entry point
├── ROADMAP.md  STATE.md  LEARNED.md   ← strategy / live state / bug catalog
├── TASKS_TREE.md                      ← T-ID hierarchy (always-current)
│
├── lib/                               ← reusable Python modules (importable)
│   ├── uart.py                          serial + DTR reset + U-Boot drive
│   ├── ssh_shell.py                     paramiko interactive shell wrapper
│   └── uart_transfer.py                 file-over-UART transfer
│
├── tools/                             ← standalone CLI utilities
│   ├── find_csp_crc.py                  compute zlib CRC (the cspstart variety)
│   ├── gen_replay_bins.py               build replay tables for the driver
│   ├── flash_header_only.py             rewrite BootPara header only
│   ├── memdump (+.c)                    cross-compiled ARM mem dumper
│   └── dtr-mod/                         FTDI cable hardware-mod tooling
│
├── tasks/                             ← per-task work folders, dotted-decimal IDs
│   ├── 00.openwrt-port/                 T0           root goal (PLANNED)
│   ├── 00.01.eth-driver/                T0.01        mainline driver (ACTIVE)
│   │   ├── README.md                      starts with ID + Parent + Children + TaskList items
│   │   ├── research/<topic>.md            live investigations (one per open question)
│   │   ├── findings/<topic>.md            promoted from research/ when answered
│   │   ├── scripts/                       task-local scripts
│   │   ├── captures/                      raw register dumps etc.
│   │   └── initramfs/                     staging
│   ├── 00.02.stock-shell/               T0.02        cspd patch + kmsg2uart (DONE)
│   ├── 00.03.nand-flash/                T0.03        doc-only flash bundle
│   ├── 00.05.firmware-load/             T0.05        umbrella w/ decision tree
│   │   └── 00.05.01.rop-no-uart/         T0.05.01    httpd ROP exploit (incl. task-local ghidra/)
│   ├── 00.10.explore/                   T0.10        🔬 umbrella for RE/discovery tasks
│   │   ├── 00.10.01.re-vmlinux/          T0.10.01    knowledge base: stock kernel (Ghidra project here)
│   │   ├── 00.10.02.re-stock-kmods/      T0.10.02    knowledge base: stock .ko collection
│   │   ├── 00.10.03.re-uboot/            T0.10.03    knowledge base: U-Boot
│   │   └── 00.10.04.mainline-archaeology/ T0.10.04   completed archaeology report
│   └── 99.01.linux-stockport/           T9.01   ⛔ parked attempt
│
├── ext/                               ← OUR device's golden source (READ-ONLY)
│   ├── h3600_nand_full.bin              full NAND dump (our unit)
│   ├── extracted/                       uImage, zImage, vmlinux.bin, DTS
│   ├── partitions/                      per-partition splits
│   ├── rootfs/                          decrypted factory JFFS2 view
│   └── kmodules_dump/                   stock .ko files
│
├── refs/                              ← third-party reference (NOT ours)
│   ├── orca-h3600p/                     orca.pet RE on his unit (different physical device)
│   └── stefan-zx297520/                 Stefan's sibling-SoC port
│
├── docs/                              ← consolidated reference docs
│   ├── ARCHITECTURE.md                  HW truth (PL011, NAND, AES, CRC)
│   ├── KERNELS.md                       all kernel trees + build commands
│   ├── ITERATE.md                       the 3 dev loops
│   ├── CROSS_COMPILE_GUIDE.md           soft-float toolchain
│   ├── EXTERNAL_RESEARCH.md             external sources we built on
│   └── CHRONICLE.md                     historical log (Spanish, archival)
│
├── linux-v6.6/                        ← mainline kernel source (used by T0.01)
├── build/                             ← kernel build artifacts
├── tftp/                              ← TFTP serve dir
└── ghidra/                            ← Ghidra projects
```

---

## Naming conventions

| Kind | Convention | Example |
|---|---|---|
| Python module | `snake_case.py`, importable | `lib/uart.py` |
| Python CLI tool | `verb_noun.py` | `tools/find_csp_crc.py` |
| Shell script | `verb_noun.sh` | `tasks/00.02.stock-shell/prepare_slot_a.sh` |
| C tool | `noun.c`, cross-compile static for ARM | `tools/memdump.c` |
| Doc | `UPPER_CASE.md` top-level, `lowercase.md` task-specific | `docs/KERNELS.md`, `tasks/00.01.eth-driver/README.md` |
| Generated artifact | in `out/` / `build/` / `staging/` (gitignored) | `tasks/00.02.stock-shell/out/rootfs_enc.jffs2` |
| Task folder | `XX(.YY)*.<slug>/` (dotted-decimal ID + kebab slug) | `tasks/00.01.01.rx-path/` |

### Task folder naming — the dotted-decimal rule

Folder format: `{NN}(.{NN})*.{slug}/`

```
tasks/00.openwrt-port/                   T-ID 00         root goal
tasks/00.01.eth-driver/                  T-ID 00.01      child of 00
tasks/00.01.01.rx-path/                  T-ID 00.01.01   child of 00.01
tasks/00.01.01.01.chip-tm-init/          T-ID 00.01.01.01 child of 00.01.01
tasks/99.parked/                         T-ID 99         parked-work root
tasks/99.01.linux-stockport/             T-ID 99.01      child of 99
```

- **Parent rule**: strip the trailing `.slug`, then strip the trailing `.NN`.
  Find the folder whose name starts with what's left.
- **Grep all descendants**: `ls tasks/00.01.*` shows eth-driver + everything under it.
- **Number with gaps** (01, 05, 10, 15…) so insertions don't cascade renames.
- **When to spawn a new folder vs add a research file**:
  - **New folder** if the subtask has its own scripts, captures, or build artifacts.
  - **`research/<topic>.md` in the parent** if it's just notes / hypotheses / open questions.
- **Depth**: unlimited in theory, ~3-5 in practice. Deeper than 5 = use `research/` instead.

Each task folder's README starts with:

```markdown
# rx-path
**ID**: 00.01.01
**Parent**: [00.01 eth-driver](../00.01.eth-driver/)
**Children**: 00.01.01.01.chip-tm-init
**TaskList items**: #87, #91, #92, #93
**Status**: blocked on 00.01.03 (printk-injection tool)
```

`TASKS_TREE.md` at zxic root holds the canonical tree view — update it
when you add/rename/re-parent a task folder.

---

## Script promotion — when to move from `tasks/X/scripts/` to `tools/` or `lib/`

The "rule of two": don't pre-extract. Wait for the second user.

| Where the script lives | When |
|---|---|
| `tasks/XX.YY.foo/scripts/` | **1st use only.** Sequences task-specific steps. Hardcodes that task's paths/names/timings. |
| `tools/` | **2nd user has materialized AND uses it unchanged.** Generic CLI utility, clean argv interface. |
| `lib/` | **`import`ed from multiple places.** Stable function/class API, no task-specific magic. |

### Promotion checklist (apply when ≥2 tasks need the same logic)

✅ Ready to promote when:
- No paths hardcoded to a specific task folder
- Magic constants are arguments or config (not literals in the body)
- Function signature would need ≤4 params to be generic
- It solves a *domain* problem (compute CRC, drive U-Boot, dump mem)
- You'd describe it as "a thing" not "a step"

❌ Keep it task-local when:
- It hardcodes "load X, then Y, then write to NAND offset Z" — that's a workflow, not a tool
- It has 8+ task-specific magic numbers
- Only the original task is actually using it
- Doing it generically would need a config file longer than the script

### `lib/` vs `tools/` (when both apply)

If a script has both an API AND a CLI: put the logic in `lib/`, the CLI in `tools/` as a thin argparse wrapper that imports from `lib/`. **Don't duplicate.**

```
lib/csp_crc.py          ← the function
tools/find_csp_crc.py   ← thin CLI: argparse + call into lib/csp_crc
```

### Demotion (rare but real)

Move from `tools/` back to `tasks/X/scripts/` when:
- Nobody else ended up using it
- It diverged to handle one task's quirks and isn't generic anymore
- The "second user" was a one-time experiment that didn't stick

### Current promotion candidates (in the codebase as of 2026-05-23)

- `tasks/00.01.eth-driver/scripts/flash_mainline.py` + `tasks/00.02.stock-shell/flash_slot_a.py` both drive U-Boot via UART for TFTP-then-nand-write. **Two real users.** → ready for `lib/uboot_flash.py` extraction (this is the "unify the flash scripts" TODO already noted in `tasks/00.03.nand-flash/README.md`).

---

## Ghidra project ownership — same "rule of two" as scripts

A Ghidra project (a `.gpr` + `.rep/` pair, where `.rep/` holds the
analyzed data and may contain many imported binaries) is treated like
any other artifact: stays task-local until a second task imports the
same binary.

| Where the project lives | When |
|---|---|
| `tasks/XX.YY.foo/ghidra/<name>.{gpr,rep}` | **1st consumer.** Task-local; consumer can rename/destruct freely. |
| `tasks/00.10.NN.re-<binary>/ghidra/<name>.{gpr,rep}` | **≥2 consumers.** Promote to its own knowledge-base task under the `00.10.explore` umbrella. Multiple consumers reference the project; findings get promoted to `findings/`. |

### Rules of engagement for shared (promoted) projects

The `00.10.NN.re-*` projects are SHARED. Annotations affect every consumer.

| OK ✅ | Avoid ❌ |
|---|---|
| Comments, labels, bookmarks | Mass renames of existing functions |
| New struct definitions | Restructuring existing struct definitions |
| Function signatures verified by RE | Speculative renames |
| New data types | Deleting existing types |

**If you need destructive experiments**: copy the `.rep/` into your
consumer task's local `ghidra/` and experiment there. Don't pollute the
shared project.

### Findings flow (text > Ghidra state for durability)

Ghidra annotations are the live working state. **Stable findings get
promoted to markdown** in the RE task's `findings/<topic>.md` so
they're grep-able, diff-able, and survive Ghidra-version migrations.

```
1. Discover something while iterating in your consumer task
2. Write a hypothesis in 00.XX.consumer/research/<topic>.md
3. Verify it
4. Promote to 00.10.NN.re-<binary>/findings/<topic>.md
5. Cross-link from your consumer task's README
```

Template for findings docs: see `tasks/00.10.explore/README.md`
"Findings doc template".

### Tooling vs projects

`zxic/ghidra/` is now **shared tooling** (`dump_*.py`, headless scripts)
that operates on the per-task projects. See `zxic/ghidra/README.md`.

---

## When touching a file

1. **If it's already in the right place** → just edit, move on.
2. **If it has stale paths** (`H3600/`, `mainline_eth/`, `stock_traced/` from
   the pre-rename era) → fix them as you touch the file. Don't sweep across
   the whole repo; fix what you're already in.
3. **If you're creating a new file** → put it in the target structure
   directly. Use the dotted-decimal task-folder rule for any new task.
4. **If you're tempted to put a script in `tools/` or `lib/`** → check the
   promotion criteria above. Default to `tasks/X/scripts/` for the first user.

---

## Common conventions

### Python style
- Top of every script: a docstring that explains WHY this exists, not just WHAT
- `from pathlib import Path` over `os.path`
- Type hints on public functions
- `argparse` for CLI tools (`-h` / `--help` should always work)
- No bare `except:` — at minimum `except Exception:` with logged context
- Imports grouped: stdlib, third-party (paramiko, pyserial), local

### Shell style
- `set -euo pipefail` at top
- Quote ALL variables: `"$VAR"` not `$VAR`
- Use absolute paths derived from `$(cd "$(dirname "$0")" && pwd)` not `$PWD`
- Don't `sudo` inside the script unless absolutely needed; document if so

### Generated artifacts
- `out/`, `build/`, `staging/`, `dist/` are .gitignore'd (or should be)
- Reproducible from sources via documented script: never check in opaque
  binary outputs except into `ext/` (and only golden-source backups there)

### Device interaction
- Always use `lib/uart.py` for serial — DO NOT reimplement DTR reset or U-Boot prompt detection
- Always use `lib/ssh_shell.py` for SSH — stock SSHd rejects sftp/exec subsystems
- TFTP server runs on host at `192.168.1.50:69`, serving `zxic/tftp/`
- Device IP: `192.168.1.1`. SSH creds: `admin / UkuGPeyRDU`. U-Boot pw: `Boot4128s!`
- See `tools/dtr-mod/README.md` for the FTDI cable's DTR→relay hardware mod

### Encryption keys (HARD-CODED for this device, per-unit)
- AES-128-ECB rootfs key: `H36000e71071c440` (ASCII, 16 bytes)
- config.bin AES-256-CBC: see `docs/CONFIG_EDIT.md` (uses buggy_sha256)
- See `aes_key_discovered.md` memory entry for derivation algorithm

### Safety rules for NAND writes
- **NEVER** touch mtd1 bootloader region (0x0 - 0xc0000) — brick risk
- Slot B (kernel: 0x2700000, rootfs: 0x2a60000, header: 0x4080000) should stay intact as fallback
- Always `nand erase` before `nand write` to the same region
- Full NAND backup at `ext/h3600_nand_full.bin` — restore any partition from here

### Hardware facts
- SoC: ZTE ZXIC ZX279128S (ARM Cortex-A9 dual-core, 1 GHz)
- 256 MiB RAM @ 0x40000000
- 128 MiB SPI NAND (ESMT F50L1G41LB) — 2 KiB page, 128 KiB erase block, 64 B OOB
- Kernel boot args from cspstart: `console=ttyAMA0 root=/dev/mtdblock8 ro rootfstype=jffs2 mem=256M`

---

## When in doubt

- Read this file's structure
- Check `docs/` for prior RE work
- Check Claude's auto-memory for hardware/firmware facts
- For boot/NAND specifics: `docs/NAND_LAYOUT_AND_BOOT.md`
- For credentials and stock UART/cspd: `docs/STOCK_DEBUG_INFRASTRUCTURE.md`
- For ABI cascade & stockport history: `docs/STOCKPORT_PLAN.md`

---

## Migration history

- **2026-05-22**: full project rename `H3600/` → `zxic/`. New top-level docs
  added (README, LEARNED, ROADMAP, STATE). Old paths like `mainline_eth/`,
  `stock_traced/`, `H3600/` may still appear in archived/parked docs — fix
  in-place if you touch them.
- **2026-05-22**: NAND-flash bundle consolidated into `tasks/00.03.nand-flash/`
  (now the single source of truth for NAND layout + CRC rules + flash scripts).
- **2026-05-23**: Spanish kernel-archaeology + DTR-mod tooling + orca refs
  pulled in from ZTE/ sibling dirs before they were compressed.
- **2026-05-23**: task folders renamed to dotted-decimal scheme (see "Task
  folder naming" above). Old kebab-slug names (`eth-driver/`, `stock-shell/`,
  `nand-flash/`, `openwrt-port/`) → `00.0N.<slug>/`.

**Open chores** (do opportunistically when touching adjacent files):
- TFTP daemon needs restart whenever the serve-dir path changes:
  `sudo pkill -f 'in.tftpd' && sudo in.tftpd -L --secure --create -a 192.168.1.50:69 /home/ubuntu/Projects/MYSELF/ZTE/zxic/tftp`
- Translate `docs/CHRONICLE.md` from Spanish chunk by chunk
- Several `docs/*.md` (SLOT_A_CSPD_PATCH_PLAYBOOK, NAND_PERSISTENCE_PLAN,
  STOCKPORT_PLAN, PCIE_DRIVER_DESIGN, WEB_RE) still have `mainline_eth/`
  or `H3600/` paths — fix when touched.
