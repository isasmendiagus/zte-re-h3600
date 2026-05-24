# ROADMAP — what's next, in what order

## North star (the real one)

**Run OpenWrt on the ZTE H3600.** Everything in between — building a
mainline 6.6 driver, doing kernel-level reverse engineering, etc. — is
infrastructure to get there. The driver work is the long pole; once it
carries traffic, the OpenWrt port is the smaller (but still real) lift.

## Stage map

```
[stage 0] Get SSH on stock firmware (✅ DONE — via orca.pet writeup + AES key)
[stage 1] RE the proprietary stock drivers (✅ partial — TM/switch/PP/IDM)
[stage 2] Build mainline 6.6 zx279128-eth driver (🚧 IN PROGRESS — TX partial, RX dead)
[stage 3] Sustained ping LAN↔device under mainline (⛔ blocked by RX)
[stage 4] Persist mainline kernel in NAND slot A (📋 planned)
[stage 5] Port to OpenWrt as a target (🎯 the actual goal)
[stage 6] Submit driver upstream to netdev (🎯 stretch)
```

## Backstory — how we got here (so we don't reset)

1. **Mainline 6.6 kernel boot**: tried PCIe, WiFi, wpa_supplicant. None working
   in mainline. Switched focus.
2. **ETH driver pivot**: built `zx279128-eth.c` with **brute-force register
   replay** from stock dumps (22,363 stock regs, 1025 pp_pm, 780 CLA) — see
   `tasks/00.01.eth-driver/`. TX path partially works, RX path doesn't.
3. **Stock kernel observability**: cspd patch (3 bytes: `logctrl -g 0/1/2 → -g 3`)
   + `kmsg2uart` daemon (drains `/proc/kmsg`, writes to ZTE-shifted PL011 DR
   at `+0x04` via `/dev/mem`) = **persistent UART output on stock kernel**
   even though the stock kernel's pl011 driver writes to standard DR (+0x00)
   which is silent on this hardware. See `tasks/00.02.stock-shell/`.
4. **kprobes/ftrace verdict**: stock 4.1.25 kernel built with
   `# CONFIG_KPROBES is not set` and `# CONFIG_FUNCTION_TRACER is not set`.
   `/sys/kernel/debug/tracing/` does not exist. Tier 1+2 of
   `docs/STRATEGY_STOCK_AS_ORACLE.md` are DEAD on stock.
5. **Where this leaves us**: we have stock kernel + UART output + the ability
   to load patched `.ko` files. We can do **runtime RE by manually injecting
   `printk` calls** into stock `.ko` binaries, loading them on the stock
   device, and watching output flow through `kmsg2uart` → UART. That is the
   next concrete RE methodology.

## Now (2026-05-22 onward)

### 1. Soft-float busybox  — *unblocks fast iteration*
Rebuild busybox 1.36 with `arm-linux-gnueabi-gcc` (no `-hf`) +
`CONFIG_STATIC=y`. Replace `tasks/00.01.eth-driver/initramfs/bin/busybox`.
Verify: `arm-linux-gnueabi-readelf -A` shows no VFP tags.

**Why first**: unlocks `live_load_mod` cycle (~30s per driver iter vs
~3 min full reboot). Saves enormous time on the RX work below.

### 2. **Manual `printk`-injection into stock `.ko` files** — *the unblock for #3*
Since kprobes is unavailable, the only way to observe what stock's
`switch.ko` / `tm.ko` / `plat-zxylzb_9128S.ko` do at runtime is to
**binary-patch the .ko files** to insert `printk` calls at chosen
addresses, load them on the stock device, and watch the output via
`kmsg2uart` → UART.

Concretely:
- Pick target functions in Ghidra (e.g. `chip_tm_init`,
  `zte_api_pp_global_init`, `def_ptl_pkt_action`-touching code).
- For each, identify a safe insertion offset (between two
  push-prologue or pre-call boundary).
- Inject `BL printk` + a fmt string in `.rodata`:
  - Save regs (`push {r0-r3, lr}`)
  - Load fmt addr (`ldr r0, =fmt_string`)
  - Load arg (`mov r1, <reg-of-interest>`)
  - `bl printk`
  - Restore (`pop {r0-r3, lr}`)
- Add a relocation entry for the printk symbol (resolved at insmod time).
- `tasks/00.02.stock-shell/prepare_slot_a.sh --write` to flash patched .ko
  in the slot-A rootfs (or just SSH+scp+insmod for fast iter).
- Capture UART log → analyze what stock writes / reads.
- Port findings to our mainline driver.

Tooling needed: a small Python ELF splicer (built on `pyelftools` or similar).
A working pattern exists informally in `auto_patch_plat.py`
(in `tasks/99.01.linux-stockport/`) — recycle that as the basis.

### 3. Driver RX path — the real eth-driver blocker
Current state: `tm_irq_count = 0`, `tm_rx_count = 0`,
`rx_packets = 0`. Per-queue RX desc rings empty
(`TM[0x10100..1011c] = 0`). TM hardware never fires RX IRQ.

Specifically:
- Task #91 — decode `SchRegTable` / `QmgRegTable` → find TM→PP forwarding gate
- Task #92 — `pp[0x2c]` `CPU_FWD` bit 25 auto-clear
- Task #93 — `def_ptl_pkt_action` table replay (we replay other tables but not this one)
- Re-verify task #55 (RX path + NAPI) — marked done but rx_packets=0 in practice

**This is what step 2 unblocks** — manual printk injection in stock
switch.ko / tm.ko will reveal what registers/RAM stock writes during
RX init that we're missing.

### 3. Driver TX path — close the intermittent gate
TX works sometimes (22 packets reached host wire in one window),
mostly doesn't. Open RE tasks #87, #89 cover the TM init knobs
that determine the gate.

## Later (after RX/TX work)

### 4. End-to-end ping LAN ↔ device
Host pings device, device replies. ARP works. Sustained traffic.

### 5. Persistence
- Flash mainline kernel to slot A on NAND.
- Initramfs containing only driver + replays + minimal busybox.
- cspstart selects slot A on power-up → mainline kernel → driver → networking.
- Slot B stays factory stock as fallback.

### 6. **OpenWrt port** (the actual goal)
- Add a `target/linux/zxic` (or similar) tree under OpenWrt.
- Package our `zx279128-eth` driver as a kmod.
- Defconfig: PL011 console with ARCH_ZX shifted DR, PCIe stub, USB stub.
- Tooling: a `zxic-firmware-tool` (rename + repackage) to wrap the OpenWrt
  zImage in the ZTE 32-byte wrapper + BootPara header for cspstart to
  accept slot A.
- Image format: cspstart-friendly slot A blob + matching header.
- LuCI on top of standard OpenWrt rootfs.

### 7. Mainline upstream prep (stretch)
- Clean driver code (no static stock-regs replay; do proper DT-based init).
- DT bindings doc.
- DT compatible matched against `zte,zx279128s-eth`.
- Submit RFC patches to `netdev@vger.kernel.org`.

## Cleanup backlog (nice-to-have, no urgency)

- ~~**Unify the 5 flash scripts** into a single `tools/flash.py`~~ — **DONE 2026-05-23**:
  `tasks/00.04.flash-tool/flash.py` (subcommands: kernel/rootfs/both/header/raw).
  Migrating the per-task call sites (eth-driver `flash_mainline.py`, stock-shell
  `flash_slot_a.py` etc.) to invoke the unified CLI is an open opportunistic chore.
- **Soft-float busybox** for `tasks/00.01.eth-driver/initramfs/bin/busybox`
  (already #1 in "Now"; mentioned here for completeness).
- **Translate `docs/CHRONICLE.md` to English** (currently Spanish; grep
  loses half).

## Parked / backlog

- **PCIe driver** (`tasks/99/pcie_re/`) — for the MT7915 WiFi.
- **Stockport** (`tasks/99/stockport/`) — vanilla 4.1.25 + stock-shim attempt.
  Was meant to be an intermediate stepping stone; we leapt to mainline 6.6
  directly so this is mostly archival.
- **WiFi mainline** — depends on PCIe.
- **VoIP / DECT** — out of scope for now.

## Anti-roadmap

Things we are NOT going to do in this project unless explicitly decided:

- Reverse-engineer the proprietary `cspd` daemon (we already patched 3 bytes
  for UART; full RE is not needed).
- Re-implement stock 4.1.25 kernel features that mainline already has.
- OpenWrt packaging until the driver carries traffic upstream.
- Marketing / blog posts / public release until the driver is upstream-clean.

## Cadence

Update this file when the "Now" section changes (a milestone moves done →
the next one starts). Keep "Now" to ≤3 items so it stays focused.
