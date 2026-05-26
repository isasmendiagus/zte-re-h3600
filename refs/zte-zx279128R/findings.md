# Findings from ZX279128R sibling boot log

Cross-referenced against our current mainline driver boot (2026-05-26).
Source: `zx279128R_boot.log` (3540 lines, stock 4.1.25 boot).

## Confirmed (matches our understanding)

| Fact | Sibling boot | Our setup |
|---|---|---|
| Kernel baseline | 4.1.25+ SMP PREEMPT | Same (stock side); mainline 6.6 (our side) |
| CPU | ARM Cortex-A9 @ 800 MHz, dual core | Same (we run @1 GHz in H3600) |
| UART | `94405000.serial: ttyAMA0 at MMIO 0x94404000 (irq=22)` | Same MMIO + IRQ |
| Boot args | `console=ttyAMA0,115200n8 root=/dev/mtdblock5 rootfstype=jffs2 mem=256M` | Same shape; we use mtdblock8 (different NAND layout) |
| Kernel load addr | `0x40008000` (uncompressed) | We use `0x42000000` (different memory map) |
| NAND chip | ESMT `c8-1-7f-7f` (`Specmaf_id:c8`) | Same chip (F50L1G41LB) |
| 4 MACs + on-chip switch | `mac 0..3 link down/up` printk pattern | Same architecture |
| Two IDM netdevs | `init wifi hardware forward handler(to idm0)/(to idm1)` | Same in our driver |
| BPPE pool layout | `bppe_va_addr=0xcef00000, jumbo_bppe_va_addr=0xcef10000` (vmalloc) | Same shape (we allocate at boot time) |
| IDM descriptor init | `idm_desc_init d0b2c000/4de10000` (virt/phys) | Same pattern |

## New / actionable

### 1. Per-MAC PHY link state (we don't have this)
```
mac 0 phy status changed: 1000M full-duplex
...
mac 0 link down
mac 1 link down
mac 2 link down
mac 3 link down
```
Stock reads PHY status from each of the 4 MACs and tracks per-port link
state. Our driver never reads any PHY — explains why we don't react to
cable plug/unplug. **Required for proper netdev behavior + DSA**.
Action: connect to `mdio@9a101000` + `gephy128s@9b000000` (4 PHYs at
`0x9b000000 + i*0x100000`).

### 2. Separate "switch module" init
```
Init switch module
zy switch detected boardtype:192
switch config 9127/9128 GPON  mode!
[SW][sw_init_switch] reg hff
[SW][sw_init_switch] reg get statistics
Init switch module Success
```
Stock has a dedicated switch driver/module separate from PON+TM that
auto-detects board type (192 here, our H3600 likely different) and
configures GPON vs ethernet-only mode. We currently treat switch as
implicit in the unified driver. **For DSA, this maps to the dsa_switch
init path.**

### 3. PON has runtime mode config
```
pon init
the pon mode is 8
```
We don't see a "pon mode" anywhere in our driver. Mode 8 in this unit
controls the GPON optical link behavior. Our H3600 doesn't run GPON,
but the same register/config word likely exists.

### 4. PON exposed as MII device
```
g_mii_dev_name[1]  pon
```
The PON-side block apparently exposes a phy/mii device named "pon" in
addition to the per-MAC MII bus. We don't use this — irrelevant for
non-GPON, but explains stock's `[1]` entry.

### 5. TM init prints buffer counts
```
pon_tm net init ok,248/176
```
Stock prints `248/176` — probably (`num_bppe_buffers`, `num_jumbo_bppe`).
We could add a similar line so dmesg confirms TM init succeeded.

### 6. fpga write to SW block
```
fpga write: reg=0x000c0000, data=0x00bb6003
```
This is the FPGA-descriptor-based access. `0x000c0000 * 4 = 0x300000`
absolute offset within the 0x92000000 window → `0x92300000` = **SW
block base**. Stock writes one config word to SW init register during
boot. Our driver doesn't explicitly write here (but may catch it via
the broad 2 MiB ioremap if it happens to be in stock_table).

### 7. Linux virq mapping (informational)
Stock's Linux IRQ numbers (after GIC remap):
```
g_tm_irq:35
g_npp_irq:19
g_pp_irq:37
g_idm_irq:33
```
These are Linux virq numbers, not the GIC SPI hwirq values in the DTS
(0x24/0x23/0x25/0x26). Our DT binding correctly uses GIC SPI numbers.

### 8. GePHY IRQ trigger warnings
```
genirq: Setting trigger mode 8 for irq 39/40 failed (gic_set_type+...)
```
Mode 8 = `IRQ_TYPE_EDGE_BOTH`, which ARM GIC v2 doesn't support.
Trigger gets silently clamped to LEVEL/RISING. Affects irq 39+40 (PHY
link interrupts in `gephy128s@9b000000`).

## Non-applicable to our H3600 unit

- GPON stack init (`zx279100_gpon_Init ok`, `mt7603_switch_channel`, etc.) — this is a GPON ONT (optical) device.
- Built-in WiFi (MT7603 + MT7613 on PCIe) — H3600 also has MT7615 but already in our 00.07.wifi work.
- `boardtype:192` — board-specific (TQY00R, hardware version V6.0). Our H3600 is a different board.

## Where the new info lands in our project

| Finding | Phase / task |
|---|---|
| MAC link state via MDIO + GePHY drivers | Future DSA work (post Phase 10b) |
| Switch as separate module | Same — DSA architecture |
| PON mode 8 register | Worth grepping Ghidra to find PON_MODE config reg |
| TM init buffer count print | Cheap dmesg-line improvement (Phase 11 polish) |
| fpga write to 0x300000 / SW | Audit our stock_table writes near 0x140000 (=0x300000-0x1c0000) to check we're hitting this |
