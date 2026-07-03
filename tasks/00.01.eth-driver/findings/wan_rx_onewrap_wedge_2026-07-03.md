# WAN/lan4 RX→CPU "one-wrap" wedge — mechanism RE'd: QMG DN hw_trap latches at 1024

Date: 2026-07-03. Device: live H3600, mainline #464 (RAM boot). Fresh-eyes attack.
Author context: controlled mode, single agent on device.

## TL;DR — the wedge is NOT an RX-ring wrap. It is a QMG trap-to-CPU latch.

The WAN/lan4 (MAC4, external ZX5201 PHY) RX→CPU path hard-wedges after **exactly
1024** frames reach the CPU. Reproduced on demand and localized precisely with the
driver's own `pipeline_stats` seq-file (all reads via safe `readl`):

- Modem replies **keep physically arriving at MAC4** after the wedge
  (`smac4 RX_pkts` climbs 1391→1492→…, `good_uc` climbs 1308→1399→…). MAC RX is fine.
- **`QMG DN hw_trap` (phys 0x9234c04c) freezes at exactly 0x400 = 1024** and never moves
  again, while in the same window `QMG DN sw_fwd` (0x9234c044) keeps climbing
  (1331→1634→…) and `RED drop` (0x1a044) keeps climbing (+370, +104…).
- `rx_per_ingress port4` == `QMG DN hw_trap` == 1024 exactly. Every trapped frame WAS
  delivered to the CPU and released; the driver's RX ring is fully drained (all
  `TM[0x10100+q*4]` pending = 0 at the wedge).

So: after the QMG has trapped 1024 DN frames to the CPU, it **stops choosing to trap**.
Subsequent WAN frames enter MAC4 → QMG → get `sw_fwd`'d (HW L2 forward, not to CPU) or
RED-dropped, and never reach the CPU. The modem's ARP/ND/ICMP replies stop arriving →
no return path → routed WAN flows can't establish. Permanent until reboot.

This overturns the prior `rx_ring_wrap_re.md` hypothesis (RX descriptor-ring
consumer-cursor / bit14 ring-selector). That fix is in the tree and IS correct for
draining, but it is **not** the wedge: the ring drains fully, the choke is upstream in
the QMG trap decision.

## Reproduction (fully controllable, does NOT disturb PPPoE)

Rig: device `lan4` is cabled to the modem (fe80::1 = cc:29:bd:22:b4:2b, the real DIGI
modem). `lan4` has 192.168.9.1/24 + an auto IPv6 link-local. Generate sustained WAN
RX→CPU by pinging the modem's link-local FROM the device over lan4 — replies ingress
lan4 and trap to the CPU. No WAN/PPPoE reconfig, read-only on the modem.

```
ip link set lan4 up
ping -6 -c 1300 -i 0.01 fe80::1%lan4 -q      # busybox: no -f; -A/-i ok
```

Result: `rx_per_ingress port4` climbs to exactly 1024 then freezes; the ping shows
massive loss past packet #(1024 − baseline). Any further WAN ping → 100% loss.
`cat /sys/kernel/debug/zx_eth/pipeline_stats` shows the smac4/QMG/RED signature above.

Baseline (fresh boot) for reference: `smac4 RX_pkts=74 good_uc=4`,
`QMG DN hw_trap=74` (== smac4 RX), `sw_fwd=30`, `RED=14`. i.e. every WAN frame traps
1:1 until the 1024 wall.

## Evidence chain (live, wedged state)

| stage | reg / counter | reads | verdict |
|---|---|---|---|
| MAC4 wire RX | smac4 RX_pkts / good_uc | 1391→1492 / 1308→1399 (climbing) | frames DO arrive |
| SPA per-uni | uni4 SPA_rcv 0x145dc | 0x3434 (climbing) | admitted |
| **QMG DN trap** | **0x9234c04c hw_trap** | **0x400 = 1024, FROZEN** | ← THE CHOKE |
| QMG DN fwd | 0x9234c044 sw_fwd | 1331→1634 (climbing) | frames diverted to L2-fwd |
| RED drop | 0x1a044 | 14→384→488 (climbing) | downstream symptom |
| CPU RX ring | TM[0x10100+q*4] pending | all 0 | ring fully drained, not backed up |
| driver deliver | rx_per_ingress port4 | 1024 == hw_trap | 1:1 with trap, nothing lost in driver |

Ruled OUT as the primary cause (all measured, not assumed):
- **MAC4 RX halt** — smac4 RX_pkts keeps climbing post-wedge.
- **RX descriptor-ring wrap / bit14** — ring drains to 0; heads never near full; ring1
  (rxdesc+0x20000) is entirely unused (all-zero in DMA RAM); WAN rides **ring0**, not
  ring1 as the driver comments assume. HW uses per-queue stride (q0/q1/q5/q6/q7 slot-0
  still hold boot canaries; q2/q3/q4 written).
- **OPC drop_RED as the *point of loss*** — drop_RED (0x1a044) climbs only ~background
  (+14 over 300 dropped pings), NOT 1:1 with the lost frames. (Prior port1 redwedge
  died AT drop_RED; this WAN wedge is a different, earlier decision point: the QMG
  simply stops trapping, and the diverted frames mostly sw_fwd, some RED.)
- **QMG dn threshold** — `qmg dn_ram_thd` (0x9234c000 bits[25:13]) = 0x1fa0 = 8096, not
  1024. `up` bits = 0xfa0. So the latch is NOT the configured threshold.

## Interpretation — what "1024" is

1024 = TM_RX_DESC_PER_Q = the CPU trap queue's descriptor-ring depth. The QMG "trap to
CPU" enqueues to a CPU trap queue backed by a 1024-slot ring. The QMG can keep trapping
only while it has a **credit** (a free ring slot / trap-queue credit). The driver
consumes and releases descriptors (`soft_release_rx_desc` → tm[0x4068]/[0x4064],
bit14=ring) and frees BPs (tm[0x8010]), yet the QMG DN trap credit is **never returned**
— so after exactly one ring's worth (1024) of traps, the QMG runs out of trap credit for
the DN path and stops trapping. LAN/UP path is unaffected in the same run (it uses a
different QMG queue and, in practice, never reaches its own 1024 wall in these tests — so
we cannot yet say the UP path is immune, only that it wasn't exercised past 1024).

Stock's `soft_release_rx_desc` (plat decomp @0x1a8e8) is **byte-identical** to
mainline's, so the release *word* is not the difference. The difference must be either
(a) a credit-return path the QMG DN trap queue needs that mainline never issues (a
separate QMG/OPC/SADM register write, not tm[0x4068]), or (b) the sop-split accounting:
stock derives `sop` per-desc from `desc[6]&1` and releases two sub-counts (sop=0 run +
sop=1 run) — mainline forces sop=1 for delivered / sop=0 for skipped. If the trap-queue
credit is returned only on a specific sop value, mainline's sop accounting could fail to
credit it. Not yet proven; see NEXT.

## Ranked hypotheses for the FIX (untested — need a rebuild or targeted poke)

1. **QMG/OPC/SADM trap-queue credit-return the driver omits (TOP).** The trapped-frame
   consumption must return a credit to the QMG DN CPU trap queue via a register other
   than tm[0x4068]. Candidates to RE in the stock decomp: `tm_pon_tm_qmg_initial`
   (@0x4d9b8), `greg_set_opc_ram_init` (@0x32498), `adm_set_credit_cmp_mode` (@0x2a570),
   `adm_set_protocol_pkt_map` (cpu_queid/pps_bucket). Trace the stock RX path for ANY
   register write per consumed CPU-trapped frame beyond soft_release_rx_desc + bmu_free.
   → If found, add that write to zx_tm_napi_poll after delivery, rebuild, retest.

2. **sop-split credit mismatch.** Match stock exactly: derive sop from `desc[6]&1`,
   accumulate sop=0 and sop=1 sub-counts, release each with its true sop. Cheap driver
   change, low risk. Rebuild + retest.

3. **A QMG/OPC/SADM trap-credit RAM re-init on a watchdog** (analogue of the old
   redwedge "find a TM/QMG soft-reset" lead, now scoped to the DN trap queue). If the
   credit register/RAM can be re-armed live, a driver watchdog (detect: QMG DN hw_trap
   0x9234c04c stuck while smac4 RX climbing) could re-arm it. Needs the exact
   credit/reset reg first (blocked on #1's RE).

4. **cpu_qid contention.** Identify the WAN/DN `cla_set_cpu_queue_id` result (which qid
   the WAN ICMP/ND ptypes trap to) and check whether that qid's ring credit is the one
   maxing. May reveal the driver is releasing the wrong qid/ring for the DN trap.

## What was tested this session

- Reproduced + localized (above). No fix applied yet — the mechanism RE consumed the
  session and the credit-return register is not yet identified.
- CLA fwd/drop/copy and SADM pass/drop counters stay 0 throughout (the trap path does
  not touch the offload/forward counters — consistent with a pure trap-queue-credit
  issue, not a CLA/forwarding decision).

## ⚠ Operational lesson (cost a device hang + DTR recovery this session)

Do **NOT** `memdump` (raw physical read) the **MAC4 register block at phys 0x92300000+**
(NOT 0x92140000 — MAC4 = e->base 0x921c0000 + offset 0x140000 = **0x92300000**). A raw
read into that block stalled the CPU bus and hung the whole device (no console, no net) →
required DTR power-cycle + TFTP re-boot to recover. Read MAC4 (and all MAC) RX counters
via the driver's `pipeline_stats` seq-file instead (it uses `readl` on the properly
mapped/clocked window). The safe live memdump range for probing is the TM/PP block
(0x921c0000..0x923bffff worked, e.g. QMG at 0x9234c000, drop_RED at 0x921da044, DMA ring
in RAM at 0x4ff1f000); the MAC sub-blocks are the hazard.

## Handy live recipe (for the next session)

```
# on device (mainline):
mount -t debugfs none /sys/kernel/debug 2>/dev/null; echo 8 > /proc/sys/kernel/printk
ip link set lan4 up
cat /sys/kernel/debug/zx_eth/pipeline_stats | grep -E 'smac4|QMG DN|drops:'   # baseline
ping -6 -c 1300 -i 0.01 fe80::1%lan4 -q                                        # wedge
cat /sys/kernel/debug/zx_eth/pipeline_stats | grep -E 'smac4|QMG DN|drops:'   # QMG DN hw_trap=1024 frozen
# QMG counters direct:  memdump 0x9234c044 0x20   (c044 sw_fwd, c048 hw_fwd, c04c hw_trap DN)
```

---

## APPENDIX (2026-07-03, second agent) — three fix-hypotheses LIVE-TESTED & RULED OUT

Device was already alive on arrival (#464, REPL) — no recovery needed. Re-confirmed the
exact same signature independently: **`0x9234c04c` (QMG DN hw_trap) latched at `0x400`
while `smac4 RX_pkts` climbs (1538→1719)**, UP hw_trap climbs (92→222, LAN/UP→CPU healthy),
RED drop climbs (14→680). The device **re-wedges from the modem's background traffic alone**
after boot — no ping needed. All tests via safe debugfs `poke` on KNOWN TM addresses; NO
MAC4 memdump.

Three of the ranked hypotheses above were live-tested (no rebuild) and **eliminated**:

1. **RX-ring / trap-queue DESCRIPTOR credit (`tm[0x4068]` sop=0) — RULED OUT.**
   Manually issued `soft_release_rx_desc(ring0, q, sop=0, count=0x400)` for **all 8 queues**
   (poke `TM[0x4068]=0x4000|q` then `TM[0x4064]=1`, phys 0x92344068/0x92344064). hw_trap
   stayed pinned at 0x400 — no frames resumed. ⇒ the missing credit is **NOT** the RX-DMA
   ring consumer credit, and adding a sop=0 release in the poll will NOT fix it. (Combined
   with `tm_rx_count==traps`, the ring is definitively not the choke.) This down-ranks
   hypothesis #2's descriptor-credit variant.

2. **SADM admission (PPS) policer — RULED OUT.** `SADM pass[0x1c4200]=0 drop[0x1c4208]=0`
   throughout the wedge → the admission block is inert; not the gate.

3. **QMG config re-apply — RULED OUT.** Re-wrote the full QMG init live
   (`0xc000=0x01f40fa0, 0xc004=2, 0xc008=0, 0xc00c=0x3ff, 0xc010=0xfaa, 0xc02c=0x1112`) —
   hw_trap unchanged. Also proved `0xc044/0xc04c/0xc060` are **read-only stat counters**
   (poke writes ignored). So the latch is NOT any writable QMG *config* register, and a
   watchdog that merely re-applies QMG config will NOT clear it (down-ranks hyp #3's
   config-reinit variant).

### Refined conclusion + narrowed leads
The gate is an **internal QMG-DN / OPC per-CPU-queue trap occupancy that is not exposed as
any writable direct TM register.** Remaining viable fixes, re-ranked:

- **(A, top) OPC-RAM indirect occupancy.** `greg_set_opc_ram_init` (stock @0x32498) inits
  OPC RAM via `tmOnuRegWrite(0x19, ctrl, 0, &gregRegTable)` — indirect, table entry stride
  0x1c (fields: base_off +8, mask +0xc, shift +0x10, stride +0x14), address resolved through
  `fpga_read_reg/fpga_write_reg`. Mainline never inits OPC RAM. NEXT: extract
  `gregRegTable[0x19]` data (data symbol — dump from stock .ko/.data or ghidra) → compute the
  phys OPC-RAM access reg → read the per-cpu-queue occupancy live in the wedged state; expect
  it pinned at 1024. Then test a live re-init/decrement. (Do the address math OFFLINE first —
  an indirect-RAM poke to a wrong address risks a bus hang.)
- **(B) QMG/OPC/RED block SOFT-RESET → driver watchdog** keyed on the `0x9234c04c`-stuck
  oracle. Needs the reset bit (search stock for `*_srst`/reset of the DN trap path).
- **(C, low confidence) sop-split rebuild** — kept only because it's cheap; the live sop=0
  no-op argues against it.

### Device left
Healthy: REPL alive, kernel 6.6.0, LAN/UP→CPU flowing (smac2 & UP hw_trap climbing). The
WAN-trap wedge persists (reboot-only clear; reboot forbidden). Temporary lan4 secondary
`10.44.66.223/24` removed; PPPoE untouched; host 192.168.1.50 kept.
