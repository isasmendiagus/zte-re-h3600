#!/usr/bin/env python3
"""Capture the stock CPU->LAN egress call path at runtime via kotrace, to
resolve the ring-vs-ring-less contradiction (DATASHEET §3.11) and find the
actual sw_fwd egress-enqueue + egress-port hint.

Loads kotrace.ko on the live stock kernel (post-boot insmod — patches the
target fns incl. the egress chain), clears the ring, drives a host ping (the
device generates ICMP replies = CPU->LAN egress), then dumps /proc/kotrace_dump.

Egress fns of interest (in plat_zxylzb_9128S, all in kotrace_targets.h):
  pdt_ethdrv_send -> pon_tm_net_tx -> pon_tm_get_next_txdesc(dir)
                  -> pon_tm_data_raw_send(skb, desc, DIR) -> soft_insert_tx_1desc(desc, DIR)
The DIR arg (r2 of data_raw_send / r1 of soft_insert) tells UP(0) vs DN(!=0) ring.
If these fire on a ping reply -> ring path IS used (re-examine the consume=0 oracle).
If they DON'T fire -> there's a ring-less egress path to find.

Drives over SSH (paramiko). Module load is the only device write; reads otherwise.
Symbol map comes from the '[ko: target NAME @ 0xADDR]' lines kotrace prints to UART
(captured in /tmp/uart_bridge.log by the running bridge).
"""
import paramiko, subprocess, time, re, os, sys

HOST,USER,PW="192.168.1.1","admin","UkuGPeyRDU"
Z="/home/ubuntu/Projects/MYSELF/ZTE"
OUT=os.path.join(Z,"tasks/00.01.eth-driver/captures/stock_state")
EGRESS=["pdt_ethdrv_send","pon_tm_net_tx","pon_tm_get_next_txdesc",
        "pon_tm_data_raw_send","soft_insert_tx_1desc","ffe_learn_skb"]

class Sh:
    def __init__(s):
        s.c=paramiko.SSHClient(); s.c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        s.c.connect(HOST,username=USER,password=PW,timeout=20,allow_agent=False,look_for_keys=False)
        s.ch=s.c.invoke_shell(width=240,height=4000); time.sleep(1.0); s._d(0.6)
    def _d(s,t):
        o='';e=time.time()+t
        while time.time()<e:
            if s.ch.recv_ready(): o+=s.ch.recv(65536).decode(errors='replace');e=time.time()+t
            else: time.sleep(0.04)
        return o
    def run(s,cmd,t=3.0): s.ch.send(cmd+"\n"); return s._d(t)
    def close(s):
        try:s.ch.close()
        except Exception:pass
        s.c.close()

def main():
    npings=int(sys.argv[1]) if len(sys.argv)>1 else 5
    os.makedirs(OUT,exist_ok=True)
    # stage the module on the host TFTP root
    subprocess.run(["cp",os.path.join(Z,"tasks/00.01.eth-driver/kotrace/kotrace.ko"),
                    os.path.join(Z,"tftp/kotrace.ko")],check=True)
    sh=Sh(); print("connected stock",flush=True)
    print("-- fetch + insmod kotrace.ko (patches targets; ~several s) --",flush=True)
    print(sh.run("cd /tmp && busybox tftp -g -r kotrace.ko 192.168.1.50 && ls -l /tmp/kotrace.ko",6).strip()[-160:],flush=True)
    o=sh.run("rmmod kotrace 2>/dev/null; insmod /tmp/kotrace.ko 2>&1; echo INSMOD_RC=$?",20)
    print("  insmod:",o.strip().splitlines()[-1] if o.strip() else "?",flush=True)
    time.sleep(2.0)
    print("-- clear ring, drive %d pings, dump --"%npings,flush=True)
    sh.run("echo > /proc/kotrace_dump; echo CLEARED",3)
    subprocess.run(["ping","-c",str(npings),"-i","0.2","-W","1",HOST],
                   stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    time.sleep(0.5)
    dump=sh.run("cat /proc/kotrace_dump",6)
    sh.run("rmmod kotrace 2>/dev/null; echo RMMOD",4)   # restore (kotrace leaves patches; rmmod best-effort)
    sh.close()

    raw=os.path.join(OUT,"kotrace_egress_raw_%s.txt"%time.strftime("%Y-%m-%d"))
    open(raw,"w").write(dump)
    print("\nsaved raw dump -> %s (%d bytes)"%(raw,len(dump)),flush=True)

    # symbol map from the bridge log ([ko: target NAME @ 0xADDR])
    sym={}
    try:
        bl=open("/tmp/uart_bridge.log",errors="replace").read()
        for m in re.finditer(r"\[ko: target (\S+) @ 0x([0-9a-f]+)\]",bl):
            sym[m.group(2).lower()]=m.group(1)
    except Exception as e: print("  (no bridge log: %s)"%e,flush=True)

    print("\n=== egress-path hits (seq marker symbol r0..r3) ===",flush=True)
    lines=dump.splitlines(); n=0
    for ln in lines:
        # resolve any 0xADDR in the line to a symbol name if known
        def repl(m): return sym.get(m.group(1).lower(),m.group(0))
        res=re.sub(r"0x([0-9a-f]{6,8})",repl,ln)
        if any(fn in res for fn in EGRESS):
            print("  "+res.strip(),flush=True); n+=1
    print("\n  %d egress-path hits. Total dump lines: %d"%(n,len(lines)),flush=True)
    if n==0:
        print("  (none — egress fns did NOT fire on the ping reply => ring-less path; show raw head:)",flush=True)
        for ln in lines[:20]: print("   |",ln.strip(),flush=True)

if __name__=="__main__": main()
