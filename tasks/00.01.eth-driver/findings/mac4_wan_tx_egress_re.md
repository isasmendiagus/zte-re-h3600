# CPU→MAC4 (WAN/uplink) TX egress — why the frame stops after QMG DN sw_fwd

**Status: pure static RE of stock kmods (plat-zxylzb_9128S.ko, tm.ko) + mainline
zx-eth-main.c + a stock live register dump. 2026-06-04. No source/device changed.**

GOAL: CPU-originated frame to MAC4 (the WAN copper uplink; logical port 4 = regport 5)
reaches QMG **DN** `sw_fwd` (+6) with **zero** drops (PP/RED/DSCH all +0) but never reaches
MAC4's wire, while CPU→MAC0-3 (LAN) egress works. Find what stock does for MAC4 egress that
the LAN ports have and MAC4 doesn't, and the concrete mainline fix.

---

## TL;DR — the answer

The egress **path** is correct: the frame is software-forwarded, the egress-port **hint is
right** (MAC4 = desc hint **0x2c**, logical 4 — NOT regport 5), and the DN ring is the same
ring that LAN egress (eg=2) rides. Nothing drops it. **The frame stops because MAC4's
MAC↔fabric SOPC bridge + MAC enable are not held open**, so the SOPC crossbar has no live
egress endpoint to issue `send2smac4` to — exactly the "send2smacN stops once the transient
READY bit drops" failure mode the LAN keepalive already fixes, **but the keepalive explicitly
skips MAC4**.

Two concrete mainline gaps, in order of load-bearing-ness:

1. **`zx_mac_keepalive_fn` (eth-main:3314-3344) skips MAC4.** It gates each port on
   `if (!phy || !phy->link || !e->phy_was_link[i]) continue;`. MAC4's PHY is the external
   ZX5201 at MDIO 0x08 which phylib never probes, so **`e->gephy[4]==NULL`** (eth-main:379,
   4652) → `continue`. The keepalive is the loop that **re-asserts the READY-gated SOPC bridge
   enable (0x19068 bit4) and re-asserts MAC4 ctrl `|=3` every 100 ms**. For LAN ports this is
   the documented fix that keeps `send2smacN` firing after the transient READY bit drops
   (eth-main:3300-3302). MAC4 never gets that maintenance, so its bridge/enable lapse and
   `send2smac4` stops — frame sits at DN sw_fwd, no drop, no wire.

2. **`zx_eth_adjust_link`'s MAC4 (`is_wan`) bring-up only fires on a *LAN* PHY link event**
   (eth-main:4646-4664). MAC4 has no phylib PHY, so its `phy_was_link[4]` transition is
   piggy-backed on whatever LAN port fires `adjust_link`. If MAC4's bridge was enabled once
   there, gap #1 still lets it lapse; if no LAN link event fires after the WAN cable is up,
   MAC4 is never brought up at all.

Net: MAC4 egress is **DN-path** (same as LAN — UP vs DN is NOT the discriminator here; see §1),
the hint and ring are correct, and the missing piece is **keeping MAC4's SOPC↔MAC bridge +
MAC enable alive**, which the keepalive must include i=4.

---

## 1. UP vs DN — settled: WAN CPU-egress is the **DN** path, not UP

Stock `pon_tm_net_tx` (plat:6719) has two branches selected by the netdev's direction field
`dev+0x4c8` (set at `pon_tm_net_register(dir, name)`, plat:6398):

| netdev | `pon_tm_net_register` call | dir (`+0x4c8`) | ring | kick | hint source |
|---|---|---|---|---|---|
| **"sw"** (LAN/mgmt) | `(1, &_LC21)` plat:6955 | **1** | **DN** | `tm[0x10064]=1` | per-frame `src_port = skb->cb[0xb4]`, `(p+0x28)` |
| **"pon"** (PON/fiber uplink) | `(0, &_LC3)` plat:6960 | 0 | UP | `tm[0x10054]=1` | only when `lan_up==1`: `(lan_up_port+0x28)` = 0x2c |

- The **UP branch** (`dir==0`, plat:6741-6822) carries the `lan_up_port+0x28` (=0x2c) hint
  **only when `lan_up==1`** — and `lan_up==1` is the **fiber/p2p mode** (`g_pon_work_mode==0x10`,
  plat:8906-8907). On the **copper H3600 the WAN is electrical RGMII↔MDIO; `lan_up==0`**
  (wan_port_bringup_re.md §3). So the stock UP/"pon" path with the `lan_up_port` hint is the
  **GPON-fiber** uplink, NOT the copper-WAN egress. It is irrelevant to MAC4-copper.
- The **DN branch** (`dir==1`, plat:6832-6876): `pon_tm_get_next_txdesc(1)` → desc `[3]=3`,
  hint `(skb->cb[0xb4]+0x28)&0x3f << 4` → `pon_tm_data_raw_send(...,1)` →
  `soft_insert_tx_1desc(...,1)` → `tm[0x10064]=1` (plat:6242). This is the ONE software-forward
  egress path for **all** copper ports — LAN0-3 **and** copper MAC4. The egress port is chosen
  purely by the per-frame hint `src_port+0x28`; there is no per-port UP/DN split for copper.

**Conclusion:** the live observation (frame reaches QMG **DN** sw_fwd) is exactly stock-correct
for a copper-port egress. UP-vs-DN is a red herring for MAC4-copper. Mainline's dual-kick
(`tm[0x10054]` + `tm[0x10064]`, eth-main:3707-3708) already covers the DN kick.
(Candidate (a) "WAN must use UP" = REJECTED for copper.)

## 2. The egress-port hint — MAC4 = **0x2c** (logical 4), confirmed correct

`port_numbering_map_re.md §4`: logical 4 (WAN/MAC4) → **desc-egress hint `(4+0x28)&0x3f = 0x2c`**;
the hint space is the **phys-MAC index**, NOT regport. regport 5 would be `(5+0x28)=0x2d` and is
**wrong** for the egress hint. The DSA tagger emits eg=4 → `((4+0x28)&0x3f)<<4 = 0x2c0` in
desc[2:3] (zx_sw_xmit eth-main:3683; `zx_sw_xmit` reads `skb->data[1]`). **This matches stock's
phys-MAC-index hint exactly.** (Candidate (d) "uses regport 5 = 0x2d" = REJECTED.) Stock's own DN
hint is `src_port+0x28` in the same MAC-index space, and `desc[3]=3` (forward class) — mainline
sets `0x00010000` at desc+4 (desc[6]=1) but **does not set desc[3]=3**; this is a minor
divergence, not the egress gate (DSCH would drop, and it doesn't).

## 3. SCH/DSCH per-egress-port — NOT the gate, and not per-egress-port at all

- `zx_sch_init` (eth-main:2721-2771) replays stock `tm_pon_tm_sch_initial` — a per-**tcont/queue**
  (`0x20` units × 8 queues) **UP-path** token-bucket shaper (RAMID 2/3 per-queue, 5/6 per-tcont).
  It is **queue-indexed, not egress-port-indexed** (port_numbering_map_re.md row "QMG/RED/DSCH":
  "largely queue/credit indexed; no standalone QMG per-LOGICAL-port remap"). There is **no
  per-port TX scheduler/queue to set up for MAC4 vs LAN** — they share the same DN forwarding.
- Live proof it is not the gate: the user's measured `drop_DSCH (0x1a04c) +0`, `drop_RED +0`,
  `drop_PP +0` for the MAC4 frame. DSCH/SCH did **not** drop it. (Candidate (b) "SCH/DSCH port-4
  queue not set up" = REJECTED — the old "eg_port=4 → DSCH drops all" was a *no-link* port
  symptom; now WAN has L1 link so there is no DSCH drop, but also no egress endpoint.)

## 4. SOPC `send2smac4` — the actual gate is the MAC4↔fabric bridge + MAC enable

The SOPC crossbar (`0x921d9000`, `send2smac0..4` at `…915c..916c`; send2smac4 = `0x921d916c`)
emits a frame to MAC[N] **only if MAC[N] is a live fabric endpoint**. "Live" means:
- the **SOPC↔SMAC bridge** `NPP[0x19068]`: RO READY bit `(port+5)` asserted by the
  serializer/PHY-MAC bond, then SW sets enable bit `(port)`. For MAC4: READY = **bit 9**,
  enable = **bit 4** (DATASHEET:505-506; stock `smac_sopc_mode_switch` plat:2290-2305 does
  `0x19068+4 |= 1<<port` after polling `1<<(port+5)`).
- the **MAC4 datapath enable**: `MAC4 ctrl (0x..140000) |= 3` and ENABLE reg `0x80000001`
  (stock `pon_npp_smac_enable`, the FINAL step after the bridge handshake, plat:3198).

There is **no separate "send2smac4" egress-enable register** distinct from these — the SOPC
dispatch is gated by the same per-port bridge+MAC-enable that the RX-admit side uses. (Candidate
(c): the MAC4 egress is the SAME 0x19068 bridge + MAC enable, just maintained; there is no
extra egress-only mux to flip.)

**Live stock dump corroboration** (`regs/stock_eth_2mib.txt`, npp_base=0x92200000):

| reg | value | meaning |
|---|---|---|
| `0x92219068` (SOPC bridge `0x19068`) | `00000000` | all bridge bits 0 in this quiescent capture (READY is transient) |
| `0x92240000`/`8` (MAC0 ctrl/en) | `00bae000` / `80000001` | LAN0 live |
| `0x92280000`/`8` (MAC1) | `00bae000` / `80000001` | LAN1 live |
| `0x922c0000`/`8` (MAC2) | `00bae000` / `80000001` | LAN2 live |
| `0x92300000`/`8` (MAC3) | `00000000` / `00000000` | LAN3 down in this dump |
| **`0x92340000`/`8` (MAC4)** | **`00000140`** / **`00000000`** | **WAN ctrl is a DISTINCT small value (0x140, not 0xbae000) and ENABLE=0** |

The `0x19068` READY/enable being 0 in a static dump matches the prior live finding that the
bridge bit is **transient** — it is set on the link event then drops, which is *precisely* why
the LAN keepalive re-asserts it every 100 ms. MAC4 having ctrl=`0x140`/enable=0 here shows the
WAN MAC's enable is not held on the same way the active LAN MACs are.

## 5. Why the mainline frame stops (root cause synthesis)

```
CPU skb → zx_sw_xmit: eg=4 → desc[2:3]=0x2c0 (✓ correct MAC4 hint), DN ring, dual-kick (✓)
  → QMG DN sw_fwd (✓ +6, the live measurement)
  → SOPC: route to MAC4 via send2smac4
       ↳ requires MAC4 bridge (0x19068 bit4) + MAC4 ctrl|=3 enable to be LIVE
       ↳ adjust_link's is_wan path enables them ONCE (only on a LAN link event), and
       ↳ keepalive (the loop that HOLDS them up for LAN) SKIPS i=4 because gephy[4]==NULL
  → send2smac4 never fires → no DSCH/RED/PP drop (not congestion, not no-link) → no wire
```

This is the MAC4 analogue of the exact LAN failure documented at eth-main:3300-3302
("mainline sets the bridge once at link-up, then READY drops and send2smac2 stops") — the
keepalive solved it for LAN by re-asserting, and MAC4 was left out of that loop.

---

## 6. Concrete mainline driver change (zx-eth-main.c)

**Primary fix — include MAC4 in the keepalive (`zx_mac_keepalive_fn`, eth-main:3314):**
The loop must treat the WAN (i==4, `gephy[4]==NULL`) as an always-up fixed link, mirroring
`zx_eth_adjust_link`'s `is_wan` handling, instead of `continue`-ing on `!phy`:

```c
for (i = 0; i < 5; i++) {
    struct phy_device *phy = e->gephy[i];
    bool is_wan = (i == 4 && !phy);
    void __iomem *mc = e->base + mac_off(i, MAC_REG_CONTROL);
    void __iomem *br = e->base + 0x19068;
    u32 c, reg; int t;

    if (!is_wan && (!phy || !phy->link || !e->phy_was_link[i]))
        continue;
    if (is_wan && !e->phy_was_link[4])   /* only once MAC4 brought up */
        continue;

    c = readl(mc);
    if (is_wan || phy->speed == SPEED_1000)
        c = (c & ~0x8000u) | 0x2000u;    /* 1G/FD running ctrl */
    writel(c, mc);

    for (t = 0; t < 5; t++) {            /* re-assert READY-gated bridge bit i */
        reg = readl(br);
        if (reg & (1u << (i + 5))) { writel(reg | (1u << i), br); break; }
        udelay(50);
    }
    writel(readl(mc) | 0x3u, mc);        /* hold MAC enable */
}
```

**Secondary (ensure MAC4 gets brought up at all):** `zx_eth_adjust_link` already has the
`is_wan` path (eth-main:4657) that runs `zx_smac_init_port(4)` + config_speed_duplex(1G/FD) +
the 0x19068 bridge handshake (bit9 READY / bit4 enable) + MAC4 ctrl|=3. Confirm it actually
runs once after the WAN cable is up — it only fires when *some* LAN PHY link event invokes
`adjust_link`. If WAN must come up independent of LAN, drive `adjust_link` (or a one-shot WAN
bring-up) from `sw_open`/the WAN poller so `phy_was_link[4]` flips even with no LAN cable.

**Already correct (do NOT change):**
- The DN egress path + dual-kick (eth-main:3707-3708) and the egress hint encoding
  `((eg+0x28)&0x3f)<<4` with eg=4 → 0x2c0 (eth-main:3683). MAC4 hint is logical 4, not regport 5.
- `ZX_NUM_MACS=5` so `zx_smac_init_port(e,4)` runs at init (eth-main:233, 1342).
- Do NOT route copper-WAN egress to the UP ring / `lan_up_port` path — that is the **fiber**
  uplink (`g_pon_work_mode==0x10`, `lan_up==1`), absent on the copper H3600.

**Minor (optional, stock-faithful):** set `desc[3]=3` (forward class) in the DN desc for the
sw-forward path to fully match stock `pon_tm_net_tx` plat:6846; not the gate (no DSCH drop seen).

**READY-bit caveat (the real residual risk):** the fix above assumes MAC4's SOPC READY bit
(0x19068 **bit 9**) actually asserts — i.e. MAC4's serializer/RGMII bonds to the external ZX5201
PHY. This is the same kind of bond the LAN ports get from their GePHYs. If bit 9 never asserts
(WAN serializer not bonded), the bridge-enable write won't latch and send2smac4 still won't fire —
then the fix moves into the MAC4 serializer/`+0xe0` iface + `pon_reset(1<<(4+6))` bring-up
(`smac_init` plat:2272-2282; `extphy_timer_func` pon_reset pulse, wan_port_bringup_re.md §4b).
**Bench check before/after:** read `0x19068` under a WAN-egress flood — expect **bit 9 (READY)
set** and **bit 4 (enable) set**, and `send2smac4` (0x921d916c) + MAC4 TX-OK (0x92340714/718)
to climb. If bit 9 stays 0, the gate is the MAC4 serializer bond, not the bridge enable.

---

## Key citations
- stock: `decomp_all_plat_zxylzb_9128S.c` `pon_tm_net_tx`@6719 (UP/DN branches 6741/6832, hints
  6800/6848), `pon_tm_data_raw_send`@6596, `soft_insert_tx_1desc`@6232 (0x10054 UP / 0x10064 DN),
  `pon_tm_net_register`@6385 (dir@6398), `pon_tm_net_init`@6955/6960, `smac_init`@2272,
  `smac_sopc_mode_switch`@2290 (READY port+5 / enable port @2298-2300; 0x19038 duplex @2305).
- mainline: `zx-eth-main.c` `gephy[5]`@379 ("[4]=WAN … MDIO 0x08"), `ZX_NUM_MACS 5`@233,
  `zx_mac_keepalive_fn`@3307 (the `!phy continue`@3321 that skips MAC4; bridge re-assert@3333-3343),
  `zx_eth_adjust_link`@4641 (`is_wan`@4657, gephy[4]==NULL@4652, smac_init@4696, 0x19068
  handshake@4757-4803), `zx_sw_xmit`@3575 (hint@3683, dual-kick@3707), `zx_sch_init`@2721.
- DATASHEET.md: SOPC send2smac0..4 @227 (`0x921d916c`=smac4), `0x19068` bridge READY/enable
  @505-506, QMG sw_fwd 0x9234c044 @243, SCH @245. live `regs/stock_eth_2mib.txt`
  (0x92219068=0, MAC4 0x92340000=0x140/enable 0).
- findings: `wan_port_bringup_re.md` (MAC4=WAN, ZX5201@0x08, copper≠fiber, lan_up gate),
  `port_numbering_map_re.md` §4 (logical4→hint 0x2c, regport5), `stock_swfwd_egress_path_re.md`
  ("sw"→DN ring), `mac_to_spa_admit_re.md` / DATASHEET:510 (0x19068 transient READY),
  `dsch_drop_cpu_egress_re.md` (old no-link DSCH-drop, now superseded by L1-up no-drop).
