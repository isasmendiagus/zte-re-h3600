# Stock CPU→LAN egress path: the DN ring was never measured (2026-05-28)

DECOMP/STATIC RE. Sources: `decomp_all_plat_zxylzb_9128S.c` (all line numbers
below are this file unless noted). Cross-checked against the two live oracles
(`stock_live_egress_oracle_re.md`, `stock_idm_ring_usage_oracle_re.md`) and the
prior (now-superseded) `stock_cpu_lan_inject_path_re.md`.

## TL;DR — the headline

**The egress IS a 16-byte software descriptor + ring kick after all — but on
the DN ring (TM[0x10064]), which neither oracle ever read.** Both oracles
measured only the UP ring (kick TM[0x10054]=0x921d0054, consume
TM[0x10058]=0x921d0058) and the IDM ring (0x8040/0x8044). The stock LAN
management netdev is named **"sw"**, its `ndo_start_xmit` is **`pon_tm_net_tx`
@ 6719**, and for that netdev the code takes the **direction-1 / DN-ring**
branch — base TM[0x10060], **kick TM[0x10064]=phys 0x921d0064**, consume
TM[0x10068]=phys 0x921d0068. So "stock uses neither ring" is almost certainly a
measurement gap, not a third mechanism. The frame is BMU-buffer-copied (not
skb-DMA'd), the desc carries a BP index + the GEM/egress-port nibble
`lan_up_port+0x28`, and the kick is to the DN ring.

## (a) The actual egress function + decomp lines

- LAN/mgmt netdev = **"sw"**, registered by `pon_tm_net_register(1,"sw")`
  (`pon_tm_net_init` @ 6951; the `param_1=1` and the error string
  "failed to register **sw** net" @ 6957 pin the name). Its ops =
  `pon_tm_net_netdev_ops`; the direction flag `dev+0x4c8 = 1` (set @ 6398).
  (The "pon" netdev is the same ops with flag 0 → UP ring; "idm0/1" use the
  separate IDM ring. Both of those are correctly observed as unused.)
- `ndo_start_xmit` = **`pon_tm_net_tx` @ 6719**. For `dev+0x4c8==1` it enters
  the `iVar6==1` branch @ **6832-6876**: `pon_tm_get_next_txdesc(1)` (DN ring)
  → fills a 16-byte desc → `pon_tm_data_raw_send(skb, desc, 1)` @ 6866.
- `pon_tm_data_raw_send` @ **6596**: BMU alloc + frame copy + desc finalize +
  `soft_insert_tx_1desc(desc, 1)` @ 6680.
- `soft_insert_tx_1desc` @ **6232**: `param_2==1` → writes **`tm_base+0x10064 =
  1`** @ 6242 (the DN-ring kick). (`param_2==0` would write 0x10054 = UP kick.)

Confidence: HIGH that "sw" is the mgmt netdev and routes to the DN ring;
MEDIUM-HIGH that the live ICMP reply specifically used "sw" vs the bridge — see
"What I could NOT pin down".

## (b) Register / doorbell sequence to enqueue (phys addresses)

`tm_base` = phys **0x921c0000** (derived: documented UP kick 0x921d0054 =
tm_base+0x10054 ⇒ tm_base=0x921c0000; same base as npp e->base). All offsets
tie to a decomp line:

1. **BMU buffer alloc** (`pon_tm_bmu_alloc_bp` @ 5772):
   - request/busy: `tm_base+0x8014` = phys **0x921c8014** — `|= 1` to request
     (5796), poll bits[1:0]==0 (5799).
   - result BP index: read `tm_base+0x800c` = phys **0x921c800c** (5787/5801);
     bit31=error, low16 = BP index `uVar3`.
   - (free path, for contrast: `tm_base+0x8010` = 0x921c8010 @ 5837.)
   NOTE: this BMU sub-block (0x800c/0x8010/0x8014) is DISTINCT from the IDM
   ring (0x8040 kick / 0x8044 consume) that the oracle read as 0. Same 0x8000
   window, different registers. Confidence HIGH (mapping is arithmetic).
2. **Frame copy into the BMU buffer** (6623-6625): `__dest = u32_BP_SIZE*BP +
   pdt_mem_size + ...` then `memcpy(__dest, skb->data, len)`. The frame is
   COPIED into a HW-pool buffer; the descriptor references it by **BP index**,
   not by skb DMA address. (This is the "shared BMU pool" the task hinted at —
   RX fills BP buffers, TX copies into a freshly-alloc'd BP.)
3. **Descriptor fields** (16 bytes, `puVar3[0..3]`; DN branch @ 6841-6864):
   word0=0x80; BP index packed as `desc+7 |= (BP&0x7f)<<1` and `desc+8 =
   BP>>7` (6661-6662); length `desc+0xc = len<<2` (6663); `desc+8 bits[?] =
   len<<9` (6666). Egress metadata: see (c).
4. **cache maint + DOORBELL** (`soft_insert_tx_1desc` @ 6232): `dma_cache_maint(
   desc,0x10,1)` then **`*(tm_base+0x10064) = 1`** = write **1** to phys
   **0x921d0064** (the DN-ring kick). DN desc-ring base is `tm_base+0x10060`
   = phys 0x921d0060 (programmed in `pon_tm_dma_init`-adjacent init).
5. **TX-done/reclaim**: `pon_tm_check_tx_done_nolock(1)` @ 6369 reads
   `tm_base+0x10068` = phys **0x921d0068** (DN consume), low16 = consumed count.

So the doorbell is `0x921d0064 = 1`, and the consume counter to watch is
`0x921d0068` — **neither was in either oracle's read list** (they read 0x10054/
0x10058). Confidence HIGH on the register identities; the only open item is
whether the live frame used this netdev (b/c).

## (c) Egress-port / DA metadata

In the DN branch with `test_da_unknown==0` (the normal case, 6845-6848):
```
desc[3] = 3;
*(u16*)(desc+2) = (desc+2 & 0xfc0f) | ((skb->cb[0xb4] + 0x28) & 0x3f) << 4;
```
`skb+0xb4` is the source-port byte; `+0x28` is the GEM/logical-port base. For a
CPU/host frame on lan_up, the UP branch uses the constant form
`((lan_up_port + 0x28) & 0x3f) << 4` (6800) with **lan_up_port=4 ⇒ GEM 0x2c**
(44). desc[3]=3 selects the forward class. This nibble at desc+2 bits[9:4] is
the egress-port/queue selector the fabric uses; the PP_BRG DA-lookup then
resolves to MAC2 and SOPC `send2smac2` (0x921d9164) fires. There is NO explicit
"send to MAC2" register — the GEM/port nibble + FDB DA-lookup do it.
Confidence MEDIUM on the exact bit semantics, HIGH that desc+2[9:4] = the GEM
port `src_port+0x28`.

## (d) Concrete first thing for mainline to try

**Before changing any code, re-run the oracle and read the DN ring.** The whole
"neither ring" conclusion rests on never having read 0x921d0064/0x921d0068.
Live-poke-read during a host `ping 192.168.1.1` flood:
- `0x921d0064` (DN kick) and `0x921d0068` (DN consume) — **predict these climb**
  with QMG sw_fwd (0x9234c044) / MAC2 TX-OK (0x92280718), exactly like the UP
  ring was expected to. Also read `0x921c8014`/`0x921c800c` (BMU alloc) — predict
  activity.
If DN climbs: mainline's `zx_sw_xmit` is kicking the **wrong ring** (UP
TM[0x10054]); it must build the 16B desc with a **BP-pool copy** (not skb DMA),
set desc+2[9:4] = `src_port+0x28`, and kick **TM[0x10064]** (DN), reclaiming via
TM[0x10068]. That is the minimal stock-faithful change.

If DN is ALSO 0: then it really is a non-ring inject and this DN finding is
wrong — fall back to tracing a PIO/FIFO CPU-port inject. But DN is by far the
most likely answer given the decomp.

## What I could NOT pin down (honesty)

1. **Which netdev the live ICMP reply used.** I proved "sw" → DN ring from the
   decomp, and that LAN-only mode is `g_pon_work_mode==0x10, lan_up=1` (8906),
   but I did NOT trace the kernel route/bridge to prove the 192.168.1.1 reply
   egresses via "sw" rather than via a bridge master that then hits "sw". The
   swport per-port netdevs (`pdt_ethdriver_init` @ 304, xmit shims
   `swport_dev_xmit_fin` @ 451 / `pdt_ethdrv_send` @ 789) are pure software
   bounces — they re-point `skb->dev` to a lower mii_dev and call
   `dev_queue_xmit_sk`, so they ultimately land on a HW netdev's xmit. "sw"
   (pon_tm_net_tx) is the most likely terminus, but a bridge fast-path is not
   excluded.
2. **The exact DN-ring desc-base value** at runtime (the init that programs
   TM[0x10060]) — `pon_tm_dma_init` @ 6277 programs the UP base (0x10050) and a
   0x10060 base; I did not fully decode the DN base arithmetic line, only that
   0x10060 is the DN desc-ring base register.
3. The prior `stock_cpu_lan_inject_path_re.md` claimed "sw"/"pon" both kick
   TM[0x10054]; that is WRONG — only "pon" (flag 0) kicks 0x10054; "sw" (flag 1)
   kicks **0x10064**. That error is likely why the oracle measured the wrong
   ring and concluded "neither."
</content>
</invoke>
