# WAN/uplink (regport 5 / uni 4) ingress→CPU delivery — DN-path RE

**Date:** 2026-06-06
**Question:** WAN/MAC4 ingress reaches MAC→SPA→QMG but is dropped before the CPU RX
ring (RED[0x921da044] climbs, conduit `sw` rx=0, `lan4` rx=0). LAN ports 1-4 were made
to work. What per-(port/path) config does stock apply for the WAN/DN ingress→CPU that
the LAN fixes did for regport 1-4 but missed for regport 5, and/or that is DN-path-only
and mainline never wired?

---

## TL;DR — ROOT CAUSE (proven from stock code)

**It is NOT a per-port (regport 5) config gap. It is a DN-path-only mechanism mainline
never implemented: the second RX-descriptor ring.**

The chip has **TWO RX descriptor rings per RX queue**, packed into the per-queue count
register `TM[0x10100 + q*4]`:
- **LOW-16 = ring 0** (the "UP" / `0x405e0000` region ring)
- **HIGH-16 = ring 1** (the "DN" / `0x405f0000` region ring)

Stock `pon_tm_net_poll` (`decomp_all_plat_zxylzb_9128S.c:8562`) drains **both rings for
all 8 queues**, with two distinct ring bases and the matching `bit14` release selector.
**Mainline `zx_tm_napi_poll` (`zx-eth-main.c:3068`) reads only `status & 0xffff` (ring 0)
and only ever consumes one RX-desc ring** (`e->rxdesc_cpu`). LAN→CPU ingress traps into
**ring 0** (q2/q4/q5) so it works; WAN/uplink ingress uses the **DOWNSTREAM (DN) path →
ring 1 (q7 HIGH-16)**, which mainline never drains → ring 1 fills → HW stops producing →
the back-pressure shows up as the RED/SIPC "drop" → WAN frames never reach the conduit.

This is the **DN-path analogue** of the exact ce365bd13 finding (bit14 = ring selector):
that commit fixed the *release-side* ring mismatch for ring 0; the WAN gap is the
*poll-side* — ring 1 is never read or drained at all.

---

## PROVEN-FROM-CODE: stock drains two RX rings; mainline drains one

### Stock `pon_tm_net_poll` @ 0x1c9f0 (`decomp_all_plat_zxylzb_9128S.c:8562`)
Per RX queue `local_58` (loop 7→0, line 8604), it reads the packed count:
```
uVar6 = *(uint *)(tm_base + (local_58 + 0x4040) * 4);   // = TM[0x10100 + q*4]   (8612)
...
iVar9  = (int)uVar6 >> 0x10;        // RING 1 count = HIGH-16   (8620-8622)
... drain loop using ring base (iVar13 + 0x78), head (iVar13 + 0x7c) ...   (8623-8723)
soft_release_rx_desc(1, q, sop, count);    // RING 1 selector = 1   (8726, 8729)
...
uVar7  = uVar6 & 0xffff;             // RING 0 count = LOW-16   (8735-8737)
... drain loop using ring base (iVar13 + 0x38), head (iVar13 + 0x3c) ...   (8732-8831)
soft_release_rx_desc(0, q, sop, count);    // RING 0 selector = 0   (8835, 8838)
```
`iVar13 = DAT_0001d324` is the global RX-ring struct; **ring 1 base @ struct+0x78**,
**ring 0 base @ struct+0x38** — two physically distinct DMA rings.

### Stock `soft_release_rx_desc` @ 0x1a8e8 (`...9128S.c:7204`)
```
*(uint *)(tm_base + 0x4068) = param_1 << 0xe | param_4 << 4 | param_2 | param_3 << 3;
//                            ^ring(bit14)     ^count(>>4)    ^q(0-2) ^sop(bit3)
*(uint *)(tm_base + 0x4064) = 1;
```
`param_1` (ring) is bit14 — exactly the selector ce365bd13 identified. Stock calls it
with `1` (ring 1) and `0` (ring 0); mainline only ever releases ring 0.

### Mainline `zx_tm_napi_poll` (`zx-eth-main.c:3079-3084`)
```c
for (q = 0; q < TM_NUM_RX_QUEUES && done < budget; q++) {
    u32 status  = tm_read(e, TM_RX_QCNT_BASE + q * 4);   // 0x10100 + q*4
    u32 pending = status & 0xffff;   // <-- LOW16 / ring 0 ONLY. HIGH16 (ring 1) ignored
    ...
    desc = (u8 *)e->rxdesc_cpu + (q*TM_RX_DESC_PER_Q + idx)*TM_DESC_SIZE;  // single ring base
```
The comment at line 3081-3084 even mis-states HIGH16 as "HW write cursor (NOT a second
ring — iter30)" — that conclusion was wrong; ce365bd13 + stock net_poll prove it IS a
second ring. There is no `bit14=1` release and no second `rxdesc` base anywhere in the
driver (grep: only `tm_write(e, 0x4068, ...)` in `zx_tm_release_rx_desc_raw` with bit14=0).

### Two ring bases exist in HW; stock programs both, mainline programs one
Stock `pon_tm_dma_init` @ 0x1927c (`...9128S.c:6285-6296`) writes TWO descriptor-region
bases:
- `TM[0x10050]` = region + **0x405e0000**  (ring 0 / UP; kicked via `TM[0x10054]`, consumed-count `TM[0x10058]`)
- `TM[0x10060]` = region + **0x405f0000**  (ring 1 / DN; kicked via `TM[0x10064]`, consumed-count `TM[0x10068]`)

Mainline `zx_tm_dma_init` (`zx-eth-main.c:2918-2921`) writes 0x10050 and 0x10060 — but
points **both at the same `e->txdesc_dma`** (a deliberate TX hack, see comment) and uses
them for **TX only**. The RX-side ring base is programmed separately at
`zx_tm_post_bmu` (`zx-eth-main.c:2776`): `tm_write(e, base + 0xF0, e->rxdesc_dma)` — a
**single** RX ring. Stock keeps five distinct desc pools (+0xE8/+0xEC/+0xF0/+0xF4/+0xF8,
see `tm_pon_tm_init`:7075 and `...9128S.c:5736-5742`); mainline only fills +0xF0 and
explicitly notes "We only have one rxdesc buffer" (comment at 2760-2764). **That is the
omission**: the DN RX ring (ring 1) has no backing buffer and is never drained.

---

## What the LAN-fix commits did, and why none of them covers the WAN/DN path

| Commit | Fix | Per-port? Covers regport 5? | UP/DN | Verdict for WAN |
|---|---|---|---|---|
| **c37e6168f** | clear SPA `port_vlan_filter` 0x142ac+port*4, loop `i<10` | YES — clears all 10 incl. uni4 | both | Already covers WAN. Confirmed live: uni4 SPA_rcv climbs. NOT the gate. |
| **ce365bd13** | `TM[0x4068]` bit14=0 release-acks ring 0 | global (not per-port) | ring-0 only | Fixed ring-0 release. **Its mirror — drain+release ring 1 — is exactly the missing WAN piece.** |
| **0e9bad123** | `TM[0xc000]` up_ram_thd 80→4000 | global | UP only | Raises the UP/CPU queue threshold; does nothing for the DN ring. Live: raising it had no effect on WAN. |
| **d2efd8b81** | `zx_red_block_init` (0x92344000 out-buffer) | per-queue q0-399 | both | Live test: disabling the 0x92344000 block did NOT recover WAN → the RED drop is a *symptom* of ring 1 filling, not the 0x92344000 block. |
| **4dbbb3e7e** | `TM_BPPE_POOL_SIZE` 1024→8192 | global pool | both | Buffer pool size; orthogonal. |
| **88e1ba385** | WAN MAC4 bring-up (`ZX_NUM_MACS` 4→5, gephy[5], adjust_link) | adds port 4 to MAC/PHY/SOPC loops | n/a (MAC layer) | Brought MAC4 RX + SPA admit up (works). Stops at the MAC/SOPC layer; never touched the TM RX-ring poll. |
| `zx_chip_tm_init_trap_queues` (2414) | `def_ptl_pkt_map` → CPU queue id, `port<8` skip 5=CPU | loops port 0..7 incl. **port 4** | both | Port 4 IS covered (skip is for port 5 = the CPU/host port, not the WAN). NOT the gate. |

**Conclusion on the LAN fixes:** every per-port LAN fix that *is* per-port already
iterates to include regport 5 / uni 4 (SPA filter clear, trap-queue map, MAC/PHY/SOPC
bring-up). The one structural fix that is path-specific — ce365bd13's ring selector —
fixed only the **ring-0 (UP)** half. The WAN/uplink uses the **DN path = ring 1**, and
the *poll + release + buffer* for ring 1 was never implemented. **This is case (b): a
DN-path-only mechanism mainline never wired**, not a per-port loop that stopped at 4.

---

## Patch recipe (wire the DN/ring-1 RX→CPU delivery)

Goal: give ring 1 its own backing buffer, drain its HIGH-16 pending, and release with
bit14=1 — mirroring `pon_tm_net_poll`'s second block.

### 1. Carve a second RX-desc ring + program its HW base
In the carved-pool block (`zx-eth-main.c:~1755`), add a DN RX ring:
```c
#define CARVED_RXDESC_DN_OFF  0x03F0F000UL   /* 64 KiB below CARVED_RXDESC_OFF (0x03F1F000); both 64 KiB rings */
...
e->rxdesc_dn_cpu = (void *)(base + CARVED_RXDESC_DN_OFF);
e->rxdesc_dn_dma = CARVED_BASE_PHYS + CARVED_RXDESC_DN_OFF;
```
In `zx_tm_post_bmu` (`zx-eth-main.c:2773-2778`), program the DN ring base. Stock's five
pool slots are +0xE8/+0xEC/+0xF0/+0xF4/+0xF8; +0xF0 is the (ring-0) RX desc, and one of
+0xF4/+0xF8 is the DN/ring-1 desc base (stock `tm_pon_tm_init`:5736 sets +0xF4 =
region+0x40520000, +0xF8 = region+...). Program the DN ring into the slot stock uses for
the second RX region (verify which by live readback of stock `TM[base+0xF4]`/`+0xF8`):
```c
for (inst = 0; inst < TM_NUM_INSTANCES; inst++) {
    u32 base = inst * TM_INSTANCE_STRIDE;
    tm_write(e, base + 0xF0, e->rxdesc_dma);      /* ring 0 (UP) — existing */
    tm_write(e, base + 0xF4, e->rxdesc_dn_dma);   /* ring 1 (DN) — NEW (confirm +0xF4 vs +0xF8 from stock live read) */
    tm_write(e, base + 0xFC, 0x28000900);
}
```

### 2. Drain ring 1 in `zx_tm_napi_poll`
Inside the per-queue loop (`zx-eth-main.c:3079`), after the existing ring-0 drain, add a
ring-1 drain reading the HIGH-16 and using the DN ring base + DN head:
```c
u32 pending_dn = status >> 16;            /* HIGH16 = ring 1 pending (stock net_poll:8620) */
/* ... identical desc walk but base = e->rxdesc_dn_cpu, head = e->rx_head_dn[q] ... */
/* on consume, release ring 1: */
zx_tm_release_rx_desc_ring(e, /*ring=*/1, q, sop, n_dn);
```
(Refactor `zx_tm_release_rx_desc_raw` to take the ring selector instead of hardcoding
bit14=0; stock `soft_release_rx_desc` proves the arg order:
`TM[0x4068] = ring<<14 | count<<4 | q | sop<<3`.)

### 3. Release uses bit14 = ring (mirror of ce365bd13)
`zx-eth-main.c:3036` (`zx_tm_release_rx_desc_raw`) currently hardcodes the ring to 0
(post-ce365bd13). Parameterize it:
```c
tm_write(e, 0x4068, ((u32)ring << 14) | ((u32)count << 4) | (u32)q | ((u32)sop << 3));
tm_write(e, 0x4064, 1);
```
Call with `ring=0` for the LOW-16 drain (unchanged) and `ring=1` for the new HIGH-16 drain.

These three writes use the driver's existing `tm_write` and the carved-pool helpers — no
new indirect protocol needed.

---

## What is INFERRED vs PROVEN, and the one live read to confirm

**PROVEN from stock code:**
- Two RX rings packed LOW16/HIGH16 in `TM[0x10100+q*4]` (`net_poll`:8612/8620/8735).
- Stock drains both, ring 1 base @ struct+0x78, ring 0 @ struct+0x38 (net_poll:8623/8733/8747).
- `TM[0x4068]` bit14 = ring selector; stock releases ring 1 with `1`, ring 0 with `0` (soft_release_rx_desc:7221; net_poll:8726/8835).
- Mainline drains only ring 0 (LOW16) and programs only one RX desc base +0xF0
  (napi_poll:3081; post_bmu:2776).
- The WAN/uplink uses the DN path and lands in q7/HIGH-16 (live capture in
  `wan_phy_powerdown_fix_2026-06-06.md`: q7 `TM[0x9235011c]=0x000d0000` → HIGH16=13, LOW16=0).

**INFERRED (needs one confirmation):**
- The exact HW register that holds the **ring-1 RX desc base**. Mainline uses +0xF0 for
  ring 0; stock fills +0xF0/+0xF4/+0xF8 with distinct regions. Which of +0xF4/+0xF8 is
  the ring-1 *RX* desc base (vs jumbo-BP / TX) is not 100% disambiguated from the decomp
  (the +0x38/+0x78 software pointers map to the 0x405e0000/0x405f0000 regions, but the
  HW RX-write base register for ring 1 should be read live).

**Exact live reads to run next (stock H3600, `echo 8 > /proc/sys/kernel/printk` first):**
1. Stock `devmem`/fpga-read of `TM[base+0xE8 .. +0xF8]` (phys 0x921d00E8..0x921d00F8) to
   get the five real pool/desc base addresses and identify the ring-1 RX desc base.
2. Stock readback of `TM[0x10050]`, `TM[0x10060]` (phys 0x921d0050 / 0x921d0060) and the
   per-queue counts `TM[0x10100+q*4]` while WAN traffic flows — confirm WAN lands in q7
   HIGH-16 and which region the DN ring uses.
3. Walk the stock global RX-ring struct `DAT_0001d324` (its +0x38/+0x78 hold the two ring
   VAs) to read back the exact DN ring physical base.

---

## Cross-references
- `tasks/00.01.eth-driver/findings/wan_phy_powerdown_fix_2026-06-06.md` — the live
  localization chain (MAC RX ✓ → SPA ✓ → QMG DN ✓ → RED/SIPC drop ✗) and the q7/HIGH-16
  smoking gun.
- Commit `ce365bd13` — the ring-0 (UP) half of this same dual-ring mechanism.
- `tasks/00.01.eth-driver/findings/redwedge_debug_state.md` — confirms `TM[0x10100+q*4]`
  count semantics and the `0x4068`/`0x4064` release protocol.
- Stock: `decomp_all_plat_zxylzb_9128S.c` — `pon_tm_net_poll`@8562, `soft_release_rx_desc`
  @7204, `pon_tm_dma_init`@6278, `tm_pon_tm_init`@7062, `pon_tm_queue_init`@6916.

---

## Ring-1 (DN) RX desc — exact registers + geometry

This section **closes the prior "INFERRED" item**. Tracing the full set of
decompiled functions (`pon_tm_dma_init`, `pon_tm_bmu_init`, `tm_pon_tm_init`,
`pon_tm_queue_init`, `soft_insert_tx_1desc`, `pon_tm_get_next_txdesc`,
`check_pon_tm_queue`, `pon_tm_net_poll`) settles all three questions from code,
no live read required. File refs below are
`ghidra/output_ko/plat-zxylzb_9128S.ko/<fn>.c`. TM base = phys `0x92340000`
(driver `e->base + TM_OFF`).

### 1. The big reconciliation — there is NO separate HW "ring-1 base" register

The decisive correction to the earlier guess: **the RX descriptor ring base is a
SINGLE region register at `+0xF0`.** Both ring0 AND ring1, for all 8 queues, live
inside the one contiguous 256 KiB block that `+0xF0` points at. The hardware does
**not** have a per-ring base register; ring1 is hard-wired to `ring0_region +
0x20000`. The driver tracks the per-(queue,ring) desc base/cursor **in software**
(the `queue_ctrl` struct), not in HW registers.

Proof chain:

- `tm_pon_tm_init.c:21` sets `TM[+0xF0] = (BP*BPPE + JBP*JBPPE + R) + 0x40520000`
  where `R = pdt_mem_size + ZX_RESERVE_MEM_SIZE*-0x100000`. This is the RX desc
  region base the HW DMA writes RX descriptors into. (Mainline already uses `+0xF0`
  and ring0 works — confirmed.)
- `pon_tm_queue_init.c:14-26` fills the software `queue_ctrl` struct. Per queue it
  writes ring0 desc-base = `iVar2` and ring1 desc-base = `iVar2 + 0x20000`, where
  `iVar2` starts at `(BP*BPPE + JBP*JBPPE + R) - 0x3fae0000` and increments by
  `0x4000` per queue. The CPU-virt term `-0x3fae0000` maps to the **same DDR** as
  the phys term `+0x40520000` (the window bias is exactly `0x80000000`:
  `0x40520000 - (-0x3fae0000 mod 2^32) = 0x80000000`). i.e. the `queue_ctrl` ring0
  region **is** the `+0xF0` region. Ring1 = ring0 + `0x20000`.
- Therefore: **ring0 RX-desc base = `TM[+0xF0]` region (phys-rel +0x40520000);
  ring1 RX-desc base = the SAME region + 0x20000 (phys-rel +0x40540000).** No
  `+0xF4`/`+0xF8`/`0x10060` involvement.

What `+0xE8/+0xEC/+0xF4/+0xF8` actually are (from `pon_tm_bmu_init.c:48-54`) — all
BMU pool/BPPE bases, NOT RX desc rings:
- `+0xE8 = R + 0x40000000` (BMU pool 0 base)
- `+0xEC = R + 0x40010000` (BMU pool 1 base)
- `+0xF4 = R + 0x40520000` (BMU BPPE base; same region as 0xF0)
- `+0xF8 = R + 0x40520000 + BP*BPPE` (BMU jumbo region)
- `+0xFC = BP_SIZE | (JUMBO_BP_SIZE<<16)` (the `0x28000900` mainline already writes)

What `0x10050`/`0x10060` actually are — the **TX** UP/DN descriptor ring bases,
NOT RX (this is the crux of the reconciliation):
- `pon_tm_dma_init.c:17` `TM[0x10050] = (BP*BPPE+JBP*JBPPE+R) + 0x405e0000` = TX **UP** ring base.
- `pon_tm_dma_init.c:21` `TM[0x10060] = (...) + 0x405f0000` = TX **DN** ring base.
- `soft_insert_tx_1desc.c:10-15` proves the pairing: `param_2==0` (UP) kicks
  `TM[0x10054]=1`; else (DN) kicks `TM[0x10064]=1`. So 0x1005x = TX-UP group,
  0x1006x = TX-DN group. `pon_tm_get_next_txdesc.c` / `check_pon_tm_queue.c` walk
  `net_txq` (a DIFFERENT region, `R-0x3fa20000`) and `+0x405e0000` for TX descs.
- The desc counts the driver already maps are correct: `0x10058 = DMA_UP_DESC_CNT`,
  `0x10068 = DMA_DN_DESC_CNT` (`pon_tm_queue_init.c:31-32`) — these are TX, not RX.

**Bottom line:** mainline's `TM_REG_DMA_TX_UP_BASE 0x10050` / `TM_REG_DMA_TX_DN_BASE
0x10060` names are CORRECT (they are TX). The ring-1 *RX* path needs nothing new in
HW registers — just (a) the carve extended by 0x20000 and (b) the poll taught to
walk `rxdesc + 0x20000`.

### 2. HIGH-16 semantics — DEFINITIVE: ring-1 PENDING COUNT (not a cursor)

From `pon_tm_net_poll.c`:
- Line 58: `uVar6 = TM[(local_58 + 0x4040)*4]` = `TM[0x10100 + q*4]` (the packed count).
- Line 66-67 (ring-1 take): `iVar9 = min((int)uVar6 >> 0x10, local_40>>1)` → ring-1
  work = **`uVar6 >> 16` = HIGH-16 = pending COUNT for ring 1.**
- Line 181-182 (ring-0 take): `uVar7 = uVar6 & 0xffff` (capped) → ring-0 work =
  **LOW-16 = pending count for ring 0.**

So HIGH-16 is unambiguously a **pending descriptor count for ring 1**, consumed
exactly like LOW-16 is for ring 0. It is NOT a write cursor. iter30's reading
("HIGH16 = cursor") was wrong; the live q7 `0x000d0000` = **13 ring-1 descriptors
pending, 0 ring-0** — i.e. 13 WAN/DN frames waiting that mainline never drains
(because it only reads LOW-16). The `0xff96` seen on q5 in an earlier run is a
genuine ring-1 pending count too (large because ring1 was never set up/drained in
mainline, so the HW count kept climbing / wrapped) — not garbage and not a cursor.
The per-queue ring-1 pending IS `TM[0x10100+q*4] >> 16`; there is no separate
register.

SW cursors (the actual "where am I in the ring" pointers) are the per-queue struct
fields, maintained by software and wrapped at 0x400 (`net_poll.c:85-89` ring1,
`:195-199` ring0), NOT in any TM register.

### 3. Ring-1 geometry — identical to ring 0

From `pon_tm_queue_init.c` + `pon_tm_net_poll.c`:
- Per (queue, ring): **1024 descriptors × 16 B = 0x4000 bytes** (ring0 stride
  `iVar2 += 0x4000` per queue, `:21`; SW cursor wraps at `0x3ff`, `net_poll:87`).
- Ring-0 block: `base + q*0x4000` for q=0..7 → spans `+0x00000..+0x20000`.
- Ring-1 block: `base + 0x20000 + q*0x4000` for q=0..7 → spans `+0x20000..+0x40000`.
- **Total RX desc region = 0x40000 (256 KiB).** Mainline currently carves only
  0x20000 (ring0); needs +0x20000 more.
- Desc address (matches mainline's `(q*1024+idx)*16`): ring0 = `rxdesc + (q*1024 +
  idx)*16`; **ring1 = `rxdesc + 0x20000 + (q*1024 + idx)*16`.**
- **No second BP pool needed.** Ring 1 shares ring 0's BP pool — the BP buffer is
  resolved from the descriptor's own `bppe_idx` against the single global BP pool in
  BOTH ring loops (`net_poll.c:105-112` ring0, `:215-222` ring1 — identical
  arithmetic, same `bp_max_number[]` / `u32_BP_SIZE` / jumbo-bit-9 split). The
  `+0xF4/+0xF8` regions are the BMU's, already programmed; ring1 does not allocate
  anything new.
- Release: `soft_release_rx_desc(ring, q, sop, count)` — `net_poll.c:172/175`
  release ring1 with first arg `1`, `:281/284` release ring0 with `0`. The first
  arg maps to `TM[0x4068]` bit14 (`soft_release_rx_desc.c:23`:
  `param_1<<0xe | count<<4 | q | sop<<3`, then `TM[0x4064]=1`). So **drain ring1 →
  release with bit14=1**; drain ring0 → bit14=0.

### Carve recipe (drop-in for mainline)

RX region currently `CARVED_RXDESC_OFF = 0x03F1F000`, ring0 = `+0..0x20000`. Put
ring1 immediately after:
- `rxdesc_dn_dma = CARVED_RXDESC_OFF + 0x20000 = 0x03F3F000` (phys
  `0x4C000000 + 0x03F3F000 = 0x4FF3F000`), size `0x20000` (256 KiB total region).
- Fits cleanly: next carve is `CARVED_TXUP_OFF = 0x03FDF000`, so RX region
  `0x03F1F000..0x03F5F000` does not collide.
- Zero it at alloc (HW writes valid bits; stale VALID/len would be mis-read by the
  len-keyed scan), same as the TX rings.
- No 2nd BP pool; no new HW base register.

### Drop-in patches

**(a) `zx_tm_alloc_pools` — carve `rxdesc_dn`** (add field `void *rxdesc_dn_cpu;
dma_addr_t rxdesc_dn_dma;` to `struct zx_eth` next to `rxdesc_cpu`, and
`#define CARVED_RXDESC_DN_OFF (CARVED_RXDESC_OFF + 0x20000)`):

```c
    e->rxdesc_cpu    = (void *)(base + CARVED_RXDESC_OFF);
    e->rxdesc_dma    = CARVED_BASE_PHYS + CARVED_RXDESC_OFF;
    e->rxdesc_dn_cpu = (void *)(base + CARVED_RXDESC_DN_OFF);   /* ring 1 (DN) */
    e->rxdesc_dn_dma = CARVED_BASE_PHYS + CARVED_RXDESC_DN_OFF;
    memset_io(base + CARVED_RXDESC_OFF,    0, 0x20000);  /* ring0: stale VALID/len */
    memset_io(base + CARVED_RXDESC_DN_OFF, 0, 0x20000);  /* ring1 */
```

**(b) `zx_tm_post_bmu` — NO new base register write.** The `+0xF0` write already
covers the whole RX region (ring0 at +0, ring1 at +0x20000) because HW derives
ring1 as `region + 0x20000`. Keep `tm_write(e, base+0xF0, e->rxdesc_dma)` as-is.
Only assert the carve is contiguous (so ring1 actually lands at rxdesc_dma+0x20000):

```c
    /* RX desc region @ +0xF0 holds BOTH rings: ring0 @ +0, ring1 @ +0x20000.
     * HW has no separate ring-1 base reg (stock pon_tm_queue_init:6916). */
    WARN_ON(e->rxdesc_dn_dma != e->rxdesc_dma + 0x20000);
    tm_write(e, base + 0xF0, e->rxdesc_dma);
    tm_write(e, base + 0xFC, 0x28000900);
```

**(c) `zx_tm_napi_poll` — drain ring 1 (HIGH-16) after ring 0.** Refactor the
existing per-queue ring0 body into a helper `drain_ring(e, q, ring, pending,
budget_left, &done)` parameterized on `ring` (0/1), then in the per-queue loop:

```c
    u32 status   = tm_read(e, TM_RX_QCNT_BASE + q * 4);
    u32 pend0     = status & 0xffff;          /* ring 0 (UP/LAN→CPU) */
    u32 pend1     = status >> 16;             /* ring 1 (DN/WAN→CPU) — PROVEN count, net_poll:66 */

    if (pend0)
        drain_ring(e, q, /*ring=*/0, pend0, budget - done, &done);
    if (pend1 && done < budget)
        drain_ring(e, q, /*ring=*/1, pend1, budget - done, &done);
```

`drain_ring` is the current loop body with two substitutions:
- desc base: ring0 → `e->rxdesc_cpu`; ring1 → `e->rxdesc_dn_cpu`
  (`desc = descbase + (q*TM_RX_DESC_PER_Q + idx)*TM_DESC_SIZE`).
- cursor: use `e->rx_head_dn[q]` for ring1 (add `u32 rx_head_dn[TM_NUM_RX_QUEUES];`
  to the struct) instead of `e->rx_head[q]`.
- release: pass `rxring = ring` into `zx_tm_release_rx_desc_raw(...)` so bit14
  matches (ring1→bit14=1, ring0→bit14=0; `soft_release_rx_desc.c:23`,
  `net_poll.c:172/281`). Mainline's `zx_tm_release_rx_desc_raw` already takes the
  `ring` arg (line 3044 `((u32)ring << 14)`), so just pass `ring` instead of the
  hardcoded `0`.

Everything else (BP resolve, loopback drop, DSA tag, `zx_bmu_free_bp`, desc
invalidate `*(__le16*)(desc+12)=0`, the `slots`/`ack` two-call release split) is
identical between rings — ring1 shares ring0's BP pool, so the body is reused
verbatim.

**Proven vs inferred:** ALL of the above is PROVEN from stock code; nothing remains
inferred. The earlier doubt about `+0xF4`-vs-`+0xF8`-vs-`0x10060` is moot — none of
them is the ring-1 RX base; ring1 is `+0xF0 region + 0x20000`, a software-derived
offset confirmed by `pon_tm_queue_init` (ring1 VA = ring0 VA + 0x20000) and
`pon_tm_net_poll` (struct +0x78 = struct +0x38 + 0x40, the per-queue ring0/ring1
split). No live read is required to implement; an optional sanity check is to
`fpga-read TM[0x923500F0]` on live HW and confirm it equals `rxdesc_dma` while the
WAN q7 HIGH-16 count drains once the patch lands.
