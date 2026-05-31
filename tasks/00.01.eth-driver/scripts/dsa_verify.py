#!/usr/bin/env python3
"""DSA per-port-op HW verification harness for the ZX279128S switch.

RUN AFTER the P1 conduit refactor makes zx-dsa probe (lan0..3 netdevs appear).
See tasks/00.01.eth-driver/findings/dsa_conduit_refactor_guide.md. Until then the
driver does not probe and this script's bridge/ip steps are no-ops.

It drives the C-init REPL over the UART bridge (:9999) and uses the debugfs
`memdump`/`poke` + standard `ip`/`bridge` to exercise each spec-backed op and
read the underlying register back, confirming the encoding the driver writes
matches the RE'd spec (memory zte-dsa-foundation). Cable on jack 3 = MAC2 = port 2.

Register refs (phys): isolation 0x923883c0 + regport*4 (regport remap
{0:1,1:2,2:3,3:4,4:5,5:0}); STP greg 0x921c0044 (3b/port, shift port*3);
port_closed 0x921c004c (1b/port); SBRAG CMD 0x92388014 / BUSY 18 / D0 1c D1 20 D2 24.
NOTE: do NOT use nested double-quotes in sh -c over the REPL (wedges it).
"""
import socket
import time
import re
import sys

BRIDGE = ("127.0.0.1", 9999)
REGPORT = [1, 2, 3, 4, 5, 0, 6, 7]   # logical -> regport (isolation/greg bit space)


class Repl:
    def __init__(self):
        self.s = socket.create_connection(BRIDGE, timeout=10)
        self.s.settimeout(0.4)
        self._drain(0.5)

    def _drain(self, t):
        b = b""
        end = time.time() + t
        while time.time() < end:
            try:
                d = self.s.recv(65536)
            except socket.timeout:
                d = b""
            if d:
                b += d
                end = time.time() + t
            else:
                time.sleep(0.03)
        return b.decode(errors="replace")

    def cmd(self, line, t=0.5):
        self.s.sendall(line.encode() + b"\n")
        return self._drain(t)

    def rd(self, phys):
        o = self.cmd("memdump %x 4" % phys, 0.4)
        m = re.findall(r"\b([0-9a-fA-F]{8})\b", o)
        return int(m[-1], 16) if m else None

    def close(self):
        self.s.close()


def check(name, got, want, mask=0xffffffff):
    ok = got is not None and (got & mask) == (want & mask)
    print("  [%s] %-28s got=0x%08x want=0x%08x mask=0x%x"
          % ("OK" if ok else "??", name, got or 0, want, mask))
    return ok


def main():
    r = Repl()
    print("=== DSA HW verification (run after P1 makes the driver probe) ===")

    # 1) Do the lanN netdevs exist? (proves DSA registered)
    o = r.cmd("sh -c 'ls /sys/class/net | tr \"\\n\" \" \"'", 1.0)
    print("netdevs:", o.strip().splitlines()[-1] if o.strip() else "(none)")
    has_dsa = "lan2" in o
    print("DSA probed (lan2 present):", has_dsa)

    # 2) port_enable readback: port_closed bit(regport[2]) should be 0 after up.
    if has_dsa:
        r.cmd("sh -c 'ip link set lan2 up'", 0.8)
        time.sleep(0.5)
    v = r.rd(0x921c004c)
    check("port_closed lan2 open", v or 0, 0, 1 << REGPORT[2])

    # 3) STP forwarding readback: greg 0x921c0044, 3b at shift port*3, want 4 (fwd).
    v = r.rd(0x921c0044)
    if v is not None:
        field = (v >> (2 * 3)) & 0x7   # port 2
        print("  [%s] %-28s field=%d want=4(fwd)"
              % ("OK" if field == 4 else "??", "STP lan2 state", field))

    # 4) FDB add + readback: add a static MAC on lan2, read the SBRAG slot.
    #    (bridge fdb add ... dev lan2) then memdump the hashed slot D0/D1/D2.
    if has_dsa:
        r.cmd("sh -c 'bridge fdb add 02:00:00:00:00:22 dev lan2 static'", 0.8)
        # read D0/D1/D2 after a prefetch would require driving the indirect read;
        # simplest: trust the driver's add + check drop counters / dmesg. TODO.
        print("  [..] FDB add issued; verify via dmesg / indirect read (TODO)")

    # 5) isolation readback: standalone lan2 should allow only CPU (regport0/bit0).
    v = r.rd(0x923883c0 + REGPORT[2] * 4)
    if v is not None:
        print("  [..] isolation slot lan2 = 0x%02x (expect CPU-only allow: bit0 set)"
              % (v & 0xff))

    # 6) ping (the real end-to-end check once egress works through the tag path)
    print("\nRun on the HOST:  ping -c5 192.168.1.99   (expect 0% loss on lan2)")
    r.close()
    print("=== done ===")


if __name__ == "__main__":
    sys.exit(main())
