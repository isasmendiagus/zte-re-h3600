# Egress LOCALIZED to the SMCT CPU-port channel — submit still invisible (2026-05-28 late)

## Empirical breakthrough (stock_sipc_smct_sweep_re.md)
Reliable stock sweep (warmup + double-read) of the never-probed SMCT-control window
during egress found TWO live gauges ticking in lock-step with QMG sw_fwd / MAC2 TX:
- **0x921d0040 (SMCT +0x40)**: idle 0x9b9b → egressing 0xf8f8; double-read DIFFERS
  in-window (live free-running). Byte-replicated 0xXYXY = a free-level/head pointer.
- **0x921d004c (SMCT +0x4c)**: companion pointer, Δ+46, also live.
- SMCT static: +0x00/04=0xB, +0x08=0x80 (depth 128), +0x10=0x3810, +0x18=0x1 (enable).
- SIPC (0x921cc000) is NOT the doorbell (credit/mailbox bridge, non-monotonic).
- All DMA rings (UP/DN/IDM) confirmed flat (ring-less egress).

## Decomp on the SMCT regs (I read these)
- 0x1004c is written by **`dma_tx_free`** (plat:6214): `if((tm+0x1004c & 0x200000)==0)
  tm+0x1004c = p3|0x200000|p2<<12|p1<<20` — a TX-buffer FREE doorbell (post-egress).
- 0x10014/18/1c is **`dma_ram_get`** (plat:6184) — an indirect-RAM read port (cmd/done/
  data), like the SCH shaper indirect access.
- **BUT `dma_tx_free` and `dma_ram_get` have NO callers in the decomp** (grep found only
  their definitions). So either they're called via function pointers, or 0x40/0x4c are
  **HW-maintained gauges** (the HW updates the free/level pointers as it drains the SMCT
  channel) — i.e. the sweep saw the HW side, not a CPU write.

## Where this leaves us
CONFIRMED: CPU→LAN egress flows through the **SMCT CPU-port channel** (gauges move,
channel enabled, depth 0x80) — NOT the UP/DN/IDM DMA rings, NOT SOPC config, NOT SIPC,
NOT FFE (all ruled out by live measurement / decomp).
STILL UNKNOWN: the CPU's frame-SUBMIT doorbell into the SMCT channel. It is invisible to
read-only sweeps (write-only reg or DRAM-resident queue) and the decomp's obvious SW-TX
path (`pon_tm_net_tx`→`pon_tm_data_raw_send`→ring kick) does NOT run live — a contradiction
unresolved after ~10 investigations.

## The tooling wall
To SEE the submit definitively we'd need instruction-level write tracing on stock during
egress (what addresses the CPU writes) — i.e. a kprobe/kallsyms-based stock kernel module,
or JTAG. Read-only register sweeps + static decomp have been exhausted: they've mapped the
entire negative space and localized the egress to the SMCT channel, but cannot expose a
write-only/RAM submit.

## Candidate next steps (need a strategic call)
1. RE the SMCT channel SUBMIT: is there a 3rd SMCT channel (besides UP 0x50 / DN 0x60) for
   the CPU/mgmt port with its own base/kick? Trace `greg_set_smct_ram_init`, `smctRegTable`,
   the SMCT RAM descriptor layout, and how a frame desc enters the channel.
2. Heavyweight: a stock kprobe module to trace register writes during egress (definitive
   but new tooling).
3. Option B: ETH_TM2 direct-mux egress (clock-gated; ungate unsolved).
