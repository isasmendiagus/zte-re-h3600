#!/usr/bin/env python3
"""Dump the SCH/DSCH token-bucket shaper indirect RAM from live stock — the
DN tcont credit (RAMID 0xe/0xf) is lead #2 for the CPU->LAN egress gate.

tm.ko init only programs the UP shaper (RAMID 2/3 per-queue, 5/6 per-tcont);
the DN tcont shaper (RAMID 0xe=fill-rate, 0xf=bucket-cap) is filled at RUNTIME
by cspd (QoS). So on a live, working stock router the DN tcont credit should be
NONZERO — while mainline's zx_sch_init replays only UP and leaves DN at 0 (zero
credit => DN scheduler never dequeues toward SOPC). This dump captures stock's
runtime DN values so we can replay them in mainline.

Indirect protocol (DATASHEET Diagram 4 / spa_indirect_ram_protocol_re.md;
SCH tm:29690, SAME CMD layout as SPA):
  CMD  0x92354014 (widx 0xd5005): addr[21:0] | ram_id[26:22] | rw_en[27] | incr[31]
  DONE 0x92354018 (widx 0xd5006): bit0
  DATA 0x9235401c.. (widx 0xd5007..9): 3 words
  rw_en=1 = READ-prefetch (the ONLY write; non-destructive read cycle).
RAMID: 2=UP pq fill, 3=UP pq cap, 5=UP tcont fill, 6=UP tcont cap,
       0xe=DN tcont fill, 0xf=DN tcont cap.
Known UP values (validate the protocol): fill=0x186a00 (1.6M), cap=0x30d40 (200k).

Reads via /bin/fpga land in /proc/kmsg. No datapath reg written, no NAND, no reboot.
"""
import paramiko, time, re, sys, json, os

HOST, USER, PW = "192.168.1.1", "admin", "UkuGPeyRDU"
CMD_ID, DONE_ID, DATA_ID = 0xd5005, 0xd5006, 0xd5007   # phys 0x92354014/18/1c
OUTDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                      "..","captures","stock_state")

# (ram_id, label, units, ndata)
PLAN = [
    (0xe, "DN_tcont_fill", range(8), 3),   # <-- the lead
    (0xf, "DN_tcont_cap",  range(8), 3),
    (5,   "UP_tcont_fill", range(4), 3),   # control: expect ~0x186a00
    (6,   "UP_tcont_cap",  range(4), 3),   # control: expect ~0x30d40
]

def rd_cmd(ram, addr): return (addr & 0x3fffff) | (ram << 22) | (1 << 27)

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
    def send(self,c): self.ch.send(c+'\n')
    def close(self):
        try: self.ch.close()
        except Exception: pass
        self.cli.close()

def burst(sh, lines):
    sh.send("killall cat 2>/dev/null; rm -f /tmp/k.txt; cat /proc/kmsg > /tmp/k.txt &")
    sh._d(0.6); time.sleep(1.0)
    sh.send("/bin/fpga -r 0x%x 1"%DONE_ID); sh._d(0.3); time.sleep(0.3)   # throwaway
    for ln in lines:
        sh.send(ln); sh._d(0.28)
    time.sleep(0.6)
    sh.send("kill %1 2>/dev/null; killall cat 2>/dev/null"); sh._d(0.3)
    sh.send("cat /tmp/k.txt"); out=sh._d(2.0)
    byw={}
    for m in re.finditer(r"reg=0x0*([0-9a-fA-F]+),\s*value=0x([0-9a-fA-F]+)",out):
        byw.setdefault(int(m.group(1),16),[]).append(int(m.group(2),16))
    return byw

def read_entry(sh, ram, addr, ndata):
    c=rd_cmd(ram,addr)
    lines=["/bin/fpga -r 0x%x 1"%DONE_ID,
           "/bin/fpga -w 0x%x 0x%x"%(CMD_ID,c),       # READ-prefetch (only write)
           "/bin/fpga -r 0x%x 1"%DONE_ID]
    for i in range(ndata): lines.append("/bin/fpga -r 0x%x 1"%(DATA_ID+i))
    byw=burst(sh,lines)
    return c, [ (byw.get(DATA_ID+i) or [None])[-1] for i in range(ndata) ]

def main():
    sh=Sh(); print("CONNECTED stock (SCH shaper dump)",flush=True)
    pre=burst(sh,["/bin/fpga -r 0x%x 1"%CMD_ID,"/bin/fpga -r 0x%x 1"%DONE_ID,
                  "/bin/fpga -r 0xd5000 1"])   # SCH enables 0x92354000
    print("PRE cmd/done/enables: %s"%{("0x%05x"%k):["0x%08x"%x for x in v] for k,v in pre.items()},flush=True)
    out={}
    for ram,label,units,nd in PLAN:
        print("\n== %s (RAMID 0x%x) =="%(label,ram),flush=True)
        rows={}
        for u in units:
            c,words=read_entry(sh,ram,u,nd)
            ws=" ".join("--------" if w is None else "%08x"%w for w in words)
            print("  unit%d cmd=0x%08x  data= %s"%(u,c,ws),flush=True)
            rows[u]=[("0x%08x"%w if w is not None else None) for w in words]
        out[label]={"ram_id":ram,"rows":rows}
    sh.close()
    os.makedirs(OUTDIR,exist_ok=True)
    path=os.path.join(OUTDIR,"sch_shaper_stock_%s.json"%time.strftime("%Y-%m-%d"))
    json.dump({"kind":"stock_sch_shaper_dump","date":time.strftime("%Y-%m-%d %H:%M:%S"),
               "note":"DN tcont RAMID 0xe/0xf = runtime cspd-filled credit; UP 5/6 = control",
               "data":out}, open(path,"w"), indent=2)
    print("\nsaved -> %s\nDONE"%path,flush=True)

if __name__=="__main__": main()
