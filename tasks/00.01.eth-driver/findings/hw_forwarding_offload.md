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

---
## ★ Iter J — CORRECTION: FFE is RE-able (NOT a dead-end). NPU driver in .ko + vmlinux.bin present
User was right — I gave up too fast. The NPU/FFE IS reverse-engineerable:
- The FULL npu_drv_* family IS in switch.ko decomp: npu_drv_create_flow (0x21d10) →
  create_flow_part_2 (builds a 5-tuple flow descriptor from the skb) → calls a registered HW-write
  func pointer (*DAT_0002b914)/(*npu_hff_func_tbl). npu_drv_{delete,refresh,free,dup}_flow,
  create_multivlan, indev_learn/outdev_learn all present + real.
- npu_hff_register(funcs[4]) (switch.ko 0x202d4) registers the 4 HW-write func pointers
  (npu_hff_func_tbl=funcs[0], DAT_0002b90c/910/914=funcs[1..3]) then npu_register_driver(&npu_drv).
  The CALLER that passes the 4 funcs = the "FastForward"/"KFASTFORWARD" module, which lives in
  stock VMLINUX — and **ext/extracted/vmlinux.bin (6.9MB) IS PRESENT** (strings: ffe_learn_skb,
  ffe_learn_passed_dev, FastForward, KFASTFORWARD). So the FFE flow-table HW-write funcs are
  recoverable by disassembling vmlinux.bin around those symbols.
- ALSO present: ext/<HW manual PDF> (V1.0 2018 — SCANNED/no text layer, would need OCR), stock
  .ko set (switch.ko/tm.ko/plat) in ext/rootfs/kmodule/, ext/extracted/{vmlinux.bin,zImage,uImage}.
- Device is GPL → ZTE must publish the kernel+driver source (incl. FastForward/NPU). GPL-source-
  search agent dispatched.
⇒ FFE OFFLOAD IS A REAL, RESOURCED RE TARGET (supersedes the "vmlinux out of reach" dead-end).
NEXT: (a) await the GPL-source agent (the actual FastForward/npu source would shortcut everything);
(b) disassemble ext/extracted/vmlinux.bin (arm-linux-gnueabi-objdump; find ffe_learn_skb +
npu_hff_register's caller → the 4 HW-write funcs → the NPU flow-table register interface);
(c) then define + implement the mainline FFE-offload (load NPU fw if any + the flow-insert path).
This is a substantial multi-session feature but the PATH IS CLEAR with all resources in hand.

---
## GPL-source search result (agent, 2026-06-04) — NO public source; RE is the only path
ZTE/Sanechips has NOT published the GPL kernel + NPU/FFE/switch driver source for the ZX279128S
anywhere reachable (no GitHub/Gitee/SDK hits for npu_drv_create_flow/ffe_learn_skb/zxylzb/
ZXICKERNEL/CONFIG_ZX_TM). The FFE/NPU offload (tm.ko, plat-zxylzb_9128S.ko) is closed; even the
GPL kernel is withheld in practice (kanxue thread: ZTE meets informal requests with commercial
licensing pushback). So there is NO source to port — RE (our vmlinux.bin disasm + switch.ko/tm.ko
decomp) is the only technical route.
LEADS: (1) closest artifact = github.com/xuejian1354/openwrt_cc (branch gateway-3.0, R2680) has
target/linux/zx279128/ + zxic128/127 board defs (BOARDNAME "ZTE zx279128 xPON (ARM)", cortex-a9,
KERNEL_PATCHVER 3.18) — but THIN WRAPPERS only (Makefile/base-files), NO kernel/driver source.
(2) firmware kernel = 4.1.25 (buildroot 2017.05, gcc 4.9.4); the FFE/NPU = a "fast L2/L3
forwarding" QoS framework under the ZXICKERNEL tag (binary only). (3) sibling ZX297520v3 mainline
port (gitlab.com/stefandoesinger/zx297520-kernel) = precedent for RE-driven porting w/o a GPL drop.
LEGIT LEVER (the GPL angle): formal GPLv2 §3(b) source request → tech.sp@zte.com.cn +
opensource.ztedevices.com (Wireless Home Gateway); ZTE owes source for 3yr from purchase. Worth
filing for the H3600 (cite the GPL kernel + in-firmware tm.ko/plat-zxylzb), escalate to the
shipping carrier / FSF gpl-violations if refused. (Surfaced to the user — their GPL point is
correct; ZTE is non-compliant in practice.)

---
## ★★★ Iter K — FFE OFFLOAD CHAIN FULLY MAPPED (RE-able end-to-end): it's the ACL L3-hardfast engine
Using Ghidra (vmlinux project decompile-by-address, Jython) + the switch.ko decomp, traced the
COMPLETE FFE flow-offload chain:
  ffe_learn_skb (vmlinux c04511f4: builds flow-key, MUST run in softirq) → notifier_call_chain
   → npu_drv_create_flow (switch.ko 0x21d10) → create_flow_part_2 (5-tuple descriptor)
   → (*npu_hff_func_tbl) == hf_set_l3_entry (switch.ko 0x12de8)
   → sw_acl_l3_hardfast_session_add (0x12d7c) → sw_acl_l3_hardfast_session_add_part_1 (0x125e0)
   → builds a 0xa0(160)-byte ACL session entry (5-tuple match + fwd action/egress) via
     sw_acl_setMtchInfo (0x11b38) / sw_acl_add_port_flowconfig (0x11e58) → programs the ACL HW.
The 4 HW funcs registered via npu_hff_register (from l3_hardfastReg @0x12404) are:
  hf_set_l3_entry (INSERT), hf_del_l3_entry, hf_query_l3_status, hf_entry_police2 — ALL in switch.ko.

⇒ THE FFE/NPU "flow offload" that gives stock 292 Mbit/s = the switch's **ACL engine running L3
"hardfast" sessions**: when the CPU learns a flow (ffe_learn_skb), it installs an ACL session
(5-tuple→forward-in-HW) so subsequent packets bypass the CPU. This is FULLY reverse-engineerable
from the decompiled switch.ko (only the ffe_learn_skb GLUE is in vmlinux, and we have vmlinux.elf
+ a working Ghidra decompile pipeline for it). The "vmlinux out of reach" dead-end was WRONG.

TO IMPLEMENT in mainline (well-defined now): (1) decode sw_acl_l3_hardfast_session_add_part_1's
160-byte ACL entry format + sw_acl_setMtchInfo + the ACL HW registers (ACL base — reserve_mem
ZX_ACL_BASE; the ACL indirect-RAM write); (2) hook flow-learn (e.g. on the bridge/forward path,
or a conntrack/flow-offload shim) to build + install the ACL session for established LAN<->LAN
flows; (3) age/delete via hf_del_l3_entry. Substantial but concrete + resourced.
NEXT: decompile sw_acl_l3_hardfast_session_add_part_1 + sw_acl_setMtchInfo (switch.ko) to C
(Ghidra by-address on the kmods project, or read the decomp directly) → extract the ACL entry
fields + the HW register sequence. Then prototype: poke an ACL hardfast session for a test
LAN<->LAN flow on mainline + measure hw_trap (should stay flat = offloaded).

================================================================================
## Iter L (2026-06-04 ~21:35 UTC) — FFE OFFLOAD IS NOW REGISTER-COMPLETE ★★★

Decompiled the rest of the chain (switch.ko → tm.ko → CLA HW). The ACL "hardfast session"
bottoms out at the **CLA hash table** — the SAME indirect-RAM interface I already poke
(clapeek/clapoke, DATASHEET §CLA `0x9238c014`). NOT a separate mystery ACL block.

### Full chain, now to the register:
```
ffe_learn_skb (vmlinux)
 → npu_drv_create_flow (switch.ko 0x21d10)
   → hf_set_l3_entry → sw_acl_l3_hardfast_session_add → _part_1 (switch.ko 0x125e0)
       builds 160B session; sw_acl_setMtchInfo (0x11b38) fills 5-tuple
     → zte_api_fast_l3_session_add (tm.ko 0x6558c)   ← real worker
         tm_acl_setMtchInfo(local_e4) builds match; local_148 = action/flag mask
       → tm_add_acl_flow_rule (tm.ko 0x5f430)
         → addFlowOperInfo + (addAclRule | tm_acl_fast_add)
           → cla_set_hash_table (tm.ko 0x15a14)      ← WRITES HW
               + SW shadow list g_FastList[512] keyed by cla_list_hash_addr_gen(&5tuple,0x28)&0x1ff
             → cla_set_indirect_rw_cmd / _data / _status
               → tmOnuRegWrite(field, val, idx, &claRegTable)  = CLA indirect HW regs
```

### cla_set_hash_table(hash_addr, entry[60]) — the exact HW write (decomp 0x15a14):
1. `hash_addr < 0x208` (max 520 entries).
2. Poll `cla_get_indirect_rw_status` (reg DONE 0x9238c018) up to 0x14× until ready.
3. **Bank-select ram_id from hash_addr range** (hash_addr is then made bank-relative):
   - `< 0x100`          → ram_id **2** (offset = hash_addr)
   - `0x100..0x17f`     → ram_id **3** (offset -= 0x100)
   - `0x180..0x1bf`     → ram_id **4** (offset -= 0x180)
   - `0x1c0..0x1ff`     → ram_id **5** (offset -= 0x1c0)
   - `0x200..0x207`     → ram_id **6** (offset -= 0x200)
4. `cla_set_indirect_rw_cmd(rw=0, ram_id, offset)` →
   `tmOnuRegWrite(0, offset | ram_id<<22 | rw<<27, 0, claRegTable)` = **write CMD 0x9238c014**
   (0x400000==1<<22, 0x8000000==1<<27 — matches DATASHEET cmd encoding exactly).
5. Write **15 words** (data_id 14→0, entry bytes [0x3c]→[0x00], 4B each):
   `cla_set_indirect_rw_data(data_id, word)` → `tmOnuRegWrite(2, word, data_id, claRegTable)`
   = **write DATA 0x9238c01c + data_id*4**.

⇒ This is the per-inport hash table I mapped in memory [[zte-cla-ram-layout]] (ram2..6). The
old paradox ("mainline replays CLA byte-for-byte yet traps") is RESOLVED: those were the STATIC
boot entries. Stock **dynamically inserts FLOW-FORWARD entries** into ram2..6 as it learns each
flow (valid_en + direct + outport + act_val=forward). Mainline never populates them ⇒ every flow
falls through to the trap default ⇒ CPU-bound + wedge. The offload = populate ram2..6 at runtime.

### 60-byte (15-word) hash entry fields (from cla_set_hash_table printks; bit-exact TBD at proto):
 - [0x00]: act_val[1:0], act_rp_en, queue_id, queue_rp_en, tcont_id(+[1])
 - [0x06..0x0a]: cpu_qid, cpu_qid_rp_en, mtu_val/mtu_rp_en, qos_id/qos_rp_en, bucket_info
 - [0x0b..0x0e]: wan_id, flow_pri, **outport**, inport   ← the forward decision
 - [0x0f..0x12]: tag_level, l2_type, pppoe_flag, extr_index, **rule_mode, direct, valid_en**, da_known
 - [0x13..0x39]: **windata0..19** (20×u16) = the 5-tuple match key/window
 - hash_addr (the bucket) = cla_acl_hash_addr_gen(5tuple) (TODO next: decode 0x16cdc).

### Why this is the breakthrough:
The offload is reachable from mainline with tools I ALREADY HAVE (the CLA indirect poke). No new
HW block, no firmware blob. PROTOTYPE PLAN (next fire): boot mainline, set up br0=lan1+lan3, start
a known LAN<->LAN unicast flow, then POKE one CLA hash entry (ram2, valid_en=1, direct=1,
outport=<lan3 phys>, act_val=forward, windata=that flow's key) and watch QMG hw_trap go FLAT for
that flow (= HW-forwarded, CPU bypassed). If it forwards → code cla_set_hash_table-equivalent as a
flow-offload hook in the mainline driver. NEXT decode: cla_acl_hash_addr_gen (0x16cdc) + the exact
windata packing in tm_acl_setMtchInfo (tm.ko 0x60ea0).

### Iter L addendum — hash bucket generator decoded (cla_acl_hash_addr_gen 0x16cdc):
`cla_acl_hash_addr_gen(hash_mode, key[0x2d], &out)`:
 - reverses the 45-byte (0x2d) match key, then runs a **byte-wise MSB-first CRC-32** over it.
 - **poly table selected by hash_mode**: 1→crctable_1EDC6F41 (CRC-32C), 2→crctable_F4ACFB13,
   3→crctable_32583499, 0/else→crctable_04C11DB7 (Ethernet CRC-32). `bucket = crc & 0xffff`.
 - 45-byte key fields: [0]outport(5b)+inport, [2]l2_type/tag_level/pppoe/direct, [3]ex_rule_id,
   [4..0x2c] extra_data0..19 (the packed 5-tuple/match window, 7-bit-offset packing).
 - hash_mode per table = cla_set_hash_poly_config (0x1103c). (cla_list_hash_addr_gen, used for the
   SW shadow g_FastList, is the SAME CRC-32 0x04C11DB7 over the raw 0x28-byte 5-tuple, &0x1ff.)

⇒ To place an entry the HW will actually hit, the bucket MUST equal CRC32(key) for that flow's key
under the table's configured poly. Computable offline, BUT the cleanest verification is EMPIRICAL.

### NEXT (empirical capture — device is on STOCK right now, perfect timing):
Stock's cla_set_hash_table PRINTS the full entry (windata, outport, act_val, hash_addr, valid_en,
direct) at g_tm_debug_level>=7. PLAN: on stock, raise tm/switch debug level → start a known
LAN<->LAN unicast flow (jack2<->jack4) → capture the printed FLOW-FORWARD entries from dmesg =
GROUND-TRUTH 60-byte entry + bucket for a real flow. Then boot mainline and replicate that exact
entry via clapoke (CMD 0x9238c014 ram2/3.., DATA 0x9238c01c x15) for the same flow + measure QMG
hw_trap (flat = offloaded) + throughput. This is the user's "dump de su inicializacion en stock".
Fallback if debug-level not reachable: fpga-oracle indirect-read ram2..6 on stock during a flow.

================================================================================
## Iter M (2026-06-04 ~21:50 UTC) — LIVE confirmation + entry-builder spec complete

Device is on MAINLINE (REPL :9999 + debugfs /sys/kernel/debug/zx_eth/ live). Worked the
prototype directly on mainline (skipped the unreliable stock boot).

### LIVE root-cause confirmation (clapeek on real silicon):
- `clapeek 2 0` → ram2[0] = `0100005d 00154000 80000408 90001417 00000045 000000e0 0...` (a
  multicast/control entry, 0100005d = IPv4-mcast MAC), ram2[1..3] = ALL ZERO.
- ⇒ the per-inport HASH fast-path table (ram2..6) is essentially EMPTY on mainline. Confirms
  live: mainline never installs per-flow forward entries → every unicast flow misses the hash →
  falls to the trap default → CPU-bound + wedge. This IS the missing FFE, observed directly.
- Static zx_cla_init_table[780] is ram_id=1 dominated (the ACL rule-TCAM, 17-word match+mask);
  ram2..6 (hash) is meant to be filled at runtime. mainline loads the static TCAM but nothing
  populates the hash → no fast-path.

### Tooling in place (no rebuild needed to experiment):
- `zx_cla_write_entry(e, ram_id, ram_addr, data[17])` ALREADY in the driver (zx-eth-main.c:2009):
  writes data[0..16] then CMD `ram_addr | ram_id<<22`. The proven indirect-write helper.
- CLA_REG_CMD=0x9238c014, DONE=0x9238c018, DATA0=0x9238c01c (npp_base 0x921C0000 + 0x1CC014..).
- `poke` debugfs writes any reg in [0x921c0000,0x923c0000) → can drive the indirect seq by hand.
- `clapeek` reads back (note: known off-by-one — read[A].word0 == table[A+1].word0).

### Full entry-build transform (now fully traced, switch.ko + tm.ko):
match struct (0xbc, built by tm_acl_setMtchInfo 0x60ea0): SIP@0x64, DIP@0x6c, proto@0x62,
sport@0x74, dport@0x76, rule_cfg@0x1c (0x301600 TCP/UDP up, 0x401600 other up, 0x1600 down)
  → addFlowOperInfo (0x5b30c) packs it into the 45-byte key (outport[0]&0x1f, inport, l2_type,
    tag_level, pppoe, direct, extra_data0..19 = the 5-tuple window, 7-bit-offset packed) +
    handles all WAN cases (NAT/PPPoE/DSLite/IPv6/6rd — ALL OFF for plain LAN↔LAN IPv4 unicast)
  → cla_acl_hash_addr_gen(hash_mode, key45, &hash): CRC32 (Ethernet 0x04C11DB7 default), bucket=
    hash&0xffff, collision-tracked via s_aclHashUsedCnt[bucket(+0x208)]
  → cla_set_hash_table(bucket, entry60): writes the 15-word entry into ram2..6.

### DECISION — implement, don't blind-poke:
addFlowOperInfo is WAN-feature-heavy; a byte-exact blind userspace poke is fragile. Instead PORT a
SIMPLIFIED basic-case builder into the driver as C (compile-checked structs, reuse
zx_cla_write_entry), covering ONLY LAN↔LAN IPv4 unicast (skip NAT/PPPoE/DSLite/IPv6/VLAN). Expose a
debugfs `claflow` trigger: write "<inport> <outport> <sip> <dip> <proto> <sport> <dport>" → driver
builds the 45-byte key, computes the CRC32 bucket, builds the 60-byte entry (valid_en=1, direct=1,
rule_mode, act_val=forward, outport), and zx_cla_write_entry's it into ram2. Then start a matching
LAN↔LAN flow and watch QMG hw_trap go flat / throughput jump. This tests the mechanism on ONE
controlled flow with debuggable C. If it forwards → wire it to a real flow-learn hook (ndo / bridge
fastpath / conntrack-offload). NEXT FIRE: write the claflow builder + debugfs in zx-eth-main.c,
rebuild, RAM-boot, test one flow. (Builder ref: the 45-byte key printk in addFlowOperInfo ~line
52360 + the 60-byte entry printks in cla_set_hash_table.)

================================================================================
## Iter N (2026-06-04 ~22:00 UTC) — COURSE-CORRECTION: hardfast is L3/NAT-routed; L2 ≠ L3-hash

Cross-checked against ffe_ringless_egress_re.md (2026-05-28, HIGH confidence). That session
established: **sw_acl_l3_hardfast_session_add programs an L3 NAT/ROUTING session** (carries
natip/natport/gemport/tcont/sessionid/pppoe → the WAN↔LAN routed/NAT fast-path). The cla
hash-table fast-path (ram2..6) I mapped in Iter K-M is fed by that L3 session API.

⚠️ MY 292 Mbit/s TEST WAS SAME-SUBNET (10.0.0.1/24 ↔ 10.0.0.2/24, jack2↔jack4) = pure **L2
bridging**, NOT L3 routing. So the L3-hardfast hash may NOT be the accelerator for that test.
Two distinct stock fast-paths likely exist:
  (A) L3-hardfast hash (ram2..6) — WAN/NAT ROUTED flows. (Iter K-M mapped this.)
  (B) L2 switch fabric — same-subnet LAN↔LAN, forwarded by the CLA L2 decision + FDB
      (CLA→QMG sw_fwd→DSCH→SOPC→MAC, NO CPU trap). This is what the 292 Mbit/s test used.

The old dead-end (zte-hw-forwarding-deadend) already showed: stock L2-forwards (hw_trap flat,
frames flow) while mainline TRAPS every L2 frame (hw_trap climbs) — and the lever was never
found because "the decisive stock-vs-mainline reg diff was NOT executable (stock boot unreliable)."

⇒ BOTH paths are blocked on the SAME missing experiment: **boot stock reliably + capture its
LIVE forwarding state during a same-subnet LAN↔LAN flow.** This single capture disambiguates
A-vs-B AND yields ground truth:
  - clapeek-equivalent ram2..6 DURING the L2 flow: if it POPULATES → the hash (A) handles L2 too
    → capture the entry, replicate (Iter M plan stands). If it stays EMPTY → it's the L2 fabric
    (B) → the lever is the CLA L2 forward decision (default-flow action / FDB / da_lookup), diff
    stock-vs-mainline CLA + QMG live.
  - Either way: diff stock's live CLA/QMG/SADM forwarding regs vs mainline during the flow.

DECISION: STOP blind-implementing claflow (might target the wrong path). PIVOT to the empirical
stock capture (the user's "dump de su init en stock"). Reliable stock boot = DTR cold reset +
DON'T interrupt autoboot → cspstart boots NAND stock (NAND still holds stock; mainline is RAM/TFTP
only). On stock: read ram2..6 via the indirect iface (devmem/reg tool: write CMD 0x9238c014 =
addr|ram_id<<22|1<<27 read, poll 0x9238c018, read 0x9238c01c x15) idle-vs-during-flow; capture
QMG (0x9234c044 sw_fwd / 0x9234c060 hw_trap) + CLA forward regs. NEXT FIRE: execute the capture.

================================================================================
## Iter O (2026-06-04 ~22:25 UTC) — ★★★ EMPIRICAL BREAKTHROUGH on LIVE STOCK ★★★

Booted NAND stock (DTR power-cycle, no autoboot interrupt — RELIABLE). /bin/fpga reads/writes
regs via kmsg (`fpga -r/-w <wordidx>`, wordidx=(phys-0x92000000)/4; value prints to /proc/kmsg).
Built a same-subnet LAN↔LAN flow that traverses the device: jack2 (enxc8a362e95900) stays in
default ns @10.0.0.1 (also .50 for SSH), jack4 (enx6c70cbb68169) → netns nsB @10.0.0.2, static
neigh both ways. SSH to .1 preserved throughout.

### THE MEASUREMENTS (QMG: sw_fwd@44=0xd3011, sw_fwd@54=0xd3015, hw_fwd@5c=0xd3017, hw_trap@60=0xd3018):
| state            | sw_fwd@44 Δ/3s | hw_fwd@5c | hw_trap@60 Δ/3s | throughput |
|------------------|----------------|-----------|-----------------|------------|
| idle             | ~0             | 0         | ~0              | -          |
| ICMP ping -f     | +1761          | 0         | +1759           | (CPU)      |
| **TCP iperf3**   | **+25 (flat)** | **0**     | **+25 (flat)**  | **353 Mbit/s** |

⇒ CONFIRMED: stock HW-OFFLOADS TCP/UDP 5-tuple LAN↔LAN flows (353 Mbit/s, 1.23 GB, 0 retr) with
hw_trap FLAT = CPU fully bypassed. ICMP is NOT offloaded (traps to CPU, hw_trap climbs in lockstep
— same as mainline). The offload is **PROTOCOL-SPECIFIC (TCP/UDP only)**, matching the hardfast
rule_cfg keyed on proto 6/0x11. Same-subnet L2 TCP IS accelerated (keyed on the 5-tuple).

### ⚠️ THE OFFLOAD TABLE IS *NOT* THE CLA HASH (ram2-6) — Iter K-M target was WRONG:
Full scan of CLA hash during the live offloaded flow:
- ram2 (256 buckets): only 14 non-zero, ALL `01:00:5x` multicast/IGMP L2 entries — NO unicast 5-tuple.
- ram3,4,5,6 (full): ALL ZERO.
So cla_set_hash_table (ram2-6) holds multicast/L2 classify entries, NOT the unicast TCP fast-path.
Moreover BOTH QMG sw_fwd@44 AND hw_trap are FLAT during TCP ⇒ offloaded packets bypass the entire
CLA→QMG→DSCH pipeline (the "ring-less" datapath from ffe_ringless_egress_re.md).

⇒ The TCP offload = the FFE / **sbrg_add_ipv4table** path (switch.ko zte_api_fast_l3_session_add →
sbrg_add_ipv4table = SBRAG L3 ipv4 forwarding table), NOT the CLA hash. The tm.ko
cla_set_hash_table path I traced in Iter K-M is a DIFFERENT (L2/multicast) table.

### NEXT (capture the REAL offload table — device staying on stock, harness live):
Diff the SBRAG L3 ipv4 table (+ FFE regs) BEFORE vs DURING the TCP flow to find the inserted
forward entry = ground truth. SBRAG base 0x92388000 (indirect CMD 0x92388014/DONE/DATA per
DATASHEET); decode sbrg_add_ipv4table (find its decomp + the ipv4-table ram_id/addr). Also sweep
for an FFE-specific counter that ticks with the TCP flow (MAC2 TX-OK 0xa01c6 climbed?). Then
implement the SBRAG-ipv4 / FFE flow-insert in mainline. NOTE: jack4 is in netns nsB — RESTORE to
default ns before any TFTP boot. Device left on stock for continued capture.

================================================================================
## Iter P (2026-06-04 ~22:50 UTC) — ★★★ THE MECHANISM: protocol-discriminated HW L2 switching

Continued on live stock. Confirmed the 360 Mbit/s TCP flow is REAL (nsB tx = 90MB/2s) and
offloaded (hw_trap flat). Then called the L3 fast-flow dumpers via /proc/tm/shell DURING the flow:
  `echo -f tm_show_fast_rule_list > /proc/tm/shell`     → EMPTY (header only)
  `echo -f sbrg_print_ipv4table   > /proc/tm/shell`     → EMPTY (header only)
So the L3 fast-rule / SBRAG-ipv4 / CLA-hash paths are ALL empty during the offloaded flow.
⇒ stock's same-subnet LAN↔LAN TCP offload is NOT any L3 fast-path — it's PLAIN HARDWARE L2
SWITCHING (FDB lookup → egress port, in the switch fabric).

### THE DECISIVE TEST (clean, same ports/MACs/subnet, simultaneous):
With the TCP flow running (hw_trap flat), fired 2000 concurrent ICMP (ping -f) nsB→10.0.0.1:
  hw_trap(0xd3018): 0x1d52 → 0x2d0b = **+0xFB9 (+4025)** ≈ 2×2000 (both directions of the ICMP).
Meanwhile the concurrent TCP added ~0 to hw_trap.
⇒ AT THE SAME TIME, on the SAME ports/MACs: **TCP data = HW-switched (no trap); ICMP = trapped to
CPU.** This is PROTOCOL-DISCRIMINATED forwarding, NOT learning/FDB-based (MACs already learned; both
run concurrently). The CLA classifier decides per-protocol: control (ICMP/ARP/IGMP) → trap to CPU;
TCP/UDP data → HW L2-forward to the egress port.

### Reframes the WHOLE problem (supersedes the Iter K-O "FFE/hash offload" framing):
- Stock's "292/353 Mbit/s LAN streaming" = the switch fabric doing HW L2 forwarding of TCP/UDP,
  with the CLA trapping only control protocols. NO per-flow software learning needed for L2.
- MAINLINE traps EVERYTHING (incl. TCP) → CPU-bound + wedge. The old "no basic-L2 HW forwarding on
  this chip" conclusion ([[zte-hw-forwarding-deadend]]) was WRONG — it was tested with ICMP/ping,
  which traps even on stock. TCP/bulk IS hw-switched on stock.
- ⇒ THE LEVER: make mainline's CLA classify TCP/UDP L2 unicast as FORWARD (not trap), like stock.

### NEXT (now decisively targeted + EXECUTABLE — stock boots reliably now):
Diff stock-vs-mainline the CLA forward/trap DECISION for a TCP L2 unicast frame. On stock (live,
during the flow) dump the CLA rule-TCAM (ram1) + the trap/forward action config (trap_acl_en
0x9238c080, oth_l3_pkt_action 0x9238c0cc, default-flow actions 0x9238c0fc/11c/120/124, transfer_en
0x92388004, da_lookup); then boot mainline and read the SAME regs; the delta governing
TCP-forward-vs-trap = the fix. (Old dead-end said ram1 entries replay byte-identical yet stock
forwards — so the lever is likely a global action/mode reg or an incomplete ram1 replay; the live
protocol-discriminated behavior now gives an exact repro to bisect against.) Implement the fix in
the mainline CLA init. Stock fpga idx=(phys-0x92000000)/4, output via /proc/kmsg.

================================================================================
## Iter Q (2026-06-04 ~23:20 UTC) — ★★★ MAINLINE TCP TEST: HW-forwards DN but TRAPS UP → WEDGES

The realization that unlocked this: ALL prior "mainline traps everything" tests used ICMP ping —
and ICMP traps even on stock (Iter P). NEVER tested mainline with TCP. So: booted mainline (TFTP),
br0=lan1(jack2)+lan3(jack4), host netns flow nsA@10.0.0.1 <-> nsB@10.0.0.2, ran iperf3 TCP.

### RESULT — mainline DOES HW-forward TCP (one direction), then WEDGES:
mainline /sys/kernel/debug/zx_eth/pipeline_stats (QMG, DN=toward-LAN / UP=toward-CPU):
| state            | DN sw_fwd | DN hw_fwd | DN hw_trap | UP hw_trap | RED drops |
|------------------|-----------|-----------|------------|------------|-----------|
| baseline         | 96        | 0         | 0          | 42         | -         |
| during TCP (~8s) | 1084      | **4240**  | **0**      | **1033**   | -         |
| after stall      | 1091      | 4258      | 0          | 1033       | **157**   |
iperf3: 1st sec **51 Mbit/s** (127 retr) → collapses to **1.7 Mbit/s** total (134 retr) → tx stalls.

⇒ DIAGNOSIS: mainline HW-forwards the BULK (DN) direction (hw_fwd 0→4258, hw_trap=0 on DN — IT
WORKS!) but TRAPS the reverse (UP) direction (the TCP ACKs: hw_trap 42→1033). The UP/CPU trap path
WEDGES under load — RED[0x1a044]=157 drops (the unicast→CPU RED latch, [[zte-redwedge-unicast-cpu]])
— stalling the reverse path so TCP collapses. So the blocker is NOT "no HW forwarding" (DN works!),
it's (a) the UP direction traps instead of forwarding, and (b) that trap path wedges.

### Contrast with stock (Iter O/P): stock's hw_fwd(QMG)=0 during its 360Mbit/s offload — stock's
datapath BYPASSES QMG entirely (pure fabric switch, both directions), so no CPU path, no wedge.
Mainline routes through QMG and traps UP → wedge. Two possible fixes:
  (1) Make the UP direction ALSO HW-forward (eliminate the CPU path → no wedge). Investigate the
      DN-vs-UP asymmetry: why does lan3→lan1 (DN) forward but lan1→lan3 (UP) trap? per-port/
      per-direction CLA or DSA-conduit config.
  (2) Prevent the RED wedge on the UP/CPU path (the old untested hypothesis: QMG up_thd=0xfa0 +
      ddr_cache_enable; or a RED/TM soft-reset/watchdog). Even if UP stays CPU-forwarded, if it
      doesn't wedge the flow could sustain (slower but stable).

### NEXT FIRE: (a) characterize the DN/UP asymmetry (read per-port CLA/forward config for lan1 vs
lan3, both directions); (b) try wedge-prevention live (poke QMG up_thd 0x9234c000 + ddr_cache
0x9234c004 BEFORE the flow) + rerun iperf → does TCP sustain? (c) if UP-forward is reachable, poke
it. Goal: sustained TCP through br0 with RED drops flat = stable LAN streaming. Device on mainline.

================================================================================
## Iter R (2026-06-04 ~23:50 UTC) — RED out-buffer share-pool: the wedge-prevention lever (hypothesis)

Found a concrete stock-vs-mainline gap in RED init. Stock's pon_tm_red_init (decomp_all_tm.c
~42509) sets GLOBAL RED enables BEFORE the per-queue loop:
  red_set_cfg_enable(0,1); red_set_open_out_en(1); red_set_trap_color_en(1); red_set_share_mode(1);
  red_set_in_share_max(0x3ff); red_set_up_out_share_max(0x3fff);
then per-queue out-buffer: q0-15=(guart 0x3ff,max 0), q16-335=(0x40,0x7ff), q336-375=(0x40,0x200/0x80),
q376-391=(0x40,0xc00), q392-399=(0x40,0x3ff).
Mainline's zx_tm_red_init (zx-eth-main.c:2352) does ONLY the 4 per-queue indirect loops — it NEVER
sets the global share-pool maxes. RED regs (DATASHEET): 0x92344004 [4]open_out_en/[3]trap_color_en/
[2]share_mode/[1:0]cfg_enable; 0x92344040[12:0]=in_share_max; 0x92344074[14:0]=up_out_share_max.
HYPOTHESIS: mainline leaves in_share_max/up_out_share_max at reset (0) → the OUT (CPU/trap) queue
has no share buffer → overflows under the reverse-ACK trap load → RED drops → unicast→CPU WEDGE.

### Test attempt (INVALID — methodology): poked 0x92344040=0x3ff + 0x92344074=0x3fff on mainline
(readback OK) but the device was ALREADY WEDGED from the Iter Q iperf (tm_rx_count frozen at 1033,
ping 100% loss, hw_trap latched at 1033). Poking RED AFTER the wedge does NOT recover it (matches
the old DATASHEET note: poking RED didn't un-wedge port1). ⇒ the share-max must be set on a CLEAN
device BEFORE load to PREVENT the wedge. Could not read mainline's pre-poke RED values (no od/
hexdump on the C-init REPL; 0x92344040/74 not in regdump windows; mem file needs a hex tool).

### NEXT FIRE (clean-boot prevention test): TFTP-boot mainline fresh → IMMEDIATELY (before any
traffic) poke 0x92344040=0x000003ff, 0x92344074=0x00003fff, and ensure 0x92344004 bits [2][3][4]
set (open_out/trap_color/share_mode) → set up br0 + netns → run iperf3 TCP → check: does the UP
hw_trap KEEP CLIMBING (CPU path alive, not latching at a fixed number) + RED drops stay ~0 +
throughput SUSTAIN? If YES → wedge prevented → codify in zx_tm_red_init (add the 5 global
red_set_* equivalents: open_out_en/trap_color_en/share_mode/in_share_max=0x3ff/up_out_share_max=
0x3fff via the RED direct regs 0x92344004/40/74) → rebuild → reverify. If NO → the share-pool isn't
the lever; PIVOT to the per-queue out-buffer max for the CPU queue, or the DN/UP asymmetry.
Device currently WEDGED (needs reboot for a clean test).

================================================================================
## Iter S (2026-06-04 ~00:30 UTC) — BP pool 1024→8192 (stock match) DONE; but wedge root = TM RX ring

USER LEAD: "how big is the queue in stock? maybe mainline is too small?" — spot-on instinct.
FOUND: mainline TM_BPPE_POOL_SIZE=1024 vs STOCK=8192 (stock prints BPPE_POOL_SIZE=0x2000). The 1024
was a leftover from when pools used dma_alloc_coherent (18MB CMA alloc failed); the driver now CARVES
pools from a reserved region via memremap_wc (zx_tm_alloc_pools, CARVED_BASE 0x4C000000), so that
reason is dead. 8192×TM_BP_SIZE(2304)=18MiB fits the BP region (0x2C20000→0x3F1F000 ≈ 20MiB). FIXED:
restored TM_BPPE_POOL_SIZE=8192 (propagates to BPPE table, BMU_POOL_SIZE 0x8048, BUCKETS_M1 0x8058).
This is a correct stock-matching fix (kept) — prevents real BP exhaustion under sustained load.

### BUT it did NOT fix the wedge. Rebuilt (build_slotA.py) + TFTP-booted + iperf3 TCP:
  37.7 Mbit/s (1st sec) → collapse to 1.5 Mbit/s; tm_rx_count LATCHED at 1035 (was 1033/1048 w/
  pool=1024 — UNCHANGED by the pool bump); tm_napi_count froze at 129.
⇒ the ~1024 latch is NOT the BP pool — it's the **TM RX DESCRIPTOR RING (TM_RX_DESC_PER_Q=1024)**.
After consuming exactly one ring's worth (~1024 trapped frames), the CPU RX stops and NAPI is never
rescheduled. The TM RX consumer (zx_tm_net_poll ~2864-3027) LOOKS correct — it frees BP
(zx_bmu_free_bp), invalidates each desc (clears len desc[12]), advances rx_head, and ACKs HW
(zx_tm_release_rx_desc). Yet it latches after one wrap ⇒ a producer/consumer/ACK pointer DESYNC on
ring-wrap, OR the trap/RX IRQ stops firing after the ring fills once (tm_napi frozen at 129).

### NEXT FIRE: pin the TM RX ring wrap bug. (a) Read the TM RX "pending count" register the poll
keys on (line ~2856 `pending`) live during the wedge — is it stuck at 0 (HW thinks nothing
pending = consumer ptr not advanced) or nonzero (NAPI not scheduled = IRQ stopped)? (b) Compare
zx_tm_release_rx_desc + the pending-count read vs stock soft_release_rx_desc / pon_tm_net_poll
(decomp): does stock write a producer/consumer cursor mainline misses on wrap? (c) Quick probe:
after the wedge, does a 2nd flow or an `echo > some-irq-rearm` un-stick it (→ IRQ) vs stay dead
(→ ring ptr)? (d) candidate fix: re-arm the TM RX IRQ / reset the ring head at end of poll, or
correct the release-desc cursor. Then rebuild+test sustained TCP. Device on mainline (wedged).

================================================================================
## Iter T (2026-06-04 ~01:10 UTC) — ★ WEDGE ROOT CAUSE FOUND: RX desc release leaks skipped slots

Decisive live test on the wedged device: sent 20 fresh pings → tm_irq_count STAYED frozen at 129
(= tm_napi_count), tm_rx_count stuck 1035, tm_tx_count=1098 (TX fine). ⇒ the trap RX IRQ stopped
firing entirely = HW STOPPED PRODUCING RX after exactly one TM_RX_DESC_PER_Q(1024) ring. Not the BP
pool (8192 now), not RED. It's RX DESCRIPTOR RING SLOT EXHAUSTION.

ROOT CAUSE (stock-vs-mainline diff of the RX poll release):
- Stock pon_tm_net_poll (decomp_all_plat_zxylzb_9128S.c:8724-8730) releases ALL iVar9 consumed ring
  slots in TWO calls: soft_release_rx_desc(1,q,sop=0, iVar9-local_4c) [the non-SOP/skipped slots] +
  soft_release_rx_desc(1,q,sop=1, local_4c) [the SOP slots]. Sum = iVar9 = every slot it advanced past.
- Mainline zx_tm_net_poll (zx-eth-main.c:2864-3027) SCANS FORWARD skipping stale/empty descs (len=0,
  line 2871-2878 — "HW writes out-of-order, idx 0 then 12+") but only calls
  zx_tm_release_rx_desc(q, ack, sop=1) where ack = DELIVERED frames. The SKIPPED ring slots (the gaps
  it scanned past) are NEVER released to HW.
⇒ skipped slots accumulate; after the consumer advances through all 1024 ring positions, HW sees no
freed slots → stops producing → no more RX IRQ → wedge. Matches the exact 1024 latch + frozen IRQ.

release reg encoding (both stock+mainline identical): TM[0x4068]=(1<<14)|(count<<4)|q|(sop<<3); TM[0x4064]=1.

### THE FIX (next fire): make mainline release EVERY ring slot it advances past, like stock. Track
the total slot advance per poll (current rx_head movement incl. skips), not just delivered frames.
Implement: per queue, record start_head; after the take-loop, slots_advanced = (rx_head - start_head)
& (TM_RX_DESC_PER_Q-1) [handle wrap]; release that many (e.g. zx_tm_release_rx_desc_raw(q, skipped,
sop=0) for the non-delivered slots + (q, ack, sop=1) for delivered, summing to slots_advanced — mirror
stock's two-call split). Then rebuild → boot → iperf3 TCP → tm_rx_count climbs PAST 1024, IRQ keeps
firing, throughput SUSTAINS = STABLE LAN STREAMING. (Caution: only release slots HW actually produced
— if the scan skips truly-unproduced slots, releasing them over-credits; verify by watching pending
not go negative / no spurious RX. Stock releases the full scanned range, so follow that.)
