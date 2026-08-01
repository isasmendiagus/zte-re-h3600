# wifi — MT7915 on internal PCIe (full mainline stack)

**ID**: 00.07
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: [00.07.01 wifi-hardening](../00.07.01.wifi-hardening/), [00.07.02 wifi-throughput](../00.07.02.wifi-throughput/)
**TaskList items**: none directly
**Status**: ✅ DONE — WiFi 6 STA mode confirmed end-to-end (2026-05-04). Productionization in progress (children).

## TL;DR

The H3600 ships a MediaTek **MT7915** (WiFi 6 / 802.11ax dual-band) wired
to the SoC's internal PCIe bus. Mainline `mt76`/`mt7915e` drives the radio
upstream — but only if Linux can enumerate the PCIe bus. That required
writing a SoC-specific glue driver for the ZX279128S's DesignWare PCIe
controller, because mainline has no support for this SoC. Both pieces are
done.

End-to-end: kernel boots → our PCIe driver brings up the bus → mt7915e
binds the chip → cfg80211/mac80211 → wlan0 associates to an AP →
**internet works** (verified `ping 8.8.8.8` via wlan0).

## Architecture (who drives what)

```
+---------------------------- userspace ------------------------------+
|  iw, wpa_supplicant, hostapd                                        |
+---------------------------------------------------------------------+
|  cfg80211 / mac80211                       (mainline, unmodified)   |
+---------------------------------------------------------------------+
|  mt76 / mt7915e                            (mainline, unmodified)   |
+---------------------------------------------------------------------+
|  Linux PCI subsystem                       (mainline, unmodified)   |
+---------------------------------------------------------------------+
|  pcie-zx279128s.ko                         ← OUR custom driver      |
|    (Synopsys DesignWare PCIe wrapper for the ZX279128S SoC)         |
+---------------------------------------------------------------------+
|  ZX279128S SoC PCIe controller hardware                             |
|     |                                                               |
|     +---- MT7915 chip (PCIe endpoint, vendor 0x14c3 device 0x7915)  |
+---------------------------------------------------------------------+
```

The only code WE write is the SoC-PCIe-controller glue. The radio
itself is fully mainline.

## Where the code + docs live

| Artifact | Location |
|---|---|
| **PCIe glue driver source** | `linux-v6.6/drivers/pci/controller/dwc/pcie-zx279128s.c` (417 LoC) |
| **Kconfig + Makefile entries** | `linux-v6.6/drivers/pci/controller/dwc/{Kconfig,Makefile}` |
| **Built module** | `build/drivers/pci/controller/dwc/pcie-zx279128s.ko` |
| **Device-tree node** | `linux-v6.6/arch/arm/boot/dts/zte/zx279128s.dtsi` (PCIe + GPIO + GIC + clocks) |
| **Design + RE notes** | [`docs/PCIE_DRIVER_DESIGN.md`](../../docs/PCIE_DRIVER_DESIGN.md) (Spanish; full memory map, init flow, reset/clock sequence) |
| **Bring-up bitácora** | [`docs/WIFI_STATUS.md`](../../docs/WIFI_STATUS.md) (Spanish; milestones, what unblocked each issue, required firmware blobs) |
| **RE source (Ghidra output)** | `ghidra/output_chain/zte_ZX279127-pcie__FUN_c0015e04.c` |
| **Stock kernel module (RE oracle)** | `ext/kmodules_dump/mt7915.ko` + `/etc/wireless/mt7915/MT7915_EEPROM.bin` |

## Load-bearing insight — MSI vs INTx

The single biggest unblocker during bring-up (from `docs/WIFI_STATUS.md`):

> Stock firmware uses **legacy INTx** interrupts (GIC SPI 95). Mainline
> mt76 prefers MSI via `pci_alloc_irq_vectors(... PCI_IRQ_ALL_TYPES)`,
> and DesignWare PCIe with `interrupt-names = "main", "msi"` configures
> MSI happily. But **MSI delivery to the MT7915 endpoint never works
> on this SoC** — the chip's MCU sends responses but the handler never
> fires.

The workaround: `pci=nomsi` on the kernel cmdline forces INTx.
Permanent fix (figuring out why MSI is broken in the DWC core for this
geometry) is on the "Pendientes" list in `docs/WIFI_STATUS.md` —
it's a polish item, not a blocker.

## Working kernel cmdline

```
pci=nomsi pcie_aspm=off rdinit=/init console=ttyAMA0,115200n8 earlycon=pl011,0x94404000 earlyprintk ignore_loglevel
```

Order matters: ZTE's U-Boot appends `; U-Boot V1.0.0 ...` to whatever the
last arg is, corrupting it. Keep `pci=nomsi` and `pcie_aspm=off` at the
front, or move them into `CONFIG_CMDLINE` (`=y` + `CONFIG_CMDLINE_FORCE`).

## Required firmware blobs (in `/lib/firmware/mediatek/`)

```
mt7915_rom_patch.bin       (linux-firmware,    144 KB)
mt7915_wm.bin              (linux-firmware,   1.26 MB)
mt7915_wa.bin              (linux-firmware,    116 KB)
mt7915_eeprom.bin          (ext/rootfs vendor, 3584 B — symlink mt7915_eeprom_dbdc.bin to this)
regulatory.db + .p7s       (Ubuntu wireless-regdb — keep the pair consistent)
```

The MT7915 EEPROM bytes are **per-unit** (calibration data); you can't
download a generic one. The stock rootfs has the right blob at
`/etc/wireless/mt7915/MT7915_EEPROM.bin` — we extract it from the NAND
dump in `ext/`.

## Module load order

```
1. pcie-zx279128s.ko          (our SoC PCIe driver — enumerates the bus)
2. cfg80211.ko                (mainline)
3. mac80211.ko                (mainline; depends on cfg80211 + arc4)
4. mt76.ko / mt7915e.ko       (mainline; binds the MT7915 endpoint)
```

`mt7915e` will fail to load if `pcie-zx279128s` didn't bring up the bus —
that's the gate.

## How to iterate

Same loop as any kernel work — see `docs/ITERATE.md` for the canonical
3-loop overview. For this driver specifically:

```sh
# 1. Edit driver
$EDITOR linux-v6.6/drivers/pci/controller/dwc/pcie-zx279128s.c

# 2. Build
cd linux-v6.6
make ARCH=arm CROSS_COMPILE=$CROSS_COMPILE_PREFIX modules \
     M=drivers/pci/controller/dwc

# 3. Test RAM-only (fast iter, no NAND write):
python3 lib/uart.py auto_bootm_dtb_appended

# 4. Or persist to slot A (slower, survives reboot):
python3 tasks/00.04.flash-tool/flash.py kernel --src tftp/slotA.bin
```

Per `docs/WIFI_STATUS.md` "Workflow de iteración funcional" for the
exact iter sequence used during bring-up.

## Cross-cutting connections

- **Depends on**: `tasks/00.04.flash-tool/` (to persist new kernels to NAND);
  `tasks/00.06.platform-drivers/` (clk + other SoC drivers the PCIe controller
  needs)
- **Used by**: `tasks/00.openwrt-port/` (OpenWRT needs WiFi for the gateway
  role to make sense at all)
- **Informed by**: `tasks/00.10.04.mainline-archaeology/` (catalog of what
  ZTE-specific code was removed from upstream mainline in 2021 — confirmed
  there was no upstream PCIe glue to inherit)

## See also

- [`docs/PCIE_DRIVER_DESIGN.md`](../../docs/PCIE_DRIVER_DESIGN.md) — design
  + RE notes (Spanish; the authoritative reference)
- [`docs/WIFI_STATUS.md`](../../docs/WIFI_STATUS.md) — bring-up bitácora
  + milestones + remaining "Pendientes"
- `docs/ARCHITECTURE.md` — SoC hardware reference (memory map etc.)
- `docs/CROSS_COMPILE_GUIDE.md` — toolchain setup (soft-float, no VFP)
- `linux-v6.6/drivers/pci/controller/dwc/pcie-designware*` — the mainline
  DWC core our glue plugs into
