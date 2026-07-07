#!/usr/bin/env python3
# WiFi bootargs (pci=nomsi pcie_aspm=off ... mem=256M) + a LONG 10s DTR-off so
# the SoC fully resets (recovers a wedged warm-state where the eth insmod
# stalls / never reaches "REPL ready"). Otherwise identical to
# reboot_mainline_wifi.py. Session-local (Stage-3 device agent, 2026-07-07).
import os, sys
os.environ["UART_TCP"] = "1"
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "lib"))
import uart

# Force a 10s DTR-off cold reset (default is 2.0s).
uart.bridge_dtr_pulse.__defaults__ = ("localhost", 9998, 10.0)

BOOTARGS = ("pci=nomsi pcie_aspm=off console=ttyAMA0,115200n8 mem=256M "
            "ignore_loglevel")
MAX_RETRIES = 3
KERNEL_READY_MARKER = "REPL ready"
KERNEL_READY_TIMEOUT = 240
TFTP_NIC = os.environ.get("ZTE_TFTP_NIC", "enxc8a362e95900")

ser = uart.open_port()
ok = False
for attempt in range(1, MAX_RETRIES + 1):
    print(f"\n>>> [reboot_wifi_longdtr] attempt {attempt}/{MAX_RETRIES}", flush=True)
    try:
        uart.bridge_dtr_pulse()
    except Exception as e:
        print(f"[reboot_wifi_longdtr] DTR pulse failed: {e}", flush=True)
        continue
    if not uart.drive_cspstart_to_uboot(ser, password="Boot4128s!"):
        print("[reboot_wifi_longdtr] could not reach U-Boot after DTR", flush=True)
        continue
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
        print(f"[reboot_wifi_longdtr] U-Boot sequence failed: {result['status']} "
              f"at cmd #{result['failed_at']}", flush=True)
        if result["status"] in ("tftp_fail", "timeout"):
            uart.recover_stuck_nic(TFTP_NIC)
        continue
    print(f"[reboot_wifi_longdtr] bootm sent — waiting {KERNEL_READY_TIMEOUT}s "
          f"for {KERNEL_READY_MARKER!r}", flush=True)
    if uart.wait_for_marker(KERNEL_READY_MARKER, timeout=KERNEL_READY_TIMEOUT,
                            start_offset=log_offset):
        ok = True
        break
    print("[reboot_wifi_longdtr] kernel marker not seen — retry from DTR", flush=True)

print("BOOT_OK" if ok else "BOOT_FAIL")
sys.exit(0 if ok else 1)
