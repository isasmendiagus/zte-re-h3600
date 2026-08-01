# USB Enablement — Plan (2026-08-01)

## Hardware
- SoC: ZTE ZX279128S
- Controllers: DWC3 (USB3 SuperSpeed) @ 0x09100000 + DWC2 (USB2 OTG) @ 0x09000000
- Physical: 1x USB3 Type-A port (rear panel)
- Clocks: TOPCRM 0x9400004C bits 0-8 (DWC2), bits 9-14 (DWC3)

## Already done
- Glue driver: dwc3-zx279128s.c (165 lines) — TOPCRM clock gating, DWC3 PHY tweaks, SoC ctrl enable
- DT: usb3 node status="okay", compatible="zte,zx279128s-dwc3"
- Config: DWC3, xHCI, usb-storage, UAS, VFAT/ext4/NTFS, partitions — all enabled

## Test plan (15 min)
1. Boot mainline, check dmesg for "ZX279128S DWC3 glue ready" + "xhci-hcd"
2. Insert FAT32 pendrive → verify /dev/sda1 appears
3. mount -t vfat /dev/sda1 /mnt/usb; ls /mnt/usb
4. Write test: dd if=/dev/zero of=/mnt/usb/test.bin bs=1M count=50 conv=fsync
5. Read test: dd if=/mnt/usb/test.bin of=/dev/null bs=1M count=50
6. Hotplug: unplug, verify "USB disconnect", reinsert, remount

## Expected throughput
- USB2: ~30 MB/s
- USB3: ~100+ MB/s (if SuperSpeed PHY wired, quirked via snps,dis_u3_susphy_quirk)

## Phase 2 (optional)
- DWC2 node status="disabled" — needs SoC glue driver
- Low priority since USB3 covers host connectivity
