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
