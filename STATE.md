# STATE — what's on the device RIGHT NOW

## ★ ROADMAP — stock features, brought up one-by-one on MAINLINE (added 2026-06-04)

**★ OBJECTIVE (the north star):** match stock's HYBRID model — **configure everything on the CPU
(software control plane: routing/firewall/NAT/DHCP/DNS/PPPoE), and let the HARDWARE do the actual
forwarding (offload).** So for every data-path feature the recipe is: (1) bring it up in SOFTWARE on
mainline (works now, CPU forwards — proves functionality), then (2) OFFLOAD its data path to HW
(the chip forwards, CPU just sets up). NOT "SW-only" and NOT "HW-only" — the stock hybrid. The CPU
must never be the forwarding bottleneck once a flow is established.

**Architecture truth (RE'd + measured): stock is HYBRID.** Control plane = CPU/software
(standard Linux: `iptables`/`ip6tables` firewall+NAT, conntrack, `pppd` PPPoE, `dnsmasq`
DHCP+DNS, kernel routing — all present in ext/rootfs). Data plane = HARDWARE (switch fabric
for L2; the **FFE** flow-offload for L3/NAT once a conntrack flow is ESTABLISHED). The FFE
(`ffe_ip_conntrack_check`, vmlinux) is the glue: CPU/conntrack decides, then it installs a HW
hardfast session so the bulk forwards in HW = ZTE's own version of Linux `flow_offload`/flowtable.
⟹ **Functionality = software on the CPU → works on mainline NOW with the same tools (no chip RE).
Performance (wire-speed routed/NAT) = needs the FFE-equivalent HW offload (flowtable + the chip
CLA-hash hardfast we mapped).** A single armv7 core won't route gigabit in pure SW — that's WHY
stock has the FFE.

Legend: [SW]=software, works on mainline now · [DRV]=driver/RE chip work · [✅]=done · [→]=next.

- **Phase 0 — L2 switch foundation [✅ DONE]:** DSA driver, HW L2 forwarding incl. the TCP-ACK
  HW-forward fix (#36), port1 ingress (#23), egress (TX-DAC/eg_port), unicast→CPU wedge (bit14,
  #27), soft-float userland. LAN↔LAN streams in HW; ping/iperf/bridge work. [DRV]
- **Phase 1 — WAN + NAT router (the spine):** 1.0 WAN=MAC4 (RGMII, ext ZX5201 @ MDIO 0x08) brought
  up + exposed as DSA port lan4 [✅]; **1.0b WAN MAC4 RX+TX [✅ DONE 2026-06-04]** — RX +1.1M, and
  CPU→MAC4 TX VERIFIED (MAC4 ctrl=0xbb6003 like the LAN MACs, TX-ok 0x92300718 climbs +6/egress,
  SOPC bridge enabled). The long "MAC4 TX never reaches the wire" blocker was a register-address
  error (read TM 0x92340718 as MAC4 TX-ok; MAC4 is at npp_base 0x921c0000 + 0x140000 = 0x92300000).
  Also ported stock zx5201_config's pad-clear (pin_mux[0x0c]&=0xffe7f7ff) — stock-faithful. End-to-end
  visible WAN just needs a host NIC on the physical WAN jack. — **1.1 [→ NEXT]** rebuild kernel WITH
  netfilter (CONFIG_NETFILTER/NF_CONNTRACK/NF_NAT/IP_NF_*, ip_forward) + iptables in initramfs;
  1.2 WAN IPv4 via udhcpc, then PPPoE via pppd [SW]; 1.3 `ip_forward` + masquerade LAN→WAN [SW].
  ⇒ working NAT router / internet sharing.
- **Phase 2 — LAN services [SW]:** dnsmasq (DHCP server + DNS + static leases), static routes.
- **Phase 3 — Firewall/security [SW]:** zone firewall (iptables/nftables: WAN-in drop, LAN-out
  accept), IP/port filter, DoS guard, port-forward (DNAT), DMZ, ALG (conntrack helpers), UPnP-IGD
  (miniupnpd), URL/parental filter.
- **Phase 4 — IPv6 [SW]:** WAN DHCPv6-PD / SLAAC, RA on LAN (radvd/odhcpd), prefix delegation, v6 firewall.
- **Phase 5 — QoS [SW now / DRV later]:** tc queue/shaper/speed; HW shaper (SCH/OPC) offload later.
- **Phase 6 — HW flow offload [DRV — the big perf piece]:** wire the chip flow engine into Linux
  `flow_offload`/flowtable (the FFE-equivalent: conntrack-ESTABLISHED → CLA-hash hardfast session,
  chain mapped in hw_forwarding_offload.md Iter L). Gives wire-speed routed/NAT. Only needed if
  software routing on the armv7 core can't keep up.
- **Phase 7 — Multicast [DRV+SW]:** IGMP/MLD snooping (DSA offload) + proxy (for IPTV).
- **Phase 8 — DSA polish [DRV]:** VLAN offload, port mirroring, FDB-offload sync (bridge↔SBRAG) —
  mainline-quality switch.
- **Phase 9 — WiFi [DRV — big]:** WiFi driver (mt7915 refs seen) + hostapd; SSIDs, mesh, band-steering, DFS.
- **Phase 10 — WAN GPON [DRV — big]:** the PON MAC uplink datapath (only if GPON WAN needed vs eth-WAN).
- **Phase 11 — extras [SW]:** VoIP (SIP), USB/Samba/DLNA, TR-069 mgmt, web UI.

**Working style: one feature at a time on mainline, verify each before the next.** Immediate next =
Phase 1 (WAN eth + NAT). Most of Phases 1–4 are software the CPU runs today (stock uses the same
binaries); the chip-specific lifts are Phase 6 (HW offload), 9 (WiFi), 10 (GPON).

## Journey-to-date (so future-you remembers why)

1. Tried mainline 6.6 with PCIe / WiFi / wpa_supplicant — none worked.
2. Pivoted to building **our own ethernet driver** (`zx279128-eth.c`)
   using brute-force stock register replay (22,363 entries + 1025 pp_pm +
   780 CLA dumped via stock sysfs hooks). TX path partial; RX path dead.
3. **Got UART output on stock kernel**: cspd 3-byte patch + `kmsg2uart`
   daemon (mmap PL011 DR at ZTE-shifted `+0x04`, drain `/proc/kmsg`).
   Stock kernel has standard pl011 driver hard-coded to DR+0x00 (silent).
4. **Verified kprobes/ftrace are NOT compiled** in stock kernel
   (`# CONFIG_KPROBES is not set`, no `/sys/kernel/debug/tracing/`).
5. **Built kotrace** (loader-notifier + RAM patcher,
   `tasks/00.01.eth-driver/kotrace/`) — replaces target fn prologues with
   `b thunk` after the kernel loader resolves all symbols. Post-boot
   loading works for 2157 functions across plat/tm/switch/mt7915/idmfdb
   and routinely captures 32 k+ entries during a ping. Bake-in init
   capture (insmod via `/etc/init.norm`) is **parked** with a silent SoC
   reset — see `tasks/00.01.eth-driver/findings/kotrace_init_capture.md`.
6. **PING BIDI on mainline** (2026-05-24, task #50) — `pon_tm_net_tx` +
   `bp_idx 10-bit decode` + frame-at-`bp_buf+16` fixes landed; RX/TX
   both alive. Refactor + iperf still pending (tasks #37, #38, #47).
7. **WiFi works** (2026-05-04, `tasks/00.07.wifi/`) — MT7915 over the
   internal PCIe link → wlan0 + internet.
8. **Now**: post-boot kotrace captures + Ghidra are the live RE loop.
   Shell access on the bake-in slot-A rootfs is via netshell
   (`nc 192.168.1.1 9001`) since the ZTE-patched dropbear wedges on
   exec — see CLAUDE.md "SSH gotchas".
9. **TX egress hairpin hunt (2026-05-28)**: RX solid; TX still hairpins
   (CPU frames loop back, never egress; loopback ~15/test, TM[0x10058]=0).
   Landed stock-faithful fixes: flood=CPU-only (PP[0x8340]), isolation-table
   port-remap (loopback 33→15), FDB aging, broadcast gates off. Built a
   **live poke/peek debug tool** (regdump+poke debugfs) — reflash-free reg
   R/W over socket 9999. Ruled out MAC egress-enable as the gate (enabling it
   storms without `+0xE0=0x00011200`; with full smac_init bring-up it stops
   storming but still doesn't egress). Remaining gate: switch routes CPU-TX
   back to CPU despite host-MAC learned in FDB on internal port 3. See
   `tasks/00.10.02.re-stock-kmods/findings/session_2026-05-28_tx_egress_state.md`
   + `tasks/00.01.eth-driver/findings/live_poke_peek_tool.md`.

10. **Breakthrough: CPU→LAN egress uses the IDM ring, not the UP ring
    (2026-05-28 PM)**: Live stock oracle showed stock egresses with
    `TM[0x10054/58/5c]=0` — the UP DMA TX ring is NOT used. Verified myself in
    the stock decomp: `idm_net_tx` (plat:4206) injects via the **IDM CPU-port
    DMA ring** (npp+0x8004 desc base, 8B descs, kick npp+0x8040=nframes<<16),
    never touches TM[0x10054]; frame flows CPU→QMG sw_fwd→FDB DA-lookup→SOPC
    send2smac2→MAC2. Rewrote `zx_sw_xmit` to submit on the IDM ring (mirrors
    `zx_idm_xmit`). Test: HW **consumes** the IDM descriptors (npp+0x8044 +3 for
    txtest 3) but the frame **dies before the QMG** (sw_fwd/SOPC/SMAC2 TX all
    stay 0, nothing on wire). So submission is right; the remaining gate is the
    **IDM CPU-port → L2-fabric forwarding config** that mainline omits. RE agent
    dispatched. See `findings/idm_ring_xmit_test_result_2026-05-28.md`,
    `idm_cpuport_fabric_forward_re.md`, `stock_live_egress_oracle_re.md`,
    `stock_cpu_lan_inject_path_re.md`.

11. **ALL THREE DMA rings RULED OUT — stock egresses via software-forward
    (2026-05-28 PM, late)**: THREE decisive live stock oracles (host flood-ping,
    before/after, each ~100-186 frames egressed: QMG sw_fwd 0x9234c044 and MAC2
    TX-OK 0x92280718 climb in lock-step) while EVERY DMA-ring counter stays 0:
    - UP ring: kick TM[0x10054]=0, consume TM[0x10058]=0
    - IDM ring: kick npp+0x8040=0, consume npp+0x8044=0
    - DN ring: kick TM[0x10064]=0, consume TM[0x10068]=0
    So **stock uses NO DMA ring** for CPU→LAN egress. This refutes #10's idm_net_tx
    hypothesis, the old UP-ring path, AND the DN-ring hypothesis (all three were
    decomp inferences that the live counters killed). The real path is a
    **software-forward**: CPU hands the frame straight into the QMG sw_fwd queue
    (BMU alloc + a direct enqueue doorbell), no ring. Explains why UP reached
    QMG-but-not-SOPC and IDM didn't reach QMG. **LESSON: decomp inference about the
    egress path has been wrong 3×; rely on EMPIRICAL stock tracing.** Current
    mainline build still has the (wrong) IDM-ring zx_sw_xmit; do NOT trust it.
    Next: empirical stock debug-trace (g_tm_debug_level/g_switch_debug_level=4 +
    logger capture during ping) to name the real sw_fwd enqueue fn + its doorbell
    reg. See `findings/stock_{idm,dn}_ring_usage_oracle_re.md`,
    `idm_fabric_forward_VERIFICATION_2026-05-28.md`, `stock_swfwd_egress_path_re.md`.
    NOTE: working uart path is `~/Projects/MYSELF/ZTE/lib/uart.py` (STATE's
    "Last-known-good" table still says `zxic/lib/uart.py` — stale).

12. **Egress netdev = "sw" → DN ring; "no ring" rule-out is SUSPECT (2026-05-28 late
    PM)**: A reliable stock oracle identified the CPU→LAN egress netdev empirically:
    **"sw"** (path br0/192.168.1.1 → sw → eth3/MAC2; only sw/eth3/br0 tx_packets tick).
    "sw".ndo = `pon_tm_net_tx`, registered dir=1. I read the decomp myself: dir-1 →
    `pon_tm_data_raw_send(...,1)` = BMU alloc (`pon_tm_bmu_alloc_bp`) + memcpy frame to
    BP buffer + DN desc (desc[0]=0x80, desc[3]=3, desc+2=(src_port+0x28)&0x3f<<4, BP idx
    in desc+7/8, len desc+0xc) + `soft_insert_tx_1desc(desc,1)` → **kick TM[0x10064] (DN
    ring)**. This REVERSES Journey #11's "no ring" conclusion: the DN-consume (0x10068)
    "=0" reading used a buggy /proc/kmsg method (first-read-dropped → false 0), and the
    "BMU flat" regs are request/index regs (not counters) → uninformative. So the
    decomp's DN-ring+BMU path is likely correct and the earlier rule-outs were
    measurement artifacts. **UPDATE: re-measured 0x10068 with the CORRECTED method
    (warmup + double-read) — DN ring is GENUINELY UNUSED (consume/cursor/kick all stable
    real 0 across -c100/200/300 while QMG sw_fwd + MAC2 TX climbed; double-read proved
    the reads were live & reliable).** So the DN-ring idea is DEAD too, and the
    decomp↔hardware contradiction is REAL: decomp says `sw→pon_tm_net_tx dir-1→kick
    TM[0x10064]` but HW never kicks it. Stock injects ring-lessly into the QMG sw_fwd
    queue. Do NOT replicate any ring kick. See `stock_dn_ring_REMEASURE_re.md`,
    `sw_netdev_dn_ring_inject_re.md`, `stock_egress_netdev_id_re.md`. **Next: the ONE
    egress netdev whose xmit is untraced = `eth3`/swport (copper port, br0 member);
    `sw`/pon_tm_net_tx is contradicted by the ring measurement, so the ring-less inject
    likely lives in the swport path (swport_dev_xmit_fin / pdt_ethdrv_send).** Mainline
    build currently = UP-ring revert (reaches QMG sw_fwd, dies at SOPC).

13. **Egress LOCALIZED to the SMCT CPU-port channel; submit doorbell invisible —
    tooling wall (2026-05-28 late PM)**: After #12, ruled out the rest by live
    measurement + decomp: SOPC/isolate config is already correct (poke-test of the 2 PP
    drifts did nothing — `sopc_gate_ruled_out`); ALL SW-TX paths in the decomp
    (pon_tm_net_tx, pdt_ethdrv_send, swport_dev_xmit_fin) funnel to a ring kick yet HW
    egresses ring-lessly = universal contradiction (`egress_contradiction_universal`);
    FFE/L3-hardfast is a NAT fast-path, doesn't apply to the locally-generated ping
    reply, and ffe_* bodies are stubs (`ffe_ringless_egress_re`). A reliable stock sweep
    of the never-probed SMCT-control window found the egress flows through the **SMCT
    CPU-port channel**: gauges **0x921d0040** (free-level/head) + **0x921d004c** tick live
    in lock-step with QMG sw_fwd + MAC2 TX; SMCT +0x18=1 (enable), +0x08=0x80 (depth)
    (`stock_sipc_smct_sweep_re`). Mainline already applies the SMCT/SIPC init (zx-eth:
    1279-1281: SIPC 0xc000=0x11, SMCT 0x10000=0xB/0x10010=0x3810). The CPU **frame-submit
    doorbell** into that channel is still unidentified: invisible to read-only sweeps
    (write-only or DRAM/indirect-RAM queue) and the decomp's obvious path kicks the ring
    (which is flat live). `dma_tx_free`(0x4c)/`dma_ram_get`(0x10014/18/1c) have no decomp
    callers → 0x40/0x4c are likely HW-maintained gauges. **WALL: cheap read-only + static
    decomp are exhausted; pinning the submit likely needs instruction-level write tracing
    on stock (kprobe module / JTAG), or pursue Option B (ETH_TM2 mux, clock-gated).** See
    `smct_channel_egress_localized_re.md`, `stock_sipc_smct_sweep_re.md`,
    `egress_contradiction_universal_2026-05-28.md`, `sopc_gate_ruled_out_2026-05-28.md`,
    `ffe_ringless_egress_re.md`, `stock_egress_netdev_id_re.md`. Open RE agent: SMCT
    channel submit / 3rd-channel (`smct_channel_submit_re.md`, pending). Mainline build =
    UP-ring revert (reaches QMG sw_fwd, dies at SOPC).

14. **Submit code is in vmlinux, not our .ko dump → pivot to runtime instrumentation
    (2026-05-28 night)**: RE of the SMCT submit confirmed there's no 3rd ring; 0x40/0x4c
    are HW-maintained gauges (0x10040 written NOWHERE in any decomp); the real submit is
    reached via **`ffe_learn_skb`**, whose body is **NOT in any .ko we decompiled** — `nm`
    shows it `U` (imported) in switch/plat/idmfdb/usbnet, defined in NONE → it lives in the
    **stock kernel (vmlinux)**, which we never decompiled. So static .ko RE has hit a hard
    limit. TWO ways past it: (a) **runtime instrumentation** — `ko_printk_splice.py`
    (tasks/00.01.eth-driver/scripts, splices printk into stock .ko entries → UART via
    kmsg2uart) and **`kotrace.ko`** (tasks/99.01.linux-stockport/kotrace/, hooks specific
    fns incl. kernel via kallsyms; prior run = tftp/kotrace_phase5b.txt) — instrument the
    egress candidates (pon_tm_net_tx 0x19c80, pon_tm_data_raw_send 0x19964,
    soft_insert_tx_1desc 0x191ac, dma_tx_free 0x19138 in plat; swport_dev_xmit_fin 0x107cc,
    pdt_ethdrv_send 0x11130 in switch) to see WHICH fire during a ping reply; (b)
    **decompile the stock vmlinux** — we HAVE it: `ext/extracted/vmlinux.bin` (+ uImage/
    zImage + `ext/h3600_nand_full.bin`) — to recover ffe_learn_skb's body. Plan: let the
    instrumentation localize the divergence first, then targeted-decompile that vmlinux fn.
    See `smct_channel_submit_re.md`, `smct_channel_egress_localized_re.md`. Instrumentation
    agent dispatched (`stock_egress_fn_trace_re.md`, pending).

15. **ADDRESS-MAP ERROR found — the whole "ring-less" saga was reading the wrong base
    (2026-05-28 night)**: kotrace instrumentation of stock proved `soft_insert_tx_1desc`
    DOES run on every egress frame (path: pdt_ethdrv_send→pon_tm_net_tx→pon_tm_data_raw_send
    dir=1→soft_insert_tx_1desc). It writes `*(tm_base+0x10064)=1` = DN ring kick. The
    catch: **tm_base=0x92340000** (PROVEN: QMG sw_fwd counter 0x9234c044 = tm_base+0xc044
    ticks correctly), so the TM ring is at **0x92350000** (UP 0x92350054/58, DN 0x92350064/
    68) — NOT 0x921d0000 (npp+0x10000) that EVERY prior oracle read (inherited from the arch
    doc's wrong "TM DMA = 0x921d0000"). So "all rings flat / ring-less egress" was measuring
    the WRONG block (0x921d0000 = SMCT/SIPC); the real TM DN ring was never measured. Stock
    DOES use the DN ring. Mainline already targets the right tm_base (TM_OFF=0x180000) but
    the old zx_sw_xmit kicked the UP ring (0x10054, dir0, desc[0]=0xc9) → QMG-but-not-SOPC;
    **stock uses the DN ring (0x10064, dir1, desc[0]=0x80)**. FIX = replicate
    pon_tm_data_raw_send dir-1 (DN desc + kick tm_write(0x10064)). Confirming via stock
    re-measure at the CORRECT address (0x92350068) then implementing. See
    `ADDRESS_MAP_ERROR_tm_ring_2026-05-28.md`, `stock_egress_fn_trace_re.md`. NOTE: this
    likely invalidates the "no ring" parts of #11/#12/#13 (wrong-base reads); IDM-ring
    rule-out stands (0x921c8044 was in the correct npp window).

16. **Found the old WORKING-TX commit (user's lead) — egress was via FLOODING, not the
    ring (2026-05-28 night)**: git archaeology found **commit `2ad931ed8`** (pre-refactor
    #38, 05-24) had ON-WIRE-verified CPU→LAN TX (host tcpdump saw device ICMP/ARP replies;
    ~60% loss + DUPs = switch FLOODING). Its mechanism: ONE shared ring (UP_BASE=DN_BASE=
    txdesc_dma) + DUAL-KICK (0x10054+0x10064) + desc[0]=0xc9 + port=0; extras: bulk fpga
    replay DISABLED + FDB self-MAC seed. I replicated the ring/kick into current zx-eth-main.c
    (shared ring CONFIRMED at runtime: UP_base==DN_base==0x4ffdf000; dual-kick runs). RESULT:
    frame reaches QMG sw_fwd (+12) but STILL dies at QMG→SOPC (send2smac2=0, MAC2 TX=0,
    nothing on wire) — SAME gate as the old UP ring. **So the ring/kick was NOT the gate;
    the working commit's egress came from its DIFFERENT init — most likely the FLOOD/
    forwarding config (it flooded), which refactor #38 restricted (flood=CPU-only PP[0x8340],
    isolation remap, FDB aging, broadcast gates off) + the bulk stock replay it added.**
    Edits made (kept — more correct than DN-only): zx_sw_xmit dual-kick + desc[0]=0xc9/port=0;
    the LAST TM-base writer (zx_eth_init_tm_subsystem ~line 4457) now sets DN=txdesc_dma
    (shared). Next: diff 2ad931ed8 flood/forwarding vs current (working_commit_flood_diff_re.md,
    pending) → poke-test the flood reg that makes the CPU frame reach SOPC. See
    `old_working_tx_commit_re.md`. Mainline build = shared-ring dual-kick.

17. **MACRO red-team reframe — we were tuning the wrong layer (2026-05-28 night)**: A
    fresh-eyes agent + a decisive live experiment broke the circle. KEY: the "ping bidi
    WORKS" baseline (commit 2ad931ed8) was an ILLUSION — its replies arrived in a single
    ~1ms burst (a buffer flush), not real round-trips. There was never clean TX. Decisive
    experiment on mainline: host tcpdump for ANY device-originated frame = **0 packets**
    (not even broadcast/flood egresses). MAC readout: **host is on MAC2** (only MAC2 has
    ctrl=0xba6003 + RX-ok=11; MAC0/1/3/4 ctrl=0); **MAC2 TX-ok=0** (never transmits). The
    device's own ARP reply (src=device→dst=host) shows up as **TM RX ingress=2 "delivered"**
    = it LOOPS BACK to the CPU instead of reaching MAC2's wire. → Since even BROADCAST
    (FDB-independent flood) never egresses, the gate is NOT FDB/ring/desc/flood/SOPC-detail
    (15 iters wasted there). It is the **source-CPU-port → physical-egress forwarding**: the
    fabric routes CPU-sourced frames back to the CPU (ingress=2), never to a physical MAC
    TX. RX (PHY→MAC→CPU) works; the inverse never activates. Host is on the RIGHT port
    (MAC2) — "wrong port" ruled out. Next: RE how stock routes a CPU-sourced frame to a
    PHYSICAL port (SPA/DPA CPU-port, the source→egress matrix) vs mainline looping to CPU.
    See `MACRO_review_tx_egress.md`. (My ring/dual-kick/flood edits this session are in
    zx-eth-main.c but did NOT egress — they tuned the wrong layer.)

18. **Runtime config-poking EXHAUSTED — found the layer (PM/SPA) but poke can't open it
    (2026-05-28 night)**: RE'd + verified (decomp + stock dump) that mainline entirely omits
    the chip's **Port-Mapper (G.988 PM) + SPA source-port classifier** init
    (`tm_pon_npp_pm_initial` tm:43376, `tm_pon_npp_spa_initial` tm:43271) — a source→
    allowed-egress authorizer separate from the SBRG/flood layer. Stock values (confirmed in
    `findings/regs/stock_eth_2mib.txt`): 0x921e0054=0xc0 (inport_equal_outport_staen+cpu_not_drop),
    0x921e01a0=0x08 (out-port rule), 0x921d407c=1 (SPA match_mode), in-port rules 0x921e0180+i*4=i.
    Poked the FULL direct recipe live → STILL no egress (QMG sw_fwd +N, SOPC send2smac2=0,
    MAC2 TX=0, 0 on wire). **Every runtime config poke this session (flood/PM/SPA/SOPC/isolate)
    fails identically** → the QMG→SOPC gate is NOT runtime-pokeable config. Likely: (a) the
    forwarding consults tables/RAM built at INIT (runtime ctrl-poke doesn't rebuild them), or
    (b) the indirect **SPA match-RAM** (source-port classifier; payload in tm.ko `_LANCHOR1`
    blob, never read), or (c) fundamental. NOTE: device-MAC table 0x921d4120/24 is DIRECT and
    mainline ALREADY writes it (not a gap). Recommended next: read stock's live SPA match-RAM +
    implement the FULL PM/SPA init at boot-time in the driver (the layer mainline omits) +
    rebuild + test; if that fails, it's deeper than config (HW-trace, not poke). See
    `cpu_source_port_egress_re.md`, `pm_spa_init_recipe_re.md`, `MACRO_review_tx_egress.md`.

19. **PM/SPA init at BOOT also fails → init-time refuted, config exhausted (2026-05-28
    night)**: Implemented `zx_pm_spa_init()` (the full direct PM/SPA recipe) in the driver,
    called LAST in probe (after replay+tm_subsystem so it isn't clobbered). Confirmed at
    boot: 0x921e0054=0xc0, 0x921e01a0=0x8, 0x921d407c=1, in-port rules set. STILL no egress
    (QMG sw_fwd +12, SOPC=0, MAC2 TX=0, 0 on wire). So setting the direct config at INIT vs
    runtime makes NO difference — the init-time hypothesis is refuted. **ALL direct config
    (runtime + init, every verified gap) is now exhausted; the QMG→SOPC→physical-MAC-TX step
    never activates for a CPU-sourced frame.** Two remaining: (1) the **SPA match-RAM**
    (indirect source-port classifier table, ram_id 0 — the ONLY config never populated; if
    the CPU source-port match entry is absent the classifier won't authorize CPU→physical
    forward), (2) **fundamental: the egress half (SOPC→MAC crossbar / ETH_TM2 mux) is
    clock/power-gated** (RX works = its clock on; TX/egress not) — Option B territory, the
    ungate (TOPCRM PLL / power-domain) was never found. Config-failing 100% makes (2) likely;
    testing (1) (read stock's live SPA match-RAM) as the last config lead before pivoting to
    (2). The zx_pm_spa_init() is in the source (kept — it's the stock-faithful PM/SPA init,
    correct even if not sufficient alone).

20. **STP port-state + pon-registered gate BOTH ruled out (2026-05-28 night)**: Two leads
    chased after the macro review, both negative (don't re-try):
    - **STP/per-port forwarding state**: reg phys 0x921c0044 (gregRegTable, 3 bits/port,
      FORWARDING=4). Stock dump = 0x00000000 (STP off, 0x40 stp_en=0, 0x4c ports-open);
      mainline doesn't write it → HW default matches stock. Stock egresses with STP fully
      off, so it's NOT the gate. (port_stp_state_re.md)
    - **lan_up / PON-operational gate** (hypothesis: egress gated behind a "registered with
      OLT" state unsatisfiable without fiber): REFUTED by reading the decomp myself —
      `pon_is_registered()` (plat:7712) is `return 1` UNCONDITIONALLY (the if just sets a
      side-effect flag). It never blocks TX, fiber or not. So the egress is NOT gated on a
      pon-registered/operational state via this path. Note: this device has NO physical
      fiber connector (copper-only, 1 WAN + 4 LAN) — confirmed we need ZERO fiber config
      (GEM/tcont/PON-MAC/SPA-stream-parser/G.988-PM are all fiber-side, irrelevant); but the
      LAN switching still routes through the PP/QMG/SOPC fabric (stock egresses to LAN with
      fiber absent). The only real effect of lan_up==1 is HW: pp[0x2c]|=1<<(lan_up_port+0x19)
      + zx_pon_clk_reset() — already partially tried (bit 25 vs 29; pp[0x2c] high bits not
      writable). STILL-open gate is unchanged: CPU-sourced frame loops to CPU, no egress
      even broadcast, all direct config exhausted. Remaining: SPA match-RAM (weak — it's a
      byte-classifier per decomp, not a source→egress map) or egress clock/power (weak —
      MAC2 ctrl identical to stock which DOES egress).

21. **FABRIC EGRESS GATE CRACKED — frames now reach MAC2 TX; final gap = MAC→PHY MII
    (2026-05-29)**: Resolved the whole #11–#20 saga. Two fixes, both evidence-driven:
    - **(a) MAC init-order wipe** (real bug): probe runs `zx_smac_init_port` BEFORE
      `pon_reset(0xffffffff)`, which wipes MAC2 (MASK/EN/+0xe0→0); `adjust_link` only
      re-wrote CTRL, never the full smac_init. Live-confirmed MAC2 MASK=0/EN=0. FIX: adjust_link
      now calls `zx_smac_init_port(e,i)` on link-UP (zx-eth-main.c ~L4082). MAC2 boots live.
    - **(b) THE egress-port hint** (the fabric gate): kotrace of LIVE stock egress
      (`kotrace_egress_capture.py`, 136/136 ping-reply frames) showed the path
      `pdt_ethdrv_send→pon_tm_net_tx→get_next_txdesc(1)→pon_tm_data_raw_send(dir=1)→
      soft_insert_tx_1desc(dir=1)`; the DN descriptor encodes the egress port as
      **desc[2:3]=((port+0x28)&0x3f)<<4** (plat:6848). Mainline hardcoded **0** → fabric had
      no destination → SOPC never picked a MAC. Setting it (port=4) → frames now traverse the
      WHOLE fabric: QMG sw_fwd → RED → DSCH → **SOPC send2smac2 +N → MAC2 TX +N** (only smac2 =
      host port, zero drops). On-wire verified config = UP ring + dual-kick (shared ring) +
      egress-port (the DN-ring rewrite was reverted: warm-boot pending pollution tm[0x10068]
      high16=0x13 + it didn't reach QMG; UP/dual-kick is the working-to-MAC path). Falsified
      this session: DN tcont shaper credit (mainline was wide-open, not 0); SOPC bridge enable
      0x19068; egress-block clock-gating (0x19004 latches fine).
    - **RESOLVED the address-map saga (#11–#15)**: measured the CORRECT tm DN ring
      (0x9235xxxx, not 0x921d00xx=SMCT): stock DN consume=0x00000001 (high16=0), QMG sw_fwd is
      the egress signal, NOT a ticking ring counter. The "ring-less" conclusion was the wrong-base read.
    - **FINAL GAP — MAC→PHY MII TX**: MAC2 counts TX (TX_frames +40, TX_bytes +2720) but host
      NIC sees NOTHING and NO errors (rx_errors/rx_crc_errors unchanged) → not bad-CRC/BP-flush;
      the GePHY isn't driving copper on TX (RX works, link up). MAC2 MII regs partial:
      +0xc20=0 (exp 0x32), +0xc50=0 (exp 0xa8), +0xb00=0xff01 (exp 0x10ff11) — though some are
      write-once (read ambiguous). NEXT: RE why the +0xc00-block MII writes don't land + the
      GePHY TX config; confirm vs stock. See
      `findings/session_2026-05-29_egress_fabric_cracked.md`, `kotrace_egress_capture.py`,
      `tx_egress_oracle.py`, `sch_shaper_dump.py`.

22. **Egress: fabric gate stays cracked, but the REAL remaining blocker is the SOPC↔MAC
    READY handshake not asserting from cold (2026-05-29, late)**: After #21, deeper testing +
    two review agents corrected the picture:
    - **CORRECTION**: the "bit19" claim in #21 was WRONG. Stock `MAC2 ctrl=0xBA6003` HAS bit19
      SET; the driver already converges there (config_speed_duplex clears bit15, sets bit13 for
      gigabit). DO NOT touch bit19. The egress-port hint (desc[2:3]=((port+0x28)&0x3f)<<4, was 0)
      and the MAC init-order-wipe fix are the real, kept fixes — they get frames QMG→DSCH→SOPC.
    - **DTR reset = COLD power-cycle** (user confirmed — unplugs/replugs PSU), so every RAM-boot is
      clean HW; the "warm-boot pollution" theory was WRONG. Each test is a fair cold boot.
    - **The blocker**: the SOPC↔MAC bridge `0x19068` **READY bit (port+5)** (MAC2=bit7=0x80) **does
      NOT assert on a cold boot** → SOPC can't engage MAC2 → send2smac2 stays 0 → 0 on wire. RX
      works (RX-side serializer bonds; TX/egress READY won't). All register pokes (bridge enable
      bits[4:0], bit15, ctrl, egress-port) are MOOT without READY. The "ping 5/5" of #21 happened on
      one boot where READY was transiently up (fragile U-Boot MII-serializer state + live RX learning).
    - **Implemented (kept, in source)**: stock-faithful adjust_link chain (smac_init →
      config_speed_duplex → ready-gated 0x19068 → enable), and a periodic **MAC keepalive**
      (zx_mac_keepalive_fn, mirrors stock extphy_timer_func — re-asserts the light bring-up every
      100ms to catch/hold READY). Keepalive can't help yet because READY never asserts to catch.
    - **Root suspect**: incomplete MAC↔PHY serializer/MII bring-up — the +0xc20/+0xc50/+0xb00/+0xe0
      MII regs are write-once and land non-deterministically; DTS has no phy-mode (relies on U-Boot,
      which pon_reset wipes). Only writer of 0x19068 = smac_sopc_mode_switch (plat:2298); it's cleared
      by the per-port pon_reset(1<<(port+6)) and never re-asserted with READY up on mainline.
    - **NEXT**: targeted RE of what makes 0x19068 READY(port+5) assert on stock (kotrace the MAC↔PHY
      bring-up watching 0x19068 + MII regs + GePHY MDIO + TOPCRM egress clock). See
      `findings/session_2026-05-29_egress_fabric_cracked.md` (update pending).

23. **port1/jack2 ingress→CPU SOLVED — SPA port_vlan_filter gate (2026-06-03)**: The
    long-standing "only port1 fails ingress→CPU; port0/2/3 work" anomaly is fixed.
    Root cause: mainline never fully inited the SPA, leaving **port_vlan_filter
    (0x921d42ac + port*4, field [5:0])** at its non-zero reset default (p0=0x36 p1=0x26
    p2=0x36 p3=0x27 p4=0x36). That per-port VLAN filter **gated port1's trap-to-CPU
    verdict** — frames passed MAC→SPA→SDET but were dropped at the OPC, never hw-trapped.
    Stock clears the WHOLE x10 table to 0. **Fix** (`zx_pm_spa_init`, last in init):
    `for (i=0;i<10;i++) npp_write(e, 0x142ac + i*4, 0);`. The clear is cross-port (the
    whole table must be 0, matching stock). **Live-confirmed + stable**: port1
    rx_per_ingress climbed 0→18→37→55→94 under sustained jack2 traffic, BPDUMP showed
    port1 frames reaching the CPU, no poke. **Also fixed a latent crash** the opened
    ingress exposed: `zx_tm_napi_poll` deref'd `bp_buf` for descriptors with
    out-of-range `bppe_idx` (stale descs, bppe up to ~4975 vs pool 1024) → ~11MB past
    the bp pool → kernel panic. Guarded with `bppe_idx < TM_BPPE_POOL_SIZE`. Debug
    observability kept in tree (poke PEEK + pipeline_stats full ingress chain).
    **Committed + merged to main** (`c37e6168f`, fast-forward; egress fix untouched —
    diff is purely additive + never touches the TX path). The user's per-port-gate
    hypothesis was correct. See `tasks/00.01.eth-driver/findings/port1_drops_at_PP_re.md`
    (full RE trail), DATASHEET errata, stock CLA golden captures. **Device was rebooted
    after the test → currently on stock NAND** (RAM-boot mainline to re-verify).

24. **HW-forwarding / stable-LAN-streaming arc + the unicast→CPU WEDGE (2026-06-04, branch
    hw-bridge-offload, NOT merged to main)**: Goal = sustained LAN↔LAN streaming via HW forwarding.

    **THE PACKET FLOW (how it works + where it breaks):**
    A frame ingresses a LAN port → MAC-RX → SPA(admit) → SDET → **CLA (classifier)** → QMG (queues)
    → then ONE of two paths:
      • **FORWARD (HW L2 switch):** if the dst MAC is KNOWN in the switch SBRAG FDB → DSCH → SOPC →
        MAC-TX out the egress LAN port, entirely in hardware. Counter: QMG `hw_fwd` (counts as "DN"
        = toward LAN). CPU not involved.
      • **TRAP (to CPU):** if dst unknown / control proto → SIPC/SMCT → **TM RX descriptor ring →
        IRQ → NAPI → Linux bridge** (software-forwards). Counter: QMG `hw_trap` ("UP" = toward CPU).
    (UP/DN = PON heritage: UP=toward CPU/WAN, DN=toward LAN.)

    **What we PROVED on real HW:** (a) STOCK does ~350 Mbit/s LAN↔LAN TCP via PLAIN HW L2 switching
    gated by CLA *protocol* classification (TCP/UDP forward, ICMP/control trap) — NOT any
    FFE/CLA-hash/SBRAG-ipv4 offload table (all empty live during the flow). The old "this chip can't
    HW-forward L2" dead-end was an ICMP-only artifact (ICMP traps even on stock). (b) MAINLINE already
    HW-forwards the bulk (DN) direction (QMG DN hw_fwd→~4400 during a TCP flow). (c) End-to-end the
    iperf moved ~6 MB before collapsing (so both directions carried real packets initially — data
    lan3→lan1 + ACKs lan1→lan3, since TCP can't advance without returning ACKs).

    **THE WEDGE (open blocker):** under a TCP flow the reverse (ACK) direction TRAPS to the CPU, and
    the **CPU-RX trap path HALTS at ~1024 frames** (tm_rx_count + tm_irq_count FREEZE) → no ACKs reach
    the server's TCP → TCP collapses to ~1.9 Mbit/s. The bulk DN forward stops as a *consequence* (no
    ACKs → TCP stops sending). Stock avoids this by HW-forwarding BOTH directions (CPU path idle).

    **The ~1024 halt is ROBUST** — survived 8 fixes/configs: BP pool 1024→8192 (Iter S, kept), RED
    global share-pool poke, RX slot-release (Iter U, reverted), BMU-free (verified OK, ruled out),
    NAPI-rearm (Iter V/W, reverted), **RED-block-init** (Iter Y: mainline NEVER inited the real RED
    block 0x92344000 — zx_tm_red_init writes TM[0x4014]=a different block; kept, lowered RED drops
    5010→61 but didn't fix the wedge), **QMG up_ram_thd 80→4000** (Iter AA: QMG 0x9234c000 [12:0]=up
    [25:13]=dn, link-UP starves the UP/CPU queue at 80 vs dn 8096; kept), **assisted FDB learning**
    (Iter AB: ds->assisted_learning_on_cpu_port=true so bridge-learned MACs offload to the real SBRAG
    FDB via the existing .port_fdb_add; kept). Iter Z = the DEFINITIVE 2-NIC iperf3 TCP test with all
    3 code fixes active in dmesg → STILL collapsed 1.9 Mbit/s, tm_rx latched 1063, tm_irq frozen.
    assisted-FDB didn't make the reverse forward — the device bridge FDB stays empty (nothing to
    offload). ⚠️ Reproducing the test is gated by a flaky HOST USB hub (jack4 enx6c70cbb68169 keeps
    dropping off the bus).

    **TWO OPEN TARGETS for next session (device testable when jack4 stays up):** (1) THE WALL — the
    TM RX desc-ring / RX-IRQ engine halting at ~1024: instrument ring head/tail + IRQ_STATUS(0x100)/
    mask LIVE at the stall, diff stock pon_tm_net_poll byte-for-byte (pending>0→IRQ/mask bug;
    ==0→HW producer/credit stop). (2) Make the reverse dir HW-forward (sidesteps the CPU like stock):
    fix why the device bridge FDB doesn't populate so assisted-learning can offload both MACs.
    Full trail: `tasks/00.01.eth-driver/findings/hw_forwarding_offload.md` (Iters K–Z + MORNING
    SUMMARY). Fixes are stock-matching corrections, kept on the branch; main + egress fix untouched.

25. **★ MAJOR CORRECTION via UDP (2026-06-04, user's lead "esto con udp?") — HW FORWARDING ALREADY
    WORKS BOTH DIRECTIONS; the "wedge" is TCP/ICMP-trap-SPECIFIC, not a forwarding problem.** My
    Journey #24 "reverse direction doesn't forward / wedge" framing was generalized from TCP+ICMP
    tests — both of which TRAP to the CPU. Re-tested with UDP (which IS HW-forwarded, per the
    protocol-discrimination finding), per direction, clean:
      - UDP lan3→lan1: 300 Mbit/s, 0% loss (0/129467).
      - UDP lan1→lan3 (the "reverse"): 300 Mbit/s, 0.0008% loss (1/129467).
      - UDP BIDIRECTIONAL simultaneous: QMG hw_fwd=450761, hw_trap=143, RED drops=0, tm_rx_count=143
        → NO WEDGE. (Proof it's real HW: CPU received only 143 frames while 450761 were forwarded —
        impossible to software-bridge that.)
    ⇒ The driver's HW L2 forwarding is SOLID in both directions, simultaneously, at ~300 Mbit/s/dir.
    The unicast→CPU WEDGE only manifests for traffic that TRAPS to the CPU: TCP (its
    handshake/control/likely flow-learn) and ICMP floods. The ~1024 CPU-RX-halt (Journey #24) is real
    but is only EXERCISED by trapped traffic; pure forwarded data (UDP, TCP bulk) bypasses it.
    ⇒ REMAINING QUESTION (narrowed): why does TCP trap ~1063 frames when UDP traps ~143? Identify the
    trapping TCP frames (tcpdump/driver RX log during a TCP iperf) and either stop them trapping or
    fix the ~1024 CPU-RX-halt so the trap path survives. **UDP streaming works on mainline TODAY.**

26. **★ ROOT CAUSE of the TCP wedge = FFE conntrack flow-cache (2026-06-04, RE via 3 background
    agents on the GPL stock binaries; modem is GPL, ZTE unresponsive).** WHY TCP traps but UDP
    forwards, settled from the REAL vmlinux bodies (the switch.ko 0x2c1xx "halt_baddata" stubs are
    just PLT import thunks; the bodies are exported from vmlinux):
      - `ffe_receive_skb` (vmlinux c0473110) gates RX: returns 0 ⇒ engine HW-forwards, !=0 ⇒ trap-to-CPU.
      - `ffe_ip_conntrack_check` (vmlinux c0452a7c): **UDP (proto 0x11) binds + forwards immediately;
        TCP (0x06) is REJECTED→trap UNLESS conntrack state==3 (ESTABLISHED)**:
        `if ((proto=='\x06') && (state!='\x03')) goto trap;`.
      - So STOCK relies on the CPU's FFE (a netfilter-conntrack software flow-cache) to process the
        first trapped TCP packets, reach ESTABLISHED, then install a HW hardfast session
        (zte_api_fast_l3_session_add → cla_set_hash_table) → subsequent packets HW-forward. MAINLINE
        has NO FFE → TCP's reverse-dir ACKs trap to the CPU FOREVER → the CPU-RX trap ring latches at
        ~1024 → wedge. UDP never touches the trap path (plain HW L2-forward via FDB).
      - The per-protocol SPA pktdeal knob (`tm_port_protocol_pktdeal_set` → HW 0x921d4300 reg67[1:0],
        0=fwd/1=trap/2=drop/3=copy) is set to forward by mainline for all slots → REFUTED as the cause.
    ⇒ STRATEGY (do NOT port the FFE — large + unnecessary for L2 bridging): the forwarding already
    works (UDP proves it). The wedge is a **trap-ring DRAIN bug** — the CPU-RX ring stops re-arming
    after exactly one TM_RX_DESC_PER_Q(1024) wrap. FIX = pin the ring-wrap/IRQ-rearm off-by-one in
    `zx_tm_net_poll` against stock `pon_tm_net_poll` (plat decomp @0x1c9f0) and correct it; then the
    trapped TCP ACKs drain via the CPU and TCP stops collapsing (CPU-assisted but stable). Prior fix
    attempts at this ring (Iter T full-slot-release, Iter V napi-rearm) failed → a 3rd agent is doing
    the precise stock-vs-mainline poll diff. Findings: `ffe_tcp_trap_re.md`, `decomp_halt_baddata_band.c`,
    `rx_ring_wrap_re.md` (pending), + `hw_forwarding_offload.md` Iters AC.

27. **★★★ unicast→CPU WEDGE SOLVED → stable LAN streaming achieved (2026-06-04). One-bit fix.**
    The long-standing wedge (CPU-RX trap path halts at ~1024 frames) is FIXED. ROOT CAUSE: the per-q
    RX count `tm[0x10100+q*4]` is a PACKED PAIR — LOW16=ring0 pending, HIGH16=ring1 (this is the
    long-unexplained `high16=??` in pipeline_stats — user spotted the connection). The release reg
    `tm[0x4068]` bit14 = ring SELECTOR. The poll reads pending from LOW16/ring0 but
    `zx_tm_release_rx_desc_raw` HARDCODED bit14=1 (ring1) → it drained ring0 but ACKed ring1 → ring0's
    consumer index never advanced → after HW fills one ~1024 ring it stops producing + stops the RX
    IRQ → tm_rx_count/tm_irq freeze at ~1024. FIX (commit ce365bd): bit14=0 so the release acks the
    ring0 the poll drains (matches stock soft_release_rx_desc @ plat 0x1a8e8). VERIFIED ON HW: ICMP
    flood 4000 → tm_rx_count=3925 (was ~1024), 5% loss (was 82-100%); **iperf3 TCP SUSTAINED 354
    Mbit/s for 20s/844MB** (was collapsing to 1.8) = STOCK-LEVEL; ping-after clean. UDP still 300
    Mbit/s both dirs. Data HW-forwards (QMG hw_fwd), TCP ACKs CPU-drain (now that the ring works,
    ~12k/s, no wedge, RED=0). The 3 acceptance criteria MET: ping ✅, bridge comm ✅, sustained TCP ✅.
    Found via 3 background RE agents (halt_baddata band = PLT thunks; FFE = conntrack flow-cache,
    TCP-traps-until-ESTABLISHED — explains stock, ruled out porting FFE; the precise ring-wrap diff vs
    stock pon_tm_net_poll). NOTE: the ACK path is CPU-assisted (not pure-HW-both-dirs like stock's FFE
    hardfast), but achieves stock throughput because ACKs are sparse/small; a future FFE-style HW
    session-install would offload the CPU entirely (optional). Branch hw-bridge-offload (also has the
    earlier stock-matching attempts: pool 1024→8192, RED-block-init, QMG up_thd, assisted-FDB — should
    be audited/trimmed before merge; bit14 is THE fix). main + egress fix untouched, NOT yet merged.
    Findings: rx_ring_wrap_re.md, ffe_tcp_trap_re.md, hw_forwarding_offload.md (Iters K–AD).

28. **Branch pruned + verified + merged to main (2026-06-04).** Post-fix audit of hw-bridge-offload:
    KEPT the legitimate fixes — **bit14 ring-selector (THE fix)**, pool 1024→8192 (load-bearing:
    napi bppe>pool guard + sustained throughput), RED-block-init (stock-match), QMG up_thd 80→4000
    (UP-queue headroom for the CPU ACK-drain). PRUNED the non-contributing: assisted_learning (Iter AB,
    inert here) + the diagnostic trap-log gate (130→10, debug kept). RE-VERIFIED on HW after the prune:
    ICMP flood→tm_rx=4028 (no wedge), iperf3 TCP **354 Mbit/s 20s/844MB 0-retransmits**, ping-after
    clean. Merged to main (commit-before-prune restore point was 8b41d68; egress fix untouched — the
    diff is RX-ring/CLA/RED, never the TX path; CPU→LAN egress is exercised by the bridge software-
    forwarding the trapped ACKs out lan3, which TCP-sustaining confirms).

    **★ NEXT STEP (documented): make the TCP ACKs HW-forward instead of CPU.** Today the data dir
    HW-forwards but the reverse (ACK) dir traps to the CPU and is software-bridged (works, ~stock
    throughput because ACKs are sparse, but CPU-assisted — not pure-HW like stock-post-ESTABLISHED).
    To offload the CPU entirely (and scale to multi-flow / higher rates), install a HW forwarding
    session for the reverse 5-tuple so the ACKs HW-forward too — i.e. a minimal FFE-style hardfast
    session-install on flow-learn: hook the trapped-flow path → build + write the CLA hash / SBRAG
    entry (chain mapped in hw_forwarding_offload.md Iter L: zte_api_fast_l3_session_add tm.ko 0x6558c
    → tm_add_acl_flow_rule → cla_set_hash_table tm.ko 0x15a14), keyed on conntrack-ESTABLISHED like
    stock's ffe_ip_conntrack_check (vmlinux c0452a7c). Optional/perf — the L2 streaming goal is met.

29. **Per-protocol pktdeal RE landed + FORWARD-ALL experiment = NEGATIVE, baseline reconfirmed
    (2026-06-04, branch hw-ack-forward, NOT merged).** Pursuing "ACKs via HW": RE completed the
    trap-vs-forward mechanism — a 2-bit pktdeal field per (port, protocol-slot) at SPA HW
    **0x921d4300[1:0]** (`tm_port_protocol_pktdeal_set` tm.ko 0x37340; 0=fwd/1=trap/2=drop/3=copy),
    table-driven by stock's def_ptl_pkt_action (mostly trap). Tested a `zx_proto_fwd_all` module param
    that forces ALL slots to deal=0. RESULT NEGATIVE: 100% loss — frames reach the MACs (smac RX
    climbs) but with no broadcast trap the ARP/ND never reach the CPU (tm_rx=0), the bridge never
    learns/replies. CONTROL (default reverted to 0 = stock table, same topology): ping 5/5 0% loss,
    tm_rx=16 (ARP traps, SW bridge forwards) → cabling OK + forward-all was the sole regression +
    merged-main baseline intact. LESSON: cannot blanket-forward; broadcast/control MUST keep trapping.
    REFINED PLAN (two parts, both required): (1) flip ONLY the TCP-pure-ACK ptype slot trap→forward
    (Iter AC: TCP data already HW-fwds, only len-66 ACKs trap → different slot; identify via upstream
    flags→enum RE / RX-desc classification log / 0x921d4300 dump+correlate), AND (2) HW FDB offload —
    "not trapping" is insufficient; the switch needs the dest MAC in SBRAG/CLA FDB to L2-forward the
    unicast ACK, but the bridge FDB is empty + driver is trap-all conduit (re-converges on the known
    open CLA-offload problem, zte-hw-forwarding-deadend). So "ACKs via HW" is an optimization bigger
    than a one-line flip; the L2 streaming GOAL is already met via the SW bridge (merged main).
    Details in hw_forwarding_offload.md Iter AF; decomp in decomp_halt_baddata_band.c.

30. **★ DECISIVE live experiment — "ACKs via HW" collapses to ONE surgical pktdeal change
    (2026-06-04, branch hw-ack-forward).** Measured per-direction/per-protocol on live HW (jack2/lan1
    nsA ↔ enx2c997/lan2 nsB, both in br0). UDP BOTH directions = 100% HW (hw_fwd climbs, tm_rx flat
    +8); TCP data HW-forwards but the small pure-ACK frames TRAP (tm_rx +60-100k/run). Seeded static
    SBRAG FDB for both MACs (fdbadd debugfs) → NO effect on the ACK trap. UDP lan1→lan2 (same dir the
    ACKs take) HW-forwards fine. ⟹ THREE refutations: (1) chip DOES HW-forward unicast L2 both dirs
    (kills the "CLA traps all" dead-end), (2) NOT a FDB miss/offload gap (static FDB inert + UDP works
    with no FDB help), (3) NOT directional. The TCP-ACK trap is the **per-protocol pktdeal/SPA
    classifier** — the short-ACK ptype slot is deal=1 (trap) while TCP-data + all UDP are deal=0.
    ⟹ FIX collapses to ONE entry: find the TCP-pure-ACK ptype slot in SPA 0x921d4300 and flip
    deal 1→0 (keep broadcast/control trapping — forward-all was too broad, #29). **No FFE port, no HW
    FDB offload needed** (both removed from the critical path). NEXT: identify the slot (RX-desc ptype
    log / live-poke bisect 0x921d4300 / RE flags→enum), set it in zx_pp_pro_actions[], re-test TCP for
    tm_rx flat = DONE. Details: hw_forwarding_offload.md Iter AG.

31. **★★ pktdeal live-bisect: ACKs-via-HW PROVEN + autonomous HW flow-learning discovered
    (2026-06-04, branch hw-ack-forward).** Added a `pktdeal` debugfs hook (flip per-proto slots at
    runtime). VALIDATED on live HW: stock table → TCP 330Mbit/s tm_rx delta=62235 (ACKs trap);
    `all 0` (forward all slots) → TCP 328Mbit/s **tm_rx delta=0 = ACKs HW-forward, CPU 100% offloaded**
    = goal reachable. ★★ BIG UNEXPECTED: after one forward, the flow STICKS — restoring stock AND
    forcing `all 1` (all slots→trap) AND a link bounce all leave it HW-forwarding (tm_rx=0). ⟹ the
    chip installs a **persistent HW flow-forward entry when it forwards a flow**, overriding pktdeal
    (= the FFE-hardfast equivalent, but triggered by forwarding not a CPU install; fresh-boot stock
    traps forever only because it never forwards to seed it). CONSEQUENCE: the runtime minimal-slot
    bisect is invalid (the all-0 seeded the sticky entry → all later per-slot tests read 0 regardless;
    [0..2] result bogus). Minimal-slot ID needs clean state per trial = reboot-per-test (sticky entry
    survives pktdeal writes + link bounce; only chip reset / FDB aging clears it). Also: flaky nsB NIC
    bad-autoneg fixed by ethtool autoneg + link down/up bounce (80ms→2.7ms). NEXT: reboot-per-trial
    bisect to set the one TCP-control slot deal=0 in zx_pp_pro_actions[], OR exploit the flow-learning
    (seed + self-sustain). Details: hw_forwarding_offload.md Iter AI.

32. **CORRECTION (2026-06-04): the "sticky/persistent flow-learning" of #31 was a flaky-NIC
    measurement artifact — RETRACTED.** User confirmed DTR cuts SoC power (real cold cycle), so
    "survives reboot" was impossible. Re-tested with iperf throughput verified per run: the delta=0
    readings that implied "sticky/overrides pktdeal" were the flaky enx2c997 NIC intermittently not
    pushing the ACK stream (no traffic ⇒ tm_rx flat ⇒ misread as "forwarding"). The 62k trap only
    appears when the link genuinely sustains the flow, and even then didn't reproduce run-to-run.
    WHAT STILL STANDS (link-stable, repeated): `all 0`→TCP 328Mbit tm_rx~0 (ACKs HW-forward,
    achievable); stock→TCP can trap ~62k; forward-all breaks broadcast (#29); UDP HW-fwds both dirs.
    The per-slot bisect is NOT doable on this rig (flaky NIC → untrustworthy per-test deltas) — needs
    a STABLE 2nd LAN NIC (good jack4 enx6c70, unplugged). Details: hw_forwarding_offload.md Iter AK.
    NIC-recovery that works: driver-level r8152 unbind/bind on 3-3.1:1.0.

33. **Deep RE (2 agents) + live tests: full HW-ACK-offload converges on the HW-forwarding-offload
    dead-end (2026-06-04, branch hw-ack-forward).** With a stable rig (good jack4 NIC + retry reader),
    confirmed cleanly: stock→TCP traps ~61k, all-0→0 (ACKs HW-fwd), no sticky state, fully reversible.
    Bisect: the ACK trap is NOT a single/double pktdeal slot — only all-0 forwards; every partial
    range traps fully (multi-slot/default-action). RE agent A (pktdeal_override_re.md): CLA-hash does
    NOT override the pktdeal trap (SPA is UPSTREAM of CLA in the pipeline) → no cheap L2 hardfast; only
    SPA pktdeal controls L2 trap; cla_set_hash_table is L3/NAT-only. RE agent B (hw_broadcast_flood_re.md):
    the chip CAN HW-flood broadcast via a SEPARATE block (SBRG VLAN-membership, not pktdeal), recipe =
    PP[0x863c]=0 + membership/isolation + flood regs — BUT live test (full recipe poked) did NOT enable
    flood (ARP still 100% loss). ⟹ broadcast flood-replication path isn't wired in the trap-all conduit
    (same root as zte-hw-forwarding-deadend). So: all-0 forwards TCP but breaks broadcast, and neither a
    pktdeal-slot subset nor the SBRG recipe nor a CLA override cleanly fixes it. Full HW-ACK-offload is
    BLOCKED on the deeper HW-forwarding/flood-replication wiring (or the FFE port). The L2 STREAMING
    GOAL remains MET via the CPU SW bridge (merged main, 354 Mbit/s). Docs: pktdeal_override_re.md,
    hw_broadcast_flood_re.md, alt_trap_levers_re.md, hw_forwarding_offload.md Iters AF–AM.

34. **★ CONCLUSIVE (2026-06-04): this chip has NO autonomous HW broadcast flood — stock ALWAYS traps
    broadcast to the CPU + SW-floods. Our merged solution = stock-equivalent for L2.** Live diagnostic:
    under all-0, broadcast dies as +N at drop_PP (0x921da040). RE (2 converging agents,
    pp_broadcast_drop_re.md): drop_PP is NOT a forwarding gate — it's the OPC-top "PP DROP" terminal
    drop-reason counter (the symptom). A broadcast gets an egress destination ONLY via (1) autonomous
    HW flood-replication — which STOCK NEVER PROGRAMS (tm_pon_pp_brg_initial calls no broadcast-flood
    setter; brdcst_fld_en/vl_trans stay 0; no MGID/flood-domain table exists), or (2) trap-to-CPU
    (pktdeal deal=1) → Linux bridge SW-floods. Stock uses ONLY (2). So all-0 removes the trap and there
    is no HW-flood fallback → PP-DROP. ⟹ a full-HW L2 bridge (broadcast in HW) is NOT achievable on
    this silicon — stock itself routes broadcast/control through the CPU. For L2 same-subnet TCP, stock
    HW-forwards DATA (DA-lookup, like our UDP) and sends CONTROL to the CPU (FFE; CLA-hash empty for L2)
    — IDENTICAL to our merged result (TCP data HW-fwds + ACKs/broadcast trap+CPU-drain, 354 Mbit/s).
    "ACKs-via-HW full" is not a real thing on this chip for L2; we are already at stock parity.
    Bonus bugs found (cleanup, don't unlock full-HW): dueling init writes 0xFF vs 0 to PP[0x8300/0x8304]
    (zx-eth-main.c:1240-1241 vs 2551-2552; 0xFF = CPU broadcast hairpin); PP[0x863c]=0xaaaaaaaa vs
    stock 0; PP[0x8008]=0x0000ff00 vs 0x0000dfdf. Docs: pp_broadcast_drop_re.md, hw_broadcast_flood_re.md,
    pktdeal_override_re.md, alt_trap_levers_re.md. INVESTIGATION CLOSED at stock parity.

35. **★★★ DECISIVE live stock measurement: stock HW-forwards TCP ACKs — we are NOT at parity, goal IS
    achievable, and it's NOT the FFE (2026-06-04).** Booted stock NAND (SSH admin@.1), iperf TCP
    between two hosts on stock LAN ports, read QMG via /bin/fpga: hw_trap 188→241 = **+53** over ~6s of
    a 353 Mbit/s flow (negligible/background) — stock does NOT trap the ACK stream, it HW-forwards it
    (hw_fwd=0 on both → bulk bypasses QMG = ring-less fabric). MAINLINE traps the SAME flow +62000.
    Same throughput (single flow) but stock's CPU is idle. Stock forwards ACKs STATICALLY from t=0 (no
    learning burst) ⟹ NOT the FFE — a static chip-config difference mainline doesn't replicate (also
    overrides this session's matchram/parity inferences — the LIVE chip forwards). ⟹ #34's "stock
    parity" RETRACTED. The lever routes TCP-ACK to the ring-less L2 fabric (forward) instead of the
    SPA-pktdeal-trap path. NEXT: diff stock LIVE config (regs/stock_eth_2mib.txt + fresh fpga reads)
    vs mainline init — pktdeal RAM 0x921d4300 / SADM / transfer / ring-less-path enables — to find it.
    Details: hw_broadcast_flood_re.md Iter AP. (Note: Journey #34's "no HW broadcast flood" still
    stands — that's broadcast; this is unicast-TCP-ACK, a different path.)

36. **★★★ SOLVED — TCP ACKs HW-forward; CPU offloaded; stock parity achieved + IMPLEMENTED
    (2026-06-04, branch hw-ack-forward).** Root cause (RE agent stock_ack_forward_lever_re.md + live
    confirm): `zx_chip_tm_init_pro_action` wrote the kotrace `proto` value DIRECTLY as the SPA pktdeal
    slot index, but stock's `zte_api_pp_set_pro_action` REMAPS proto→ptype-slot first (71-case switch).
    So mainline's forward/trap actions landed on the WRONG slots → TCP control frames (pure-ACK/SYN/FIN)
    trapped to CPU (~62k/flow). FIX: force stock's actual forward-slot set
    {0x0c,0x0d,0x17,0x1f,0x22,0x24,0x25,0x26,0x2c,0x2d,0x2f,0x40-0x45} to deal=0 via
    `zx_spa_set_enty_pktdeal_cfg` (the INDIRECT write — a direct poke of 0x921d4300 does NOT update the
    live classifier; that's why the first poke-test failed). Slot set read LIVE from stock's pktdeal RAM.
    VERIFIED ON HW from boot (no runtime poke, commit 05e12e13a): TCP **354 Mbit/s, 20s, 0 retransmits,
    tm_rx delta=13** (was +60884) = ACKs HW-forward CPU-offloaded; ARP/ping 4/4 = broadcast still traps
    (bridge intact). Why prior attempts failed: forward-all broke broadcast (too broad); the bisect used
    contiguous ranges but stock's forward set is SCATTERED across both halves; direct poke missed the
    indirect classifier. NOT merged yet (verify egress + clean before merge). Details:
    stock_ack_forward_lever_re.md, hw_broadcast_flood_re.md Iter AP.

**Last updated**: 2026-06-04 (Journey #36 — ★★★ SOLVED: TCP ACKs HW-forward [tm_rx delta 13 vs +60884],
CPU offloaded, 354Mbit/s 0-retr, ARP/broadcast still traps. Root cause = missing proto→ptype remap in
zx_chip_tm_init_pro_action; fix = force stock's scattered forward-slot set via spa_set_enty_pktdeal_cfg.
Stock parity achieved + implemented [commit 05e12e13a, branch hw-ack-forward NOT merged]). Prior #35 —
stock forwards ACKs [decisive]. #34 — no HW bcast flood. #28 — pruned+merged. #27 — WEDGE SOLVED. Earlier #34 — no HW broadcast flood [broadcast, separate]. #28 —
pruned+merged. #27 — WEDGE SOLVED. #23 — port1 SOLVED.

**(superseded) Journey #34**: 2026-06-04 — CONCLUSIVE: chip has NO autonomous HW broadcast flood;
stock ALWAYS traps broadcast→CPU+SW-flood. drop_PP is just the OPC terminal drop counter. Full-HW L2
bridge NOT achievable on this silicon; our merged 354Mbit/s [data HW-fwd + control/bcast trap+CPU] =
stock parity for L2. "ACKs-via-HW full" isn't real here. Found cleanup bugs [dueling 0x8300 0xFF/0,
0x863c, 0x8008]. INVESTIGATION CLOSED). Prior #33 — converges on dead-end. #28 — pruned+merged. #27 —
WEDGE SOLVED. #23 — port1 SOLVED.
Manually maintained; update when you change slot A or boot a different kernel.

## Slot A NAND (kernel + rootfs)
- **Kernel at 0x700000**: stock (factory) — last touched 2026-05-22 ~13:00
  during mainline-flash attempts (those wrote then we recovered to stock).
- **Rootfs at 0xa60000**: stock-traced custom JFFS2 (cspd patched + kmsg2uart
  baked) from iter 8c. Slot A still has this rootfs even after mainline
  TFTP attempts (we never reflashed slot-A rootfs in those attempts).
- **Header at 0x2080000**: factory.

## Slot B NAND (kernel + rootfs)
- **Untouched factory stock** — always intact. cspstart falls back here
  if slot A header CRC mismatches OR JFFS2 magic missing.

## Currently running
- **Boot path**: most recent boot was via `uart.py auto_bootm_dtb_appended`
  → TFTP loaded `tftp/zImage_dtb.uimg` into RAM 0x42000000 → `bootm`.
- **Kernel**: mainline Linux 6.6 (`6.6.0-dirty`) compiled today.
- **rootfs**: in-RAM initramfs cpio embedded in the uImage. Contains:
  - `/init` — static ARM C binary, our REPL loop (forks busybox per command)
  - `/lib/modules/zx279128-eth.ko` — our driver
  - `/lib/firmware/zx-replay/{stock,cla,pm}.bin` — replay tables
  - `/bin/busybox` — **HARD-FLOAT** (will be replaced; see ROADMAP step 1)
- **Driver loaded**: yes (per `cat /proc/modules` = `zx279128_eth Live`)
- **sw netdev**: up, IP `192.168.1.99/24`, MAC `f4:f6:47:0f:42:64`
- **RX**: works end-to-end (host ARPs reach the driver; NAPI drains).
- **TX**: CPU→LAN now traverses the WHOLE switch fabric to the MAC (Journey #21):
  QMG sw_fwd → RED → DSCH → SOPC send2smac2 → **MAC2 TX counter increments** (+N
  per txtest, only smac2=host port, 0 drops). Config = UP ring + dual-kick (shared
  ring) + **egress-port hint desc[2:3]=((4+0x28)&0x3f)<<4** + MAC init-order-wipe fix
  (adjust_link re-runs full smac_init). **Final gap: MAC2→PHY→copper** — MAC counts TX
  but host NIC sees nothing (no errors either) = MAC↔PHY MII TX not driving the wire
  (RX works). MAC2 MII regs +0xc20/+0xc50/+0xb00 partial. See Journey #21.
  (NB: needs a few priming txtest frames after boot before SOPC starts firing.)

## Last-known-good for fallback recovery

If anything breaks:

| Want | Run |
|---|---|
| Re-flash factory slot A (recovery to stock-traced kmsg2uart rootfs) | `python3 zxic/tasks/00.02.stock-shell/flash_slot_a_RECOVERY.py` |
| Re-flash the slot-A stock-traced custom rootfs (cspd patched + kmsg2uart) | `cd zxic/tasks/00.02.stock-shell && ./prepare_slot_a.sh --write` |
| Boot mainline from TFTP (in-RAM, no NAND change) | `python3 zxic/lib/uart.py auto_bootm_dtb_appended` |
| Get UART shell on running mainline | `python3 -c "from lib.uart import open_port; ser=open_port(); ser.write(b'\r')"`  → type commands |
| Reset device via DTR | `python3 zxic/lib/uart.py reset` |

## Open inflight things
- `/tmp/initramfs_extract/` — current staging dir kernel embeds. May
  contain stale .ko if you forget to copy after rebuild.
- TFTP daemon — was running with cwd at OLD `H3600/tftp` path; needs
  restart pointing at `zxic/tftp` (or it serves stale files).
- Background processes from earlier uart.py log sessions might still
  hold the serial port. `pkill -f uart.py` if stuck.

## Sanity check before any iter

```sh
cd ~/Projects/MYSELF/ZTE/zxic

# 1. TFTP serving from correct path?
ps -ef | grep '[i]n.tftpd'
# expected: -a 192.168.1.50:69 .../zxic/tftp
# if wrong path or not running: sudo tools/host/tftpd_start.sh
# (full docs: docs/HOST_SETUP.md)

# 2. No stale serial holders?
pgrep -fa "uart\.py"
# expected: empty

# 3. Device reachable?
ping -c 2 -W 1 192.168.1.1   # stock
# OR ping -c 2 192.168.1.99   # our mainline assigned IP
```
