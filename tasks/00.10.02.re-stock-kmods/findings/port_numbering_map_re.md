# ZX279128S cross-block port-numbering map (DEFINITIVE)

**Status: static RE of stock decomp + mainline driver, cross-checked against live golden values. 2026-06-01.**

This SoC uses **at least four distinct port-index spaces**, and the same C variable named `port`
means different things in different blocks. This doc resolves, per switch block, which space it is
addressed by, the remap function applied, and the source citation. It then traces logical **port1**
through every block (the leading suspect for the silent port1 ingress drop).

---

## 0. The index spaces

| Space | Definition | LAN0..3 | CPU | Notes |
|---|---|---|---|---|
| **logical** (DSA) | DSA port id; what netdevs/DSA core use | 0,1,2,3 | 5 | LAN ports = 0..3, CPU = 5 |
| **greg/phys** (getPort variant A) | `tm_port_status_set` / STP / port_closed switch (decomp tm:37504, tm:37917) | 0,1,2,3 | (none) | `0→0 1→1 2→2 3→3 4→4 6→5 7→6`; **CPU logical 5 is REJECTED** (no greg slot). Identity for LAN0..3. |
| **regport** (getPort variant B) | `getPort @0x4f108` (tm:43494) + isolation + FDB | 1,2,3,4 | 0 | table `{1,2,3,4,5,0,6,7}`; CPU logical5→regport0. |
| **uni** | SDET / SPA per-uni counters; SDET `sdet_no` | 0,1,2,3 | — | `uni == logical` for LAN ports (LIVE-confirmed: uni1=port1, uni2=port2). SDET `sdet_no=param_1` (tm:24472) accepts 0..4 = logical. |
| **phys MAC index** | `SMAC[i]` window `e->base+(i+1)*0x40000`; `mac_off(port,off)=(port+1)*0x40000+off` | 0,1,2,3 | — | MAC[N] addressed by **raw logical** N (mac_off uses raw `port`, eth-main:408). smacRegTable stride 0x10000 dwords, port 0..4. |
| **desc egress hint** | TX desc[2:3] `((p+0x28)&0x3f)<<4` | — | — | `p` is a **MAC/phys egress port** value; `eg_port=2` LIVE = MAC2 = the cabled host (eth-main:3485). +0x28(=40) is the HW base offset. |
| **desc ingress decode** | RX `(desc[6]>>3 & 0x1f) - 1` | 0,1,2,3 | — | yields **uni/logical** ingress port (uni1=port1); -1 because field is 1-based (eth-main:2899). |
| **PHY/MDIO addr** | gephy0..3 | mdio 0x0a..0x0d | — | separate addressing, not a switch-fabric port space. |

The two "getPort" functions are the trap: **variant A** (greg, `…6→5 7→6`, CPU rejected) and
**variant B** (regport, `{1,2,3,4,5,0,6,7}`, CPU→0). They are NOT the same table.

---

## 1. THE TABLE — which space each block uses

| Block | Index space | Remap applied (logical→) | HW reg / encoding | Source citation |
|---|---|---|---|---|
| **greg / STP / port_closed** | **greg/phys (variant A)** | `0→0…4→4, 6→5, 7→6`; CPU logical5 **rejected** | reg-id = port + base (stp_en `+0x1d`, stp_state `+0x2b`, closed `+0x39`), written via gregRegTable | stock: `greg_set_port_closed` tm:22444 (`param_1+0x39`), `greg_set_port_stp_en` tm:22190 (`+0x1d`), `greg_set_port_stp_rstp_status` tm:22312 (`+0x2b`); caller remap `tm_port_status_set` tm:37504. mainline: `zx_phys_port`=IDENTITY zx-dsa.c:103, greg ops zx-dsa.c:135-204 |
| **PP_BRG isolation** (0x923883c0 + p*4) | **regport** | `{1,2,3,4,5,0,6,7}` for BOTH slot index AND bit positions | byte = inverted allow-bitmap reshaped; slot = regport*4 | stock: `tm_port_isolate_set` switch tm:36297-36328 + `sbrg_set_isolate_pt_cfg`. mainline: `zx_tm_port_isolate_set` eth-main:2149, `zx_isolate_set` zx-dsa.c:390-402 (`zx_regport[]` for slot+bits) |
| **FDB / SBRAG (D2 bitmap)** | **regport** | `{1,2,3,4,5,0,6,7}`, then `BIT(regport)` | D2[7:0] = port bitmap in regport space | mainline: eth-main:689-692 (`port_remap`, `d2=BIT(regport)`); live-verified D2=0x08=BIT(3)=regport3=logical2. zx-dsa.c FDB uses identity addr (slot=CRC) but the **bitmap** must be regport. |
| **SPA per-uni receive** | **uni (=logical)** | identity | rcv_uniN sop/eop @ `0x921D45CC + N*4` (byte-packed) | findings port1_sdet_ingress_gate_re.md:32,120,186; DATASHEET:489. SPA `pkt_en` bitmaps (0x14000/04/08) are per-ENTRY (rule), NOT per-port. |
| **SDET per-uni admit** | **uni (=logical)** | identity (`sdet_no = port`) | maxframe: reg-id=port (tm:24492); port0=`0x921C4000[29:16]`, **port1=`0x921C4250[13:0]`**, port2 same word[29:16] | stock: `sdet_set_maxframe_length(sdet_no=param_1)` tm:24472,24492; `tm_pon_npp_sdet_initial` loops 0..4. counters `0x921C4160+uni*4` (uni=logical). DATASHEET:415-421 |
| **SMAC RX-ok / wire counters** | **phys MAC index (=raw logical)** | identity | `0x92200000 + N*0x40000 + off` (RX pkt +0x780, RX byte +0x784, TX +0x714/718) | smac_real_counters_re.md (smacRegTable stride 0x10000 dw, port 0..4); mainline `mac_off` eth-main:408 uses raw `port` |
| **CLA inport field** | **regport** | `{0,1,2,3}→{1,2,3,4}` | hash-table (ram2-6) inport value; ram1 inport_mask is a flag | cla_ram_layout_re.md:22,30 ("CLA inport = regport"); `sw_acl_setMtchInfo` inport@0x9e = switch port (decomp_all_switch.c:1035). regport2 = logical port1. |
| **QMG / RED / DSCH** | **regport** (port-keyed paths) / shared | regport where per-port; many are queue-indexed not port-indexed | sw_fwd / hw_trap not per-port addressable for discrimination | DSCH/QMG are largely queue/credit indexed; per-port forwarding decisions inherit the isolation+FDB regport bitmaps. (No standalone QMG per-LOGICAL-port remap found.) |
| **PM in-port rule** | **logical/raw** | identity (raw value 0..7 stored) | `pm_set_in_port_rule_valid`: `tmOnuRegWrite(reg=6, val=port|valid<<3, sub=cfg_num)`; init `0x20180+i*4 = i` | stock tm:23061-23077; pm_spa_init_recipe_re.md:132 (`0x20180+i*4=i`) |
| **PM out-port rule** | **logical/raw** | identity (raw value 0..7 stored) | `pm_set_out_port_rule_valid`: `tmOnuRegWrite(reg=7, val=port|valid<<3, sub=cfg_num)`; init `0x201a0+i*4 = i`, then idx0 `=0x08` | stock tm:23147-23163; pm_spa_init_recipe_re.md:133,135 |
| **desc egress-port hint** | **phys MAC index** | none (raw MAC port + 0x28 base) | desc[2:3] = `((p+0x28)&0x3f)<<4` | stock pon_tm_net_tx tx_path_stock_decomp.md:102 (`lan_up_port`); mainline eth-main:3485 (`eg`, default 2 = MAC2) |
| **desc ingress decode** | **uni (=logical)** | `-1` (1-based field) | `(desc[6]>>3 & 0x1f) - 1` | stock RE; mainline eth-main:2899; uni1=port1 confirmed via rx_per_ingress histogram |
| **PHY / MDIO** | **mdio addr** | gephy0..3 = 0x0a..0x0d | MDIO bus address | DATASHEET; not a fabric port space |

---

## 2. INCONSISTENCIES (driver vs HW/decomp)

### I-1. greg uses variant A, isolation/FDB/CLA use variant B — by design, NOT a bug
`zx_phys_port` (zx-dsa.c:103) is identity, used for greg STP/port_closed. This is **CORRECT**: stock
greg (`greg_set_port_closed` etc.) is fed by `tm_port_status_set`'s variant-A switch, which is identity
for LAN0..3 (`0→0…3→3`). The regport `{1,2,3,4,5,0,6,7}` table is ONLY for isolation (`zx_isolate_set`,
`zx_regport[]`) and the FDB D2 bitmap (`port_remap`). The driver correctly uses identity for greg and
regport for isolation/FDB. **No inconsistency for LAN ports.** ⚠️ The one gap: `zx_phys_port` is identity
even for CPU/internal ports (logical 5/6/7), where variant A would map 6→5, 7→6 and REJECT logical5.
The driver guards this by `if (port >= ZX_DSA_USER_PORTS) return;` (zx-dsa.c:142,156,170) so CPU never
reaches greg — safe, but the comment at zx-dsa.c:99-101 claiming the full remap is "TODO" is misleading:
for the 4 user ports the identity is already exactly right.

### I-2. SDET / SPA / SMAC / desc-ingress / desc-egress all use DIFFERENT spaces — driver indexes some by raw, which is right for these but masks the regport blocks
- SDET/SPA per-uni and SMAC counters use **logical/uni = raw port** → mainline's raw-port indexing
  (`mac_off(port)`, SDET `sdet_no=port`) is CORRECT.
- BUT the per-port admit *trap*/forwarding decisions live in **regport** (CLA inport, isolation). A
  diagnostic that reads SDET uni1 (logical) and an isolation/CLA entry "for port1" using regport must
  remember uni1 = logical1 = **regport2**. Conflating uni1 with regport1 (=logical0) would read the
  WRONG port's classifier state. This is the precise foot-gun the multiport hunt kept hitting.

### I-3. desc egress hint space ≠ logical
`eg_port` is a **phys MAC index**, not a logical/regport id. `eg_port=2` works because it selects MAC2
(the cabled host), NOT logical port 2. A future DSA tagger that puts a *logical* egress port into
`skb->data[1]` (eth-main:3412 `eg = skb->data[1]`) will mis-route unless the tagger emits the MAC/phys
index. ⚠️ **Latent bug for DSA TX**: the tag byte must be in the same +0x28 MAC-index space as the
standalone `zx_eg_port`, not a logical DSA port.

### I-4. mainline never initializes SDET/SPA per-uni init in the stock order
Not a numbering bug per se, but the omitted `tm_pon_npp_sdet_initial`/full SPA loop means the per-uni
(logical) admit state is left at reset. Relevant to port1 only insofar as the live trace shows the drop
is upstream of SDET (see §3).

---

## 3. PORT1 TRACED THROUGH EVERY BLOCK

Logical **port1** = greg/phys **1** = regport **2** = uni **1** = phys MAC **1** = desc-ingress decode **1**.

| Block | port1 lands at | Verdict for the silent drop |
|---|---|---|
| PHY/MDIO | mdio 0x0b (gephy1) | OK — PHY[1] negotiates 1G/FD/an_done (multiport_root_cause:67) |
| SMAC RX (phys MAC1) | `0x92240000+0x780/784` | OK — MAC1 RX-ok climbs with CLEAN frames, 0 CRC/align (multiport:156) |
| **SPA per-uni rcv (uni1)** | `0x921D45CC` low region | **SUSPECT — uni1 region low while uni2/3≈229/230** (port1_sdet:186). Frames don't reach SDET. |
| **SDET per-uni (uni1)** | `0x921C4164` (and maxframe `0x921C4250[13:0]`) | uni1 transport=2 (vs uni2/3=229/230), drop=0 → NOT dropped at SDET; they don't ARRIVE (port1_sdet:183). maxframe word reads correct stock value. |
| CLA inport (regport2) | ram2 addrs 0x21/0x93/0x121 | NOT the gate — regport2 entries valid + action-identical to working regport3 (clapeek live; cla_ram_layout_re.md:30-35). Downstream of the drop. |
| isolation (regport2 slot) | `0x923883c8` | identical to working ports (multiport:116) |
| PM in/out-port (logical1) | rule value 1 | stock & mainline both `{0,1,2,3,4,5}` (multiport:116) — identical |
| SIPC/SMCT (shared) | not per-port | drop=0; shared block cannot discriminate port1 (multiport:133) |
| desc-ingress decode | would emit 1 | rx_per_ingress[port1]=0 — nothing ever decodes to port1 (multiport:146) |

**Conclusion on the port1 hypothesis:** No block MIS-MAPS port1 in a way that silently drops it — the
numbering is internally consistent (uni1=logical1, regport2, MAC1 all correctly the same physical port,
and the driver indexes each block in the right space for LAN ports). The live evidence localizes the
drop to the **MAC1→SPA admit stage** (SPA rcv_uni1 low, SDET uni1 transport≈2): frames reach MAC1 clean
but are not admitted into the fabric. Because SPA per-uni *receive* is indexed by **uni=logical** (not
regport), and the per-ENTRY SPA pkt_en bitmaps are portless, the most likely remaining mechanism is NOT
a wrong-index write but either (a) a per-uni SPA receive/admit field for uni1 left in a bad state
(mainline skips the full stock SPA per-uni init), or (b) a silicon/dynamic quirk on uni1's admit FIFO.

⚠️ **The one numbering trap that could still bite a fix:** any new code that "enables port1" by writing
an **isolation/CLA/regport** register must use **regport 2**, while a fix that pokes **SPA/SDET per-uni**
state must use **uni/logical 1**. Using logical-1 on a regport block (hitting regport1=logical0) or
regport-2 on a uni block (hitting uni2=logical2) would target the wrong port and look like "no effect" —
exactly the pattern seen during the hunt. This cross-space mismatch is the residual risk, even though no
*existing* block is provably mis-mapping port1.

---

## 4. Quick reference: logical → every space

| logical | greg/phys | regport | uni | phys MAC | desc-egress (p+0x28) | role |
|---|---|---|---|---|---|---|
| 0 (LAN0) | 0 | 1 | 0 | 0 | 0x28 | user |
| 1 (LAN1) | 1 | 2 | 1 | 1 | 0x29 | user |
| 2 (LAN2) | 2 | 3 | 2 | 2 | 0x2a | user |
| 3 (LAN3) | 3 | 4 | 3 | 3 | 0x2b | user |
| 4 (WAN/PON) | 4 | 5 | 4 | 4 | 0x2c | uplink |
| 5 (CPU) | — (rejected) | 0 | — | — | — | CPU |
| 6 (internal) | 5 | 6 | — | — | — | internal |
| 7 (internal) | 6 | 7 | — | — | — | internal |

---

## Key references
- mainline: `zx-dsa.c:48` (`zx_regport`), `:103` (`zx_phys_port`=identity), `:390` (`zx_isolate_set`),
  `:135-204` (greg ops). `zx-eth-main.c:408` (`mac_off`), `:689` (`port_remap`), `:2149`
  (`zx_tm_port_isolate_set`), `:2899` (RX ingress decode), `:3485` (TX egress hint).
- stock: `decomp_all_tm.c` `tm_port_isolate_set@36297`, `getPort@43494` (regport variant B),
  `greg_set_port_closed@22444`/`stp_en@22190`/`tm_port_status_set@37504` (greg variant A),
  `sdet_set_maxframe_length@24472`, `spa_set_up_reg_pkt_en@26269`, `pm_set_in_port_rule_valid@23061`,
  `pm_set_out_port_rule_valid@23147`, `tm_pon_npp_spa_initial@43269`.
- findings: `cla_ram_layout_re.md`, `smac_real_counters_re.md`, `pm_spa_init_recipe_re.md`,
  `tx_path_stock_decomp.md`, `cpu_source_port_egress_re.md:176`,
  `00.01.eth-driver/findings/{port1_sdet_ingress_gate_re,multiport_root_cause_macinit}.md`,
  `DATASHEET.md:247` (Port numbering), `:415-421` (SDET per-uni).
</content>
</invoke>
