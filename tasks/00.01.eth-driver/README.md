# eth-driver — Linux 6.6 ethernet driver for ZX279128S

**ID**: 00.01
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: [00.01.01.fix-lief-rel-sections](../00.01.01.fix-lief-rel-sections/) (LIEF upstream fix), [kotrace/](kotrace/) (loader-notifier RAM-patch tracer, working)
**TaskList items**: #53, #87, #89, #90, #91, #92, #93, #103, #104
**Status (2026-05-28)**: RX works end-to-end. TX: CPU→LAN frames pass QMG + DSCH
(the DSCH shaper-credit drop is **FIXED** via `zx_sch_init`) but die at the **SOPC
egress** stage — the frame never reaches a physical MAC (SMAC TX stays 0). Live
debug toolkit (poke/regdump/mem/txtest) built — see "Live debug toolkit" below.
Current frontier docs in `../00.10.02.re-stock-kmods/findings/`:
`session_2026-05-28_tx_egress_state.md`, `eth_pipeline_architecture_2026-05-28.md`,
`txtest_clean_trace_dsch_fixed.md`.

**Goal**: port the ZTE-proprietary ethernet stack (Traffic Manager + Switch +
PP packet processor + CLA + IDM CPU port + BMU buffer manager) to a clean
upstream Linux 6.6 driver, so we can run a normal kernel and toolchain on
the H3600 instead of the stock 4.1.25.

For driver internals, see `ETHERNET_DRIVER_DESIGN.md` (141 KB, ground truth).

## Live debug toolkit + build/flash loop ⭐ (2026-05-28)

### Build + RAM-boot (no NAND write) — the fast iter loop
- **One-shot**: `bash tasks/00.01.eth-driver/scripts/refactor_test_cycle.sh`
  (regen → build → DTR-reset boot → watch UART log ~180s).
- **Or split**:
  1. `python3 tasks/00.01.eth-driver/scripts/build_slotA.py`
     → builds the driver + zImage, wraps `tftp/zImage_dtb.uimg`.
  2. `python3 tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py`
     → DTR relay reset → drive U-Boot → TFTP to RAM 0x42000000 → `bootm`.
     RAM-only; next power-cycle returns to whatever's on NAND.
- NAND-persistent flash (only when shipping): `scripts/flash_mainline.py`
  — read `tasks/00.04.flash-tool/README.md` FIRST.
- Pre-flight (`STATE.md`): TFTP serving from `zxic/tftp`, no stale `uart.py`
  holding the port, `uart_bridge.py` running.

### Live register debug — reflash-free, via the UART bridge socket `localhost:9999`
The bridge exposes the device REPL on TCP **9999** (commands) + **9998** (DTR/reset).
The REPL execs ONE busybox applet per line (no `;`/`|`/redirect directly), BUT
`sh -c "..."` works and gives redirects. Mount once per boot:
`mount -t debugfs none /sys/kernel/debug`.

Driver debugfs `/sys/kernel/debug/zx_eth/` (added this session):

| file | how | what |
|---|---|---|
| `stats` | `cat` | driver counters (tm_rx_count, tm_rx_loopback_drops, tm_tx_count, TM[0x10054/58]…) |
| `regdump` | `cat` | hex-TEXT `<phys> <val>` of forwarding windows — robust over the glitchy UART (vs binary `mem`) |
| `mem` | binary | 2 MiB dump of `e->base+0..0x200000` |
| `poke` | `sh -c "echo '<phys> <val>' > .../poke"` | **live register WRITE**; phys in [0x921c0000,0x923c0000), 4-aligned |
| `txtest` | `sh -c "echo N > .../txtest"` | inject N KNOWN TX frames via `zx_sw_xmit` (dst=host MAC, ethertype 0x88b5) — isolates the TX path, no ARP/ping/storm |
| `memdump <hexphys> <hexlen>` | busybox bin in `/bin` | hex peek by physical address |

Addressing: **phys = 0x921c0000 + e->base offset.** PP at +0x1c0000, MAC[i] at
+(i+1)*0x40000 (MAC2/host = 0x92280000), TM at low offsets.
Full tool doc: `../00.10.02.re-stock-kmods/findings/live_poke_peek_tool.md`.
Pipeline stage-by-stage counter map (find where a frame dies):
`../00.10.02.re-stock-kmods/findings/pipeline_counter_map.md`.
Host capture (no sudo — tcpdump has `cap_net_raw`):
`tcpdump -i enxc8a362e95900 -e -nn 'ether host f4:f6:47:0f:42:64 or arp'`.

> NOTE: `poke`/`regdump`/`txtest` are DEBUG-only (in `zx-eth-main.c`
> `zx_poke_*`/`zx_regdump_*`/`zx_txtest_*`); strip before upstreaming.

## Tracing the stock driver — current state (2026-05-26)

kotrace (`kotrace/`) is the live RAM-patch tracer we use to capture
stock-driver behavior. **Post-boot loading works fully** (insmod
`/tmp/kotrace.ko` from netshell → 2157 functions patched across plat /
tm / switch / mt7915 / idmfdb → 32 k+ entries captured during a single
ping). **Boot-time bake-in init capture is parked** — silent SoC reset
when too many functions are patched at module-load time; root cause
likely cortex-A9 icache prefetch errata or init-context call-site
assumptions our naive 4-byte branch can't honor. The exhaustive
experiment log + lessons-learned are in
[findings/kotrace_init_capture.md](findings/kotrace_init_capture.md).

Workflow docs to read in order if you're picking this up fresh:

- `findings/kotrace_workflow.md` — fast post-boot iter loop (the path that works)
- `findings/kotrace_bake_in.md` — the bake-in pipeline + the rabbit hole
- `findings/kotrace_init_capture.md` — option B plan + everything tried + why each failed
- `findings/idea_a_kotrace.md` — original kotrace design (Phase A3)

Practical shell access on the bake-in rootfs: `nc 192.168.1.1 9001`
(raw-TCP netshell, source at `tasks/00.02.stock-shell/netshell.c`).
Avoids ZTE's patched dropbear entirely — see CLAUDE.md "SSH gotchas".

If init-time capture becomes truly blocking later, the unparked path
is `tasks/99.01.linux-stockport/`: vanilla 4.1.25 + ZTE board file +
turning on `CONFIG_KPROBES=y` / `CONFIG_FUNCTION_TRACER=y` then using
mainline kprobes (~4400 hardened lines) instead of our 10-line
`insn_is_displaceable()`. Estimated 1–2 days incl. kernel flash risk.

## Refactor plan — replacing bulk replay with explicit C (task #38)

Stockport was unparked 2026-05-26 and now boots cleanly, providing a
live oracle for the stock eth stack. The captured init flow (SHIM_TRACE
+ kotrace + Ghidra) maps directly to the mainline-driver refactor:

- **Input** (read first): [`../00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md`](../00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md)
  — canonical knowledge base of what stock does at init.
- **Plan**: [`findings/stockport_to_mainline_refactor_plan.md`](findings/stockport_to_mainline_refactor_plan.md)
  — phased plan (6 phases, ~4–7 days total) to replace the 480 KB of
  binary replay blobs (`fpga.bin`/`stock.bin`/`cla.bin`/`pm.bin`) with
  explicit C code derived from the stock init flow.

## Layout

```
tasks/00.01.eth-driver/
├── README.md                       ← this file
├── ETHERNET_DRIVER_DESIGN.md       ← design doc (141 KB, the ground truth)
├── initramfs/                      ← initramfs staging for mainline boot
│   ├── bin/busybox                   (HARD-FLOAT — being replaced, see ROADMAP)
│   ├── lib/modules/                  zx279128-eth.ko (the live build copy)
│   └── lib/firmware/zx-replay/       stock register replay tables
├── captures/                       ← raw register/state dumps from stock device
│   ├── stock_dumps/                  (brctl, dmesg, iomem, idm_fdb, etc.)
│   └── stock_state/                  (live sysfs / debugfs snapshots)
├── scripts/                        ← task-specific Python helpers
│   ├── build_slotA.py                builds tftp/slotA.bin + header (NAND-flash bundle)
│   ├── capture_tx_regs.py            stock TX register snapshot
│   ├── dump_stock_function.py        per-function symbol/addr dump
│   ├── dump_stock_regs.py            general register dumper
│   ├── flash_mainline.py             U-Boot drive to flash mainline to slot A
│   ├── probe_stock_tracing.py        probe what tracing infra exists on stock
│   └── stock_recon.py                first-look reconnaissance
├── research/                       ← LIVE investigations (one .md per open question)
│   ├── README.md                     template + lifecycle
│   ├── rx_path_dead.md               THE blocker (#87, #91, #92, #93)
│   └── printk_injection_methodology.md  the RE methodology to unblock RX (#103, #104)
├── findings/                       ← answered investigations
│   ├── ko_splice_bugs.md             why on-disk LIEF splicing fails on this kernel (3 bugs)
│   └── idea_a_kotrace.md             the working RAM-patch tracer + first init trace captured
├── kotrace/                        ← the working tracer kmod (Idea A)
│   ├── README.md                     operator's manual
│   ├── kotrace.c                     module-notifier + RAM-patcher
│   ├── hello.c                       Phase A1 build-env sanity .ko
│   ├── Makefile                      out-of-tree build against 4.1.25 tree
│   └── build_rootfs_with_kotrace.py  bake into a rootfs + insmod-at-boot via init.norm
├── out/                            ← gitignored build artifacts (rootfs, spliced .kos)
└── PLAN_init_debug.md              ← phased plan for the init RE work
```

The kernel source + build output live at the zxic/ root (not inside this
task folder) because they're enormous and shared:
- `../../linux-v6.6/` — kernel source (1.5 GiB)
- `../../build/` — kernel build output (1.1 GiB)
- `../../tftp/` — what U-Boot serves
- `../../ext/h3600_nand_full.bin` — factory NAND backup (recovery)

## How to build the kernel + driver

See `docs/KERNELS.md` "kernel #1 — mainline 6.6" for the canonical
commands. Quick form:

```sh
cd ~/Projects/MYSELF/ZTE/zxic/linux-v6.6
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build \
     zImage dtbs modules -j$(nproc)
```

Output of interest:
- `../build/arch/arm/boot/zImage`
- `../build/arch/arm/boot/dts/zte/zx279128s-h3600.dtb`
- `../build/drivers/net/ethernet/zte/zx279128-eth.ko`

Then wrap as uImage with appended DTB — full recipe in
`docs/ITERATE.md` Loop A.

## Boot the mainline kernel

Two modes — pick based on what you're doing:

| Mode | When | How |
|------|------|-----|
| **RAM-only** (ephemeral, fast iter) | Active driver dev | `python3 ../../lib/uart.py auto_bootm_dtb_appended` |
| **NAND-persistent** (slot A) | Shipping a build | `python3 scripts/flash_mainline.py` |

See `tasks/00.04.flash-tool/README.md` for NAND layout + CRC rules + the DTR
hardware mod that enables auto-reset. See `docs/ITERATE.md` Loop A for
the full iter cycle.

## Open task IDs (related)

- #53 — MDIO + PHY (deferred — U-Boot autoneg currently sufficient)
- #87 — Port `chip_tm_init` (confirmed missing in mainline) — covered by `research/rx_path_dead.md`
- #89 — Port `zte_api_pp_global_init` + cpu_queue_rate
- #90 — Dump + replay `def_ptl_pkt_map` + `def_ptl_pkt_action`
- #91 — Decode `SchRegTable` / `QmgRegTable` → find TM→PP forwarding gate
- #92 — Investigate `pp[0x2c]` `CPU_FWD` bit 25 auto-clear
- #93 — Extract `def_ptl_pkt_action` table + implement `pro_action` replay
- #103 — Build `tools/ko_printk_splice.py` (unblock RE for #87 etc.)
- #104 — First splice: stock `switch.ko` `chip_tm_init`

The research thread tying #87/#91/#92/#93 together is
`research/rx_path_dead.md`. Read it before touching any of those tasks.

## Related work

- `tasks/00.02.stock-shell/` — custom slot-A rootfs + kmsg2uart daemon (gives
  persistent UART + SSH on **stock** kernel — the RE oracle for this task)
- `tasks/00.04.flash-tool/README.md` — unified flasher (read before any flash)
- `tasks/99.01.linux-stockport/` — vanilla 4.1.25 + stock-shim attempt (parked)
- `tasks/99/pcie_re/` — PCIe driver RE (the MT7915 WiFi sits on PCIe)
- `../../docs/KERNELS.md` — where all 3 kernel trees live + which to use
- `../../docs/ITERATE.md` — the 3 dev loops

## Notes

- The driver lives **in-tree** at
  `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`. It's not an
  out-of-tree module — that gives us proper Kconfig integration and means
  `make modules` builds it automatically.
- The replay tables (`stock`, `cla`, `pm` blobs) are generated by
  `tools/gen_replay_bins.py` from CSV dumps in `captures/stock_dumps/`.
- `initramfs/` is the staging area; `CONFIG_INITRAMFS_SOURCE` in the
  kernel config points at it so the cpio gets embedded in zImage at link time.
