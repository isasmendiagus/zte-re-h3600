#!/usr/bin/env python3
# Read the egress-stage pipeline counters via the poke debugfs (output -> dmesg).
# Prints a dict of {name: value}. Tracks the LAST peek of each addr in dmesg.
import socket, time, select, sys, re

HOST, PORT = "127.0.0.1", 9999
CTRS = [
    ("cla_dn_fwd", 0x9238c3cc, True),   # DN forward verdict (lo16)
    ("cla_dn_drop",0x9238c3c8, True),   # CLA DN drop
    ("cla_copy",   0x9238c3d8, True),   # CLA copy-to-CPU
    ("qmg_dn_sw",  0x9234c044, False),  # QMG DN sw_fwd
    ("qmg_dn_hw",  0x9234c048, False),  # QMG DN hw_fwd (switch HW-forward enqueue)
    ("qmg_dn_trap",0x9234c04c, False),  # QMG DN hw_trap-to-CPU (saturates 1024)
    ("qmg_up_sw",  0x9234c054, False),  # QMG UP sw_fwd
    ("qmg_up_hw",  0x9234c058, False),  # QMG UP hw_fwd
    ("qmg_up_trap",0x9234c05c, False),  # QMG UP hw_trap-to-CPU
    ("pp_drop",    0x921da040, False),  # PP drop
    ("red_drop",   0x921da044, False),  # RED drop
    ("dsch_drop",  0x921da04c, False),  # DSCH drop
    ("sadm_pass",  0x921c4200, False),  # SADM pass
    ("sadm_drop",  0x921c4208, False),  # SADM drop
    ("send2smac2", 0x921d9164, False),  # SOPC dequeue -> MAC2 (host port)
    ("mac2_tx",    0x92280718, False),  # MAC2 physical TX frames
    # DN pipeline per-stage (stock tm_switch_statistics_rx decode, phys=0x92000000+widx*4)
    ("red_fwd_in", 0x92344204, False),  # RED fwd in  (0xd1081)
    ("red_fwd_out",0x92344210, False),  # RED fwd out (0xd1084)
    ("red_trp_in", 0x92344208, False),  # RED trap in (0xd1082)
    ("red_trp_out",0x92344214, False),  # RED trap out(0xd1085)
    ("pm_recv",    0x9239c088, True),   # PM recv lo16 (0xe7022)
    ("pm_send",    0x9239c080, False),  # PM send (0xe7020, hi16)
    ("pm_fwdtrp",  0x9239c0a0, False),  # PM fwd hi16 / trap lo16 (0xe7028)
    ("dpa_fdct",   0x9239810c, False),  # DPA fwd/drp/cpy/trp bytes (0xe6043)
    ("cla_dn_trap",0x9238c3d0, True),   # CLA dn trap pkts (0xe30f4)
    ("acl_fail",   0x9238c3b8, True),   # CLA lookup-miss (LOOK_UP_MISS) lo16
    ("dsch_inq",   0x92354200, "b3"),   # DSCH in-que pkts (0xd5080 byte3)
    ("dsch_outq",  0x923541fc, "b1"),   # DSCH out-que pkts (0xd507f byte2)
]

def zc(cmds, wait=2.5):
    s = socket.create_connection((HOST, PORT), timeout=6); s.setblocking(False)
    t0 = time.time()
    while time.time() - t0 < 0.2:
        r, _, _ = select.select([s], [], [], 0.05)
        if r:
            try: s.recv(65536)
            except BlockingIOError: pass
    for c in cmds:
        s.sendall((c + "\n").encode())
        time.sleep(0.05)
    buf = bytearray(); last = time.time()
    while time.time() - last < wait and time.time() - t0 < 20:
        r, _, _ = select.select([s], [], [], 0.2)
        if r:
            try:
                d = s.recv(65536)
                if d: buf += d; last = time.time()
            except BlockingIOError: pass
    s.close()
    return buf.decode(errors="replace")

def read():
    cmds = []
    for _, addr, _ in CTRS:
        cmds.append("echo %08x > /sys/kernel/debug/zx_eth/poke" % addr)
    # [regress.py/first-run fix 2026-07-04] tail depth MUST exceed len(CTRS)
    # (28 today) or the earliest pokes' "peek 0x..." lines fall off the tail
    # and read() silently returns None for them. This was hardcoded at 20 <
    # 28 -> the first 8 CTRS entries (cla_dn_fwd, cla_dn_drop, cla_copy,
    # qmg_dn_sw, qmg_dn_hw, qmg_dn_trap, qmg_up_sw, qmg_up_hw) ALWAYS read
    # back None, every call, regardless of driver behavior -- confirmed live
    # (rig.py download --counters showed the identical "?" set every time).
    # This made regress.py's baseline_download hit-rate check (which needs
    # cla_dn_fwd) spuriously fail/None. Size the tail to the list + margin.
    cmds.append("dmesg | grep -a 'peek 0x' | tail -%d" % (len(CTRS) + 10))
    out = zc(cmds)
    vals = {}
    for name, addr, lo16 in CTRS:
        pat = re.compile(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, re.I)
        m = pat.findall(out)
        if m:
            v = int(m[-1], 16)
            if lo16 is True: v &= 0xffff
            elif lo16 == "b3": v = (v >> 24) & 0xff
            elif lo16 == "b2": v = (v >> 16) & 0xff
            elif lo16 == "b1": v = (v >> 8) & 0xff
            vals[name] = v
        else:
            vals[name] = None
    return vals

if __name__ == "__main__":
    v = read()
    print(" ".join("%s=%s" % (k, ("0x%x" % vv if vv is not None else "?")) for k, vv in v.items()))
