#!/usr/bin/env python3
"""Empirical DSCH/SCH diff on a cold mainline boot (Option A, egress-nibble path).

After 4 agents confirmed every init recipe (egress-nibble, PM/SPA, SBRG flood,
SCH shaper RAMID2/3/5/6, DN mount/mode) is ALREADY in the driver yet drop_DSCH
still climbs + send2smac2=0, this stops theorizing and gathers live data:

  1. READ BACK the SCH shaper RAM (RAMID 2/3/5/6/0xb/0xc/0xe/0xf) for the CPU→LAN
     unit (port3/MAC2 → unit=3) — does the credit the driver wrote actually stick?
  2. READ the quesch mount reg (0x92354340 + unit*4) — is queue→secsch mount live?
  3. txtest baseline: QMG sw_fwd / RED / drop_DSCH / send2smac2 / MAC2 TX deltas.
  4. RX-PRIME test: sustained host ping (device RX), THEN txtest again — does RX
     traffic through the fabric unblock the DSCH→SOPC dequeue? (The one good boot
     had a live ping; Agent 2 says FDB is a red herring — this settles it.)

Drives debugfs poke/memdump over the :9999 REPL. Run on a cold mainline boot.
"""
import socket, time, re, subprocess

BRIDGE=("127.0.0.1",9999); HOST_NIC="enxc8a362e95900"; DEV="192.168.1.99"
SCH=0x92354000
CMD=SCH+0x14; DONE=SCH+0x18; DATA=SCH+0x1c
UNIT=3   # host CPU→LAN = internal port3 / MAC2

class R:
    def __init__(s): s.s=socket.create_connection(BRIDGE,timeout=10); s.s.settimeout(0.4); s._d(0.5)
    def _d(s,t):
        b=b'';e=time.time()+t
        while time.time()<e:
            try:d=s.s.recv(65536)
            except socket.timeout:d=b''
            if d:b+=d;e=time.time()+t
            else:time.sleep(0.03)
        return b.decode(errors='replace')
    def cmd(s,l,t=0.5): s.s.sendall(l.encode()+b"\n"); return s._d(t)
    def close(s): s.s.close()
def rd(r,p):
    o=r.cmd("memdump %x 4"%p,0.4); t=re.findall(r"\b([0-9a-fA-F]{8})\b",o); return int(t[-1],16) if t else None
def poke(r,p,v): r.cmd('sh -c "echo \'%x %x\' > /sys/kernel/debug/zx_eth/poke"'%(p,v),0.30)
def df(x,y):
    try:return (int(y)-int(x))&0xffffffff
    except:return "?"

def sch_read(r,ramid,addr):
    """SCH indirect READ: CMD with rwEn(bit27)=1, poll DONE, read DATA."""
    poke(r, CMD, (addr&0x1ff)|((ramid&0xf)<<22)|(1<<27))
    for _ in range(20):
        if (rd(r,DONE) or 0)&1: break
        time.sleep(0.002)
    return rd(r, DATA)

def stage(r):
    return dict(qmg=rd(r,0x9234c044), red=rd(r,0x92344204),
                drop=rd(r,0x921da04c), sm2=rd(r,0x921d9164), tx=rd(r,0x92280718))
def txt(r,n,label):
    a=stage(r)
    tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-c","60","-l","ether proto 0x88b5"],
                         stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True); time.sleep(0.6)
    r.cmd('sh -c "echo %d > /sys/kernel/debug/zx_eth/txtest"'%n,1.6); time.sleep(1.2); tcp.terminate()
    try: tdo,_=tcp.communicate(timeout=5)
    except Exception: tcp.kill(); tdo=""
    b=stage(r); w=sum(1 for ln in tdo.splitlines() if "88b5" in ln.lower())
    print("  [%s] QMG d=%s RED d=%s drop_DSCH d=%s send2smac2 d=%s MAC2_TX d=%s | wire=%d"%(
        label, df(a['qmg'],b['qmg']), df(a['red'],b['red']), df(a['drop'],b['drop']),
        df(a['sm2'],b['sm2']), df(a['tx'],b['tx']), w), flush=True)
    return w or (df(a['sm2'],b['sm2']) not in (0,"?"))

def main():
    r=R(); print("connected :9999",flush=True)
    r.cmd("mount -t debugfs none /sys/kernel/debug 2>/dev/null",0.5)

    print("\n== SCH RAM readback, unit=%d (does the credit/mount the driver wrote stick?) =="%UNIT,flush=True)
    print("  tcont RAMID5 fill = 0x%08x (exp 0x186a0)"%(sch_read(r,5,UNIT) or 0),flush=True)
    print("  tcont RAMID6 cap  = 0x%08x (exp 0x30d40)"%(sch_read(r,6,UNIT) or 0),flush=True)
    print("  tcont RAMID0xe fill(DN)=0x%08x  RAMID0xf cap(DN)=0x%08x"%(sch_read(r,0xe,UNIT) or 0, sch_read(r,0xf,UNIT) or 0),flush=True)
    for q in range(8):
        a=q+UNIT*8
        print("  q%d(addr0x%02x): RAMID2 fill=0x%08x RAMID3 cap=0x%08x RAMID0xb dnmode=0x%08x RAMID0xc wrr=0x%08x"%(
            q,a, sch_read(r,2,a) or 0, sch_read(r,3,a) or 0, sch_read(r,0xb,a) or 0, sch_read(r,0xc,a) or 0),flush=True)
    print("  quesch_mount 0x%08x = 0x%08x (exp 0x000000ff)"%(SCH+0x340+UNIT*4, rd(r,SCH+0x340+UNIT*4) or 0),flush=True)

    print("\n== BASELINE txtest (no RX prime) ==",flush=True)
    txt(r,16,"baseline")

    print("\n== RX-PRIME: sustained host ping (device RX through fabric), then txtest ==",flush=True)
    p=subprocess.Popen(["ping","-c","80","-i","0.05","-W","1",DEV],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    time.sleep(2.5)
    rxf=rd(r,0x92280710)  # MAC2 RX frames — confirm RX actually happening
    print("  (MAC2 RX_frames now=0x%x)"%(rxf or 0),flush=True)
    ok=txt(r,16,"after-RX-prime")
    try: p.wait(timeout=8)
    except Exception: p.kill()

    print("\n== with ping STILL flooding, second txtest ==",flush=True)
    p2=subprocess.Popen(["ping","-c","60","-i","0.05","-W","1",DEV],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    time.sleep(0.5); ok2=txt(r,16,"during-ping");
    try: p2.wait(timeout=8)
    except Exception: p2.kill()

    print("\n==> RX-prime %s egress"%("ENABLED" if (ok or ok2) else "did NOT enable"),flush=True)
    r.close()

if __name__=="__main__": main()
