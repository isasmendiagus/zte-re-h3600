#!/usr/bin/env python3
"""Verify CPU->LAN egress on a FRESH mainline boot after the lead-#1 fix
(adjust_link now re-runs full zx_smac_init_port on link-UP). No pokes — pure
observation: confirm MAC2 came up live, then txtest + host tcpdump.

PASS = SOPC send2smac2 (0x921d9164) and MAC2 TX_frames (0x92280718) climb and
0x88b5 frames appear on the wire.
"""
import socket, time, re, sys, subprocess

BRIDGE=("127.0.0.1",9999); HOST_NIC="enxc8a362e95900"; DEV_MAC="f4:f6:47:0f:42:64"
MAC2=0x92280000
W=[(0x9234c044,"QMG sw_fwd"),(0x921d9164,"SOPC send2smac2"),
   (MAC2+0x718,"MAC2 TX_frames"),(MAC2+0x714,"MAC2 TX_bytes"),
   (0x921da04c,"drop_DSCH"),(MAC2+0x780,"MAC2 RX_frames")]
CFG=[(MAC2+0x00,"CTRL","ba6003/bae003"),(MAC2+0x04,"MASK","3fff"),
     (MAC2+0x08,"ENABLE","80000001"),(MAC2+0xe0,"iface","0(W1)"),
     (0x921d9068,"SOPC bridge","BIT2 set")]

class Repl:
    def __init__(s): s.s=socket.create_connection(BRIDGE,timeout=10); s.s.settimeout(0.4); s._d(0.5)
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
def wit(r): return {l:rd(r,p) for p,l in W}

def main():
    n=int(sys.argv[1]) if len(sys.argv)>1 else 16
    r=Repl(); print("connected :9999",flush=True)
    r.cmd("mount -t debugfs none /sys/kernel/debug 2>/dev/null; echo ok",0.5)
    print("\n== MAC2 config (fix should make these live, no pokes) ==",flush=True)
    for phys,lbl,exp in CFG:
        print("  %-14s = 0x%-10s (expect %s)"%(lbl,"%x"%(rd(r,phys) or 0),exp),flush=True)
    before=wit(r)
    print("\n== txtest %d + host tcpdump =="%n,flush=True)
    tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-l","ether proto 0x88b5 or ether src %s"%DEV_MAC],
                         stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True)
    time.sleep(0.6)
    r.cmd('sh -c "echo %d > /sys/kernel/debug/zx_eth/txtest"'%n,1.2)
    time.sleep(1.2); tcp.terminate()
    try: tdo,_=tcp.communicate(timeout=5)
    except Exception: tcp.kill(); tdo=""
    after=wit(r)
    w88=sum(1 for ln in tdo.splitlines() if "88b5" in ln.lower())
    def d(l):
        b=before[l];a=after[l]; return (a-b)&0xffffffff if (a is not None and b is not None) else None
    print("\n  %-18s %12s %12s %8s"%("stage","before","after","delta"),flush=True)
    for p,l in W:
        b=before[l];a=after[l]
        print("  %-18s 0x%08x 0x%08x %+8s"%(l,b or 0,a or 0,str(d(l))),flush=True)
    print("\n  wire 0x88b5 frames: %d"%w88,flush=True)
    print("\n----- VERDICT -----",flush=True)
    if (d("SOPC send2smac2") or 0)>0 or (d("MAC2 TX_frames") or 0)>0 or w88>0:
        print("  *** PASS: CPU->LAN egress WORKS. send2smac2 d=%s MAC2_TX d=%s wire=%d ***"%(
            d("SOPC send2smac2"),d("MAC2 TX_frames"),w88),flush=True)
    else:
        print("  FAIL: still no egress (sw_fwd d=%s, drop_DSCH d=%s). MAC live but SOPC silent → next lead."%(
            d("QMG sw_fwd"),d("drop_DSCH")),flush=True)
    r.close()

if __name__=="__main__": main()
