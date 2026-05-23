#!/usr/bin/env python3
"""Capture MT7915 + PCIe state from stock kernel via SSH (paramiko shell).
Saves output to /tmp/stock_mt7915_recon.txt
"""
import sys, time, paramiko

HOST, USER, PASS = "192.168.1.1", "admin", "UkuGPeyRDU"
SENTINEL = "@@DONE_$$_MARK@@"

CMDS = [
    "echo === resources MT7915; cat /sys/bus/pci/devices/0000:00:00.0/resource",
    "echo === resources MT7916; cat /sys/bus/pci/devices/0000:01:00.0/resource",
    "echo === interrupts; cat /proc/interrupts",
    "echo === SoC ctrl + LTSSM:; for off in 0x09500000 0x095000DC 0x09600000 0x096000DC; do printf '%s = ' $off; devmem2 $off w 2>/dev/null | grep Value; done",
    "echo === TOPCRM:; for off in 0x94000008 0x94000024 0x9400004c 0x94000070 0x94000074; do printf '%s = ' $off; devmem2 $off w 2>/dev/null | grep Value; done",
    "echo === PCIE-CRM:; for off in 0x94100070 0x94100074; do printf '%s = ' $off; devmem2 $off w 2>/dev/null | grep Value; done",
    "echo === PCIE-CRM2:; for off in 0x9420000c; do printf '%s = ' $off; devmem2 $off w 2>/dev/null | grep Value; done",
    "echo === GPIO bank3 lvl/oen:; for off in 0x944070C0 0x944070C4 0x944070C8 0x944070CC 0x944070D0 0x944070D4 0x944070D8 0x944070DC 0x944070E0 0x944070E4 0x944070E8; do printf '%s = ' $off; devmem2 $off w 2>/dev/null | grep Value; done",
]

def run():
    cli = paramiko.SSHClient()
    cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    cli.connect(HOST, username=USER, password=PASS,
                allow_agent=False, look_for_keys=False, timeout=10)
    sh = cli.invoke_shell(width=240, height=50)
    out = bytearray()
    def drain(t=0.5):
        time.sleep(t)
        while sh.recv_ready():
            out.extend(sh.recv(65536)); time.sleep(0.05)
    drain(1.0); out.clear()
    for c in CMDS:
        sh.send(c + f"; echo {SENTINEL}\n")
        deadline = time.time() + 30
        while time.time() < deadline:
            if sh.recv_ready():
                out.extend(sh.recv(65536))
                if SENTINEL.encode() in out: break
            time.sleep(0.05)
        out.extend(b"\n----\n")
    sh.close(); cli.close()
    text = bytes(out).decode("utf-8", "replace")
    open("/tmp/stock_mt7915_recon.txt","w").write(text)
    print(text)

if __name__ == "__main__": run()
