#!/usr/bin/env python3
"""DECISIVE test of lead #2 (DN tcont shaper credit) on the live MAINLINE
kernel — no rebuild. Drives the driver debugfs over the UART-bridge REPL (:9999).

Hypothesis: mainline zx_sch_init programs only the UP shaper (RAMID 2/3/5/6),
leaving the DN tcont shaper (RAMID 0xe fill / 0xf cap) at 0 = zero credit, so
the downstream scheduler never dequeues a CPU->LAN frame toward SOPC (frame
passes QMG, not dropped, never egresses). Stock-live DN tcont values (captured
2026-05-29): fill=0x1f4000, cap=0x30d40.

Test: read baseline egress witnesses -> read mainline DN tcont (expect 0) ->
poke DN tcont to stock values for units 0..7 via the SCH indirect WRITE protocol
(same as zx_sch_indirect_write: CMD then DATA) -> txtest N -> re-read witnesses +
count host wire frames. If SOPC send2smac2 / MAC2 TX climb and frames hit the
wire => lead #2 CONFIRMED, fix = add DN tcont to zx_sch_init.

REPL: one busybox applet per line; `sh -c "..."` for redirects. poke/memdump/
txtest are the driver debug hooks (DEBUG build). Reads via memdump (phys peek).
"""
import socket, time, re, sys, subprocess

BRIDGE=("127.0.0.1",9999)
HOST_NIC="enxc8a362e95900"
DEV_MAC="f4:f6:47:0f:42:64"

# SCH indirect ports (absolute phys; tm_base 0x92340000)
SCH_CMD=0x92354014; SCH_DATA=0x9235401c
RAMID_DN_FILL=0xe; RAMID_DN_CAP=0xf
DN_FILL=0x1f4000; DN_CAP=0x30d40        # stock-live values

# egress witnesses (absolute phys)
W = [(0x9234c044,"QMG sw_fwd"), (0x921d9164,"SOPC send2smac2"),
     (0x92280718,"MAC2 TX_frames"), (0x92280714,"MAC2 TX_bytes"),
     (0x921da04c,"drop_DSCH"), (0x92280780,"MAC2 RX_frames")]

class Repl:
    def __init__(self):
        self.s=socket.create_connection(BRIDGE,timeout=10); self.s.settimeout(0.4)
        self._drain(0.5)
    def _drain(self,t):
        buf=b''; end=time.time()+t
        while time.time()<end:
            try: d=self.s.recv(65536)
            except socket.timeout: d=b''
            if d: buf+=d; end=time.time()+t
            else: time.sleep(0.03)
        return buf.decode(errors='replace')
    def cmd(self,line,settle=0.6):
        self.s.sendall(line.encode()+b"\n"); return self._drain(settle)
    def close(self): self.s.close()

def memrd(r, phys):
    """memdump <hexphys> 4 -> parse the 32-bit word."""
    out=r.cmd("memdump %x 4"%phys, 0.5)
    # accept "<phys>: xxxxxxxx" or bare hex; grab last 8-hex token
    toks=re.findall(r"\b([0-9a-fA-F]{8})\b", out)
    return int(toks[-1],16) if toks else None

def poke(r, phys, val):
    r.cmd('sh -c "echo \'%x %x\' > /sys/kernel/debug/zx_eth/poke"'%(phys,val), 0.4)

def sch_dn_write(r, ramid, addr, val):
    poke(r, SCH_CMD, (addr & 0x1ff) | ((ramid & 0xf) << 22))   # indRwEn=0 => write
    poke(r, SCH_DATA, val)

def sch_dn_read(r, ramid, addr):
    poke(r, SCH_CMD, (addr & 0x1ff) | ((ramid & 0xf) << 22) | (1<<27))  # read-prefetch
    return memrd(r, SCH_DATA)

def witnesses(r):
    return {lbl: memrd(r,phys) for phys,lbl in W}

def show(tag, d):
    print("  [%s] %s"%(tag, "  ".join("%s=%s"%(l,("0x%x"%d[l] if d[l] is not None else "??")) for _,l in W)), flush=True)

def main():
    n=int(sys.argv[1]) if len(sys.argv)>1 else 16
    r=Repl(); print("connected :9999",flush=True)
    print(r.cmd("mount -t debugfs none /sys/kernel/debug 2>/dev/null; echo MOUNTED",0.6).strip()[-40:],flush=True)
    print("\n== mainline DN tcont BEFORE (expect ~0) ==",flush=True)
    for u in range(2):
        print("  unit%d fill(0xe)=%s cap(0xf)=%s"%(u,
              ("0x%x"%(sch_dn_read(r,RAMID_DN_FILL,u) or 0)),
              ("0x%x"%(sch_dn_read(r,RAMID_DN_CAP,u) or 0))),flush=True)
    before=witnesses(r); show("before", before)

    print("\n== POKE DN tcont -> stock values (units 0..7) ==",flush=True)
    for u in range(8):
        sch_dn_write(r, RAMID_DN_FILL, u, DN_FILL)
        sch_dn_write(r, RAMID_DN_CAP,  u, DN_CAP)
    # verify a couple landed
    print("  readback unit0 fill=0x%x cap=0x%x"%((sch_dn_read(r,RAMID_DN_FILL,0) or 0),
                                                  (sch_dn_read(r,RAMID_DN_CAP,0) or 0)),flush=True)

    print("\n== txtest %d (inject known 0x88b5 frames) + host tcpdump =="%n,flush=True)
    tcp=subprocess.Popen(["tcpdump","-i",HOST_NIC,"-nne","-l","ether proto 0x88b5 or ether src %s"%DEV_MAC],
                         stdout=subprocess.PIPE,stderr=subprocess.DEVNULL,text=True)
    time.sleep(0.6)
    r.cmd('sh -c "echo %d > /sys/kernel/debug/zx_eth/txtest"'%n, 1.2)
    time.sleep(1.0); tcp.terminate()
    try: tdo,_=tcp.communicate(timeout=5)
    except Exception: tcp.kill(); tdo=""
    wire88=sum(1 for ln in tdo.splitlines() if "88b5" in ln.lower())
    wiredev=sum(1 for ln in tdo.splitlines() if DEV_MAC in ln)
    after=witnesses(r); show("after ", after)
    print("\n  wire frames: ethertype-0x88b5=%d  src-%s=%d"%(wire88,DEV_MAC,wiredev),flush=True)

    print("\n----- VERDICT -----",flush=True)
    def d(l):
        b=before[l]; a=after[l]
        return (a-b)&0xffffffff if (a is not None and b is not None) else None
    sm=d("SOPC send2smac2"); tx=d("MAC2 TX_frames"); sw=d("QMG sw_fwd"); dd=d("drop_DSCH")
    print("  QMG sw_fwd d=%s | SOPC send2smac2 d=%s | MAC2 TX d=%s | drop_DSCH d=%s"%(sw,sm,tx,dd),flush=True)
    if (sm or 0)>0 or (tx or 0)>0 or wire88>0:
        print("  ==> CONFIRMED: DN tcont credit was the gate (egress appeared).",flush=True)
    else:
        print("  ==> NOT confirmed by DN tcont alone (sw_fwd d=%s). Move to lead #1 (MAC init-order wipe)."%sw,flush=True)
    r.close()

if __name__=="__main__": main()
