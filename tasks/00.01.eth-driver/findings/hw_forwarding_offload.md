# HW bridge offload — overnight loop working state (branch hw-bridge-offload)

GOAL (user, 2026-06-03 night): leave the driver functional + tested for ALL THREE — ① ping
② bridge comm (lan<->lan) ③ good perf/streaming — with **HW FORWARDING, not CPU**. Stop the loop
only when all 3 work. Document + commit every iteration. Resolve by morning.

## What works / what's the blocker (from the port1-redwedge-debug investigation, now merged to main)
- ① ping: ✅ (clean boot, bidirectional).
- ② bridge comm: ✅ functional but via SOFTWARE bridge (CPU) — offload_fwd_mark fix (tag_zte.c,
  merged main 8bc9beb32) + flood masks poked. CPU-bound, wedges under load. NOT HW.
- ③ perf/HW forwarding: 🔴. The switch traps EVERYTHING to CPU (QMG UP hw_trap climbs, hw_fwd=0).
  A 30MB bridge stream pushed tm_rx +573 (1:1 = CPU/SW bridge), <7Mbit, then WEDGED.

## Key facts established
- sbrag L2-fwd ENABLE regs are ALREADY ON in mainline: transfer_en 0x92388004[7:0]=0xff,
  smac_look_en(learning) 0x923881c0[7:0]=0xff, da_lookup_en 0x923882c0[7:0]=0xff, learn_mode
  0x923881c4=0x5555. vlan_chk 0x92388008=0x0000ff00.
- FLOOD masks were OFF; poking them enabled SW-bridge ARP: brdcst_fwd_en 0x92388300[15:8] (was 0
  → poke 0xff), unknown_ucast_fwd 0x92388340[31:24] (was 0x01 → poke 0xff). (unknown_mcast
  0x923882d4[31:24], unkmul_portmask 0x923882d8 x9, multicst_md 0x92388180[1].)
- DESPITE all the above ON, frames still trap to CPU (hw_trap, not hw_fwd). ⇒ the CLA/pipeline
  traps to CPU BEFORE the L2-forward engine, OR the FDB isn't populated so DA lookup misses.
- forward-vs-trap lever = the "pktdeal" values: sbrg_set_pt_smac_lookfail_pktdeal (stock=0),
  sbrg_set_unknown_unicst_pktdeal, sbrg_set_unknown_multicst_pktdeal, + da_lookup. pktdeal 2b/port
  (stock 0x5555 = "1" each). Need the meaning of pktdeal values {fwd/flood/trap/drop}.
- QMG counters: UP hw_fwd=0x9234c05c, hw_trap=0x9234c060, sw_fwd=0x9234c054; DN hw_fwd=0x9234c048.
  HW forwarding = hw_fwd should climb (it's 0 now).

## PLAN (iterate; document+commit each)
1. Clean boot. Check QMG **hw_fwd** during a bridge forwarding test: if hw_fwd>0 the switch CAN
   HW-forward (just need it primary); if hw_fwd=0 the CLA traps before forward.
2. Check if the switch HW FDB (sbrag) actually LEARNS source MACs during traffic (read it back).
   If not learning → DA always misses → trap/flood (no HW fwd). Find why learning doesn't populate.
3. Find the CLA/pktdeal config that makes KNOWN-unicast hw_fwd instead of trap (RE
   decomp_all_tm.c cla_* / sbrg_set_*_pktdeal bodies for the value meanings; the stock per-port
   loop @43590 is the blueprint). POKE-test it live (tm_rx FLAT + hw_fwd climbs + throughput high
   + no wedge = success).
4. CODE it on hw-bridge-offload: implement .port_bridge_join (dsa_switch_ops) that programs the
   switch to HW-forward bridged ports + the flood-mask enable in driver code; restore
   offload_fwd_mark (correct once HW forwards); keep a STATIC trap entry for the CPU MAC so
   to-CPU (mgmt/ARP-to-device) still works. RISK: wrong un-trap breaks CPU connectivity — keep the
   CPU-MAC trap + test ping-to-device after every change.
5. Rebuild (build_slotA.py) + boot (uart.py auto_bootm_dtb_appended) + VERIFY all 3: ping,
   bridge comm (HW: tm_rx flat), sustained throughput (no wedge, >>7Mbit).

## TOOLS / GOTCHAS
- Device mainline (RAM-boot). Rebuild: `python3 tasks/00.01.eth-driver/scripts/build_slotA.py`
  (make all + zImage + tftp/zImage_dtb.uimg). Boot: stop bridge `fuser -k /dev/ttyUSB0`, then
  `nohup python3 lib/uart.py auto_bootm_dtb_appended >/tmp/boot.log 2>&1 &`; wait ~3min for
  "C-init REPL ready"; then `fuser -k /dev/ttyUSB0`; restart `nohup python3
  tasks/00.04.02.uart-bridge/uart_bridge.py &`. NEVER pkill -f a pattern in my own cmdline (self-
  kill exit 144) — use fuser.
- REPL :9999 (simple spaced cmds). peek/poke: `echo 0x<phys> [val] > /sys/kernel/debug/zx_eth/poke`,
  read `dmesg|grep peek`. TM reg phys = 0x92340000+off; sbrag phys = 0x92388xxx direct.
- Host: sudo -S available (password provided by the user this session). netns fwd test = jack2
  (enxc8a362e95900->lan1) + jack4 (enx6c70cbb68169->lan3); device br0=lan1+lan3; nsA=10.0.0.1
  nsB=10.0.0.2; stream nsA->nsB. (jack3 enx2c99 vanished from USB — ignore it.)
- C-init leaves IP on conduit sw + lanN DOWN; for bridge test: brctl addbr br0 + addif lan1 lan3.
- NEVER touch main / break egress. Test on HW before asserting. Commit+document each iteration.

---
## Iter A (overnight 2026-06-03 ~19:10) — hw_fwd=0 confirmed; trap-all = SPA pktdeal=1

Live on a clean-ish boot: br0=lan1+lan3 + flood masks poked, ran netns fwd test jack2<->jack4 =
6/6 ping OK (SW bridge). QMG counters: UP hw_fwd(0xc05c)=0 BEFORE and AFTER, UP hw_trap(0xc060)
103->139 (+36). ⇒ the switch NEVER HW-forwards — every frame hw_traps to CPU; the L2/SBRG
forward engine never runs (so no learning, no DA-forward, hw_fwd stuck 0).

★ TRAP-ALL MECHANISM = SPA per-entity pktdeal. The driver (zx-eth-main.c ~1139) sets
spa_enty_pktdeal_cfg = **1** for ALL entities 0..7 × slots 0x43..0x7d via
byte_off=(zx_spa_table[slot].base_dword + port*stride)*4 - 0x1c0000, field mask/shift. pktdeal=1
means "deliver/trap to CPU" (the driver added it to MAKE frames reach the CPU — comment: "without
it the switch [doesn't deliver to CPU]"). Stock spa_set_enty_pktdeal_cfg(entity,slot,val) val is
2-bit; action type ∈ {0,1,2} (stock zte_api uses pkt-type->slot map @56430). So pktdeal: likely
0=forward(L2)/1=trap-to-CPU/2=drop (TBD).

HW-FWD HYPOTHESIS: set pktdeal=0 (forward) for the LAN-port entities (across the L2-unicast
slots) → frames proceed to the SBRG L2 engine → learn + DA-forward in HW (hw_fwd climbs). KEEP
pktdeal=1 (trap) for the CPU-destined slots/the CPU port so ping-to-device + mgmt still work.
RISK: changing the wrong slots breaks CPU connectivity (ARP-to-device stops trapping).

NEXT ITER: (a) decode pktdeal value 0/1/2 meaning + which slots = normal-unicast vs control
(decomp zte_api pkt-type->slot map @56430: pkt types 8->0x1a, 9->0x1c, 10->0x1b, 0xb->0x1d, ...);
(b) get zx_spa_table[slot] {base_dword,mask,shift,stride} from zx-fpga-reg-tables.h; (c) poke-test:
set pktdeal=0 for lan1+lan3 entities on the L2-unicast slots, re-run fwd test, check hw_fwd climbs
+ tm_rx flat + throughput high + ping-to-device still works; (d) if it works, code it as
port_bridge_join + keep CPU trap. This is a deep + risky feature (un-trapping the SPA); progress
is incremental. Device currently: br0=lan1+lan3, flood masks poked, uptime ~2.3h (dirty but
usable for hw_fwd diagnostics).

---
## ROBUST BOOT RECIPE (use this every fire — learned 2026-06-03 night)
The auto_bootm-direct path desyncs if TFTP is slow. The reliable flow:
  1. RESTORE host NICs to default ns + .50 FIRST (the netns fwd test leaves enxc8a362e95900 in
     nsA → TFTP from default-ns tftpd fails with 'T T T' timeouts):
     `echo <pass> | sudo -S bash -c 'for ns in nsA nsB; do for nic in $(ip netns exec $ns ls /sys/class/net 2>/dev/null|grep enx); do ip netns exec $ns ip link set $nic netns 1; done; ip netns del $ns 2>/dev/null; done; sleep 1; ip addr flush dev enxc8a362e95900; ip addr add 192.168.1.50/24 dev enxc8a362e95900; ip link set enxc8a362e95900 up; ip link set enx6c70cbb68169 up'`
  2. Launch the bridge FIRST (owns the serial, serves :9999 cmd + :9998 DTR):
     `fuser -k /dev/ttyUSB0; sleep 2; nohup python3 tasks/00.04.02.uart-bridge/uart_bridge.py >/tmp/bridge.log 2>&1 &`
  3. RAM-boot via the dedicated script (UART_TCP=1, talks through the bridge, retry/DTR-recovery,
     no NAND write): `nohup python3 tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py >/tmp/boot.log 2>&1 &`
     then wait ~3min for 'C-init REPL ready' (grep /tmp/boot.log). The bridge stays up = REPL on
     :9999 ready immediately after boot (NO kill/restart needed — the script shares the bridge).
  - Rebuild first if code changed: `python3 tasks/00.01.eth-driver/scripts/build_slotA.py`.
  - tftp_boot_mainline.py also produced slotA.bin+header for `flash_mainline.py` (NAND persist) if
    TFTP ever too fragile — but RAM boot is faster for the loop.

---
## Iter B RESULT — pktdeal=0 is NOT the HW-fwd lever (negative, but informative)
Booted zx_spa_pktdeal=0 (confirmed "applied val=0" in log, no panic). Tests:
- ping-to-device (host .50 -> br0 .99) = 4/4 0% loss ✅ → the ONU-MAC trap is INDEPENDENT of SPA
  pktdeal; CPU mgmt connectivity SURVIVES pktdeal=0. (Good safety result.)
- LAN<->LAN fwd test (nsA jack2 <-> nsB jack4 through br0) = 6/6 ping, BUT QMG hw_fwd(0xc05c)
  stayed at 1 (did NOT climb), hw_trap(0xc060) +30, tm_rx +32. ⇒ STILL CPU/SW-bridge forwarding,
  NOT HW. **SPA pktdeal is NOT the trap-all lever.**
⇒ The trap-to-CPU happens regardless of SPA pktdeal — the lever is deeper: either the CLA
per-inport trap action (replayed from stock zx_cla_table) OR the HW FDB never learns (so DA
lookup always misses → trap), likely because the CLA traps the frame to CPU BEFORE the SBRG
learn/forward stage runs. NEXT: (a) decisive test — statically add both host MACs to the HW FDB
(debugfs fdbadd) pointing at lan1/lan3 + static host ARP, ping, check hw_fwd: if KNOWN-unicast now
hw_fwds → learning was the issue; if still traps → the CLA traps regardless of FDB = the CLA is
the lever (deep). (b) the CLA is replayed byte-for-byte from stock yet stock HW-forwards — the
fundamental puzzle (why same CLA traps in mainline but forwards in stock) may be architectural.
ASSESSMENT: HW forwarding is looking like a DEEP blocker (CLA trap-all, replayed-from-stock,
risky to change). pktdeal param left in (harmless, default 0). Continuing but flagging possible
honest dead-end if the CLA proves architectural.

---
## ★ HONEST DEAD-END for HW forwarding (overnight 2026-06-03 night) — CLA trap-all is architectural

DECISIVE static-FDB test: added BOTH host MACs as static HW-FDB entries (fdbadd, rc=0) so the
switch DA-lookup is guaranteed to HIT, set static host ARP (skip ARP), ping nsA<->nsB through
br0 = 6/6 — but QMG hw_fwd(0x9234c05c) STILL stays 0 (hw_trap +26, tm_rx +28). ⇒ the switch traps
to CPU REGARDLESS of the FDB. So it is NOT FDB/learning, and the CLA preempts the L2 forward
decision entirely.

RULED OUT as the HW-fwd lever (all tested live, none make hw_fwd climb):
 - SPA pktdeal (zx_spa_pktdeal=0 module param, rebuilt+booted): ping-to-device survives but
   hw_fwd stays 0.
 - Flood masks (brdcst_fwd 0x92388300, unknown_ucast 0x92388340): enable SW-bridge ARP only.
 - HW FDB / learning (static fdbadd entries): hw_fwd stays 0.
 - trap_acl_en (CLA reg4 0x9238c080[17]): already 0 — not the trap mechanism.
 - Enable regs (transfer_en/smac_look/da_lookup/learn_mode): already on.

CONCLUSION: the driver is architected as a TRAP-ALL DSA conduit — the CLA (replayed byte-for-byte
from stock zx_cla_table) traps EVERY frame to the CPU before the switch's L2 forward engine runs,
so hw_fwd is always 0 and ALL inter-port traffic is CPU/software-forwarded (slow + wedges under
load). None of the reachable config levers change this. The fundamental puzzle — stock HW-forwards
with the SAME CLA replay — means the trap-all is either (a) inherent to how this driver drives the
pipeline (CPU-port-centric), or (b) gated by a higher-level mode (PON-vs-switch / a CLA default-
flow action / SADM CPU-port routing) NOT captured in the per-entry CLA dump. Cracking it is a
DEDICATED multi-session RE effort: live-trace stock forwarding a LAN<->LAN frame (kotrace the
cla/sbrg/qmg path) and diff vs mainline to find what makes stock hw_fwd; likely needs the CLA
default-flow action (claRegTable reg0 0x9238c014) + the SADM/CPU-port forward config decoded. NOT
attainable safely overnight. Stopping the loop here (honest dead-end).

WHAT THIS SESSION DELIVERED (all merged to main / committed):
 - port1 ingress→CPU gate fix (SPA port_vlan_filter) — MERGED, verified bidi ping.
 - offload_fwd_mark fix (tag_zte.c) — MERGED — bridge comm works via SW (lan<->lan).
 - ping (1) ✅, bridge comm (2) ✅ (SW, light/moderate load). Performance (3) 🔴 — needs HW fwd.
 - Full RE map of the trap-all mechanism + the precise next-step (above) on branch
   hw-bridge-offload (the zx_spa_pktdeal experiment param can be reverted; it's harmless).

---
## Iter C (overnight, user supervising, runway to 07:00 UTC) — narrowing the CLA trap-all
Found the CLA default-flow + action cfg regs (driver does NOT write them, at reset/replay value):
  oth_l3_pkt_action 0x9238c0cc=0, dn_unknown_da_action 0x9238c0d0=1 (act∈{0,1,2,3}, claReg 0x16),
  up_l2_uni_default_flow_cfg 0x9238c0fc (x9, reg23, set via cla_set_up_l2_uni_default_flow_cfg
  @decomp 0x11f64 — per-uni struct), dn_l2_default 0x9238c11c, up_l3 0x9238c120, dn_l3 0x9238c124.
But the static-FDB test already showed KNOWN unicast (FDB-hit) STILL traps → the default-flow (for
UNMATCHED frames) is not the (only) cause.

★ REAL trap-all suspect = the CLA ram2-6 per-inport HASH entry's TRAP ACTION. Datasheet: ram2-6
hold "inport VALUE + trap action cpu_qid + cpu_qid_rp_en + valid_en/direct". If every inport's
hash entry carries an ACTIVE trap-to-CPU action (cpu_qid_rp_en set / direct), the frame traps to
cpu_qid REGARDLESS of the L2 DA-forward result — exactly matching "known unicast still traps".
The port1 saga found regport2==regport3 entries (identical, valid, trap action) → ALL ports trap.
Stock has the SAME entries yet HW-forwards → the trap must be CONDITIONAL on a field
(cpu_qid_rp_en? a global mode?) that differs, OR stock's forwarding path bypasses this.
NEXT: clapeek the ram2-6 entry for a LAN inport (regport for lan1/lan3), decode the trap-action +
cpu_qid_rp_en field, and poke-test CLEARING the trap action (or cpu_qid_rp_en) for that inport →
re-run the fwd test → if hw_fwd climbs, that's the lever (then code it as port_bridge_join). RISK:
clearing trap for the CPU inport breaks mgmt — only touch the LAN inports.

---
## Iter D — CLA CONCLUSIVELY RULED OUT as the trap-all; it's a global driver-vs-stock diff
Compared live mainline vs the stock CLA golden dump (captures/cla_stock): stock's regport2 ram2
entries carry `cpu_qid=0x15 valid/dir=0x42` — and STOCK HW-FORWARDS with those exact entries
(the working ports forward in stock). Mainline replays the SAME entries byte-for-byte. ⇒ the
cpu_qid in the CLA hash entry is NOT an unconditional trap, and the CLA is NOT the trap-all
differentiator (logic: identical CLA, opposite behaviour → the cause is elsewhere). This matches
the static-FDB result (the trap is upstream of / independent of the CLA forward decision).
Peeked global-mode candidates (no smoking gun yet): pp ctrl 0x92380000=1, pp 0x92380004=0x02abfc8d,
pp CPU-fwd ctrl 0x9238002c=0x106 (the lan_up_port+0x19 bit NOT set, but that gates CPU-SOURCE fwd,
likely egress not LAN->LAN), sbrag 0x92388004=0x040200ff.

⇒ The trap-all is a GLOBAL config the mainline driver sets/omits differently from stock. Reg-by-reg
poking is NOT converging. The DECISIVE next step is a stock-vs-mainline FORWARDING-CONFIG DIFF:
boot stock (DTR reset → NAND), dump the sbrag/cla/qmg/pp/spa/opc forwarding-relevant regs via the
fpga-read oracle (/dev/logger_main, see zte-device-access), boot mainline, dump the same, and diff
— the reg(s) that differ = the trap-all lever. (Lighter alternative to kotrace-stock; the
egress-diff-harness already does stock-vs-mainline reg diffs.) This is the dedicated RE the
dead-end note flagged. ASSESSMENT: HW forwarding needs this stock-config-diff; not crackable by
blind poking. Continuing the loop toward the stock diff (heavier per-iteration).

---
## Iter E — forwarding-init stages audited (decomp vs driver); no single global lever found
Stock forwarding init = tm_pon_pp_initial → {reg, sadm, brg, cla, adm, dpa, pm}. Audited:
 - tm_pon_pp_brg_initial (sbrg per-port loop @43590): transfer_en/smac_look/da_lookup/learn_mode
   all ON in mainline (matches). flood masks were off (poked, only gave SW-bridge ARP).
 - tm_pon_pp_cla_initial: CLA entries match stock byte-for-byte (stock forwards with them).
 - tm_pon_tm_qmg_initial: minimal (ext_ddr/ddr_cache + up/dn thd) — matches mainline.
 - tm_pon_pp_dpa_initial: dpa_set_protocol_cpu_pps_en(1) = trap PROTOCOL pkts to CPU (control
   plane, correct) — NOT a data-plane trap-all.
No single global forward-vs-trap bit found in any audited stage. GROWING ASSESSMENT: the trap-all
is likely INHERENT to the driver's DSA-conduit design (it configures the pipeline to deliver
everything to the CPU so Linux can switch in SW) and/or a difference across the FULL init sequence
(brg+cla+adm+dpa+pm+sadm + order + dynamic state) that no single reg captures. The hardware CAN
forward (stock proves it) but enabling HW forwarding = replicating stock's COMPLETE forwarding
pipeline config, not flipping one bit — a dedicated re-architecture.
DECISIVE next: boot stock + dump the full sbrg/cla/qmg/pp/spa/opc/adm/dpa forwarding-reg set via
the fpga oracle, boot mainline, dump the same, diff — the reg(s) the driver's replay does NOT
cover/sets differently = the lever (or confirms it's whole-pipeline). Heavy but decisive.
NOTE: still ruled out cleanly — CLA, pktdeal, flood, FDB, trap_acl, qmg, dpa-protocol. ping ✅ +
SW bridge comm ✅ remain delivered (merged main). Continuing per user (supervising, run to 07:00 UTC).

---
## Iter F — macaddr_exchange_md/multicst_md also negative; pivoting to stock-boot reg diff
Found a real diff: 0x92388180 = 0x4 → macaddr_exchange_md(bit0)=0 + multicst_md(bit1)=0 (stock
sets BOTH =1 in brg_initial). Poked to 0x7 (set both) → hw_fwd STILL 0x01 (no climb). Negative.
(mirror bit7=1 matches; pp[0x2c] bit25 correctly unset = matches stock.)

6 iterations, EVERY incremental lever negative; hw_fwd never moves off ~0. Firm conclusion: the
trap-all is NOT a single configurable register — it's either inherent to the driver's DSA-conduit
pipeline drive, OR a gap in the 22363-entry stock REPLAY blob (zx_stock_ops) that the code audit
cannot see (a forwarding reg stock sets that the replay omits AND the driver doesn't explicitly
set → at reset default in mainline). The ONLY decisive remaining step that can catch a replay gap
= boot stock, dump the full forwarding-reg set via the fpga oracle, boot mainline, diff. Pivoting
to that now (heavy, multi-iteration). If the stock diff shows the forwarding regs MATCH → the
trap-all is whole-pipeline/dynamic = honest dead-end (HW offload needs a dedicated re-architecture
replicating stock's complete forwarding-domain setup + likely runtime learning state).

---
## ★★ HONEST DEAD-END — HW forwarding (overnight loop conclusion, 2026-06-04 ~20:30 UTC)
Iter G attempted the decisive stock-boot reg diff: DTR reset reached U-Boot, but `boot` landed on
MAINLINE (RAM/NAND holds the mainline image, not stock) — could NOT boot stock to dump its
forwarding regs. Booting stock is unreliable this session (auto_bootm desync earlier; `boot` →
mainline now; 2+ failed attempts). So the one decisive remaining step (stock-vs-mainline reg diff
to catch a replay gap) is NOT executable right now.

FINAL CONCLUSION (HW forwarding): after 6+ iterations the switch NEVER HW-forwards (QMG hw_fwd
0x9234c05c never moves off ~0; every frame hw_traps to CPU). CONCLUSIVELY RULED OUT as a single
lever: SPA pktdeal (module-param test), flood masks, FDB/learning (static-FDB: known unicast still
traps), trap_acl_en, CLA default-flow regs, CLA per-inport hash entries (stock HW-forwards with
the IDENTICAL cpu_qid entries mainline replays), QMG init (matches stock), dpa protocol-trap
(control-plane only), macaddr_exchange_md/multicst_md, isolation, pp[0x2c] mode. ⇒ HW forwarding
is NOT a flip-one-register fix. It needs a DEDICATED RE + re-architecture: this driver is a
trap-all DSA conduit (everything to CPU so Linux switches in SW); replicating stock's complete
HW-forwarding pipeline config (the full tm_pon_pp_* init + any replay-blob gap + runtime
learning/forwarding state) is a multi-session project. PRECISE NEXT STEP: reliably boot stock
(fix the boot-slot selection / use a known-good stock NAND), kotrace the cla/sbrg/qmg path while
stock forwards a LAN<->LAN frame, and diff the live forwarding config + path vs mainline.

DELIVERED THIS SESSION (merged to main, verified on HW): (1) port1 ingress→CPU gate fix (SPA
port_vlan_filter); (2) offload_fwd_mark fix (tag_zte.c) → lan<->lan bridge comm via SOFTWARE
bridge. So: ping ✅, bridge comm ✅ (SW, light/moderate load). Performance/HW-forwarding 🔴 (the
SW path is CPU-bound + hits the unicast→CPU wedge under load — see zte-redwedge-unicast-cpu).
Device left on mainline (functional). Branch hw-bridge-offload has the full trail (zx_spa_pktdeal
experiment param is harmless/revertible). Loop STOPPED (honest dead-end).

---
## ★★★ Iter G BREAKTHROUGH (new approach: stock-boot diff) — "HW forwarding" was a FALSE PREMISE
Cracked reliable stock boot: DTR cold reset (bridge :9998) + DO NOT interrupt autoboot → cspstart
boots stock NAND (the earlier failures interrupted autoboot → mainline). Verified stock up (.1).

DECISIVE LIVE TEST on STOCK: ran the netns fwd test jack2<->jack4 THROUGH stock = 6/6 ping (stock
forwards LAN<->LAN). Dumped stock's QMG counters via the fpga oracle around it:
  hw_fwd (0x9234c05c / widx 0xd3017): 0 BEFORE, **0 AFTER** (did NOT climb)
  hw_trap (0x9234c060 / widx 0xd3018): 0x143 BEFORE, **0x1d9 AFTER (+150)** (climbed)
⇒ **STOCK ALSO CPU-FORWARDS LAN<->LAN — it traps to the CPU (hw_trap) and forwards in software,
EXACTLY like mainline. STOCK DOES NOT HW-FORWARD (hw_fwd=0).** The chip's basic L2 LAN<->LAN path
is CPU/software-forward in BOTH stock and mainline. So the entire "enable HW forwarding / hw_fwd
should climb" goal was based on a FALSE PREMISE — mainline ALREADY MATCHES stock's forwarding
mechanism. There is no "HW bridge offload" for basic L2 on this chip's normal path; the trap-all
is CORRECT (matches stock), not a bug.

Stock forwarding-reg dump (vs mainline): all match (sbrag 0x040200ff, flood 0x015555ff,
brdcst_fwd 0x92388300=0 in BOTH, cla default-flow, pp 0x9238002c=0x106) EXCEPT qmg 0x9234c000:
stock=0x01f40fa0 (up_thd 0xfa0/dn 0xfa0, lan_up=0 state) vs mainline=0x03f40050 (up_thd 0x50 set
at lan_up). Not a HW-fwd lever.

⇒ REFRAME of the real goal (stable streaming): both stock & mainline CPU-forward LAN<->LAN. The
REAL difference that matters = (1) mainline's unicast→CPU path WEDGES under load
([[zte-redwedge-unicast-cpu]]) while stock's does NOT → FIX THE WEDGE = stable CPU forwarding =
matches stock's behavior (TRACTABLE). (2) Stock likely uses the FFE flow fast-path for sustained
throughput acceleration (ffe_learn_skb / the L3 fast-path) — that, not basic L2 hw_fwd, is the
real "offload" — a separate feature. NEXT: stress-test stock under SUSTAINED bulk (does stock
wedge like mainline, or stay stable?) to confirm the wedge is the key fixable diff; then pursue
the wedge fix (RED/OPC latch recovery) for stable streaming. HW-fwd dead-end is RESOLVED as a
non-goal.

---
## ★★★ Iter H — THE ANSWER: stock uses FFE flow offload (292 Mbit/s); mainline lacks it
Stress-tested stock under SUSTAINED bulk: 30MB nsA->nsB (jack2<->jack4) THROUGH stock =
**0.82s = ~292 Mbit/s, COMPLETE, STABLE, no wedge** (ping after 3/3). Stock hw_trap (0x9234c060)
climbed only **+280** across the ~20000-packet 30MB blast (0x1d9→0x2f1). So only ~280 packets
(the learning/slow-start phase) hit the CPU; the remaining ~19700 were OFFLOADED TO HARDWARE.

⇒ DEFINITIVE: stock achieves stable high-throughput LAN<->LAN via the **FFE flow fast-path**
(hardware flow offload) — NOT basic-L2 hw_fwd (which is 0). After the CPU learns a flow
(ffe_learn_skb), the FFE offloads it to HW → line-rate, CPU untouched. MAINLINE has NO FFE → every
packet stays CPU-forwarded → <7 Mbit/s AND the CPU path saturates/WEDGES. **The "wedge" is a
SYMPTOM of missing FFE** (the CPU drowns in traffic that stock offloads to HW).

THE REAL TARGET for stable streaming = implement the FFE flow offload in the mainline driver.
PROVEN correct (stock = 292 Mbit/s via FFE). This supersedes BOTH the "HW L2 forwarding" goal
(false premise) AND treating the wedge as the root cause (it's a symptom). NOTE: ffe_learn_skb
lives in stock VMLINUX (not the decompiled .ko) per the egress saga — so FFE RE needs the chip's
FFE flow-table HW registers + how stock programs them (datasheet FFE block / runtime trace),
a substantial but now-correctly-targeted feature.
NEXT: RE the FFE — find the FFE/flow-table HW block (registers/indirect-RAM), how stock learns +
programs a flow into it, and what mainline must do to offload established flows. Start: datasheet
+ decomp for ffe_*/flow-table/napt regs; dump stock's FFE block before/after a flow; find the
flow-insert path.

---
## Iter I — FFE confirmed VMLINUX-only (NPU); PIVOT to wedge-prevention (up_thd/ddr_cache)
RE'd the FFE: ffe_learn_skb / ffe_receive_skb / ffe_get_npu_enable are all halt_baddata() STUBS in
the decompiled .ko → the FFE core is an NPU whose code lives in stock VMLINUX (not decompiled).
pp_pm_set_flow_info / pm_set_flow_cfg exist but are PM flow-STATISTICS, not the forwarding offload.
⇒ Implementing the FFE = a massive NPU + vmlinux RE (and likely NPU firmware) — out of reach now.
Per the loop's pivot rule (FFE needs vmlinux → pivot), the achievable target = STABLE (if slow,
CPU-bound) LAN streaming by fixing the WEDGE.

FRESH wedge hypothesis (NOT yet tested this way): stock qmg 0x9234c000 up_thd=0xfa0 (4000) +
ddr_cache_enable(1) [0x9234c004 bit1] vs mainline up_thd=0x50 (80). Earlier I raised up_thd on an
ALREADY-wedged device (no un-wedge). But I NEVER set the big up_thd + ddr_cache on a FRESH boot
BEFORE the load — to PREVENT the wedge (small on-chip CPU-queue threshold may overflow under burst
→ RED latch → wedge; a big threshold + DDR-backed cache like stock may avoid overflow). NEXT:
RAM-boot mainline fresh, set qmg up_thd field to 0xfa0 (0x9234c000) + ext_ddr_only_enable(0)/
ddr_cache_enable(1) (0x9234c004) BEFORE the bulk, then stress-test (30MB nsA->nsB through br0) →
if it does NOT wedge (sustains without dying) → that's the wedge-prevention fix → code it at init.
It'll still be CPU-bound (slow, no FFE) but STABLE. If it still wedges → pursue the TM-block
soft-reset/watchdog recovery (pon_reset + re-init) from the redwedge investigation.

MORNING-SUMMARY-READY CONCLUSION: stock's 292 Mbit/s is FFE/NPU (vmlinux, out of reach). Mainline
can at best do stable-but-slow CPU forwarding (if the wedge is fixed). True high-throughput needs
the NPU/FFE = a dedicated vmlinux-RE project.
