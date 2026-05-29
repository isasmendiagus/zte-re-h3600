# CPU→LAN egress gate — the residual hairpin is BROADCAST flood-back

**Date:** 2026-05-28. **Device:** booted, MAINLINE driver, probed live over the
minimal C REPL `localhost:9999` + cross-checked against the captured stock-live
2 MiB dump (`regs/stock_eth_2mib.txt`).

**One-line verdict:** The just-applied PP[0x8004/0x8184/0x8188] fixes **STUCK**
(verified live, no clobberer). They did nothing because the residual +15
loopback is **not a unicast-DA-lookup miss** — the looped frame is a
**BROADCAST** (dst `ff:ff:ff:ff:ff:ff`, SMAC = device MAC `f4:f6:47:0f:42:64`),
and mainline force-floods broadcast back to the CPU port via three non-stock
flood registers. Stock keeps all three OFF. **Root cause = PP[0x8300] (broadcast
flood-enable) = 0xffff in mainline vs 0x00000000 stock-live**, plus the two
flood-portmask regs PP[0x8304] / PP[0x8344].

---

## PART A — did the fixes stick? YES. No clobberer.

### Live readback (mainline, this device)

Read via `/sys/kernel/debug/zx_eth/mem` (PP at mem byte 0x1c0000+0xXXXX),
streamed and self-calibrated on the host-MAC signature `00 59 e9 62` at
PP[0x80a8] (the prior-agent drift caveat applies; values below are from the
calibrated captures that passed the `PP[0x80a8]==0x62e95900 &&
PP[0x80ac]==0x0000c8a3` anchor check):

```
PP[0x8004] = 0x040200ff   <- FIX STUCK (bit17 age_en + bit26 hash_collision)
PP[0x8184] = 0x00000001   <- FIX STUCK (ramaddr_sel = 512 buckets)
PP[0x8188] = 0x00211b00   <- FIX STUCK (aging cycle)
PP[0x8180] = 0x00000004   (multi_vlan_mode bit2)
PP[0x8050] = 0x0000000a
PP[0x80a8/ac/b0] = 62e95900 / 0000c8a3 / 00000108   (host MAC learned, port bit3)
PP[0x81c0] = 0x000000ff   PP[0x81c4] = 0x00005555   PP[0x82c0] = 0x000000ff
PP[0x8340] = 0x015555ff
```

All three target values match `zx_pp_brg_init` literals (zx-eth-main.c L2369,
L2392, L2393) **exactly**. The fixes are LIVE.

### No clobberer (static proof)

Probe init order (verified at call sites):
`zx_eth_apply_stock_init` (L4444, runs FIRST) → `zx_eth_init_vlan_and_isolation`
(L4450) → `zx_eth_init_tm_subsystem`: `zx_pp_brg_init` (L4080, writes
0x8004/0x8184/0x8188) → `zx_tm_dma_init`/`bmu` → `zx_eth_init_chip_tm` (L4108:
trap_queues/isolate/pro_action) → `zx_pp_pm_apply_replay` (L4109) →
`zx_eth_repoint_tm_descriptors` (L4110).

Everything that runs AFTER `zx_pp_brg_init` touches only: the isolation table
(PP[0x83c0..]), CLA RAM (PP[0xc0xx]), spa/cla indirect tables, and pp_pm RAM.
**None writes PP byte 0x8004 / 0x8184 / 0x8188** (= base_dword 0x0e2001 /
0x0e2061 / 0x0e2062). Confirmed by grep of every replay header
(`zx_stock_table.h`, `zx_stock_bursts.h`, `zx_cla_table.h`, `zx_pm_table.h`,
`zx_npp_twin_data.h`, `zx-pp-pro-actions.h`, `zx_pkt_map.h`) — the only hits on
"0e2001" are the `zx_sbragregtable` *descriptor* rows (zx_reg_tables.h:151-159),
not replay *data*. This corroborates `tx_hairpin_persists_after_8340_fix_re.md`.

---

## PART B — root cause of the residual hairpin: broadcast flood-back

### Empirical: the looped frame is BROADCAST, not a unicast-DA miss

`cat /sys/kernel/debug/zx_eth/stats` BP dump (live mainline):
```
bp[bppe=0] (first 64B): ffffffff ffffffff ffffffff ffffffff 00c28001 f6f41300 64420f47 ...
                        ^^^^^^^^^^^^^^^^^^^ dst = ff:ff:ff:ff:ff:ff (BROADCAST)
                                              SMAC region contains f4 f6 47 0f 42 64 = DEVICE MAC
```
The frame the switch reflects to the CPU is a **broadcast** carrying the
device's own SMAC (the kernel's outbound ARP request / gratuitous ARP that
accompanies the ping exchange). It comes back to RX, `zx_sw_xmit`-detected as
SMAC==own at zx-eth-main.c:2749, counted as `tm_rx_loopback_drops`. The earlier
"unicast DA lookup miss" theory (`fdb_learn_commit_re.md`) was wrong for the
residual 15 — the host MAC IS learned (PP[0x80b0]=0x108, internal port 3) and
age_en is now on, yet loopback is still exactly 15, because the looped frames
are broadcast and never consult the unicast FDB.

### The stock CPU→LAN broadcast egress decision (decomp trace)

Authoritative bridge init is `tm_pon_pp_brg_initial`
(`decomp_all_tm.c:43579`), NOT the simpler plat `pon_pp_brg_init`
(`decomp_all_plat_zxylzb_9128S.c:5359`, which writes 0x8340=0xff5555ff /
0x8380=0x1f and is NOT what runs — stock-live 0x8340=0x015555ff proves tm.c's
version is authoritative). `tm_pon_pp_brg_initial` does:

- `sbrg_set_unknown_unicst_fwd(port,0)` all ports, then `(0,1)` only
  (tm.c:43631/43637) → PP[0x8340] bits24-31 = 0x01 (CPU only). Mainline ✓.
- `sbrg_set_pt_tls(port,0)` all ports, then `(0,1)` only (tm.c:43633/43638) →
  PP[0x8380] = **0x01** (TLS only on CPU/internal-port-0). `sbrg_set_pt_tls`
  writes sbragRegTable reg 0x38 = byte 0x8380 (`decomp_all_tm.c:11675`,
  zx_reg_tables.h:206).
- It NEVER calls `sbrg_set_brdcst_fld_en` (reg 0x31, byte 0x8300,
  `decomp_all_tm.c:6321`), nor `sbrg_set_pon_brdcst_flood_portmask` (reg 0x33,
  byte 0x8304, `decomp_all_tm.c:11420`), nor `sbrg_pon_unkuni_flood_portmask`
  (reg 0x37, byte 0x8344, `decomp_all_tm.c:11452`). They stay at cold-init 0.

So in stock, a CPU-sourced broadcast egresses purely by **VLAN-0 membership
minus the per-port isolation mask**. The source CPU port (internal port 0) is
excluded by its own isolation row, so the broadcast goes out the LAN ports and
**does not** return to the CPU. No hairpin.

### The divergence (stock-live ground truth vs mainline)

`regs/stock_eth_2mib.txt` (stock-live) vs `zx_pp_brg_init` writes:

| PP reg | sbrag reg / function | Stock-live | Mainline (line) | Match |
|---|---|---|---|---|
| 0x8300 | 0x31 `sbrg_set_brdcst_fld_en` | **0x00000000** | **0x0000ffff (L2395)** | ✗ |
| 0x8304 | 0x33 `sbrg_set_pon_brdcst_flood_portmask` | **0x00000000** | **0x020000ff (L2396)** | ✗ |
| 0x8344 | 0x37 `sbrg_pon_unkuni_flood_portmask` | **0x00000000** | **0x0000001e (L2377)** | ✗ |
| 0x8380 | 0x38 `sbrg_set_pt_tls` | **0x00000001** | **0x0000001f (L2378)** | ✗ |
| 0x8340 | 0x36 unknown_unicst_fwd | 0x015555ff | 0x015555ff (L2376) | ✓ |
| 0x8008 | 0x0a/0x0b transfer/vlan-chk | 0x0000dfdf | 0x0000ff00 (L2398) | ✗ (2nd-order) |
| 0x8004 / 0x8184 / 0x8188 | (Part A) | 040200ff/1/00211b00 | same | ✓ |

`sbrg_set_brdcst_fld_en` is a **per-port bitmap that turns ON forced broadcast
flooding**. Mainline sets it to 0xffff (= bits 0-15 → all 8 ports incl the CPU
port bit 0); stock leaves it 0. With it on, AND the flood-portmask regs
(0x8304/0x8344) listing the CPU port, the switch force-floods the device's own
broadcast back out the CPU port → the +15 hairpin. These four registers were
copied from the WRONG stock function (plat `pon_pp_brg_init`, which writes
0x8380=0x1f) instead of the authoritative `tm_pon_pp_brg_initial`.

---

## CONCRETE FIX

**File:** `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`, fn `zx_pp_brg_init`.
Set the four broadcast/flood/TLS registers to the stock-live values:

```c
// L2377  — was: writel(0x0000001e, pp + 0x8344);
writel(0x00000000, pp + 0x8344);   // sbrg_pon_unkuni_flood_portmask = 0 (stock-live)

// L2378  — was: writel(0x0000001f, pp + 0x8380);
writel(0x00000001, pp + 0x8380);   // sbrg_set_pt_tls: TLS on CPU port (bit0) ONLY (stock-live)

// L2395  — was: writel(0x0000ffff, pp + 0x8300);
writel(0x00000000, pp + 0x8300);   // sbrg_set_brdcst_fld_en = 0 (stock-live) — THE GATE

// L2396  — was: writel(0x020000ff, pp + 0x8304);
writel(0x00000000, pp + 0x8304);   // sbrg_set_pon_brdcst_flood_portmask = 0 (stock-live)
```

The single highest-leverage line is **PP[0x8300] = 0** (broadcast flood-enable
off). Land all four together — they are the complete stock-live broadcast/flood
config. After this, the device's own broadcast is no longer force-flooded to the
CPU port; it egresses via VLAN-0 membership minus isolation (which excludes the
source CPU port), so it reaches LAN3/PHY[2] and stops hairpinning.

Secondary (lower priority, not the gate): PP[0x8008] should be 0x0000dfdf (stock)
not 0x0000ff00 (L2398); CLA[0xc080] should be 0x600 (stock) not 0x1000 (replay).
Fix only if loopback is not fully cleared after the four-register primary fix.

---

## SOPC bridge / NPP[0x19068] — NOT the gate (cleared)

The brief candidate #5 (NPP[0x19068]) is correct in mainline. The decompiler
mislabels the constant 0x19064 as the function symbol `dma_cfg_byteorder`
(both live at file address 0x19064); `smac_sopc_mode_switch`
(`decomp_all_plat_zxylzb_9128S.c:2290`) actually does
`NPP[0x19064+4] = NPP[0x19068]` poll-bit-(port+5)/set-bit-port, then
`NPP[0x19038]` bit (port+0x10) duplex — **exactly** what mainline
`zx_eth_adjust_link` (zx-eth-main.c:3835-3878) does. MAC[2].ctrl=0x00ba6003
live (= MAC_CTRL_LINK_UP, bits 0+1 set = `pon_npp_smac_enable_part_3`'s `|3`,
plat:2775). MAC[2] is up and SOPC-bridged. Stock-live NPP[0x19068]=0 and
NPP[0x19038]=0 in the dump (captured in a state where they read back 0), so they
are not a useful diff axis. spa/dpa CPU-port setters (ROADMAP #40): the relevant
spa loop (`zx_chip_tm_init_pro_action`) is already replayed; `dpa` is the GPON
downstream block, irrelevant in LAN-only mode. None gate the broadcast hairpin.

---

## Confidence

- **Fixes stuck / no clobberer:** HIGH. Live readback matches source literals;
  static init-order + replay-table grep shows nothing rewrites 0x8004/0x8184/0x8188.
- **Looped frame is broadcast:** HIGH. Live BP dump dst = ff:ff:ff:ff:ff:ff with
  device SMAC.
- **PP[0x8300]/0x8304/0x8344/0x8380 are the divergence:** HIGH. Stock-live dump
  is unambiguous (0/0/0/1) vs mainline source (0xffff/0x020000ff/0x1e/0x1f);
  reg→byte mapping and setter names cited from decomp + zx_reg_tables.h.
- **PP[0x8300]=0 is THE gate:** MEDIUM-HIGH. `sbrg_set_brdcst_fld_en`'s name +
  the broadcast nature of the looped frame + stock keeping it 0 directly explain
  "device broadcast reflected to CPU"; empirical confirmation requires applying
  the fix and re-pinging (this pass is read-only).
