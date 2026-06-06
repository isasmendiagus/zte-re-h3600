#!/usr/bin/env python3
# A-vs-B resolver: does the routed transit packet REACH the CLA hash (B: malformed entry)
# or is it trapped/dropped UPSTREAM (A: ingress gate)? Reads the full CLA counter set
# (decomp tm.c:68134) before/after the flow. The DSA cls_flower hook installs the recipe.
#   cla rx fwd/trp/drp climb  -> packet reached the CLA  => hypothesis B (entry content)
#   cla rx all flat, hw_trap climbs -> trapped upstream  => hypothesis A (ingress gate)
# Prereq: hw_rig_setup.py (lan2=172.31.9.1 ingress / lan1=192.168.9.1 egress; SRC/DST hosts).
import subprocess, re
REPO = "/home/ubuntu/Projects/MYSELF/ZTE"; ZCON = "/tmp/zcon.py"; PW = "45788798"
CT = {  # name -> phys
    "acl_failreq": 0x9238c3b8, "cla_tx_fwd": 0x9238c3c0, "cla_tx_trp": 0x9238c3c4,
    "cla_tx_drp": 0x9238c3c8, "cla_rx_fwd": 0x9238c3cc, "cla_rx_trp": 0x9238c3d0,
    "cla_rx_drp": 0x9238c3d4, "hw_fwd": 0x9234c05c, "hw_trap": 0x9234c060,
}
def z(cmd, w=3):
    return subprocess.run(["python3", ZCON, cmd, str(w)], capture_output=True, text=True, cwd=REPO).stdout
def rd_all():
    cmd = "".join("echo 0x%x > /sys/kernel/debug/zx_eth/poke;" % p for p in CT.values()) + \
          "sleep 1; dmesg | tail -40"
    o = z(cmd, 5); out = {}
    for n, p in CT.items():
        m = re.findall(r"peek 0x%x = 0x([0-9a-f]+)" % p, o)
        out[n] = int(m[-1], 16) if m else None
    return out
def host_flow(sp):
    subprocess.run("echo %s|sudo -S ip netns exec SRC hping3 -S -c 300 -i u3000 -s %d -k -p 5201 192.168.9.50"
                   % (PW, sp), shell=True, capture_output=True, text=True)
if __name__ == "__main__":
    print("=== install tc flower filter (fires DSA hook -> recipe) ===")
    print(z("tc qdisc add dev lan2 clsact 2>/dev/null; tc filter add dev lan2 ingress protocol ip "
            "flower skip_sw ip_proto tcp dst_ip 192.168.9.50 src_ip 172.31.9.50 dst_port 5201 "
            "action mirred egress redirect dev lan1 2>&1; dmesg|grep 'recipe:'|tail -1", 4))
    a = rd_all(); print("BEFORE:", {k: hex(v) if v is not None else "?" for k, v in a.items()})
    host_flow(40000)
    b = rd_all()
    print("\nDELTAS (flow 40000, 300 pkts):")
    for k in CT:
        d = (b[k] - a[k]) if (a[k] is not None and b[k] is not None) else "?"
        print("  %-12s %+s" % (k, d))
    print("\n=> cla_rx_* climb = REACHED CLA (hyp B, entry content). flat + hw_trap up = UPSTREAM gate (hyp A).")
