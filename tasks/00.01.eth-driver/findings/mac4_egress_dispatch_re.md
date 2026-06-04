# MAC4 (WAN) egress dispatch — QMG-DN-sw_fwd → which-MAC selection, and why MAC4 stops

**Status: pure static RE of stock kmods (tm.ko, plat-zxylzb_9128S.ko) + mainline zx-eth-main.c +
the live stock register dump + the project egress memory. 2026-06-04. No source/device changed.**

SHARPENED PROBLEM (supersedes `mac4_wan_tx_egress_re.md`'s SOPC-bridge conclusion, now DISPROVEN
as the gate): a CPU frame to MAC4 reaches **QMG DN sw_fwd** (+6) and **tm_tx** (+6) with the SOPC
bridge held open (0x921d9068 bit4 set, READY bit9 set) and **zero** drops (PP/RED/DSCH all +0),
yet `send2smac4` never fires and the frame never hits MAC4's wire. CPU→MAC0-3 (LAN) egress works
on the same path. Find the QMG-DN-sw_fwd → dispatch → MAC4 gap and the concrete fix.

---

## TL;DR — the answer (and it is NOT a missing per-egress-port DN dispatch table)

1. **There is no per-egress-port "DN dispatch map" that lists MAC0-3 but excludes MAC4.** The
   dispatch to a specific MAC is **purely the TX-descriptor egress-port hint** `desc[2:3] =
   ((eg+0x28)&0x3f)<<4` (MAC4 → 0x2c0). Every stock TM/PP/NPP init block that touches per-port
   state **loops 0..4 (5 MACs) or 0..7 (8 fabric ports)** and includes MAC4 identically — SDET,
   SOPC crc_pad, SMAC tsf, SCH shaper (queue-indexed), RED (queue-indexed), QMG (global), the SBRG
   per-port forwarding (0..7). **MAC4 is excluded from NONE of them.** (§2, §3). So question (2)
   "is there a DSCH/QMG port-map configured for 0-3 but not 4?" → **NO. There is no such map.**

2. **`send2smacN` is a COUNTER, not a trigger.** It is the SOPC/OPC-ISSUE-stage per-port count of
   frames dispatched toward MAC[N] (`fpga_read_reg(0x76457+N)`). It increments **when the OPC issue
   stage selects port N from the frame's egress hint AND that egress endpoint is live/up**. The
   trigger is the descriptor hint + a *dynamic* per-port "egress endpoint up" condition — exactly
   the mechanism the LAN egress was SOLVED on (§4).

3. **The dispatch gate is the same dynamic per-port readiness that LAN egress hit — and for MAC4
   the missing piece is the WAN PHY's copper TX-driver, the ZX5201 analogue of the GePHY "TX-DAC
   force".** The project memory ([[zte-tx-egress-blocker]]) records LAN egress was solved by TWO
   changes: (a) `zx_eg_port=2` = direct the hint to a LINKED port (a no-link port → OPC/DSCH
   *drops*), and (b) **GePHY TX-DAC force-drive** in phy-zte-gephy.c (without it, MAC2 TX counted
   but copper was not driven → wire=0). MAC4's symptom — sw_fwd +N, **no drop**, no send2smac4 —
   is the "directed to a port the OPC will not issue to" case: the OPC silently does not dispatch
   (no drop counter) because MAC4 is not a *fully-up egress endpoint*. MAC4's PHY is the **external
   ZX5201 at MDIO 0x08**, NOT a zte-gephy, so the GePHY TX-DAC force does nothing for it; MAC4 needs
   its own `zx5201_config()` + power-up so the WAN copper TX is actually driven and the port reads
   as a live egress endpoint (§4, §5).

Net: MAC4 egress is the **DN path, hint-driven, same as LAN** (UP-vs-DN is a red herring for
copper — confirmed again, §1). The gap is **not** a QMG/DSCH port-map; it is **(i)** the descriptor
not being stamped with the full DN forward-class (`desc[3]=3`, mainline omits it) and **(ii)** the
MAC4 WAN-PHY copper TX driver / link not being brought up the GePHY-TX-DAC way, so the OPC issue
stage has no live MAC4 egress endpoint to count `send2smac4` against.

---

## 1. QMG-sw_fwd → MAC dispatch mechanism — what selects the dest MAC (TASK 1)

The DN egress datapath, end to end, with the stage that picks the MAC:

```
zx_sw_xmit/pon_tm_net_tx  → builds TX desc with egress-port HINT desc[2:3]=((eg+0x28)&0x3f)<<4
   → pon_tm_data_raw_send → soft_insert_tx_1desc → TM DN ring kick tm[0x10064]=1
   → QMG (0x9234c000): forward-vs-trap verdict → DN sw_fwd counter 0x9234c044 (+N)   [user sees this]
   → RED (0x923d1xxx): buffer-queue admission (no drop)
   → DSCH (0x92354000): per-queue/per-tcont DWRR dequeue → DSCH-in/DSCH-out
   → OPC ISSUE stage (SOPC, 0x921d8000/0x921d9000 block): reads the frame's resolved EGRESS PORT
       and emits send2smac[port] (0x76457+port) IFF MAC[port] is a live egress endpoint
   → SMAC[port] TX (smac "send total frame", smacRegTable stat 0x10) → PHY copper driver → wire
```

**The dest-MAC selector is the descriptor egress-port hint**, `desc[2:3]`. Stock builds it in two
places, both in the **phys-MAC index space** (NOT regport):
- DN sw-forward (`pon_tm_net_tx` DN branch, plat:6841-6848): `desc[0]=0x80`, **`desc[3]=3`**
  (DN forward-class, set only when `test_da_unknown==0`), `desc[2:3] |=
  ((skb->cb[0xb4]+0x28)&0x3f)<<4`. For port4 → **0x2c0**.
- UP path (`pon_tm_net_tx` UP branch, plat:6790-6800): hint `(lan_up_port+0x28)&0x3f)<<4` set **only
  when `lan_up==1`** (= GPON fiber mode). Copper H3600 has `lan_up==0` → UP path never stamps the
  WAN hint. **The UP/lan_up_port path is the FIBER uplink, irrelevant to copper MAC4** (§ confirmed
  again from wan_port_bringup_re.md §3 / plat:8906).

The OPC issue stage is **shared by all 5 MACs** and contains the `send2smac0..4` counters and the
`DSCH DROP` counter in **one** hardware unit (DATASHEET §3.21, addr 0x921d8000/0x921d9000). The
LAN-egress SOLVE proved the mechanism is hint-driven: setting the hint to the cabled port (eg=2)
made `send2smac2` climb and frames egress; setting it to a no-link port made `DSCH DROP` climb.

## 2. Is there a per-egress-port DN dispatch map for MAC0-3 but not MAC4? — NO (TASK 2)

Every per-port init in stock covers MAC4. Verified by reading each init function:

| stock init fn (tm.ko) | what it programs | port coverage |
|---|---|---|
| `tm_pon_npp_sdet_initial` (tm:43182) | `sdet_set_maxframe_length(i,0x3000)` | **loop i=0..4 (≠5)** — incl MAC4 |
| `tm_pon_npp_sopc_initial` (tm:43240) | `sopc_set_crc_pad_cfg(i,0)` then `opc_top_set_sp_rr_cfg(0)` | **loop i=0..4** — incl MAC4 |
| `tm_pon_npp_smac_initial` (tm:43422) | `smac_set_tsf_mode(i)` | **loop i=0..4** — incl MAC4 |
| `tm_initial` (tm:47123) | `smac_get_cfg(i)`/`smac_set_cfg(i)` | **loop i=0..4** — incl MAC4 |
| `tm_pon_pp_initial` (tm:43628) | `sbrg_set_pt_da_lookup_en(i,1)`, `sbrg_set_unknown_*_fwd(i,..)`, `sbrg_set_pt_tls(i,..)` | **loop i=0..7** — incl port4/5 |
| `tm_pon_tm_sch_initial` (tm:47023) | DWRR/sharp/age enables (global) + `tm_tcont_sharp_set(t)`/`tm_tcont_que_sharp_set(t,q)` | **per-tcont 0..0x1f × queue 0..7** — NOT port-indexed |
| `tm_pon_tm_red_initial` (tm:42487) | `red_set_out/in_buffer_queue_cfg(q,..)` | **per-queue 0..400** — NOT port-indexed |
| `tm_pon_tm_qmg_initial` (tm:42624) | `qmg_set_ext_ddr/ddr_cache`, ram_thd | **global** (ram_thd only if lan_up==1) |

There is **no QMG queue→port map, no DSCH per-egress-port enable, and no "downstream port list"**
that enumerates the egress MACs. The scheduler is **queue/tcont-indexed**; the forwarding tables
(SBRG) are **8-port** and include the uplink. **The "DN scheduler maps only to LAN MAC0-3"
hypothesis is REFUTED.** (Question 3 "UP vs DN for the uplink" → copper MAC4 egress is DN, like
LAN; there is no distinct UP-side or egress-mux for it.)

**The egress mux ETH_TM2 `0x923a00e0`** (DATASHEET:238) is NOT in the MAC4 egress path: it reads 0
on stock live too (`0x923a00e0=0` while stock egresses), is clock-gated under the kmod, and was
ruled out for LAN egress ([[zte-tx-egress-blocker]] 2026-05-29 "ETH_TM2 MUX RULED OUT"). Copper-WAN
egress does not route through it.

## 3. What stock programs for ALL 5 ports incl MAC4 (the per-port SOPC fields) (TASK 2 detail)

`tm_pon_npp_sopc_initial` sets only `crc_pad(0..4)` + `sp_rr`. The remaining per-port SOPC fields
have setters but **NO caller in any decomp module** — they sit at power-on defaults for ALL ports
(so they are not a per-port discriminator that MAC4 lacks):
- `sopc_set_smac_ready_mode(port,mode)` (tm:25782) — sopcRegTable **RAMID 7**, 2-bit field at
  `port<<1`. Validation accepts port==4. Uncalled.
- `sopc_set_smac_half_mode(port,mode)` (tm:25693) — RAMID 6. Uncalled.
- `sopc_set_smac_delay_cnt_cfg(cnt)` (tm:25633) — RAMID 5 (global). Uncalled.

So MAC4 differs from MAC0-3 in **none** of the static SOPC/OPC config. The only per-port,
dynamically-driven SOPC state is the `0x19068` bridge handshake (`smac_sopc_mode_switch`,
plat:2290) — and the user reports that is already held for MAC4.

## 4. send2smac4 — counter, and what makes the OPC issue FIRE it (TASK 4)

`send2smac4` is a **per-port COUNTER** read by the stats dumpers (`tm_dn_statistics_get` tm:46584,
`tm_switch_statistics_rx` tm:46650): `fpga_read_reg(0x7645b)` → **phys `0x921d916c`** (0x76457+4,
`phys=0x92000000+id*4`). `smacN send total frame` is a separate per-MAC TX counter
(`smac_get_statistics(N,0x10,..)` → smacRegTable stat 0x10, sub_idx=N).

`send2smac[port]` increments when the **OPC issue stage dequeues a frame and dispatches it to
port** = the descriptor's resolved egress port. The "good LAN boot" proved the firing condition:
hint→a LINKED port + that port's egress endpoint live ⇒ `send2smac2 +N`, `MAC2 TX +N`. The two
distinct failure signatures, both LAN-confirmed and now mapped onto MAC4:

| condition | DSCH DROP | send2smacN | matches | meaning |
|---|---|---|---|---|
| hint → **no-link** port | **+N** (0x921da04c) | 0 | old `eg_port=4` LAN | OPC refuses to issue, drops, counts the drop |
| hint → linked port, endpoint **not fully up** | **+0** | **0** | **user's MAC4 now** | OPC does not select/issue, frame backs up/idles, **no drop counter** |
| hint → linked port, endpoint up, copper **not driven** | +0 | **+N** | LAN before TX-DAC | dispatched + MAC TX counts, but **wire=0** |
| hint → linked port, endpoint up, copper driven | +0 | +N | **LAN SOLVED** | on the wire |

The user's MAC4 signature (sw_fwd +N, **all drops +0**, send2smac4 untested/0, smac4 RX 0) is row
2: the OPC has the frame queued but does **not issue** to MAC4, and because it is not a *drop* (the
port is not no-link — WAN has L1), no drop counter moves. The discriminator vs LAN is that MAC4's
**egress endpoint is not brought fully up the way the GePHY ports are** — specifically the WAN PHY
copper TX driver (the ZX5201, not a GePHY) is not driven, so MAC4 is not a "ready, link-up,
TX-driving" egress endpoint the OPC will issue to/that produces wire output.

## 5. Concrete fix — make a QMG-DN-sw_fwd frame dispatch to MAC4 (TASK 3 + 5)

The fix is the **MAC4 analogue of the two LAN-egress fixes**, plus a desc-faithfulness item. None
of these is a "QMG/DSCH port-map" — that does not exist.

**(a) Direct the hint to MAC4 only when MAC4 has link, and stamp the full DN forward-class.**
- `zx_sw_xmit` already stamps `desc[2:3]=((eg+0x28)&0x3f)<<4`; eg=4 → 0x2c0 is correct (phys-MAC
  index, NOT regport 5). Keep this.
- **Add `desc[3]=3`** (DN forward-class) to match stock `pon_tm_net_tx` DN branch (plat:6846).
  Mainline currently sets `desc[0]=0xc9` (UP marker) + `desc[6]=1` but leaves `desc[3]=0`. Stock's
  DN sw-forward uses `desc[0]=0x80` + `desc[3]=3`. This is the "forward, DA-known, use egress port"
  class; without it the OPC may treat the frame as DA-unknown and not honor the directed port.
  (Mainline tried a `desc[12:13]|=3` "DA-known" variant with marginal effect; the load-bearing
  field for the DN forward path is `desc[3]=3`.)

**(b) Bring MAC4's WAN copper TX driver up — the ZX5201 equivalent of the GePHY TX-DAC force.**
This is the actual gate. MAC4's PHY is **not** a zte-gephy, so the existing `phy-zte-gephy.c`
TX-DAC force does nothing for it. Port stock's WAN-PHY init so the WAN copper TX is driven:
- `zx5201_config()` (plat:3224) — the external dual-page PHY magic at MDIO **8/9**
  (full sequence in `wan_port_bringup_re.md` §2), then power-up
  `v=mdio_read(8,0); mdio_write(8,0, v|0x800)` (plat:3317).
- MAC4 link bring-up via `extphy_timer_func` (plat:3137, poll MDIO8 reg0x1a): on link →
  `smac_init(4)` + `config_speed_duplex(4,..)` + `smac_sopc_mode_switch(4,duplex)` +
  `pon_npp_smac_enable(4)` (MAC4 ctrl|=3). Mainline's `zx_eth_adjust_link is_wan` path already
  replicates most of this; the **WAN-PHY copper-driver init (zx5201_config) is the missing
  equivalent of the GePHY TX-DAC** that makes MAC4 a TX-driving endpoint.
- Include MAC4 (i==4, gephy[4]==NULL) in the keepalive so the bring-up/enable is held (per the
  prior finding §6) — necessary but, per the new evidence, **not sufficient alone**.

**(c) Do NOT route copper-WAN egress to the UP ring / lan_up_port path** — that is the fiber uplink
(`g_pon_work_mode==0x10`, `lan_up==1`), absent on copper.

**Verification sequence:** under a WAN-egress flood, expect to see, in order: QMG DN sw_fwd +N
(already), DSCH-in/out +N, **send2smac4 (0x921d916c) +N**, **MAC4 TX-ok +N**, then **wire**. If
send2smac4 stays 0 with no drop ⇒ OPC still not issuing (endpoint not up — chase (b)). If
send2smac4 climbs but wire=0 ⇒ exactly the pre-TX-DAC LAN state ⇒ the WAN copper driver (zx5201)
is the remaining gap. If DSCH DROP climbs ⇒ MAC4 is being treated as no-link (link/speed-duplex not
programmed into the egress side).

## 6. On-device-readable diagnostics — exact regs for pipeline_stats (TASK 5 detail)

All from the stock stats dumpers `tm_dn_statistics_get` (tm:46455) and `tm_switch_statistics_rx`
(tm:~46480), using the decomp-grounded conversion **`fpga_read_reg(id)` → phys = `0x92000000 +
id*4`** (DATASHEET:215). These resolve the pipeline_stats `send2smacN` "(TODO) need NPP_Sopc
per-port offset" stub:

### NPP_Sopc send2smacN per-port counters (the stub fill-in)
| counter | fpga id | **phys addr** |
|---|---|---|
| sopc_send2smac0 | 0x76457 | **0x921d915c** |
| sopc_send2smac1 | 0x76458 | **0x921d9160** |
| sopc_send2smac2 | 0x76459 | **0x921d9164** |
| sopc_send2smac3 | 0x7645a | **0x921d9168** |
| **sopc_send2smac4** | **0x7645b** | **0x921d916c** |

(stride = 4 bytes; base `send2smac[N] = 0x921d915c + N*4`. These are exactly the addresses the
[[zte-tx-egress-blocker]] memory cites for send2smac2=0x921d9164.)

### QMG / DSCH / RED / drop counters (DN pipeline)
| counter | fpga id | phys addr | notes |
|---|---|---|---|
| QMG sw_fwd (DN) | 0xd3011 | 0x923 4c044 → **0x9234c044** | user's "+6" reg |
| QMG hw_fwd | 0xd3012 | **0x9234c048** | |
| QMG hw_trap | 0xd3013 | **0x9234c04c** | |
| DSCH in-que | 0xd5080 (>>24) | **0x92354200** | byte field [31:24] |
| DSCH out-que | 0xd507f (<<16>>24) | **0x923541fc** | byte field [23:16] |
| RED fwd in / out | 0xd1081 / 0xd1084 | **0x923 44204 / 0x92344210** | |
| RED trap in / out | 0xd1082 / 0xd1085 | **0x92344208 / 0x92344214** | |
| RED drop in / out | 0xd1083 / 0xd1086 | **0x9234420c / 0x92344218** | |
| PP DROP | 0x76810 | **0x921da040** | OPC block |
| RED DROP | 0x76811 | **0x921da044** | OPC block |
| **DSCH DROP** | **0x76813** | **0x921da04c** | OPC block — the "no-link" drop |
| tcont_sch_active_ena | 0x76001 | **0x921d8004** | OPC issue enable (live=0x1=stock) |

### Per-MAC TX/RX (smacRegTable, sub_idx=port, MAC[i] base = npp+(i+1)*0x40000)
MAC4 window (live-confirmed in `mac4_wan_tx_egress_re.md`): **ctrl 0x92340000, enable 0x92340008,
TX-ok 0x92340718, RX-ok 0x92340780** (note: aliases the tm_base window — separate of_iomap;
base-gotcha per DATASHEET §3.11). `smacN send total frame` = `smac_get_statistics(N,0x10,..)`.
SOPC↔MAC bridge: **0x921d9068** (READY bit `port+5` → MAC4=bit9; enable bit `port` → MAC4=bit4).

**For pipeline_stats:** add `send2smac[N] = readl(npp_sopc + 0x915c + N*4)` where the SOPC sub-base
is npp+0x19000 (i.e. 0x921d9000), giving 0x921d915c+N*4. The existing debugfs regdump range
(~0x921c0100..0x921c0d00) cannot reach these — they live at 0x921d8000-0x921da0ff (OPC/SOPC),
0x92344000/0x9234c000/0x92354000 (RED/QMG/DSCH). Poke/peek those phys directly via the fpga tool
(`fpga -r <id>` with id=(phys-0x92000000)/4), e.g. send2smac4 = `fpga -r 0x7645b`.

---

## Key citations
- stock plat: `pon_tm_net_tx`@6719 (DN branch desc[3]=3 @6846, hint @6848; UP/lan_up @6790-6800),
  `pon_tm_data_raw_send`@6596, `soft_insert_tx_1desc`@6232 (0x10064 DN), `zx5201_config`@3224,
  `extphy_timer_func`@3137, `smac_sopc_mode_switch`@2290.
- stock tm: `tm_pon_npp_sopc_initial`@43240 (crc_pad 0..4 + sp_rr), `tm_pon_npp_sdet_initial`@43182
  (0..4), `tm_pon_npp_smac_initial`@43422 (0..4), `tm_initial`@47123 (smac cfg 0..4),
  `tm_pon_pp_initial`@43628 (sbrg per-port 0..7), `tm_pon_tm_sch_initial`@47023 (per-tcont/queue),
  `tm_pon_tm_red_initial`@42487 (per-queue), `tm_pon_tm_qmg_initial`@42624 (global),
  `sopc_set_smac_ready_mode`@25782 / `half_mode`@25693 / `delay_cnt`@25633 (uncalled),
  `send2smacN`/`tm_dn_statistics_get`@46455 (0x76457+), `tm_switch_statistics_rx`@46650,
  `smac_get_statistics`@21383 (stat 0x10), `qmg_get_statistics`@33036 (0xd3011 DN sw_fwd),
  `fpga_read_reg`@70019 (import thunk; phys=0x92000000+id*4 per DATASHEET:215).
- mainline: `zx_sw_xmit`@3586 (hint @3694, desc[0]=0xc9 @3690, NO desc[3]=3, dual-kick @3718),
  `zx_eth_adjust_link is_wan`, `zx_mac_keepalive_fn`.
- findings: `mac4_wan_tx_egress_re.md` (superseded SOPC-bridge conclusion), `wan_port_bringup_re.md`
  (MAC4=WAN, ZX5201@0x08, copper≠fiber), `port_numbering_map_re.md` §4 (logical4→hint 0x2c),
  `smct_channel_submit_re.md` (smct/dma map), DATASHEET §3.10/3.12/3.21 (QMG/DSCH/OPC).
- memory [[zte-tx-egress-blocker]]: LAN egress SOLVED 2026-05-30 = `zx_eg_port=2` (hint→linked
  port) + GePHY **TX-DAC force-drive** (both needed; MAC2 TX counted but wire=0 without TX-DAC);
  0x19068 ruled out (stock=0 while egressing); DSCH scheduler config fully ruled out; ETH_TM2 mux
  ruled out (stock=0).

---

## LIVE PEEK DIAGNOSTIC (Iter loop-3) — frame IS dispatched to MAC4; MAC4 TX doesn't reach the wire

Used the existing poke-debugfs one-arg PEEK to read the egress path during 8 lan4→host pings
(device on the zx5201_config + keepalive build):
- QMG DN sw_fwd (0x9234c044): 0x24→0x2a (+6)        — frame reaches QMG ✓
- DSCH in  (0x92354200): low byte 0x92→0x98 (+6)     — reaches DSCH ✓
- DSCH out (0x923541fc): 0x9200→0x9800 (+6)          — dispatched OUT of DSCH ✓
- **send2smac4 (0x921d916c): 0x15→0x1b (+6)**         — **the SOPC DISPATCHES to MAC4 ✓**
- **MAC4 TX-ok (0x92340718): 0x00→0x00 (UNCHANGED)**  — **MAC4 does NOT TX to the wire ✗**
  (caveat: MAC4 window 0x92340000 aliases tm_base — this counter read may be unreliable; but
   the host tcpdump seeing NOTHING corroborates "no wire TX".)

⟹ The whole fabric path WORKS (QMG → DSCH → SOPC send2smac4 all +6). The frame is handed to MAC4.
The gap is **MAC4 MAC-TX → RGMII → ZX5201 → copper** — MAC4 gets the frame but it never reaches the
wire. This is NOT a dispatch/SOPC/QMG problem (all confirmed working).

LEADING CAUSES for the next iteration:
1. **RGMII TX timing** — the 4 LAN MACs use internal MII/GMII (no clock delay); MAC4 uses RGMII to
   the external ZX5201, which needs TX/RX clock delay (2ns) on the MAC or PHY side. Mainline sets
   none. Find stock's RGMII delay config for MAC4 (MAC iface +0xe0 / a CRM/clock reg / a ZX5201 page).
2. **The CRM reg 0xf060000c** that stock's zx5201_config toggles (`&= 0xffe7f7ff`) around the PHY
   access — SKIPPED in our port (it's outside the eth ioremap window, ~PON CRM). May be the RGMII
   clock/delay enable. Needs a separate ioremap to set.
3. MAC4 iface reg +0xe0 (mac4+0xe0 = 0x00011200 from smac_init) — verify it's the RGMII iface value,
   not the internal-MII value the GePHY MACs use.
