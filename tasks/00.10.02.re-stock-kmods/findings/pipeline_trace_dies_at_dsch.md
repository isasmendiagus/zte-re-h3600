# Pipeline trace: CPU-TX frame DIES at the DSCH drop (2026-05-28)

Method: live per-stage counter trace (no rebuild) using `memdump` on the
egress-path counters mapped in `pipeline_counter_map.md`. Read baseline → ping
host 6× → re-read → diff. Counters are free-running `readl(e->base + off)`;
phys = 0x921c0000 + off.

## Result — deltas for 6 pings (= ~6 device ARP-reply TX frames)
```
CLA_fwd (0x9238c3cc)        d=0    (TX doesn't traverse CLA — RX-side classifier)
QMG_sw_fwd (0x9234c044)     d=+6   ← frames REACH QMG and are forwarded
QMG_hw_fwd / hw_trap        d=0
DSCH in/out queues          changed (activity)
drop_DSCH (0x921da04c)      d=+6   ← *** THE FRAMES ARE DROPPED HERE ***
SOPC_send2smac2 (0x921d9164) d=0   ← never reach the crossbar→MAC stage
SMAC2 TX (0x92280714..)     d=0    ← MAC[2] never sees them
drop_PP (0x921da040)        d=0
drop_RED (0x921da044)       d=+1   (minor)
```

## Conclusion (definitive localization)
The CPU→LAN egress frame is **dropped at the DSCH (downstream scheduler)**:
QMG forwards it (sw_fwd +6) → DSCH **drops** it (drop_DSCH +6, exactly matching
the 6 TX) → it never reaches SOPC `send2smac2` or MAC[2]. This is THE gate. All
prior suspects (MAC enable, flood, isolation, aging, FDB) are downstream/unrelated
to this drop — the frame dies before egress-port selection.

## Where to look next (DSCH config)
The DSCH config is mis-set so it drops CPU-sourced egress frames instead of
scheduling them to the egress queue/port. Prime suspects = the TM-DMA/DSCH region
divergences from `live_vs_live_diff_data.md` (phys 0x921d00xx = e->base+0x100xx):
e.g. 0x921d00e8 stock=0x00ed0000/main=0, 0x921d00ec stock=0xb3b30000/main=0,
0x921d00f8 stock=0x00aa0000/main=0x000e0000, 0x921d00fc stock=0x00004d4d/
main=0x00000e0e, 0x921d0114 stock=0xededaaaa/main=0x00000e0e, 0x921d0118
stock=0x00009797/main=0x0000230e — these look like per-queue DSCH
weight/rate/enable tables (stock has them populated, mainline near-zero).
Likely the DSCH egress queue for the CPU/LAN-up path has no rate/credit or isn't
enabled → drop. RE the DSCH init (tm dsch / sch setters in decomp_all_tm.c) to
find the queue-enable / rate / queue→port binding mainline omits. Some of these
may be poke-testable (unlike the dynamic QMG block at 0xc000).
