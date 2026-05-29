#!/usr/bin/env python3
"""READ-ONLY dump of the SPA source-port match-RAM (ram_id 0) and hash-RAM
(ram_id 5) from factory-stock ZTE H3600 via the indirect-RAM READ protocol.

Protocol derived from decomp_all_tm.c:
  spa_set_indirect_rw_cmd (tm:25957):
      cmd = ram_addr | (ram_id<<22) | (ind_rw_en<<27)
      -> tmOnuRegWrite(reg4, ..., spaRegTable); reg4 base 0x75005 = phys 0x921d4014
  spa_get_indirect_rw_status (tm:25971): reg5 base 0x75006 = phys 0x921d4018.
      "access done" when value NONZERO (decomp loops while local==0).
  spa_get_indirect_rw_data (tm:26090): reg6 base 0x75007 stride1, idx 0..5
      = phys 0x921d401c..0x921d4030 (6 data words).
  spa_get_matchram (tm:28402): poll done, cmd READ (ind=1,ram=0,addr), poll done,
      read data_id 5..0 (6 words).  ram_addr range 0..7 (4 rules packed per row).
  spa_get_hashram (tm:28585): poll done, cmd READ (ind=1,ram=5,addr), poll done,
      read data_id 1 then 0 (2 words).  ram_addr 0..7.

The ONLY hardware WRITE issued is the CMD read-command to id 0x75005 with
ind_rw_en=1 (READ semantics). Data ports are only READ. No datapath registers
touched. No NAND. reads via /bin/fpga land in /proc/kmsg.
"""
import paramiko, time, re, sys

HOST, USER, PW = "192.168.1.1", "admin", "UkuGPeyRDU"

CMD_ID  = 0x75005   # phys 0x921d4014
DONE_ID = 0x75006   # phys 0x921d4018
DATA_ID = 0x75007   # phys 0x921d401c .. (+idx)

def rd_cmd(ind, ram, addr):
    return (addr & 0x3fffff) | (ram << 22) | (ind << 27)

class Sh:
    def __init__(self):
        self.cli = paramiko.SSHClient()
        self.cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.cli.connect(HOST, username=USER, password=PW, timeout=20,
                         allow_agent=False, look_for_keys=False,
                         banner_timeout=30, auth_timeout=30)
        self.ch = self.cli.invoke_shell(width=240, height=4000)
        time.sleep(1.0); self._d(0.6)
    def _d(self, s):
        out = ''; t = time.time()
        while time.time() - t < s:
            if self.ch.recv_ready():
                out += self.ch.recv(65536).decode(errors='replace'); t = time.time()
            else:
                time.sleep(0.04)
        return out
    def send(self, c): self.ch.send(c + '\n')
    def close(self):
        try: self.ch.close()
        except Exception: pass
        self.cli.close()

def burst(sh, lines):
    """Run a sequence of /bin/fpga ops inside one persistent kmsg window.
    `lines` is a list of shell fragments (reads/writes). Returns ordered list
    of (regidx, value) parsed from the kernel ring, in issue order."""
    inner = "; ".join(lines)
    sh.send("killall cat 2>/dev/null; rm -f /tmp/k.txt; cat /proc/kmsg > /tmp/k.txt &")
    sh._d(0.6); time.sleep(1.0)
    sh.send("/bin/fpga -r 0x%x 1" % DONE_ID)   # throwaway (first read often dropped)
    sh._d(0.3); time.sleep(0.3)
    sh.send(inner); sh._d(0.6); time.sleep(0.6)
    sh.send("kill %1 2>/dev/null; killall cat 2>/dev/null"); sh._d(0.3)
    sh.send("cat /tmp/k.txt"); out = sh._d(2.0)
    hits = [(int(m.group(1), 16), int(m.group(2), 16)) for m in
            re.finditer(r"reg=0x0*([0-9a-fA-F]+),\s*value=0x([0-9a-fA-F]+)", out)]
    # drop leading throwaway DONE read
    if hits and hits[0][0] == DONE_ID:
        hits = hits[1:]
    return hits, out

def dump_match_row(sh, row):
    """Issue READ cmd for matchram row, then read 6 data words. ind_rw_en=1."""
    c = rd_cmd(1, 0, row)
    lines = [
        "/bin/fpga -r 0x%x 1" % DONE_ID,          # status before
        "/bin/fpga -w 0x%x 0x%x" % (CMD_ID, c),   # READ command (ONLY write)
        "/bin/fpga -r 0x%x 1" % DONE_ID,          # status after
    ]
    for i in range(6):
        lines.append("/bin/fpga -r 0x%x 1" % (DATA_ID + i))
    lines.append("/bin/fpga -r 0x%x 1" % DONE_ID)
    hits, out = burst(sh, lines)
    data = {}
    for reg, val in hits:
        if DATA_ID <= reg <= DATA_ID + 5:
            data[reg - DATA_ID] = val
    words = [data.get(i) for i in range(6)]
    return c, words, out

def dump_hash_row(sh, row):
    """Issue READ cmd for hashram row (ram_id 5), read data_id 1 then 0."""
    c = rd_cmd(1, 5, row)
    lines = [
        "/bin/fpga -r 0x%x 1" % DONE_ID,
        "/bin/fpga -w 0x%x 0x%x" % (CMD_ID, c),
        "/bin/fpga -r 0x%x 1" % DONE_ID,
        "/bin/fpga -r 0x%x 1" % (DATA_ID + 1),   # data_id 1
        "/bin/fpga -r 0x%x 1" % (DATA_ID + 0),   # data_id 0
        "/bin/fpga -r 0x%x 1" % DONE_ID,
    ]
    hits, out = burst(sh, lines)
    data = {}
    for reg, val in hits:
        if reg == DATA_ID + 1: data[1] = val
        if reg == DATA_ID + 0: data[0] = val
    return c, [data.get(0), data.get(1)], out

def main():
    sh = Sh()
    print("CONNECTED stock", flush=True)
    # confirm idle / done state and capture leftover cmd
    h, _ = burst(sh, ["/bin/fpga -r 0x%x 1" % CMD_ID, "/bin/fpga -r 0x%x 1" % DONE_ID,
                       "/bin/fpga -r 0x7501f 1"])
    print("PRE: %s" % (["0x%05x=0x%08x" % (r, v) for r, v in h]), flush=True)

    print("\n===== MATCH-RAM (ram_id 0), rows 0..7, 6 words each =====", flush=True)
    match = {}
    for row in range(8):
        c, words, _ = dump_match_row(sh, row)
        match[row] = words
        ws = " ".join("--------" if w is None else "%08x" % w for w in words)
        print("row%d cmd=0x%08x  data[0..5]= %s" % (row, c, ws), flush=True)

    print("\n===== HASH-RAM (ram_id 5), rows 0..7, 2 words each =====", flush=True)
    hashr = {}
    for row in range(8):
        c, words, _ = dump_hash_row(sh, row)
        hashr[row] = words
        ws = " ".join("--------" if w is None else "%08x" % w for w in words)
        print("row%d cmd=0x%08x  data[0,1]= %s" % (row, c, ws), flush=True)

    # restore-free: leave cmd as-is (a READ command is harmless). Re-read final state.
    h2, _ = burst(sh, ["/bin/fpga -r 0x%x 1" % CMD_ID, "/bin/fpga -r 0x%x 1" % DONE_ID,
                       "/bin/fpga -r 0x7501f 1", "/bin/fpga -r 0x75048 1",
                       "/bin/fpga -r 0x75049 1"])
    print("\nPOST: %s" % (["0x%05x=0x%08x" % (r, v) for r, v in h2]), flush=True)
    sh.close()
    print("DONE", flush=True)

if __name__ == "__main__":
    main()
