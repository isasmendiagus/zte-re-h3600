# PHY-MAC serializer bond — what asserts `phy_mac_ready` (0x19068 bit port+5), and the port1 gap

**Status:** static RE of stock kmod decomp (`decomp_all_plat_zxylzb_9128S.c`), U-Boot decomp
(`tasks/00.10.03.re-uboot/.../FUN_40e50c40.c`) and mainline (`zx-eth-main.c`), cross-checked
against live HW notes in memory (`zte-multiport-ingress-gap`, `zte-tx-egress-blocker`).
**Date:** 2026-06-01. **Analysis only — no device touched.**

**Question:** what makes the per-port PHY-MAC serializer *bond* so that `phy_mac_ready`
(`0x921d9068` bit(port+5)) asserts, and what does stock's bring-up do that mainline's
`zx_smac_init_port` omits — leaving port1's ready bit unasserted (port1 ingress root cause).

---

## 0. TL;DR

- `phy_mac_ready` (`0x921d9068` bit(port+5)) is a **RO HW status bit**. The HW raises it when the
  per-port SMAC↔PHY serializer/MII datapath comes into lock **after a per-port reset pulse +
  full per-port MAC register program**. It is NOT a writable enable — you cannot poke it.
- The authoritative bond sequence is **U-Boot `FUN_40e50c40`** (per link-up) and the kmod runtime
  twin `switch_phy_int_check_part_5` → `smac_init` + `pon_npp_smac_config_speed_duplex_part_0` +
  `smac_sopc_mode_switch`. The READY bit asserts as a *consequence* of that exact write set in
  that exact order, immediately followed by the poll loop in `smac_sopc_mode_switch`.
- **The single load-bearing step mainline omits / mis-orders for port1 is the PER-PORT RESET
  PULSE `pon_reset(1<<(port+6))` happening AT THE RIGHT TIME relative to the MAC program and the
  bond poll, and the bond poll being driven for the port that actually has link.** Stock pulses the
  reset *inside* the same link-up handler that immediately reprograms the MAC and then polls READY
  (one atomic chain). Mainline runs the chain only on a phylib `adjust_link` *edge*, and with
  `PHY_POLL` that edge for port1 can land such that the reset → reprogram → poll chain does not
  re-converge the serializer (the poll's 20×100µs window expires before the just-reset serializer
  re-locks, OR the reset pulse is skipped because `e->pon_early` is null / the edge was missed).
- Secondary: mainline's `zx_smac_init_port` is a faithful port of **U-Boot `FUN_40e50c40`** but NOT
  of the kmod runtime `smac_init`. Two register-value/semantic mismatches vs the *runtime* path
  remain (ctrl 0xBBE003 vs 0xBAE003; D00/D30 absolute-write 0x32/0xA8 vs read-mod-CLEAR). Neither
  alone blocks READY (U-Boot itself uses 0xBBE003 + 0x32/0xA8 and READY bonds), but they are noise.

---

## 1. The complete stock/U-Boot serializer-bond sequence (every reg write, in order)

### 1a. U-Boot `FUN_40e50c40(port, …)` — the authoritative per-link bond
(`tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_40e50c40.c`)

MMIO bases recovered from the DAT_ constants: MAC0 ctrl base `0x92200000` (`-0x6de00000`),
MAC0+0xe0 base `0x922000e0` (DAT_40e50e7c), MAC0+0x70 base `0x92200070` (DAT_40e50e84),
SOPC/bond base `0x921d9000` (DAT_40e50e8c). Per-port stride `0x40000`.

```
# read PHY link/speed via MDIO regs 0x1e/0x1a (FUN_40e4010c/40e40204), bail if !(0x40)   :24-31
# decode speed(uVar6)/duplex(iVar8) from MDIO 0x1a bits[9:7]                              :38-55
FUN_40e2a1b4(...)                              # LED/board callback (irrelevant to bond)  :56
FUN_40e4fdcc(1 << (port+6)):                   # ==pon_reset:  *0x92000008 &= ~(1<<(port+6))
    delay(10)                                  #               *0x92000008 = 0xffffffff       :58
# ---- per-port MAC register program (= kmod smac_init + the +0xc20/+0xc50/+0x70/+0xb4/+0xb00) ----
MAC[port]+0x000  = 0x00bbe003   (ctrl; DAT_40e50e70)                                       :61
MAC[port]+0x008  = 0x80000001   (enable)                                                   :62
MAC[port]+0x0e0  = 0x00011200   (DAT_40e50e78 — serializer/PHY iface "config word")        :64
MAC[port]+0xd00  = 0x00000032   (= 0x922000e0 + 0xc20 + port*0x40000)                      :65
MAC[port]+0xd30  = 0x000000a8   (= 0x922000e0 + 0xc50 + port*0x40000)                      :66
MAC[port]+0x004  = 0x0000fffe   (irq mask)                                                 :68
MAC[port]+0x070  = 0x00300002   (IFG/rate; DAT_40e50e80)                                   :70
MAC[port]+0x0b4  = 0x00004000   (= 0x92200070 + 0x44 + port*0x40000)                       :71
MAC[port]+0xb00  = 0x0010ff11   (= 0x92200070 + 0xa90 + port*0x40000; DAT_40e50e88)         :72
FUN_40e2a1b4(...)                              # 2nd board callback                        :73
FUN_40e50bd4(port, speed, duplex):             # == config_speed_duplex: ctrl bits 13/14/15:74
    1G  -> ctrl = (ctrl & ~0x8000) | 0x2000
    FD  -> ctrl |= 0xa000 ; HD -> (ctrl&~0x2000)|0x8000 ; 100 -> |0x4000 ; else &~0x4000
# ---- THE BOND POLL (this is what observes/sets the handshake; READY asserts in this window) ----
iVar8 = 0x921d9000 ; retries = 5                                                           :75-76
do {
    FUN_40e45ac0(1)                            # short delay (lets the serializer settle)
    if (*(0x921d9000+0x68) & (1<<(port+5))) {  # poll phy_mac_ready (RO)                    :79
        *(0x921d9000+0x68) |= (1<<port)        # set mac_rx_to_fabric_en (the SW admit bit) :80
        break
    }
} while (--retries)                                                                        :77-84
FUN_40e50c20(port):  MAC[port]+0x000 |= 3      # FINAL rx/tx datapath enable                :85
```

### 1b. kmod runtime twin — `switch_phy_int_check_part_5(port)` (plat:2797, link-UP arm @2899-2906)
Identical structure, called on every PHY-IRQ link transition and at cold bring-up
(`switch_phy_int_check`→…→`smac_sopc_mode_switch`, plat:3197):

```
pon_reset(1 << (port+6))                       # plat:2901  *pon_base+8 &= ~bit; delay; |= bit
smac_init(port)                                # plat:2902 / @2272:
    MAC[port]+0x000 = 0xbae003                 #   NOTE: kmod uses 0xBAE003 (U-Boot used 0xBBE003)
    MAC[port]+0x004 = 0xffff                   #   NOTE: kmod 0xFFFF (U-Boot 0xFFFE)
    MAC[port]+0x008 = 0x80000001
    MAC[port]+0x0e0 = &PTR_caseD_47_00011200   #   ⚠ a Ghidra *symbol-address* (0x00011200 = the
                                               #     pointer's location in .text), reads back ~0 live
    MAC[port]+0xd00 &= ~0x2                     #   read-mod-CLEAR bit1 (NOT =0x32)
    MAC[port]+0xd30 &= ~0x20                    #   read-mod-CLEAR bit5 (NOT =0xA8)
pon_npp_smac_config_speed_duplex_part_0(port, speed, dup)   # plat:2903/2737 (== FUN_40e50bd4)
smac_sopc_mode_switch(port, dup)               # plat:2904 / @2290:
    for i=5..1: barrier();
        if (NPP[0x19068] & (1<<(port+5))) { NPP[0x19068] |= (1<<port); break; }   # THE BOND POLL
    NPP[0x19038] = (NPP[0x19038] & ~(1<<(port+16))) | ((dup!=1)<<(port+16))        # duplex flag
pon_npp_smac_enable_part_3(port)               # plat:2905  MAC[port]+0 |= 3  (final enable)
```

### 1c. What physically raises `phy_mac_ready` (bit port+5)
There is **no software writer** of bit(port+5) anywhere in stock/U-Boot/mainline (only bit(port) is
ever written, by the poll loops above). It is a **HW-driven serializer/PHY-MAC lock-done status**.
The HW raises it after:
1. the per-port reset bit `pon_base+8` bit(port+6) is **de-asserted→re-asserted** (the
   `pon_reset(1<<(port+6))` / `FUN_40e4fdcc` pulse), which re-arms the SMAC↔PHY serializer, AND
2. the per-port MAC datapath is reprogrammed (ctrl/enable/+0xe0/+0x70/+0xb00/D00/D30 — establishes
   the MII iface/clock), AND
3. a short settling delay (`FUN_40e45ac0(1)` per poll iteration; the poll itself paces it).

So READY = "serializer re-armed by the port reset pulse, then the MAC iface reprogrammed, has
re-locked." The poll loop's *delays* are load-bearing — they give the just-reset serializer time
to re-lock before the window closes. (`zte-tx-egress-blocker` independently observed READY is a
**transient** lock strobe — it asserts shortly after this chain and can drop later; the kmod holds
it by re-running the chain every 10 jiffies via `extphy_timer_func`, plat:3137.)

---

## 2. What gates `phy_mac_ready` asserting — dependency chain

`phy_mac_ready[port]` (0x19068 b(port+5)) depends, in order, on:
1. **Per-port serializer reset pulse** `pon_reset(1<<(port+6))` (pon_base+8 = `0x92000008`+8 →
   actually `pon_base+8`; in U-Boot `*0x92000008`). Without this re-arm the serializer never
   re-attempts lock on a link change.
2. **Full per-port MAC iface reprogram** (the smac_init / FUN_40e50c40 body — ctrl, enable, +0xe0,
   +0x70, +0xb4, +0xb00, D00, D30) establishing the GMII/serializer clocking.
3. **Speed/duplex applied to ctrl** (config_speed_duplex) — the serializer locks at the negotiated
   rate; a stale/half-duplex ctrl can prevent FD lock.
4. **Settling time** before/while polling (the per-iteration `FUN_40e45ac0(1)` delay).

It does NOT depend on a separate PLL/SerDes register write — there is none in software; the PON
subsystem clock (`top_crm` TOPCRM[0x0C] |= 0x1E0) is global and already up. (`phy_mac_rgmii_wedge_re.md` §1.)

---

## 3. DIFF vs mainline — exactly what's omitted / mis-ordered (ranked)

Mainline runs the chain in `zx_eth_adjust_link` (zx-eth-main.c:4355-4500), per phylib link-edge:
`pon_reset pulse (4378-4385)` → `zx_smac_init_port (4400)` → `config_speed_duplex ctrl (4408-4417)`
→ `TM[0xc000] (4437)` → **`0x19068 READY poll+set (4463-4478)`** → `0x19038 duplex (4485-4489)` →
`ctrl|=3 (4495)`. `zx_smac_init_port` (1226) is a faithful port of **FUN_40e50c40's MAC-register
body** (the [egress fix 2026-05-29] comment confirms it). So the *structure* matches stock.

### R1 (LEADING) — the reset→reprogram→poll chain is not reliably atomic per-port on the link edge
- **pon_reset pulse is conditional on `e->pon_early`** (4378 `if (e->pon_early)`). If `pon_early`
  is not mapped, the per-port serializer is **never re-armed**, so on a link-up *edge* the serializer
  for that port is whatever it was — and for a port that came up later / was reset by the global
  probe-time `pon_reset(0xffffffff)`, it is in reset-cleared state and never re-locks → READY never
  asserts. Stock/U-Boot ALWAYS pulse it (unconditional, inside the same handler).
  ⇒ verify `e->pon_early != NULL` at runtime; if null this is the bug for any non-boot port.
- **The READY poll window is 20×100µs = 2ms (4463-4470)** AFTER `msleep(10)` in the reset pulse.
  U-Boot polls 5× with `FUN_40e45ac0(1)` between the MAC reprogram and the poll, and the *kmod*
  re-runs the WHOLE chain every 10 jiffies (`extphy_timer_func`) so READY is continuously re-driven.
  Mainline polls **once per link edge**; if the just-reset serializer hasn't relocked inside 2ms the
  branch takes the `else` ("ready bit N NEVER set — bridge NOT enabled" warning, 4476) and **never
  retries for that port** unless another link edge fires. With `PHY_POLL` (no link IRQ), a stable
  link produces exactly one edge → one failed poll → permanently closed bridge.
  **This is the most likely port1 failure mode.** (file:line 4463-4478)
- The keepalive `zx_mac_keepalive_fn` (3109) DOES re-poll READY every 100ms (3135-3142) — BUT it is
  **light**: it does NOT re-run `pon_reset` or `zx_smac_init_port` (comment 3105 "NO
  pon_reset/smac_init, so it doesn't disturb live traffic"). So if the serializer needs a
  reset+reprogram to relock (it does — that's what arms it), the keepalive can never make READY
  assert; it only catches a READY that the *edge* handler already produced. ⇒ port1, whose edge
  handler failed to bond, is never recovered by the keepalive. **Mainline lacks stock's heavy
  re-run-the-whole-chain timer (`extphy_timer_func`).**

### R2 — `zx_smac_init_port` value/semantic mismatches vs the kmod *runtime* smac_init
`zx_smac_init_port` matches **U-Boot FUN_40e50c40**, not the kmod runtime `smac_init`. The kmod
runtime (the path that actually holds READY in steady state) differs:
| reg | mainline (=U-Boot FUN_40e50c40) | kmod runtime smac_init (plat:2276-2281) |
|---|---|---|
| MAC+0x000 ctrl | `0x00bbe003` | `0x00bae003` (bit20 clear) |
| MAC+0x004 mask | `0x0000fffe` | `0x0000ffff` |
| MAC+0x0e0 | `0x00011200` | `&PTR_caseD_47…` (effectively ~0 live) |
| MAC+0xd00 | `=0x32` (absolute) | `&= ~0x2` (read-mod-clear bit1) |
| MAC+0xd30 | `=0xa8` (absolute) | `&= ~0x20` (read-mod-clear bit5) |
These are **not bond-blockers** (U-Boot uses the BBE003/0x32/0xA8 set and READY *does* bond at
boot), so R2 is **noise, not the gate** — but the D00/D30 absolute-write can leave non-reset bits
in a different state than the runtime path; lowest priority.

### R3 — duplex flag write order (`0x19038`)
Mainline writes `0x19038` (4485-4489) AFTER setting the admit bit; stock writes it inside
`smac_sopc_mode_switch` right after the poll, before the final enable. Functionally equivalent for
FD; only matters if the link trained HD. Low priority.

---

## 4. Why PORT1-specific (if mainline runs the same chain for all 4)?

Mainline DOES run `zx_smac_init_port` for i∈{0,1,2,3} at probe (1301-1302) and re-runs the chain in
`adjust_link` for whichever port's link edge fires. So a per-index *code* bug is unlikely — and the
numbering is confirmed correct (port1 → bit1/bit6, raw/logical; §5). The port1-specificity is a
**timing/ordering/transient** effect, ranked:

- **(a) ORDER/edge-timing (LEADING).** port1 is the historical *boot* host port; ports 2/3 were
  hotplugged after the `PHY_POLL` fix. The bond is produced only on a phylib link *edge*. The boot
  port's edge fires once, very early, possibly before the serializer has re-locked from the
  probe-time global `pon_reset(0xffffffff)` (which clears ALL per-port reset bits) — its single
  2ms poll window expires, READY never set, and the light keepalive can't recover it (R1). Later
  hotplugged ports get a *fresh* reset pulse from the per-port path at a calmer time and bond. This
  matches every live observable: MAC1 RX-ok climbs (wire-side, before the bridge), PHY[1] negotiates
  1G/FD fine, but `rcv_uni1≈0`, `0x19068` bit6/bit1 clear for port1 only.
- **(b) READY transient + no heavy re-run.** Even if port1 momentarily bonds, READY is a transient
  lock strobe (`zte-tx-egress-blocker`); stock's `extphy_timer_func` re-runs reset+smac_init every
  10 jiffies to hold it. Mainline's keepalive is light (R1) and cannot re-bond → port1 drifts back
  to unbonded.
- **(c) shared-serializer disturbance.** Bringing up port2/3 issues their own `pon_reset(1<<(p+6))`;
  if the serializer/clock resources are shared at the SMAC↔PHY block, a later port's reset can
  perturb port1's lock — and only port1 (no fresh re-bond) stays down. Plausible but unconfirmed.
- **(d) +0xe0 / +0xc-block WRITE-ONCE non-determinism** (`zte-tx-egress-blocker` notes the +0xe0
  serializer reg reads back 0 live and that the +0xc20/+0xc50/+0xb00 land non-deterministically).
  If port1's iface write didn't land, its serializer never locks. Lower confidence because mainline's
  zx_smac_init_port now writes the U-Boot set, but the WRITE-ONCE behavior could still bite port1
  on the boot-time path.

**Not the cause:** a per-index wrong value (all four ports get identical code/values), SPA/SDET/CLA
classify (all exonerated, identical across ports), numbering (§5).

---

## 5. Numbering — confirm mainline targets port1 correctly

| element | index space | mainline expr | port1 lands at |
|---|---|---|---|
| `zx_smac_init_port`/`mac_off(port)` | phys-MAC = raw logical | `(port+1)*0x40000` (410) | MAC1 `0x92240000` ✅ |
| `pon_reset` pulse | raw logical | `1u<<(i+6)` (4379) | bit7 ✅ |
| READY poll bit | raw logical | `1u<<(i+5)` (4452) | bit6 ✅ |
| admit bit | raw logical | `1u<<i` (4453) | bit1 ✅ |
| duplex flag | raw logical | `1u<<(i+16)` (4454) | bit17 ✅ |

All consistent with stock (raw/logical). **Mainline uses the correct index for port1 in every
serializer/bond write.** The gate is state/timing, not a wrong index.

---

## 6. Citations
- U-Boot: `FUN_40e50c40` (full bond, reset @58, MAC body @61-72, config_speed_duplex @74,
  READY poll @75-84, final enable @85); `FUN_40e4fdcc` (=pon_reset, `*0x92000008`);
  `FUN_40e50bd4` (=config_speed_duplex); `FUN_40e50c20` (=ctrl|=3).
- stock kmod: `smac_init` plat:2272; `smac_sopc_mode_switch` plat:2290 (poll @2298, set @2300,
  duplex @2305); `config_speed_duplex_part_0` plat:2737; `pon_npp_smac_enable_part_3` plat:2769;
  `switch_phy_int_check_part_5` link-up arm plat:2899-2906; `extphy_timer_func` plat:3137
  (10-jiffy heavy re-run); `pon_npp_smac_init` cold init plat:3273; `pon_reset` plat:7744
  (`pon_base+8` clear/delay/set).
- mainline: `zx_smac_init_port` :1226; `mac_off` :408; `zx_eth_adjust_link` :4355 (pon_reset cond
  :4378, smac_init :4400, ctrl :4408, READY poll+set :4463-4478, duplex :4485, enable :4495);
  `zx_mac_keepalive_fn` :3109 (light re-poll :3135, no reset/smac_init :3105).
- findings: `mac_to_spa_admit_re.md`, `ingress_datapath_architecture_re.md`,
  `phy_mac_rgmii_wedge_re.md` (§1-3, Fix A); memory `zte-multiport-ingress-gap`
  (live: MAC1 RX-ok climbs, port1 only fails, fix = serializer bring-up not poking),
  `zte-tx-egress-blocker` (READY transient, extphy re-run, +0xe0 write-once).

---

## DATASHEET updates

1. **`phy_mac_ready` is a HW serializer-lock STATUS, and how it is produced** (extend the existing
   `0x921d9068` entry, DATASHEET §"SOPC↔SMAC bridge"):
   - `0x921d9068` bit(port+5) `phy_mac_ready[port]` — RO. HW raises it after the per-port chain
     **`pon_reset(1<<(port+6))` (pon_base+8 pulse) → full MAC iface reprogram (ctrl/en/+0xe0/+0x70/
     +0xb4/+0xb00/+0xd00/+0xd30) → config_speed_duplex ctrl → settle**, i.e. when the SMAC↔PHY
     serializer re-locks. There is **no SW writer** of this bit and **no separate PLL/SerDes
     register** — it is the serializer lock-done. It is **transient**: stock holds it by re-running
     the whole chain every 10 jiffies (`extphy_timer_func`). Confidence ✅.
   - bit(port) `mac_rx_to_fabric_en[port]` — the only SW-written bit; set ONLY after bit(port+5)
     observed. (already in datasheet — annotate that bit(port+5) cannot be forced.)
2. **MAC per-port serializer/iface register block** (new sub-table; U-Boot FUN_40e50c40 +
   kmod smac_init), per-port stride `0x40000`, MAC0 base `0x92200000`:
   - `+0x000` ctrl — U-Boot/mainline `0xBBE003`, kmod-runtime `0xBAE003`; bits[1:0] rx/tx enable,
     b13 1G, b14 100M, b15 half/10M.
   - `+0x004` irq mask — U-Boot `0xFFFE`, kmod `0xFFFF`.
   - `+0x008` enable — `0x80000001`.
   - `+0x0e0` serializer/PHY-iface config word — U-Boot writes `0x00011200`; kmod writes a
     fn-pointer symbol; **reads back ~0 live** (write-once / clock-gated sub-reg). Treat the live
     value as don't-care; the *act* of writing during the bond chain is what matters.
   - `+0x070` `0x00300002` (IFG/rate); `+0x0b4` `0x00004000`; `+0xb00` `0x0010FF11`.
   - `+0xd00` (= base+0xe0+0xc20) — U-Boot `=0x32` absolute; kmod runtime `&= ~0x2`. tsf/store-fwd.
   - `+0xd30` (= base+0xe0+0xc50) — U-Boot `=0xa8` absolute; kmod runtime `&= ~0x20`. rsf/flow.
   Confidence ✅ (two independent decomps agree on offsets/values).
3. **Per-port serializer reset:** `pon_base+8` bit(port+6) = per-port SMAC↔PHY serializer reset
   (active behavior: clear→delay→set re-arms the serializer; U-Boot `FUN_40e4fdcc` ends by setting
   `*0x92000008 = 0xffffffff`). port1 → bit7. This pulse is a PRECONDITION for `phy_mac_ready`
   re-asserting on a link change. Confidence ✅.

---

## mainline fix

**Goal:** make port1's `phy_mac_ready` (0x19068 b6) re-assert so the `if(ready)` guard sets admit
bit1 → SOPC↔SMAC bridge opens → `rcv_uni1` climbs.

### Fix 1 (primary) — make the READY poll robust + retry the WHOLE chain, mirroring `extphy_timer_func`
In `zx_eth_adjust_link` (around 4449-4478): the bond can fail because the just-reset serializer
hasn't relocked inside the 2ms window. Two changes:

(a) **Unconditionally pulse the per-port reset** (drop the `if (e->pon_early)` skip, or hard-fail
   probe if `pon_early` is null) so the serializer is always re-armed before the MAC reprogram —
   stock never skips it.

(b) **If READY is not seen, retry the full reset→smac_init→config_speed_duplex→poll chain** a few
   times (not just the light poll). Concretely, wrap 4400-4478 in a `for (try=0; try<3 && !ready; try++)`
   that re-issues `pon_reset(1<<(i+6))` + `zx_smac_init_port(e,i)` + ctrl + poll. This is what
   stock's `extphy_timer_func` effectively does over time.

### Fix 2 (durable hold) — upgrade the keepalive to re-run the heavy chain for un-bonded ports
In `zx_mac_keepalive_fn` (3109): for any link-up port whose `0x19068` bit(i+5) is **clear**, run the
FULL bring-up (pon_reset pulse + `zx_smac_init_port` + config_speed_duplex) before the poll — exactly
stock `extphy_timer_func` (plat:3137) which calls `pon_reset → smac_init → config_speed_duplex →
smac_sopc_mode_switch → enable` on the polled port every 10 jiffies. The current keepalive
deliberately skips reset/smac_init (3105) and therefore can never *bond* a port that failed at the
edge — only hold one already bonded. Gate the heavy re-run on `!(readl(br) & (1u<<(i+5)))` so it does
not disturb already-bonded live traffic.

```c
/* in zx_mac_keepalive_fn, replace the light per-port body for un-bonded ports */
reg = readl(br);
if (!(reg & (1u << (i + 5)))) {            /* serializer not bonded — re-run heavy chain */
    if (e->pon_early) {
        u32 m = 1u << (i + 6), v = readl(e->pon_early + 8);
        writel(v & ~m, e->pon_early + 8); msleep(10); writel(v | m, e->pon_early + 8);
    }
    zx_smac_init_port(e, i);
    c = readl(mc);
    if (phy->speed == SPEED_1000) c = (c & ~0x8000u) | 0x2000u;
    writel(c, mc);
}
for (t = 0; t < 5; t++) {                  /* then the existing ready-gated set */
    reg = readl(br);
    if (reg & (1u << (i + 5))) { writel(reg | (1u << i), br); break; }
    udelay(50);
}
writel(readl(mc) | 0x3u, mc);
```

### Fix 3 (cleanup, low risk) — align `zx_smac_init_port` D00/D30 to the kmod runtime semantics
Optional: change `writel(0x32, mac+0xD00)` / `writel(0xA8, mac+0xD30)` to read-mod-clear
(`v &= ~0x2` / `v &= ~0x20`) to match the kmod runtime smac_init (plat:2280-2281) rather than U-Boot.
Not expected to fix the bond by itself; do it only if Fix 1/2 don't fully stabilize port1.

---

## Bench test (verify port1 bonds → rcv_uni1 climbs)

All addresses are **raw/logical** port space (port1 = bit1/bit6/bit7).

1. **Baseline read** — boot with cable on jack2 (port1) AND a working jack (e.g. jack3/port2):
   - `devmem 0x921D9068` → expect working ports show bit{2,3}=admit + bit{7,8}=ready set;
     **port1 = bit1 clear AND bit6 clear** (confirms READY never asserted).
   - `devmem 0x921D45CC` byte1 (`rcv_uni1`) ≈ 0 while MAC1 RX-ok (`0x92240780`) climbs under host ping.
2. **Confirm it's the serializer, not the admit bit** — force admit only:
   `v=$(devmem 0x921D9068); devmem 0x921D9068 32 $((v|2))` → `rcv_uni1` **stays ~0** (bit6 RO not set
   ⇒ bridge HW still closed). This reproduces the prior failed poke and proves READY is the gate.
3. **Apply Fix 1+2, rebuild** (`make` the zx-eth module, reload / reboot). Re-read `0x921D9068`:
   **port1 bit6 (ready) now set, bit1 (admit) set.** dmesg should show
   `[egress] PHY[1] SOPC bridge ENABLED (ready)` instead of the `ready bit 6 NEVER set` warning.
4. **Confirm datapath** under host→device ping to port1:
   - `0x921D45CC` byte1 (`rcv_uni1`) climbs; `0x921C4164` (SDET uni1 transport) climbs;
   - `0x9234C060` (QMG hw_trap) climbs; driver `tm_rx_count` increments; host ARP/ping to port1
     succeeds. If `rcv_uni1` climbs but ping still fails, the residual is the post-QMG SIPC→QMG
     FIFO backpressure noted in `zte-multiport-ingress-gap` (separate, lower-value).
5. **Hold test** — let the link idle 30s, re-read `0x921D9068`: port1 bit6/bit1 must STILL be set
   (Fix 2 holds it). If it drops, the heavy keepalive re-run isn't firing for port1 — check the
   `!(reg & (1<<(i+5)))` gate.
