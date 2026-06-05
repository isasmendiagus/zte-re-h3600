#!/usr/bin/env python3
# Load the (best-effort) SPA classify matchram banks + hashram into mainline's SPA via
# the indirect iface (cmd 0x921d4014, data 0x921d401c+id*4), readback-verify, then test
# the routed flow (hw_trap + CLA fwd). Low confidence in matchram packing -> a NEGATIVE
# result is ambiguous (packing bug vs hypothesis); POSITIVE = HW forward.
import subprocess, re
REPO="/home/ubuntu/Projects/MYSELF/ZTE"; ZCON="/tmp/zcon.py"; PW="45788798"
CMD=0x921d4014; DATA=0x921d401c; STAT=0x921d4018
# matchram banks (data_id 0..5)
BANKS={0:[0xffff013e,0xe0ed962d,0x22c59fff,0xb3fffc08,0x7f8008d8,0x000b0800],
       1:[0xffff0043,0xe008962c,0x0ec51fff,0xa3fffc01,0xff80a0d8,0x000b177f],
       2:[0x00000000,0xe0166000,0x1ac59fff,0x4003fc00,0xff802258,0x000b167f]}
HASH=[(0x000016a9,0x1aa50200),(0x00001aa5,0x328d0200),(0x0000328d,0x62750200),
      (0x00026275,0xa2750200),(0x0001a275,0x62750200),(0x00016275,0xa2750200),
      (0x0002a275,0x20a10200),(0x000c20a1,0x00000200)]
SPORT,DPORT,DST=40000,5201,"172.31.9.50"
def pk(cmd,w=2): subprocess.run(["python3",ZCON,cmd,str(w)],capture_output=True,text=True,cwd=REPO)
def pkr(phys):
    o=subprocess.run(["python3",ZCON,"echo %x > /sys/kernel/debug/zx_eth/poke"%phys,"2"],capture_output=True,text=True,cwd=REPO).stdout
    m=re.search(r"peek 0x%x = 0x([0-9a-f]+)"%phys,o); return int(m.group(1),16) if m else None
def wr(phys,val): pk("echo %x %x > /sys/kernel/debug/zx_eth/poke"%(phys,val))
def trap():
    return pkr(0x9234c060)
def clafwd():
    return pkr(0x9238c3c0)
def hping(n,sp):
    subprocess.run("echo %s|sudo -S hping3 -S -c %d -i u12000 -s %d -k -p %d %s >/dev/null 2>&1"%(PW,n,sp,DPORT,DST),shell=True,cwd=REPO)
if __name__=="__main__":
    print("loading matchram banks...")
    for bk,w in BANKS.items():
        wr(CMD, bk)                       # cmd: rw=0 write, ram_id=0, addr=bank
        for did in (5,4,3,2,1,0):
            wr(DATA+did*4, w[did])
    print("verify matchram bank readback:")
    for bk,w in BANKS.items():
        wr(CMD, bk|(1<<27))               # cmd: rw=1 read
        rb=[pkr(DATA+i*4) for i in range(6)]
        ok = rb==w
        print("  bank%d %s exp=%s got=%s"%(bk,"OK" if ok else "DIFF",
              [hex(x) for x in w],[hex(x) if x is not None else "?" for x in rb]))
    print("loading hashram...")
    for slot,(d0,d1) in enumerate(HASH):
        wr(CMD, slot|(5<<22))             # cmd: rw=0, ram_id=5, addr=slot
        wr(DATA+1*4, d1)                  # data_id1 = data1
        wr(DATA+0*4, d0)                  # data_id0 = data0
    f0,t0=clafwd(),trap(); print("baseline CLA_fwd=0x%x hw_trap=0x%x"%(f0,t0))
    hping(80,SPORT); f1,t1=clafwd(),trap()
    print("matched flow: CLA_fwd=0x%x (d%d) hw_trap=0x%x (d%d)"%(f1,f1-f0,t1,t1-t0))
    print("VERDICT: CLA_fwd climbs / hw_trap flat -> HW FORWARD; else (ambiguous: packing or hypothesis)")
