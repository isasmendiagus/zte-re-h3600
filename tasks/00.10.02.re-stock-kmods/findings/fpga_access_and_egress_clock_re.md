# FPGA reg access mechanism + egress clock/power-gate RE (2026-05-28)

Static/decomp-only investigation of (1) the `fpga_write_reg`/`fpga_read_reg`
mechanism, (2) the exact clock/reset gate that makes the egress block
(0x9238c000 / ETH_TM2 0x923a0000) writable, and (3) whether that gate also
governs the SOPC fabric egress.

Sources cited inline:
- Stock kmod decomp: `decomp_all_zx_ponreg.c`, `decomp_all_tm.c`, `decomp_all_switch.c`
- U-Boot decomp: `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_*.c`
- Stock plat static analysis: `static_analysis_plat_zxylzb_init.md`
- Mainline driver: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`,
  `zx-fpga-reg-tables.h`

---

## 1. fpga_write_reg / fpga_read_reg — DIRECT, no indirect window

**Canonical definition** (`decomp_all_zx_ponreg.c:1-17`):

```c
undefined4 fpga_read_reg(int id)        { return *(u32 *)(pon + id*4); }
void       fpga_write_reg(int id, u32 v){ *(u32 *)(pon + id*4) = v; }
```

`pon` is the ioremap of the FPGA/PON base (virt `0xf4000000` in the chrdev module;
phys **0x92000000** per the platform iomap and the architecture map). Both
accessors are **plain 32-bit word load/store**. There is:
- **NO** command register, **NO** data register, **NO** DONE/busy poll bit.
- **NO** difference between read and write paths.
- **NO** sub-range with an indirect window. (The only "indirect" accessors in the
  decomp are `cla_set_indirect_rw_cmd/_data/_status` @ `decomp_all_tm.c:298-428`,
  which are the **CLA classifier table** RAM protocol — TM[0x14014]/[0x18]/[0x1c]
  style — *unrelated* to the egress block. Likewise the DSCH shaper RAM is its own
  TM[0x14014] indirect protocol. Neither touches 0x9238c/0x923a0.)

So the earlier note is **confirmed**: `fpga_read_reg(id) == readl(0x92000000 + id*4)`
and `fpga_write_reg(id,v) == writel(v, 0x92000000 + id*4)`. Reg-id is a **word index**
(× 4), not a byte offset.

**Register-id ↔ phys examples** (id*4 + 0x92000000):
| reg-id | phys | block |
|---|---|---|
| 0xe8007 | 0x923a001c | ETH_TM2 (egress mux region 0x923a0000) |
| 0xe8131..e813b | 0x923a04c4.. | ETH_TM2 |
| 0xe218c | 0x92388630 | PP_BRG (0x92388000) |
| 0xe2300 | 0x92388c00 | PP_BRG |
| 0x76401 / 0x7640e / 0x76800 | 0x921d9004 / 0x921d9038 / 0x921da000 | **SOPC** (NPP 0x921d9000) |

**`tmOnuRegWrite(idx, val, sub, table)`** (`decomp_all_tm.c:35356`) is just a
read-modify-write field helper *on top of* `fpga_read_reg`/`fpga_write_reg`:
```c
reg_id = table[idx].base_off + sub*table[idx].stride;   // word index
rmw:   v = fpga_read_reg(reg_id);
       fpga_write_reg(reg_id, (v & ~(mask<<shift)) | ((val&mask)<<shift));
```
fields: +0x08 base_off(word id), +0x0c mask, +0x10 shift, +0x14 stride. Mainline
already mirrors this in `zx-fpga-reg-tables.h` + the `zx_fpga_*` helpers. **Still a
plain writel underneath.** ⇒ A debugfs `poke <phys> <val>` to 0x923a00e0 is the
exact same bus transaction the firmware uses. The write being ignored is therefore
a **clock/reset-gate** problem, not an access-mechanism problem.

### Verdict for Q1
**DIRECT writel. There is no FPGA indirect-access path for this block.** The
hypothesis "egress regs go through fpga_write_reg indirect window" is FALSE — but
"fpga_write_reg" itself is real and is just `writel(0x92000000 + id*4)`.

---

## 2. The clock/power gate that makes 0x9238c000 / 0x923a0000 writable

The egress block lives in the **PON subsystem** clock+reset domain controlled by
**TOPCRM @ 0x94000000** (+ SYSCTRL @ 0x94100000, pin_mux @ 0x94200000). The block
will silently drop writes (reads back 0) while its domain is held in reset / its
gate is closed. Two bring-up actors program this domain:

### 2a. U-Boot bring-up (the proven-working order)

Top-level eth init `FUN_40e21050` runs, **in order**:
```
FUN_40e40454()      # (pre)
FUN_40e50998()      # alloc/register eth dev struct + board MAC 0x47f4af88
FUN_40e4fc7c(0)     # <<< THE CLOCK + RESET GATE (see below)
FUN_40e40844()
```

**`FUN_40e4fc7c` (the gate — `uboot_eth_decomp/FUN_40e4fc7c.c`):**
```c
FUN_40e4fa08(0);                               // TOPCRM PLL/clock-enable (see 2b)
_DAT_94000008 &= 0xffffffcf;                    // TOPCRM[0x08] &= ~0x30  (ASSERT reset: clr bits 4,5)
udelay(100);                                    // FUN_40e45a90(100)
_DAT_94000008 |= 0x20;                           // TOPCRM[0x08] |= 0x20   (deassert bit5)
udelay(100);
FUN_40e4fa9c();                                  // (serdes/aux)
_DAT_94000008 |= 0x10;                            // TOPCRM[0x08] |= 0x10   (deassert bit4)
// then SYSCTRL[0x10] RGMII cfg:
*(SYSCTRL+0x10) &= 0xfffff7ff;                    // clear bit11
*(SYSCTRL+0x10) = (..&0xfffffc3f) | (mdio[9a107000+8]>>... <<6);
```

**`FUN_40e4fa08` (TOPCRM PLL/clock — `FUN_40e4fa08.c`, base 0x94000050):**
```c
_DAT_94000050 &= 0x7fffffff;                      // clear PLL MSB before reconfig
// mode-dependent PLL program of TOPCRM[0x50]:
FUN_40e4f580(0x94000050,1,0x32,4,2)   (integer)   // or
FUN_40e4f700(0x94000050,1,0x5d,0x4fdf3b,5,3) (frac)
```
`FUN_40e4f580/700` set MSB (0x80000000) + 0x08000000, clear, program the divider
fields, `udelay(100)`, then clear MSB (release PLL). This is the reference-clock
PLL for the PON subsystem.

**Then, later in init**, the *block-internal* enables run via `FUN_40e4fda4`
(`FUN_40e4fda4.c`, reached from `FUN_40e50440 → FUN_40e4fe04`):
```
FUN_40e50384()      # TM/SCH/DSCH/BMU/DMA
FUN_40e50b0c():     #  -> FUN_40e50b34: *0x92380000 = 2 ; udelay(1000)   (PP master enable)
                    #  -> FUN_40e50a9c: PP_BRG @0x92388000 (already in mainline)
                    #  -> FUN_40e50a60: *(0x9238c000+0x80)=0x309a; +0x88=0; +0xcc=1
                    #  -> *(0x923a0000+0x10)=0; +0x14=0    (ETH_TM2 clear)
FUN_40e50f20()      # SCH/RED/QMG[0]=0x11
*(0x923a0000+0xe0) = 0x11    # THE DIRECT EGRESS MUX
```

**So the full writability prerequisite is: TOPCRM PLL up (0x94000050) →
TOPCRM[0x08] reset assert→deassert EDGE (`&~0x30; |0x20; |0x10` with 100us
delays) → THEN `*0x92380000=2` PP master (+1ms) → THEN 0x9238c000 / 0x923a0000
accept writes.**

### 2b. Stock kmod / plat bring-up — same sequence

`static_analysis_plat_zxylzb_init.md` [fn-03] `zx_pon_clk_reset_init` and [fn-09]
`zx_pon_clk_reset` do the identical thing:
```
TOPCRM[0x08] &= ~0x20 ; &= ~0x10 ; delay ; |= 0x20 ; delay ; |= 0x10   # reset edge
... serdes band cal, sys_ctrl[0x10] &= ~0x800 ...
TOPCRM[0x0c] |= 0x1e0    # enable PON clock bits 5..8
TOPCRM[0x50] PLL (ref_clk_set) = pll_cfg_integer/fractional, identical args to U-Boot
```

### 2c. WHY hand-poke of `0x92380000=2 + 0x9238c000 writes` did NOT stick

The poke recipe in `uboot_direct_egress_plan.md §5` started at `*0x92380000=2`
and the 0x9238c000 writes — it **skipped the TOPCRM[0x08] reset EDGE and the PLL**.
The mainline driver's `zx_eth_init_topcrm` (zx-eth-main.c:4584-4617) **also skips
the edge**: it does
```c
writel(readl(topcrm+0x0c) | 0x1e0, topcrm+0x0c);   // clock bits — OK, matches stock
writel(0x0003cfff, topcrm+0x4c);
writel(0x1ff7ffff, topcrm+0x08);                    // <<< single OR-style slam
```
`0x1ff7ffff & 0x30 == 0x30` → bits 4 AND 5 are left **set**, with **no falling
edge** and **no PLL (0x50) program**. If a prior boot stage already left bits 4/5
set, this write changes nothing about the reset state — the egress sub-block stays
in whatever reset/clock state it powered up in, and `writel(0x923a00e0)` is dropped.

**The missing piece is the reset-deassert EDGE on TOPCRM[0x08] (assert 0→
deassert), with the PON PLL (TOPCRM[0x50]) programmed first** — not the PP master
write, not the 0x9238c000 writes, and not any indirect path.

### Exact gate sequence to make the block writable (regs / values / order / delays)

All on TOPCRM phys 0x94000000 unless noted. Order is mandatory.
```
1. TOPCRM[0x50] &= 0x7fffffff                       # PLL: clear MSB
   (program PLL via the FUN_40e4f580 integer or FUN_40e4f700 fractional field set;
    minimal warm-boot replay: leave [0x50] as-is if PLL already locked — but the
    reset edge below is non-optional)
2. TOPCRM[0x0c] |= 0x1e0                             # PON clock bits 5..8 (mainline already does)
3. TOPCRM[0x08] &= ~0x30                             # ASSERT reset (clear bits 4 AND 5)
4. udelay(100)
5. TOPCRM[0x08] |= 0x20                              # deassert bit5
6. udelay(100)
7. TOPCRM[0x08] |= 0x10                              # deassert bit4
8. SYSCTRL[0x10] &= ~0x800   (phys 0x94100010)       # clear bit11 (RGMII)
9. writel(2, 0x92380000) ; udelay(1000)             # PP master enable
10. writel(0x309a, 0x9238c080); writel(0, 0x9238c088); writel(1, 0x9238c0cc)
11. writel(0, 0x923a0010); writel(0, 0x923a0014)    # ETH_TM2 clear  ← now latches
12. (MAC slot table, QMG[0]=0x11, then writel(0x11, 0x923a00e0))
```

Mainline must **replace** the single `writel(0x1ff7ffff, topcrm+0x08)` in
`zx_eth_init_topcrm` with steps 3-7 (and add step 1 PLL + step 8 SYSCTRL), THEN
do the PP/ETH_TM2 writes (steps 9-12) in a new `zx_eth_tm2_init`.

---

## 3. Is it poke-testable? Yes — corrected sequence

The earlier poke plan failed because it omitted the reset edge. Corrected live
test (debugfs `poke <phys> <val>`, device-side; do NOT need the PLL reprogram on a
warm boot but the EDGE is required):

```
# --- reset edge (the part that was missing) ---
poke 0x9400000c <cur | 0x1e0>     # ensure PON clock bits (or skip if already 0x..1e0)
poke 0x94000008 <cur & ~0x30>     # assert reset (clear bits 4,5)   <-- KEY
# (no sub-100us sleep tool; issue next pokes back-to-back, the bus delay suffices,
#  but prefer a >=100us gap if the poke tool supports it)
poke 0x94000008 <prev | 0x20>     # deassert bit5
poke 0x94000008 <prev | 0x30>     # deassert bit4 (now 0x..30 set)
poke 0x94100010 <cur & ~0x800>    # SYSCTRL RGMII bit11
# --- now the block should be alive ---
poke 0x92380000 2                 # PP master
poke 0x9238c080 0x309a ; poke 0x9238c088 0 ; poke 0x9238c0cc 1
poke 0x923a0010 0 ; poke 0x923a0014 0
# verify writability BEFORE the mux:
poke 0x923a00e0 0x11 ; mem 0x923a00e0     # expect 0x11 read-back (was 0)
```
**Pass criterion:** `mem 0x923a00e0` now reads back `0x11` (previously 0). If it
reads back non-zero, the reset edge fixed writability and the direct-mux egress
recipe (slot table + QMG[0]=0x11 + TX desc format) can be validated next. If it
*still* reads 0, the PLL (TOPCRM[0x50]) program is also required — add step 1.

---

## 4. Does this unify the direct-mux AND the SOPC fabric egress?

**Partially — same clock DOMAIN, different sub-blocks.**
- ETH_TM2 mux (0x923a0000) and the PP clk/en sub-block (0x9238c000) and PP master
  (0x92380000) are all in the **PON subsystem** gated by TOPCRM[0x08]/[0x0c].
- SOPC (`sopcRegTable` base_off 0x76401/0x7640e/0x76800 → phys **0x921d9004 /
  0x921d9038 / 0x921da000**) is in the **NPP window 0x921d9000**, a *different*
  sub-block but in the **same PON TOPCRM clock domain**.

Implication: the **reset-edge gate is a necessary precondition for the whole PON
egress datapath**, so fixing it is a prerequisite for BOTH paths. But it is **not
by itself sufficient** for the fabric/SOPC path: SOPC `send2smacN` is reachable via
plain readl/writel today (we read its counters fine), so SOPC's silence is a
*configuration/forwarding* issue (egress-port pick / crossbar enable), not a
clock-gate. The clock-edge fix is the **unifying enabler** (it makes the 0x9238c/
0x923a0 mux writable so the U-Boot direct-mux path becomes available); the fabric
path needs the additional SOPC egress-port programming on top. **Recommended:
land the reset-edge fix first (it is the single highest-value change and is
required either way), then pursue the direct-mux egress as the proven path.**

---

## Summary
- **Q1: DIRECT writel.** `fpga_write_reg(id,v)=writel(v,0x92000000+id*4)`; no
  indirect window, no CMD/DATA/DONE, reads==writes. `tmOnuRegWrite` is just a
  field RMW on top.
- **Q2: It's a clock/reset gate, not an FPGA path.** The egress block is held
  until TOPCRM[0x08] gets a reset assert→deassert **EDGE** (`&~0x30; |0x20; |0x10`,
  100us gaps) with the TOPCRM[0x50] PLL up. Mainline + the prior poke both skipped
  the edge (mainline slams 0x1ff7ffff once → no edge), so 0x9238c/0x923a0 ignore
  writes.
- **Q3: Same TOPCRM clock domain** for ETH_TM2 mux and SOPC, so the edge-fix is a
  shared prerequisite, but SOPC's separate failure is forwarding-config, not clock.
- **#1 missing piece:** the **TOPCRM[0x08] reset-deassert edge** (with PON PLL),
  before the PP-master/0x9238c000/0x923a0000 writes.
