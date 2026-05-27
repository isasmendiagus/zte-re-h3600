# TM RX path bench validation on stock (2026-05-27)

Bench session pivoting from "investigation only" loop into runtime validation
of the TM RX IRQ model. Stock 4.1.25 booted from factory NAND slot A.
Cables: LAN1, LAN3 (SSH path .50), WAN — all three USB-Ethernet NICs on host.

## TL;DR

- TM[0x100] **bit 0** is the GLOBAL "RX → CPU" IRQ trigger of the whole switch
  fabric. Masking it stalls every port's CPU-bound path simultaneously
  (frames buffer in the TM rings, drain in a burst on unmask).
- Stock uses **three** distinct physical RAM regions for descriptors:
  RX desc at 0x4FF1F000, UP DMA ring at 0x4FFDF000, DN DMA ring at 0x4FFEF000
  (all 0x10000 apart in the carved PDT pool at top of 256 MiB).
- Mainline writes `e->txdesc_dma` to both TM[0x10050] (UP) and TM[0x10060]
  (DN). The shared address is the most plausible root cause of the
  `tm_irq_count=0` symptom — HW pushes up to 24 entries into the UP ring and
  then stops (ring "full" relative to the colocated DN side).

## Architecture diagram

```
              ┌─────────────────────────────────────────────────────────┐
              │                ZX279128S SoC ethernet block             │
              │                                                         │
LAN 1 ─┐      │  ┌────────┐                                             │
LAN 2 ─┤PHYs  │  │        │                                             │
LAN 3 ─┤ +    │  │ switch │ ─port-to-port─ stays in fabric              │
LAN 4 ─┤ MACs │  │ fabric │                                             │
WAN  ─┘ + MAC4│  │        │ ──CPU-bound──→ ┌──────┐                     │
              │  └────────┘                │  TM  │ ─irq #29 (GIC 68)─→ CPU
              │                            │      │   bit 0 = RX pending│
              │                            │      │   bit 1 = TX done   │
              │                            └──────┘                     │
              │                              ↓                          │
              │     descriptor rings in RAM at 0x4FF1_F000 (RX),         │
              │     0x4FFD_F000 (UP DMA), 0x4FFE_F000 (DN DMA)            │
              │                                                         │
              └─────────────────────────────────────────────────────────┘
```

Key insight: **TM is the single bottleneck for "switch → CPU" traffic**.
Port-to-port forwarding (e.g., LAN1 unicast to LAN3 once ARP is warm) goes
straight through the switch fabric and **does not touch TM IRQ at all**.

## Experiment 1 — bit-0 mask on stock during ping

Method: run `ping -c 14 -i 1 -W 1 192.168.1.1 -I 192.168.1.50` in
parallel. SSH-write `0xFFFFFFFE` to `TM[0x104]` (mask bit 0), sleep 6 s,
write `0xFFFFFFFC` back (unmask). Script logs ran on device (decoupled
from SSH so the mask period didn't break the experiment).

Result:

```
ping: 14/14 received, 0% loss
       min  0.603 ms
       avg  1455 ms     ← 6-s mask buffered the traffic
       max  5940 ms     ← oldest queued frame on burst-drain
       mdev 2031 ms
```

Mask survived a full ping period. Frames did NOT drop — they queued in
the TM HW rings, then NAPI ran on unmask and drained in a single burst.
IRQ #29 stayed flat during the mask window (only +3) and resumed
afterward.

**Conclusion**: `TM[0x100] bit 0` is the gate that turns "frames pending"
into "CPU NAPI runs". Mainline mask is correct (`~BIT(0)` unmasked); the
bug is elsewhere.

## Experiment 2 — register diff stock-idle vs stock-during-ping

| Register | Idle (no ping) | During 5 pps ping | Notes |
|---|---|---|---|
| `TM[0x100]` IRQ_STATUS | `0x08` (bit 3 only) | `0x08` | bit 0 set is too brief to catch in snapshot reads, only the IRQ counter proves it transitions |
| `TM[0x104]` MASK | `0xFFFFFFFC` | `0xFFFFFFFC` | bits 0+1 unmasked |
| `TM[0xF0]` RX desc base | `0x4FF1F000` | `0x4FF1F000` | per-instance ring base |
| `TM[0x10050]` UP DMA base | `0x4FFDF000` | `0x4FFDF000` | RX-to-CPU descriptor ring base |
| `TM[0x10058]` UP DESC CNT | `2` | `0..2` (oscillates) | "pending for NAPI"; decremented by SW drain |
| `TM[0x10060]` DN DMA base | `0x4FFEF000` | `0x4FFEF000` | CPU-to-switch ring base (≠ UP, Δ 0x10000) |
| `TM[0x10068]` DN DESC CNT | `0` | `0` | TX-done count |
| `TM[0x10000]` DMA CTRL | `0x003F6564` | same | matches our mainline write |
| `MAC[0/2/4].ctrl` | `0xBA6003` | `0xBA6003` | linked pattern (LAN1, LAN3, WAN) |
| IRQ #29 pon_tm | +50-100/s baseline | +50-100/s + ping load | 30 pings ≈ +111 IRQs |

## Experiment 3 — netdev counter delta during ping

100 pings sent via LAN 3 cable (1.50 → 1.1). Stock `/proc/net/dev` delta:

```
br0:    +bytes +packets (aggregate over bridge)
pon:    +2337   ← same numbers as eth0
sw:     +20 packets only (this is NOT the path our ping enters!)
eth0:   +2337   ← aliased / shared counter w/ pon
eth1..4: minimal
```

Confirms that **`sw` is NOT the netdev where our ping arrives** despite
its name suggesting "the switch netdev". The actual CPU-bound RX lands on
`pon`/`eth0`-aliased counters. `sw` is reserved for some internal CPU
traffic on stock.

For mainline this is interesting: we only register one CPU netdev called
"sw". Stock has two ("sw" and "pon") and the `pon_tm_net_open` callback
specifically gates the IRQ unmask on the **pon** netdev being brought up.
Whether mainline's single netdev is enough or whether we need a
"pon"-equivalent path is open.

## Experiment 4 — buffer fill/drain proof during mask

Method: mask bit 0, send 50 pings rapidly (-i 0.1), dump TM rings + run
`/proc/net/dev` snapshot mid-mask, restore.

UP ring at `0x4FFDF000` during mask (4 s into a flood):

```
0x4FFDF000: 0x02C000C9   ← desc entry word 0 (status/len?)
0x4FFDF004: 0xA8010000   ← word 1 (LE: 0x000001A8 = 424; possibly length)
0x4FFDF008: 0x21010C00   ← word 2 (handle / index?)
0x4FFDF00C: 0x00000218   ← word 3
0x4FFDF010: 0x02C000C9   ← entry 2, same header
0x4FFDF014: 0x52010000
0x4FFDF018: 0x2100EC00
0x4FFDF01C: 0x000001D8
... (16-byte descriptor entries)
```

Entries are structured 4-word descriptors. **NOT raw packet payload** —
the words look like handle/length/flags pointing into a separate BMU
buffer pool. We could not pinpoint the exact pool location: stock
busybox is stripped of `od`/`head`/`seq` and our cross-compiled
`memdump` errors with "Illegal instruction" on stock 4.1 due to the
VFPv3/NEON ABI mismatch noted in `aes_key_discovered.md` memory.

Strong indirect evidence the buffers DO hold our packets:
- The RTT signature (0.5 ms baseline, max 5940 ms when mask released) is
  only explainable by frames queueing in HW then bursting out.
- IRQ counter +20 between T2 and T4 = NAPI drain burst on unmask.
- UP ring entries are non-zero and structured (not garbage / not zeroed
  out by mask).

To prove the exact payload location, would need either soft-float
cross-compile of a `memdump`-equivalent or a kernel module reading
`/dev/mem`. Neither blocks the mainline fix; deferring.

## Cursor counters at 0x9235_0100..0x9235_0114 are not packet trackers

| Reg | Stock idle | Stock after 30 pings | Mainline (Phase 52) |
|---|---|---|---|
| `0x92350100` (q0) | 0 | 0 | `0x00030000` |
| `0x92350108` (q2) | 0 | 0 | `0x00000367` |
| `0x92350110` (q4) | 0 | 0 | `0x000003BD` |
| `0x92350114` (q5) | 0 | 0 | `0x000000E6` |

Stock leaves them at 0 even under heavy ping. Mainline's non-zero values
are unrelated HW bookkeeping — **not** "RX packet cursors". Previous
mainline diagnostics interpreted them as queue depth; that
interpretation is incorrect.

## Mainline driver mismatch — UP and DN ring share `e->txdesc_dma`

```c
/* zx_eth_init_chip_tm, linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c */
2353:    tm_write(e, TM_REG_DMA_TX_UP_BASE, e->txdesc_dma);  /* TM[0x10050] */
2354:    tm_write(e, TM_REG_DMA_TX_DN_BASE, e->txdesc_dma);  /* TM[0x10060] */
```

Stock writes two distinct physical addresses (0x4FFDF000 vs 0x4FFEF000,
0x10000 apart). Mainline writes the same `txdesc_dma` to both.

Live mainline reads (from earlier session):

```
TM[0x10050] = 0x4c048000   (e->txdesc_dma)
TM[0x10060] = 0x4c048000   (e->txdesc_dma — same)
TM[0x10058] = 0x18 (24)    UP CNT stuck at 24 since boot
TM[0x100]   = 0x0A         bits 1+3, NEVER bit 0
IRQ #24 pon_tm = 0
```

Symptom chain:
1. HW pushes RX descriptors into the UP ring at `e->txdesc_dma`.
2. After ~24 entries, HW concludes the ring is "full" because UP and DN
   read/write pointers collide on the same memory.
3. HW stops pushing → bit 0 of `TM[0x100]` is never asserted (HW logic
   needs "non-empty AND room" before firing).
4. NAPI never runs → SW never drains → UP CNT stuck at 24 forever.

Fix candidate: allocate a second DMA region for DN, write it to
`TM[0x10060]`. `struct zx_eth` already has `txdesc_cpu/dma` + `rxdesc_cpu/dma`
fields — easy to add a third allocation, or alternatively use offsets
within a single larger allocation if the HW only cares about address
delta.

## Cross-validation: stock PHY IRQs work, mainline PHY IRQs broken

Stock `/proc/interrupts` shows:

```
 31:          1     GIC  71 Level     gphy0   ← LAN1 link-up at boot
 32:          0     GIC  72 Level     gphy1
 33:          1     GIC  73 Level     gphy2   ← LAN3 link-up at boot
 34:          0     GIC  74 Level     gphy3   ← no cable on LAN4 = 0 IRQs
```

Stock confirms GIC SPI 71..74 ARE the correct IRQ assignments — same
mapping our DT uses. So the storm we see on mainline `mdio-zte-...:0d`
(PHY[3] = 148M IRQs at 32 h uptime) is **not** a DT/GIC conflict with
pcie1-msi — it's a mainline driver bug in the PHY interrupt handler.
Separate fix from the TM IRQ blocker.

PHY[0,1,2] in mainline show 0 IRQs — `phy_request_interrupt` either was
not called or silently failed for these three (likely tied to the
"could not add device link" sysfs warnings at boot when multiple PHYs
attach to the single netdev sysfs slot).

## Memory allocation strategy — stock uses fixed RAM, mainline uses kernel DMA

**Stock H3600 SOFTWARE uses fixed (deterministic) RAM addresses** for the
TM descriptor rings — not because the HW requires it, but because the
stock kmod computes the address from module-init constants:

```c
/* pon_tm_dma_init, plat-zxylzb_9128S.ko @ decomp line 6290 */
*(tm_base + 0x10050) = u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE
                     + u32_BP_SIZE * u32_BPPE_POOL_SIZE
                     + pdt_mem_size
                     + 0x405e0000              /* hardcoded base offset */
                     + ZX_RESERVE_MEM_SIZE * -0x100000;
```

Every term except the base offset is set once at module init from
`.data`. The result is **always** `0x4FFDF000` on this firmware build —
a region in the upper end of the 256 MiB RAM that the bootloader carves
out of the kernel's managed memory. Stock never calls `dma_alloc_*` or
`kmalloc` for these buffers.

**The HW itself does not require fixed addresses.** It dereferences
whatever physical address is in TM[0x10050] / TM[0x10060] / TM[0xF0] as
long as it's in DMA-accessible RAM. Mainline already runs with
`dma_alloc_coherent` addresses (e.g., `0x4c048000`) and HW pushed 24
descriptors into them successfully before the UP/DN aliasing bug stopped
further pushes. So the kernel DMA path is functional on this SoC.

**Why stock uses fixed RAM**: the `pdt_mem` carved region is a contiguous
block reserved at boot for the entire packet processor data path (BP
pool, BPPE indirection table, jumbo BP pool, descriptor rings — all
co-located). Stock's BMU uses the relative offsets within this region as
linked-list indices, which only works if the region is contiguous and at
a known base. The mainline driver doesn't use that linked-list scheme —
each DMA region is independent — so contiguity isn't required and
`dma_alloc_coherent` is the correct API.

| Aspect | Stock | Mainline |
|---|---|---|
| Allocator | Carved RAM, address computed | `dma_alloc_coherent` |
| Determinism | Same address each boot | Varies per boot |
| Kernel aware? | No (hidden region) | Yes (DMA-coherent pool) |
| Contiguity? | All buffers in one region | Each buffer independent |
| HW dereference works? | Yes | Yes (confirmed empirically) |

## Mainline fix applied 2026-05-27

Single root cause: `zx_eth_init_chip_tm` wrote `e->txdesc_dma` to both
TM[0x10050] (UP) and TM[0x10060] (DN). Fix is three lines:

1. Add `void *dndesc_cpu; dma_addr_t dndesc_dma;` to `struct zx_eth`.
2. `dma_alloc_coherent` a second 16 KiB ring at `e->dndesc_dma`.
3. Change line 2354 to write `e->dndesc_dma` to TM_REG_DMA_TX_DN_BASE.

Plus matching `dma_free_coherent` + NULL check + zero-on-free.
Compiled clean against linux-v6.6. Bench test pending.

## Open follow-ups (not blocking mainline RX fix)

- PHY[3] storm: `zte_gephy_handle_interrupt` may need a proper ack
  sequence beyond `phy_read(0x1a)` (the latch may need an explicit
  write-1-to-clear or page-select). Stock manages 0 IRQs on PHY[3]
  without a cable; we manage 148M.
- PHY[0,1,2] dead: `phy_request_interrupt` likely failing silently for
  the secondary PHYs. Investigate whether all four need their own
  `phylink`/netdev attach point.
- `sw` vs `pon` netdev split: stock has two CPU netdevs and gates IRQ on
  the pon one. Mainline has one ("sw"). Once RX is unblocked we may find
  RX traffic landing in nobody.

## Mainline `/proc/net/dev` interface naming on stock for reference

```
sw        – aggregated switch-side CPU iface (low packet count)
pon       – PON/CPU iface — actual "RX from any port" landing point
eth0..4   – per-physical-port stats (eth0 mirrors pon; eth2 LAN3 is 0)
br0       – bridge containing eth0..eth4 with the .1 IP
```
