#!/usr/bin/env python3
"""Empirical CPU->LAN egress netdev identification + BMU/QMG reg diff (v2).

Reads only. SSH (paramiko invoke_shell) to live factory stock.
- Per-netdev tx_packets BEFORE/AFTER host `ping 192.168.1.1` -> which egresses.
- BMU/QMG regs IDLE vs DURING egress via per-register /proc/kmsg capture
  (one dedicated window per reg, retry-until-seen -- the proven reliable
  pattern from the DN-ring oracle).
"""
import paramiko, subprocess, time, re

HOST = "192.168.1.1"; USER = "admin"; PW = "UkuGPeyRDU"

BMU_QMG_REGS = [
    (0x921c8000, 0x72000, "BMU 0x921c8000"),
    (0x921c8004, 0x72001, "BMU 0x921c8004"),
    (0x921c8008, 0x72002, "BMU 0x921c8008"),
    (0x921c800c, 0x72003, "BMU 0x921c800c bp_idx"),
    (0x921c8010, 0x72004, "BMU 0x921c8010 free"),
    (0x921c8014, 0x72005, "BMU 0x921c8014 alloc"),
    (0x921c8018, 0x72006, "BMU 0x921c8018"),
    (0x921c801c, 0x72007, "BMU 0x921c801c"),
    (0x9234c040, 0xd3010, "QMG 0x9234c040"),
    (0x9234c044, 0xd3011, "QMG 0x9234c044 swfwd"),
    (0x9234c048, 0xd3012, "QMG 0x9234c048"),
    (0x9234c04c, 0xd3013, "QMG 0x9234c04c"),
]
# confirm-egress witnesses
MAC2_TXOK = (0x92280718, 0xa01c6, "MAC2 0x92280718 TX-OK")


class Shell:
    def __init__(self):
        self.cli = paramiko.SSHClient()
        self.cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.cli.connect(HOST, username=USER, password=PW, timeout=20,
                         allow_agent=False, look_for_keys=False,
                         banner_timeout=30, auth_timeout=30)
        self.chan = self.cli.invoke_shell(width=240, height=4000)
        time.sleep(1.0); self._drain()

    def _drain(self):
        t = time.time()
        while time.time() - t < 0.5:
            if self.chan.recv_ready():
                self.chan.recv(65536); t = time.time()
            else:
                time.sleep(0.04)

    def run(self, cmd, settle=1.5):
        mk = "MK%dZ" % (int(time.time() * 1000) % 1000000)
        self.chan.send(cmd + " ; echo " + mk + "\n")
        out = ""; deadline = time.time() + settle + 12
        while time.time() < deadline:
            if self.chan.recv_ready():
                out += self.chan.recv(65536).decode(errors="replace")
                # the marker appears twice: in the command echo and in output.
                if out.count(mk) >= 2:
                    break
            else:
                time.sleep(0.04)
        # return the slice AFTER the echoed command line (2nd marker region)
        return out

    def close(self):
        try: self.chan.close()
        except Exception: pass
        self.cli.close()


def read_one_reg(sh, widx, retries=4):
    """Read ONE reg via fpga -r in a dedicated kmsg window. Returns int or None."""
    for _ in range(retries):
        sh.run("(cat /proc/kmsg > /tmp/kr.txt 2>/dev/null &)", settle=0.4)
        time.sleep(0.5)
        sh.run("/bin/fpga -r 0x%x 1" % widx, settle=0.4)
        time.sleep(0.7)
        out = sh.run("cat /tmp/kr.txt", settle=0.8)
        sh.run("kill $(pidof cat) 2>/dev/null; rm -f /tmp/kr.txt", settle=0.4)
        m = None
        for mm in re.finditer(r"reg=0x0*%x,\s*value=0x([0-9a-fA-F]+)" % widx, out):
            m = mm
        if m:
            return int(m.group(1), 16)
    return None


def read_regs(sh, regs):
    vals = {}
    for phys, widx, lbl in regs:
        vals[phys] = read_one_reg(sh, widx)
    return vals


def read_netdev(sh):
    out = sh.run("for d in /sys/class/net/*; do "
                 "echo NDV $(basename $d) $(cat $d/statistics/tx_packets) "
                 "$(cat $d/statistics/rx_packets); done", settle=2.0)
    res = {}
    for line in out.splitlines():
        m = re.match(r"\s*NDV\s+(\S+)\s+(\d+)\s+(\d+)\s*$", line)
        if m:
            res[m.group(1)] = (int(m.group(2)), int(m.group(3)))
    return res


def host_ping(count, interval=0.15):
    p = subprocess.run(["ping", "-c", str(count), "-i", str(interval), "-W", "1", HOST],
                       capture_output=True, text=True)
    m = re.search(r"(\d+) packets transmitted, (\d+) (?:packets )?received", p.stdout)
    return (int(m.group(1)), int(m.group(2))) if m else (0, 0)


def main():
    sh = Shell()
    print("CONNECTED.", flush=True)
    print("UNAME:", sh.run("uname -a", 1.0).strip().splitlines()[-2:], flush=True)

    # topology
    print("\n@@IP_ADDR@@\n" + sh.run("ip -o addr 2>/dev/null", 2.0), flush=True)
    print("\n@@BRCTL@@\n" + sh.run("brctl show 2>/dev/null", 2.0), flush=True)

    # ===== RUN A: ping -c 50 (netdev delta) =====
    print("\n===== RUN A netdev: ping -c 50 =====", flush=True)
    before = read_netdev(sh)
    txa, rxa = host_ping(50)
    print("host ping50: tx=%d rx=%d" % (txa, rxa), flush=True)
    time.sleep(0.6)
    after = read_netdev(sh)
    print_netdev_delta("RUN A (ping50)", before, after, txa)

    # ===== RUN B: ping -c 100 (netdev delta, confirm) =====
    print("\n===== RUN B netdev: ping -c 100 =====", flush=True)
    before2 = read_netdev(sh)
    txb, rxb = host_ping(100)
    print("host ping100: tx=%d rx=%d" % (txb, rxb), flush=True)
    time.sleep(0.6)
    after2 = read_netdev(sh)
    print_netdev_delta("RUN B (ping100)", before2, after2, txb)

    # ===== IDLE reg snapshot =====
    print("\n===== IDLE BMU/QMG/MAC2 regs =====", flush=True)
    idle = read_regs(sh, BMU_QMG_REGS + [MAC2_TXOK])
    for phys, widx, lbl in BMU_QMG_REGS + [MAC2_TXOK]:
        v = idle.get(phys)
        print("  IDLE %-26s = %s" % (lbl, "0x%08x" % v if v is not None else "MISS"), flush=True)

    # ===== DURING egress reg snapshot (sustained host flood) =====
    print("\n===== DURING-EGRESS regs (sustained host ping flood) =====", flush=True)
    flood = subprocess.Popen(["ping", "-c", "400", "-i", "0.08", "-W", "1", HOST],
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    time.sleep(1.5)
    during = read_regs(sh, BMU_QMG_REGS + [MAC2_TXOK])
    try:
        fo, _ = flood.communicate(timeout=60)
    except Exception:
        flood.kill(); fo = ""
    m = re.search(r"(\d+) packets transmitted, (\d+) (?:packets )?received", fo)
    fc = (int(m.group(1)), int(m.group(2))) if m else (0, 0)
    print("flood: tx=%d rx=%d" % fc, flush=True)

    print("\n===== REG DIFF: IDLE -> DURING =====", flush=True)
    for phys, widx, lbl in BMU_QMG_REGS + [MAC2_TXOK]:
        b = idle.get(phys); a = during.get(phys)
        if b is None or a is None:
            print("  %-26s %s -> %s  (incomplete)" % (
                lbl, "0x%08x" % b if b is not None else "MISS",
                "0x%08x" % a if a is not None else "MISS"), flush=True)
            continue
        d = (a - b) & 0xffffffff
        sd = d if d < 0x80000000 else d - 0x100000000
        flag = "  <== CHANGED (d=%+d)" % sd if a != b else "  (flat)"
        print("  %-26s 0x%08x -> 0x%08x%s" % (lbl, b, a, flag), flush=True)

    sh.close()


def print_netdev_delta(label, before, after, tx):
    print("--- %s netdev tx deltas (host tx=%d) ---" % (label, tx), flush=True)
    for ifn in sorted(set(before) | set(after)):
        b = before.get(ifn, (0, 0)); a = after.get(ifn, (0, 0))
        dtx = a[0] - b[0]; drx = a[1] - b[1]
        if dtx == 0 and drx == 0:
            continue  # only show movers
        flag = ""
        if tx and abs(dtx - tx) <= max(8, tx // 5):
            flag = "  <== MATCHES host tx (%d)" % tx
        print("  %-10s tx %7d->%7d dtx=%+5d  rx dxx=%+5d%s" % (
            ifn, b[0], a[0], dtx, drx, flag), flush=True)


if __name__ == "__main__":
    main()
