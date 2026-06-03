# RED-wedge debug — working state (branch port1-redwedge-debug)

**Goal**: make port1 survive load + cable relink (currently bulk TCP / a replug wedges
unicast→CPU). End state: sustained throughput on port1 + a relink doesn't break ping.

## What's confirmed (2026-06-03)
- port1 gate fix (SPA port_vlan_filter clear) is SOLID + merged to main (c37e6168f). Clean
  boot: bidi ping 8/8, no crash. This bug is SEPARATE.
- Failure mode (repeatable, two triggers — heavy bulk TCP blast ~1000pkts, OR cable
  disconnect/reconnect which pulses MAC port-reset bit7):
  - unicast→CPU stops; broadcast/flood→CPU keeps working (ARP resolves, ICMP no reply).
  - Per-stage (5 ICMP): smac1 good_uc +5 (clean at MAC, crc=0) → QMG UP hw_trap +1 →
    **RED[0x1a044] +5** (the 5 unicast die at RED) → tm_tx +1 → host 100% loss.
  - RED drops **before** the CPU ring: during a unicast burst tm_rx_count / tm_napi_count /
    rx_head are ALL FLAT (no enqueue, no RX IRQ, NAPI doesn't even run). So it is NOT a
    NAPI/drain-side problem — RED rejects at ingress-to-QMG.
  - port_vlan_filter still =0 (peek-verified) — gate not involved.
  - RX not hard-wedged (tm_rx climbs for broadcast; bmu_free_credit fluctuates 5..33).
- Queue mapping (from BPDUMP "TM RX q=N" logs): unicast→CPU uses **q=2**; broadcast/mcast
  uses q4/q5. rx_head[2] cumulative ~849. So the q2 QMG queue's RED state is wedged-full.

## Hypothesis
The QMG CPU queue for the unicast cpu_qid (q2) has a RED average-occupancy that saturated
during the burst and does NOT decay/drain → RED drops all new unicast. Boot-time RED init
(zx_tm_red_init) sets it right; nothing re-applies it on link-up or recovers it at runtime.

## Address map (UNLOCKED — peek any TM reg)
- e->base = 0x921c0000 (npp). TM_OFF = 0x180000 → TM regs at phys **0x92340000 + off**.
- peek = `echo 0x<phys> > /sys/kernel/debug/zx_eth/poke` → reads "peek 0xPHYS = 0xVAL" to
  kernel log (read via REPL `dmesg | grep peek`). poke (2 args) writes.
- RED indirect (WRITE-ONLY so far): cmd TM[0x4014]=q|(type<<22); data TM[0x401c/20/24/28];
  idle gate TM[0x4018] bit0. RED drop counter = NPP 0x921da044 (=0x1a044).
- RX per-queue pending/count: TM_RX_QCNT_BASE=0x10100 → TM[0x10100+q*4]; q2 phys 0x92350108.
- RX desc release/ACK: TM[0x4068]=(1<<14)|(count<<4)|q|(sop<<3) then TM[0x4064]=1.
- QMG region TM[0xc000+] (init writes 0xc000/04/0c/10/2c/44/60). Counters 0xc044/48/4c (DN),
  0xc054/5c/60 (UP) at NPP 0x9234c0xx.

## Plan (next iterations)
1. In the live wedged state, peek QMG q2 occupancy/depth + RED state regs; find the reg that
   shows q2 "full" vs a working queue. Need QmgRegTable / RED read path from DATASHEET +
   stock decomp (plat-zxylzb red_set_queue_cfg / qmg). Check if RED config is READABLE
   (write q to 0x4014 with a read opcode, then read 0x401c-28).
2. Compare q2 RED/occupancy wedged vs clean-boot to see what changed.
3. Try a live unwedge (poke): drain q2 (release descs via 0x4068/0x4064) and/or re-write the
   RED queue cfg for q2's cpu_qid; measure if unicast→CPU recovers (rx_per_ingress port1 +,
   ping replies). That validates the fix mechanism before coding it.
4. Code the fix: re-apply RED/queue init on link-up (adjust_link path) and/or a watchdog that
   re-arms the trap queue; OR raise RED thresholds for the CPU trap queue so a burst can't
   saturate it. Rebuild (build job) + tftp_boot_mainline + retest: 50MB nc both directions +
   a cable replug, confirm no wedge + a real throughput number.

## Tools / gotchas
- Device on mainline (RAM-boot). Reboot → stock NAND; rebuild + `python3 lib/uart.py
  auto_bootm_dtb_appended` (stop the uart bridge first — it holds /dev/ttyUSB0; use
  `fuser -k /dev/ttyUSB0`, NOT pkill -f <pattern-in-my-own-cmdline> which self-kills the
  wrapper → exit 144). Restart bridge: `python3 tasks/00.04.02.uart-bridge/uart_bridge.py`.
- DSA: after boot bring `lan1` up + move 192.168.1.99 to it (C-init leaves it on conduit sw).
- REPL :9999 — simple commands, space them (UART input-overrun if too fast).
- Host: ping/dd/nc/tcpdump on enxc8a362e95900 (jack2=port1, .50). No sudo for ethtool -s.
- Bulk test: device `nc -l -p 5001 >/dev/null &`; host `dd if=/dev/zero bs=64k | nc -N .99 5001`.

---
## Iteration 2026-06-03 (live, continuous) — RED ruled out; FDB-miss is the lead

RULED OUT LIVE (in the wedged state, poke-tested, reversible):
- **RED block** (0x92344004 cfg_enable [1:0]): poked 0xde→0xdc (readback OK) → unicast still
  100% loss, drop_RED counter still climbing. So the OPC "drop_RED" bucket (0x921da044) is
  NOT enforced by the RED block. (DATASHEET flagged ❓ — see RED + drop-counter notes.)
- **QMG up_ram_thd** (0x9234c000[12:0]): raised 0x050→0x1fff (readback OK) → no effect. Not a
  UP-RAM-occupancy/threshold drop. QMG config is otherwise correct (up_thd=0x50/dn_thd=0x1FA0
  = stock values, applied at lan_up; 0xc00c=0x3ff depth; 0xc008 trap_cfg=0).
- NAPI advances/ACKs ALL descriptors incl. bad ones (invalidate+rx_head++ +ack are OUTSIDE the
  bppe bound-check `if`, lines 2990-3002) — so the crash bound-check does NOT stall the queue.
  (Minor: BP not freed when bppe_idx>=pool — possible slow pool leak, lines 2875/2988; low
  priority.)

DROP STAGE: every unicast→CPU frame increments OPC drop bucket **0x921da044** (+5 per 5 ICMP);
QMG UP hw_trap only +1; frames die BEFORE the CPU ring (tm_rx/tm_napi/rx_head flat during a
pure-unicast burst → no enqueue, no RX IRQ, NAPI doesn't run).

★ LEAD HYPOTHESIS: **FDB-miss for the CPU/host MAC** (f4:f6:47:0f:42:64). The asymmetry fits:
- device→host unicast (ARP reply, DA=host MAC c8:a3:62, NOT in FDB since learning is off) →
  egresses fine (flooded). ✅ seen on wire.
- host→CPU unicast (DA = CPU MAC) → needs FDB hit (CPU MAC → CPU port) to trap. If that entry
  is evicted/aged under load or on relink → unknown-unicast → flooded to LAN ports but NOT to
  the CPU port → CPU never sees it → no reply. ✅ matches symptom + drop bucket.
- broadcast→CPU (ARP req) → flooded to ALL incl CPU → always works. ✅
Driver: dynamic FDB learning is DISABLED (zx_tm_napi_poll ~2970); only the CPU's own MAC is
seeded at probe via zx_sbrag_add_mac (sbragRegTable, ZX_SBRAG_CMD 0x388814/BUSY 0x388818/
D0-2 0x38881c/20/24) + zx_fdb_add (PP_BRG_RAM). Suspect the seed ages out / is flushed by the
MAC port-reset on relink, and a traffic burst's source-MAC churn evicts it (or aging timer).

NEXT: (a) confirm CPU-MAC FDB entry is gone in the wedged state (read sbrag table back, or
re-seed it live and see unicast recover); (b) check unknown-unicast flood mask includes CPU
(PP unk-ucast ~0x8340 / phys ~0x92388340); FIX likely = program the CPU/host MAC as a STATIC
NON-AGING FDB entry + re-seed on link-up (adjust_link) + ensure CPU port in the unknown-ucast
flood mask. 3 research agents dispatched (general patterns+TI doc / silicon lineage / mainline
DSA CPU-port FDB+flood+link-up patterns) to ground the exact mechanism + fix.

---
## Iteration 2026-06-03 (cont.) — 3 research agents landed + more live negatives

LIVE NEGATIVES (none recovered unicast→CPU in the wedged state; all reversible/restored):
- Add CPU to unknown-unicast flood bitmap: PP[0x8340] 0x015555ff→0x215555ff (set bit5/0x20).
  No recovery. ⇒ drop is UPSTREAM of the flood/forward decision (active OPC drop, not flood-miss).
- Re-seed CPU/own MAC into sbrag FDB → CPU port via debugfs `fdbadd` (`echo 5 f4:f6:47:0f:42:64
  > /sys/kernel/debug/zx_eth/fdbadd`, rc=0). No recovery. ⇒ either wrong port/table, or the
  CPU-MAC trap doesn't go through the sbrag FDB (the own-MAC is also "spa+pp_pm registered" at
  probe, ~line 2273 — the my-MAC trap match may live in SPA/PP_PM, not sbrag).
- (earlier this iter) RED block disable + QMG up_ram_thd raise: no recovery.
Per-stage still: smac1 good_uc +5 → UP hw_trap +1 (NO trap) → drop_RED(0x1a044) +5.

RESEARCH (3 agents, full reports in session; key cites):
- IP lineage (agent 2): the switch/TM is ZTE Sanechips (ZXIC) IN-HOUSE IP (CONFIG_ZX_TM /
  PLAT_ZXYLZB_128S; same zte,zx29xxxx family as mainline zx296702). NO public SDK/datasheet
  with register semantics — the decompiled tm.ko/plat-zxylzb + our RE are the ONLY source.
  No public erratum for this symptom (novel finding). HW manual paywalled (scribd 787350189).
- DSA patterns (agents 1+3, strongly corroborated): "broadcast-to-CPU works, unicast-to-CPU
  drops" is the TEXTBOOK signature of: HW FDB used as a DA filter for the CPU port + flood-to-
  CPU off + the host/CPU-MAC FDB entry being aged/evicted/flushed. Canonical mainline fix:
  install host MAC (and each user-port MAC) as STATIC NON-AGING FDB entries → CPU port
  (dsa_switch_host_fdb_add→port_fdb_add), ensure port_fast_age flushes DYNAMIC only, re-apply
  on link-up, and/or put CPU in the unknown-unicast flood mask (mt7530 UNU_FFP analog), and
  optionally assisted_learning_on_cpu_port. Refs: https://lwn.net/Articles/886699/ ,
  https://docs.kernel.org/networking/dsa/dsa.html , mt7530 UNU_FFP +
  https://lore.kernel.org/all/20230210172822.12960-1-richard@routerhints.com/ .
  RED-lockout (agent 1): RED EWMA average only decays on packet ARRIVAL; if it latches high and
  all packets are then dropped, it never decays → permanent drop; disabling the RED *block*
  does NOT clear the latched average (matches our negative). Fix = explicitly CLEAR the per-
  queue RED average register at init + link-up. Ref Floyd/Jacobson https://www.icir.org/floyd/red.html

SYNTHESIS / remaining leads (the lever NOT yet found, since flood-mask + sbrag-reseed failed):
1. ★ The CPU-MAC trap mechanism in THIS chip may be the SPA/PP_PM "my-MAC" match (registered
   at probe, ~line 2273), NOT the sbrag FDB. Under load/relink that registration may be lost.
   NEXT: RE how stock traps the device's own MAC to CPU (SPA/PP_PM my-MAC table); peek/compare
   that table wedged vs boot; re-apply it live.
2. ★ RED EWMA latch on the CPU-trap queue — clearing the *average* (not disabling the block).
   NEXT: find the per-queue RED average reg (RED indirect read at 0x92344014/18/1c+) or whether
   re-running zx_red_set_queue_cfg for the trap queue resets it; test live.
3. The fix is almost certainly a LINK-UP/periodic RE-APPLY of the CPU-trap state (FDB/my-MAC +
   RED clear + flood) — but must be validated by finding the live recovery lever first (coding
   the flood/sbrag re-apply is premature since both failed live).

---
## Iteration 2026-06-03 (cont.2) — my-MAC trap table INTACT → it's a congestion latch, not registration loss

DECISIVE: peeked the SPA ONU-MAC table (ZX_SPA_ONU_MAC_BASE 0x14120 → phys 0x921d4120+slot*8)
in the wedged state: slot0 low=0x470f4264 high=0x0000f4f6 = f4:f6:47:0f:42:64 (CPU MAC) PRESENT
+ correct (slots 1-3 = ...65/66/67). So the my-MAC trap registration (zx_register_cpu_mac:
SPA ONU-MAC + PP_PM, mirrors stock tm_onu_mac_addr_set) is NOT lost under the wedge.

⇒ The frame reaches the MAC (good_uc+5), the CPU MAC IS registered for trap, yet it is dropped
(drop_RED+5) instead of trapped (hw_trap+1). So this is NOT an FDB/registration loss — it is a
**congestion/RED LATCH on the unicast CPU-trap queue (q2)** that survives disabling the RED
block (matches agent-1's RED-EWMA-lockout: the average only decays on enqueue; once latched
high with all packets dropped, it never recovers; disabling the block doesn't clear the latched
average — only a reset/reboot does). Broadcast uses a different cpu_qid (q4/q5) whose RED state
is not latched → still works.

CONCLUSION OF THIS SESSION'S LIVE WORK: ruled out as the recoverable lever (none restored
unicast in the wedged state): RED-block disable, QMG up_ram_thd, unknown-ucast flood mask +CPU,
sbrag FDB re-seed, and confirmed the SPA ONU-MAC my-MAC trap table is intact. The remaining
lever is CLEARING the latched per-queue RED/congestion average for the unicast CPU-trap queue —
which the block-enable bit does not do. NEXT (needs more RE or a rebuild):
1. Find/clear the per-queue RED average state: try re-applying zx_red_set_queue_cfg for the
   CPU-trap cpu_qid via the indirect iface (TM[0x4014] cmd=q|(type<<22), data 0x4028/24/20/1c,
   idle 0x4018b0) and see if a re-write resets the average → live unwedge. Need the exact
   cpu_qid (unicast trap) from CLA def_ptl_pkt_map (stock decomp).
2. If a re-write clears it → CODE fix: re-apply RED queue init (and/or a periodic/again-on-
   link-up clear of the CPU-trap-queue average) in zx-eth-main.c, rebuild, test (bulk + relink).
3. Belt-and-suspenders per agents: also program host/user MACs as STATIC non-aging FDB→CPU and
   re-apply CPU-path state on link-up (even though the flood/sbrag pokes alone didn't recover a
   table that's already intact — they matter once learning/aging is involved).

---
## Iteration 2026-06-03 (cont.3) — stock decomp checked; HONEST DEAD-END for cheap approaches

Checked stock decomp (decomp_all_tm.c / plat_zxylzb): `tm_pon_tm_initial` (red+qmg+sch+reg init,
@0x54258) is BOOT-ONLY. The lan_up handler `tm_set_p2pmode` (@0x464c0) only sets lan_up_port +
tm_set_pp_wan_cfg — it does NOT re-run red/qmg init. `tm_pon_tm_qmg_initial` sets up_thd=0x50/
dn=0x1fa0 gated on lan_up but is called from the boot init path, not on link transitions. So
stock does NOT "re-init on link-up" — it simply never wedges. ⇒ the easy "re-apply init on
link-up" fix has no stock precedent to copy.

ALSO tried this iteration: re-applied q2's RED queue cfg (types 0/2/4) via the indirect iface
(TM[0x4014] cmd + 0x401c/20/24/28 data) → no recovery. CAVEAT: did not verify each indirect
write committed (no idle-wait on TM[0x4018] between pokes; the iface is write-only/hard to read
back), and q2 may not be the unicast cpu_qid's RED index — so this single negative is not
conclusive proof that "config re-write can't clear the latch", only that this attempt didn't.

CONCLUSION (cheap live-poke approach EXHAUSTED): the unicast→CPU drop is a latched state in the
TM/QMG/RED/OPC block that is NOT cleared by any config register I can reach via poke (RED-block
enable, up_thd, flood mask, sbrag FDB, RED per-queue cfg) and NOT a registration loss (SPA
ONU-MAC my-MAC trap table verified intact). Only a full reboot (HW reset) clears it. This is an
undocumented in-house ZTE Sanechips silicon behaviour with no public datasheet/SDK (agent 2).

REMAINING OPTIONS (all expensive/uncertain — need user decision):
 A. Find a TM/QMG/RED block SOFT-RESET bit (stock decomp deep-dive for *_srst / reset regs) that
    clears the latch without a reboot, then trigger it from a driver watchdog (detect wedge:
    drop_RED climbing while host-RX idle) or on link-up. MOST LIKELY to actually work.
 B. Deep stock-vs-mainline RED/QMG config diff for the CPU trap queue (maybe stock's per-queue
    RED thresholds for the cpu_qid are set so a CPU-terminated burst never saturates). Multi-
    session RE.
 C. Accept as a documented KNOWN LIMITATION: port1 (and all ports) work bidirectionally on a
    clean boot (the merged gate fix is verified); sustained CPU-terminated bulk load OR a cable
    replug wedges unicast→CPU until reboot. The port1 deliverable is met; this is an edge-case.

NB the agents' FDB/static-host-entry fix (broadcast-works/unicast-drops = unknown-unicast-to-CPU)
is the textbook cause BUT here the my-MAC trap table is intact and re-seeding sbrag didn't help,
so the FDB angle does not fit this instance — it's the RED/OPC latch, option A is the lead.

---
## Iteration 2026-06-03 (cont.4) — found the reset mechanism; option A needs CODE (not poke)

Stock reset = `pon_reset(mask)` (plat_zxylzb @0x1b284): `pon_base+8 &= ~mask; <wait>; pon_base+8
|= mask` — i.e. pulse-LOW a per-block reset register. `pon_reset(0xffffffff)` = full reset at
boot; per-port MAC reset = `1<<(port+6)` (this is the bit the cable-relink pulses, via
extphy_timer_func). Bits 0..5 reset the major blocks (TM/QMG/RED/SPA/CLA/…) but the exact
bit→block map isn't decoded.

⇒ A block soft-reset CANNOT be cleanly validated by a live poke: pulsing pon_reset on the
TM/QMG/RED block leaves it RESET-BUT-UNINITIALIZED (the driver won't re-run its init), so it
would break the datapath, and a blind full pon_reset would hang the running path. The reset must
be PAIRED with a re-init in the driver. So option A is necessarily a CODE change:
  on wedge-detect (drop_RED 0x921da044 climbing while host-RX idle) or on link-up →
  pon_reset(<TM/QMG/RED block bits>) THEN re-run tm_pon_tm_initial-equivalent (zx_tm_red_init +
  QMG init + register_cpu_mac + flood policy), rebuild, test (bulk + relink).
This requires decoding the pon_reset bit→block map first (stock decomp: which bit each init path
asserts), then a careful re-init sequence. NON-TRIVIAL + needs a rebuild/boot/test cycle.

FINAL STATUS (this loop): cheap live-poke approach EXHAUSTED and proven insufficient (the latch
needs a HW block reset, which needs paired re-init = code). The port1 GATE fix (the deliverable)
is DONE + merged + verified on clean boot. This load/relink wedge is a documented OPEN robustness
bug; the actionable fix is option A (reset+re-init on link-up/watchdog) — a code+rebuild task for
a future session. Memory: [[zte-redwedge-unicast-cpu]].

---
## Iteration 2026-06-03 (cont.5) — FORWARDING test (для "streaming estable"): inter-port fwd does NOT work

Tested the REAL router data-plane (forwarding through the device, not CPU-terminated): device
br0 = lan1+lan2 (brctl, both forwarding state); host netns nsA(jack2/lan1)=10.0.0.1, nsB(jack3/
lan2)=10.0.0.2; ping nsA→nsB. RESULT: 100% loss. tcpdump localization: nsA's broadcast ARP
EGRESSES jack2 fine, but **nsB (jack3) receives NOTHING** — the device bridge does NOT flood
lan1→lan2. Frames RX on lan1 (rx_per_ingress port1 climbs, trapped to CPU) but never egress
lan2 (lan2 tx barely moves). So inter-port forwarding is non-functional:
 - NO HW bridge offload (port_bridge_join doesn't program the switch to forward lan1↔lan2 in HW
   → frames go up to the CPU instead of HW-forwarding), AND
 - the CPU software-bridge path doesn't complete the lan1→lan2 egress either (broadcast reaches
   CPU but isn't flooded back out lan2).
Not a wedge/dirty-state artifact (broadcast-to-CPU works; this is CPU→lan2 egress / bridge
forwarding missing) — a clean reboot won't fix a missing feature.

⇒ "STABLE STREAMING" SCOPE (both paths are substantial DRIVER FEATURES, not live-poke fixes):
 (1) Through-traffic (forwarding, the real router data plane): needs DSA **HW bridge offload**
     (port_bridge_join → program the switch fwd/flood masks so lan↔lan forwards in HW, bypassing
     the CPU). Without it, even a working SW bridge would be CPU-bound + would hit the wedge.
 (2) To-device traffic (CPU endpoint): the unicast→CPU RED/OPC wedge (option A: reset+re-init).
Neither is a quick loop win. The port1 gate fix (the original deliverable) remains DONE+merged.
Recommend treating stable-streaming as a deliberate DSA-offload feature effort. Bench restored
to sane state (lan1=.99 standalone, host=.50, br0 removed, netns deleted).

---
## Iteration 2026-06-03 (cont.6) — CLEAN-boot forwarding test: routing WORKS, but wedge is UNIVERSAL

Clean reboot (fresh state, wedge cleared). Tested on a clean boot with host netns:
- **lan1 (jack2) AND lan2 (jack3) both work standalone (L3 endpoint): bidirectional ping OK**
  (lan2 5/5 0% loss, 1.3ms). So per-port egress works on BOTH ports, not just port1.
- **L2 BRIDGE forwarding (br0=lan1+lan2) does NOT work** even clean: nsA's ARP reaches the CPU
  (port1 RX climbs) but is NOT flooded out lan2 (nsB sees nothing). No HW offload + the SW-bridge
  lan1→lan2 flood doesn't complete.
- **L3 ROUTING through the device WORKS (functional!):** lan1=10.0.0.99, lan2=10.1.0.99,
  ip_forward=1; nsA(10.0.0.1)→nsB(10.1.0.50) routed = ttl=63, 5/5 0% loss, ~14ms. The device
  IS a functional multi-port IP router at light/moderate load.
- **BUT sustained streaming through the routed path WEDGES** (same as CPU-terminated): a 20MB
  stream stalled at <4 Mbit/s after routing ~500+ frames bidirectionally (port1=557, port2=504,
  tx=959), then ping = 100% loss (wedged). drops RED only +34 this time (lower than the
  terminated case) but the path is dead until reboot.

★ KEY CONCLUSION: the CPU UP-trap wedge is the UNIVERSAL blocker for stable streaming. ALL
inter-port/endpoint traffic currently goes through the CPU (no HW bridge offload), so terminated,
routed, AND (would-be) bridged traffic all wedge under sustained load. → Fixing the wedge
(option A) enables stable streaming on ALL CPU paths; it is the right universal target.
"Functional" (light/moderate: ping, routing, per-port endpoints) ALREADY WORKS on a clean boot.
"Stable streaming" (sustained) is gated solely by the wedge. (HW bridge offload is a separate
perf feature that would make forwarding FAST + bypass the CPU, but the wedge fix is what makes it
STABLE.) Next per user's "las dos en orden": pursue option A (wedge reset+re-init recovery).

---
## Iteration 2026-06-03 (cont.7) — STREAMING loop: found+fixed the bridge-comm bug (offload_fwd_mark)

User goal: leave the driver functional+tested — ① ping ② bridge comm (lan<->lan) ③ good perf;
loop stops only when all work.

★ BRIDGE-COMM BUG FOUND + FIXED: net/dsa/tag_zte.c zte_tag_rcv() called
`dsa_default_offload_fwd_mark(skb)` which sets `skb->offload_fwd_mark = !!(dp->bridge)` → 1 when
the user port is in a bridge. This driver is TRAP-ALL with NO HW bridge offload (confirmed: no
.port_bridge_join / dsa_switch_ops bridge ops anywhere). So offload_fwd_mark=1 LIES to the bridge
("HW already forwarded this") → the bridge skips software-forwarding → frame reaches CPU but is
dropped instead of flooded to the peer lan port → lan<->lan broken (matches the test: ARP RX on
lan1 never egressed lan2). FIX: removed the offload_fwd_mark call (leave it 0) so the software
bridge forwards lan1<->lan2 through the CPU. Clean 1-spot change. Rebuild + test pending.
NOTE: this makes bridge comm work via SOFTWARE (CPU) forwarding → moderate load OK, but heavy
streaming will still hit the CPU-trap wedge (③). HW bridge offload (a bigger feature) would make
it both stable AND fast, but the offload_fwd_mark fix is the correct first step for ② now.

---
## Iteration 2026-06-03 (cont.8) — HW FORWARDING is the goal (user) — found stock's L2-fwd blueprint

User course-correction: we want HW forwarding, NOT CPU/software bridging (CPU wedges + slow). The
offload_fwd_mark removal (cont.7) was only a SW-bridge stopgap. Correct fix = HW bridge offload:
configure the switch to L2-forward LAN<->LAN in hardware (bypasses CPU → no wedge + line rate).

★ STOCK L2-FORWARDING BLUEPRINT (decomp_all_tm.c, the tm_pon_*_initial per-port loop ~43590):
per-port (0..7) the stock enables HW switching that mainline's trap-all driver OMITS:
  - sbrg_set_pt_transfer_en(port, 1)          # per-port forwarding/transfer enable
  - sbrg_set_pt_smac_look_en(port, 1)         # SMAC lookup => MAC learning
  - sbrg_set_pt_smac_lookfail_pktdeal(port,0)
  - sbrg_set_pt_da_lookup_en(port, 1)         # DA lookup => HW forwards by FDB
  - sbrg_set_pt_learn_mode(0,port) then (1,port)   # learn mode (reg_id = port+0x22 in sbragRegTable)
  - tm_vlan_check_ena_set(port,0/1,0)         # vlan check off
  - sbrg_set_unknown_unicst_fwd(port,0) + (0,1)   # unknown-ucast: off per-port, ON to port0
  - sbrg_set_unknown_multicst_fwd(port,1)
  - sbrg_set_pt_tls(port,0) + (0,1)
globals: sbrg_set_macaddr_age_en(1), tm_mac_aging_cycle_set(300), sbrg_set_multicst_md(1),
  sbrg_set_hash_collision_pktdeal(1), sbrg_set_macaddr_exchange_md(1), sbrg_set_brdcst_fwd_en
  (reg_id 0x32 = the PP[0x8340] bits24-31 FWD bitmap), sbrg_set_irq_en_mask(10).
All via tmOnuRegWrite(reg_id, val, 0, &sbragRegTable) → direct sbragRegTable registers
(base ~0x92388xxx; 0x32=PP[0x8340], learn_mode=port+0x22, etc.).

PLAN to implement HW forwarding:
1. Map the sbragRegTable reg_ids → phys addr/bitfield for transfer_en, smac_look_en,
   da_lookup_en, learn_mode (port+0x22), unknown_ucast/mcast_fwd, pt_tls (from DATASHEET sbrag
   section / decomp tmOnuRegWrite + the per-set_* bodies).
2. LIVE-TEST via poke on a clean boot: enable transfer_en + smac_look_en + da_lookup_en +
   brdcst_fwd for the lan ports, bridge lan1+lan2, ping nsA<->nsB → success = forwards with
   tm_rx FLAT (HW, not CPU). Measure throughput (should be fast + not wedge).
3. CODE it: a zx_sbrg_l2_fwd_init() replicating the stock per-port loop, called at probe (and/or
   port_bridge_join); restore offload_fwd_mark (correct once HW forwards); keep the static CPU-MAC
   trap entry so to-CPU still works.
4. Rebuild + test all 3: ping, bridge comm (HW), performance (sustained, no wedge).
This ALSO fixes the wedge for streaming (forwarded traffic never touches the CPU UP-trap path).
