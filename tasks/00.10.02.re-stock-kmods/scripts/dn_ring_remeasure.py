#!/usr/bin/env python3
"""DN-ring RE-MEASURE (reads only) with the CORRECTED /proc/kmsg method.

Resolves the contradiction: decomp says sw egress kicks the TM DN ring
(TM[0x10064]) and bumps consume TM[0x10068], but an earlier oracle measured
0x10068=0 using a method that had a first-read-drop bug.

CORRECTED method (per task):
  - ONE persistent `cat /proc/kmsg` per snapshot.
  - ~1.2s warmup after starting the cat.
  - a THROWAWAY first /bin/fpga read (it gets dropped).
  - THEN read the real registers.
  - read each KEY reg TWICE in the same snapshot so we SEE the first-read-drop
    and discard the (possibly dropped) first one, keeping the LAST value.
  - NO short-lived per-reg cats, NO backgrounded (&) subshells around fpga.

fpga read: `/bin/fpga -r <wordidx> 1`, wordidx=(phys-0x92000000)/4. Output lands
in the kernel ring (parsed `fpga read: reg=0x..., value=0x...`). reads only.
"""
import paramiko, subprocess, time, re, sys

HOST="192.168.1.1"; USER="admin"; PW="UkuGPeyRDU"

# (phys, wordidx, label, is_key)  -- key regs are read TWICE per snapshot
REGS = [
    (0x921d0068, 0x7401a, "TM DN consume", True),   # THE KEY ONE
    (0x921d006c, 0x7401b, "TM DN cursor",  True),
    (0x921d0064, 0x74019, "TM DN kick",    True),   # write-1 doorbell, likely 0
    (0x921d0058, 0x74016, "TM UP consume", False),  # control
    (0x921d005c, 0x74017, "TM UP cursor",  False),  # control
    (0x9234c044, 0xd3011, "QMG sw_fwd",    False),  # egress confirm (must climb)
    (0x92280718, 0xa01c6, "MAC2 TX-OK",    False),  # egress confirm (must climb)
]

class Sh:
    def __init__(self):
        self.cli=paramiko.SSHClient(); self.cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.cli.connect(HOST,username=USER,password=PW,timeout=20,allow_agent=False,
                         look_for_keys=False,banner_timeout=30,auth_timeout=30)
        self.ch=self.cli.invoke_shell(width=240,height=4000); time.sleep(1.0); self._d(0.6)
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
    (in read order). Key regs read twice; first read may be the dropped one,
    so we keep the full list and the caller picks the LAST value."""
    seq=[]   # ordered (phys,widx) reads we will issue this snapshot
    for phys,widx,_,key in REGS:
        seq.append((phys,widx))
        if key:
            seq.append((phys,widx))   # second read of key regs (see the drop)
    vals={phys:[] for phys,_,_,_ in REGS}
    for attempt in range(3):
        sh.send('killall cat 2>/dev/null; rm -f /tmp/k.txt; cat /proc/kmsg > /tmp/k.txt &')
        sh._d(0.8); time.sleep(1.2)                    # warmup: cat needs ~1s to attach
        sh.send('/bin/fpga -r 0xd3011 1'); sh._d(0.4); time.sleep(0.5)   # THROWAWAY first read
        for phys,widx in seq:
            sh.send('/bin/fpga -r 0x%x 1'%widx); sh._d(0.30)
        time.sleep(1.2)
        sh.send('kill %1 2>/dev/null; killall cat 2>/dev/null'); sh._d(0.4)
        sh.send('cat /tmp/k.txt'); out=sh._d(2.2)
        # parse ALL value lines in order; the throwaway 0xd3011 read is the very
        # first match -> drop exactly one leading sw_fwd hit, then map in order.
        hits=[(int(m.group(1),16),int(m.group(2),16)) for m in
              re.finditer(r"reg=0x0*([0-9a-fA-F]+),\s*value=0x([0-9a-fA-F]+)",out)]
        # drop the single throwaway sw_fwd read at the front if present
        if hits and hits[0][0]==0xd3011:
            hits=hits[1:]
        # now consume hits against our expected seq in order
        tmp={phys:[] for phys,_,_,_ in REGS}
        hi=0
        for (phys,widx) in seq:
            # find the next hit matching this widx
            while hi<len(hits) and hits[hi][0]!=widx:
                hi+=1
            if hi<len(hits):
                tmp[phys].append(hits[hi][1]); hi+=1
        # complete if every reg has at least one captured value
        if all(len(tmp[p])>=1 for p,_,_,_ in REGS):
            vals=tmp
            return vals, out
        vals=tmp
    return vals, out

def pick(vlist):
    """Discard the (possibly dropped) first read; keep the LAST value seen."""
    return vlist[-1] if vlist else None

def print_snap(tag, snap):
    print("\n##### %s #####"%tag, flush=True)
    for phys,widx,lbl,key in REGS:
        vl=snap[phys]
        shown="0x%08x"%pick(vl) if vl else "MISS"
        raw="  raw=[%s]"%(",".join("0x%08x"%x for x in vl)) if (key and len(vl)>1) else ""
        print("  %-15s (%s) = %s%s"%(lbl,"0x%05x"%widx,shown,raw), flush=True)

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
    print_snap("AFTER (during flood)", during)
    print("\n----- DELTA (run -c %d) -----"%count, flush=True)
    res={}
    for phys,widx,lbl,key in REGS:
        b=pick(before[phys]); a=pick(during[phys])
        if b is None or a is None:
            print("  %-15s incomplete (b=%s a=%s)"%(lbl,b,a)); res[lbl]=(b,a,None); continue
        d=(a-b)&0xffffffff; sd=d if d<0x80000000 else d-0x100000000
        tag="  <== CHANGED d=%+d"%sd if a!=b else "  (flat)"
        print("  %-15s 0x%08x -> 0x%08x%s"%(lbl,b,a,tag), flush=True)
        res[lbl]=(b,a,sd)
    return res, rd

def main():
    sh=Sh(); print("CONNECTED to stock", flush=True)
    r1,raw1=run(sh,100)
    r2,raw2=run(sh,200)
    print("\n===== RAW kmsg (run2 DURING) tail =====", flush=True)
    for ln in raw2.splitlines():
        if "fpga read" in ln: print("  "+ln.strip(), flush=True)
    sh.close()
    print("\nDONE", flush=True)

if __name__=="__main__": main()
