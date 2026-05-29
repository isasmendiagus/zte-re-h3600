# "sw" netdev egresses via the DN ring + BMU — "no ring" was likely a measurement artifact (2026-05-28 late)

## Empirical (netdev-ID oracle, RELIABLE method)
CPU→LAN egress interface = **`sw`** netdev. Path `br0 (192.168.1.1) → sw → eth3/MAC2`;
only sw/eth3/br0 tx_packets tick in lock-step. `sw`'s ndo_start_xmit = **`pon_tm_net_tx`**.
`sw` is registered `pon_tm_net_register(1,"sw")` → `dev+0x4c8 = 1` → **dir 1**.

## Decomp (I read these myself — full inject recipe)
`pon_tm_net_tx` dir-1 branch (LAB_00019cd8, plat:6832-6877):
- `pon_tm_get_next_txdesc(1)` → DN desc slot (plat:6834)
- `desc[0]=0x80`; if `test_da_unknown==0`: `desc[3]=3`, `desc+2 = (skb->cb[0xb4(src_port)] + 0x28) & 0x3f << 4` (egress GEM; lan_up_port=4 → 0x2c); else `desc[3]=2` (plat:6841-6852)
- queue select into desc[3] bits[7:5]
- `pon_tm_data_raw_send(skb, desc, 1)` (plat:6866)

`pon_tm_data_raw_send(skb, desc, dir)` (plat:6596-6684):
1. `uVar3 = pon_tm_bmu_alloc_bp()` — **BMU buffer alloc** (6614)
2. `__dest = u32_BP_SIZE*uVar3 + pdt_mem_size + ...`; `memcpy(__dest, skb->data, len)` — **copy frame into BP buffer** (6623-6625)
3. fill desc: BP idx → `desc+7 = (uVar3&0x7f)<<1`, `desc+8 = uVar3>>7`; len → `desc+0xc`; `desc+0xb |= 0x20` (VALID)
4. `dma_cache_maint(__dest, len)` (6679)
5. `soft_insert_tx_1desc(desc, dir)` → `*(tm_base + (dir? 0x10064 : 0x10054)) = 1` — **DN ring kick for dir 1** (6680 → 6242)

So stock "sw" egress = BMU alloc + memcpy + DN desc + **kick TM[0x10064]**. Unambiguous.

## Why this CONTRADICTS the "no ring / BMU flat" oracles — and why those are SUSPECT
- **DN consume (0x10068) measured 0**: but the DN-ring oracle used the `/proc/kmsg`
  fpga-read method BEFORE the read-drop bug was diagnosed. The netdev-ID agent later
  found: "the first read after cat-start is dropped; per-reg short-lived cats / (&)
  subshells lose the printk." So the earlier 0x10068=0 may be a **dropped-read false 0**.
- **BMU regs flat**: 0x800c (BP index), 0x8010, 0x8014 are alloc-request/result regs,
  **not monotonic counters** — reading them before/after shows the last value, not a
  count. "Flat" is **uninformative**, not proof of "no BMU alloc." The netdev-ID agent
  over-concluded "BMU not consumed."
- (UP ring 0x10054/58/5c and IDM 0x8040/44 were also early-method reads; only the QMG
  sw_fwd / MAC2 TX climbs are solidly reliable across oracles.)

## Strong hypothesis (reverses "software-forward, no ring")
Stock "sw" egresses via the **DN ring + BMU**, exactly per `pon_tm_data_raw_send` dir-1.
The mainline driver's OLD zx_sw_xmit used the **UP ring** (dir 0, kick 0x10054, desc[0]
=0xc9) → reached QMG sw_fwd but not SOPC. The fix is to replicate **dir-1**: BMU alloc +
memcpy + DN desc (desc[0]=0x80, desc[3]=3, desc+2 egress-GEM, BP idx) + **kick 0x10064**.
(A prior mainline DN attempt "0x10068 HIGH16 grows but never drains" likely had a
desc-format mismatch — replicate raw_send EXACTLY.)

## Next
1. RE-MEASURE DN consume 0x10068 (+ UP 0x10058, cursors 0x1005c/0x1006c) on stock with
   the CORRECTED /proc/kmsg method (persistent cat, ~1.2s warmup, throwaway first read)
   during a ping flood. If 0x10068 climbs → DN ring CONFIRMED.
2. Then implement the dir-1 DN replica in zx_sw_xmit and test (txtest → QMG sw_fwd +
   SOPC send2smac2 + SMAC2 TX should all climb).
