#!/usr/bin/env python3
# Phase 6 / Stage 2 test: drive the DSA cls_flower offload hook (zx_dsa_cls_flower_add)
# instead of manual register pokes. A `tc flower skip_sw` filter on lan2 ingress with a
# redirect to lan1 fires the hook, which now (Stage 2) installs the CLA+PM recipe.
# We then run the routed flow and watch hw_fwd (0x9234c05c, the POSITIVE HW-forward
# signal) vs hw_trap (0x9234c060). hw_fwd>0 / hw_trap flat = HW L3 FORWARD engaged.
#
# Prereq: hw_rig_setup.py already run (device lan2=172.31.9.1 ingress / lan1=192.168.9.1
# egress; SRC netns on enx2c99 = 172.31.9.50; DST on enx6c70 = 192.168.9.50, iperf3 -s).
import subprocess, re, time
REPO = "/home/ubuntu/Projects/MYSELF/ZTE"; ZCON = "/tmp/zcon.py"; PW = "45788798"
DST_IFACE = "enx6c70cbb68169"

def z(cmd, w=3):
    return subprocess.run(["python3", ZCON, cmd, str(w)],
                          capture_output=True, text=True, cwd=REPO).stdout

def rd(phys):
    # read a chip register via the mainline debugfs poke (peek logged to dmesg/UART)
    o = z("echo %x > /sys/kernel/debug/zx_eth/poke; sleep 1; dmesg | grep 'peek 0x%x' | tail -1" % (phys, phys), 5)
    m = re.findall(r"0x%x = 0x([0-9a-f]+)" % phys, o)
    return int(m[-1], 16) if m else None

def host_flow(sp):
    subprocess.run("echo %s|sudo -S ip netns exec SRC hping3 -S -c 300 -i u3000 -s %d -k -p 5201 192.168.9.50"
                   % (PW, sp), shell=True, capture_output=True, text=True)

if __name__ == "__main__":
    HW_FWD, HW_TRAP, CLA_FWD = 0x9234c05c, 0x9234c060, 0x9238c3c0
    print("=== install tc flower skip_sw filter on lan2 ingress -> redirect lan1 (fires Stage 2 hook) ===")
    print(z("tc qdisc add dev lan2 clsact 2>&1; "
            "tc filter add dev lan2 ingress protocol ip flower skip_sw "
            "ip_proto tcp dst_ip 192.168.9.50 src_ip 172.31.9.50 dst_port 5201 "
            "action mirred egress redirect dev lan1 2>&1; echo RC=$?", 4))
    print("=== dmesg (expect [phase6] FFE armed + recipe ...520 buckets) ===")
    print(z("dmesg | grep phase6 | tail -8", 3))
    print(z("tc -s filter show dev lan2 ingress 2>&1 | head -20", 3))

    f0, t0, c0 = rd(HW_FWD), rd(HW_TRAP), rd(CLA_FWD)
    print("BEFORE: hw_fwd=%s hw_trap=%s cla_fwd=%s" % (hex(f0 or 0), hex(t0 or 0), hex(c0 or 0)))
    host_flow(40000)
    f1, t1, c1 = rd(HW_FWD), rd(HW_TRAP), rd(CLA_FWD)
    print("MATCHED(40000): hw_fwd+%s hw_trap+%s cla_fwd+%s"
          % (f1 - f0 if f1 and f0 else "?", t1 - t0 if t1 and t0 else "?", c1 - c0 if c1 and c0 else "?"))
    print("=> hw_fwd increment (or cla_fwd>0, hw_trap flat) = HW L3 FORWARD ENGAGED via the DSA hook")
