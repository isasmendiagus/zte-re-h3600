# Undecoded pipeline counter registers — WAN-ingress (download / DN) loss localization

Date: 2026-07-03. Device-free static analysis (no device touched; a device experiment ran concurrently).
Sources: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` (`zx_pipeline_stats_show`), stock decomp
`tasks/00.10.02.re-stock-kmods/findings/{decomp_all_tm.c,decomp_all_switch.c}`, `DATASHEET.md`, memories
zte-flowoffload-framework / zte-datasheet / zte-cla-hw-hash-engine / zte-redwedge-unicast-cpu.

Address conventions:
- `phys = fpga_widx*4 + 0x92000000` (datasheet rule).
- `mem`-debugfs word offset (what the existing `dd skip=N count=… | od -An -tx4` scripts use, base = eth
  controller `e->base = 0x921c0000`): **`mem_woff = (phys - 0x921c0000)/4 = fpga_widx - 0x70000`**.
- ⚠ NEVER memdump MAC4 `0x92300000` (bus-hang). All reads here are in the SIPC/SPA/DPA/CLA/ADM/RED/QMG/SOPC
  windows, safe via `mem`/poke or by adding a `seq_printf` line to `zx_pipeline_stats`.

---

## HEADLINE FINDING (task deliverable (c)) — the driver reads the WRONG CLA counter bank for downloads

The CLA forward/trap/drop/copy counters are **split by direction into two banks**, proven by the two stock
dump functions:

| function (stock) | CLA fwd | CLA trap | CLA drop | CLA copy | QMG sw/hw-fwd/hw-trap |
|---|---|---|---|---|---|
| `tm_up_statistics_get` (UP = LAN→WAN, uploads) | `0x9238c3c0` | `0x9238c3c4` | `0x9238c3c8` | `0x9238c3d8` | `0x9234c054/5c/60` |
| `tm_dn_statistics_get` (DN = **WAN→LAN, downloads**) | **`0x9238c3cc`** | **`0x9238c3d0`** | **`0x9238c3d4`** | **`0x9238c3dc`** | `0x9234c044/48/4c` |

The mainline driver's `pipeline_stats` (`zx-eth-main.c:5521`) reads `CLA fwd[0x1cc3c0]` / `drop[0x1cc3c8]` /
`copy[0x1cc3d8]` — i.e. the **UP bank** — and the datasheet only documents the UP bank + `acl_required`
`0x9238c3b8` + the `desIn` latches. **The DN bank `0x9238c3cc/d0/d4/dc` is undocumented and never read.**
The driver DID get QMG right (it reads the DN QMG bank `0xc044/48/4c`), so its CLA/QMG pairing is
direction-inconsistent: DN QMG + UP CLA.

Consequence for the flow-offload investigation: every "authoritative" statement about the ~86% download
miss — `cla_tx_fwd 0x9238c3c0`, `cla_tx_trp 0x9238c3c4`, the l3_en decomposition
(`l3_en=1 = cla_tx_fwd+cla_tx_trp`, `l3_en=0 = QMG_DN_hw_trap − cla_tx_trp`) — was computed from the **UP**
CLA counters against the **DN** QMG counters. One memory note claims `0x9238c3c0 == QMG_DN_hw_fwd` held
empirically; that identity only requires `cla_fwd==qmg_dn_hw_fwd` and may have been coincidental (symmetric
UP traffic, or the counter aliases). **This must be settled by reading the DN bank directly.** Even if
`0x3c0` did track DN, the DN bank `0x3cc/d0/d4` is the authoritative, direction-correct measurement and has
never been looked at on mainline.

Zero-cost read: the existing wide dump `dd skip=471192 count=100 | od -An -tx4 -v` (skip 471192 = widx
`0xe3098` = `gparsehashkey 0x9238c260`; the scripts already label word 88=CFW/89=CTRP/98=desIn2) **already
contains the DN bank** — it is just unlabeled: within that same 100-word block,
**word 91 = cla_dn_fwd (0x9238c3cc), word 92 = cla_dn_trap (0x9238c3d0), word 93 = cla_dn_drop (0x9238c3d4),
word 95 = cla_dn_copy (0x9238c3dc)**. (mem_woff 471795/6/7/9 minus the 471192 skip = 91/92/93/95.)

---

## (a) FULL DN (download) pipeline counter map — defined vs undefined

Pipeline order per `tm_dn_statistics_get` (decomp_all_tm.c:46455), the exact download datapath
SIPC→SPA→PP_CTRL→SADM→CLA→ADM→PM→DPA→SBRG→RED→QMG→DSCH→SOPC→SMAC. "in driver?" = read+labeled by
`zx_pipeline_stats_show`.

| stage | counter(s) | fpga_widx | phys | mem_woff | in driver? |
|---|---|---|---|---|---|
| SIPC | cpu_short_drop / cpu_pkt_drop / sipc2cpu_aful_dn / sipc2cpu_ful_dn (bitfields) | 0x73001 | 0x921cc004 | 12289 | ~ raw only (driver prints `SIPC drop=0x…` undecoded) |
| SIPC | dn_cpu / PON0 / PON1 DROP_HPMAU | 0x73060/67/68 | 0x921cc180/19c/1a0 | 12384/407/408 | ✗ |
| SIPC | dn_cpu / PON0 / PON1 DROP_AFUL | 0x73070/77/78 | 0x921cc1c0/1dc/1e0 | 12480/503/504 | ✗ |
| SIPC | sipc_2spa sop / eop / drop | 0x73011 | 0x921cc044 | 12305 | ✗ |
| SPA | **before-vlan spa_fwd/drp/cpy/trp** (byte fields) | 0x75171 | **0x921d45c4** | 20849 | ✗ (driver reads per-uni `SPA_rcv 0x921d45cc`, not the verdicts) |
| SPA | **after-vlan spa_fwd/drp/cpy/trp** | 0x75172 | **0x921d45c8** | 20850 | ✗ |
| PP_CTRL | pp_ctrl_drop | 0xe0026 | 0x92380098 | 65574 | ✗ |
| SADM | pon pass pkt/uni/brd/multi | 0xe1080 | 0x92384200 | 66048 | ✗ (driver's `SADM pass[0x1c4200]`=**0x923a4200**, WRONG block) |
| SADM | pon drop pkt/uni/brd/multi | 0xe108a | 0x92384228 | 66058 | ✗ (driver's `0x1c4208`=0x923a4208, wrong) |
| **CLA (DN)** | **cla_dn_fwd** | 0xe30f3 | **0x9238c3cc** | 471795 | ✗ ★ |
| **CLA (DN)** | **cla_dn_trap** | 0xe30f4 | **0x9238c3d0** | 471796 | ✗ ★★ |
| **CLA (DN)** | **cla_dn_drop** | 0xe30f5 | **0x9238c3d4** | 471797 | ✗ ★ |
| **CLA (DN)** | cla_dn_copy | 0xe30f7 | 0x9238c3dc | 471799 | ✗ |
| ADM | adm drop (aggregate) | 0xe508b | 0x9239422c | 74795 | ✗ |
| PM (PP_PM) | pm recv | 0xe7022 | 0x9239c088 | 76066 | ✗ |
| PM | pm send | 0xe7020 | 0x9239c080 | 76064 | ✗ |
| PM | pm fwd [31:16] / **pm trap [15:0]** | 0xe7028 | 0x9239c0a0 | 76072 | ✗ ★ |
| **DPA (parse)** | **dpa_fwd/drp/cpy/trp** (byte fields: [31:24]/[23:16]/[15:8]/[7:0]) | 0xe6043 | **0x9239810c** | 483395 | ✗ ★★★ |
| SBRG | brg_rx / brg_tx | 0xe2300 | 0x92388c00 | 68099 | ✗ |
| RED | RED fwd in/out | 0xd1081/84 | 0x92344204/210 | 459777/780 | ✗ |
| RED | **RED trap in/out** | 0xd1082/85 | 0x92344208/214 | 459778/781 | ✗ ★ |
| RED | RED drop in/out | 0xd1083/86 | 0x9234420c/218 | 459779/782 | ✗ |
| QMG (DN) | sw fwd / hw fwd / hw trap | 0xd3011/12/13 | 0x9234c044/48/4c | 462865/6/7 | ✅ (driver "QMG DN …") |
| DSCH | DSCH in / out que | 0xd5080/507f | 0x92354200/1fc | 471168/167 | ✗ |
| SOPC | send2smac0..4 | 0x76457..b | 0x921d915c..6c | 25687.. | ✗ (driver marks TODO) |
| SOPC | PP DROP / RED DROP / DSCH DROP | 0x76810/11/13 | 0x921da040/44/4c | 26624/5/7 | ✅ (driver "drops PP/RED/DSCH") |
| SMAC | smacN send total frame (TX) | via `smac_get_statistics(N,0x10)` | MAC[N]+~0x718 | — | ~ (driver reads MAC+0x780 RX, not TX-send) |

Defined/OK on the download path today: smac RX (0x780..), SPA per-uni RX (0x921d45cc+), SDET
egress_transport (0x921c4160+), QMG DN+UP (0xc044/54 banks), SOPC PP/RED/DSCH drop (0x921da040/44/4c),
SIPC raw (0x921cc004). Everything marked ✗ above is undecoded/unread.

UP-direction extras (from `tm_up_statistics_get`) not on the DN path but useful for the LAN-ingress
control comparison: per-**UNI0..4** HPMAU/AFUL drop counters at widx `0x73061+` (`0x921cc184+`) — the only
genuinely **per-ingress-port** ingress-drop array in the design (DN side only has cpu/PON0/PON1).

---

## (b) RANKED shortlist to READ LIVE during a WAN download (what a climb means)

1. ★★★ **CLA DN bank — cla_dn_fwd 0x9238c3cc / cla_dn_trap 0x9238c3d0 / cla_dn_drop 0x9238c3d4**
   (mem words 91/92/93 of the existing `skip=471192 count=100` dump; or add three `seq_printf` lines).
   - `cla_dn_trap` climbs ≈ the ~86% ⇒ the download packets ARE reaching the CLA and trapping *in* the CLA
     lookup (LOOK_UP_MISS 0x54) — confirms VERDICT B, and means the UP-bank-based l3_en=0 story was an
     artifact of reading the wrong bank.
   - `cla_dn_trap` stays FLAT while `cla_dn_fwd` ≈ the ~14% and the missing ~86% shows up upstream (DPA/SPA
     below) ⇒ the download packets never reach the CLA (pre-CLA parse gate) — confirms the l3_en=0 /
     parse-arm hypothesis. Either way this bank *directly* localizes at/above vs in the CLA — the fork the
     concurrent `acl_required` experiment is chasing, measured on the correct direction.
   - Cross-check `cla_dn_fwd` vs QMG DN hw_fwd (0x9234c048): they should be equal if the CLA is the last
     word on forwarding; a gap means a post-CLA drop (ADM/PM/RED).

2. ★★★ **DPA parse verdict — dpa_fwd/drp/cpy/trp @ 0x9239810c** (byte fields [31:24]/[23:16]/[15:8]/[7:0];
   mem_woff 483395 — separate `dd skip=483395 count=1`). DPA = "downstream packet analysis" = the DN-side
   PARSE/analysis stage the task asked for.
   - `dpa_trp` (byte[7:0]) or `dpa_drp` (byte[23:16]) climbs with the ~86% ⇒ the loss is at the parse stage,
     BEFORE the CLA — pinpoints the l3_en=0 gate to DPA (the HW parse/analysis block, upstream of CLA and of
     the SPA pktdeal). This is the single most likely per-stage counter to reveal the WAN-ingress parse-fail.
   - `dpa_fwd` ≈ total while dpa_trp/drp ≈ 0 ⇒ parse is fine, loss is downstream (at the CLA — see #1).
   - Note DPA also owns `protocol_cpu_pps_en 0x92398014` (a CPU-punt gate) and the unknown enables
     `0x92398000[6:12]` — if dpa_trp implicates DPA, those enable bits are the next config to compare
     stock-vs-mainline.

3. ★★ **SPA classify verdict — before/after-vlan spa_fwd/drp/cpy/trp @ 0x921d45c4 / 0x921d45c8**
   (byte fields; mem_woff 20849/20850).
   - `spa_trp` climbs ⇒ trapped at the SPA parser (the pre-CLA UDF_DMAC0 0x3f "to-me" trap path). Splits
     the trap ladder: SPA-trap (very pre-CLA) vs DPA-trap vs CLA-trap. The pktdeal test already argued SPA
     proto-action isn't the gate, but this counts the SPA *trap verdict* directly — a cleaner exclusion.

4. ★★ **PM (PP_PM) — pm_trap 0x9239c0a0[15:0], plus pm_recv/send/fwd 0x9239c088/80/0x9239c0a0[31:16]**.
   - PM sits between CLA and RED. `pm_trap` climbing ⇒ a post-CLA / pre-QMG port-mapper trap; `pm_recv` vs
     `pm_send` gap ⇒ packets dropped inside the port-mapper. Localizes a loss that is neither parse nor CLA.

5. ★ **RED trap in/out @ 0x92344208 / 0x92344214** (+ RED drop 0x9234420c/218).
   - Directly relevant to the RED-wedge memory. `RED trap` climbing on the DN path ⇒ the loss is at RED/TM
     (the OPC/RED latch), not at classify. Distinguishes a TM-block wedge from a lookup miss.

6. ★ **SADM per-port drop @ 0x92384228 (pon) + uni0..4 0x9238422c/30/34/38/3c; pass @ 0x92384200+**
   (each entry byte-packs pkt/uni/brd/multi). SADM is *downstream* of the CLA, so it only counts packets
   that already passed the CLA — a climb here is a post-CLA admission/policing drop (exclusion; unlikely the
   ~86% but cheap). NB the driver's current `SADM pass/drop` prints `0x923a4200/08` which is the WRONG block
   — the real SADM counters are at `0x92384200/28`.

7. ★ **SIPC DN backpressure — DROP_HPMAU 0x921cc180/19c/1a0, DROP_AFUL 0x921cc1c0/1dc/1e0, sipc_2spa
   sop/eop/drop 0x921cc044**. Climb ⇒ buffer-full / almost-full backpressure drop at the CPU/PON ingress
   ring — a throughput/saturation signature rather than a classify miss (would corroborate or refute the
   already-refuted saturation hypothesis).

---

## (c) / task pt 4 — trap-REASON fork: there is NO per-reason histogram counter

Searched both decomp files: the trap reason exists only as the `desIn[2] action_rsn` latch
(`0x9238c3e8[29:23]`, one in-flight packet, shared/noisy — already known stale on #476) decoded through the
**string table `trapPktType[]`** (`(&trapPktType)[rsn]`, decomp_all_tm.c:64138/65712/66367/68001/68841). It
is a decode array, not a counter — **no per-reason (0x3f/0x54/0x49) count register exists.**

The per-stage TRAP verdict counters give the equivalent information without the noisy latch — a
"where did it trap" ladder that answers the exact pre-CLA vs in-CLA fork the `acl_required` experiment is
settling:

| observation during download | meaning | maps to reason |
|---|---|---|
| `spa_trp` (0x921d45c4/c8) climbs | trapped at SPA parser (to-me DMAC) | 0x3f UDF_DMAC0 — pre-CLA / L2 |
| `dpa_trp` (0x9239810c[7:0]) climbs | trapped at DN parse/analysis | pre-CLA parse (the l3_en=0 stage) |
| `cla_dn_trap` (0x9238c3d0) climbs | trapped inside the CLA hash lookup | 0x54 LOOK_UP_MISS — in-CLA |

Read all three during one download and the ~86% resolves to a stage. This is the direct, direction-correct
complement to the concurrent `acl_required 0x9238c3b8` fork-settler (note: `acl_required` is a single reg,
read only by the driver/tooling — neither stock up nor dn stats reads it; there is no DN-specific
`acl_required`, so it is direction-agnostic/UP-leaning and should be corroborated by `cla_dn_trap`).

Secondary reason-adjacent histogram that DOES exist (per-PROTOCOL, not per-trap-reason): ADM per-proto
pass/drop counters `0x92394100..0x923941c0` (x9, proto 0=ARP…5=ICMP; `adm_get_*_pass/drop_protocal_packtcnt`).
Won't split by trap reason but could show if bulk-TCP download data is being policed/dropped at ADM.

---

## Summary of what to add to the device experiment

Cheapest highest-value single action: in the existing `dd skip=471192 count=100` CLA dump, start reading
**words 91/92/93** (cla_dn_fwd/trap/drop) alongside the UP words 88/89 already read — that alone tests the
headline finding at zero extra cost. Then add one read of **DPA 0x9239810c** and one of **SPA 0x921d45c4/c8**
to complete the pre-CLA(SPA/DPA)-vs-in-CLA(cla_dn_trap) trap ladder for the download direction.
