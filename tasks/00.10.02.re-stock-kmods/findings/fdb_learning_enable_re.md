# FDB Learning Enable — Stock RE

**Question:** What register/bit does stock write to enable automatic FDB
learning of host MAC as frames ingress? Where does the HW FDB live?
What is the FDB-miss default action?

**Status:** Fully RE'd from `decomp_all_tm.c` (sbrg_* family),
`decomp_all_plat_zxylzb_9128S.c` (`pon_pp_brg_init`, `pon_pp_add_mac`,
`brg_ram_get`), live stock register dump
(`regs/stock_eth_2mib.txt`), kotrace boot trace
(`captures/kotrace_p3c_analysis.txt`), and the already-RE'd
`zx-fpga-reg-tables.h:zx_sbragregtable`. **Confidence: high.**

---

## Q1 — SMAC LEARN enable register

There is **no global "enable learning" bit**. There is a 2-bit-per-port
LEARN_MODE field packed into a single register. Stock programs every
port to mode `1` (= "standard learn-on-SMAC-miss").

### Stock call

`sbrg_set_pt_learn_mode(mode=1, port=0..7)` — `decomp_all_tm.c:5770`:

```c
tmOnuRegWrite(port + 0x22, mode, sub_idx=0, &sbragRegTable);
```

That is: 8 distinct sbragRegTable register-ids (`0x22..0x29`), one per
internal port.

### Where it lands

From `zx-fpga-reg-tables.h:zx_sbragregtable` (mainline already has
this table RE'd):

| regId (dec / hex) | base_off  | mask | shift | byte_off (PP+) |
|---|---|---|---|---|
| 34 / 0x22 | 0x000e2071 | 0x3 |  0 | 0x81C4 |
| 35 / 0x23 | 0x000e2071 | 0x3 |  2 | 0x81C4 |
| 36 / 0x24 | 0x000e2071 | 0x3 |  4 | 0x81C4 |
| 37 / 0x25 | 0x000e2071 | 0x3 |  6 | 0x81C4 |
| 38 / 0x26 | 0x000e2071 | 0x3 |  8 | 0x81C4 |
| 39 / 0x27 | 0x000e2071 | 0x3 | 10 | 0x81C4 |
| 40 / 0x28 | 0x000e2071 | 0x3 | 12 | 0x81C4 |
| 41 / 0x29 | 0x000e2071 | 0x3 | 14 | 0x81C4 |

**All 8 ports pack into one PP register: `pp_base + 0x81C4`. With
LEARN_MODE = 1 for every port, the register reads `0x5555`.**

### Kotrace confirms

`captures/kotrace_p3c_analysis.txt`:
```
--- L (tm_mac_learn_mode_set) — 8 distinct ---
  r0=0x00000000  r1=0x00000001   (×1)
  r0=0x00000001  r1=0x00000001   (×1)
  …
  r0=0x00000007  r1=0x00000001   (×1)
```
8 calls, every port, mode=1. (Note `tm_mac_learn_mode_set`
re-maps logical port 5 → internal 0 — see `decomp_all_tm.c:35672`.)

### Live stock dump confirms

`regs/stock_eth_2mib.txt`:
```
923881c4  00005555
```

### **Mainline already programs this.**

`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c:2360`:
```c
writel(0x00005555, pp + 0x81c4);
```

Mainline's `zx_pp_brg_init` writes the byte-for-byte equivalent of
stock's 8× `sbrg_set_pt_learn_mode(1, port)`. **Learning IS enabled.**
The FDB-miss / learn pipeline is therefore not the missing piece for
Q1.

The companion-but-distinct controls (all already in mainline):

| Setter | regId | PP byte | Stock val | Mainline writes? |
|---|---|---|---|---|
| `sbrg_set_pt_transfer_en(port,1)` ×8 | regId 1 | 0x8004 b0..7 | 0xff | bit 0..7 of PP[0x8004]=ff ✓ |
| `sbrg_set_pt_smac_look_en(port,1)` ×8 | regId 0x20 (32) | 0x81c0 b0..7 | 0xff | ✓ |
| `sbrg_set_pt_smac_lookfail_pktdeal(port,0)` ×8 | regId 0x21 (33) | 0x81c0 b8..15 | 0x00 | ✓ (mainline writes only low byte) |
| `sbrg_set_pt_da_lookup_en(port,1)` ×8 | regId 0x2c (44) | 0x82c0 b0..7 | 0xff | ✓ |
| `sbrg_set_pt_learn_mode(1, port)` ×8 | regId 0x22..0x29 | 0x81c4 | 0x5555 | ✓ |

---

## Q2 — Where the HW FDB lives

The H3600 has **TWO HW FDB tables**, both in the PP block. Stock has
helpers for both; mainline writes only one.

### FDB-A: PP_BRG_RAM hashed table (1024 buckets × 4 slots × 12 bytes)

* Size selector at `pp_base + 0x8184` bits 0..1: `0=1024, 1=512,
  2=256, 3=128` (live stock = 1, so 512 buckets).
* Bucket address selector: `pp_base + 0x8188` bits 0..23: live
  stock = `0x211b00` (= the hash mode / aging cycle blob).
* Hash function: `crc_16` over the 6-byte MAC, masked with `bucket_count-1`
  (`decomp_all_plat_zxylzb_9128S.c:4750` `pon_pp_add_mac`).
* **Access protocol (poll-then-write):**
  1. Spin until `readl(pp+0x8018) & 1` is set (idle).
  2. Write CMD: `writel(bucket | (slot<<22) | (read?0x08000000:0), pp+0x8014)`.
  3. Read/write payload at `pp+0x801c..0x8024` (3 words = 12 bytes).
* Entry layout (`brg_ram_get`/`pon_pp_add_mac`):
  ```
  word0 (pp+0x801c): vid_low8 | vid_hi4<<8 | status<<12 | port<<16  (etc.)
  word1 (pp+0x8020): mac[3..5]_lo + mac[2]<<24
  word2 (pp+0x8024): status_nibble<<4 | vid_hi4 | smac_ctrl<<8 | dmac_ctrl<<9
  ```

### FDB-B: sbrag indirect-protocol secondary table

Same hash, separate RAM. Accessed via sbragRegTable regs 0x13 (CMD),
0x4c/0x4d/0x4e (data words). Stock `sbrg_add_mactable`
(`decomp_all_tm.c:10706`) writes here. Mainline names this `ZX_SBRAG_*`
(`zx-eth-main.c:614-618`) and has `zx_sbrag_add_mac` (currently unused).

**Per `cpu_egress_routing_re.md`: stock auto-learning populates FDB-A
(PP_BRG_RAM). FDB-B is a parallel/shadow path that mainline can skip.**

### What live stock shows (post-ping)

`regs/stock_eth_2mib.txt`:
* `pp+0x80a8 = 0x62e95900` (host MAC bytes 5..2)
* `pp+0x80ac = 0x0000c8a3` (host MAC bytes 1..0)
* `pp+0x80b0 = 0x00000102` (status + port bitmap)
* `pp+0x88e1c = 0x62e95900` (second instance, sbrag side)
* `pp+0x88e20 = 0x0000c8a3`
* `pp+0x88e24 = 0x42017400` (status w/ aging timestamp)

Stock learned the host MAC. The entry shows up in BOTH FDB-A (the
`pp+0x80a8..0xb0` slot is a directly-readable shadow of one bucket-4
slot in PP_BRG_RAM) and FDB-B (`pp+0x88e1c..0x88e24` block).

### How to dump on mainline

Brute readback of `pp+0x80a8..0xb0` (FDB-A bucket-4 slot — quickest) or
full `pp+0x8000..0x8200` mem dump. If host MAC bytes appear → learning
worked. If zeroes → learning is silently failing.

---

## Q3 — Stock LIVE FDB vs Mainline LIVE FDB

| Region (PP byte) | Stock live | Meaning |
|---|---|---|
| 0x80a8 / 0x80ac / 0x80b0 | host MAC + port bitmap 0x102 | learned-host slot |
| 0x88e1c / 0x88e20 / 0x88e24 | host MAC + timestamp | sbrag mirror |

Mainline dump not in repo, but **mainline's `0x80a8..0xb0` SHOULD be
re-readable on the live device** via `memdump` after a ping attempt.
Bet: zero. If zero → FDB-A is not being populated despite LEARN_MODE=1.

If `0x80a8..0xb0 == 0` on mainline AFTER ARP traffic, then **the learn
pipeline isn't firing at all** — the SMAC ingress path is not reaching
the FDB writer. Candidates (NOT all in this doc's scope):

1. `tm_mac_ramaddr_sel_set(1)` — sets PP[0x8184] bits 0..1 to RAM size
   index. **Mainline does NOT call this.** Default is undefined → may
   point at a non-existent 4th table. Live stock shows `pp+0x8184=1`;
   mainline likely has 0.
2. `sbrg_set_table_sel(0)` — regId 0x1d → PP[0x8184] bits 0..1. Same
   register as (1), different alias.
3. `sbrg_set_hash_mode(1)` — regId 0x1a → PP[0x8180] bit 3.
   **Mainline does NOT write this.** Without it, hash mode = 0 (some
   default), which may not align with bucket size from (1).
4. `sbrg_set_macaddr_age_en(1)` — regId 4 → PP[0x8004] bit 17.
   Stock live: SET (`0x040200ff`). Mainline: CLEAR (`0x020000ff`).
   Without aging enabled, the HW may also not commit new entries on
   ingress (some chips gate write-on-learn through the same enable as
   age-tick).

---

## Q4 — Mainline `zx_sbrag_*` and the right call

Mainline `zx_sbrag_add_mac` (zx-eth-main.c:670) and `zx_sbrg_hash` use
the **right indirect protocol** (sbragRegTable regs 0x4c/0x4d/0x4e via
CMD reg 0x13 / BUSY reg 0x14 at PP+0x388814..0x388824), targeting
FDB-B. Per `cpu_egress_routing_re.md` the switch fabric egress decision
consults FDB-A first; FDB-B is the additional indirect-access mirror
stock uses for `sbrg_add_mactable` static entries.

**Correct stock API for static MAC** = `sbrg_add_mactable` (FDB-B) +
`pon_pp_add_mac` (FDB-A). Stock at boot only adds static entries for
multicast group MACs; unicast entries arrive via autolearn into FDB-A.

For mainline: do nothing special — auto-learn is the intended path.
The fix is to make sure FDB-A's prerequisites are set (Q3 items 1–4).

---

## Q5 — Port isolation: NOT the wedge

Mainline correctly mirrors stock's port_isolate setup:
- `pp+0x83c0..0x83dc` = per-port mask; stock LIVE has 0xfe, 0xfd, 0xfb,
  0xf7, 0xef, 0xdf, 0xff, 0xff. Mainline's `chip_tm_init_isolate` writes
  matching values via `zx_tm_port_isolate_set` (sbragRegTable regId 57).
- CPU port (internal port 0 = "port 5" externally) bit pattern in mask
  byte 5 (PP+0x83d4) = 0xdf = blocks self, forwards to all others.
  Frames FROM CPU CAN reach every LAN port — isolation is not the wedge.

---

## Q6 — FDB-miss default action: **flood-to-all (mainline) vs CPU-only (stock)**

This is the biggest single divergence we found.

`sbrg_set_unknown_unicst_fwd(port, en)` → sbragRegTable regId 0x36 (54)
→ PP[0x8340] bits 24..31, 1 bit per port.

### Stock LIVE: `pp+0x8340 = 0x015555ff`
- bits 24..31 = `0x01` = **only internal port 0 (= CPU)** gets unknown
  unicast forwarded.
- bits 8..23 = `0x5555` = PKTDEAL=1 per port (normal lookup).
- bits 0..7 = `0xff` = reserved low byte.

### Mainline writes: `pp+0x8340 = 0xff5555ff`
- bits 24..31 = `0xff` = **all 8 ports flood**.

**This means every CPU TX with an unknown-DA goes back as flood to all
4 LAN ports + the CPU port itself → CPU sees its own frame as loopback
RX. Matches the observed 32 loopback drops / 18 TXs.**

### Why mainline currently has it wrong (comment at L3310-3318):

`zx_eth_main.c:3310` explicitly says "DO NOT call
`zx_sbrg_set_unknown_unicast_flood_policy(e, 0x20)`" with the
reasoning that PP[0x8340]=0xff5555ff is the "CORRECT stock-matching
state". **This reasoning is empirically false** — stock LIVE clearly
has 0x015555ff, not 0xff5555ff.

The 0x20 bitmap (= bit 5 = port 5 externally = internal port 5) is
also wrong: stock's port-5 ⇒ internal-0 remap means the CPU bit is
**0x01**, not **0x20**.

---

## Single most actionable fix

**`writel(0x015555ff, pp + 0x8340)` after `zx_pp_brg_init`.**

This matches stock's live state exactly:
- PKTDEAL=1 per port (normal lookup, no drop on miss before flood).
- FWD bitmap = 0x01 (internal port 0 = CPU only).

Result: any unknown-DA frame's last-resort action is **trap to CPU
only**, not flood to all ports. The CPU sees one copy (in the netdev
RX path, via the normal SMAC-learn ingress), the LAN ports see NONE.
With the host's ARP request already populated FDB-A on ingress, ARP
replies thereafter hit FDB-A and forward directly to the host's LAN
port. The "frames-back-as-loopback" wedge breaks because the loop
(CPU→flood→CPU) no longer exists.

**Secondary hardening (defensive, low cost):**
1. `writel(0x000e218f, pp + 0x8004)` to set MAC age enable (bit 17)
   and macaddr_exchange_md (bit 26) per stock. Effective value depends
   on what bits are inherited — read-modify-write `|= 0x04020000`,
   `&= ~0x02000000` from `0x020000ff` baseline.
2. Call equivalent of `sbrg_set_table_sel(1)` + `sbrg_set_hash_mode(1)`
   via `zx_table_write(e, zx_sbragregtable, _, 29, 1, 0)` and
   `zx_table_write(e, ..., 26, 1, 0)` so the FDB ram_size + hash match
   stock's 512-bucket / mode-1 configuration.

(2) is only needed if (1) alone doesn't move the needle; the FDB-A
shadow at `pp+0x80a8..0xb0` will tell us empirically.

---

## Confidence

* Q1 (LEARN_MODE register/bit): **high** — kotrace + decomp + table +
  live regs all triangulate to PP[0x81c4]=0x5555. Mainline already has
  this correct.
* Q2 (FDB address): **high** — PP_BRG_RAM at PP+0x8014..0x8028 indirect
  + readback shadow at PP+0x80a8..0xb0 corroborated by stock live dump.
* Q3 (live FDB compare): **medium** — mainline live FDB dump not yet
  captured; this doc states the inspection target.
* Q4 (sbrag_* role): **high** — `cpu_egress_routing_re.md` already
  resolved this; FDB-A is the auto-learn target.
* Q5 (port-isolate): **high** — already documented in
  `cpu_egress_routing_re.md`.
* Q6 (FDB-miss action / unknown-unicast-fwd bitmap): **high** —
  stock live dump unambiguously shows `0x015555ff`, mainline writes
  `0xff5555ff`. This is the single largest deviation and matches the
  TX-loopback symptom one-for-one.
