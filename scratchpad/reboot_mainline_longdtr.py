#!/usr/bin/env python3
# Like reboot_mainline.py but forces a LONG DTR-off (10s) so the upstream WAN
# modem (whose power rides the same DTR line) fully resets. The default
# bridge_dtr_pulse hold is 2.0s which does NOT revive the wedged modem port.
import os, sys
os.environ["UART_TCP"] = "1"
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "lib"))
import uart
# Force default hold_secs -> 10s (monkeypatch the module fn defaults so the
# internal flash_image_to_ram call inherits it).
uart.bridge_dtr_pulse.__defaults__ = ("localhost", 9998, 10.0)
ser = uart.open_port()
ok = uart.flash_image_to_ram(ser, image_name="zImage_dtb.uimg",
                             kernel_ready_marker="REPL ready",
                             kernel_ready_timeout=150, max_retries=3)
print("BOOT_OK" if ok else "BOOT_FAIL")
