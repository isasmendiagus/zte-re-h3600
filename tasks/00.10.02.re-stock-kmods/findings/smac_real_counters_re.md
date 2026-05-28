# SMAC wire-side statistics — exact register addresses (RE'd from tm.ko)

**Source**: stock `tm.ko` `.data` section, symbol `smacRegTable` @ `.data + 0x43b0`
(size 0x700 = 64 entries × 28 B), accessor `smac_get_statistics(port, tbl_idx, out)`.

**TL;DR for the impatient**

| Counter | Per-port physical address (port `N` = 0..4 = LAN1..LAN4,WAN) |
|---|---|
| `smac N receive total frames` (RX pkt) | `0x92200000 + N*0x40000 + 0x780` |
| `smac N receive total bytes`  (RX byte) | `0x92200000 + N*0x40000 + 0x784` |
| `smac N send total bytes`     (TX byte) | `0x92200000 + N*0x40000 + 0x714` |
| `smac N send total frames`    (TX pkt) | `0x92200000 + N*0x40000 + 0x718` |

For LAN3 (port 2, the SSH path), RX byte counter is at **`0x92280784`**. That is
the address that incremented to ~678,587 in the stock register dump
(`regs/stock_eth_2mib.txt` byte 401,396).

Mainline `pipeline_stats` currently reads `MAC[N]+0x710..0x71c` which is the
*TX* counter quartet (plus one unused offset). It has no RX counter at all.

---

## 1. The `smacRegTable` structure

Decoded from `tmOnuGlbRegValidation` / `tmOnuRegRead` / `tmOnuRegWrite`
(tm.c lines 35310, 35337, 35356):

```c
struct smacRegEntry {       /* sizeof = 0x1c (28 B) */
    u16 id;          /* +0x00 must equal index — validation */
    u16 _pad;        /* +0x02 */
    u32 access;      /* +0x04 1=RO, 2=WO, 3=RW */
    u32 off;         /* +0x08 base FPGA reg-index (dword units!) */
    u32 mask;        /* +0x0c bitfield mask */
    u16 shift;       /* +0x10 bitfield shift */
    u16 max_port;    /* +0x12 highest legal port index (always 5 here) */
    u32 stride;      /* +0x14 per-port dword stride */
    u32 count;       /* +0x18 access counter, bumped on every R/W */
};
```

The accessor math (verbatim from `tmOnuRegRead`):

```c
reg_dword_idx = entry.off + port * entry.stride;
raw           = fpga_read_reg(reg_dword_idx);            /* *(u32*)(pon + idx*4) */
value         = (raw >> entry.shift) & entry.mask;
```

with `pon = 0xf4000000` (virt) = **`0x92000000`** (phys); `fpga_read_reg`
itself is `zx_ponreg.ko`'s `*(u32*)(pon + idx*4)`.

So:
```
phys_addr(tbl_idx, port) = 0x92000000 + (smacRegTable[tbl_idx].off
                                       + port * smacRegTable[tbl_idx].stride) * 4
```

For every stats entry, `stride = 0x10000` (dwords) = **0x40000 bytes** — matches
the MAC[N] block stride we already use (`MAC_STRIDE` in mainline).

`smacRegTable[i].off` always starts in the band `0x80000..0x801ff` (dword) =
byte band `0x200000..0x2007fc` from `pon_base`. With `pon_base = 0x92000000`,
that lands inside `0x92200000..0x922007fc` — i.e. **MAC[0]** at byte offsets
`0x000..0x7fc`. Per-port copies are at MAC[N]+same offset. So every wire-side
counter lives **inside the existing 2 MiB ETH MMIO window** mainline maps at
`0x921c0000`.

Sanity check from stock register dump (`regs/stock_eth_2mib.txt`, captured
while port 0 / LAN1 had traffic):

| tbl idx | computed addr | label | dump value |
|---|---|---|---|
| 0x0f | 0x92200714 | smac0 send total bytes | 0x00021931 (135,985) |
| 0x10 | 0x92200718 | smac0 send total frames | 0x0000054d (1,357) |
| 0x28 | 0x92200780 | smac0 recv total frames | 0x000005b4 (1,460) |
| 0x29 | **0x92200784** | **smac0 recv total bytes** | **0x000a58bb (678,587)** |
| 0x2a | 0x92200788 | smac0 recv good bytes | 0x000a58bb (678,587) |
| 0x23 | 0x92200764 | smac0 send good bytes | 0x00021931 |
| 0x24 | 0x92200768 | smac0 send good frames | 0x0000054d |

The "recv total bytes" / "recv total frames" pair are the wire-side ingress
counters (PHY → MAC) — they tick on every Ethernet frame the MAC successfully
clocks in off the wire, regardless of what happens downstream in NPP/PP/TM.
That makes them the *correct* RX visibility counter, which is what we need to
prove whether the wire side is alive at all.

---

## 2. Full decoded smacRegTable (entries 0x0f..0x3f — the stat range)

Entries 0x00..0x0d are *config* registers (RW, used by `smac_set_*`). The
stat range begins at 0x0f. Entry 0x0e is a zeroed hole.

| tbl  | off (dword) | byte off in MAC[N] | label (from `smac_get_stat` printk) |
|------|-------------|--------------------|--------------------------------------|
| 0x0f | 0x0801c5    | +0x714 | send total bytes |
| 0x10 | 0x0801c6    | +0x718 | send total frames |
| 0x11 | 0x0801c7    | +0x71c | send good broadcast |
| 0x12 | 0x0801c8    | +0x720 | send good multicast |
| 0x13 | 0x0801c9    | +0x724 | send 64-byte frames |
| 0x14 | 0x0801ca    | +0x728 | send 65-127 |
| 0x15 | 0x0801cb    | +0x72c | send 128-255 |
| 0x16 | 0x0801cc    | +0x730 | send 256-511 |
| 0x17 | 0x0801cd    | +0x734 | send 512-1023 |
| 0x18 | 0x0801ce    | +0x738 | send 1024-1518 |
| 0x19 | 0x0801cf    | +0x73c | send total unicast |
| 0x1a | 0x0801d0    | +0x740 | send total multicast |
| 0x1b | 0x0801d1    | +0x744 | send total broadcast |
| 0x1c | 0x080014    | +0x050 (bitfield) | send underflow err (sub-field of regs at +0x50) |
| 0x1d | 0x080014    | +0x050 (bitfield) | send single-collision |
| 0x1e | 0x080015    | +0x054 (bitfield) | send multi-collision |
| 0x20 | 0x080015    | +0x054 (bitfield) | send late-collision |
| 0x21 | 0x080015    | +0x054 (bitfield) | send excess-collision |
| 0x22 | 0x080016    | +0x058 (bitfield) | send carrier err |
| 0x23 | 0x0801d9    | +0x764 | send good bytes |
| 0x24 | 0x0801da    | +0x768 | send good frames |
| 0x25 | 0x0801db    | +0x76c | (unlabeled, contiguous) |
| 0x26 | 0x0801dc    | +0x770 | send pause frames |
| 0x27 | 0x080017    | +0x05c (bitfield) | send vlan frames |
| 0x28 | 0x0801e0    | +0x780 | **receive total frames** |
| 0x29 | 0x0801e1    | +0x784 | **receive total bytes** |
| 0x2a | 0x0801e2    | +0x788 | receive good bytes |
| 0x2b | 0x0801e3    | +0x78c | receive broadcast frames |
| 0x2c | 0x0801e4    | +0x790 | receive multicast frames |
| 0x2d | 0x0801e5    | +0x794 | receive CRC error frames |
| 0x2e | 0x080019    | +0x064 (bitfield) | receive align error |
| 0x32 | 0x0801ea    | +0x7a8 | receive oversize frames |
| 0x33 | 0x0801eb    | +0x7ac | receive 64-byte frames |
| 0x34 | 0x0801ec    | +0x7b0 | receive 65-127 |
| 0x35 | 0x0801ed    | +0x7b4 | receive 128-255 |
| 0x36 | 0x0801ee    | +0x7b8 | receive 256-511 |
| 0x37 | 0x0801ef    | +0x7bc | receive 512-1023 |
| 0x38 | 0x0801f0    | +0x7c0 | receive 1024-1518 |
| 0x39 | 0x0801f1    | +0x7c4 | receive good unicast |
| 0x3a | 0x08001c    | +0x070 (bitfield) | receive length error |
| 0x3b | 0x08001c    | +0x070 (bitfield) | (aliased — same off, different shift) |
| 0x3c | 0x0801f4    | +0x7d0 | receive pause frames |
| 0x3d | 0x0801f5    | +0x7d4 | receive overflow error |
| 0x3e | 0x08001d    | +0x074 (bitfield) | receive vlan frames |
| 0x3f | 0x0801f7    | +0x7dc | receive watchdog err |

(The big block at MAC[N]+0x714..+0x7dc is one cumulative-counter region.
The entries at +0x50..+0x74 are bitfield sub-counters living inside MAC
control regs.)

All entries with off in the +0x7xx band have `mask=0xffffffff`, `shift=0`,
`stride=0x10000` dwords — i.e. **plain 32-bit free-running counters at
MAC[N]+offset**.

Stock confirms (from the same dump) they are **read-to-clear OFF** — values
persisted across the multiple memdump iterations represented in the file. (TM
register `0x10058` is the *one* clear-on-read counter we found; SMAC stats are
not in that class.)

---

## 3. Mainline correction needed

`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` `zx_pipeline_stats_show`:

```c
/* current — WRONG label */
seq_printf(s, "  smac%d MAC[+710..71c] = %08x %08x %08x %08x   (RX/TX byte+pkt counters)\n",
           p, r710, r714, r718, r71c);
```

What `+0x710..0x71c` actually contains:

| offset | actually is | confidence |
|---|---|---|
| +0x710 | unused / table entry 0x0e is empty | high (zero in stock dump) |
| +0x714 | TX total bytes (entry 0x0f) | high (matches stock 0x21931 = 135,985 bytes for 1357 frames ≈ 100 B avg) |
| +0x718 | TX total frames (entry 0x10) | high |
| +0x71c | TX good broadcast (entry 0x11) | high |

So the mainline read has **zero RX visibility**. RX byte and RX packet
counters are at `+0x784` and `+0x780` respectively, both 32 bytes further
into the MAC block.

Minimum fix: extend the `pipeline_stats` per-port readout to include
`+0x780` (rx_pkts) and `+0x784` (rx_bytes), and relabel the existing
four as TX-only.

Recommended fix: expose the canonical "headline counters" stock prints from
`smac_get_stat` —

```
TX bytes  = MAC[N] + 0x714
TX pkts   = MAC[N] + 0x718
RX bytes  = MAC[N] + 0x784
RX pkts   = MAC[N] + 0x780
RX CRC err= MAC[N] + 0x794
RX overflow=MAC[N] + 0x7d4
```

— and call them "wire-side smac counters" so it is unambiguous which side
of the pipeline they cover (PHY↔MAC, before NPP/PP/TM).

---

## 4. Counters worth exposing in mainline `pipeline_stats`

Priority A — the four traffic-alive headlines per port:

| port | name | phys addr (port 2 = LAN3 shown) |
|---|---|---|
| N | `smac N tx_bytes` | `0x92200000 + N*0x40000 + 0x714` (LAN3: `0x92280714`) |
| N | `smac N tx_pkts`  | `0x92200000 + N*0x40000 + 0x718` (LAN3: `0x92280718`) |
| N | `smac N rx_pkts`  | `0x92200000 + N*0x40000 + 0x780` (LAN3: `0x92280780`) |
| N | `smac N rx_bytes` | `0x92200000 + N*0x40000 + 0x784` (LAN3: `0x92280784`) |

Priority B — error counters (any of these >0 tells you what's wrong):

| port | name | phys addr (port 2 shown) |
|---|---|---|
| N | `smac N rx_crc_err` | `... + 0x794` |
| N | `smac N rx_oversize` | `... + 0x7a8` |
| N | `smac N rx_overflow` | `... + 0x7d4` |
| N | `smac N rx_watchdog_err` | `... + 0x7dc` |
| N | `smac N rx_pause` | `... + 0x7d0` |

Priority C — distribution / discrimination counters (only useful for deeper
debugging, can be left as TODO):

| port | name | phys addr |
|---|---|---|
| N | `smac N rx_unicast` | `... + 0x7c4` |
| N | `smac N rx_broadcast` | `... + 0x78c` |
| N | `smac N rx_multicast` | `... + 0x790` |
| N | `smac N rx_64..1518` | `... + 0x7ac..+0x7c0` |
| N | `smac N tx_pause` | `... + 0x770` |
| N | `smac N tx_unicast` | `... + 0x73c` |

All free-running 32-bit. No special access mode needed (plain readl). They
sit inside the existing 2 MiB ETH MMIO window — no DT change required.

---

## Footnotes

- Validation in `tmOnuGlbRegValidation` rejects port >= entry.max_port. Every
  stat entry sets `max_port = 5`, so legal ports are 0..4 (= LAN1..LAN4, WAN).
- The `count` field at +0x18 is just an access counter that stock increments
  on every R/W of that entry; not exposed to userland. Useful as a
  "did userland ever poll this stat" indicator if we ever want to mirror
  stock's behavior, but irrelevant for the actual hardware counters.
- Entry 0x25 has no printk in `smac_get_stat` but sits between "send good
  frames" (+0x768) and "send pause" (+0x770); presumably a vendor-internal
  counter at +0x76c. Skip.
- Entries with `off` in the `0x80014..0x8001d` band are bitfield sub-counters
  packed into the per-port MAC control registers at +0x50..+0x74. They use
  non-32-bit shifts/masks — handle separately if exposed (low priority — the
  main counters above already give the visibility we need).
