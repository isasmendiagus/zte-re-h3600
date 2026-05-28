# HW write-lock pattern RE — MAC/PP/NPP register write rejections

**Source**: deep static RE of `decomp_all_plat_zxylzb_9128S.c`,
`decomp_all_tm.c`, U-Boot `FUN_40e50c40.c` / `FUN_40e50f20.c` /
`FUN_40e4fdcc.c`, cross-checked against the live stock register dump
`regs/stock_eth_2mib.txt`.

**Date**: 2026-05-28.

---

## 1. Summary

There is **no software unlock register**. The "writes silently rejected"
symptom reported for `MAC[N][0xE0]`, `MAC[N][0x70]`, `MAC[N][0xB4]`,
`MAC[N][0xC20]`, `MAC[N][0xC50]`, `MAC[N][0xB00]`, `PP[0x2c] bit 29`,
and `NPP[+0x40] |= 0x300` is **present identically on stock**. The live
stock register dump from the working device shows the same "writes
don't stick" behavior:

| Register | Stock code does | Stock device reads | Mainline reads |
|---|---|---|---|
| MAC[0][0xE0] | writes 0x00011200 (smac_init) | **0x00000000** | 0x00000000 |
| MAC[0][0x70] | (no write) | 0x00000000 | 0x00000000 |
| MAC[0][0xB4] | (no write) | 0x00000000 | 0x00000000 |
| MAC[0][0xB00] | (no write) | 0x00002000 (HW default) | 0x00002000 |
| MAC[0][0xC20] | (no write) | 0x00000000 | 0x00000000 |
| MAC[0][0xC50] | (no write) | 0x00000000 | 0x00000000 |
| MAC[0][0x00] | writes 0xBAE003 | 0x00BA6003 (bit 13 dropped — gigabit-mode-flag) | similar |
| MAC[0][0x04] | writes 0xFFFF | 0x00003FFF (some bits cleared) | similar |
| NPP[+0x08] | writes 0xFFFFFF (24 bits) | 0x00000000 | 0 (mainline writes 0) |
| NPP[+0x0C] | writes 0xFFFFF (20 bits) | 0x0003FFFF (18 bits) | 0x3FFFF (mainline writes) |
| NPP[+0x40] | `\|= 0x300` (after smac_init) | 0x00000000 (bits NOT set) | 0x00000000 |
| NPP[+0x48] | writes 0 | 0x00000000 | 0x00000000 |
| PP[0x2c] | `\|= BIT(lan_up_port+25) = BIT(29)` | 0x00000106 (bit 29 NOT set) | 0x00000106 |
| NPP[+0x18000] | `\|= 8` | 0x00000124 | 0x00000124 |

The MAC config registers (0x70/0xB4/0xC20/0xC50) are **never written
by stock kernel** — only U-Boot writes them. U-Boot's writes also
don't persist past kernel `pon_reset(0xffffffff)`. The runtime stock
state shows these registers at HW default, and stock TFTP/PING/Internet
work fine in that state.

**Conclusion**: the "silent rejection" is real but **expected and benign**.
These registers are W1C, write-then-snapshot, or fed into HW logic
without being stored in an addressable readback. **They are not the
cause of mainline's TX wedge.** The TX failure is elsewhere (see Section 4).

---

## 2. Stock per-register write semantics (per RE)

The decompiled stock code writes these registers with these semantics:

### 2.1 MAC[N][0xE0] — write-once register
- Stock `smac_init` (plat-zxylzb_9128S decomp 2272): writes literal
  0x00011200 immediately after pon_reset(0xffffffff) and the NPP+8/+0xC
  unlock sequence.
- Live stock device shows MAC[0][0xE0] = 0 after boot. The write hit
  the HW but the value didn't persist as a readable register — it was
  consumed (probably as a "PHY callback config" command, latched into
  MAC microcontroller state).
- Ghidra emits `&PTR_caseD_47_00011200` which looks like a pointer; it
  is in fact the literal 0x00011200, confirmed by U-Boot's identical
  write at FUN_40e50c40 line 64.

### 2.2 MAC[N][0x70], [0xB4], [0xC20], [0xC50], [0xB00] — U-Boot-only writes
- Stock kernel **never writes these**. Search in
  `decomp_all_plat_zxylzb_9128S.c` for `mac_off + 0x70` / `+ 0xb4` /
  `+ 0xc20` / `+ 0xc50` / `+ 0xb00` returns 0 hits.
- Only U-Boot's `FUN_40e50c40` writes them, with values
  0x00300002 / 0x00004000 / 0x32 / 0xa8 / 0x0010FF11.
- U-Boot's writes are wiped by stock's later `pon_reset(0xffffffff)`,
  so the stock kernel runtime state shows them at HW default
  (0 except 0xB00 = 0x2000).
- Mainline's Iter 21 added these writes (lines 1230-1235) because they
  came from U-Boot RE, on the assumption they were needed. **They are
  not — stock works without them and they don't stick in mainline
  either.** Removing them changes nothing in stock-vs-mainline parity.

### 2.3 PP[0x2c] BIT(29) — locked or not implemented
- Stock writes `pp_base[0x2c] |= 1 << (lan_up_port + 25)` ONLY in the
  `lan_up != 0` branch at `init_module` line 8938, AFTER both
  `tm_pon_pp_init()` and `tm_pon_npp_init()` complete.
- For `lan_up_port = 4`, the bit is BIT(29).
- Stock device runtime shows PP[0x2c] = 0x00000106 — bit 29 NOT set.
- Either: HW silently masks that bit, or `lan_up_port` is something
  different at runtime, or that branch wasn't actually taken. Either
  way: **the working stock device runs with bit 29 cleared**, so
  mainline doesn't need it either.
- Cross-ref `iter15_npp_gap_phantom_2026-05-27.md`.

### 2.4 NPP[+0x40] BITS 8+9 — locked or not implemented
- Stock writes `npp_base[0x40] |= 0x300` at `tm_pon_npp_init` line 2253.
- Stock device runtime: 0x00000000. Bits NOT set.
- Same pattern as PP[0x2c] BIT(29). Mainline matches stock runtime by
  not setting (or by being blocked).

### 2.5 NPP[+0x08] and NPP[+0x0C] — block reset/clock gate (clear-on-readback)
- Stock writes 0xFFFFFF to NPP+8 and 0xFFFFF to NPP+0xC at the START
  of `tm_pon_npp_init`, followed by `msleep(1)`.
- U-Boot writes 0xFFFFFFFF to both at `FUN_40e50f20`, followed by
  `mdelay(1)` after each.
- Runtime readback: NPP+8 = 0, NPP+0xC = 0x3FFFF.
- These are **write-1-to-toggle-and-clear** style reset/clock-gate
  registers. The WRITE is what matters; the readback shows post-pulse
  state, not the written value.
- **Mainline currently writes `0` to NPP+8 and `0x3FFFF` to NPP+0xC**
  (matching the readback, NOT the stock write). The current mainline
  comment "stock = 0, not 0xFFFFFF" is **misleading** — it confuses
  observed readback with intended write. Stock and U-Boot both write
  ones to set every clock/reset bit, then HW snaps them back.

### 2.6 pon_base[0x40018], pon_base[0x4001c], pon_base[0x40044]
- Stock at `init_module` line 8925-8930:
  ```
  pon_base + 0x40018 = 2          (purpose unknown)
  pon_base + 0x4001c = 0xf        (purpose unknown)
  pon_base + 0x40044 = 0xffffff7f (interrupt mask: unmask bit 7)
  ```
- Mainline writes `pon_base + 0x4001c = 0xf` ([A05]) but **does NOT
  write `pon_base + 0x40018 = 2` or `pon_base + 0x40044 = 0xffffff7f`**.
- The 0x40018 write happens BEFORE TOPCRM/SERDES bring-up. If it is a
  block-enable for the eth subsystem, missing it could leave eth in a
  half-enabled state where SOME registers accept writes and others don't.
- This is the **single most plausible mainline-stock state divergence**
  for an unknown HW-side gate.

---

## 3. Per-target unlock sequences (as practiced by stock/U-Boot)

### MAC[N] writes — at INITIAL boot
Stock relies on the global `pon_reset(0xffffffff)` at start of
init_module to put all 5 MAC blocks in a known clean state. After this:

```
pon_reset(0xffffffff)               // pon_base+8 cleared then set
msleep(10)
pon_base + 0x40018 = 2              // ⚠️ MAINLINE MISSING
zx_pon_clk_reset_init(1)            // TOPCRM + SERDES
register_pon_int()
pon_base + 0x40044 = 0xffffff7f     // ⚠️ MAINLINE MISSING
pon_base + 0x4001c = 0xf
msleep(1)
// ... TM init + PP init ...
tm_pon_npp_init() {
    npp_base + 0x08 = 0xFFFFFF      // ⚠️ MAINLINE WRITES 0 INSTEAD
    npp_base + 0x0C = 0xFFFFF       // ⚠️ MAINLINE WRITES 0x3FFFF INSTEAD
    msleep(1)
    ... sub-inits ...
    npp_base + 0x04 = 0xFFFFFFFF
    npp_base + 0x48 = 0
    pon_npp_smac_init() {
        for N in 0..3:
            zx_mdio_write(phy[N], 0x10, 0x8001) + zx_mdio_write(phy[N], 0x11, 0)
            smac_init(N)            // writes MAC[N][0]/[4]/[8]/[E0]/[D00]/[D30]
            npp_base + (N+1)*0x40000 |= 2  // enable MAC at NPP level
    }
}
```

### MAC[N] writes — at LINK STATE TRANSITION (re-init path)
Stock `switch_phy_int_check.part.5` re-resets the per-MAC region
before re-running smac_init:

```
pon_reset(1 << (N + 6))             // pulse just THIS MAC's reset bit
smac_init(N)                        // 5 writes
pon_npp_smac_config_speed_duplex_part_0(N, speed, duplex)
smac_sopc_mode_switch(N, duplex)
pon_npp_smac_enable_part_3(N)       // MAC[N][0] |= 3
```

**Mainline does NOT do this per-port reset pulse on link-up.** This is
a real miss for link state transitions, but it isn't relevant for the
initial init failure because the global `pon_reset(0xffffffff)`
already cleared every per-MAC reset bit.

### PP[0x2c] write
- Stock does it as a single `|=` AFTER both pp_init and npp_init.
- Bit 29 doesn't end up set on the live stock device.
- **No unlock exists**: even stock can't (or doesn't) set this bit.
- Mainline already removed/ignored this — matches stock parity.

### NPP[+0x40] write
- Same pattern as PP[0x2c]. Stock writes `|= 0x300` but live readback
  is 0. Mainline doesn't bother and that's the correct behavior.

### Indirect-write protocols
Yes, stock uses CMD/STATUS/DATA triplets but only for **specific RAMs**,
not for the MAC/PP/NPP config registers under discussion:

| RAM target | Triplet | Where used |
|---|---|---|
| TM RED queue cfg | `tm + 0x4014/4018/4020-4028` | `red_set_queue_cfg` |
| TM RX desc release | `tm + 0x4064/4068` | `soft_release_rx_desc` |
| PP SADM | `pp + 0x4014/4018/4020-4028` | `sadm_ram_set/get` |
| PP CLA RAM | `pp + 0xc014/c018/c020-c028` | `cla_ram_set/get` |
| TM USCH | `tm + 0x14014/14018/1401c` | `usch_ram_set` |

None of these are used for the registers under discussion (MAC config
regs at `mac_base + 0x70`, `+ 0xB4`, etc.). So no indirect-write
protocol applies to the "stuck" MAC writes.

---

## 4. Init-order constraint (must MAC writes happen before TM enable?)

**No.** Stock does MAC writes LAST:

```
init_module:
  pon_reset(0xffffffff)
  ... pon-block writes ...
  tm_pon_tm_init()    ← TM block (BMU + RED + DMA + IRQ)
  tm_pon_pp_init()    ← PP block (bridge + classifier)
  tm_pon_npp_init()   ← NPP block (includes per-MAC smac_init)
  if lan_up: PP[0x2c] |= BIT(lan_up_port + 25)
```

The MAC writes inside `smac_init` happen AFTER all TM/PP setup is
complete. So the hypothesis "the lock activates after tm_pon_tm_init,
mainline needs MAC writes before TM init" is **false**.

Stock's order is:
1. pon_reset
2. TM
3. PP
4. NPP+MAC

Mainline's order (from probe path):
1. zx_eth_init_topcrm
2. zx_pp_init (apply_stock — replays stock_table.h, includes MAC writes)
3. zx_npp_init (NPP global + per-MAC smac_init_port)
4. zx_eth_init_pon_chip (pon_reset + 0x4001c)
5. zx_eth_apply_stock_init
6. zx_eth_init_tm_subsystem (TM ring + IRQ)

**Mainline's pon_reset comes AFTER many writes (zx_pp_init,
zx_npp_init, including per-MAC smac_init_port). Stock's pon_reset
comes FIRST.** This **is** an order-of-operations divergence, but
since stock's flow also wipes all per-MAC writes with pon_reset and
then re-applies them via tm_pon_npp_init→smac_init, the net effect at
the END of init is the same: pon_reset has happened, then all per-MAC
writes are applied. So this order divergence doesn't explain a lock.

---

## 5. Code patch suggestions (priority-ranked)

### P1 — Match stock's NPP+8/+0xC write VALUES (highest confidence)
The current mainline code:
```c
npp_write(e, NPP_REG_IRQ_ENABLE, 0x000000);  /* "stock = 0, not 0xFFFFFF" */
npp_write(e, NPP_REG_IRQ_MASK,   0x03FFFF);  /* "stock = 0x3FFFF" */
```

Stock and U-Boot BOTH write **maximum 1-bits** to these registers, then
HW resets the bits. Change to:
```c
npp_write(e, NPP_REG_IRQ_ENABLE, 0xFFFFFF);  /* stock writes this; HW snaps to 0 */
npp_write(e, NPP_REG_IRQ_MASK,   0xFFFFF);   /* stock writes this; HW snaps to 0x3FFFF */
usleep_range(1000, 2000);
```

Rename the macros to `NPP_REG_BLOCK_RESET` and `NPP_REG_CLOCK_GATE`.
The mnemonic "IRQ_ENABLE/IRQ_MASK" is wrong.

This is the **single highest-confidence change** to try. The labels in
mainline were derived from observing the runtime value, not from RE'ing
the actual semantics. Writing zero very plausibly leaves the NPP block
in a partially-reset state where some registers accept writes and others
don't — which matches the reported symptom.

### P2 — Add missing pon_base writes
Add these between `zx_pon_reset` and `zx_pon_clk_reset_init`:
```c
writel(2,          ctx->pon_early + 0x40018);  /* stock A04 (unknown) */
```
And after register_pon_int (whenever that's done):
```c
writel(0xffffff7f, ctx->pon_early + 0x40044);  /* IRQ enable bit 7 = pon_tm */
```

Lower confidence — purpose unknown — but stock unconditionally writes
them at the very early init. `pon_base + 0x40018 = 2` runs before
SERDES, so it's likely a block-enable for some subsystem.

### P3 — Per-port reset pulse on link state transition
On link-up, do `pon_reset(1 << (port + 6))` before re-running
smac_init_port. Stock's `switch_phy_int_check.part.5` does this.
Mainline doesn't. This is **not** related to initial-boot symptoms but
will manifest as flakiness on cable replug.

### P4 — Remove the Iter 21 U-Boot-only MAC writes
Stock kernel does NOT write MAC[N][0x70/0xB4/0xC20/0xC50/0xB00]. These
came from U-Boot RE on the assumption "we need to match U-Boot's
working init". But:
1. Stock kernel's pon_reset wipes everything U-Boot did.
2. Stock kernel works without these writes.
3. The runtime state on stock matches "writes never happened".

The Iter 21 additions in `zx_smac_init_port` (zx-eth-main.c:1230-1235)
should be **removed** to match stock's behavior. They're harmless
(writes go to /dev/null per our findings) but they obscure the diff.

### P5 — Re-check NOT setting PP[0x2c] BIT(29) and NPP[+0x40] |= 0x300
These already match stock runtime behavior (i.e., they remain 0). No
change needed; the mainline comments already document this.

---

## 6. What the actual TX wedge is (not a lock)

Per `iter11_a11_not_tx_cause_2026-05-27.md` and prior findings, the
real TX failure manifests as `tm_irq_count = 0` and TX descriptors
not being consumed by HW. The candidate causes from those docs:

- A07/A08/A09: PON / NPP IRQ registration. Mainline may be missing the
  PON aggregate IRQ registration that gates TM enable.
- A13: `zte_zx_api_pp_set_trap_queue` — protocol→CPU queue mapping.
- TM[0x10058] clear-on-read confirmed (commit 546ae0b3a).
- Periodic TX reclaim timer needed (commit 858df07c8, 80f610eda).

The "writes don't stick" symptom for MAC/PP/NPP registers is a **red
herring** — stock has the exact same symptom on a working device.

---

## 7. Confidence summary

| Question | Answer | Confidence |
|---|---|---|
| Q1: Is there an unlock register sequence? | No software unlock exists. The writes are W1C / consumed-by-HW. Stock has the same symptom and runs fine. | High (live stock readback confirms) |
| Q2: What does stock do between BMU enable and the failed writes? | Same things mainline does, plus `npp+8 = 0xFFFFFF` and `npp+0xC = 0xFFFFF` (BIG bit-1 writes, not 0). | High |
| Q3: pon_npp_smac_init body | See Section 3. Just gephy_ldo_init + per-port (mdio + smac_init + `npp[N*40000] \|= 2`) loop. | High |
| Q4: Indirect-write protocol? | Yes for TM RED / PP SADM / PP CLA / TM USCH RAMs, **NOT** for the failing MAC config registers. | High |
| Q5: U-Boot writes that don't lock | U-Boot does per-port reset pulse + writes same MAC regs. Doesn't matter — stock kernel wipes everything via pon_reset. | High |

## 8. Single most actionable fix to test next

**Change mainline's NPP+8 / NPP+0xC writes to match stock's literal
values** (0xFFFFFF and 0xFFFFF, with a 1ms sleep after). This is the
only register-level divergence between stock and mainline where stock
writes "max bits" and mainline writes "the observed-readback value".
Writing zero here might be leaving the NPP block in a reset-asserted
state, which would explain why downstream MAC writes have no effect.

```c
/* In zx_npp_init: */
npp_write(e, 0x08, 0x00FFFFFF);  /* was 0 — stock writes 24 bits */
npp_write(e, 0x0C, 0x000FFFFF);  /* was 0x3FFFF — stock writes 20 bits */
usleep_range(1000, 2000);
```

If this single change makes MAC[N][0xE0] writes start sticking,
confirmed. If not, investigate `pon_base + 0x40018 = 2` next.

## 9. Cross-references
- Live stock register dump: `regs/stock_eth_2mib.txt`
- Stock init flow: `eth_init_flow_2026_05_26.md`
- Static analysis: `static_analysis_plat_zxylzb_init.md`
- Prior gap-matrix discussion: `tasks/00.01.eth-driver/findings/stock_init_sequence_analysis_2026-05-27.md`
- Iter 15 phantom-gap finding: `tasks/00.01.eth-driver/findings/iter15_npp_gap_phantom_2026-05-27.md`
- U-Boot reference impl: `tasks/00.10.03.re-uboot/findings/static_analysis_uboot_eth.md`
