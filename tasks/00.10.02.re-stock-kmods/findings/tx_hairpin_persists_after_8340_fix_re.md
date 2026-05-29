# TX hairpin persists after the PP[0x8340] fix — root cause RE

**Date**: 2026-05-28.
**Status**: ROOT CAUSE FOUND (high confidence). Live + static triangulated.
**Verdict**: Hypothesis (b) — the 0x8340 fix is LIVE and was NOT clobbered;
the flood/hairpin comes from a DIFFERENT register: the **PP_BRG per-port
isolation table (PP[0x83c0..0x83dc]) is written with off-by-one / wrong
values by `zx_chip_tm_init_isolate`, which runs LAST and clobbers the
correct stock values.** The CPU port (port 5) ends up NOT blocking its own
egress → CPU-TX frames hairpin back to the CPU port.

---

## 1. LIVE value of PP[0x8340] — the fix is LIVE, not clobbered

Read on the running device via the `mem` debugfs file. Note: the task brief
said PP-BRG (0x388340) is out of debugfs `mem` range, but that is wrong.
`zx_mem_read` reads `e->base + *ppos` over REGION 0x200000, and
`e->base` = NPP window phys **0x921c0000** (`/proc/iomem`: "92000000.ethernet npp"
= 0x921c0000-0x923bffff). So PP[0x8340] = phys 0x92388340 = `e->base + 0x1C8340`,
which is **inside** the 0x200000 range. (`devmem` is unusable: this kernel has
no `/dev/mem`; the REPL also rejects args containing `=`. `tail -c +N file`
works and seeks via lseek, so I read the `mem` file at byte 0x1C8340.)

```
PP[0x8340] = 0x015555ff   (LIVE, mainline, post-fix)
```

Stock LIVE (`regs/stock_eth_2mib.txt:466989-area`, addr 92388340) = `015555ff`.
**They match exactly. The fix is live and was NOT re-overwritten** by any
later init / replay step (CLA, trap_queue, pro_action, stock replays). The 3
sbrag regs that share dword 0x0e20d0 (= byte 0x388340) — regId 0x34/0x35/0x36
(`zx_reg_tables.h:202-204`, `zx-fpga-reg-tables.h:474-476`) — are the only
encodings of this register, and none of the replay tables
(`zx_stock_table.h`, `zx_cla_table.h`, `zx_pm_table.h`, `zx_npp_twin_data.h`,
`zx-pp-pro-actions.h`, `zx_pkt_map.h`) write byte 0x388340 / phys 0x92388340.
The only `0x8340` hit in `zx_stock_table.h` is an unrelated entry
(`{ -0xafffc, 0x61a7 }`, a negative relative offset, not this register).

=> **Hypothesis (a) is REFUTED. Hypothesis (b) confirmed.**

---

## 2. The actual flooding mechanism: PP_BRG isolation table is WRONG

### LIVE PP_BRG dump (mainline, this device) vs stock LIVE

| Reg (PP+) | Stock LIVE | Mainline LIVE | Match |
|---|---|---|---|
| 0x8340 unknown-ucast fwd | 015555ff | **015555ff** | ✓ (the fix) |
| 0x80a8/ac host MAC | 62e95900 / 0000c8a3 | 62e95900 / 0000c8a3 | ✓ learned |
| 0x80b0 FDB port field | 00000102 | **00000108** | ✗ (see §4) |
| 0x8004 | 040200ff | **020000ff** | ✗ (see §4) |
| **0x83c0 (port0 isol)** | **fe** | **fd** | ✗ |
| **0x83c4 (port1)** | **fd** | **fb** | ✗ |
| **0x83c8 (port2)** | **fb** | **f7** | ✗ |
| **0x83cc (port3)** | **f7** | **ef** | ✗ |
| **0x83d0 (port4)** | **ef** | **df** | ✗ |
| **0x83d4 (port5=CPU)** | **df** | **fe** | ✗ |
| **0x83d8 (port6)** | **ff** | **bf** | ✗ |
| **0x83dc (port7)** | **ff** | **7f** | ✗ |

Isolation semantics (per `zx_pp_init` comment, L1155-1158): each port's mask =
"ports this port MAY forward to"; a **0 bit = blocked**.

- Stock: every port p blocks ONLY bit p (its own self-loop). Ports 6,7 = 0xff
  (block nothing). The CPU port (5) = 0xdf = blocks bit 5 (itself).
- Mainline LIVE: every port p blocks bit **(p+1)** — off by one. The CPU port
  (5) = 0xfe = **blocks bit 0, does NOT block bit 5 (itself).** Ports 6 and 7
  block bits 6 and 7 instead of nothing.

**Because the CPU port (5) no longer blocks its own egress, a CPU-originated
TX frame entering the switch on the CPU port is allowed to egress back out the
CPU port → it returns to the CPU as RX and is counted as a loopback drop
(`zx_sw_xmit` SMAC == own MAC, detected at zx-eth-main.c:2723-2729).** This is
the hairpin. It is independent of the 0x8340 flood bitmap, which is why fixing
0x8340 changed nothing.

### Who writes the wrong values, and why (the FINAL writer)

Four writers touch PP[0x83c0..]; init order (verified by call sites):

1. probe L4405 `zx_pp_init` — direct `writel` 0xFE/0xFD/0xFB/0xF7 to ports 0-3
   ONLY (L1160-1163). Correct, but partial.
2. probe L4424 `zx_eth_init_vlan_and_isolation` — `zx_port_isolate(i, ~(1<<i))`
   (OR-accumulate) for 0-5, then 0xFF on 6/7 (L4223-4226). Also correct.
3. L4054 `zx_pp_brg_init` (inside tm_subsystem, probe L4449) — OR 0xdf into
   ports 6/7 (L2414).
4. **L4082 `zx_eth_init_chip_tm` -> `zx_chip_tm_init_isolate` (L2161-2171) —
   the LAST writer. It REPLACES the low byte of all 8 ports via
   `zx_tm_port_isolate_set(p, 0xffffff00u | (1u<<p))` (L2166).**

`zx_tm_port_isolate_set` (L2100-2108) computes:
```
inv = ~mask = 0xff & ~(1<<p)        // for the L2166 arg
hw  = ((inv>>5)&1) | ((inv<<1)&0x3e) | (inv&0xc0)   // rotate-left-by-1 of low 6 bits
```
This rotate-by-1 reshape shifts every blocked bit by +1. It writes sbragRegTable
reg_id 57 = base_off 0x0e20f0 (dword) = byte 0x3883c0, stride 1 dword
(`zx-fpga-reg-tables.h:479`), i.e. PP[0x83c0 + p*4]. The write is a
read-modify-write replacing the low byte (mask 0xff, `zx_fpga_table_write`,
zx-fpga-reg-tables.h:781). I computed `hw` for p=0..7 = **fd, fb, f7, ef, df,
fe, bf, 7f** — which is **byte-for-byte identical to the mainline LIVE
readback above.** This proves `zx_chip_tm_init_isolate` is the clobbering
final writer.

The bug is twofold: (a) it passes the wrong `mask` arg — stock's
`tm_port_isolate_set` is called with `mask = (1<<port)` (block only self), not
`0xffffff00|(1<<port)`; and (b) running last, it overwrites the correct values
that steps 1-3 had already set.

---

## 3. Recommended next code change (concrete)

**Primary fix — make `zx_chip_tm_init_isolate` write the exact stock isolation
bytes (simplest, robust).** File `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`,
function `zx_chip_tm_init_isolate` (L2161-2172). Replace the loop body so it
produces the stock per-port values fe,fd,fb,f7,ef,df,ff,ff. Two equivalent
options:

Option A — direct writes (clearest):
```c
static void zx_chip_tm_init_isolate(struct zx_eth *e)
{
    void __iomem *pp = e->base + PP_OFF;
    static const u8 iso[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xff,0xff};
    int p;
    for (p = 0; p < 8; p++)
        writel(iso[p], pp + PP_BRG_BASE + 0x03C0 + p * 4);
}
```

Option B — keep the table path, pass the mask that yields stock values. Per the
reshape solved-inverse, the correct arg per port is `mask` whose low byte =
{0x20,0x01,0x02,0x04,0x08,0x10,0x00,0x00} for p=0..7 (i.e. the bit the port
must block, pre-reshape). Simplest single-expression form that reproduces
stock for all 8 ports:
```c
/* stock tm_port_isolate_set(p, 1<<p) for 0..5; 0 (block none) for 6,7 */
u32 mask = (p < 6) ? (0xffffff00u | (1u << p)) : 0xffffff00u; // see note
```
(Note: Option A is recommended — the reshape in `zx_tm_port_isolate_set`
introduces the off-by-one and is error-prone; bypass it for this table.)

**Expected result:** PP[0x83d4] (CPU port 5) returns to 0xdf, blocking its own
egress; CPU-TX frames can no longer hairpin back to the CPU port.
`tm_rx_loopback_drops` should stop tracking `tm_tx_count`, and frames should
egress to the physical LAN port (the host MAC is already learned in FDB-A, so
unicast ARP replies route to PHY[2]/LAN3).

---

## 4. Secondary divergences (lower priority; fix after primary)

These were also observed live but are NOT the hairpin cause:

- **PP[0x8004] = 0x020000ff (mainline) vs 0x040200ff (stock LIVE).** Mainline
  is missing MAC-age-enable (bit 17) and bit 26. `zx_pp_init` L1091 writes
  0x040200FF, but a later step leaves 0x020000ff live (age bit cleared).
  Per `fdb_learning_enable_re.md` Q3 this can gate FDB commit-on-learn. Host
  MAC IS currently learned, so it is not blocking us today, but it is a real
  delta. Recommend a read-modify-write `pp[0x8004] |= 0x04020000` after init.
- **PP[0x80b0] = 0x108 (mainline) vs 0x102 (stock).** This is the learned-host
  FDB slot's egress field. Low byte 0x08 (bit 3) vs stock 0x02 (bit 1) — a
  different egress-port encoding for the learned host. Likely a downstream
  effect of the isolation/port-id mismatch; re-check after the primary fix.

---

## 5. Confidence

- **PP[0x8340] live = 0x015555ff (fix not clobbered):** HIGH. Direct live
  read; matches stock; no table writes that address.
- **Isolation table off-by-one is the hairpin:** HIGH. Live readback is
  byte-for-byte the computed output of `zx_chip_tm_init_isolate`; that fn is
  the last writer; the CPU port (5) live value 0xfe fails to block its own
  egress (bit 5), which is exactly the loopback the driver detects at L2723.
- **Recommended fix:** HIGH that it restores stock isolation; MEDIUM that it
  alone fully clears the hairpin (the 0x8004 age bit and 0x80b0 port-id deltas
  may need follow-up, but neither blocks egress the way the isolation does).

---

## 6. How to reproduce the live reads (read-only)

REPL at localhost:9999, one busybox applet per line, no `=` in args, no pipes.
```python
# read PP[0x8340] = e->base+0x1C8340  (byte offset; tail -c +N is 1-indexed)
s.sendall(b"tail -c +1868609 /sys/kernel/debug/zx_eth/mem\r")
# first 4 bytes (LE) = PP[0x8340]; first 0x400 bytes cover 0x8340..0x873f.
# For the whole PP_BRG block, read from 0x1C7F00 (N=1862913) and self-align
# on the known signature ff 55 55 01 at the 0x8340 slot.
```
`cat /sys/kernel/debug/zx_eth/stats` works (exit 0) and dumps counters +
curated regs, but does NOT include the 0x83c0/0x8340 BRG block — use the `mem`
file for those.
