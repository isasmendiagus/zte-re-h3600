# ZX279128S ethernet/switch — HARDWARE BLOCK DIAGRAM (high-level)

A human-readable map of the ZTE ZX279128S ethernet + switch fabric: **where each block sits, how a
packet flows through it, and which physical address is which.** Companion to `DATASHEET.md` (register
detail). Built by consolidating the RE findings; confidence tags carry over (✅ verified /
🟡 inferred / ❓ unknown). All addresses are **absolute physical**.

> Two register windows overlap by offset (the "base gotcha"): `npp_base = 0x921c0000` and
> `tm_base = 0x92340000` (= npp+0x180000). Always read the absolute phys below, never a bare offset.
> Device is an ONU die but **copper-only** — the optical/GPON/serdes path is dead; ignore it.

---

## 1. THE FORWARDING DATAPATH (one packet's journey)

```
             ┌──────────────────────── SWITCH FABRIC = the "PP" (packet processor) ────────────────────────┐
  wire            ingress                                                                        egress          wire
   │                │                                                                              │             │
   ▼                ▼                                                                              ▼             ▼
┌──────┐  RX   ┌─────────┐   ┌────────┐   ┌────────┐   ┌────────┐   ┌────────┐   ┌────────┐        ...
│GePHY │──────▶│ SMAC[i] │──▶│  SPA   │──▶│  SDET  │──▶│  SADM  │──▶│  CLA   │──▶│  ADM   │──▶ (continued below)
│ RJ45 │       │ per-MAC │   │ parse/ │   │ frame  │   │per-sub │   │classify│   │CPU-que │
└──────┘       │ 0x9220k │   │classify│   │ detect │   │policer │   │/lookup │   │ policer│
  admit gate ──┤+i*0x40k │   │0x921d4 │   │0x921c4 │   │0x92384 │   │0x9238c │   │0x92394 │
  SOPC↔SMAC    └─────────┘   └────────┘   └────────┘   └────────┘   └───┬────┘   └────────┘
  0x921d9068                                               ┌────────────┘
                                                 lookup ── │ ── verdict = FORWARD or TRAP-to-CPU
                                                           │        (+ CPU-queue id from CLA ram7)
   (continued) ──▶┌────────┐   ┌────────┐   ┌──────────┐   │   ┌────────┐   ┌────────┐
                  │   PM   │──▶│  DPA   │──▶│  SBRAG /  │──▶│──▶│  RED   │──▶│  QMG   │── FORWARD ─┐
                  │ rewrite│   │DN parse│   │  PP_BRG   │   │   │congest.│   │ queue  │            │
                  │(NAT/L2)│   │0x92398 │   │ FDB/VLAN/ │   │   │ /WRED  │   │ mgr +  │            │
                  │0x9239c │   │        │   │ flood/iso │   │   │0x92344 │   │fwd/trap│            │
                  └────────┘   └────────┘   │ 0x92388   │   │   └────────┘   │0x9234c │            │
                                            └──────────┘   │                └───┬────┘            │
                                                           │                    │ TRAP            │
                                                           ▼                    ▼                 ▼
                                                    (CPU-trap branch, §2)   TM RX DMA        ┌────────┐
                                                                            ring→NAPI        │  DSCH  │  egress
                                                                                             │ /SCH   │  scheduler
                                                                                             │ shaper │  + shaping
                                                                                             │0x92354 │
                                                                                             └───┬────┘
                                                                                                 ▼
                                                                                          ┌────────────┐
                                                                                          │   SOPC     │ egress
                                                                                          │ crossbar   │ crossbar
                                                                                          │send2smacN  │→ MAC[N]
                                                                                          │0x921d915c..│
                                                                                          └─────┬──────┘
                                                                                    TX ┌────────▼───┐  ┌──────┐
                                                                                       │  SMAC[N]   │─▶│GePHY │─▶ wire
                                                                                       │  0x9220k.. │  │ RJ45 │
                                                                                       └────────────┘  └──────┘
```

Stage-by-stage (base address · role):

| # | block | base | role in the flow | conf |
|---|---|---|---|---|
| 1 | **GePHY** | MDIO `0x9a101000` (addr 10-13) + WAN ext ZX5201 @MDIO 0x08 | copper PHY (integrated for LAN0-3; external RGMII PHY for WAN) | ✅ |
| 2 | **SMAC[i]** (RX) | `0x92200000 + i*0x40000` | per-port ethernet MAC; RX-ok `+0x780`, TX-ok `+0x718`, ctrl `+0x00` | ✅ |
| — | **SOPC↔SMAC admit gate** | `0x921d9068` | RW `mac_rx_to_fabric_en[port]` (bit port) admits a MAC's RX into the fabric once `phy_mac_ready` (bit port+5) asserts | ✅ |
| 3 | **SPA** | `0x921d4000` | source-port parse/classify; `trap_dmac` table `0x921d41a0` traps "to-me" DMAC (action_rsn 0x3f) *before* CLA; per-uni RX `0x921d45cc`; verdict `0x921d45c4/c8` | ✅ |
| 4 | **SDET** | `0x921c4000` | per-uni frame-detect / min-max length / VLAN detect; transport+drop counters `0x921c4160+uni*4` | ✅ |
| 5 | **SADM** | `0x92384000` | per-subscriber/per-port admission policing — upstream of CLA per `queue_subsystem_re` §A (⚠ the older `mac_to_spa_admit_re` placed it after CLA — superseded); either way NOT a per-ingress-port gate | 🟡 |
| 6 | **CLA** | `0x9238c000` | **the classifier/ACL** — L3 5-tuple hash lookup → FORWARD (with PM slot via `cmd_flow_id`) or TRAP (with CPU-queue via ram7). HW hash engine `0x9238c2c0`; verdict counters `0x9238c3c0`(UP)/`c3cc`(DN) | ✅/🟡 |
| 7 | **ADM** | `0x92394000` | **per-CPU-queue PPS policer** on the trap path (`0x92394080/c0 +q*4`); drops excess trap pps before RED. Mainline inits none of it | ✅ |
| 8 | **PM** (packet-modifier) | `0x9239c000` | **HW NAT/rewrite**: SNAT/DNAT, DMAC/SMAC set, TTL--, checksums. flow_info ram0 + next_hop ram1; fetch `ram0[cmd_flow_id\|dir<<10]` | ✅ |
| 9 | **DPA** | `0x92398000` | downstream (WAN→LAN) protocol parse; per-port aly-en `[12:6]`; verdict `0x9239810c` | ✅ |
| 10 | **SBRAG / PP_BRG** | `0x92388000` | L2 bridge: FDB learn/lookup, VLAN check, flood/bcast, port isolation `0x923883c0+regport*4` | ✅ |
| 11 | **RED** | `0x92344000` | random-early-detect / WRED congestion drop; per-queue out-buffer (0x400 = 1024 trap latch); trap in/out `0x92344208/214` | 🟡 |
| 12 | **QMG** | `0x9234c000` | **queue manager — the forward-vs-trap bookkeeping**; DN sw/hw/trap `0x9234c044/48/4c` (trap pins at 1024 = the wedge), UP `0x9234c054/5c/60` | ✅ |
| 13 | **DSCH / SCH** | `0x92354000` | egress token-bucket shaper + DWRR scheduler (UP + DN RAMID table sets); indirect `0x92354014` | ✅ |
| 14 | **SOPC** | `0x921d9000` | egress crossbar → physical MAC[N]; `send2smac0..4` at `0x921d915c..0x921d916c` | ✅ |
| 15 | **SMAC[N]** (TX) | `0x92200000 + N*0x40000` | egress MAC → GePHY → wire | ✅ |

Per-stage **drop counters** live together at **`0x921da000`**: `drop_PP 0x40` (forwarding/policy),
`drop_RED 0x44` (the wedge-correlated one — ⚠ its association with the RED *block* is UNCONFIRMED:
disabling RED didn't stop it; see the DATASHEET drop-counter note), `drop_DSCH 0x4c` (egress-sched).

---

## 2. THE CPU-TRAP BRANCH (miss / setup / control → CPU) and CPU-INJECT TX (back out)

```
 ─── TRAP (from QMG verdict, §1) ────────────────────────────────────────────────────────────┐
   CLA lookup-miss / to-me / broadcast / control  →  ptype(action_rsn)  →  CLA ram7 → CPU queue (0..7)
                                                                                               │
        ADM per-queue PPS cap (0x92394000) ── drop excess ──▶ (never charges RED)              │
                                                                                               ▼
                                                    RED (0x92344000) ─▶ QMG (0x9234c000) ─▶ TM RX DMA ring
                                                                                               │
                                                                       ring-pending TM[0x10100+q*4]
                                                                                               ▼
                                                                        SIPC (0x921cc000) → CPU  → NAPI (weight 512)
                                                                        cpu_up_en 0x921cc000       linux netstack

 ─── CPU-INJECT TX (sw / idm netdev → wire) ──────────────────────────────────────────────────┐
   CPU builds skb → SIPC (0x921cc000) credit → TM TX DMA ring (0x92350000: UP base +0x50 kick  │
   +0x54 consume +0x58 ; DN base +0x60 kick +0x64 consume +0x68)                               │
        │  desc egress-port hint desc[2:3] = ((port+0x28)&0x3f)<<4                              │
        ▼                                                                                       │
   QMG (0x9234c000) → RED → DSCH/SCH (0x92354000) → SOPC send2smacN (0x921d915c..) → SMAC[N] TX → wire
```

Notes:
- The **CPU reaches the fabric via SW_AXI/APB**, not through a MAC (vendor brief). So CPU→LAN =
  CPU → TM-ring → QMG → … → SOPC → SMAC → GePHY → RJ45.
- **IDM** (`0x921c8000`) is the CPU-port DMA engine for the `idm0/idm1` netdevs (WiFi forward path);
  **BMU** (`0x92348000` = TM[0x8000], 5 instances at +0x400 — ⚠ corrected 2026-07-04: the old
  "0x921c8000, overlaps IDM low" claim was itself a base-gotcha; npp+0x8000 is IDM) is the
  buffer-pointer pool. **SMCT** (`0x921d0000`) = CPU-port multi-channel transfer gauges.
- Trap-latch reminder: `drop_RED` (`0x921da044`) ≈100k + `QMG DN hw_trap` (`0x9234c04c`) pinned at
  1024 = the reboot-only churn wedge; the ADM per-queue policer is the prescribed fix.

---

## 3. PORTS / "PINS" / CONNECTORS — physical jack ↔ netdev ↔ MAC ↔ numbering

### 3a. The five external ethernet ports (what a cable plugs into)
```
  RJ45 J0 ── GePHY0 ─(GMII/MII)─ MAC0 0x92200000 ── lan0 (DSA user port 0)
  RJ45 J1 ── GePHY1 ─(MII)────── MAC1 0x92240000 ── lan1 (DSA user port 1)
  RJ45 J2 ── GePHY2 ─(MII)────── MAC2 0x92280000 ── lan2 (DSA user port 2)   ← host/client cabled here
  RJ45 J3 ── GePHY3 ─(MII)────── MAC3 0x922c0000 ── lan3 (DSA user port 3)
  RJ45 J4 ── ZX5201 ─(RGMII)──── MAC4 0x92300000 ── lan4 = WAN (DSA user port 4, un-bridged L3 uplink)
                     ext PHY @MDIO 0x08
```
**MAC address rule:** `MAC[i] = npp_base + (i+1)*0x40000` (npp_base = `0x921c0000`). So MAC0=0x92200000
… MAC4=**0x92300000**. ⚠ `0x92340000` is the TM block, NOT MAC4 (the classic off-by-0x40000 trap).
Per-MAC: ctrl `+0x00`, TX-ok `+0x718`, RX-ok `+0x780`.

### 3b. Port-numbering spaces — EACH BLOCK USES A DIFFERENT ONE (the #1 poke footgun)
Logical **port1** = greg/phys **1** = **regport 2** = uni **1** = phys-MAC **1**. Get the space wrong
and the register write silently hits a different port.

| physical | netdev | MAC index | **logical** (DSA) | **regport** | **uni** | jack |
|---|---|---|---|---|---|---|
| LAN0 | lan0 | 0 (0x92200000) | 0 | 1 | 0 | J0 |
| LAN1 | lan1 | 1 (0x92240000) | 1 | 2 | 1 | J1 |
| LAN2 | lan2 | 2 (0x92280000) | 2 | 3 | 2 | J2 (host) |
| LAN3 | lan3 | 3 (0x922c0000) | 3 | 4 | 3 | J3 |
| WAN  | lan4 | 4 (0x92300000) | 4 | **5** (`ZX_WAN_REGPORT`) | 4 | J4 |
| CPU / conduit | sw | — | 5 | 0 | — | (SW_AXI/APB) |
| PON | — | — | (6→5 in greg var-A) | 6 | — | fiber (dead) |
| WLAN / IDM | idm0/idm1 | — | 7 | 7 | — | internal |

Which block uses which space (definitive, from `zte-port-numbering` / `port_numbering_map_re`):

| space | used by | logical port1 = |
|---|---|---|
| **phys-MAC index** | SMAC counters, `mac_off=(port+1)*0x40000`, TX egress-hint `((p+0x28)&0x3f)<<4` | 1 |
| **uni = logical** | SPA rcv_uni, SDET per-uni (`0x921c4160+uni*4`), RX-desc ingress `(desc[6]>>3&0x1f)-1` | 1 |
| **regport** `{1,2,3,4,5,0,6,7}` | PP_BRG isolation (`0x923883c0+regport*4`), FDB D2 bitmap, CLA inport (ram2-6) | **2** |
| **greg identity** (variant A) | greg/STP/`port_closed` (`0x921c0044`); CPU logical5 rejected; `6→5, 7→6` | 1 |
| **raw logical** | PM in/out-port rules (`0x921e0180/01a0 + i*4`, value stored = i) | 1 |

- Two decomp `getPort` remaps exist: **variant A** (greg, identity for LAN0-3, CPU rejected) and
  **variant B** (`{1,2,3,4,5,0,6,7}` regport). They are NOT the same table.
- The DSA driver uses **identity** (`zx_phys_port`) for greg and **regport** (`zx_regport[]`) for
  isolation/FDB — correct for LAN ports; guarded so CPU (logical 5) never hits greg.
- **POKE GOTCHA:** poke isolation/CLA/FDB in **regport** (port1→2), but SPA/SDET/uni in **uni=logical**
  (port1→1). regport2 on a uni block would hit uni2 = logical port2.

### 3c. The internal / fabric ports
- **CPU / conduit ("sw" netdev)** = logical 5 / regport 0. The DSA conduit; all lan1-4 user-port
  CPU-TX funnels through it. The eth controller registers 3 netdevs (`sw`, `idm0`, `idm1`) — the DSA
  switch must anchor to the `sw` child node (`conduit {}`), not the parent, or RX demux breaks.
- **PON** = switch port 5 (in greg variant A the `6→5` slot) — fiber, **not populated** on this board.
- **WLAN / IDM** = internal ports 6/7, served by the IDM DMA engine (`0x921c8000`) and the
  `idm0/idm1` netdevs (WiFi forwarding).

---

## 4. WHERE THE MMIO WINDOWS LIVE (quick address orientation)

```
  0x92000000  pon / PON-MAC window  (fpga_read base *(0x92000000+id*4); NOT in the 2MiB dump)
  0x921c0000  npp_base ── datapath blocks:
              0x921c0000 greg/STP     0x921c4000 SDET      0x921c8000 IDM (BMU is in the tm window)
              0x921cc000 SIPC         0x921d0000 SMCT      0x921d4000 SPA
              0x921d8000 (U)OPC       0x921d9000 SOPC      0x921da000 drop counters
              0x921dc000 ✗ dead window (stale zx-dsa ZX_PM_PHYS — NOT the PM; see note below)
              0x921e0000 PM-G988 authorizer
              0x92200000..0x92300000  SMAC0..4 (stride 0x40000)
              0x92380000 PP ctrl      0x92384000 SADM      0x92388000 SBRAG/PP_BRG
              0x9238c000 CLA          0x92394000 ADM       0x92398000 DPA
              0x9239c000 PM (packet-modifier / NAT)        0x923a0000 PON-PP / ETH_TM2 mux
  0x92340000  tm_base (= npp+0x180000) ── traffic manager:
              0x92344000 RED          0x92348000 BMU (×5, +0x400)   0x9234c000 QMG
              0x92350000 TM DMA ring (UP+DN)               0x92354000 DSCH/SCH shaper
  0x9a101000  MDIO (LAN GePHY @10-13; WAN ext PHY @0x08)
  (out of dump) TOP_CRM 0x94000000 / sys_ctrl 0x94100000 / pin_mux 0x94200000 / pon_serdes 0x9fe00000
```

✅ **PM base — RESOLVED (2026-07-04 verification):** the PM packet-modifier is at **`0x9239c000`**.
The validated conduit path is `e->base + 0x1DC014`, and `e->base` maps the "npp" DT window at
`0x921c0000` (zx-eth-main.c:7700) → CMD = phys `0x9239c014`. The `zx-dsa.c`
`ZX_PM_PHYS = 0x921dc000` (= npp+0x1c000 — no PM block lives there) is a **wrong constant**:
writes through that mapping were proven NOT to commit (readback-verify, word1 never lands — see
the comment block in `include/linux/dsa/zte.h`); the DSA binder therefore delegates all PM access
to the conduit via `zx_pm_ops`, keeping its local mapping only as a pr_warn'd fallback
(zx-dsa.c:689). Never use `0x921dc000`. See `DATASHEET.md` → "PP_PM = PM packet-modifier".

---

### Legend / cross-refs
✅ verified live/decomp · 🟡 inferred · ❓ unknown. Register detail: `DATASHEET.md`.
Primary findings: `queue_subsystem_re_2026-07-04`, `nat_offload_re_2026-07-03`,
`download_pm_rewrite_2026-07-04`, `up_hwoffload_2026-07-04`, `stock_red_drain_up_RE_2026-07-04`,
`counter_audit_2026-07-03`, `port_numbering_map_re`, memories `zte-datasheet`, `zte-port-numbering`,
`zte-cla-ram-layout`, `zte-cla-hw-hash-engine`, `zte-tx-egress-blocker`, `zte-dsa-foundation`,
`zte-redwedge-unicast-cpu`, `zte-flowoffload-framework`.
