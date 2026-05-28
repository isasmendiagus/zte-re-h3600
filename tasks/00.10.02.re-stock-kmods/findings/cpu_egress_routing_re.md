# CPU-TX egress routing — how stock routes CPU frames to the physical MAC[N]

**Status**: deep RE complete; one register/desc gap identified, FDB self-MAC
NOT required, three smaller cleanups suggested.
**Date**: 2026-05-28.
**Symptom (input)**: mainline driver: HW consumes TX desc
(TM[0x1005c] HIGH=LOW=26, BMU recycles bp_idx, kick advances), host tcpdump
sees ZERO frames, every CPU TX increments `tm_rx_loopback_drops` — switch
fabric reflects back to CPU.

Sources walked:
- `decomp_all_plat_zxylzb_9128S.c` lines 6232–6911 (full pon_tm_net_tx +
  pon_tm_data_raw_send + soft_insert_tx_1desc + tx desc fill paths).
- `decomp_all_plat_zxylzb_9128S.c` lines 5359–5536 (pon_pp_brg_init,
  pon_pp_add_port_to_vlan, pon_pp_cla_init, pon_pp_port_isolate).
- `decomp_all_tm.c` lines 10706–10840 (sbrg_add_mactable D0/D1/D2 encoding).
- `decomp_all_tm.c` lines 20316–20384 (pp_pm_set_onu_mac_ram_info — PP self-MAC).
- `decomp_all_tm.c` lines 35962–35988 (tm_set_pp_wan_cfg → PP[0x1a01c] BIT(29)).
- `decomp_all_tm.c` lines 41273–41362 (tm_onu_mac_addr_set — what writes self-MAC).
- `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_40e50a9c.c`
  (U-Boot PP block bring-up: 11 writes to `0x92388000+`, including 0x2c0).
- `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_40e50854.c`
  (U-Boot TX dispatcher: `desc[0xc] = 2` and NO 0xc9 marker).
- `tasks/00.10.02.re-stock-kmods/findings/tx_consume_engine_re.md`
  (prior pass; this doc supersedes by reframing the "CPU port routing" Q).
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` 460-700 (zx_fdb_add,
  zx_sbrag_add_mac), 2200-2413 (zx_pp_ctrl_init, zx_pp_brg_init,
  zx_register_cpu_mac), 3070-3220 (zx_sw_xmit), 4180-4234
  (zx_eth_register_cpu_mac_slots, zx_eth_init_vlan_and_isolation).

---

## TL;DR

The mainline TX desc bytes are byte-for-byte identical to stock. The wedge
is **NOT** in the desc. The wedge is one of three things, in priority order:

1. **HIGHEST**: mainline's `zx_sw_xmit` writes to `e->dndesc_cpu` and kicks
   `TM[0x10064]` (DN ring). Stock for the "sw" netdev unambiguously uses
   the UP ring + UP kick (`TM[0x10054]`). The DN ring is the GPON downstream
   path — it lives in a different egress fabric and crucially **does not
   activate the per-port LAN egress that the UP→SW→MAC[N] crossbar uses**.
   When HW dequeues from DN ring it routes the frame through the GPON
   upstream-to-LAN classifier, which on a unit with no PON link is a
   hairpin to CPU = "loopback drop". This perfectly explains the symptom.

2. **HIGH**: post-kick `desc[11] &= ~0x20` (VALID clear) in mainline
   (line ~3215). Stock NEVER clears VALID after the kick. HW reads the
   desc asynchronously after `TM[0x1005x] = 1` returns. If we clear VALID
   first, HW skips the slot → frame stays in BMU but never egresses;
   eventually the BP gets recycled by BMU and re-used for the next TX,
   the kick advances the cursor (TM[0x1005c] HIGH16), but no wire egress
   happens. This compounds with (1).

3. **MEDIUM** (cleanup only): stock writes
   `PP[0x1a01c] |= BIT(lan_up_port + 0x19)` (`= BIT(29)` for `lan_up_port=4`)
   via `tm_set_p2pmode → tm_set_pp_wan_cfg`. Mainline doesn't. Per the
   stock 2 MiB dump this bit reads as 0 (write-locked or
   write-only-side-effect), so empirically it's likely not the gate
   blocking us — but the write is free to add and we can't prove it's
   inert without doing it.

**FDB seed for the device's own MAC is NOT required** — stock never adds
its own MAC to the bridge FDB. The CPU port (port 5 in stock) is enabled
in the SMAC_LOOK_EN bitmap (PP[0x81c0] = 0xff) and the switch fabric uses
**source-port routing**, not destination-MAC routing, for CPU→LAN frames.

---

## Q1: How does stock route CPU-TX → physical MAC[N]?

**Answer: via the UP ring + soft_insert_tx_1desc(desc, dir=0) →
TM[0x10054] = 1 kick. The 0x2c0 encoded in desc[2..3] is NOT a destination
port: it is the GEM (Generic Encapsulation Method) ID = LAN-up-virtual-port
40+lan_up_port. The switch fabric uses dst-MAC FDB lookup OR (more
commonly) port-isolation + VLAN-membership to pick the egress port.**

### Stock TX dispatcher (`pon_tm_net_tx`, plat:6721)

Two netdevs are registered at module init:

```
pon_tm_net_register(0, "swM") → priv[0x4c8] = 0 → UP path (dir=0)
pon_tm_net_register(1, "pon") → priv[0x4c8] = 1 → DN path (dir=1)
```

For LAN-only mode (`g_pon_work_mode = 0x10`), all CPU→LAN egress flows
through the "swM" netdev → **UP path** (line 6745–6810):

```c
desc[0]    = 0xc9;                       // CPU source marker
desc[1..3] = 0;
desc[4..7] = 0x00010000;                 // byte 6 = 1 (= no-source-port marker)
desc[8..11]= (initially 0x01000000)
desc[2..3] = (lan_up_port + 0x28) << 4;  // GEM ID 40..43 for lan_up=0..3
                                         // → 0x2c0 for lan_up_port = 4
pon_tm_data_raw_send(skb, desc, /*dir=*/0);
  ├── bp = bmu_alloc()
  ├── memcpy(BP[bp]+16, skb->data, len)
  ├── desc[11] = (desc[11] & 1) | 0x20    // VALID + format = 0x21
  ├── desc[7]  = (bp & 0x7f) << 1
  ├── desc[8]  = bp >> 7
  ├── desc[12..13] = (len << 2)            // (or 0x100 if len<0x40 padded)
  ├── desc[8..11] |= (len << 9)
  ├── soft_insert_tx_1desc(desc, dir):
  │     dma_cache_maint(desc, 16, 1)
  │     TM[0x10054] = 1   // UP kick (dir=0)
  │     // dir=1 would write TM[0x10064], but sw netdev is ALWAYS dir=0
  └── return
```

**No FDB lookup, no destination-MAC routing logic on the TX path.** The
switch fabric is given: a frame with `desc[0]=0xc9` (CPU source), GEM ID
0x2c (encoded in desc[2..3]), and a BP pointer to the actual ethernet
frame at `BP[bp]+16`. The fabric then runs the frame through:

```
UP TX ring (TM[0x10054]) → TM crossbar → PP/PP_BRG classifier
   → reads ethernet dst-MAC + VLAN tag → FDB lookup in PP_BRG_RAM
   → if dst-MAC in FDB: forward to learned port
   → if dst-MAC NOT in FDB AND unknown-unicast-flood allowed: flood to
        all ports not in port-isolate mask, MINUS the CPU port
   → if dst-MAC is broadcast: flood to all VLAN members
```

The desc[2..3] GEM ID = 0x2c is used as the **source GEM port** for the
PP_BRG VLAN classifier (`pon_pp_add_port_to_vlan(vlan=0, port, 3)` loop
at plat:5384–5386 sets all 8 ports as VLAN-0 members), AND as the
"per-port isolate source" for the port-isolation table at PP[0x83c0+port*4].

### Why 0x28? the LAN-up GEM-port offset

Stock GEM port numbering:
- 0x00..0x07: LAN ports 0..7 (physical)
- 0x28..0x2f: LAN-up virtual ports 0..7 (CPU-source frames)
- (other ranges for GPON, OAM, etc.)

The +0x28 offset means "this frame is from CPU acting as a virtual UNI on
port lan_up_port". The switch then treats it as ingress on a virtual LAN-up
port, NOT as a destination hint. **Routing happens by FDB / flooding on
destination MAC, AFTER the GEM-classifier consumes the frame.**

### What the GEM port DOES control

It picks which VLAN-membership row is consulted (in PP_BRG ram) for ingress
ACL + egress flood mask computation. Since stock adds all 8 ports to
VLAN 0 with type 3 (both tagged + untagged), any GEM port 0..7 or 0x28..0x2f
sees the same VLAN-0 membership = "flood to all 8 ports". So `lan_up_port=4`
→ GEM 0x2c works identically to `lan_up_port=0` → GEM 0x28 in our case.

---

## Q2: Is FDB seed of self-MAC required? — NO

Three different MAC tables exist on this chip; stock seeds two of them
for the device's OWN MAC, neither of which is the bridge FDB:

| Table | Purpose | Stock writes own MAC? | Mainline replicates? |
|---|---|---|---|
| **NPP.SPA ONU MAC slots** (`npp_base + slot*8 + 0x120/0x124`, 16 slots) | "this MAC is local to ONU, route to CPU on RX" | ✓ `tm_set_onu_mac(slot, mac)` | ✓ `zx_register_cpu_mac` |
| **PP_PM ONU MAC RAM** (PP_PM indirect via `pp_pm_set_onu_mac_ram_info`) | duplicate of SPA table, used by PP classifier for dst-MAC filtering | ✓ in `tm_onu_mac_addr_set` | ✓ `zx_pp_pm_set_cpu_mac` |
| **PP_BRG_RAM bridge FDB** (PP[0x801c-0x8028] indirect) | learned per-port unicast forwarding | ✗ stock NEVER adds its own MAC here | ✓ but ADDITIVE — port=1 |
| **sbragRegTable secondary FDB** (PP[0x388814-0x388824] indirect) | shadow of PP_BRG_RAM for switch fabric egress lookup | ✗ stock NEVER adds own MAC here | ✓ but ADDITIVE |

The reason stock doesn't add own MAC to PP_BRG_RAM: **frames TO the device
own-MAC arrive from LAN, hit the MAC RX, get classified by PP_PM
(`pp_pm_set_onu_mac_ram_info`) as "for-local-CPU", and get trapped to the
CPU queue via QMG up_hw_trap.** They never need to traverse the
bridge-FDB. The bridge FDB is for LAN-to-LAN forwarding only.

Frames FROM the device own-MAC (CPU TX) go OUT via the UP ring. The
switch fabric uses **destination MAC** (the HOST's MAC, not ours) for the
egress port pick. The host MAC IS learned dynamically by stock as
incoming frames pass through PP_BRG learning (`mac learn:pbm %d vlan %d
mac ...` printk in pon_pp_brg_int). After the first ARP exchange the
host MAC sits in PP_BRG_RAM at port = whatever LAN it came in on, and
all subsequent device→host TXes get routed there.

### Mainline's two extra FDB seeds (lines 537, 655)

`zx_fdb_add(e, dev_addr, 0, 1)` at line 3307 and `zx_sbrag_add_mac` are
additive vs. stock. They don't hurt (the entry just sits there idle).
But they don't fix CPU egress either — the relevant routing decision is
on the **host's** MAC, not the device's own. **If you delete both calls
the behavior should be unchanged**; cleanup, not bugfix.

### What WOULD help: nothing on the FDB axis

Even seeding the host's MAC in PP_BRG_RAM at port 2 (LAN3) wouldn't help
the current symptom — because the current bug (UP/DN ring + post-kick
clear) prevents HW from emitting the frame to the fabric AT ALL. Once
the frame is emitted, ARP/flooding will populate the host-MAC entry
naturally.

---

## Q3: PP[0x2c] and PP[0x1a01c] are HW-locked — what does this mean?

### PP[0x2c] = pp_base + 0x2c

Stock `pon_init` at plat:8940 does:
```c
if (lan_up) pp_base[0x2c] |= 1 << (lan_up_port + 0x19);
```
For `lan_up_port=4` → bit 29.

Live stock dump: `PP[0x2c] = 0x106` (bits 1, 2, 8). **Bit 29 NOT set.**
This register's high bits are sticky-clear or write-locked
(`hw_write_lock_pattern_re.md` documents this). Stock writes it but the
write doesn't latch; stock works anyway. So we don't need to write it.

The actual meaning of `0x106` is the boot-default left in PP control RAM
by the chip cold-init; mainline correctly leaves this alone.

### PP[0x1a01c]: fpga_write_reg(0xe8007, val | (1 << (port + 0x19)))

`tm_set_pp_wan_cfg` writes this via the FPGA indirect-access window. For
`lan_up_port=4` it sets bit 29. The fpga index 0xe8007 = phys
`0x9239c01c` = PP+0x1c01c (NOT PP+0x1a01c — earlier docs had a typo).

Live stock: PP+0x1c01c value at capture: 0 (similar write-lock pattern
likely applies). Stock prints "after PON_PP_TM_CFG=0x..." — we don't have
that captured.

**Recommendation**: mainline should add the write
`writel(readl(pp + 0x1c01c) | BIT(29), pp + 0x1c01c)` in `zx_tm_dma_init`.
Either it sticks and we get a free fix, or it's inert. Cost is one MMIO.

---

## Q4: What does the "encoded port" `(lan_up_port + 0x28) << 4 = 0x2c0` decode to?

**It decodes to "GEM port 0x2c" in the GPON Generic Encapsulation Method
addressing space.** It is NOT a physical port index. The +0x28 (=40)
offset is the start of the LAN-up virtual GEM range in stock's GPON SDK.

For the H3600's LAN-only mode (`g_pon_work_mode = 0x10`), `lan_up_port=4`
is the WAN logical port (the one ZTE designates as "uplink"). The mainline
hardcoded value of `port = 4` matches stock byte-for-byte. **Correct.**

There is NO encoding of "the destination LAN port" anywhere in the TX
desc. Egress port selection is done by the switch fabric via dst-MAC
lookup, AFTER the desc is consumed by the TM crossbar. For an ARP reply
to host on LAN3:
- Device's egress desc encodes `(4 + 0x28) = 0x2c` (LAN-up GEM ID).
- Switch fabric receives frame at virtual GEM-0x2c port.
- Classifier reads dst-MAC = host's MAC (already in PP_BRG_RAM
  after the host's earlier ARP request arrived).
- Egress decision: forward to LAN3 (= MAC[2]).

If host MAC is NOT yet in PP_BRG_RAM (cold ARP reply scenario), the
classifier floods: dst is broadcast OR unknown-unicast → all VLAN-0
members minus port-isolate mask minus CPU port = all 4 LAN ports get the
frame. Host receives via the LAN it's plugged into.

**So the +0x28 encoding is RIGHT for our case.** Don't tinker with it.

---

## Q5: sbragRegTable / sw_sbrag_* CPU forwarding entry

`sbragRegTable` is the second register-window descriptor table for the
PP_BRG block (sbrg = Secondary BRG). It's a 64-entry × 4-word indirect-
access table at PP[0x388814-0x388824]. Stock uses regs 0x4c/0x4d/0x4e
(=D0/D1/D2) to read/write 12-bit address × 3-word entries via
`sbrg_add_mactable` (tm.c:10706).

**No CPU forwarding entry exists** in sbragRegTable. The CPU forwarding
in stock is gated entirely by:
1. PP[0x81c0] SMAC_LOOK_EN bitmap, bit 5 = CPU port (stock sets 0xff =
   all 8 ports including CPU port 5; mainline replicates → `pp + 0x81c0`
   gets 0xff at line 2358).
2. PP[0x82c0] DA_LOOKUP_EN = 0xff (mainline ✓).
3. PP[0x8050] = 0xfffffffa (mainline writes this at line 2365, but live
   stock has 0x0a — partial clear after init).
4. PP_BRG VLAN-0 + VLAN-1 membership (mainline ✓ replicates at lines
   2387-2406).
5. PP[0x83c0-0x83dc] port-isolate mask (mainline ✓ writes 6 ports +
   forces 0xff on 6/7).

Mainline already does all of the above. The only thing that could be
wrong on the sbrag axis is the **hash function** for FDB lookup
(`zx_sbrg_hash` vs IBM-CRC), and even that doesn't matter because the
host MAC enters via auto-learning, which uses the same hash on both
write (learn) and read (lookup), so misalignment with stock is a no-op
as long as we're internally consistent.

---

## ROOT CAUSE (the wedge) — restated unambiguously

The "loopback drops" symptom + "no wire egress" + "HW consumes desc"
empirical state is fully explained by:

### Root cause A (highest confidence): wrong ring

```c
// mainline zx_sw_xmit (lines ~3146, 3197 in current state)
desc = (u8 *)e->dndesc_cpu + e->tx_head * TM_TX_DESC_SIZE;  /* DN ring */
...
tm_write(e, 0x10064, 1);                                     /* DN kick */
```

Stock for the "sw" netdev in LAN-only mode unambiguously uses:
```c
desc = (u8 *)e->txdesc_cpu + ...                              /* UP ring */
tm_write(e, 0x10054, 1);                                      /* UP kick */
```

The DN ring is meant for GPON downstream-line traffic (frames coming
DOWN from the GPON line that need to go to CPU or LAN). On a unit with
no PON link, the DN classifier hairpins back to CPU as loopback (because
no LAN port is configured as "GPON-downstream egress"). Result:
`tm_rx_loopback_drops++` per TX.

### Root cause B (high confidence): post-kick desc clear

The mainline post-kick `desc[11] &= ~0x20` to "prevent re-emission" is
defeating HW's asynchronous desc fetch. HW reads desc AFTER the kick
register write returns; if VALID is cleared first, HW skips the slot.
This is on the same code path as A — both must be fixed for either to
work.

### Root cause C (medium confidence, additive fix): missing PP[0x1c01c] BIT(29)

Stock writes this; mainline doesn't. Live readback shows 0 either way.
Could be write-locked (no-op) or could be a write-only side-effect
register. Cost to add: 1 MMIO. Benefit: possibly nothing, possibly
everything. Add it.

---

## Single most actionable fix

**Three-line patch in `zx_sw_xmit`**:

```c
// Line ~3146
desc = (u8 *)e->txdesc_cpu + e->tx_head * TM_TX_DESC_SIZE;  // was dndesc_cpu

// Line ~3197
tm_write(e, 0x10054, 1);  // UP kick, was 0x10064

// Delete the post-kick "desc[11] &= ~0x20" block (lines ~3211-3217)
```

Plus, in `zx_tm_dma_init` or `zx_pp_brg_init`, one extra line:

```c
writel(readl(pp + 0x1c01c) | BIT(29), pp + 0x1c01c);  // tm_set_p2pmode(4)
```

After this patch:
- HW consumes UP ring (TM[0x10054] kick).
- Desc VALID bit (0x21 at desc[11]) stays high until HW naturally clears
  it after consume.
- Frame egresses through UP→TM→PP_BRG path (the same path stock uses).
- PP_BRG runs FDB lookup on host MAC, routes to the LAN port host is on
  (via auto-learned host MAC from earlier ARP request).
- Host tcpdump sees the frame.

Loopback drops should go to zero.

---

## Confidence

- **HIGH** on A (UP vs DN ring): stock decomp `pon_tm_data_raw_send(...,
  dir=0)` → `soft_insert_tx_1desc(desc, 0)` → `TM[0x10054]` is
  unambiguous. The previous iter-32 switch to DN was a misinterpretation
  of "loopback drops" as "the desc went the wrong direction"; in fact
  loopback drops come from DN's classifier on a no-PON unit, which is
  the very wedge we're hitting.

- **HIGH** on B (post-kick clear): stock `pon_tm_data_raw_send` and
  `soft_insert_tx_1desc` have NO write to desc after the kick. HW owns
  the desc starting from the kick write. Clearing VALID is racy by
  construction.

- **MEDIUM** on C (PP[0x1c01c]): the live-stock readback of 0 suggests
  the write doesn't stick, but stock writes it 100% of init paths in
  `tm_set_p2pmode → tm_set_pp_wan_cfg`. Empirically harmless to add.

- **HIGH** on "FDB self-MAC seed not required": both stock and mainline
  RX paths trap own-MAC-destined frames via PP_PM (which IS populated
  with own MAC by `zx_register_cpu_mac` already). For TX, the relevant
  MAC is the host's, learned dynamically by auto-learn.

- **HIGH** on "GEM 0x2c is right, don't change": +0x28 offset is the
  LAN-up GEM range start; lan_up_port=4 maps to GEM 0x2c; this is the
  source ingress, not destination. Routing happens by dst-MAC FDB
  lookup downstream of the GEM classifier.

---

## Cross-references

- `tx_consume_engine_re.md` — prior pass; conclusions align with this doc.
- `lan_up_port_lifecycle.md` — `lan_up_port=4` setter/consumer chain.
- `mac_to_cpu_path_re.md` — RX path RE; section Q4 catalogs the
  candidate divergences (PP[0xc080] = 0x1000 vs 0x600 is worth
  re-validating with mainline live readback after the A+B fix).
- `hw_write_lock_pattern_re.md` — explains PP[0x2c] / PP[0x1c01c]
  write-lock behavior.
- mainline driver: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`.
- U-Boot equivalent (simpler reference): `tasks/00.10.03.re-uboot/
  findings/uboot_eth_decomp/FUN_40e50854.c` — uses UP ring, desc[0xc]=2,
  no 0xc9 marker, no post-kick clear; runs at L3 speeds end-to-end on
  same chip during TFTP.

---

## Lower-priority cleanups (don't fix the wedge but worth doing)

1. **Delete `zx_fdb_add(e, ndev->dev_addr, 0, 1)` at L3307** — stock
   never adds own MAC to bridge FDB; this entry just consumes a bucket.
   Cleanup, not bugfix.

2. **Delete `zx_sbrag_add_mac` for own MAC if it's called** (search shows
   it's defined but I didn't find a caller for own-MAC seed in current
   tree; verify and remove if dead).

3. **Re-verify PP[0xc080]** after A+B fix. Stock dump shows 0x600, our
   replay table likely writes 0x1000. This is the CLA control reg; could
   be the next gate AFTER ring-direction is fixed. Sub-investigation in
   `mac_to_cpu_path_re.md` Q4(c).

4. **Drop the `f4:f6:47:0f:42:64` self-MAC FDB cleanup at every netdev
   register** — same as #1 above, just in different code.

5. **dma_wmb() before `tm_write(e, 0x10054, 1)`** — already present, but
   verify ordering: desc bytes must hit DDR before the kick register
   write hits the bus. Current code looks OK with the existing dma_wmb()
   on line 3182.
