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
