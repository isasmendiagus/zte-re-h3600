# ZTE H3600 zx279128-eth TX/RX path — RE notes from plat-zxylzb_9128S.ko + switch.ko

Status: **PING BIDI WORKS** as of commit a3e6a8017 (2026-05-24).
Source RE: `pon_tm_net_tx` + `pon_tm_data_raw_send` (TM TX function pair) and
`pdt_ethdrv_recv` (TM RX dispatch). Validated against live stock vs mainline
diff via UART REPL + tcpdump on host.

---

## TX path

### Layer 1 — kernel ndo_start_xmit → driver
Stock: `pon_tm_net_tx(ndev, skb)` (plat-zxylzb_9128S.ko @ 0x9c80).
Mainline equivalent: `zx_sw_xmit` in zx279128-eth.c.

### Layer 2 — BP buffer alloc + memcpy
1. Call `pon_tm_bmu_alloc_bp()` → returns BP slot index 0..255.
2. Compute `bp_buf = bp_dma + bp_idx * BP_SIZE` (BP_SIZE = 0x900 = 2304 bytes).
3. **`memcpy(bp_buf, skb->data, skb->len)`** — frame at offset 0 (NOT +0x10
   like RX; TX uses different layout — no HW metadata prefix on TX).

### Layer 3 — TX descriptor format (16 bytes)
This is what we got wrong for the longest time. Bytes:
```
offset  | bits  | meaning
--------|-------|--------
0       | 7:0   | 0x80 (constant)
1       | 7:0   | 0  (was 0xc9 in our code — WRONG, stock leaves 0)
2..3    | 9:4   | ((port + 0x28) & 0x3f) << 4 — egress port indicator!
                | ^^^ THIS WAS THE FINAL MISSING PIECE FOR TX → wire
3       | 7:5   | qid (queue id) — stock sets via bfi from skb [r5,#120]
4..7    | u32   | 0x00010000 (constant, so byte 6 = 0x01)
7       | 7:1   | bp_idx << 1 (bp_idx 0..0x7f)
7       | 0     | preserved (set by pon_tm_data_raw_send via bfi)
8       | 7:0   | bp_idx >> 7 (high bits of bp_idx; usually 0)
8..11   | 22:9  | len << 9 (14-bit packet length)
8..11   | 24    | TX VALID bit — desc[11] = 0x01 (NOT 0x20!)
12..13  | 15:0  | (small pkt) len | 0x100 or (normal) len << 2
                | small pkt path used when len < 64 + caller flag
14      | 0     | "small pkt enable" — set by caller for short frames
14      | 15:1  | r5+0xba metadata (caller-provided flags)
15      | 7:0   | (unused or another flag)
```

Key insight: **`desc[2..3]` encodes which UNI port the switch should
egress to**. Without it, switch loops the packet back to CPU (no
destination). Stock encodes this from `CSPKernel_skb_SelectQueue` which
does an FDB lookup based on dst MAC. We currently hardcode port=0 which
works because the switch then floods unknowns (causing 40% DUPs).

### Layer 4 — kick HW
1. `dma_cache_maint(desc, 16, 1)` — flush 16 bytes of desc to mem
2. Direction 1 (UP) → `TM[0x10054] = 1`  
   Direction 0 (DN) → `TM[0x10064] = 1`

HW reads desc from `TM[0x10050]` (UP) or `TM[0x10060]` (DN), processes,
sends packet out.

---

## RX path

### Layer 1 — HW writes to BP buffer + RX desc
1. HW allocates BP slot from BMU.
2. **Writes 16-byte metadata header to bp_buf[0..15]** (zeros at our
   observed point).
3. **Writes actual ethernet frame to bp_buf[16..16+len]**.
4. Writes RX descriptor at TM[+0xF0] base (rxdesc_dma area) with:
   - desc[12..13]: `cpu_to_le16(len << 2)` → our code: `le16_to_cpu(*(u16*)(desc+12)) >> 2`
   - desc[7] >> 1: bp_idx

### Layer 2 — IRQ fires, NAPI runs
1. HW fires GIC line 68 (zx279128-eth-tm) when bits 0/1 of TM[0x100]
   pending and TM[0x104] bits 0/1 cleared (unmasked).
2. `zx_tm_irq` reads status, schedules NAPI.
3. `zx_tm_napi_poll` iterates 8 RX queues, reads desc, extracts:
   - len = (desc[12..13] LE u16) >> 2
   - bp_idx = desc[7] >> 1
4. **Reads frame from `bp_buf + 16`** (NOT bp_buf + 0 — HW header offset).
5. Loopback filter: drop if src MAC == sw_dev->dev_addr.
6. `netif_receive_skb` to deliver to stack.

### Layer 3 — release RX desc back to HW
`zx_tm_release_rx_desc(q, count)`:
1. Poll `TM[0x4064] & 1` for ready (max 100 × 2us).
2. Write `TM[0x4068] = (1 << 14) | (count << 4) | qid | (sop << 3)`.
3. Write `TM[0x4064] = 1` (commit).

---

## Critical init steps (order matters)

Inside `zx_eth_probe`:
```c
zx_tm_pre_init(e);     // TM[0x000..0x134] x N instances
zx_tm_red_init(e);     // RED queue config — needed for TM IRQ bits 0/1 to fire!
zx_pp_ctrl_init(e);    // pp[0x28]=0x01070104, pp[0]=2, 52ms delay
zx_pp_brg_init(e);     // 13 PP regs + VLAN 0/1 + port6/7 isolate
zx_tm_dma_init(e);     // TM[0x10000+] DMA control + TX_UP_BASE
zx_tm_bmu_init(e);     // TM[0xE8..0xFC] desc base + BMU regs
zx_tm_post_bmu(e);     // TM[0xF0] rxdesc per-instance
zx_tm_bmu_enable(e);   // TM[0x8000] = 1
zx_chip_tm_init_*();   // CLA, isolate, pro_action replays
writel(0xa, fpga+0);   // sbrg_set_irq_en_mask (no-op due to mask=0)
bulk replay fpga.bin;  // 25k stock register values (whitelisted to TM/PP/NPP/pon-low only)
// SKIP TM[0x10050/0x10060] (TX base) and TM[+0xF0] x 4 instances in replay
zx_pp_pm_apply_replay(e);
re-write TM[0xF0] = rxdesc_dma x N instances; // redundant w/ skip but harmless
```

---

## Open questions / future work

1. **Eliminate ping DUPs**: implement minimal FDB so `desc[2..3]` port
   reflects actual host MAC's port (not always port 0).
2. **`pon_tm_int_init`**: write `TM[0x104] = 0xffffffff` after probe
   completes (rather than 0xfffffffc) — caused silent hang in earlier
   tests but may now work post-RED-init.
3. **IDM IRQ count = 0** in /proc/interrupts — IDM block isn't firing.
   May need IDM register setup we never touch.
4. **The `desc[3] qid` field**: stock encodes `[r5,#120] = skb_select_queue`
   result at bits 5..7. We use 0 — works but may matter for QoS.

---

## Validation matrix: stock vs mainline

| Init step                       | Stock source (plat-zxylzb_9128S) | Mainline source (zx279128-eth.c)        | Status |
|----------------------------------|----------------------------------|------------------------------------------|--------|
| TM clock/reset                   | `zx_pon_clk_reset_init`          | `TOPCRM[0x0C] |= 0x1E0` at probe         | ✅     |
| TM IRQ-routing TOPCRM            | (set at boot by BL/Linux init)   | TOPCRM[0x08]=0x1ff7ffff, [0x4c]=0x0003cfff | ✅     |
| TM block master cfg (per-inst)   | tm_pon_tm_init writes 0x140 to 16 inst | `zx_tm_pre_init` writes to 4 inst   | ⚠️ only 4 of 16 |
| TM RED queue config              | `pon_tm_red_init` (4 loops × 1168)| `zx_tm_red_init` (4 loops × 1168)       | ✅     |
| PP ctrl init                     | `pon_pp_ctrl_init`               | `zx_pp_ctrl_init`                        | ✅     |
| PP bridge init                   | `pon_pp_brg_init` (13 regs+VLAN) | `zx_pp_brg_init`                         | ✅     |
| Port isolation (sbragRegTable[57])| `chip_tm_init_isolate` (8 ports)| `zx_chip_tm_init_isolate`                | ✅     |
| Pro-action (def_ptl_pkt_action)  | `chip_tm_init_pro_action`        | `zx_chip_tm_init_pro_action`             | ✅     |
| BMU init + enable                | `pon_tm_bmu_init/enable`         | `zx_tm_bmu_init/enable`                  | ✅     |
| TM DMA control                   | `pon_tm_dma_init`                | `zx_tm_dma_init`                         | ✅     |
| RX desc base (TM[+0xF0])         | DMA-allocated in plat            | `e->rxdesc_dma` re-write after replay    | ✅     |
| TX desc base (TM[0x10050/0x60])  | DMA-allocated in plat            | `e->txdesc_dma` skipped in replay        | ✅     |
| TM IRQ enable (TM[+0x104])       | `pon_tm_int_init` writes 0xffffffff | `zx_tm_pre_init` writes 0xfffffffc    | ⚠️ different value but works |
| Request IRQ handler              | `request_threaded_irq(g_tm_irq, ...)` | `devm_request_irq(eth->irq_tm, ...)` | ✅     |
| RX path: read at bp_buf+0x10     | implicit (HW metadata header)    | `src = bp_buf + 16`                      | ✅     |
| TX path: desc[11]=0x01 VALID     | `*desc8 = 0x01000000`             | `(0x01U << 24)`                          | ✅     |
| TX path: desc[2..3] egress port  | `((port+0x28) & 0x3f) << 4`      | `((port+0x28) & 0x3f) << 4` (port=0)     | ⚠️ hardcoded port 0 |
| TX path: desc[3] qid             | `skb_select_queue` result bits 5..7| 0                                       | ⚠️ unused |

---

## Known artifacts / open work

### 40% packet loss + duplicates
Symptom: `ping -c5 192.168.1.99` returns 3 replies, 70 DUPlicates.
Cause: TX desc port hardcoded to 0 (LAN port 0) — switch correctly egresses
the unicast reply to LAN port 0, but may also flood-bounce a copy back to
CPU which retries. Also some pings get dropped because the loopback filter
catches our own reply on the rebound and drops it as "from self".

Fix: implement FDB so port comes from dst-MAC lookup; or use a special
"flood to all LAN ports" code if dst MAC unknown.

### tm_rx_loopback_drops scaling with traffic
With sustained traffic, drops/min grows fast. Each TX packet creates 1+
loopback drop. Indicates switch is also forwarding TX back to CPU port,
which is harmless but wastes CPU on filtering.

Fix: configure switch to not reflect CPU-source frames back to CPU port.

### TM_NUM_INSTANCES = 4 vs stock's 16
Stock initializes 16 TM instances. We only do 4. Functional today but the
12 uninitialized instances may bite us later when MORE complex TM
features get used.

Fix: bump to 16 — earlier this caused silent hang on probe but with the
RED init now in place, may work fine.

### pon_tm_int_init (TM[+0x104] = 0xffffffff)
Stock writes 0xffffffff (all bits set in mask) initially. We write
0xfffffffc (bits 0,1 cleared). The 2-bit difference may matter for some
HW state machine — or may not. Worth re-trying now that other init is
correct.
