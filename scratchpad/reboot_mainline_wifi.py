#!/usr/bin/env python3
# Same flow as reboot_mainline.py (DTR -> U-Boot -> TFTP zImage_dtb.uimg ->
# bootm -> wait "REPL ready"), but sets the PROVEN WiFi bootargs before bootm:
# pci=nomsi + pcie_aspm=off at the FRONT (MSI never delivers MT7915 IRQs on
# this SoC; ZTE U-Boot corrupts the LAST bootarg, so criticals go first).
# Exact line proven 2026-05 (docs/WIFI_STATUS.md "Cmdline final que funciona"
# + scratchpad/boot2.log).
# Routes through the running uart-bridge (UART_TCP=1).
import os, sys
os.environ["UART_TCP"] = "1"
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "lib"))
import uart

# NOTE 2026-07-04: the previously-documented May/Jun line carried
# cma=16M@0x4e800000 which lands INSIDE the eth-carved DMA region
# (0x4c000000-0x50000000, DTS eth_carved) now that the eth driver exists —
# it corrupted userspace page cache (every busybox exec SIGSEGV'd, REPL
# [exit=11]). Proven-good recipe: the default-env line (console+mem=256M,
# which boots every eth QA session) with ONLY the two PCI args prepended.
BOOTARGS = ("pci=nomsi pcie_aspm=off console=ttyAMA0,115200n8 mem=256M "
            "ignore_loglevel")

MAX_RETRIES = 3
KERNEL_READY_MARKER = "REPL ready"
KERNEL_READY_TIMEOUT = 240  # 19MB image: decompress+boot ~200s

# Host NIC on the TFTP/boot jack — used ONLY for the stuck-NIC recovery
# below (see uart.recover_stuck_nic docstring: known host USB-driver
# stall, symptom is U-Boot 'T T T' / host carrier=0 despite the device's
# own PHY link-up log). Override with $ZTE_TFTP_NIC if the cabling
# changes; the recovery itself derives the USB path dynamically from the
# iface name, it does not hardcode a bus/port.
#
# NOTE 2026-07-05: the live TFTP path is enxc8a362e95900 (matches
# scratchpad/rig.py's canonical HOST_NIC), NOT the r8152 enx2c9975313ea9
# that older notes named. Verified this session: U-Boot brings up its
# MAC[2]/LAN3 egress ("mac 2 phy status changed") which is cabled to
# enxc8a362e95900 (carrier UP, reaches the device); enx2c9975313ea9 had
# no carrier at all. A stale duplicate 192.168.1.50 on the wrong NIC was
# the actual cause of the 'T T T' storm this session (not the r8152
# stall) — keep the boot IP on ONE carrier-up NIC only.
TFTP_NIC = os.environ.get("ZTE_TFTP_NIC", "enxc8a362e95900")

ser = uart.open_port()
ok = False
for attempt in range(1, MAX_RETRIES + 1):
    print(f"\n>>> [reboot_mainline_wifi] attempt {attempt}/{MAX_RETRIES}", flush=True)
    try:
        uart.bridge_dtr_pulse()
    except Exception as e:
        print(f"[reboot_mainline_wifi] DTR pulse failed: {e}", flush=True)
        continue
    if not uart.drive_cspstart_to_uboot(ser, password="Boot4128s!"):
        print("[reboot_mainline_wifi] could not reach U-Boot after DTR", flush=True)
        continue
    # Only search log content that appears AFTER this point — the bridge log
    # already contains "REPL ready" from earlier boots this session.
    try:
        log_offset = os.path.getsize(uart.LOG)
    except OSError:
        log_offset = 0
    result = uart.run_uboot_seq(ser, [
        ("tftp 0x42000000 zImage_dtb.uimg", 180),
        (f"setenv bootargs '{BOOTARGS}'", 5),
        ("bootm 0x42000000", 5),
    ], wait_for_prompt=True, prompt_timeout=180)
    if result["status"] != "ok":
        print(f"[reboot_mainline_wifi] U-Boot sequence failed: {result['status']} "
              f"at cmd #{result['failed_at']} — retry from DTR", flush=True)
        if result["status"] in ("tftp_fail", "timeout"):
            # Known issue: the host USB NIC on the TFTP jack periodically
            # stalls (U-Boot 'T T T' / host carrier=0 despite the device's
            # own PHY link-up log) — a host USB-driver wedge, not a bad
            # cable/jack. Try the proven no-unplug fix once before burning
            # a whole DTR-retry cycle on a dead host NIC.
            uart.recover_stuck_nic(TFTP_NIC)
        continue
    print(f"[reboot_mainline_wifi] bootm sent — waiting {KERNEL_READY_TIMEOUT}s "
          f"for {KERNEL_READY_MARKER!r}", flush=True)
    if uart.wait_for_marker(KERNEL_READY_MARKER, timeout=KERNEL_READY_TIMEOUT,
                            start_offset=log_offset):
        ok = True
        break
    print("[reboot_mainline_wifi] kernel marker not seen — retry from DTR", flush=True)

print("BOOT_OK" if ok else "BOOT_FAIL")
sys.exit(0 if ok else 1)
