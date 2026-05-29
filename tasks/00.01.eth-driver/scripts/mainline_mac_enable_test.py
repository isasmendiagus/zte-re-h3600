#!/usr/bin/env python3
"""DECISIVE live probe of lead #1 (MAC init-order wipe) on the MAINLINE kernel.

Live-confirmed: MAC2 MASK/ENABLE/iface = 0 (stock 0x3fff/0x80000001/0x00011200)
and SOPC<->MAC bridge 0x921d9068 = 0. Hypothesis: SOPC won't issue send2smac2
to a MAC that isn't enabled+bridged, so CPU->LAN egress dies before the MAC.

Probe: (0) restore DN tcont to wide-open so DSCH doesn't drop; (1) bring MAC2
fully live in the storm-safe order iface(+0xe0)->MASK->ENABLE (per §3.19: forcing
ENABLE alone without the +0xe0 serializer bond storms); (2) set SOPC<->MAC bridge
BIT(port)=BIT(2); (3) txtest 16 + host tcpdump; (4) read witnesses. Safety: quell
MAC2 (ENABLE=0, ctrl&=~3) at the end; everything resets on reboot anyway.

If send2smac2 / MAC2 TX climb and 0x88b5 frames hit the wire => lead #1 CONFIRMED,
fix = re-run full smac_init after pon_reset on link-up (+ sopc_mode_switch).
"""
import socket, time, re, sys, subprocess

BRIDGE=("127.0.0.1",9999); HOST_NIC="enxc8a362e95900"; DEV_MAC="f4:f6:47:0f:42:64"
MAC2=0x92280000
M_CTRL=MAC2+0x00; M_MASK=MAC2+0x04; M_EN=MAC2+0x08; M_IFACE=MAC2+0xe0
M_TXB=MAC2+0x714; M_TXF=MAC2+0x718; M_RXF=MAC2+0x780
SOPC_BR=0x921d9068
SCH_CMD=0x92354014; SCH_DATA=0x9235401c
W=[(0x9234c044,"QMG sw_fwd"),(0x921d9164,"SOPC send2smac2"),
   (M_TXF,"MAC2 TX_frames"),(M_TXB,"MAC2 TX_bytes"),
   (0x921da04c,"drop_DSCH"),(M_RXF,"MAC2 RX_frames")]

class Repl:
    def __init__(s):
        s.s=socket.create_connection(BRIDGE,timeout=10); s.s.settimeout(0.4); s._d(0.5)
    def _d(s,t):
        b=b''; e=time.time()+t
        while time.time()<e:
            try:d=s.s.recv(65536)
            except socket.timeout:d=b''
            if d:b+=d;e=time.time()+t
            else:time.sleep(0.03)
        return b.decode(errors='replace')
    def cmd(s,l,t=0.5): s.s.sendall(l.encode()+b"\n"); return s._d(t)
    def close(s): s.s.close()

def rd(r,phys):
    o=r.cmd("memdump %x 4"%phys,0.5); t=re.findall(r"\b([0-9a-fA-F]{8})\b",o)
    return int(t[-1],16) if t else None
def poke(r,phys,val): r.cmd('sh -c "echo \'%x %x\' > /sys/kernel/debug/zx_eth/poke"'%(phys,val),0.4)
def sch_wr(r,ramid,addr,val):
    poke(r,SCH_CMD,(addr&0x1ff)|((ramid&0xf)<<22)); poke(r,SCH_DATA,val)
def wit(r): return {l:rd(r,p) for p,l in W}
def show(tag,d): print("  [%s] %s"%(tag,"  ".join("%s=%s"%(l,("0x%x"%d[l] if d[l] is not None else "??")) for _,l in W)),flush=True)

def main():
    n=int(sys.argv[1]) if len(sys.argv)>1 else 16
    r=Repl(); print("connected :9999",flush=True)
    r.cmd("mount -t debugfs none /sys/kernel/debug 2>/dev/null; echo ok",0.5)

    print("\n== (0) restore DN tcont wide-open (undo prior probe) ==",flush=True)
    for u in range(8):
        sch_wr(r,0xe,u,0x1fffff); sch_wr(r,0xf,u,0x7ffffff)

    print("== (1) MAC2 enable: iface->mask->enable (storm-safe order) ==",flush=True)
    print("  pre:  CTRL=0x%x MASK=0x%x EN=0x%x IFACE=0x%x BR=0x%x"%(
        rd(r,M_CTRL) or 0, rd(r,M_MASK) or 0, rd(r,M_EN) or 0, rd(r,M_IFACE) or 0, rd(r,SOPC_BR) or 0),flush=True)
    poke(r,M_IFACE,0x00011200)      # serializer/PHY bond FIRST
    poke(r,M_MASK,0x00003fff)
    poke(r,M_EN,0x80000001)
    poke(r,M_CTRL,0x00ba6003)       # ensure rx/tx-en (bits0,1) + link
    print("  (2) SOPC<->MAC bridge: set BIT(2) on 0x921d9068",flush=True)
    br=rd(r,SOPC_BR) or 0; poke(r,SOPC_BR, br|0x4)
    time.sleep(0.3)
    print("  post: CTRL=0x%x MASK=0x%x EN=0x%x IFACE=0x%x BR=0x%x"%(
        rd(r,M_CTRL) or 0, rd(r,M_MASK) or 0, rd(r,M_EN) or 0, rd(r,M_IFACE) or 0, rd(r,SOPC_BR) or 0),flush=True)

    before=wit(r); show("before",before)
    print("\n== (3) txtest %d + host tcpdump =="%n,flush=True)
    tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-l","ether proto 0x88b5 or ether src %s"%DEV_MAC],
                         stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True)
    time.sleep(0.6)
    r.cmd('sh -c "echo %d > /sys/kernel/debug/zx_eth/txtest"'%n,1.2)
    time.sleep(1.2); tcp.terminate()
    try: tdo,_=tcp.communicate(timeout=5)
    except Exception: tcp.kill(); tdo=""
    w88=sum(1 for ln in tdo.splitlines() if "88b5" in ln.lower())
    wdev=sum(1 for ln in tdo.splitlines() if DEV_MAC in ln)
    after=wit(r); show("after ",after)
    print("  wire: 0x88b5=%d  src-dev=%d"%(w88,wdev),flush=True)

    print("\n== (4) safety: quell MAC2 ==",flush=True)
    poke(r,M_EN,0); poke(r,M_CTRL,(rd(r,M_CTRL) or 0)&~3)

    def d(l):
        b=before[l];a=after[l]
        return (a-b)&0xffffffff if (a is not None and b is not None) else None
    print("\n----- VERDICT -----",flush=True)
    print("  sw_fwd d=%s | send2smac2 d=%s | MAC2 TX d=%s | drop_DSCH d=%s | MAC2 RX d=%s"%(
        d("QMG sw_fwd"),d("SOPC send2smac2"),d("MAC2 TX_frames"),d("drop_DSCH"),d("MAC2 RX_frames")),flush=True)
    if (d("SOPC send2smac2") or 0)>0 or (d("MAC2 TX_frames") or 0)>0 or w88>0:
        print("  ==> CONFIRMED: bringing MAC2 fully live unblocked egress. Fix = full smac_init after pon_reset.",flush=True)
    elif (d("MAC2 RX_frames") or 0)>50:
        print("  ==> STORM suspected (MAC2 RX exploded). MAC quelled; reboot to recover.",flush=True)
    else:
        print("  ==> still no egress; MAC-enable alone insufficient (needs per-port pon_reset + sopc_mode_switch handshake — go Option B).",flush=True)
    r.close()

if __name__=="__main__": main()
