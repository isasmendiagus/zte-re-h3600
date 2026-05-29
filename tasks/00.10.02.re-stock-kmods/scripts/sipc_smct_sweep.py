#!/usr/bin/env python3
"""SIPC + SMCT-control window sweep (reads only), CORRECTED /proc/kmsg method.

Goal: find the ring-less CPU->LAN inject doorbell/counter. Stock egress uses NO
DMA ring (UP/DN/IDM all 0) yet QMG sw_fwd (0x9234c044) and MAC2 TX-OK
(0x92280718) climb. Prior RE localized the ring-less inject to the SIPC bridge
(0x921cc000) / SMCT CPU-port channel (0x921d0000) windows, which no oracle has
read during egress (we only ever read +0x54/+0x64 ring kicks inside SMCT).

Sweep these BEFORE (idle) and DURING a host ping flood; report deltas. The
reg(s) that tick in lock-step with sw_fwd / MAC2 TX-OK = the inject.

CORRECTED method (per task / prior agent):
  - ONE persistent `cat /proc/kmsg` per snapshot.
  - ~1.2s warmup after starting the cat.
  - a THROWAWAY first /bin/fpga read (it gets dropped by the ring).
  - read each reg TWICE in the same snapshot (DOUBLE-READ everything here, so we
    can tell a live-incrementing counter from a stable value AND detect dropped
    reads); keep the LAST value.
  - NO short-lived per-reg cats, NO backgrounded (&) subshells around fpga.

fpga read: `/bin/fpga -r <wordidx> 1`, wordidx=(phys-0x92000000)/4.
"""
import paramiko, subprocess, time, re, sys

HOST="192.168.1.1"; USER="admin"; PW="UkuGPeyRDU"

def widx(phys): return (phys-0x92000000)//4

# (phys, wordidx, label, is_key)  -- ALL regs double-read here (key=True)
REGS = []
# SIPC bridge window: 0x921cc000 .. 0x921cc03c (16 regs)
for off in range(0, 0x40, 4):
    p = 0x921cc000 + off
    REGS.append((p, widx(p), "SIPC+0x%02x"%off, True))
# SMCT-control window: 0x921d0000 .. 0x921d004c, SKIP 0x54/0x64 (known ring kicks)
for off in range(0, 0x50, 4):
    p = 0x921d0000 + off
    REGS.append((p, widx(p), "SMCT+0x%02x"%off, True))
# (0x54 and 0x64 are outside this 0x00..0x4c range already, so nothing to skip,
#  but be explicit: do NOT read 0x921d0054 / 0x921d0064.)
# Controls (must climb, proves egress live)
REGS.append((0x9234c044, widx(0x9234c044), "QMG sw_fwd", True))
REGS.append((0x92280718, widx(0x92280718), "MAC2 TX-OK", True))

THROWAWAY_WIDX = widx(0x9234c044)  # 0xd3011

class Sh:
    def __init__(self):
        self.cli=paramiko.SSHClient(); self.cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.cli.connect(HOST,username=USER,password=PW,timeout=20,allow_agent=False,
                         look_for_keys=False,banner_timeout=30,auth_timeout=30)
        self.ch=self.cli.invoke_shell(width=240,height=8000); time.sleep(1.0); self._d(0.6)
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

def snapshot(sh):
    """One persistent cat window. Returns dict phys -> list-of-values-seen
    (read order). Every reg read twice; first read may be the dropped one, so
    keep the full list and pick the LAST value."""
    seq=[]
    for phys,wx,_,key in REGS:
        seq.append((phys,wx)); seq.append((phys,wx))   # double-read everything
    vals={phys:[] for phys,_,_,_ in REGS}
    out=""
    for attempt in range(3):
        sh.send('killall cat 2>/dev/null; rm -f /tmp/k.txt; cat /proc/kmsg > /tmp/k.txt &')
        sh._d(0.8); time.sleep(1.2)                    # warmup
        sh.send('/bin/fpga -r 0x%x 1'%THROWAWAY_WIDX); sh._d(0.4); time.sleep(0.5)  # THROWAWAY
        for phys,wx in seq:
            sh.send('/bin/fpga -r 0x%x 1'%wx); sh._d(0.18)
        time.sleep(1.2)
        sh.send('kill %1 2>/dev/null; killall cat 2>/dev/null'); sh._d(0.4)
        sh.send('cat /tmp/k.txt'); out=sh._d(3.0)
        hits=[(int(m.group(1),16),int(m.group(2),16)) for m in
              re.finditer(r"reg=0x0*([0-9a-fA-F]+),\s*value=0x([0-9a-fA-F]+)",out)]
        # drop the single throwaway sw_fwd read at the front if present
        if hits and hits[0][0]==THROWAWAY_WIDX:
            hits=hits[1:]
        tmp={phys:[] for phys,_,_,_ in REGS}
        hi=0
        for (phys,wx) in seq:
            while hi<len(hits) and hits[hi][0]!=wx:
                hi+=1
            if hi<len(hits):
                tmp[phys].append(hits[hi][1]); hi+=1
        if all(len(tmp[p])>=1 for p,_,_,_ in REGS):
            return tmp, out
        vals=tmp
    return vals, out

def pick(vlist):
    return vlist[-1] if vlist else None

def print_snap(tag, snap):
    print("\n##### %s #####"%tag, flush=True)
    for phys,wx,lbl,key in REGS:
        vl=snap[phys]
        shown="0x%08x"%pick(vl) if vl else "MISS"
        raw="  raw=[%s]"%(",".join("0x%x"%x for x in vl)) if len(vl)>1 else ("  raw=[%s]"%(",".join("0x%x"%x for x in vl)) if vl else "")
        print("  0x%08x %-12s (0x%05x) = %s%s"%(phys,lbl,wx,shown,raw), flush=True)

def run(sh, count):
    print("\n================ RUN ping -c %d ================"%count, flush=True)
    before,rb=snapshot(sh)
    print_snap("BEFORE (idle)", before)
    fl=subprocess.Popen(["ping","-c",str(count),"-i","0.05","-W","1",HOST],
                        stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
    time.sleep(1.2)
    during,rd=snapshot(sh)
    try: fo,_=fl.communicate(timeout=120)
    except Exception: fl.kill(); fo=""
    m=re.search(r"(\d+) packets transmitted, (\d+) (?:packets )?received",fo)
    print("\nflood: %s"%(m.group(0) if m else "?"), flush=True)
    print_snap("DURING (flood)", during)
    print("\n----- DELTA (run -c %d) -----"%count, flush=True)
    res={}
    for phys,wx,lbl,key in REGS:
        b=pick(before[phys]); a=pick(during[phys])
        if b is None or a is None:
            print("  0x%08x %-12s incomplete (b=%s a=%s)"%(phys,lbl,b,a)); res[lbl]=(b,a,None); continue
        d=(a-b)&0xffffffff; sd=d if d<0x80000000 else d-0x100000000
        tag="  <== CHANGED d=%+d"%sd if a!=b else "  (flat)"
        print("  0x%08x %-12s 0x%08x -> 0x%08x%s"%(phys,lbl,b,a,tag), flush=True)
        res[lbl]=(b,a,sd)
    return res, rd

def main():
    sh=Sh(); print("CONNECTED to stock", flush=True)
    r1,raw1=run(sh,100)
    r2,raw2=run(sh,200)
    print("\n===== RAW kmsg (run2 DURING) fpga lines =====", flush=True)
    for ln in raw2.splitlines():
        if "fpga read" in ln: print("  "+ln.strip(), flush=True)
    sh.close()
    print("\nDONE", flush=True)

if __name__=="__main__": main()
