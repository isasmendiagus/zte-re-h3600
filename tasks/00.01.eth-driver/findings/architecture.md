# ZTE H3600 mainline driver — full architecture

## Hardware layout

```
SoC: ZXIC ZX279128S (ARM Cortex-A9 dual-core @ 1 GHz)
RAM: 256 MiB @ 0x40000000
NAND: 128 MiB SPI NAND (ESMT F50L1G41LB)

FPGA windows (memory-mapped to ARM):
  0x92000000 + 0x400000  : pon block (4 MiB) — main FPGA control
    +0x000000  pon_low (sbragRegTable[0], misc)
    +0x040000-+0x07ffff  ??? (4 sub-blocks at +0x40000 stride)
    +0x080000-+0x0bffff  PON-specific (don't write — hangs bus if unclocked)
    +0x0c0000-+0x17ffff  ??? (PP/IDM-related, 5 sub-blocks)
    +0x1c0000-+0x1fffff  NPP block (MAC/PHY)
    +0x200000-+0x33ffff  ??? (15 sub-blocks)
    +0x340000-+0x37ffff  TM block (BMU, DMA, IRQ, queues — main path!)
    +0x380000-+0x3bffff  PP block (bridge, CLA, classifier)
  0x94000000 + 0x001000  : topcrm (clock/reset manager)
  0x94100000 + 0x001000  : pcie_crm
  0x94200000 + 0x001000  : pcie_crm2
  0x9fe00000 + 0x001000  : ??? (sometimes referenced)

GIC interrupt numbers (verified via stock /proc/interrupts):
  GIC 66 = pon       (FPGA general)
  GIC 67 = pon_npp   (NPP block)
  GIC 68 = pon_tm    (TM block — main RX/TX done!) ⭐
  GIC 69 = pon_pp    (PP block)
  GIC 70 = idm       (IDM block — wifi forwarding)
  GIC 71-74 = gphy0-3 (PHY link state)
```

## Stock kernel module load order

From `lsmod` on running stock device (2026-05-24):
```
shellproc                    (base, permanent)
patch                        (boot-time patches)
zx_ponreg                    (FPGA register accessor — exports `pon`, fpga_read_reg, fpga_write_reg)
plat_zxylzb_9128S            (HARDWARE PLATFORM driver — all the init functions)
mt7915                       (WiFi)
idmfdb                       (IDM forwarding DB — wifi MAC learning, uses mt7915)
switch                       (switch control — uses idmfdb)
tm                           (TM control — uses switch)
... USB, cdc, voip, etc.
```

Dependency tree (resolved from lsmod's "Used by" column):
```
shellproc ⟵ patch (permanent base)
zx_ponreg ⟵ switch, tm
plat_zxylzb_9128S ⟵ mt7915, idmfdb, switch, tm
mt7915 ⟵ idmfdb
idmfdb ⟵ switch
switch ⟵ tm
```

**The critical observation**: `plat_zxylzb_9128S` loads BEFORE `switch.ko`
and `tm.ko`. Its `init_module()` does ALL the HW init (TOPCRM clocks,
TM block setup, BMU, DMA, PP bridge, IRQ registration via
`pon_tm_int_init`, etc.). Once `plat` finishes, the HW is fully
initialized and `switch.ko` + `tm.ko` just add software state on top.

In mainline we collapse this into one driver — `zx279128-eth.c` does
both plat-level HW init AND the switch/tm sw-state setup.

## What each stock module does

### `zx_ponreg.ko` (2 KB)
- Exports `pon` (void __iomem *) — the FPGA window base pointer
- Exports `fpga_read_reg(offset)` and `fpga_write_reg(offset, val)`
- Single-purpose: provides FPGA access to other modules
- In mainline: we use our own `fpga_base` (devm_ioremap of 0x92000000+4MiB).

### `plat_zxylzb_9128S.ko` (~158 KB)
This is THE biggest puzzle piece. Does:
- TOPCRM clock + reset (zx_pon_clk_reset_init)
- Memory reservation (reserve_mem_info)
- PON serdes init
- of_iomap of npp_base, tm_base, pp_base, idm_base
- Sub-init functions called in order from init_module:
  1. `tm_pon_tm_init()` → calls red_init + dma_init + bmu_init + post_bmu + bmu_enable + net_init + int_init
  2. `tm_pon_pp_init()` → calls pp_ctrl_init + pp_brg_init + pp_cla_init + IRQ req
  3. `tm_pon_npp_init()` → NPP MAC + PHY init
  4. `pon_npp_idm_init()` → IDM block init + IRQ req
- Registers net_devices `sw` (and maybe pon0)
- Exports `pon_tm_net_register`, `pon_tm_data_raw_send`, `set_pon_tm_int_info`, etc.
- All the IRQ handlers (`zx_pon_tm_int`, `zx_pon_pp_int`, `zx_pon_npp_int`)

### `tm.ko` (~1.1 MB)
- Implements `chip_tm_init` (HUGE function, ~700 reg writes)
- Implements all the `tmOnuReg*` helpers
- Has the 20 RegTables we decoded (sbragRegTable, tmRegTable, claRegTable, etc.)
- Implements per-API functions like `tm_port_isolate_set`, `tm_protocol_pkt_limit_*`
- Higher-level: protocol-aware traffic management

### `switch.ko` (~153 KB)
- Implements `pdt_ethdrv_send` (TX from sw netdev → calls plat's pon_tm_data_raw_send)
- Implements `pdt_ethdrv_recv` (NAPI poll callback for RX completion)
- Implements `chip_tm_init` orchestration (calls into tm.ko's helpers)
- Switch-aware ndo callbacks
- The "switch chip" abstraction layer

## Mainline driver collapsing

`zx279128-eth.c` consolidates all 4 modules above into one. Order of
operations in `zx_eth_probe`:

```c
1. devm_ioremap fpga_base (0x92000000, 4 MiB)
2. devm_ioremap topcrm     (0x94000000, 4 KiB)
3. dma_alloc_coherent: bppe, bp, rxdesc, txdesc rings
4. zx_tm_pre_init   (TM master config — instances 0..3 of 16)
5. zx_tm_red_init   ★ port of pon_tm_red_init — 1168 queue configs
6. zx_pp_ctrl_init  ★ port of pon_pp_ctrl_init
7. zx_pp_brg_init   ★ port of pon_pp_brg_init + VLAN setup
8. zx_tm_dma_init   (TM[0x10000+] DMA config)
9. zx_tm_bmu_init   (TM BMU init)
10. zx_tm_post_bmu  (TM[0xF0] desc bases per-instance)
11. zx_tm_bmu_enable (TM[0x8000] = 1)
12. zx_sw_netdev_create
13. devm_request_irq(zx_tm_irq, "pon_tm")
14. devm_request_irq(zx_idm_irq, "idm")
15. CPU MAC registration to pp_pm/spa tables
16. CLA replay (from cla.bin firmware)
17. trap_queue replay
18. chip_tm_init_isolate (port isolation x 8)
19. chip_tm_init_pro_action (def_ptl_pkt_action x 8 ports x 71 entries)
20. writel(0xa, fpga+0)  (sbrg_set_irq_en_mask equiv — no-op due to mask=0)
21. bulk replay fpga.bin (whitelist TM/PP/NPP/pon-low, skip desc bases)
22. zx_pp_pm_apply_replay (pp_pm flow info)
23. (re-write TM[+0xF0] for safety — covered by skip in #21)
```

★ marked: ported in this session.

## TX/RX data flow

See `tx_rx_paths.md` for the exact descriptor format and BP buffer layout.
Summary:

```
TX (kernel → wire):
  kernel ndo_start_xmit
  → zx_sw_xmit
  → BMU alloc bp_idx
  → memcpy(bp_buf, skb->data, len)   [TX uses bp_buf+0]
  → fill TX desc:
     desc[0]=0x80
     desc[2..3]=((port+0x28)&0x3f)<<4   ★ egress port indicator (THE TX fix)
     desc[4..7]=0x00010000
     desc[7]=(bp_idx&0x7f)<<1
     desc[8..11]=(bp_hi)|(len<<9)|(0x01<<24)  ★ bit 24 = VALID (not bit 29!)
     desc[12..13]=len<<2 or len|0x100 (small pkt)
  → kick TM[0x10054]=1 (UP) + TM[0x10064]=1 (DN)
  → HW reads desc from TM[0x10050/0x10060] base
  → HW DMAs bp_buf to switch
  → Switch egresses to UNI port (LAN)
  → Wire

RX (wire → kernel):
  Wire
  → Switch RX (MAC port) ingress
  → BMU alloc bp slot
  → HW writes:
     bp_buf[0..15] = HW metadata header (zeros at our observed point)
     bp_buf[16..16+len] = ethernet frame   ★ THE RX offset fix
  → HW writes RX descriptor:
     desc[7]>>1 = bp_idx
     desc[12..13] = len << 2 (le16)
  → HW raises TM IRQ on TM[0x100] bit 0 (RX done) — requires RED queue config!
  → GIC line 68 fires
  → zx_tm_irq handler reads TM[0x100] status & TM[0x104] mask
  → napi_schedule
  → zx_tm_napi_poll iterates 8 RX queues
  → reads bp_buf+16, allocs skb, eth_type_trans, netif_receive_skb
  → loopback filter: drop if src MAC == sw_dev->dev_addr
  → ACK desc via TM[0x4068] + TM[0x4064]
```

## Known issues / artifacts

See `tx_rx_paths.md` "Known artifacts" + `phase4_PING_BIDI_2026-05-24.md`
"Tuning experiments".

Top open issue: switch flooding causes ping DUPs and intermittent loss.
Real fix requires implementing `ffe_learn_skb` equivalent (built into
stock vmlinux, not a module) OR registering host MAC in the switch FDB
via spaRegTable entries.

## Files reference

```
linux-v6.6/drivers/net/ethernet/zte/
  zx279128-eth.c              — main driver (~2800 lines)
  zx-fpga-reg-tables.h        — 20 RegTable definitions
  zx-pp-pro-actions.h         — def_ptl_pkt_action table

tasks/00.01.eth-driver/
  findings/
    architecture.md           — this file
    tx_rx_paths.md           — TX/RX desc format + init sequence
    phase4_PING_BIDI_2026-05-24.md  — Phase 4 session journey
    ... older findings ...
  kotrace/                    — runtime patcher used for stock RE
  initramfs/                  — mainline initramfs (C-init REPL + busybox)
  scripts/
    tftp_boot_mainline.py     — fast iteration via TFTP (no NAND flash)
    build_slotA.py            — build NAND-flashable slot A image
    flash_mainline.py         — flash slot A persistently (slower path)
```
