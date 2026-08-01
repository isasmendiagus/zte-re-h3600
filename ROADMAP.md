# ROADMAP — what's next, in what order

## North star (the real one)

**Run OpenWrt on the ZTE H3600.** Everything in between — building a
mainline 6.6 driver, doing kernel-level reverse engineering, etc. — is
infrastructure to get there. The driver work is the long pole; once it
carries traffic, the OpenWrt port is the smaller (but still real) lift.

## Stage map

```
[stage 0] SSH on stock firmware (✅ DONE)
[stage 1] RE the stock drivers (✅ TM/switch/PP/IDM/BMU/CLA/pp_pm/SMCT/SIPC)
[stage 2] Mainline 6.6 zx279128-eth DSA driver: lan0-4 + WAN, RX/TX/wire/hotplug (✅ DONE)
[stage 3] Ethernet HW flow-offload — bidirectional DN+UP, NAT in silicon (✅ DONE, ~line rate, 10GB+)
[stage 3a] Churn / RED CPU-queue "1024" wedge (✅ FIXED — RED_CFG bit6)
[stage 3b] WiFi MT7915: STA + AP + slow-path (✅ DONE) + HW-offload mechanism DN+UP (✅ validated, ⚠️ "wedge #2" gates ftwifi OFF)
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

## Now (2026-08-01)

Ethernet (DSA + **bidirectional HW offload**, NAT in silicon, line-rate) and WiFi
(STA + AP + slow-path + **HW-offload mechanism** validated in both directions)
are all working on mainline. Working branch: `main`.
Current priorities, in order:

### 1. WiFi HW-offload durability — "wedge #2" ✅ DONE
Root cause: BMU DDR prefetch engine never auto-primes its pool on mainline
(bppe_cnt=0 vs stock's ~8112). Fix: manually prime by freeing all 8192 BP
indices after BMU enable → bppe_cnt=1872, bppi_cnt=186. Verified: 
139k WiFi fabric-ingress frames with ZERO freeze (wedge_coldstart.py, 60 rounds).
ftwifi now defaults ON. See `findings/wifi_stage3_wedge2_fix_2026-08-01.md`.

### 2. WiFi productionization (in progress)
Auto-bind (netdevice notifier hooks hostapd vif creation), csum-to-HW
(flow_info bit4, already unconditional), hardening + regress, throughput
tuning (MT7915 11ax/TXBF — test client currently links at 11n).
Multi-SSID + 2.4 GHz + multi-client deferred (need more test hardware).
See `findings/wifi_stage3_*` + memory `zte-wifi-up-offload`. `ftwifi` stays OFF
until fixed. (Two real bugs already fixed en route: BMU BP double-free + the
pm_ext BPPE-table memset wipe.)

### 2. WiFi productionization (after the wedge)
Auto-bind (hostapd vif → idm/ssid, drop the manual `wifi_bind` debugfs knob),
multi-SSID + 2.4 GHz + multi-client, csum-to-HW (flow_info bit4 like eth),
hardening + a regress battery, throughput tuning (strip debug hooks + MT7915
11ax/TXBF calibration — the test client currently links at 11n).

### 3. USB
Pendrive mount / RW / throughput / hotplug (not started).

### 4. Code cleanup before upstream (S1/S2/S3)
FT/DSA dedup, monolith split, strip debug hooks — deferred until fully stable.

## Later

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
