#!/usr/bin/env python3
"""Replay the EXACT register-poke sequence from the 2026-05-29 'good boot' where
CPU->LAN egress worked (send2smac2 climbed, txtest frames on wire, ping 5/5),
reconstructed from this session's transcript + mainline_mac_enable_test.py.

KEY difference vs the failing clean tests: a SUSTAINED host ping runs BEFORE the
txtest (the good boot had live bidirectional traffic → device learns the host MAC
in its FDB → fabric can DA-resolve egress to MAC2). This tests whether FDB learning
(not the pokes) was the real enabler.

Drives the mainline debugfs over the :9999 REPL. Reads via memdump.
Run on a cold mainline boot. Reports send2smac2/MAC2 TX/drop_DSCH deltas + wire count.
"""
import socket, time, re, subprocess

BRIDGE=("127.0.0.1",9999); HOST_NIC="enxc8a362e95900"; DEV="192.168.1.99"
M=0x92280000
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
def poke(r,p,v): r.cmd('sh -c "echo \'%x %x\' > /sys/kernel/debug/zx_eth/poke"'%(p,v),0.35)
def sch_wr(r,ramid,addr,val):
    poke(r,0x92354014,(addr&0x1ff)|((ramid&0xf)<<22)); poke(r,0x9235401c,val)
def df(x,y):
    try:return (int(y)-int(x))&0xffffffff
    except:return "?"

def main():
    r=R(); print("connected :9999",flush=True)
    r.cmd("mount -t debugfs none /sys/kernel/debug 2>/dev/null",0.5)

    print("== STEP 1: restore DN tcont wide-open (mac_enable_test did this) ==",flush=True)
    for u in range(8):
        sch_wr(r,0xe,u,0x1fffff); sch_wr(r,0xf,u,0x7ffffff)

    print("== STEP 2: MAC2 enable seq (iface->mask->enable), bit15-set then later clear ==",flush=True)
    poke(r,M+0x0e0,0x00011200); poke(r,M+0xc20,0x00000032); poke(r,M+0xc50,0x000000a8)
    poke(r,M+0x004,0x00003fff); poke(r,M+0x008,0x80000001); poke(r,M+0x000,0x00bae003)

    print("== STEP 3: SOPC bridge 0x19068 = 0x1f ==",flush=True)
    poke(r,0x921d9068,0x1f)

    print("== STEP 4: SUSTAINED host ping (FDB-learn host MAC) — 60 frames ==",flush=True)
    p=subprocess.Popen(["ping","-c","60","-i","0.1","-W","1",DEV],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    time.sleep(2.0)

    print("== STEP 5: prime txtest with bit15 SET (engage), watch send2smac2 ==",flush=True)
    sm0=rd(r,0x921d9164);
    r.cmd('sh -c "echo 32 > /sys/kernel/debug/zx_eth/txtest"',1.2); time.sleep(0.8)
    sm1=rd(r,0x921d9164)
    print("   after engage-txtest: send2smac2 d=%s (0x%x->0x%x)"%(df(sm0,sm1),sm0 or 0,sm1 or 0),flush=True)

    print("== STEP 6: clear bit15 (ctrl=0xba6003) ==",flush=True)
    poke(r,M+0x000,0x00ba6003)

    print("== STEP 7: txtest 40 + host tcpdump (the wire test) ==",flush=True)
    sm0=rd(r,0x921d9164); tx0=rd(r,M+0x718); dd0=rd(r,0x921da04c)
    tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-c","80","-l","ether proto 0x88b5"],
                         stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True); time.sleep(0.6)
    r.cmd('sh -c "echo 40 > /sys/kernel/debug/zx_eth/txtest"',1.5); time.sleep(1.5); tcp.terminate()
    try: tdo,_=tcp.communicate(timeout=5)
    except Exception: tcp.kill(); tdo=""
    sm1=rd(r,0x921d9164); tx1=rd(r,M+0x718); dd1=rd(r,0x921da04c)
    w=sum(1 for ln in tdo.splitlines() if "88b5" in ln.lower())
    print("   send2smac2 d=%s | MAC2_TX d=%s | drop_DSCH d=%s | wire88=%d"%(
        df(sm0,sm1),df(tx0,tx1),df(dd0,dd1),w),flush=True)
    try: p.wait(timeout=10)
    except Exception: p.kill()

    print("== STEP 8: real ping test ==",flush=True)
    pr=subprocess.run(["ping","-c","10","-i","0.3","-W","1",DEV],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=30).stdout
    m=re.search(r"(\d+) packets transmitted, (\d+) received",pr)
    print("   PING: %s"%(m.group(0) if m else "?"),flush=True)
    print("\n==> %s"%("*** REPRODUCED: egress works ***" if (w or df(sm0,sm1)) else "did NOT reproduce"),flush=True)
    r.close()

if __name__=="__main__": main()
