# DSA dup-storm on lan2 — what's fixed, what remains

## UPDATE 2026-05-31 (later): bridge test — root cause is HW FDB LEARNING
Built CONFIG_BRIDGE=y + VLAN_8021Q (kernel had NO bridge support), added a static
`mkbridge` helper (FAILED: built with the eabihf/hardfloat toolchain → SIGILL on
this **no-VFP ARMv7 Cortex-A9**; the CPU `Features` line has no `vfp`/`neon`).
Used busybox `brctl` instead — note it **does the operation but SIGILLs on exit**
(no-VFP quirk), so it must be run on its OWN REPL line (a `;`-chain after it is
aborted by the signal). Created br0, enslaved lan2, moved .99 to br0.

RESULT: DSA bridge offload DID engage — CONFIG_NET_SWITCHDEV=y, and
`port_bridge_join` reprogrammed the isolation live (regport3/lan2 0xf7 → 0x01 =
forward to CPU only; non-bridged ports also recomputed). **But the dup storm
PERSISTS and grows (+71→+189).** So isolation was never the cause (consistent
with the earlier poke result). The HW switch keeps FLOODING because it never
learns the host's MAC: the SW bridge learns in software, but that is NOT reaching
the hardware FDB. Dynamic HW learning is DISABLED in the driver (zx-eth-main.c
:2918 — it was writing the wrong table, PP_BRG/VLAN instead of the sbrag MAC FDB).

### Conclusion: the residual flood needs HW FDB learning (or static HW FDB)
The clean fix is to get the host MAC into the **sbrag MAC FDB** pointing at the
ingress port, so the switch directs unicast instead of flooding. Two routes:
1. Implement correct HW address learning on bridged ports (sbrag FDB, using the
   verified zx_sbrag_add_mac path + zx_sbrg_hash) and wire DSA's switchdev FDB
   sync (port_fdb_add) to it — so bridge-learned MACs program the HW FDB.
2. Or seed a static FDB entry for the peer MAC -> port (test-only).
Until then, lan2 unicast floods/loops in unbridged AND software-bridged modes.
This is a substantial driver+RE item (the FDB MAC byte-order / wrong-table
history makes it delicate). NOT a quick fix.

---


**Date:** 2026-05-31 · Branch: eth-dsa · Context: first end-to-end TX test of the
DSA datapath (host = the build box itself, `enxc8a362e95900` = 192.168.1.50,
cabled to jack3 = MAC2 = lan2).

## Symptom
`ping 192.168.1.99` from the host to the device (IP on lan2) returns the right
replies but with a massive **DUPLICATE storm**: initially +761 dups per 5 pings,
latency escalating to >1000ms. The legacy (non-DSA) path on `main` pings clean.

## Fixed (commit 1c60a4b2c): CPU-egress hairpin
The switch fabric hairpins the CPU's own egress back into the CPU RX path (HW
behaviour — confirmed: isolating the SBRAG forwarding table to CPU<->lan2 only
did NOT stop it). The standalone path drops these (`src MAC == our conduit MAC`)
but the drop was gated `!dsa`. Re-enabling it in DSA mode cut the storm ~97%:
fresh-boot rate +761/5 → +36/10, latency 1026ms → 13ms, 0% loss. **lan2 TX is
thereby confirmed working** (replies reach the host).

## REMAINS: a residual flood-loop that GROWS over time
On a clean boot, no pokes, the dup count climbs across repeated ping rounds:
round1 +36, round2 +129, round3 +270 (per 10 pings). Hard data for one 10-ping
round: **CPU "sw"/lan2 RX +1023, TX +521**, host saw +314 dups. So each echo
**request** (src = host MAC, dst = device MAC) is delivered to the CPU ~50-100×,
and the CPU replies to every copy. The loopback-drop can't catch these (their src
is the host MAC, not ours).

### Experiments that did NOT fix it
- **SBRAG isolation** (PP 0x923883c0+regport*4): poking it to CPU<->lan2-only
  made dups WORSE (+180). Baseline is already `{fe,fd,fb,f7,ef,df,ff,ff}` =
  each port blocks only itself (set by the self_mask loop at zx-eth-main.c:2174 —
  NOT missing, contra one RE pass that only saw the ports-6/7 write at :2449).
- **Downing the uncabled netdevs** (lan0/1/3): no effect (fixed-link likely keeps
  the underlying switch ports forwarding regardless of netdev admin state).

### Static RE (agent) — inconclusive
Stock `tm_pon_pp_brg_initial` (decomp_all_tm.c:43628-43638) sets per-port
`unknown_unicst_fwd=0` + `pt_tls=0` for all ports, then `=1` only for the CPU
port (regport0). Mainline already writes the equivalent CPU-only bitmaps
(0x92388340[31:24]=0x01, 0x92388380=0x01). So the obvious flood-control bits look
correct. No single missing register identified.

### Open mechanism question
For a unicast frame (dst = device MAC, which IS FDB-seeded → CPU) to reach the
CPU 50-100×, it must CIRCULATE in the fabric. Neither known-unicast (FDB→CPU
once) nor unknown-unicast (flood→CPU once) explains 50× delivery. Something
re-injects the frame. Candidates not yet ruled out:
- the cableless `fixed-link` switch ports (lan0/1/3) wrapping TX→RX at the MAC
  level (netdev admin-down doesn't disable the switch MAC; needs HW port_disable
  / greg port_closed @npp+0x4c to truly close them);
- a CPU-port copy/flood setting that re-queues;
- stale/missing FDB causing repeated flood cycles (the documented "RUN1→RUN2
  storm", zx-eth-main.c:2918).

## The likely real answer: BRIDGE the ports
This whole test is the UNBRIDGED standalone-port config (lan2 with a direct IP).
Normal DSA usage bridges the user ports (`ip link add br0 type bridge; ip link
set lan2 master br0; ...`), which enables FDB learning (host MAC learned → all
traffic directed, no flood) and applies zx-dsa's bridge isolation. The residual
flood-loop is plausibly an artifact of the unbridged config and may vanish under
a bridge. **Cannot test here:** this C-init REPL's busybox `ip` has no `bridge`
applet and no `ip link ... master` / `type bridge` support.

## Recommendation / next steps (USER DECISION)
1. Decide the target: bridged operation (the upstream-normal DSA case) vs.
   unbridged standalone ports must work.
2. To test bridging: boot with a fuller userland (iproute2 + bridge, or a small
   initramfs with busybox configured with bridge), create br0, enslave lan2, and
   re-ping — expect the dup storm to vanish once the host MAC is learned.
3. If unbridged must work: deeper fabric RE on loop-prevention — specifically
   HW-close the linkless ports (greg port_closed @npp+0x4c) so fixed-link doesn't
   leave them looping, and trace where a unicast-to-CPU gets re-injected.

## Status of lan2 (honest)
- RX demux: ✅ VERIFIED.
- TX to wire: ✅ VERIFIED (replies reach the host).
- Clean bidirectional unicast: ❌ NOT yet — residual flood-loop in unbridged mode
  (dups grow over time). Catastrophic hairpin storm is fixed; this is the smaller,
  separate, pre-existing flood/FDB issue.

## UPDATE 2026-05-31 (final, this session): config matches stock — it's the DSA datapath
Fixed the SBRAG FDB write protocol (commit c3fa24a0a: BUSY=wait-for-idle, write
order D2→D1→D0 then CMD; D2=BIT(regport) bitmap). Entries now verifiably store
(readback round-trips). BUT seeding host-MAC→lan2 + device-MAC→CPU still does NOT
stop the dup-loop.

Then diffed EVERY forwarding register live (mainline) — ALL already match stock:
isolation {fe,fd,fb,f7,ef,df,ff,ff}, PP[0x8004]=040200ff (age_en SET),
PP[0x8180]=04, PP[0x8184]=01, PP[0x8188]=00211b00, PP[0x8340]=015555ff
(unknown-unicast-fwd = CPU only), PM 0x921e0054=c0, SPA 0x921d407c=01. So the
switch CONFIG is correct.

Key signals:
- `tm_rx_loopback_drops = 0` (loopback-drop never fires now) while `tm_rx_count`
  climbs to 20k+. So the over-delivered frames are the echo REQUESTS (src = host
  MAC, dst = our MAC), NOT reply-hairpins. The CPU receives each request ~50-100×
  and replies to each → the host sees the dup storm.
- The LEGACY `sw` path (non-DSA, direct IP on the conduit) pings CLEAN with the
  SAME switch config. Only the DSA `lan2` path loops.

⇒ ROOT CAUSE IS DSA-DATAPATH-SPECIFIC, not the switch registers. Something in the
conduit RX/TX hooks or the tagger causes the switch to re-deliver a CPU-bound
unicast many times on the DSA path but not the legacy path. Two automated RE
agents gave UNRELIABLE analysis here (repeated regport-vs-logical indexing errors;
claimed "missing" registers that are already set) — do not trust them; verify live.

### Next step (focused, needs methodical RE — likely a separate session)
Compare the DSA vs legacy CPU datapath directly: boot stock with kprobe on the
CPU RX/forwarding path (or instrument mainline) to see why a request is delivered
to the CPU once on legacy but N× on DSA. Suspects: the conduit MTU bump (1504
"DSA overhead"), the tag prepend/strip altering frame handling, BMU buffer reuse,
or a CPU-copy/mirror that the DSA conduit enables. The fix is in the datapath
code, NOT a switch register.

### What IS fixed/verified this session
- CPU-egress hairpin storm: FIXED (commit 1c60a4b2c) — cut the worst of it.
- Conduit selection idm0→sw: FIXED (a4508c981) — RX demux verified.
- SBRAG FDB write protocol: FIXED + verified by readback (c3fa24a0a).
- lan2 RX ✅ and TX ✅ both verified on HW. Clean bidirectional unicast ❌
  (residual DSA-datapath dup-loop, root cause now correctly localized).

## UPDATE 2026-05-31 (leading lead): egress replication at smac2 + BMU free failing
debugfs pipeline_stats + stats under DSA-path ping:
- `smac2 TX_pkts = 467826` while CPU `tm_tx_count = 6260` → the egress MAC for the
  host port physically transmits ~75x more than the CPU injects. So the dup storm
  is EGRESS-SIDE REPLICATION (DSCH/SCH/SOPC → smac2), not RX over-delivery.
  (smac2 RX_pkts=302 is small → frames are not looping at ingress.)
- `tm_bmu_free_fail = 25473` vs `tm_bmu_free_ok = 4274` (~85% fail), `bmu_free_credit
  = 0`. The BMU buffer-free path is failing almost always. If TX/egress BP buffers
  aren't recycled correctly, the egress scheduler may re-send/replicate them.
- Only PHY[2] link=1 (host); PHY 0/1/3 link=0. MAC2 ctrl=00bb6003 en=80000001 (live).
- All TOPCRM/PP/PM/SPA regs match stock (re-confirmed in this dump).

⇒ NEXT (focused, this is the real lead): investigate (a) why smac2 egresses ~75x the
CPU TX — the DSCH/SCH/SOPC egress path replicating CPU frames on the DSA path but
not the legacy path; and (b) the BMU free-fail (zx_bmu_free_bp returning fail 85%
of the time) — a TX/egress BP recycle bug would explain re-send/replication. Compare
the egress + BMU-free behaviour DSA-path vs legacy-path (stock kprobe on
pp_bmu_free_bp / the DSCH egress, or mainline instrumentation of zx_bmu_free_bp
return + per-frame egress count). The fix is in the egress/BMU datapath.
