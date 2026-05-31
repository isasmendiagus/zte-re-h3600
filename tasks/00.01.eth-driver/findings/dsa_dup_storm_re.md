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

## UPDATE 2026-05-31 (ROOT-CAUSE CANDIDATE): BMU free-credit starved (1 vs stock 34)
Per-ping amplification measured precisely (1 ping): smac2_rx +2 (host's request
physically arrives) -> cpu_rx +275 (delivered to CPU ~137x) -> cpu_tx +176
(replies) -> smac2_tx +14382 (egressed ~82x the CPU replies). TWO compounding
amplifications in the DSA datapath.

Smoking gun: `tm[0x80dc] = 0x40000409` → free-credit field bits[8:3] = **1**.
The driver's own comment (zx_bmu_free_bp) documents the STOCK value as
`tm[0x80dc]=0x...111` → bits[8:3] = **34**. So the HW grants only 1 BMU free-credit
vs stock's 34. zx_bmu_free_bp frees 1 buffer per credit; with credit≈1 and a slow
HW replenish, 85% of frees time out (tm_bmu_free_fail=25473 vs ok=4274). Un-freed
BMU buffers get re-DMA'd by HW with their STALE frame contents → the same frame is
re-delivered to the CPU (137x RX) AND re-egressed (82x TX). It only runs away on
the DSA path because that path generates the buffer pressure; the legacy path's
light load stays under the 1-credit ceiling, so it pings clean.

### THE FIX (next): make the BMU grant ~34 free-credit like stock
tm[0x80dc] is a STATUS reg reflecting the BMU pool/free-FIFO config. mainline's
zx_tm_bmu_init leaves it reporting 1. Compare zx_tm_bmu_init / zx_tm_bmu_enable /
the BMU pool sizing (TM[0x8004]=0x0104c040, TM[0x80d0..0x80e0]) against stock's
pp_bmu_init to find the missing/wrong BMU config that sets the free-credit depth.
Live now: tm[0x80d0]=07d00000 tm[0x80d4]=ffffff00 tm[0x80d8]=ffffe000
tm[0x80e0]=00000fb1 tm[0x8004]=0104c040 tm[0x8000]=1. This is the concrete,
stock-divergent register to fix — verify by re-reading tm[0x80dc] bits[8:3]≈34 and
re-pinging (expect dups→0).

## UPDATE 2026-05-31 (correction): BMU credit is a SYMPTOM, not the static root
Poke test: tm[0x80dc] is READ-ONLY HW status — poking 0x50000111 didn't stick
(reads back 0x40000401 / 0x40000511). And it FLUCTUATES 0..34 dynamically
(0x...511 → bits[8:3]=34 at one sample), NOT stuck at 1 (the earlier "1" was an
idle snapshot). So the BMU free-credit is overwhelmed by the amplification under
load, not statically misconfigured — a zx_tm_bmu_init rebuild likely won't fix it.

Refined model (positive-feedback runaway):
1. SEED: at FRESH boot, ~3.6 dup-copies/ping (the documented mild "1-3 copies"
   flood, line 713). Manageable.
2. FEEDBACK: the amplified RX outruns the BMU free path → free_fail → buffers not
   recycled → HW re-DMAs stale buffers → MORE re-delivery/re-egress → MORE free
   pressure → runaway. Dups grow over the session (36 → 1000+); a fresh boot
   resets to ~36. So the GROWTH is the buffer-leak feedback; the SEED is the
   baseline mild flood.

⇒ Real fix priority: kill the SEED (the baseline ~3.6-copies/ping flood on the DSA
egress path) — once each reply egresses exactly once, the free path keeps up and
the feedback can't run away. Tools that CAN test without rebuild are exhausted
(isolation/FDB/port-close all read-only-confirmed or ineffective; tm[0x80dc]
read-only). The decisive next step is the stock+kprobe comparison of the EGRESS
path (DSCH/SCH/SOPC send2smac) DSA-vs-legacy to find why one CPU reply egresses
~3.6x (fresh) on the DSA path but 1x on legacy — that is a rebuild/instrumentation
or stock-trace task, not a poke.

## UPDATE 2026-05-31 (GOLDEN stock reference — egress replication CONFIRMED)
Re-flashed REAL stock to Slot A (flash.py both, ext/partitions/06_kernel1.bin +
07_rootfs.bin). Stock pings clean 10/10 0-dup 11.6ms. (Stock self-reboots every
~2-3 min on the bench — watchdog, no PON/WAN uplink; reads are NOT the cause;
work in the ~140s+ windows.)

reg_diff.py on clean stock, 600-ping flood, IDLE->DURING deltas:
  QMG sw_fwd (0x9234c044): +193    MAC2 TX-OK (0x92280718): +217   (~0.3-0.36/ping)
  BMU/IDM regs (0x921c8000..801c): FLAT under load.
vs MAINLINE-DSA: smac2 TX +14382 for ONE ping (CPU tm_tx_count +176 → ~82x).
⇒ EGRESS REPLICATION CONFIRMED: stock egresses <=1 frame/ping; mainline replicates
~14000x/ping at MAC2. The bug is in mainline's EGRESS DATAPATH (TM/DSCH/SCH/SOPC +
the BMU free starvation feedback), NOT the switch config (matches stock).
PRIME SUSPECT: mainline DUAL-KICK (zx_sw_xmit kicks BOTH TM[0x10054] UP + TM[0x10064]
DN rings per TX, same txdesc base — see zx-eth-main.c:3434). Needed for egress to
work at all (single-kick=100% loss) but may re-inject/replay frames. Next: compare
stock's CPU-egress inject (QMG sw_fwd, software-forward, no DMA ring per egress
notes) vs mainline's dual-ring DMA inject; test single-kick / ring-cleanup variants.
NOTE: reg_diff mislabels 0x921c8000 as BMU; it's IDM CTRL (=0x020f6766).

## UPDATE 2026-05-31 (ROOT CAUSE FULLY RE'd via stock egress-inject registers)
Captured stock egress-inject path idle-vs-ping (400 pings) via /bin/fpga -r:
  TM[0x10054] UP kick   : FLAT 0        TM[0x10058] UP count : FLAT 0
  TM[0x10064] DN kick   : FLAT 1        TM[0x10068] DN count : FLAT 1
  QMG sw_fwd (0x9234c044): +151   SOPC send2smac2 (0x921d9164): +156   MAC2 TX-OK (0x92280718): +161
⇒ STOCK injects CPU egress straight into QMG sw_fwd (software-forward); the TM
UP and DN DMA rings are UNUSED (flat). QMG->SOPC->MAC2 run 1:1 — no replication.
MAINLINE instead injects via the TM UP ring + DUAL-KICKS the DN ring per frame
(zx_sw_xmit, TM[0x10054]+TM[0x10064], same txdesc base) → that DMA-ring path
REPLAYS/replicates ~82x at MAC2 = the dup storm. This is the FULL root cause and
matches the old egress note ("stock uses NO DMA ring — sw-forwards to QMG sw_fwd").

### FIX DIRECTION (mainline-side, next session)
Option A (match stock, correct): inject CPU egress into QMG sw_fwd directly (no TM
DMA ring) — RE the stock sw_fwd inject (decomp pon_tm_data_raw_send / the sw_fwd
write) and replicate it; retire the dual-kick UP/DN ring path.
Option B (patch the ring): make the ring send EXACTLY ONCE — single-kick + proper
tx desc ownership/advance + don't leave the DN ring re-fetching. The dual-kick was
added because single-kick gave 100% loss ("fetched-but-not-drained"); the real fix
is correct desc ownership/drain, not dual-kick. Verify: MAC2 TX delta == ping count.

## CORRECTION 2026-05-31 (decomp+kotrace agent): NOT sw_fwd — it's DN-ring dual-kick
My "stock uses QMG sw_fwd, no DMA ring" conclusion was WRONG (confounded by:
TM ring regs are WRITE-ONLY doorbells reading back constant 1 → "flat" ≠ unused;
+ base-gotcha). DEFINITIVE (decomp + live kotrace, fully cited in agent output):
- 0x9234c044 (QMG sw_fwd) = READ-ONLY statistics counter, not an inject reg.
- Stock TX = pdt_ethdrv_send → pon_tm_net_tx → pon_tm_data_raw_send(dir=1) →
  soft_insert_tx_1desc(dir=1): the ONLY per-frame write is **0x92350064 = 1**
  (DN-ring kick, ONE descriptor). desc[0]=0x80, desc[2] bits[9:4]=((port+0x28)&0x3f),
  desc[0xb]|=0x20 VALID (LEFT SET — HW owns desc), reclaim via 0x92350068 consume.
  DN ring base = tm_base+0x10060; cursor is SW (net_txq+0xc mod 0x400).
- Single-kick "lost" on mainline ONLY because the DN-tcont SHAPER CREDIT (SCH
  RAMID 0xe/0xf via 0x9235401c/0x92354014) is never programmed (cspd does it on
  stock) → DSCH can't dequeue. Dual-kick brute-forced past that.
MAINLINE BUG (zx_sw_xmit zx-eth-main.c:3441-3489): (1) dual-kick UP 0x10054 + DN
0x10064 off SHARED desc base → frame presented 2x; (2) clears VALID post-kick →
fights async HW; (3) DN shaper credit never set. → ~82x MAC2 replication.

### FIX (concrete, agent recipe; HIGH conf on ring/kick/VALID, MED on shaper):
1. desc[0]=0x80 (DN marker, not 0xc9). 2. kick ONLY 0x10064=1 (drop the UP kick).
3. do NOT clear desc VALID after kick. 4. reclaim via 0x10068 consume counter.
5. program DN-tcont shaper credit (RAMID 0xe fill @0x9235401c=0x186A00 +
   0x92354014=0x03800000|unit; RAMID 0xf cap @0x9235401c=0x030D40 +
   0x92354014=0x03C00000|unit; unit 3≈MAC2) so single-kick drains.
VERIFY: MAC2 TX delta == ping count (no dups). Full citations in session log /
the RE agent output.

## UPDATE 2026-05-31 (TX-fix attempt — replication is RING-DRAIN, not kick): 
Implemented single-kick + DN-tcont shaper credit (RAMID 0xe/0xf). Results on HW:
- single DN-kick (desc[0]=0x80): DN ring QUEUES but NEVER DRAINS — smac2 TX=0,
  TM[0x10068] high16 grows / low16(consumed) flat, 100% loss. DN-tcont shaper
  credit did NOT unblock it. (So DN is not mainline's working drain path.)
- single UP-kick (desc[0]=0xc9): DRAINS (10/10 rx) but STILL replicates ~790x/ping
  (smac2 TX +7912 / 10 pings), and dups GROW across rounds (+48 → +193).
⇒ The replication is NOT the dual-kick and NOT DN-vs-UP. ROOT: the HW UP ring
RE-SCANS accumulated VALID TX descriptors. zx_sw_xmit writes each desc with VALID
(desc[11] bit5) SET and NEVER clears it after the HW consumes it; descs pile up in
the 1024-entry ring and the HW re-emits every VALID one each cycle → replication
that GROWS with the number of un-reclaimed descs. (Iter-33 had removed the
post-kick VALID clear because clearing it *immediately* made the DN ring skip; the
correct fix is clear-on-CONSUME, not immediate and not never.)

### REAL FIX (next): proper TX-ring reclaim / consumer-cursor
Implement a TX reclaim: read the UP consume counter (TM[0x10058] low16), and for
each desc the HW has consumed, CLEAR its VALID bit (desc[11] &= ~0x20) so it is not
re-emitted. Maintain SW head/tail; reclaim from tail up to consumed in NAPI and/or
at the start of the next xmit. Verify smac2 TX delta == ping count. Open question:
the ~790x/ping suggests the HW re-emits a desc many times BEFORE any reclaim runs —
may also need the ring producer/consumer/size registers set so HW stops at the
produced count (kick value = count). Inspect TM ring ptr/size regs vs stock.
NOTE: committed eth-dsa code is still the dual-kick; the single-UP edit is the
current (uncommitted) experiment in the booted image.

## UPDATE 2026-05-31 (NEGATIVE RESULT — TX-ring hypothesis is WRONG)
Tested split-base (DN=dndesc_dma, distinct from UP) + single-UP-kick on HW:
- STILL replicates: smac2 TX +9776 / 10 pings (~977x), dups GROW (+60→+198→+288).
- lan2 RX +372/10 (~37x over-delivery), lan2 TX +98, smac2 TX +9776.
⇒ Splitting the ring base did NOT help. Combined with the hard fact that **`main`
(no DSA) is CLEAN with the SAME TX-ring code (shared base + dual-kick + VALID never
cleared)**, this RULES OUT the TX-ring config as the cause. The agent's "shared
base / consumer-cursor" theory and my single-kick theory are both DISPROVEN by HW.
Reverted the experiments (back to committed dual-kick).

### TRUE state of the problem (honest):
The dup storm is **DSA-path-specific** — `main`/legacy is clean, eth-dsa storms,
identical TX ring. There are TWO DSA-specific amplifications, mechanism uncracked:
  (a) RX over-delivery: lan2 RX ~37x/ping (the CPU receives each REQUEST ~37x).
  (b) egress replication: smac2 TX ~10-100x the conduit lan2 TX.
Neither is explained by the TX ring (main shares it, clean). Suspects not yet
isolated: zx-dsa's setup() changing switch forwarding vs the conduit RX/TX tag
hooks vs the lanN ports' existence changing flood/forwarding. loopback_drops=0
(over-delivered frames are src=host REQUESTS, not reply-hairpins).

### NEXT ANGLE (need a different approach — blind ring tweaks are exhausted):
1. Bisect DSA-enable: boot eth-dsa with `&switch_dsa` DISABLED (= legacy on the same
   kernel). If clean → the bug is zx-dsa setup() or the conduit DSA hooks; then
   neutralize the conduit RX/TX tag hooks (keep lanN) to split setup-vs-datapath.
2. Live-diff eth-dsa(dirty) vs main(clean) switch FORWARDING regs (QMG/flood/FDB/
   isolation) — find what zx-dsa's setup() changed that main doesn't.
3. Instrument zx_tm_napi_poll: log BMU/desc index per RX delivery — is the SAME
   desc/BP re-processed (driver) or are there 37 distinct deliveries (switch)?

## UPDATE 2026-05-31 (localized to QMG sw_fwd / RX over-delivery): 
eth-dsa live deltas, 10 pings: QMG sw_fwd +370, smac2 TX +370 (EQUAL = 37x/ping),
drop_DSCH +0, hw_fwd +0, drop_RED +1. So egress is NOT separately replicating —
QMG sw-forwards the request to the CPU 37x/ping, the CPU replies to each, each
egresses 1:1 (no DSCH drop). CORE BUG = the RX over-delivery (request reaches CPU
~37x), a QMG/fabric behaviour on the DSA path (stock/main = 1x, same switch cfg).
Mechanism (why the request is sw_fwd'd 37x on DSA but 1x on legacy) still uncracked.
Build-speed fixed: disabled CONFIG_STACKPROTECTOR (parent) so GCC_PLUGINS/PER_TASK
no longer drift on olddefconfig → builds are now incremental (skip the config step).
NEXT BISECT (now fast): (1) boot with &switch_dsa disabled → confirm clean (sanity);
(2) keep DSA but no-op zx-dsa setup() → is it the switch setup or the conduit hooks;
(3) neutralize the conduit RX tag-prepend path → does the 37x RX over-delivery stop.

## UPDATE 2026-05-31 (single-ping BPDUMP — replication is at the CPU RX QUEUE / CLA):
Disabling lan0/1/3 (cableless fixed-link ports) did NOT help (+36→+266) — ruled out.
no set_rx_mode in driver — promisc ruled out. (8 hypotheses now disproven: FDB,
isolation, flood-cfg, BMU, TX-ring, greg-port-ops, cableless-ports, promisc.)

Single-ping (-c1) BPDUMP — the SHARPEST localization: each CPU-bound frame is
delivered MULTIPLE times, as IDENTICAL copies, across MULTIPLE CPU RX queues:
  - ICMP echo request (host→device): delivered on q=4 idx=0 AND q=5 idx=0.
  - host's ARP reply: delivered ~5x across q=4 (idx 0,1,2) and q=5 (idx 0 repeatedly).
  - all ingress=2, identical payloads.
⇒ NOT a fabric L2 loop and NOT modifying — the switch CLA/queue-classifier COPIES
each CPU-bound frame to MULTIPLE CPU RX queues (q4+q5...), and the driver's napi
delivers every copy. q=5 idx stays 0 (re-read same desc); q=4 idx cycles. This is
the DSA-path-specific replicator. main/legacy (same napi) is clean → the DSA enable
changes the CLA/CPU-queue classification so frames are copied to multiple queues.
NEXT: compare the CLA / CPU-queue classification config (PP_CLA + the per-queue
CPU-copy/trap mask) eth-dsa-vs-main/stock; find why CPU-bound frames hit multiple
queues. Likely a CLA "copy to all CPU queues" or trap-mask misconfig triggered by
DSA. (Build-speed fixed; lan0/1/3 disabled + the no-op port-op bisect reverted.)

## UPDATE 2026-05-31 (DEFINITIVE: legacy vs DSA single-ping comparison)
Booted the SAME kernel with &switch_dsa DISABLED (legacy) and single-ping BPDUMP:
  LEGACY:  tm_rx_count=5, ICMP request delivered q4 ONLY (1x), host sees 1 reply
           (0 dups, CLEAN), loopback-drop fires (catches the device's own reply).
  DSA:     tm_rx_count=15, ICMP request delivered q4 AND q5 (2x+), host sees 37 (storm).
⇒ CONFIRMED ROOT: DSA-enable makes the switch/CLA COPY each CPU-bound frame to
MULTIPLE CPU RX queues (q4+q5...); the driver's napi (rx_head[0..7]) delivers every
copy → the dup storm. Legacy = one CPU queue = clean. The 8 disproven hypotheses
(FDB/isolation/flood/BMU/TX-ring/greg-port-ops/cableless/promisc) were all red
herrings; THIS (multi-CPU-queue classification under DSA) is it.
NEXT (focused RE, decisive): find WHY DSA-enable changes CPU-queue classification.
zx-dsa setup() is a stub + doesn't touch the CLA, so the trigger is one of: (a) the
extra lanN netdevs/queues registered, (b) the conduit's queue/CLA setup differing
when it's a DSA conduit, (c) a CLA "copy-to-CPU-queues" mask. Compare the CLA / CPU
trap-queue config (PP_CLA + per-queue masks) and the napi queue set legacy-vs-DSA;
or restrict the napi to the single primary CPU queue. Build-speed fixed; DT bisect
reverted (switch_dsa re-enabled, lan0/1/3 still disabled per the prior commit).

## ✅✅ RESOLVED 2026-05-31 (commit 7123d5fac) — RX-descriptor invalidation
ROOT CAUSE: zx_tm_napi_poll scans the RX ring for valid descs via len=desc[12..13]>>2>0
but NEVER cleared the len after consuming a desc → delivered descs stayed "valid" →
re-found on ring-wrap/re-scan → SAME bppe re-delivered → CPU replies to each copy →
dup storm (grows as ring is traversed). FIX: clear desc[12..13]=0 + dma_wmb after
consuming each descriptor (one line). HW VERIFIED: ping -c20 = 20/20, 0% loss, ZERO
dups, stable, ~12ms; smac2 TX +31/20pings (was +14382/1ping); lan2 RX+30/TX+30 (1:1).
All 9 prior suspects were red herrings. DSA datapath now works end-to-end on lan2.

## MULTI-PORT GAP 2026-05-31 (lan1 cabled, doesn't ping)
Cable moved jack3→jack1. PHY[1] link=1, MAC[1] fully inited (ctrl=0xbb6003,
en=0x80000001), smac1 RX +9 (MAC1 receives). BUT sw RX +0 with .99 on lan1 →
the SWITCH FABRIC does not forward port1-ingress to the CPU. Only port2 (jack3)
has the ingress→CPU path working. So multi-port needs the per-port forwarding-to-
CPU config (CLA trap / SPA source-port auth / PM in-port→CPU) for ports 0/1/3,
not just MAC2. MAC init is per-port (adjust_link) and fine; the gap is the fabric
trap-to-CPU per source port. lan2 (jack3) still pings clean (dup-fix verified).

## MULTI-PORT GAP PINPOINTED 2026-05-31 (MAC1 RX clean, QMG no trap)
With soft-float userland (ip/ping work now), measured via /sys/.../mem (head -c|tail -c, base e->base=0x921c0000):
- MAC1 ctrl @0x80000 = 0xbb6003 (validated mapping)
- MAC1 RX-ok @0x80780 = 0x6e (110) — MAC1 RECEIVES CLEAN host frames; RGMII RX on port1 is fine.
- QMG hw_trap @0x18c060 = 0 — ZERO frames trapped to CPU.
- tm_rx_count=0, tm_irq_count=0 (IP on conduit OR slave, same result).
Datasheet proven for port2: MAC2 RX-ok == QMG hw_trap. For port1 the chain breaks
between MAC1 (clean RX, counted) and the QMG trap-to-CPU. So the gap is the INGRESS
CLASSIFICATION pipeline (SDET/SPA/CLA) between MAC and QMG — NOT rgmii, NOT MAC init,
NOT isolation (port1 mask 0xfd incl CPU bit5), NOT broadcast flood (0xFF). Only port2's
MAC-RX→QMG-trap path is configured. Next: RE the per-port SDET/SPA ingress-trap enable
(0x14000 SPA pkt-enable, sdet uniN) vs stock where all ports trap.

## CORRECTION 2026-05-31: base-gotcha invalidated the QMG read
e->base = 0x92000000 (boot log "base=[mem 0x92000000-0x921bffff]"), mem window 0x200000.
The `mem` and `poke` debugfs both operate on offsets from e->base, NOT npp_base 0x921c0000.
So my "QMG hw_trap @0x18c060 = 0" actually read phys 0x9218c060 (meaningless) — the REAL
QMG (0x9234c000, tm_base) is OUTSIDE the mem window and NOT readable via mem/poke. CLAIM RETRACTED.
Still SOLID: tm_rx_count=0, tm_irq_count=0 (port1→CPU RX ring gets nothing); and a counter at
e->base+0x80780 (driver MAC1 region) climbs to 110 with host pings (MAC1 receives frames).
The greg STP regs (DSA ZX_NPP_PHYS=0x921c0000) ARE in-window at mem offset 0x1c0040/44/4c.
Open question for RE: exact per-port ingress→CPU gate (STP/VLAN/SDET/SPA/CLA) for port1 vs port2.

## LOOP GOAL 2026-05-31: make jack2 (= physical port1, PHY[1]) ping with DSA
User numbering: jackN → port(N-1). jack3=port2 (the committed dup-fix, worked).
jack2 = port1 = where the cable is now (PHY[1] link=1). Goal: make port1 ingress
reach the CPU so jack2 pings clean over its DSA slave (lan1).
Status this session: userland soft-float FIXED (ip/ping/brctl work on-device, committed
in tasks/00.01.eth-driver/userland/). port1 datapath: MAC1 RX climbs (110), tm_rx_count=0 —
fabric doesn't deliver port1 ingress to CPU. Uniform per-port config ruled in (isolate/flood/
pro_action/trap_queue all loop 0..7). Live STP read (offset-uncertain due to base-gotcha)
hinted port2=Forwarding / port1=Disabled. RE agent running to resolve base aliasing + nail
the exact ingress→CPU gate + give the poke/fix. Next: apply agent's recipe, test ping on jack2.

## RESOLVED DIAGNOSIS 2026-05-31 (RE agent + live poke): port1 SOPC ingress bridge never bonds
RE agent (general-purpose) proved e->base = 0x921c0000 (NOT 0x92000000 — the boot-log
"base=[mem 0x92000000..]" prints resource[0]="pon", not e->base="npp"@0x921c0000, zx-eth-main.c:4938,5095).
=> The earlier "CORRECTION: base-gotcha invalidated QMG read" is ITSELF wrong: mem off 0x18c060
   = real QMG hw_trap 0x9234c060 = 0 (VALID). MAC1 RX-ok mem off 0x80780 = 0x92240780 = 110 (VALID).
   poke writes the LITERAL phys (off=phys-0x921c0000, writel(e->base+off), e->base=0x921c0000) — no aliasing.
CONFIRMED GATE: SOPC↔SMAC ingress bridge at NPP[0x19068]. Live read = 0x00000000 (no port has
ready bit(p+5) NOR enable bit(p)). Poke 0x921d9068=0x42 → readback 0x02: enable(bit1) latches,
READY(bit6) does NOT (HW status, transient). With enable=0x02 set, tm_rx_count STILL 0 → enable
alone insufficient; HW needs READY concurrently bonded. The keepalive worker zx_mac_keepalive_fn
(zx-eth-main.c:3090) already loops all 4 ports re-asserting this, but never catches port1's READY
=> port1's MAC↔SOPC serializer does not bond (READY never asserts), unlike port2 (which works).
Toggling lan1 down/up only cycles the DSA slave phylink (fixed-link), NOT the real GePHY
adjust_link, so it doesn't re-run the serializer bring-up. Same family as the egress blocker
(solved for port2 via eg_port=2 + TX-DAC force). NOT pokeable — needs RE of port1's serializer
bring-up (FUN_40e50c40 / smac_init params, per-port PHY TX-DAC/RGMII) to make READY assert.
NEXT: compare port2 vs port1 serializer bond conditions; consider per-port smac re-init or holding READY.

## 0x19068 IS A RED HERRING FOR INGRESS TOO 2026-05-31 (cross-check vs egress saga)
The egress investigation already ruled 0x19068 out DECISIVELY: stock egresses with
NPP[0x19068]=0x00000000 (zte-tx-egress-blocker memory). So 0x19068=0 is NORMAL. My
ingress poke (enable bit1 → readback 0x02) left tm_rx_count=0 → 0x19068 is NOT the
ingress gate either. The RE agent's medium-high 0x19068 hypothesis joins the ~6-iteration
0x19068 red-herring pile. SOLID & unchanged: frames lost between MAC1 (RX-ok=110) and CPU
(tm_rx_count=0, QMG hw_trap=0). The real per-port ingress→CPU gate is still unidentified.
DECISIVE NEXT STEP (same conclusion the egress saga reached): boot STOCK from NAND with the
cable on jack2 (port1), confirm stock forwards port1→CPU, and live-diff the ingress regs
(SIPC/SDET/SPA/CLA/QMG + FDB) port1-vs-port2. Stop theorizing; measure the working reference.
Also note (egress TODO): driver hardcodes zx_eg_port=2 — for DSA the tagger should drive the
egress port per-packet from the slave dp->index (lan1→port1); verify the device's REPLY to a
jack2 host actually egresses port1, not the hardcoded port2.

## STOCK ORACLE on jack2/port1 2026-05-31 — stock forwards port1→CPU (host ping .1 = 4/4)
Static per-port config IDENTICAL stock vs mainline: SOPC 0x19068=0 (CONFIRMS red herring),
STP greg 0/0/0, SPA pkten=0xffffffff match=1, ISO p0-3=fe/fd/fb/f7, MAC1 en=0x80000001.
DIFFS found:
- MAC1 ctrl: stock 0xBA6003 vs mainline 0xBB6003 (mainline has extra bit16).
- QMG cfg 0x9234c000: stock 0x01F40FA0 vs mainline link-up writes 0x03F40050 (zx-eth-main.c ~4324).
Stock QMG golden block (devmem2, port1 active, actively trapping):
  c000=0x01F40FA0 c004=0x2 c008=0 c00c=0x3FF c010=0xFAA c02c=0x1112
  c044(swfwd)=0xEB↑ c060(hwtrap)=0x166↑  (counters climbing => QMG traps port1 to CPU)
Mainline QMG hwtrap=0 (no trap). zx_pkt_port_addr_offset[1]=0x100,[2]=0x180 (uniform, not the bug).
HYPOTHESIS TO TEST on mainline: poke QMG cfg 0x9234c000=0x01F40FA0 (+ c00c=0x3FF, c010=0xFAA,
c02c=0x1112 if needed) and/or clear MAC1 ctrl bit16 → see if tm_rx_count starts climbing on jack2.

## GATE LOCALIZED upstream of QMG 2026-05-31 (poke test)
On mainline (jack2/port1), poked the full QMG block to stock golden (c000=0x1f40fa0, c004=2,
c00c=0x3ff, c010=0xfaa, c02c=0x1112) AND MAC1 ctrl→0xba6003 (clear bit16). All readbacks
confirmed. Result: tm_rx_count STILL 0, QMG hw_trap (0x9234c060) STILL 0, host ping 100% loss.
=> The QMG-cfg/MAC diffs are NOT the gate. The frame is dropped UPSTREAM of the QMG, in the
ingress classification (SIPC/SDET/SPA/CLA) — it never becomes a QMG trap. Every per-port reg
compared so far MATCHES stock (SOPC 0x19068=0, STP=0, SPA pkten/match, ISO, MAC-en, QMG cfg).
NEXT (broad diff): compare SIPC (0x921cc000, the regdump "0xc000" window) and the SDET per-uni
ingress enable/drop counters between stock(port1 active, trapping) and mainline(port1, trap=0).
Best method: bulk-dump the NPP ingress region 0x921c0000..0x921d9000 from stock (devmem2) AND
mainline (mem debugfs) with port1 cabled+active in both, diff → find the one port-1 reg mainline
doesn't set. (Same approach as the egress diff harness.) The static config is a dead end; the
gate is a per-port ingress-classify/detect enable not yet in our register map.

## INGRESS REGISTER DIFF EXHAUSTED 2026-05-31 — all plain regs match stock
Compared SIPC (0x921cc000-0x48) + SMCT (0x921d0000) stock-vs-mainline (port1 active both).
The apparent SIPC "diffs" (cc004/cc008/cc018/cc01c/cc020/cc044) CHANGE between consecutive
stock reads (cc004: 0x50000→0xe0000, cc008: 0x9aa→0x777) => they are LIVE COUNTERS, not config.
Stable SIPC config (cc000=0x11, cc038/cc03c=0x318, cc040=0x01980000) MATCHES mainline.
Cumulative result: EVERY plain ingress register compared (SOPC, STP, SPA, ISO, MAC, QMG, SIPC,
SMCT) matches stock. Yet stock forwards port1→CPU and mainline does not. => the gate is NOT a
plain per-port register. It is almost certainly an INDIRECT RAM TABLE (CLA classify / FDB / VLAN
PVID per ingress port) or a dynamic/stateful difference (FDB learning of host MAC, ingress-port
PVID→VLAN-member-set incl CPU). NEXT APPROACH (heavier): dump+diff the CLA classify RAM and the
FDB/VLAN BRG_RAM per ingress port stock-vs-mainline, OR check the per-ingress-port PVID/default-VLAN
assignment (does port1's ingress get a VLAN whose member set includes the CPU port?). The plain
register-diff approach is exhausted.

## GATE NARROWED to SIPC→QMG classification 2026-05-31
On mainline (jack2/port1), mainline SIPC counters (0x921cc008/018/01c/044) DO move with host
pings (cc008 0→0xfff000, cc018 0x10→0x70, cc044 0x77→0x88) => frames DO reach SIPC from MAC1.
But QMG hw_trap stays 0 => the drop is BETWEEN SIPC and the QMG, in the SPA/CLA classification.
Tested+RULED OUT (all poked, readback ok, ping still 100%/tm_rx_count=0): QMG cfg→stock golden,
MAC1 ctrl bit16, SOPC bridge enable, broadcast flood 0x8300/0x8304→0xFF. None fix port1.
cc008=0xfff000 on mainline vs ~0x777 stock — looks like a saturated SIPC output FIFO/drop counter
(frames enter SIPC but don't drain downstream to SPA/CLA/QMG).
=> The gate is the ingress CLASSIFICATION (SPA pktdeal / CLA action / CLA trap RAM) for port1.
NEXT (heavy): dump+diff the CLA classify RAM (indirect via 0x9238c014/018/01c) and the SPA pktdeal
table per (port,proto) stock-vs-mainline. The static SPA/CLA *config* regs match; the difference
must be in the indirect RAM contents or a per-port classify result. Consider: zx_chip_tm_init_pro_action
uses action_pp0 for ALL ports (proto 0x14 PP0=1/PP1=0) — verify port1 should use PP0 not PP1.
