#!/usr/bin/env python3
"""churn_ab.py — live A/B for the ADM per-CPU-queue PPS policer (churn latch).

Fires a high connection-churn burst (N concurrent short flows via the LAN-local
server, distinct local ports = distinct 5-tuples = a storm of new-flow
first-packets that trap to the CPU data queues q3/q4 before HW-forward installs)
and samples the latch oracles + the ADM drop counters throughout.

Used to prove, live with pokes (before the driver change):
  * baseline (caps OFF): rdrop (0x921da044) climbs, qmg_dn_trap creeps toward
    the 1024 latch, ADM drop counters stay ~0 (nothing policed).
  * caps ON  (poke the recipe): ADM q3/q4/q6 drop counters CLIMB (excess dropped
    at admission = mechanism working), rdrop stays ~flat and qmg_dn_trap stays
    low (ADM-stage drops do NOT charge the OPC/RED latch), flows still served.

Reuses rig.py (rig lifecycle + REPL), ctr.py (latch counters), adm_probe.py
(ADM decode/program). Concurrent-flow launch mirrors regress.py
test_concurrency_race. LAN-local server (modem-independent) per rig.DL_URL_LOCAL.
"""
import argparse
import os
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import rig
import ctr
import adm_probe as adm


def _fire_churn(n, dur, port_base, waves, wave_gap):
    """Fire `waves` waves of `n` concurrent curl flows (distinct local ports per
    flow across all waves) against the LAN-local server; near-zero stagger.
    Returns connected fraction over all flows."""
    connected = total = 0
    port = port_base
    for w in range(waves):
        procs, outs = [], []
        for i in range(n):
            cmd, of = rig._curl_cmd_local(port, dur) if hasattr(rig, "_curl_cmd_local") else _curl_cmd_local(port, dur)
            procs.append(subprocess.Popen(cmd, shell=True))
            outs.append(of)
            port += 1
            time.sleep(0.02)
        for p in procs:
            try:
                p.wait(timeout=dur + 20)
            except subprocess.TimeoutExpired:
                p.kill()
        for of in outs:
            total += 1
            try:
                txt = open(of).read()
                if "http=200" in txt or "http=206" in txt:
                    connected += 1
            except OSError:
                pass
            try:
                os.remove(of)
            except OSError:
                pass
        if w + 1 < waves and wave_gap:
            time.sleep(wave_gap)
    return connected, total


def _curl_cmd_local(lport, dur):
    of = "/tmp/churn_ab_%d.out" % lport
    cmd = (rig.SUDO + rig.NS +
           "curl -s -o /dev/null --max-time %d "
           "-w 'bytes=%%{size_download} http=%%{http_code} t=%%{time_total}\\n' "
           "--local-port %d %s > %s 2>&1" %
           (int(dur), lport, rig.DL_URL_LOCAL, of))
    return cmd, of


def _ping_loss(target):
    out = rig.dev(["ping -c3 -W2 %s | busybox grep loss" % target], wait=5.0)
    import re
    m = re.search(r"(\d+)% packet loss", out)
    return int(m.group(1)) if m else None


def _host_ping_loss(target):
    """Ping FROM the host root ns (needs HOST_NIC / wlo1 in root ns). Used as the
    modem-independent switch-wedge oracle: host->device-lan4."""
    import re
    rc, out = rig.sh("ping -c3 -W2 %s" % target, timeout=12)
    m = re.search(r"(\d+)% packet loss", out)
    return int(m.group(1)) if m else None


def _snap():
    b = ctr.read()
    d = adm.drops()
    return {
        "rdrop": b.get("red_drop"),
        "red_trp_in": b.get("red_trp_in"),
        "red_trp_out": b.get("red_trp_out"),
        "qmg_dn_trap": b.get("qmg_dn_trap"),
        "qmg_up_trap": b.get("qmg_up_trap"),
        "adm_drop": {q: d[q] for q in (3, 4, 6)},
    }


def _pr(tag, s):
    print("[%s] rdrop=%s red_trp_in=%s red_trp_out=%s qmg_dn_trap=%s qmg_up_trap=%s" % (
        tag, s["rdrop"], s["red_trp_in"], s["red_trp_out"], s["qmg_dn_trap"], s["qmg_up_trap"]))
    print("      adm_drop(DN,UP): " + "  ".join("q%d=%s" % (q, s["adm_drop"][q]) for q in (3, 4, 6)))


def main():
    p = argparse.ArgumentParser()
    p.add_argument("arm", choices=["off", "on"], help="off = caps disabled (baseline); on = program policer")
    p.add_argument("-n", type=int, default=30, help="concurrent flows per wave")
    p.add_argument("--waves", type=int, default=2)
    p.add_argument("--dur", type=float, default=4.0, help="per-flow --max-time (s)")
    p.add_argument("--wave-gap", type=float, default=1.0)
    p.add_argument("--pps", type=int, default=2000)
    p.add_argument("--port-base", type=int, default=52000)
    args = p.parse_args()

    print("=== churn A/B arm=%s  n=%d waves=%d dur=%.1f ===" % (args.arm, args.n, args.waves, args.dur))
    print("--- ADM state before ---")
    adm.dump()

    if args.arm == "on":
        print("--- programming policer: q0/q5=8000, q3/q4/q6=%d (both banks) ---" % args.pps)
        adm.program({0: 8000, 5: 8000, 3: args.pps, 4: args.pps, 6: args.pps})
        time.sleep(0.3)
        adm.dump()
    else:
        print("--- caps OFF (data queues unlimited) ---")

    rig.sh(rig.SUDO + rig.NS + "pkill -9 curl 2>/dev/null; true")
    # warm neighbor entries (host sudo + client->gw + device->server)
    rig.sh(rig.SUDO + "true", timeout=15)
    rig.sh(rig.SUDO + rig.NS + "ping -c1 -W2 %s >/dev/null 2>&1; true" % rig.LAN2_GW, timeout=10)
    host, _ = rig.DL_URL_LOCAL.split("//")[1].split(":")[0], None
    rig.dev(["ping -c1 -W2 %s >/dev/null 2>&1; echo done" % host], wait=3.0)

    b0 = _snap()
    _pr("BEFORE", b0)

    port_base = args.port_base + (int(time.time()) % 500)
    t0 = time.time()
    connected, total = _fire_churn(args.n, args.dur, port_base, args.waves, args.wave_gap)
    dt = time.time() - t0

    b1 = _snap()
    _pr("AFTER ", b1)

    alive = "AB_ALIVE" in rig.dev(["echo AB_ALIVE"], wait=3.0)

    # --- CLEAN, MODEM-INDEPENDENT wedge oracle (established live 2026-07-04) ---
    # The churn burst overloads the flaky WAN modem too, so device-side pings to
    # anything on the WAN /24 are confounded. Discriminator: ping device lan4
    # (10.44.66.223) FROM THE HOST (wlo1=10.44.66.133). If the modem is up
    # (host->modem 0%) but host->device-lan4 = 100% loss, the DEVICE's lan4
    # switch datapath is wedged (the 1024 RED trap-queue latch), independent of
    # the modem. If host->modem is also down, it's a modem drop (inconclusive).
    host_to_modem = _host_ping_loss(rig.WAN_GW)
    host_to_lan4 = _host_ping_loss(rig.LAN4_IP)

    def dd(k):
        a, b = b0.get(k), b1.get(k)
        return (b - a) if (a is not None and b is not None) else None

    print("\n=== RESULT arm=%s (%.1fs) ===" % (args.arm, dt))
    print("flows connected: %d/%d (%.0f%%)" % (connected, total, 100.0 * connected / total if total else 0))
    print("delta rdrop        = %s" % dd("rdrop"))
    print("delta red_trp_in   = %s" % dd("red_trp_in"))
    print("delta red_trp_out  = %s" % dd("red_trp_out"))
    print("qmg_dn_trap: %s -> %s" % (b0.get("qmg_dn_trap"), b1.get("qmg_dn_trap")))
    for q in (3, 4, 6):
        a_dn, a_up = b0["adm_drop"][q]
        b_dn, b_up = b1["adm_drop"][q]
        ddn = (b_dn - a_dn) if (a_dn is not None and b_dn is not None) else None
        dup = (b_up - a_up) if (a_up is not None and b_up is not None) else None
        print("adm_drop q%d: DN +%s  UP +%s" % (q, ddn, dup))
    print("device alive (REPL): %s" % alive)
    print("--- MODEM-INDEPENDENT wedge oracle (host-side) ---")
    print("host wlo1 -> modem(%s) loss      = %s%%" % (rig.WAN_GW, host_to_modem))
    print("host wlo1 -> device lan4(%s) loss = %s%%" % (rig.LAN4_IP, host_to_lan4))
    if host_to_modem is not None and host_to_modem >= 100:
        print("VERDICT: INCONCLUSIVE (modem itself down — cannot judge switch)")
    elif host_to_lan4 is not None and host_to_lan4 >= 100:
        print("VERDICT: WEDGED (modem UP but device lan4 datapath dead = switch trap-queue latch)")
    elif host_to_lan4 == 0:
        print("VERDICT: HEALTHY (switch lan4 datapath alive after churn)")
    else:
        print("VERDICT: unclear (host->lan4 loss=%s)" % host_to_lan4)


if __name__ == "__main__":
    main()
