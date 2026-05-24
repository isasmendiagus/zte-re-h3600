# Plan — debug the eth driver init path via stock-.ko printk injection

**Owner**: —
**Created**: 2026-05-23
**Status**: ✅ Phase 2 DONE — init sequence captured via `kotrace.ko`. Phase 3 (drill into `chip_tm_init`) next.
**Goal**: understand exactly what stock `switch.ko` does during init, port the
missing bits to mainline, get RX path alive (= unblock TaskList #87, #91, #92,
#93 in one shot).
**TaskList items**: [#16](phase-0--confirm-debug-bridge-is-alive) through
[#20](phase-4--port-and-verify), one per phase.

## Progress tracker

Update this table AND the per-phase `**Status**` lines below as each phase
moves through `📋 PLANNED → 🚧 IN PROGRESS → ✅ DONE`. Also reflect each
status change in the corresponding TaskList item via TaskUpdate.

| Phase | TaskList | Status | Notes |
|---|---|---|---|
| 0 — confirm debug bridge | #16 | ✅ DONE | 2026-05-23: re-flashed cspd-patched rootfs via `flash.py rootfs`, device booted, kmsg2uart (PID 464) + cspd (PID 550) running, kernel `printk` lines reach UART. |
| 1 — build splicer (on-disk attempt) | #17 | ⚠️ SUPERSEDED | 2026-05-23: on-disk LIEF/ELF splicing fundamentally doesn't work for this kernel. Three distinct bugs found and documented in [findings/ko_splice_bugs.md](findings/ko_splice_bugs.md); fix to LIEF #661 done at [tasks/00.01.01.fix-lief-rel-sections/](../00.01.01.fix-lief-rel-sections/); a `scripts/ko_loader_sim.py` userspace simulator was built but couldn't catch the final blocker. Approach abandoned in favor of Phase 2's Idea A. |
| 2 — switch.ko init trace (via `kotrace.ko`) | #18 | ✅ DONE | 2026-05-23: Idea A (loader-notifier + RAM patching) implemented in [kotrace/](kotrace/), full writeup in [findings/idea_a_kotrace.md](findings/idea_a_kotrace.md). Captured init sequence: `sw_init_switch → sw_init_wlan_ssid → ethdrv_port_dev_init×5 (one per UNI port) → chip_tm_init → sw_alarm_init`. |
| 3 — drill chip_tm_init | #19 | 📋 PLANNED | Extend `kotrace.c`'s `targets[]` with the internal callees of `chip_tm_init` (find them in Ghidra against [tasks/00.10.02.re-stock-kmods/](../00.10.02.re-stock-kmods/)), capture nested call order + register writes. |
| 4 — port + verify | #20 | 📋 PLANNED | Translate captured chip_tm_init sequence into `linux-v6.6/zx279128-eth`, RAM-boot test, confirm RX comes alive. |
| 5 — next stock .ko | (open when needed) | 📋 PLANNED | Generalize kotrace.c to take a `target_module=` param + per-module `targets[]` so the same .ko works for `tm.ko`, `mt7915.ko`, etc. |

**Process commitment**: at the start of each phase, set its row to
`🚧 IN PROGRESS` and call `TaskUpdate(taskId=N, status="in_progress")`. On
completion, set to `✅ DONE` (with a one-line "what we learned" in the Notes
column) and call `TaskUpdate(taskId=N, status="completed")`. If blocked, set
to `⛔ BLOCKED` and add a short blocker description in Notes.

## Why this plan exists

Mainline `zx279128-eth` driver: RX dead, TM IRQ never fires, no packets reach
the CPU. See [`research/rx_path_dead.md`](research/rx_path_dead.md) for the
full diagnosis.

**Strongest hypothesis** (also from `rx_path_dead.md`): stock `switch.ko`
calls a function `chip_tm_init` during module load that touches multiple TM
registers our mainline driver never writes. We've brute-replayed static
register dumps and it's not enough — what's missing is the *runtime
init sequence* (specific writes, specific order, specific dependencies on
read-back values).

To get that sequence, we need to **observe what stock does** at runtime
without source code. The methodology is documented in
[`research/printk_injection_methodology.md`](research/printk_injection_methodology.md):
binary-patch `printk` calls into the stock `.ko`, load it on the
cspd-patched stock kernel (which has UART output via `kmsg2uart`), trigger
the init path, read the log, port the missing logic.

This plan is the concrete execution of that methodology.

## What's already in place (the prereqs are done)

- ✅ cspd-patched stock rootfs gives us persistent SSH + UART
  (`tasks/00.02.stock-shell/`)
- ✅ `kmsg2uart` daemon bridges kernel `printk` → UART
  (`tasks/00.02.stock-shell/kmsg2uart.c`)
- ✅ Flash tool can swap rootfs / .kos in one command
  (`tasks/00.04.flash-tool/flash.py`)
- ✅ Stock `.ko` files easily accessible at `ext/kmodules_dump/`
  (symlink → `ext/rootfs/kmodule/`, 31 modules)
- ✅ Ghidra project for stock `.ko` RE
  (`tasks/00.10.02.re-stock-kmods/ghidra/`)
- ✅ Mainline kernel source + driver in tree (`linux-v6.6/`)
- ✅ Stock kernel + register dumps already captured
  (`tasks/00.01.eth-driver/captures/stock_dumps/`)
- ✅ Prior-art ARM ELF splicing pattern to lift from
  (`tasks/99.01.linux-stockport/auto_patch_plat.py`)

The **only** missing piece is the splicer tool itself. Build it once, use it
for every stock `.ko` we ever want to trace.

## Iter modes used by this plan

Two device-side workflows, picked per phase:

| Mode | What | Cost/iter | Used in |
|---|---|---|---|
| **SCP + rmmod/insmod** | Push a patched `.ko` to `/tmp/`, hot-swap on the running stock kernel | ~30 s | Phases 2–3 (rapid trace iteration) |
| **Flash rootfs** | Bake the patched `.ko` into a rootfs, `flash.py rootfs --src ...`, reboot | ~5 min | Phase 0 (initial bridge setup); when you need post-reboot persistence |
| **RAM-only `bootm`** | TFTP new mainline kernel into RAM, `bootm` — no NAND touched | ~3 min | Phase 4 (testing the mainline-side port) |

## Phase 0 — confirm debug bridge is alive

**Status**: ✅ DONE (2026-05-23) **·** **TaskList #16** **·** Cost: ~10 min one-time sanity.

Before any debugging work, verify the stock-with-UART bridge is currently
loaded on the device.

1. SSH in: `ssh admin@192.168.1.1` (password: `UkuGPeyRDU`)
2. Confirm `kmsg2uart` is running: `ps | grep kmsg2uart`
3. Write a test message: `echo "[TEST] hello from $(date)" > /dev/kmsg`
4. Check UART (in another terminal, via `python3 lib/uart.py log`) — message
   should appear within a second

If kmsg2uart isn't running OR slot A doesn't have the cspd-patched rootfs:
re-flash via
`./tasks/00.02.stock-shell/prepare_slot_a.sh && python3 tasks/00.04.flash-tool/flash.py rootfs --src tftp/rootfs_a_patched_enc.jffs2`.

**Success condition**: arbitrary kernel-side `printk` reaches the UART
terminal. Now we have the observation channel for everything that follows.

## Phase 1 — build the splicer (Tier 1 only)

**Status**: ⚠️ SUPERSEDED **·** **TaskList #17** **·** Three sub-attempts: (a) LIEF on-disk splice — blocked by LIEF issue #661 (silent section drop on REL files); (b) patched LIEF — still blocked by stale-relocation, sh_info, and one unidentified structural bug, see [findings/ko_splice_bugs.md](findings/ko_splice_bugs.md); (c) **finally pivoted to a runtime tracer kernel module ([kotrace/](kotrace/), Phase 2)** which sidesteps all three failure classes by writing pre-resolved bytes into module RAM after the kernel's own loader runs.

The Phase 1 design history below is preserved for context only — the
working implementation is in Phase 2 / [findings/idea_a_kotrace.md](findings/idea_a_kotrace.md).

### Phase 1 pivot — runtime tracer module instead of binary splicer

**Why pivoted (discovered 2026-05-23):**

The binary-patching approach (splice printk into stock `.ko` files via ELF
surgery) hits a fundamental tooling wall:

- **LIEF 0.17.6** is the right shape of tool, but **crashes when adding any
  section to a Linux kernel `.ko`** (`IndexError: unordered_map::at` deep in
  LIEF's C++ relocation-tracking). Reproduced on `switch.ko` AND our own
  `zx279128-eth.ko`, with and without `.ARM.exidx` stripped. Not a config
  issue we can work around — it's a LIEF bug in kernel-module support.
- **pyelftools alone** is a parser, not a modifier. Doing the section-table
  surgery manually is ~600 LoC of error-prone ELF wrestling.
- **Other tools** (Ghidra's exporter, patchelf, e9patch) are wrong scope.

The splicer code at `scripts/ko_printk_splice.py` is preserved — its
candidate-detection + ARM thunk codegen are reusable. Only the LIEF-based
emission path is dead.

**New approach: runtime tracer kernel module (`tracer.ko`)**

Write a small kernel module **with our own source**. At insmod time it:

1. Calls `kallsyms_lookup_name("chip_tm_init")` to find the live address of
   the stock function (stock kernel has `CONFIG_KALLSYMS=y` per
   `docs/STOCK_DEBUG_INFRASTRUCTURE.md`).
2. Saves the function's original first instruction.
3. Overwrites it with `b tracer_thunk` (or a longer movw/movt/bx sequence if
   the displaced instruction is PC-relative — easier to handle in C than in
   ELF surgery).
4. Calls `flush_icache_range()` to flush the I-cache so the patch takes
   effect immediately.
5. The thunk (compiled C function with naked attribute, or inline asm):
   - saves registers,
   - calls `printk("[STOCK %s] called\n", "chip_tm_init")`,
   - restores registers,
   - executes the saved original instruction,
   - branches to the function+4.

Tradeoffs vs. binary patching:

| Concern | Binary splicer | Runtime tracer module |
|---|---|---|
| Source we control | no (patching stock .ko) | **yes** |
| Iter loop | regenerate + scp + insmod | edit C + rebuild + scp + insmod |
| Surgery complexity | ELF section/symbol/reloc | C + small inline asm + cache flush |
| Multiple functions instrumented | one-shot at splice time | dynamic — `insmod tracer.ko targets=chip_tm_init,sw_init_switch` |
| Removability | rebuild stock .ko | `rmmod tracer` restores |
| Tooling risk | LIEF bug (proven) + pyelftools complexity | standard kernel C, kallsyms is well-known |
| LoC estimate | ~600 LoC (with ELF surgery) or ~200 LoC (if LIEF worked) | ~200 LoC C + Makefile |

**Plan for the next focused session:**

1. Write `tasks/00.01.eth-driver/tracer/tracer.c` (kernel module source).
2. Write its Makefile (build against our mainline kernel headers? or
   against stock kernel build artifacts in `linux-stockport/linux-4.1.25/`?
   — needs deciding; stock is more honest since we run on stock kernel).
3. Build it cross-compiled for ARM, target stock kernel 4.1.25.
4. Add a CLI parameter: `insmod tracer.ko targets=chip_tm_init,sw_init_switch`.
5. SCP + insmod on the cspd-patched device (Phase 0's bridge is already alive).
6. Verify "[STOCK chip_tm_init] called" appears on UART when `switch.ko` is
   reloaded with `rmmod switch ; insmod switch.ko`.

Then Phases 2-4 proceed unchanged — just substituting "splice the .ko →
insmod patched .ko" with "insmod tracer.ko targets=... → reload switch.ko".

Deliverable: `tasks/00.01.eth-driver/scripts/ko_printk_splice.py`.

### Sub-steps

1. **Read** `tasks/99.01.linux-stockport/auto_patch_plat.py` end-to-end. It
   already solves ARM relocation-aware ELF splicing — we recycle the pattern.
2. **Design** the splicer's interface:
   ```
   ko_printk_splice.py --src ext/kmodules_dump/switch.ko \
                       --out tasks/00.01.eth-driver/out/spliced/switch.scope-init.ko \
                       --scope init        # Tier 1 default
   ```
   For Tier 1, `--scope init` means "every `STT_FUNC` symbol in `.init.text`".
   Later add `--scope <regex>` (Tier 2) and `--scope all --max-calls N`
   (Tier 3); v1 doesn't need them.
3. **Implement**:
   - Parse ELF via `pyelftools`
   - Locate `.init.text` section + walk `STT_FUNC` symbols inside it
   - For each function entry: append an ARM thunk to the `.text` section
     that does `stmfd sp!, {r0-r12, lr} ; ldr r0, =fmt ; bl printk ; ldmfd sp!, {r0-r12, lr} ; b <orig_entry>`
   - Patch the original entry with `b <thunk>`
   - Add `.rodata` entries for each format string (`"[STOCK] <func_name>\n"`)
   - Add relocation entries: one R_ARM_CALL for `printk`, one R_ARM_JUMP24 for
     the back-branch
4. **Smoke-test** on a `.ko` we own: take
   `build/drivers/net/ethernet/zte/zx279128-eth.ko`, splice
   `printk("[SPLICE-TEST] zx_eth_open\n")` at `zx_eth_open`'s entry, build a
   mainline kernel that loads it, run, confirm the printk reaches UART.
5. **Output layout** the tool establishes:
   ```
   tasks/00.01.eth-driver/
   ├── out/                  ← gitignored
   │   ├── .gitignore        ← `*`
   │   └── spliced/          ← patched .kos land here
   │       └── switch.scope-init.ko
   └── scripts/
       └── ko_printk_splice.py
   ```

**Success condition**: smoke test on our own `.ko` produces a UART log line
matching the format we encoded. Tier 1 is complete; we never need to
re-implement.

### Risks for Phase 1

- ARM relocation encoding is subtle — copy from `auto_patch_plat.py`, don't
  reinvent. If the relocation is wrong, the module loader fails or the
  `printk` call lands at the wrong address (silent miss).
- `printk` symbol must be in the module's symbol table relocations — verify
  with `readelf -r` on the original `.ko`. If not present, we need to add a
  new GOT-style entry, which is more work.

## Phase 2 — first real trace: switch.ko init

**Status**: 📋 PLANNED **·** **TaskList #18** **·** Cost: ~30 min (assumes splicer works from Phase 1).

Goal: capture the full function-call sequence during `switch.ko` init.

### Commands

```bash
# 1. Splice
python3 tasks/00.01.eth-driver/scripts/ko_printk_splice.py \
    --src ext/kmodules_dump/switch.ko \
    --out tasks/00.01.eth-driver/out/spliced/switch.scope-init.ko \
    --scope init

# 2. Push to device
scp tasks/00.01.eth-driver/out/spliced/switch.scope-init.ko \
    admin@192.168.1.1:/tmp/

# 3. Start UART capture (in another terminal)
python3 lib/uart.py log > tasks/00.01.eth-driver/captures/spliced_logs/switch.scope-init.$(date +%F).log

# 4. Hot-swap the module (via ssh)
python3 lib/ssh_shell.py "rmmod switch; insmod /tmp/switch.scope-init.ko"

# 5. Stop UART capture, review log
```

### What to look for in the log

A sequence of lines like:
```
[STOCK] init_module
[STOCK] switch_probe
[STOCK] chip_init
[STOCK] chip_tm_init        ← the function we care about
[STOCK] chip_pp_init
[STOCK] ...
```

Each line corresponds to one `.init.text` function entry. Expected total:
50–200 lines (Tier 1 is bounded — each function fires once per `insmod`).

### Deliverable

`tasks/00.01.eth-driver/captures/spliced_logs/switch.scope-init.<date>.log`
committed to git.

**Success condition**: the log shows `chip_tm_init` getting called (or some
near-equivalent symbol). If it doesn't, our hypothesis about WHERE the
missing init code lives is wrong — re-evaluate before Phase 3.

## Phase 3 — drill into chip_tm_init

**Status**: 📋 PLANNED **·** **TaskList #19** **·** Cost: ~1–2 hours (multiple splice/capture cycles).

Now we know `chip_tm_init` is called. Next we want every register write *inside* its call chain. That requires Tier 2 (regex scope), so the splicer
gains its `--scope <regex>` flag here if it didn't already.

### Commands

```bash
# 1. Splice with a regex that catches chip_tm_init + every helper it likely calls
python3 tasks/00.01.eth-driver/scripts/ko_printk_splice.py \
    --src ext/kmodules_dump/switch.ko \
    --out tasks/00.01.eth-driver/out/spliced/switch.scope-tm.ko \
    --scope '^(chip_tm_|pp_reg_write|qmg_reg_write|sch_reg_write|switch_reg_write)'

# 2. Push, swap, capture (same as Phase 2)

# 3. The expected log shape:
#    [STOCK] chip_tm_init
#    [STOCK]   pp_reg_write r0=0x28 r1=0x1
#    [STOCK]   pp_reg_write r0=0x2c r1=0x02000000
#    [STOCK]   qmg_reg_write r0=0x40 r1=0x3
#    [STOCK]   sch_reg_write r0=0x10 r1=0x5
#    [STOCK]   ... etc ...
```

### Analysis output

Write up findings in
**`tasks/00.01.eth-driver/findings/chip_tm_init.md`**:

- Full register-write sequence (address, value, ordering)
- Cross-reference each write to whether our mainline driver does it
- Mark the **missing** ones explicitly — that's the actionable diff

This findings doc is the input to Phase 4.

### Risks for Phase 3

- Some helpers may be inlined by GCC in the stock build → can't be spliced.
  Fallback: read the Ghidra-decompiled `chip_tm_init` in
  `tasks/00.10.02.re-stock-kmods/ghidra/` for those inlined sites.
- If the trace is too verbose (e.g. `pp_reg_write` fires 1000+ times because
  some inner loop) → switch to a tighter regex or use Tier 3 with
  `--max-calls`.

## Phase 4 — port and verify

**Status**: 📋 PLANNED **·** **TaskList #20** **·** Cost: hours to days, mainline kernel work.

Edit `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c` to replay the
register-write sequence from `findings/chip_tm_init.md`. This is where the
actual driver coding happens.

### Iter loop (use the fast RAM-only path)

```bash
# 1. Edit the driver
$EDITOR linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c

# 2. Rebuild kernel
cd linux-v6.6 && make ARCH=arm CROSS_COMPILE=$CROSS_COMPILE_PREFIX -j$(nproc)
cd ..

# 3. Rebuild slotA bundle for TFTP
python3 tasks/00.01.eth-driver/scripts/build_slotA.py

# 4. RAM-only test (NO nand write — instant revert on reboot)
python3 lib/uart.py auto_bootm_dtb_appended

# 5. On the device: check if RX is alive
#    (via SSH or via the boot console once Linux is up)
cat /proc/interrupts | grep zx_eth        # tm_irq_count > 0 ?
ip link show eth0                         # link up ?
ping -c 3 192.168.1.50 from the device    # actual packets ?
```

~3 min per cycle. Repeat until RX path works.

### Success condition (THE goal of all 5 phases)

- TM IRQ fires (`tm_irq_count` > 0 after a few ping attempts)
- RX descriptor ring gets populated (visible in `ethtool -S eth0` if exposed,
  or via `/proc/zte/sys/...`)
- `ping 192.168.1.1` from a host on the LAN receives responses

That closes TaskList **#87**, **#91**, **#92**, **#93** in one shot.

### When to call Phase 4 done vs. recurse to Phase 5

- If RX comes alive → Phase 4 done. `rx_path_dead.md` graduates from
  `research/` to `findings/`. Move on to TX hardening or unrelated work.
- If RX still dead → some other module's init is also missing. Pick the
  next suspect (`pp.ko`, `plat-zxylzb_9128S.ko`, `idmfdb.ko`) and recurse
  through Phases 2–4 for it. **Phase 1 stays done** — the splicer is reusable
  across all .kos.

## Phase 5 — extend the methodology to other stock .kos (as needed)

**Status**: 📋 PLANNED **·** TaskList: (open one per stock .ko when concrete) **·** Cost: recurses Phases 2–4 per module.

Same loop as Phases 2–3 applied to:

- `ext/kmodules_dump/pp.ko` — packet processor (suspected #2 cause)
- `ext/kmodules_dump/plat-zxylzb_9128S.ko` — platform driver, sets up the
  bus / arbitration / clock domains
- `ext/kmodules_dump/idmfdb.ko`, `voip_codec.ko`, etc. — unlikely but
  possible

Each module gets its own `findings/<modname>_init.md` and its own porting
PR to the mainline driver.

The splicer tool itself doesn't change — same `--scope init` for the first
pass, same `--scope <regex>` for the deep drill, same `out/spliced/` for the
patched binaries, same UART capture loop.

## Risks across the whole plan

| Risk | Probability | Mitigation |
|---|---|---|
| Splicer's ARM relocation handling broken → silent no-op printks | medium | Smoke-test on a `.ko` we own (Phase 1 step 4) BEFORE trusting it on stock binaries |
| `chip_tm_init` itself isn't the missing piece (hypothesis wrong) | low-medium | Phase 2's broad trace will show — if `chip_tm_init` doesn't appear in the call chain, re-evaluate |
| Tier-1 log volume swamps UART | very low | Tier 1 is init-only, ~50–200 lines per insmod; well under UART bandwidth |
| Stock kernel rejects our patched `.ko` (signature, version magic) | low | Stock has `CONFIG_MODULE_SIG = n` per `docs/STOCK_DEBUG_INFRASTRUCTURE.md`. vermagic mismatch handled by `modprobe --force` if needed |
| Heisenberg — `printk` itself changes timing, hides the bug | low | We're tracing init (one-shot, not real-time), so timing effects are minimal |
| Splicer adds too much code → `.ko` exceeds memory or `.text` overflow | very low | Tier 1 is ~50 thunks × 32 bytes = ~1.6 KB added to a ~50 KB `.ko`. Trivial |

## What this plan deliberately does NOT cover

- **The splicer becoming a generic project tool**: it stays in
  `tasks/00.01.eth-driver/scripts/` per CLAUDE.md rule-of-two until a
  second consumer task wants it (then promote to `tools/`)
- **Tier 3 (every-function-with-rate-limit)**: not built in v1, plumbed
  into the CLI from day 1 so we can add it later without breaking callers
- **WiFi or PCIe driver tracing**: same methodology would apply, but those
  drivers already work — no debug pressure
- **Stock cspd or daemon-level tracing**: out of scope; this plan is
  kernel-side only

## See also

- [`research/printk_injection_methodology.md`](research/printk_injection_methodology.md) — the methodology this plan executes
- [`research/rx_path_dead.md`](research/rx_path_dead.md) — the blocker this plan unblocks
- [`ETHERNET_DRIVER_DESIGN.md`](ETHERNET_DRIVER_DESIGN.md) — driver architecture
- [`docs/STOCK_DEBUG_INFRASTRUCTURE.md`](../../docs/STOCK_DEBUG_INFRASTRUCTURE.md) — what stock gives us (logctrl, /proc/tm/shell, /etc/autokernelconf)
- [`docs/STRATEGY_STOCK_AS_ORACLE.md`](../../docs/STRATEGY_STOCK_AS_ORACLE.md) — the overall RE strategy
- [`docs/ITERATE.md`](../../docs/ITERATE.md) — the 3 canonical iter loops
- `tasks/00.02.stock-shell/` — the cspd-patched UART bridge (foundation for everything)
- `tasks/00.04.flash-tool/` — flash mechanism used in Phase 0 and Phase 4
- `tasks/00.10.02.re-stock-kmods/ghidra/` — Ghidra project for cross-referencing
  decompiled stock `.ko`s against the spliced traces
