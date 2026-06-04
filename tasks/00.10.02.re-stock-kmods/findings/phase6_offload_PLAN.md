# Phase 6 — HW flow offload: STAGED PLAN ("por etapas, de a cachitos")

Branch: **`phase6-hw-offload`** (main = the known-good SW router; never regress it).
Goal: established conntrack flows forward in the chip's HARDWARE (wire-speed), CPU only sets up —
stock's FFE model. Today the CLA traps everything to the CPU (memory zte-hw-forwarding-deadend), so
all routed/NAT traffic is software-forwarded. This is the HARD, OPEN RE problem — incremental.

## Working conventions (per user, 2026-06-04) — apply EVERY iteration
1. **Small chunks.** One stage (or sub-stage) per iteration, each with a concrete on-HW verification.
   Don't build ahead of the RE.
2. **Findings → this dir** `tasks/00.10.02.re-stock-kmods/findings/` (the "ko-stock-findings" home).
   Name Phase-6 docs `phase6_*` or `ffe_*`.
3. **DATASHEET is a LIVING doc** `findings/DATASHEET.md`: if a live/RE result **doesn't match** an
   entry → correct it (add to the ERRATA style with date + evidence). If you **discover something
   new** (a reg, field, table format, trigger) → add it with a confidence mark (✅/🟡/❓).
4. **Dynamic stock RE = koprobe (kotrace.ko).** See `stock_instrumentation_extraction_howto.md`:
   boot STOCK, build a focused `kotrace_targets_*.h` with the FFE fns, insmod, cause a flow to
   establish (iperf/curl through the stock router), `cat /proc/kotrace_dump` → call order + r0-r3
   args; resolve func_addr via module base + nm. rmmod-safe. Source tasks/99.01.linux-stockport/kotrace/.
   Stock access: DTR power-cycle, SSH admin@192.168.1.1 / UkuGPeyRDU, TFTP pull from host .50.
5. **Commit every iteration** on this branch ("Co-Authored-By: Claude Opus 4.8 (1M context) <noreply@anthropic.com>").

## Known starting points (decomp)
FFE symbols already present: `ffe_learn_skb`, `ffe_receive_skb`, `ffe_get_npu_enable`
(decomp_all_{switch,idmfdb,plat_zxylzb_9128S}.c), and "hardfast" in decomp_all_switch.c. Prior RE:
findings/hw_forwarding_offload.md (Iters A-L, the CLA-hash hardfast chain), cla_ram_layout_re.md,
memory zte-cla-ram-layout / zte-hw-forwarding-deadend.

## STAGES (each = ~1 iteration, verifiable)

### Stage 0 — UNDERSTAND (RE only, no driver code)
- **0a static:** trace the stock FFE install path from `ffe_receive_skb`/`ffe_learn_skb`/`hardfast`:
  what decides a flow is offloadable, what builds the hardfast entry, which CLA/SBRAG/QMG/PP regs or
  indirect tables it writes, the entry format (5-tuple, egress port, NAT rewrite fields), the trigger
  (pkt count / conntrack state). Doc `ffe_hardfast_install_re.md`; update DATASHEET with new regs.
- **0b dynamic (koprobe):** boot stock, kotrace the FFE fns while an iperf LAN→WAN flow establishes;
  capture the live call order + args + (via the stock `fpga -r`) the actual reg values written.
  Ground 0a in real values. Doc the trace.
- **0c Linux side:** survey mainline 6.6 flow_offload/flowtable hooks (ndo_setup_tc TC_SETUP_FT,
  flow_block_cb, nf_flow_table_offload, flow_offload_action) + a reference driver (mtk_ppe, felix).
  Identify the minimal hook set for zx-dsa/zx-eth. Doc.
- **0d design:** `phase6_offload_design.md` — FFE-hardfast ⇄ Linux-flowtable mapping, exact per-flow
  chip programming, driver hook plan, Stage-2 milestone definition + how to measure it.

### Stage 1 — Linux plumbing (callbacks only, no chip writes)
Wire the flowtable hooks; on ESTABLISHED conntrack flow get add/del callbacks; just LOG the 5-tuple +
in/out ports. Verify callbacks fire under iperf (dmesg). Proves the Linux side in isolation.

### Stage 2 — First HW forward (one direction, no NAT) ← the first real win
On flow-add, program ONE chip hardfast entry for the simplest case (routed, no NAT, one direction).
Verify HW forwards: under iperf, the CPU-trap counters (pipeline_stats / hw_trap) go FLAT for that
flow and throughput climbs. Smallest possible offload.

### Stage 3 — NAT rewrite
Add SNAT/DNAT field rewrite to the hardfast entry (chip rewrites addr/port like conntrack). Verify a
masqueraded flow forwards in HW with correct rewrite (WAN-side tcpdump shows the NAT'd tuple).

### Stage 4 — Bidirectional + teardown
Both directions; remove the hardfast entry on conntrack del/expiry. Verify no stale entries, correct
teardown, return traffic offloaded too.

### Stage 5 — HW QoS (replaces the skipped SW-QoS phase)
Fold the chip shaper (SCH/OPC/DSCH) into the offloaded path (SW tc is bypassed by offload). Rate-limit
an offloaded flow; verify with iperf throughput. Matches stock's qos_* HW shaper.

### Stage 6 — Robustness / perf
Max offloaded throughput vs SW, conntrack-table sync, edge cases, fragmentation, multi-flow scale.

## Test rig (no WAN cable): host enxc8a362e95900↔lan1, enx2c9975313ea9↔lan2; netns 'wan' stand-in WAN;
iperf3 for load; pipeline_stats/hw_trap = whether traffic hits the CPU (offload working ⇒ flat under
load); keep TFTP .50 intact; clean up netns/addrs after (kill by pid, not pkill).
