# Verification of idm_cpuport_fabric_forward_re.md (agent hypothesis) — 2026-05-28 PM

I verified the RE agent's `idm_cpuport_fabric_forward_re.md` against decomp + live.
Mixed result: the agent's headline poke-fix is WRONG, its ring "correction" is WRONG,
but it surfaced one real source bug. Recorded so future iterations don't re-try these.

## Agent claim 1 (REJECTED): poke PON_PP_TM_CFG 0x923a001c = 0x23200000 to open egress
- The register IS real: `tm_set_pp_wan_cfg` (decomp_all_tm.c:35962) does
  `fpga_write_reg(0xe8007, val | 1<<(lan_up_port+0x19))`; `fpga_read_reg(id)= *(pon+id*4)`,
  pon=0x92000000, so 0xe8007 → phys **0x923a001c** ✓ (mapping verified myself).
- BUT **live read 0x923a001c = 0x21200000 already** (bit 29 = 0x20000000 already set;
  also bits 24,21). So nothing to add — the agent's "missing" bit is already present.
- Poked it anyway (|=bit29) → no-op, still 0x21200000. NOT clock-gated, NOT missing.

## Agent claim 2 (the other stock write — also already satisfied / unwritable)
- Stock lan_up branch (decomp plat:8937-8943) also does `pp_base+0x2c |= 1<<(lan_up_port+0x19)`.
  pp_base=0x92380000 → **pp+0x2c = 0x9238002c**.
- **lan_up_port = 4** CONFIRMED (stock boot log `boot_init_2026-05-22.log:28: lan_up=1,
  lan_up_port=4`). So the bit is `1<<(4+0x19)` = **bit 29**, NOT bit 25.
- Mainline source bug: `PP_CPU_FWD_BIT = BIT(25)` (zx-eth-main.c:130, line 1035) assumes
  lan_up_port=0. Technically wrong — should be BIT(29). HOWEVER:
- **Live read pp+0x2c = 0x00000106** — neither mainline's bit 25 nor a poked bit 29 sticks
  (only low bits 0x106 present). The high bits of 0x9238002c are read-only / not
  CPU-writable in this state. So this is a dead end via poke (and mainline's bit-25 write
  silently no-ops too).

## Agent claim 3 (REJECTED): "LAN netdev uses pon_tm_net_tx (UP ring), not idm_net_tx"
- Decomp does show `pon_tm_net_tx` (plat:6719) → `soft_insert_tx_1desc` (6680) → kicks
  `TM[0x10054]` (6239), binding `pon_tm_net_netdev_ops` (6399). So a UP-ring netdev path exists.
- BUT the **oracle's live before/after is decisive against it**: stock egressed **186 frames**
  (QMG sw_fwd, SOPC send2smac2, MAC2 TX all +186) while `TM[0x10054]=0`, `TM[0x10058]=0`,
  `TM[0x1005c]=0` the entire time (stock_live_egress_oracle_re.md:24-46). Stock does NOT use
  the UP ring. The agent's decomp inference loses to the live measurement.

## Live test of the current IDM-ring build (txtest 3/4)
- `tm_tx_count` +N and **IDM consume npp+0x8044 +N** → my new zx_sw_xmit submits and the HW
  DMA consumes the descriptors.
- BUT QMG sw_fwd (0x9234c044)=0, SOPC (0x921d9164)=0, SMAC2 TX (0x92280718)=0, 0 on wire.
  The IDM-consumed frame **vanishes before the QMG**.
- Contrast: the OLD UP-ring mainline build DID reach QMG sw_fwd (+5/+6) but died at SOPC.
  So IDM (as implemented) gets LESS far than the old UP ring.

## Net state / open question
- Stock: frame → QMG sw_fwd → SOPC → MAC2, using NEITHER the UP ring (proven) — hypothesized
  to use the IDM ring, but **that is NOT yet confirmed**.
- My IDM impl: consumed but never reaches QMG. Either my IDM descriptor/init is incomplete,
  OR stock doesn't use the IDM ring either.
- **Dispatched decisive oracle** (`stock_idm_ring_usage_oracle_re.md`): boot stock, ping,
  measure npp+0x8044 (IDM consume) before/after a real egress. If it climbs with MAC2 TX →
  stock uses IDM (fix my impl). If it stays 0 → stock uses neither ring (rethink the inject).

## word0 addressing note (checked, likely fine)
Stock idm_net_tx word0 = skb_phys − 0x80000000; mainline uses dma_map_single. RX works using
e->desc_dma in the same ring base, so the dma ops give HW-correct addresses; my word0 is the
DMA-API equivalent of stock's manual subtract. Not the suspected cause.
