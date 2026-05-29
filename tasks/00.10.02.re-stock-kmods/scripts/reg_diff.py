#!/usr/bin/env python3
"""BMU/QMG/MAC2 reg diff: IDLE vs DURING host-ping egress (reads only).

Uses the proven per-register /proc/kmsg capture: one dedicated window per
reg (plain `cat /proc/kmsg > /tmp/k.txt &`, fixed sleeps, `kill %1`),
retry-until-the-line-appears. Matches the DN-ring oracle's reliable method.
"""
import paramiko, subprocess, time, re

HOST="192.168.1.1"; USER="admin"; PW="UkuGPeyRDU"

REGS = [
    (0x921c8000,0x72000,"BMU 0x921c8000"),
    (0x921c8004,0x72001,"BMU 0x921c8004"),
    (0x921c8008,0x72002,"BMU 0x921c8008"),
    (0x921c800c,0x72003,"BMU 0x921c800c bp_idx"),
    (0x921c8010,0x72004,"BMU 0x921c8010 free"),
    (0x921c8014,0x72005,"BMU 0x921c8014 alloc"),
    (0x921c8018,0x72006,"BMU 0x921c8018"),
    (0x921c801c,0x72007,"BMU 0x921c801c"),
    (0x9234c040,0xd3010,"QMG 0x9234c040"),
    (0x9234c044,0xd3011,"QMG 0x9234c044 swfwd"),
    (0x9234c048,0xd3012,"QMG 0x9234c048"),
    (0x9234c04c,0xd3013,"QMG 0x9234c04c"),
    (0x92280718,0xa01c6,"MAC2 0x92280718 TX-OK"),
]

class Sh:
    def __init__(self):
        self.cli=paramiko.SSHClient(); self.cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.cli.connect(HOST,username=USER,password=PW,timeout=20,allow_agent=False,
                         look_for_keys=False,banner_timeout=30,auth_timeout=30)
        self.ch=self.cli.invoke_shell(width=240,height=4000); time.sleep(1.0); self._d(0.5)
    def _d(self,s):
        out=''; t=time.time()
        while time.time()-t<s:
            if self.ch.recv_ready(): out+=self.ch.recv(65536).decode(errors='replace'); t=time.time()
            else: time.sleep(0.04)
        return out
    def send(self,cmd): self.ch.send(cmd+'\n')
    def close(self):
        try: self.ch.close()
        except Exception: pass
        self.cli.close()

def read_all(sh, attempt_tag=""):
    """ONE persistent `cat /proc/kmsg` window; warm it up with a throwaway
    read (the first read after cat-start is unreliable), then read every reg
    into the same file, dump once. Retry any reg that missed in a second pass."""
    vals = {phys: None for phys, _, _ in REGS}
    for attempt in range(3):
        sh.send('killall cat 2>/dev/null; rm -f /tmp/k.txt; cat /proc/kmsg > /tmp/k.txt &')
        sh._d(0.8); time.sleep(1.2)
        # warmup throwaway read (the cat needs ~1s to actually attach to kmsg)
        sh.send('/bin/fpga -r 0xd3011 1'); sh._d(0.4); time.sleep(0.4)
        missing = [(p, w) for p, w, _ in REGS if vals[p] is None]
        for phys, widx in missing:
            sh.send('/bin/fpga -r 0x%x 1' % widx); sh._d(0.35)
        time.sleep(1.2)
        sh.send('kill %1 2>/dev/null; killall cat 2>/dev/null'); sh._d(0.4)
        sh.send('cat /tmp/k.txt'); out = sh._d(2.0)
        for phys, widx, _ in REGS:
            mm = [int(m.group(1), 16) for m in
                  re.finditer(r"reg=0x0*%x,\s*value=0x([0-9a-fA-F]+)" % widx, out)]
            if mm:
                vals[phys] = mm[-1]
        if all(v is not None for v in vals.values()):
            break
    return vals

def main():
    sh=Sh(); print("CONNECTED",flush=True)
    print("\n##### IDLE snapshot #####",flush=True)
    idle=read_all(sh)
    for phys,widx,lbl in REGS:
        v=idle[phys]; print("  IDLE %-26s = %s"%(lbl,"0x%08x"%v if v is not None else "MISS"),flush=True)

    print("\n##### DURING-EGRESS (host ping -c 600 -i 0.05 flood) #####",flush=True)
    fl=subprocess.Popen(["ping","-c","600","-i","0.05","-W","1",HOST],
                        stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    time.sleep(1.5)
    during=read_all(sh)
    try: fo,_=fl.communicate(timeout=90)
    except Exception: fl.kill(); fo=""
    m=re.search(r"(\d+) packets transmitted, (\d+) (?:packets )?received",fo)
    print("flood: %s"%(m.group(0) if m else "?"),flush=True)

    print("\n##### REG DIFF IDLE -> DURING #####",flush=True)
    for phys,widx,lbl in REGS:
        b=idle[phys]; a=during[phys]
        if b is None or a is None:
            print("  %-26s %s -> %s (incomplete)"%(lbl,
                  "0x%08x"%b if b is not None else "MISS",
                  "0x%08x"%a if a is not None else "MISS"),flush=True); continue
        d=(a-b)&0xffffffff; sd=d if d<0x80000000 else d-0x100000000
        tag="  <== CHANGED d=%+d"%sd if a!=b else "  (flat)"
        print("  %-26s 0x%08x -> 0x%08x%s"%(lbl,b,a,tag),flush=True)
    sh.close()

if __name__=="__main__": main()
