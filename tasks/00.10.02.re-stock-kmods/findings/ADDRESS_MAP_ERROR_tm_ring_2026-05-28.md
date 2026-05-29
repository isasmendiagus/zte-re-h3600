# THE address-map error: TM ring is at tm_base+0x10000 (0x92350000), NOT npp+0x10000 (0x921d0000) — 2026-05-28 night

## What broke the whole "ring-less egress" saga
All the live oracles measured the TM UP/DN ring counters at **0x921d00xx** (= npp_base
0x921c0000 + 0x10000), inherited from the arch doc's claim "TM DMA 0x10000 = 0x921d0000".
**That base is WRONG.** The TM block is a SEPARATE DT node from npp:
- Stock decomp: `npp_base = of_iomap(nodeA,0)` (plat:8981); `tm_base = of_iomap(nodeB,0)`
  (plat:8996) — different nodes.
- `tm_base = 0x92340000`, PROVEN: the QMG sw_fwd counter (which DID tick correctly with
  egress in every oracle) is at **0x9234c044** = tm_base + 0xc044. QMG lives at tm_base+
  0xc000 = 0x9234c000. So tm_base = 0x92340000.
- Therefore the TM ring is at tm_base + 0x10000 = **0x92350000**:
  UP kick 0x92350054 / UP consume 0x92350058 / DN kick 0x92350064 / DN consume 0x92350068.
- The oracles read 0x921d0054/58/64/68 = npp+0x10000 = the **SMCT/SIPC block** (a DIFFERENT
  block) — which is why they read 0 (or SMCT-gauge behaviour at 0x40/0x4c). **The real TM
  ring was never measured.**

## What kotrace proved (stock_egress_fn_trace_re.md)
During a real ping reply, stock runs (every frame, in order):
`pdt_ethdrv_send → pon_tm_net_tx → pon_tm_data_raw_send(dir=1) → soft_insert_tx_1desc(desc,1)`.
`soft_insert_tx_1desc(_,1)` writes `*(tm_base+0x10064)=1` = **0x92350064 (DN ring kick)**.
So stock DOES use the TM DN ring. The "ring-less" conclusion was an address artifact.

## Why mainline still fails (the actual fix)
Mainline's `tm_write` targets `e->base + TM_OFF(0x180000) + off` = 0x9235xxxx — the CORRECT
tm_base. But the OLD zx_sw_xmit kicked the **UP ring** (tm_write 0x10054, dir 0, desc[0]=0xc9)
→ reached QMG sw_fwd, died at SOPC. **Stock uses the DN ring (0x10064, dir 1, desc[0]=0x80).**
A prior mainline DN attempt saw "0x10068 HIGH16 grows but never drains" → it kicked the right
address but the desc format was wrong.

## The fix to implement + test
Rewrite zx_sw_xmit to replicate stock `pon_tm_data_raw_send` dir-1 exactly:
- BMU alloc a BP, memcpy frame into the BP buffer (mainline old code already does BMU alloc).
- Build the DN desc: desc[0]=0x80; desc[3]=3; desc+2 = (src_port+0x28)&0x3f<<4 (lan_up_port
  =4 → 0x2c0); BP idx → desc+7=(bp&0x7f)<<1, desc+8=bp>>7; len → desc+0xc; desc+0xb |= 0x20.
- Write to the DN desc ring (dndesc_cpu), kick **tm_write(0x10064, 1)** (NOT 0x10054).
- (mainline DN ring base already programmed: tm_write(TM_REG_DMA_TX_DN_BASE=0x10060, dndesc_dma).)

## Confirm first (verify the crux)
Re-measure stock at the CORRECT address (0x92350064 DN kick, 0x92350068 DN consume, +0x54/58
UP) during a ping flood. Predict DN consume 0x92350068 ticks with egress (UP 0x92350058 flat).
That confirms the address-map error definitively before the rewrite.
