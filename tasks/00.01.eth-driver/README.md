# eth-driver — Linux 6.6 ethernet driver for ZX279128S

**ID**: 00.01
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: none yet (open work lives in `research/*.md`; promote to a subfolder if it grows scripts+artifacts)
**TaskList items**: #53, #87, #89, #90, #91, #92, #93, #103, #104
**Status**: ACTIVE — RX path dead (`research/rx_path_dead.md`); TX intermittent.

**Goal**: port the ZTE-proprietary ethernet stack (Traffic Manager + Switch +
PP packet processor + CLA + IDM CPU port + BMU buffer manager) to a clean
upstream Linux 6.6 driver, so we can run a normal kernel and toolchain on
the H3600 instead of the stock 4.1.25.

**Status**: TX path partially working (zx_sw_xmit baseline ships packets;
TM forwarding gate still under investigation — task #91). RX path with
NAPI was implemented (task #55) but `rx_packets=0` in practice — see
`research/rx_path_dead.md` for the open investigation.

For driver internals, see `ETHERNET_DRIVER_DESIGN.md` (141 KB, ground truth).

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
└── findings/                       ← answered investigations (promoted from research/)
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

See `tasks/00.03.nand-flash/README.md` for NAND layout + CRC rules + the DTR
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
- `tasks/00.03.nand-flash/README.md` — NAND layout + flash bundle (read before any flash)
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
