#!/usr/bin/env python3
"""Verify the DN-ring egress fix and sweep the egress-port hint (zx_eg_port)
to find which value routes a CPU->LAN frame to MAC2 (the host).

For port in 2,3,4: write /sys/module/zx279128_eth/parameters/zx_eg_port, run
txtest 16, read ALL SOPC send2smac0..4 + per-MAC TX deltas + host 0x88b5 wire
count. PASS when send2smac2 / MAC2 TX climb and 0x88b5 frames hit the wire.
"""
import socket, time, re, sys, subprocess

BRIDGE=("127.0.0.1",9999); HOST_NIC="enxc8a362e95900"
SOPC={0:0x921d915c,1:0x921d9160,2:0x921d9164,3:0x921d9168,4:0x921d916c}
MACTX={i:(0x92200000+(i)*0x40000+0x718) for i in range(5)}   # per-MAC TX_frames
PARAM="/sys/module/zx279128_eth/parameters/zx_eg_port"

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
    o=r.cmd("memdump %x 4"%p,0.5); t=re.findall(r"\b([0-9a-fA-F]{8})\b",o)
    return int(t[-1],16) if t else None

def snap(r): return ({i:rd(r,SOPC[i]) for i in SOPC}, {i:rd(r,MACTX[i]) for i in MACTX})

def main():
    n=16; r=R(); print("connected :9999",flush=True)
    r.cmd("mount -t debugfs none /sys/kernel/debug 2>/dev/null; echo ok",0.5)
    print("param file:",r.cmd("ls -l %s 2>&1"%PARAM,0.5).strip().splitlines()[-2:],flush=True)
    print("MAC2 EN=%s (lead-#1 fix)  DN base check via dump"%hex(rd(r,0x92280008) or 0),flush=True)
    for port in (2,3,4):
        w=r.cmd('sh -c "echo %d > %s"; cat %s'%(port,PARAM,PARAM),0.6)
        cur=re.findall(r"\b(\d+)\b",w); setp=cur[-1] if cur else "?"
        sb,mb=snap(r)
        tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-l","ether proto 0x88b5"],
                             stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True); time.sleep(0.6)
        r.cmd('sh -c "echo %d > /sys/kernel/debug/zx_eth/txtest"'%n,1.2); time.sleep(1.0); tcp.terminate()
        try: tdo,_=tcp.communicate(timeout=5)
        except Exception: tcp.kill(); tdo=""
        sa,ma=snap(r); wire=sum(1 for ln in tdo.splitlines() if "88b5" in ln.lower())
        def d(b,a,i): return ((a[i]or 0)-(b[i]or 0))&0xffffffff
        sopc_d=" ".join("smac%d+%d"%(i,d(sb,sa,i)) for i in SOPC if d(sb,sa,i))
        mac_d=" ".join("MAC%d_TX+%d"%(i,d(mb,ma,i)) for i in MACTX if d(mb,ma,i))
        hint=((port+0x28)&0x3f)<<4
        print("\n== zx_eg_port=%s (hint desc[2:3]=%#x) =="%(setp,hint),flush=True)
        print("   SOPC: %s"%(sopc_d or "(none)"),flush=True)
        print("   MAC : %s"%(mac_d or "(none)"),flush=True)
        print("   wire 0x88b5 = %d"%wire,flush=True)
        if wire>0 or d(sb,sa,2)>0 or d(mb,ma,2)>0:
            print("   *** PASS @ port=%s — egress to MAC2! ***"%setp,flush=True)
    r.close()

if __name__=="__main__": main()
