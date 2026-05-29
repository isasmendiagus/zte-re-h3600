#!/usr/bin/env python3
"""Stock TX-egress ORACLE capture (reads only) — golden profile for the
stock-vs-mainline egress diff.

Brackets a known CPU->LAN egress burst (host pings the device; the device's
CPU generates ICMP replies that egress out MAC2 = the host port) and snapshots
the canonical egress-pipeline checkpoint counters + the load-bearing egress
config registers, BEFORE vs DURING. Per-stage deltas show where a frame lives
("alive at stage N, 0 at N+1" = the gate). Host tcpdump counts the frames that
actually hit the wire = ground truth.

Method = the corrected /proc/kmsg discipline from dn_ring_remeasure.py:
  one persistent `cat /proc/kmsg`, ~1.2s warmup, a throwaway first /bin/fpga
  read (the kernel ring drops it), then the real reads; climbing counters are
  read TWICE so we see+discard a dropped first read and keep the LAST value.

fpga read: `/bin/fpga -r <wordidx> 1`, wordidx=(phys-0x92000000)/4. Output lands
in the kernel ring, parsed `fpga read: reg=0x..., value=0x...`.

NO registers are written, no NAND flashed, no reboot. SSH closed cleanly.
Absolute phys only (respects the npp_base=0x921c0000 vs tm_base=0x92340000
base-gotcha; widx is derived from absolute phys).
"""
import paramiko, subprocess, time, re, sys, json, os

HOST="192.168.1.1"; USER="admin"; PW="UkuGPeyRDU"
HOST_NIC="enxc8a362e95900"
OUTDIR=os.path.join(os.path.dirname(os.path.abspath(__file__)),
                    "..","captures","stock_state")

def widx(phys): return (phys-0x92000000)>>2

# Egress-pipeline checkpoint COUNTERS, in CPU->wire flow order.
# (phys, label, key)  key => read twice/snapshot (must climb during egress).
# extract notes (applied in the report, raw stored): DSCH in>>24, out (raw>>8)&0xff
COUNTERS = [
    (0x9234c044, "QMG sw_fwd",        True),   # first egress counter; ticks
    (0x9234c048, "QMG hw_fwd",        False),
    (0x9234c04c, "QMG hw_trap",       False),  # hairpin-to-CPU witness
    (0x92344204, "RED fwd in",        False),
    (0x92344210, "RED fwd out",       False),
    (0x92354200, "DSCH in_que >>24",  False),
    (0x923541fc, "DSCH out_que",      False),  # (raw>>8)&0xff
    (0x921d915c, "SOPC send2smac0",   False),
    (0x921d9160, "SOPC send2smac1",   False),
    (0x921d9164, "SOPC send2smac2",   True),   # host port; THE gate counter
    (0x921d9168, "SOPC send2smac3",   False),
    (0x921d916c, "SOPC send2smac4",   False),
    (0x92280714, "MAC2 TX_bytes",     False),
    (0x92280718, "MAC2 TX_frames",    True),   # wire-side dead end; must climb
    (0x92280780, "MAC2 RX_frames",    False),  # control: RX works
    (0x921da040, "drop_PP",           False),
    (0x921da044, "drop_RED",          False),
    (0x921da04c, "drop_DSCH",         False),
]

# Load-bearing egress CONFIG registers (static; the Diff-B target set).
CONFIG = [
    (0x92280000, "MAC2 CTRL"),         (0x92280004, "MAC2 MASK"),
    (0x92280008, "MAC2 ENABLE"),       (0x922800e0, "MAC2 iface(+0xe0)"),
    (0x921e0054, "PM ctrl"),           (0x921e01a0, "PM out_port_rule"),
    (0x921d407c, "SPA match_mode"),    (0x9234c000, "QMG thresholds"),
    (0x923881c4, "BRG learn_mode"),    (0x92388340, "BRG unk_unicast_fwd"),
    (0x92388008, "BRG vl_chk"),        (0x9238863c, "BRG mcast_vltrans"),
    (0x923a001c, "PON_PP_TM_CFG"),     (0x921cc000, "SIPC ctrl"),
    (0x92354000, "SCH enables"),       (0x9238002c, "PP CPU_fwd"),
    (0x921d4120, "SPA onu_mac_lo"),    (0x921d4124, "SPA onu_mac_hi"),
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
    def send(self,c): self.ch.send(c+'\n')
    def close(self):
        try: self.ch.close()
        except Exception: pass
        self.cli.close()

def _read_window(sh, physes, reads_per=2):
    """One small kmsg window: read each phys `reads_per` times. Returns
    {widx: [values]} grouped by widx (robust to dropped reads — a drop just
    means fewer samples for that widx, never a cascade). Keeps reads-per-window
    small so stock printk rate-limiting under load doesn't suppress them."""
    sh.send('killall cat 2>/dev/null; rm -f /tmp/k.txt; cat /proc/kmsg > /tmp/k.txt &')
    sh._d(0.8); time.sleep(1.2)
    sh.send('/bin/fpga -r 0xd3011 1'); sh._d(0.4); time.sleep(0.4)   # throwaway (first read dropped)
    for _ in range(reads_per):
        for phys in physes:
            sh.send('/bin/fpga -r 0x%x 1'%widx(phys)); sh._d(0.30)
    time.sleep(0.8)
    sh.send('kill %1 2>/dev/null; killall cat 2>/dev/null'); sh._d(0.4)
    sh.send('cat /tmp/k.txt'); out=sh._d(2.4)
    byw={}
    for m in re.finditer(r"reg=0x0*([0-9a-fA-F]+),\s*value=0x([0-9a-fA-F]+)",out):
        byw.setdefault(int(m.group(1),16),[]).append(int(m.group(2),16))
    return byw

def snapshot(sh, regs, chunk=7):
    """Chunked, drop-resilient. Returns {phys: [values]} (keep LAST elsewhere).
    Small chunks dodge printk rate-limit; group-by-widx + keep-last absorbs the
    leading throwaway and any dropped reads without cascading."""
    physes=[r[0] for r in regs]
    out={p:[] for p in physes}
    for i in range(0, len(physes), chunk):
        grp=physes[i:i+chunk]
        for attempt in range(2):
            byw=_read_window(sh, grp)
            miss=[p for p in grp if not byw.get(widx(p))]
            for p in grp:
                if byw.get(widx(p)): out[p]=byw[widx(p)]
            if not miss: break          # whole chunk captured
            grp=miss                    # retry only the missing ones
    return out

def pick(vl): return vl[-1] if vl else None   # discard throwaway/dropped first; keep last

def dev_mac():
    subprocess.run(["ping","-c1","-W1",HOST],stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    try:
        o=subprocess.check_output(["ip","neigh","show",HOST],text=True)
        m=re.search(r"lladdr ([0-9a-f:]{17})",o)
        if m: return m.group(1)
    except Exception: pass
    return "f4:f6:47:0f:42:64"   # DATASHEET ONU-MAC fallback

def run_burst(sh, count, mac):
    # Counters are free-running cumulative -> bracket the WHOLE flood: idle
    # snapshot, then run the full ping (egress happens here), then snapshot.
    # No need to race the chunked read against the flood window.
    before=snapshot(sh,COUNTERS)
    tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-l","ether src %s"%mac],
                         stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True)
    time.sleep(0.6)
    fo=subprocess.run(["ping","-c",str(count),"-i","0.05","-W","1",HOST],
                      stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=120).stdout
    time.sleep(0.4); tcp.terminate()
    try: tdo,_=tcp.communicate(timeout=5)
    except Exception: tcp.kill(); tdo=""
    after=snapshot(sh,COUNTERS)
    wire=sum(1 for ln in tdo.splitlines() if mac in ln)
    pm=re.search(r"(\d+) packets transmitted, (\d+) (?:packets )?received",fo)
    return before,after,(pm.group(0) if pm else "?"),wire

def main():
    count=int(sys.argv[1]) if len(sys.argv)>1 else 200
    mac=dev_mac(); print("device wire MAC: %s"%mac,flush=True)
    sh=Sh(); print("CONNECTED to stock (Linux H3600 4.1.25)",flush=True)
    print("\n== CONFIG snapshot (static egress config) ==",flush=True)
    cfg=snapshot(sh,CONFIG)
    cfg_out={}
    for phys,lbl in CONFIG:
        v=pick(cfg[phys]); cfg_out["0x%08x"%phys]={"label":lbl,"value":("0x%08x"%v if v is not None else None)}
        print("  %-20s 0x%08x = %s"%(lbl,phys,"0x%08x"%v if v is not None else "MISS"),flush=True)
    print("\n== EGRESS burst: host ping -c %d ==" % count,flush=True)
    before,during,ping,wire=run_burst(sh,count,mac)
    print("  ping: %s | wire frames (src=%s): %d"%(ping,mac,wire),flush=True)
    print("\n  %-18s %12s %12s %10s"%("stage","before","during","delta"),flush=True)
    ctr_out={}
    for phys,lbl,key in COUNTERS:
        b=pick(before[phys]); a=pick(during[phys])
        if b is None or a is None:
            print("  %-18s %12s %12s   incomplete"%(lbl,b,a),flush=True)
            ctr_out["0x%08x"%phys]={"label":lbl,"before":b,"during":a,"delta":None}; continue
        d=(a-b)&0xffffffff; sd=d if d<0x80000000 else d-0x100000000
        flag="  <==" if sd else ""
        print("  %-18s 0x%08x 0x%08x %+10d%s"%(lbl,b,a,sd,flag),flush=True)
        ctr_out["0x%08x"%phys]={"label":lbl,"before":"0x%08x"%b,"during":"0x%08x"%a,"delta":sd}
    sh.close()
    os.makedirs(OUTDIR,exist_ok=True)
    path=os.path.join(OUTDIR,"tx_egress_oracle_stock_%s.json"%time.strftime("%Y-%m-%d"))
    json.dump({"kind":"stock_tx_egress_oracle","date":time.strftime("%Y-%m-%d %H:%M:%S"),
               "kernel":"4.1.25 stock","dev_mac":mac,"ping_count":count,
               "ping_result":ping,"wire_frames":wire,
               "config":cfg_out,"counters":ctr_out},
              open(path,"w"),indent=2)
    print("\nsaved golden profile -> %s"%path,flush=True)
    print("DONE",flush=True)

if __name__=="__main__": main()
