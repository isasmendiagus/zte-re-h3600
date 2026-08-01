# usb — USB pendrive mount / R/W / throughput / hotplug

**ID**: 00.08
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: none
**Status**: 🔧 PLANNED — driver complete, DT ready, pending physical test

## What's done

- **Glue driver**: `dwc3-zx279128s.c` (165 lines) — handles TOPCRM clock gating,
  DWC3 PHY tweaks, SoC USB ctrl enable, child population. Already in kernel tree.
- **DT node**: `usb3@9100000` with `compatible = "zte,zx279128s-dwc3"` — already
  `status = "okay"` in dtsi, not overridden by board DTS.
- **Kernel config**: DWC3, xHCI, usb-storage, UAS, VFAT/ext4/NTFS, partition
  support — all enabled.
- **Hardware**: ZX279128S has DWC3 (USB3 SuperSpeed) + DWC2 (USB2) controllers.
  TOPCRM bits 0-14 gate USB clocks. Physical USB3 Type-A port on rear panel.

## What's pending

1. **Boot test**: DTR-boot mainline, check dmesg for "ZX279128S DWC3 glue ready"
   and "xhci-hcd" probing.
2. **Pendrive mount**: Insert FAT32 pendrive, verify `/dev/sda1` appears,
   mount R/W, test with `dd`.
3. **Throughput**: `dd if=/dev/zero of=/mnt/usb/test.bin bs=1M count=50 conv=fsync`
   (write) and readback. Expect ~30 MB/s (USB2) or ~100+ MB/s (USB3).
4. **Hotplug**: Unplug, verify dmesg "USB disconnect", reinsert, remount.

### Phase 2 (optional) — USB2/DWC2
- DWC2 node is `status = "disabled"` in DT
- Needs SoC glue driver (similar to dwc3-zx279128s.c)
- Low priority — USB3 covers host connectivity

## Hardware

- SoC: ZTE ZX279128S — DWC3 SuperSpeed + DWC2 OTG
- Physical: 1x USB3 Type-A port (rear panel, standard ONU/router layout)
- Clocks: TOPCRM `0x9400004C` bits 0-8 (DWC2), bits 9-14 (DWC3)

## Plan

See `research/usb_plan.md` for full research. Based on agent research 2026-08-01.
