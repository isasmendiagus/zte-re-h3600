#!/usr/bin/env python3
# Recover the wedged device: DTR power-cycle -> drive U-Boot -> TFTP mainline
# zImage_dtb.uimg -> bootm (default jffs2 bootargs) -> wait "REPL ready".
# Routes through the running uart-bridge (UART_TCP=1) so it doesn't fight the
# bridge for /dev/ttyUSB0.
import os, sys
os.environ["UART_TCP"] = "1"
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "lib"))
import uart
ser = uart.open_port()
ok = uart.flash_image_to_ram(ser, image_name="zImage_dtb.uimg",
                             kernel_ready_marker="REPL ready",
                             kernel_ready_timeout=150, max_retries=3)
print("BOOT_OK" if ok else "BOOT_FAIL")
