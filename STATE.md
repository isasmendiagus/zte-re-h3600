# STATE — what's on the device RIGHT NOW

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

**Last updated**: 2026-05-29 (Journey #22 — corrected diagnosis: remaining blocker = 0x19068 READY
handshake won't assert from cold; egress-port fix + MAC init-order fix are real & kept).
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
