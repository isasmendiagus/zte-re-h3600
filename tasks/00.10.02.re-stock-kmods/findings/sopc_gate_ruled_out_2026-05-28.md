# SOPC/egress-port config RULED OUT as the gate — it's the submission path (2026-05-28 PM late)

## What the SOPC RE agent verified (cross-checked decomp + live)
- **No source-gated SOPC egress matrix exists.** `sopcRegTable` covers only crc_pad /
  smac-delay/half/ready / sp_rr; `tm_pon_npp_sopc_initial` (tm:43242) writes zeros. The
  egress port N = whatever PP_BRG DA-lookup (FDB pbm) resolves. The per-source
  allowed-egress matrix is the isolate table `PP[0x83c0 + phys*4]` =
  `{fe,fd,fb,f7,ef,df,ff,ff}` = `~BIT(self)` → already permits MAC2 from every source
  AND **already matches mainline**. So the egress-port/SOPC config is correct.
- `0x921d91c8 = 0x1f` is SOPC **status** (tm:46781), not a config gate — red herring.
- **Forward, not trap:** QMG hw_trap (0x9234c04c) = 0 on BOTH stock and mainline while
  egressing. Mainline's sw_fwd is a forward, not a trap → that worry is dead.
- Port remap (load-bearing): getPort (tm:43494) = {0→1,1→2,2→3,3→4,4→5,5→0,6→6,7→7};
  CPU = logical5 = phys0.

## Live P2 poke-test (this session) — RULED OUT
On the UP-ring mainline baseline (frame reaches QMG sw_fwd), enabled MAC2 stock-style
(en=0x80000001) and poked the only two stock-vs-mainline PP_BRG drifts the agent found:
- `PP 0x92388008`: 0xff00 → **0xdfdf** (in/out-port VLAN-check)
- `PP 0x9238863c`: 0xaaaaaaaa → **0**
Then `txtest 4`:
```
QMG sw_fwd  0x9234c044  d=+4   (frame still reaches QMG)
SOPC smac2  0x921d9164  d=0    (STILL does not fire)
SMAC2 TX    0x92280718  d=0    (no egress)
wire                    0      (tcpdump nothing)
```
→ The PP VLAN-check regs are NOT the gate. SOPC config angle exhausted.

## The real gate (consistent across all evidence)
Stock egresses CPU→LAN with ALL DMA rings untouched (UP/IDM/DN consume = 0 over 100+
frames) — a pure fabric **software-forward**. Mainline's UP-ring frame reaches QMG
sw_fwd (+N) but the ring path consumes it WITHOUT feeding the SOPC crossbar →
send2smac2 = 0. So the gate is the **submission mechanism**, not any config register.

## The unresolved contradiction (must crack next)
Decomp: `pon_tm_net_tx → pon_tm_data_raw_send → soft_insert_tx_1desc` ends in a TM ring
kick (tm:6239/6242). Live: stock egresses with NO ring kicked (UP cursor 0x1005c stays
0; on mainline it advances when UP-kicked). So stock's management reply does NOT go
through pon_tm_net_tx — it uses an unidentified no-ring inject. We keep concluding this
but can't find the function by static RE (3 wrong guesses: UP, IDM, DN rings).

## Next: definitive empirical step (stock, live)
1. **Identify the egress netdev**: on stock during a ping flood, snapshot
   `/sys/class/net/*/statistics/tx_packets` idle vs flooding — the netdev whose count
   jumps ~N IS the egress interface. Then RE that specific netdev's ndo_start_xmit.
2. **Targeted reg diff** (idle vs egressing) over the BMU window (0x921c8000-0x80ff,
   esp. alloc/free pointers 0x800c/0x8014) + QMG queue cursors — to see the inject
   footprint even if the final doorbell is write-only.
This cuts through the decomp-vs-live contradiction empirically.
