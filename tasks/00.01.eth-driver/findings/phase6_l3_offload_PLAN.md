# Phase 6 — HW L3 Offload: STATE + PLAN (2026-06-06)

## OBJECTIVE
Mainline Linux DSA driver for the ZTE H3600 (ZX279128S) where the CPU configures (routing/NAT/firewall)
and the HARDWARE forwards (offload), matching stock's hybrid model. End goal OpenWrt.

## THE MODEL (re-framed, ground-truth confirmed)
Stock HW L3 forward is **conntrack-driven, per-flow offload** via a PROPRIETARY framework
(`npu_register_driver`/`npu_hff_register`). There is **NO global "L3-route-enable" bit.**
```
1st pkts → ALWAYS trap→CPU→SW-route → conntrack ESTABLISHED
   → npu framework installs the hardfast (CLA-hash + PM next-hop/flow_info) for that 5-tuple
   → subsequent pkts HW-forward (~300 Mbit/s)
```
Master SW gate: `g_fast_opti` (tm.c:54280/54814). Per-flow chain: npu_drv_create_flow (switch.c:12240)
→ hf_set_l3_entry → sw_acl_l3_hardfast_session_add → zte_api_fast_l3_session_add → CLA/PM install.

## WHAT WORKS TODAY (on mainline, merged/verified)
- **L2 same-subnet LAN↔LAN HW switching: 332 Mbit/s, hw_trap flat** (DA-lookup, merged to main).
- **SW routing (L3 inter-subnet): ~9 Mbit/s** (every pkt trap→CPU→route→reinject). Works after rig fixes.
- TCP-ACK HW-forward + the redwedge fix (merged).

## WHAT WE DECODED (the full per-flow install recipe — ground truth from kotrace on stock)
Captured stock forwarding a routed LAN→WAN flow (328 Mbit/s) with custom kotrace.ko. Per-flow writes:
1. **PM next-hop** (PM ram_id 1, addr=NHIDX): `word0=next-hop IP, word1=MAC[2..5], word2=(MAC[0]<<8)|MAC[1]`.
2. **PM flow_info** (PM ram_id 0, addr=FIDX): next_hop_idx @ `(B7&7)<<6|(B6>>2)` + en bits (hl_ttl_en B4.2, etc).
3. **CLA hash** (ram2, addr=slot): action=OUTPORT (NOT a flow_info ptr; CLA→flow_info is implicit-by-flow);
   inport `(B[0xe]&0x3f)<<6|(B[0xd]>>2)`, outport `(B[0xd]&3)<<3|(B[0xc]>>5)`, valid_en B[0x10].1,
   windata (5-tuple key) @ bytes 0x13+ (proto @0x13, IP/port u16s @0x15,0x17,...). **windata layout INFERRED.**
4. **Extract** (ram1[0x98] + ram0[9]): per-PORT (not per-flow), one-time. ram0[9] = 16 byte-ptrs to ram1
   0x90..0x9f; v4 5-tuple uses ext-index 9. Mainline FFE init writes 0x90,0x91,0x94-0x97 (we added 0x92,93,98-9f).

PM indirect iface (driver, decoded): CMD 0x1DC014 / DONE 0x1DC018 / DATA0 0x1DC01C / DATA4 0x1DC100.
CLA indirect: CMD 0x1CC014 / DONE 0x1CC018 / DATA0 0x1CC01C. CMD=`addr|ram_id<<22|rw<<27`.
PM write order MUST be CMD-FIRST then data (fixed in zx_pp_pm_write_entry).
Hash engine: load 12 key words 0x9238c2c4.., trigger 0x9238c2c0=1, read 0x9238c2fc. Counters: hw_trap
0x9234c060 (climbs=trapped), cla_fwd 0x9238c3c0.

## THE GAP (why manual install still traps)
Mainline has **NO flow-offload framework** — `cls_flower` in zx-dsa.c:510 is a STUB (-EOPNOTSUPP); no
nf-flowtable/TC_SETUP_FT binder. Nothing drives the per-flow install+activation lifecycle. We wrote the
RAM entries manually (PM+CLA+extract, all committed) and the routed flow STILL traps (hw_trap climbs,
cla_fwd=0). TWO possible causes, must disambiguate:
  (a) CLA **windata** doesn't match our exact flow (layout inferred, never confirmed for lan→lan), OR
  (b) the npu "session" has **activation state beyond the RAM** we captured.

## PLAN (ordered)
### PIECE 1 — DECISIVE: can a manual RAM entry forward at all? (windata vs activation)
- Decode the exact windata byte→field layout from the captured stock entry (NAT'd flow 192.168.1.128↔10.9.9.x:
  `03005044 fa11c000 00000608 80000000 06000049 80c0a800 010a0901 51bfe209 00000014`). Learn the layout.
- Build correct windata for our lan→lan flow (172.31.9.50:40000→192.168.9.50:5201 TCP).
- Boot mainline, rig (hw_rig_setup.py), write PM+CLA(correct windata)+extract, run flow, measure hw_trap/cla_fwd.
- IF forwards → RAM is sufficient → PIECE 2 is viable. IF not → investigate npu activation (broader kotrace).
- ALT decisive: capture stock's COMPLETE entry set for a flow via fpga/clapeek read + replicate verbatim.

### PIECE 2 — implement the flow-offload binder (the driver feature)
- zx-dsa.c: register nf-flowtable / cls_flower offload (ndo_setup_tc TC_SETUP_FT). On an ESTABLISHED flow,
  parse 5-tuple + egress port + next-hop MAC from flow_cls_offload, build PM+CLA entries (the recipe),
  compute slot (hash engine), write them. Mirror stock's zte_api_fast_l3_session_add.
- ~hundreds of lines; we have the recipe + primitives (zx_pp_pm_write_entry, zx_cla_write_entry, hash engine).

### PIECE 3 — userspace (mostly works)
- nftables flowtable with `flags offload` (or kernel flow-offload) + ip_forward + conntrack → drives PIECE 2.

## TOOLING / SCRIPTS (all in tasks/00.01.eth-driver/scripts/ unless noted)
- hw_rig_setup.py — robust rig: device lan2=172.31.9.1/lan1=192.168.9.1, SRC=enx2c99 netns, DST=enx6c70,
  the enx6c70 r8152 netns-BOUNCE (bidi quirk), dup-IP cleanup, NM-unmanage. Verifies SW routing. ONE command.
- hw_l3_final_test.py — write PM next-hop+flow_info + CLA(fill520) + measure.
- hw_fasttest.py — fast extract+fill520+flow iteration. hw_extract_fix_test.py — ram1[0x90-9f]+ram0[9].
- debugfs: pmwrite "<ram_id> <addr> <w0..w7>", clawrite "<ram_id> <addr> <w0..>", fill520 "<15w>" (all 520
  slots in-kernel), clapeek, hashcalc, pktdeal. (zx-eth-main.c)
- kotrace (tasks/99.01.linux-stockport/kotrace/): kotrace_targets_l3pm2.h = the PM+CLA install trace.
  Build: cp <hdr> kotrace_targets.h; make CROSS=arm-linux-gnueabihf- KCFLAGS="-march=armv7-a -fno-pic -fno-PIE";
  restore full.bak. TFTP to device + insmod. Dump: /proc/kotrace_dump.
- Boot mainline: UART_TCP=1 python3 tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py (~115s). NEEDS a host
  NIC = 192.168.1.50 (tftp server) or U-Boot tftp times out (*T T).
- Boot stock: DTR_PULSE to :9998, let autoboot (no console interrupt). SSH/webUI: 192.168.1.1.
- Stock cmds: `echo '<cmd>' | python3 lib/ssh_shell.py -` (admin/UkuGPeyRDU). Stock has NO kprobe → use kotrace.ko.
- Stock webUI: Chrome MCP, http://192.168.1.1, admin/a3.141592A.

## RIG (physical, 2026-06-06) — 3 jacks connected
- enx2c99 (2c:99:75:31:3e:a9) → device lan2 (LAN/SRC side). TOLERATES netns.
- enx6c70 (6c:70:cb:b6:81:69) → device lan1 (DST side). r8152 BIDI QUIRK → needs netns bounce each boot.
- enxc8a362 (c8:a3:62:e9:59:00) → device WAN jack (was used as stock WAN host 10.9.9.1).
- GOTCHA: enx6c70 keeps getting 172.31.9.50 re-added (NetworkManager) → dup with SRC → breaks return path.
  hw_rig_setup.py cleans it + sets NM unmanaged.

## DECOMP / RE REFERENCES
- decomp_all_tm.c, decomp_all_switch.c (tasks/00.10.02.re-stock-kmods/findings/).
- Ground truth dumps: phase6_pm_nexthop_GROUNDTRUTH.txt, phase6_stock_hffgate_kotrace.txt.
- Memory: zte-hw-forwarding-deadend.md (full journal), zte-roadmap, zte-cla-ram-layout, zte-cla-hw-hash-engine.

## PIECE 1 RESULT (2026-06-06) — DEFINITIVE NEGATIVE: manual RAM install NEVER forwards
Confirmed the windata layout from the captured stock entry (proto@0x13, IP_A=src@0x15-18, IP_B=dst@0x19-1c,
sport@0x1d, dport@0x1f; each IP = two u16 (oct0<<8|oct1),(oct2<<8|oct3)). Stock fwd entry: inport=0,
outport=0(=regport0=WAN), valid byte0x10=0x49 (mine had 0x09). Rebuilt the CLA entry to match stock exactly
(valid=0x49) + correct windata + outport=2(lan1)/inport=3(lan2), wrote PM next-hop ram1[5] + flow_info ram0[5]
+ CLA at all 520 (fill520) + extract. ALL committed. RESULT: routed flow STILL traps (hw_trap +607 ≈ control,
cla_fwd=0). Also poked CLA config 0x9238c080|=0xE000 (up/dn_unicast_ctrl, the init-intended bits, Rank3) →
still +603. ⇒ EXHAUSTED the manual approach: extract tables, all 520 slots, PM next-hop+flow_info, windata-
corrected, valid=0x49, unicast_ctrl, pktdeal forward-all — NONE forward. cla_fwd=0 ALWAYS = the CLA hash is
NEVER consulted for our flow.
REFINED ROOT CAUSE: the CLA-hash/FFE fast-path is DORMANT on mainline. The packet never enters the extract/
hash stage (cla_fwd never moves), so writing entries into a dormant engine does nothing. The stock npu
framework (npu_register_driver/npu_hff_register, run once at module load) almost certainly does a GLOBAL
FFE-ENGINE ACTIVATION (route v4-to-me-MAC packets INTO the extract→hash→PM fast-path) that mainline never
does — distinct from the per-flow install we replicated AND from tm_pon_pp_initial. This is the real gate.
NOTE: L2 same-subnet HW forward works because it uses DA-lookup (a DIFFERENT path), not the CLA-hash/FFE — so
the FFE engine being dormant doesn't affect L2.

## NEXT EXPERIMENTS (to find the FFE-engine global activation)
1. kotrace `npu_register_driver` / `npu_hff_register` (switch.c:1407/12556) RE-TRIGGERED: on stock, rmmod+insmod
   the switch module (RISKY on live router) OR find a /proc/tm/shell call that re-runs the FFE-engine enable,
   with kotrace tracing it → capture the global HW write that activates the fast-path. SAFER: trace at the next
   stock boot via a baked kotrace (slot-A) so it patches before init runs.
2. Register DIFF: read the CLA/FFE/QMG ingress "to fast-path vs CPU" engine-enable registers on stock (idle,
   forwarding-capable) vs mainline. The diff = the activation. (CLA range 0xe3xxx reads via fpga at idle.)
3. Decode `npu_register_driver`/`npu_hff_register` + `tm_sdk_init` FFE-enable in the decomp for the GLOBAL HW
   write (not per-flow, not tm_pon_pp_initial) — what arms the extract→hash pipeline for routed packets.
The answer to "(a) windata vs (b) activation" is now (b)+: it's an engine-activation gate UPSTREAM of even the
hash consult (cla_fwd=0). Manual RAM is necessary but the engine must be armed first.

## FINAL RESULT (2026-06-06) — ALL pieces together STILL trap; cla_fwd NEVER moves
Combined ALL four on one boot, all committed+verified: (A) extract rule ram1[0x98]=v4-5tuple,
(B) ram0[9] word4=0x00150151 (index_valid bit8 — the agent's "engine arm"), (C) PM next-hop ram1[5] +
flow_info ram0[5], (D) CLA hash ram2 at all 520 (stock-exact valid=0x49 + confirmed windata + outport=2).
RESULT: routed flow STILL traps (hw_trap +203 ≈ control +202), **cla_fwd 0x9238c3c0 == 0 across EVERY
combination ever tried.** ⇒ DEFINITIVE: the packet NEVER enters the CLA/FFE extract→hash stage at all. The
gate is UPSTREAM of the CLA — at the QMG/SADM/parser L2-termination: a to-me-MAC IPv4 packet is sent to the
CPU-trap queue and NEVER offered to the FFE/CLA extract. (L2 same-subnet works via DA-lookup, a path that
doesn't go through QMG-trap.) NONE of the RAM tables / config regs we found divert it.

## HONEST CONCLUSION (judgment call — manual/poke approach EXHAUSTED)
After exhaustive RE (6 agents) + HW testing, the COMPLETE per-flow install + extract-arm have been decoded
and replicated, yet cla_fwd never moves. The mechanism that, on stock, diverts a to-me-MAC IPv4 transit
packet INTO the FFE extract pipeline (instead of QMG-trapping it) is NOT any standalone RAM/register we can
find — it appears bound to the npu framework's runtime operation and/or a chip ingress MODE we haven't
identified. Manual poking cannot get further. The realistic paths (both are dedicated multi-session efforts):
  (P-A) Implement the full npu-equivalent flow-offload framework in the driver + see if engaging via the
        proper Linux flow-offload lifecycle (TC_SETUP_FT, conntrack-established) makes the FFE engage —
        RISKY (manual install fails, so this may also fail), but it's the architecturally-correct path.
  (P-B) Deep RE of the ingress trap-vs-FFE decision: QMG (0x9234xxxx) / SADM (0x92384xxxx) / the parser /
        a PON-vs-switch chip MODE. A live stock-vs-mainline register diff of the FULL ingress region during
        a forward (not just the candidates) — needs reliable stock reads (the chronic blocker).
What we ACHIEVED (banked, major): decoded the entire HW L3 install recipe (PM next-hop/flow_info + CLA hash +
extract-arm, all formats + the windata layout), built the tooling (pmwrite/fill520/clawrite, hw_rig_setup,
the kotrace flow), confirmed L2 HW switch (332 Mbit/s) + SW routing work. The blocker is a single
undiagnosed ingress engagement gate.

## P-B ATTEMPT (2026-06-06) — blocked by stock-read reliability + no webUI reg tool
- Read mainline baseline ingress-config regs (reliable, saved /tmp/mainline_ingress_regs.txt): QMG 0x9234c000=
  0x03f40fa0, SADM 0x92384000=0x21 /04=0x2008, SBRG 0x92388004=0x040200ff /81c0=0xff /82c0=0xff /8340=0x015555ff,
  CLA 0x9238c080=0x600 /088=0x7fff /094=0x4 /0cc=0 /0fc,11c,120,124=0, ADM 0x92394000=0x1, DPA 0x92398000=0x10c0
  /014=0x1f, SPA 0x921d407c=0x1.
- Stock-side reads FAILED: dump_stock_regs.py (fpga -r + /dev/logger_main) TIMED OUT (chronic blocker — slow/flaky).
- webUI register tool: DOES NOT EXIST. "Gestión y diagnóstico" submenus = Estado/Cuentas/Sistema/TR-069/Registros/
  Diagnóstico-de-red/Tabla-ARP/Tabla-MAC/IPv6-Switch/Modo-de-trabajo. No raw reg read/write.
- webUI "Modo de trabajo" = MESH ROLE only (Mesh-Auto / Controlador-enrutador[current] / Agente / Router) — not the
  FFE/chip-forwarding mode; not the gate. (Device: H3600 V9, HW V9.0.20, SW V9.0.0P4_DIGI, SN ZTE0H89N5Q05834.)
- NOTE: the targeted ingress regs the agents checked ALREADY match stock==mainline, so a useful P-B diff must be
  BROAD — which is exactly what the slow/flaky stock fpga reads block. P-B needs a reliable bulk stock-read method
  first (e.g. a custom kotrace/kmod that dumps a reg range to /proc, or fixing the logger_main flood).

## FINAL STATUS — manual + readily-accessible RE avenues EXHAUSTED (honest judgment call)
HW L3 offload is a deep open problem. Definitive: cla_fwd never moves across every manual combination → the
to-me-MAC IPv4 packet never enters the CLA/FFE extract; the divert gate is undiagnosed and not reachable by the
RAM/register writes or reads we can do. Both remaining paths are dedicated multi-session efforts:
  P-A: implement the Linux flow-offload framework (TC_SETUP_FT/nf-flowtable in zx-dsa.c) — architecturally correct,
       but may still fail (manual install fails); needs the windata/sub-index parameterized from the recipe.
  P-B: broad ingress register diff stock-vs-mainline — BLOCKED until a reliable bulk stock-read exists (build a
       kmod that dumps reg ranges to /proc, like kotrace but for reads; the fpga+logger_main path is too flaky).
RECOMMENDED FIRST: build the reliable-stock-read kmod (unblocks P-B + all future stock RE), THEN the broad diff.

## ★ regdump.ko BUILT — chronic stock-read blocker SOLVED (P-B unblocked)
tasks/99.01.linux-stockport/kotrace/regdump.c (built like kotrace: `make -C <KDIR-abs> M=<kotrace-dir-abs>
obj-m=regdump.o ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- KCFLAGS="-march=armv7-a -fno-pic -fno-PIE" modules`;
staged tftp/regdump.ko). On stock: `tftp -g -r regdump.ko ...; insmod`; then
`echo "<phys_hex> <count_dec>" > /proc/regdump; cat /proc/regdump` → "<phys> <val>" per line, RELIABLE
(ioremap+readl, no /dev/logger_main flood). Mainline equivalent: debugfs `memdump <hexphys> <hexlen>` (same
output format). This unblocks ALL stock RE + the P-B diff.

## P-B DIFF #1 (2026-06-06) — done, config candidates NEGATIVE; diff was CONTAMINATED
Read 368 ingress regs (QMG/SADM/SBRG/CLA/ADM/DPA/SPA) on stock (regdump) vs mainline (memdump), saved
/tmp/stock_regs.txt + /tmp/mainline_regs.txt. Diffs found, but MOST are DYNAMIC (stock had active flows,
mainline idle): QMG counters 0x9234c044/4c/60, CLA indirect data-latches 0x9238c01c-0x05c (slots 0-15, transient),
CLA flow-state 0x9238c1cc-0x1fc (MACs/IPs of live flows). Real CONFIG diffs = SBRG 0x92388008(stock dfdf/main
ff00), 0x92388014(01000fff/000001c8), 0x9238801c(0001ffff/0064420f). TESTED: poked all 3 to stock values +
full L3 set (extract-arm+PM+CLA) → STILL traps (+201, cla_fwd=0). So those SBRG regs are NOT the gate.
⇒ The contamination (active-vs-idle) masks the real config diff. NEXT: CLEAN idle-vs-idle diff — boot stock,
ensure NO active flows (no webUI traffic, idle), regdump the blocks; boot mainline idle, memdump same; diff +
FILTER the dynamic regs (counters/data-latches/flow-state). The remaining static-config delta is the gate
candidate set — poke each on mainline + test. regdump.ko makes this now-tractable.

## CLEAN P-B DIFF + EMPIRICAL BEFORE/AFTER-FLOW (2026-06-06) — arm is BOOT-TIME, in an un-diffed reg/table
Clean idle-vs-idle diff (regdump.ko, stock ×2 to filter dynamics): NO static-config "FFE-arm" register in the
diffed blocks (QMG/SADM/SBRG/CLA-x128/ADM/DPA/SPA). Only SBRG 0x92388008/14/1c (tested NEGATIVE) + CLA indirect
data-latches + CLA last-packet status (0x9238c1e0-1fc = MACs/IPs of the LAST packet, dynamic — NOT a session table).
EMPIRICAL before/after a live LAN→WAN flow (snapshot CLA 0x9238c000 x192 idle vs mid-flow): ALL deltas
(0x9238c1cc-0x29c) are DYNAMIC — counters + per-packet capture regs. ZERO new config writes. ⇒ the per-flow
install writes ONLY the PM/CLA-RAM entries we already replicate; the FFE engine is ALREADY ARMED AT IDLE on
stock. So the ARM is BOOT/INIT-time, and it's in a register/indirect-table OUTSIDE the blocks I diffed (the diff
must broaden) OR an indirect RAM (SADM/DPA/parser/admit) the mainline replay missed. NOT defeatist — the npu is
GPL-RE-able via Ghidra (decomp_all_*.c). Agent a06d11284bbcb2355 running: exhaustive Ghidra enumeration of EVERY
HW write in the install chain (esp. direct writels the kotrace missed) + the boot-init arm. NEXT after agent:
diff/replicate the specific boot-time arm reg/table it identifies. regdump.ko makes any reg/range readable on
both stock+mainline now.

## STATIC-STATE REPLICATION EXHAUSTED (2026-06-06) + NEW LEAD: external SRAM hash
Agent (npu RX-path RE): ffe_receive_skb/ffe_learn_skb/npu_register_driver are in VMLINUX (U stubs in switch.ko),
a SW flow-cache (Broadcom-FAP style) — NONE touch MMIO. So there is NO HW "divert enable" bit; stock traps the
1st pkt to CPU, SW learns, installs HW per-flow, then HW forwards. We've now replicated EVERY static HW write:
extract ram1[0x90/0x98] (BYTE-MATCH stock, verified via indirect read), index ram0[9]=00150151, hash ram2 (×520),
PM next-hop ram1[5] + flow_info ram0[5], AND SPA classify matchram(0)+hashram(5) — ALL TOGETHER on valid rig →
STILL traps (hw_trap +404, cla_fwd=0). The CLA hash is NEVER consulted regardless. ⇒ no static RAM/register
makes the dormant FFE engine engage.
★ UNEXPLORED LEAD (the agent flagged, never investigated): init does __memzero(0xf1020000, 0x400000) +
__memzero(0xf1420000, 0x100000) = LARGE EXTERNAL SRAM hash regions (OUTSIDE chip MMIO 0x92xxxxxx). cla_set_
external_hash_table exists (tm.c:52800). HYPOTHESIS: the FFE hash/flow table lives in EXTERNAL SRAM at
0xf1020000/0xf1420000 that mainline never maps/inits → the HW engine has no backing store → dormant. This is
the one thing never explored (regdump.ko ioremaps only 0x92000000; need to map 0xf1020000 too).
NEXT: (1) read 0xf1020000/0xf1420000 on stock (extend regdump.ko ioremap or a 2nd map) — is it populated on
stock (flow entries) vs zero on mainline? (2) check if mainline's driver maps/inits this external SRAM at all
(grep 0xf1020000/0xf1420000 in zx-eth-main.c). (3) if the FFE hash is external + mainline lacks it → that's the
gap; init it + retest. This is GPL-RE-able (vmlinux.dis has the FFE core).

## CURRENT DEVICE STATE
On MAINLINE (rig up, SPA classify + extract-arm + PM + CLA all written — reboot restores). regdump.ko (stock-side)
+ memdump (mainline) for any reg. Static-state replication exhausted (cla_fwd=0 always). NEW lead = external SRAM
hash 0xf1020000. P-A needs the engine to engage first. Full journal: memory zte-hw-forwarding-deadend.md.
