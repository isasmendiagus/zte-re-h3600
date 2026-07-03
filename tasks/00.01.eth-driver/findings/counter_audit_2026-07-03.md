# Pipeline-counter audit — every HW counter the driver/tooling reads, cross-checked vs stock decomp + datasheet

Date: 2026-07-03. Device-free static audit (no device touched; a device experiment ran concurrently).
Authoritative sources: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c`
(`tm_up_statistics_get`@46132, `tm_dn_statistics_get`@46457, the CLA `statics`/`desIn`/`desOut`
debug commands @67958–68153, `smac_get_statistics`@21385), `DATASHEET.md` PART-3, and the driver
`zx_pipeline_stats_show` (`linux-v6.6/.../zx-eth-main.c:5470`). Address rule: `phys = widx*4 +
0x92000000`; driver `e->base = 0x921c0000` (confirmed zx-eth-main.c:1190), so a driver offset
`0xXXXXX` resolves to `0x921c0000 + 0xXXXXX`.

**The single most important new fact this audit adds:** the stock `statics` command decodes the CLA
counters into MORE sub-fields than either `tm_up/tm_dn` or the driver — `0x9238c3c0` and `0x9238c3c8`
are each **two packed 16-bit counters** (`no_e8` in lo16, `e8` in hi16), and all CLA fwd/trap/drop
are **16-bit**, not u32. The driver reads them as full u32.

---

## (a) CORRECTED authoritative counter table

Legend: dir = direction bank (UP=LAN→WAN uploads / DN=WAN→LAN downloads / agn=agnostic single reg).
"stock read" = how the authoritative getter masks it. C=counter, L=latch.

### CLA verdict counters (read directly, NOT via indirect-RAM; the primary flow-offload signal)
| name | phys | widx | dir | field (authoritative) | C/L | scope |
|---|---|---|---|---|---|---|
| acl_failed | 0x9238c3b8 | 0xe30ee | agn | **lo16 [15:0]** | C16 | submitted-to-CLA packets whose lookup FAILED |
| acl_required | 0x9238c3b8 | 0xe30ee | agn | **hi16 [31:16]** | C16 | packets SUBMITTED to CLA lookup (the submit gate) |
| cla_tx_fwd_no_e8 | 0x9238c3c0 | 0xe30f0 | UP | **lo16** | C16 | UP HW-forwarded, no-e8 |
| cla_tx_fwd_e8 | 0x9238c3c0 | 0xe30f0 | UP | **hi16** | C16 | UP HW-forwarded, e8(extended-action) |
| cla_tx_trp | 0x9238c3c4 | 0xe30f1 | UP | lo16 (tm_up masks; statics prints full) | C16 | UP trap-to-CPU |
| cla_tx_drp_no_e8 | 0x9238c3c8 | 0xe30f2 | UP | **lo16** | C16 | UP drop, no-e8 |
| cla_tx_drp_e8 | 0x9238c3c8 | 0xe30f2 | UP | **hi16** | C16 | UP drop, e8 |
| cla_tx_copy | 0x9238c3d8 | 0xe30f6 | UP | full32 | C32 | UP copy-to-CPU |
| **cla_dn_fwd** (rx fwd) | **0x9238c3cc** | 0xe30f3 | **DN** | lo16 (tm_dn masks; statics full) | C16 | **DN HW-forwarded** |
| **cla_dn_trap** (rx trp) | **0x9238c3d0** | 0xe30f4 | **DN** | lo16 / full | C16 | **DN trap = LOOK_UP_MISS 0x54** |
| **cla_dn_drop** (rx drp) | **0x9238c3d4** | 0xe30f5 | **DN** | lo16 / full | C16 | DN drop |
| cla_dn_copy | 0x9238c3dc | 0xe30f7 | DN | full32 | C32 | DN copy |
| desIn[0..6] | 0x9238c3e0..0x9238c3f8 | 0xe30f8.. | agn | packed descriptor | **L** | last in-flight CLA-*ingress* descriptor (SHARED) |
| desIn action_rsn | 0x9238c3e8 (desIn word2) | — | agn | complex: `((w>>16)<<0x12)>>0x19` (≈bits[29:23]) via `trapPktType[]` | **L** | trap reason of latched pkt |
| desIn l3_en | 0x9238c3ec (desIn word3) | — | agn | bit6 | **L** | HW L3-route flag of latched pkt |
| desOut[0..8] | 0x9238c394..0x9238c3b4 | 0xe30e5.. | agn | packed descriptor | **L** | last CLA-*egress* descriptor (SHARED) |

### QMG forward-decision counters (base 0x9234c000)
| name | phys | widx | dir | field | C/L | note |
|---|---|---|---|---|---|---|
| QMG DN sw_fwd | 0x9234c044 | 0xd3011 | DN | full32 | C | |
| QMG DN hw_fwd | 0x9234c048 | 0xd3012 | DN | full32 | C | |
| QMG DN hw_trap | 0x9234c04c | 0xd3013 | DN | full32 | C(sat) | **SATURATES/pins at 1024** = CPU-trap-queue credit (the wedge) |
| QMG UP sw_fwd | 0x9234c054 | 0xd3015 | UP | full32 | C | |
| QMG UP hw_fwd | 0x9234c05c | **0xd3017** | UP | full32 | C | ⚠ NOT 0xd3016/0x…c058 — there is a gap |
| QMG UP hw_trap | 0x9234c060 | 0xd3018 | UP | full32 | C | == MAC RX-ok on LAN→CPU (datasheet 1820) |

### Per-stage disposition counters (the trap ladder)
| name | phys | widx | dir | field | note |
|---|---|---|---|---|---|
| SPA classify before-vlan | 0x921d45c4 | 0x75171 | both | byte-pack **fwd[31:24]/drp[23:16]/cpy[15:8]/trp[7:0]** | spa_trp = byte0 |
| SPA classify after-vlan | 0x921d45c8 | 0x75172 | both | same byte-pack | |
| SPA per-uni RX (sop/eop) | 0x921d45cc + uni*4 | 0x75173+ | UP | byte-packed sop/eop | what the DRIVER prints as `SPA_rcv` |
| DPA parse verdict | 0x9239810c | 0xe6043 | DN | byte-pack fwd[31:24]/drp[23:16]/cpy[15:8]/trp[7:0] | dpa_trp = byte0; "downstream packet analysis" |
| SADM pon pass | 0x92384200 | 0xe1080 | both | byte-pack pkt[7:0]/uni[15:8]/brd[23:16]/multi[31:24] | UP also has per-uni 0xe1081..89 |
| SADM pon drop | **0x92384228** | **0xe108a** | both | same byte-pack | |
| ADM drop (aggregate) | 0x9239422c(dn)/0x9239c... | 0xe508b(dn)/0xe508c(up) | split | full | |
| PM recv / send / fwd[31:16] / trap[15:0] | 0x9239c088 / 0x9239c080 / 0x9239c0a0 | 0xe7022/20/28 | both | fwd=hi16, trap=lo16 of 0x…0a0 | |
| RED fwd in/out | 0x92344204 / 0x92344210 | 0xd1081/84 | both | full | |
| RED trap in/out | 0x92344208 / 0x92344214 | 0xd1082/85 | both | full | |
| RED drop in/out | 0x9234420c / 0x92344218 | 0xd1083/86 | both | full | |
| SDET egress_transport / drop | uni0-3 0x921c4160+uni*4; **uni4 0x921c4178** | 0x71058-5b, **0x7105e** | UP | byte0=transport, byte2=drop | ⚠ uni4 is NON-contiguous (see bug #4) |
| SIPC drop word | 0x921cc004 | 0x73001 | both | bitfield cpu_short/cpu_pkt/aful/ful | driver prints raw |
| SOPC PP/RED/DSCH drop | 0x921da040 / 0x921da044 / 0x921da04c | 0x76810/11/13 | both | full | |
| MAC[p] RX total / bytes | (p+1)*0x40000 + 0x780 / +0x784 | — | UP | full (RX-side) | verified via memdump; stock uses smac subcmd 0x28 |
| MAC[p] TX send total | via smac subcmd 0x10 (~+0x718) | — | DN | | driver does NOT read (DN gap) |

---

## (b) RANKED list of misreads / bugs found, and the conclusion each distorted

### 1. ★★★ CRITICAL — the 75/11 "l3_en split" is a cross-bank artifact (already partly known; now fully pinned)
`wan_ingress_l3en_split_2026-07-03.md` computed the download decomposition as:
- `l3_en=1 = cla_tx_fwd(0x9238c3c0) + cla_tx_trp(0x9238c3c4)` — **both UP bank**
- `l3_en=0 = QMG_DN_hw_trap(0x9234c04c, DN) − cla_tx_trp(0x9238c3c4, UP)` — **DN minus UP**

This subtracts an UP-direction counter from a DN-direction counter for a DN (download) test. It is
cross-bank AND cross-scope, so the derived "~75 % l3_en=0 (never reach the CLA / parse-arm gap) +
~11 % l3_en=1-but-trap" is an ARTIFACT, not a measurement.
**Distorted conclusion:** the entire "dominant ~75 % pre-CLA parse-arm gate / fix the DN L3-parse so
l3_en=1" narrative (also `wan_ingress_l3en_split`, `disposition_compare`,
`stock_wan_ingress_l3en_arm_RE`). **REFUTED** by the direction-correct re-measure in
`acl_required_fork_settler_2026-07-03.md` (same build #476): `acl_required` tracks load 1:1
(≈100 % reach the CLA), `acl_failed(+83) ≈ cla_dn_trap 0x9238c3d0 (+84) ≈ QMG_DN_hw_trap (+84)`,
`dpa_trp=0`, `spa_trp≈+4` → the loss is IN the CLA lookup (VERDICT B), NOT pre-CLA parse. There is no
75 % l3_en=0 population.

### 2. ★★★ Driver `pipeline_stats` reads the UP CLA bank + as unpacked u32 (wrong dir AND wrong field)
`zx-eth-main.c:5521` reads `CLA fwd[0x1cc3c0]` / `drop[0x1cc3c8]` / `copy[0x1cc3d8]` = the **UP** bank,
and reads them with `readl()` as full u32. Per stock `statics`, `0x9238c3c0` = `[fwd_no_e8 lo16 |
fwd_e8 hi16]` and `0x9238c3c8` = `[drp_no_e8 | drp_e8]` — each is two 16-bit counters. So the printed
"CLA fwd/drop":
- is **UP-direction** (useless for a download; the DN bank 0x3cc/d0/d4 is never read), and
- is a **corrupted composite** (`no_e8 + 65536*e8`) whenever the e8/hi16 sub-count is non-zero.
**Distorted:** any download conclusion taken off the driver's `pipeline_stats` CLA line; and the
"~13–14 % HW-forward" figure — that came from reading UP `cla_tx_fwd` during a DN download. The
direction-correct #476 read of `cla_dn_fwd 0x9238c3cc` was **≈0 %** (the ~14 % was UP-ACK bleed into
the UP bank). Re-measure DN forward rate on 0x9238c3cc (lo16).

### 3. ★★ Driver SADM `drop` reads inside the PASS block (and the prior "wrong-block" claim was itself an arithmetic error)
Driver: `SADM pass[0x1c4200]` → `0x92384200` = SADM pon pass = **CORRECT address** (but printed raw,
byte-packed, pon-only). `SADM drop[0x1c4208]` → `0x92384208` = widx 0xe1082 = **still the 3rd word of
the PASS block**, NOT the drop block. Real DN pon drop = 0xe108a = `0x92384228` = offset `0x1c4228`
(off by 0x20). **Correction to the record:** `undecoded_pipeline_counters` + memory
`zte-datasheet`/`zte-flowoffload-framework` state the driver's SADM is at "0x923a4200/08, WRONG
block" — that is a base-arithmetic slip (0x921c0000+0x1c4200 = 0x92384200, not 0x923a4200). The truth:
SADM **pass is correct**, only **drop is wrong** (reads a pass word).
**Distorted:** any "SADM drop" reading from `pipeline_stats`. (Low impact — SADM is post-CLA, was
never the ~86 % gate.)

### 4. ★ Driver SDET `uni4` reads the wrong register (non-contiguous stride)
Driver assumes `0x4160 + uni*4`, so uni4 → `0x921c4170` (widx 0x7105c). Stock reads uni4 at widx
**0x7105e = 0x921c4178** (uni0-3 are at 0x71058-5b, then it SKIPS 0x7105c/5d). uni0-3 correct, uni4
wrong. Also SDET `egress_transport` is an egress/UP-transport gauge, used in the per-uni **ingress**
chain — scope caveat. **Distorted:** only the uni4 line of the port1 ingress-chain hunt (minor).

### 5. ★★ desIn latches (l3_en 0x9238c3ec bit6 / action_rsn 0x9238c3e8) are STALE on #476 — not counters
`wan_ingress_l3en_split` itself recorded them constant: `l3_en=0x80010803` (bit6=0 fixed),
`reason=0x88b00000` (→0x11 fixed, never 0x54/0x49). They are shared per-last-packet snapshots, not
per-flow, and the reason extraction is more complex than the datasheet's shorthand "[29:23]"
(decomp: `((w>>16)<<0x12)>>0x19`). **Distorted:** the original "l3_en=0 on mainline vs 1 on stock"
observation that seeded the parse-arm hypothesis is latch-noise. Use the acl_required/stage-ladder
counters, never the latch, on this build.

### 6. ★ Datasheet reg-table calls the CLA counters "u32" (contradicts the decomp and its own PART 3)
DATASHEET.md lines 885–886 label `cla_tx_fwd/cla_tx_trp` "u32 counter"; the decomp (statics + the
tm_up/tm_dn `& 0xffff` masks) and PART-3 line 1496 say they are **16-bit**, and fwd/drop are packed
no_e8/e8 pairs. Fix the reg-table entry.

---

## (c) TRUSTWORTHY as-measured vs NEEDS RE-MEASURE

### TRUSTWORTHY (direction- and field-correct, verified against the decomp)
- **VERDICT B / in-CLA lookup miss (`acl_required_fork_settler_2026-07-03.md`, #476).** Reads
  `acl_required` hi16 + `acl_failed` lo16 (0x9238c3b8) ✓, `cla_dn_trap` 0x9238c3d0 ✓, QMG DN hw_trap
  0x9234c04c ✓, `spa_trp` 0x921d45c4[7:0] ✓, `dpa_trp` 0x9239810c[7:0] ✓ — all correct, measured
  below the 1024 wedge. The "~72 % of submitted packets fail the CLA lookup; parse (SPA/DPA) carries
  none of the loss" verdict STANDS.
- **LAN-ingress 100 % data hit (`hitrate_rootcause`).** UP-direction (lan1→lan4 redirect); UP bank
  `cla_tx_fwd/trp` is the correct direction; e8/hi16 = 0 (clean ±N deltas) so the full-u32 read
  happened to equal lo16. STANDS. Same for `c1_fix_validation`, `autooffload_wire` (both LAN-inject
  upstream tests → UP bank correct).
- **QMG DN/UP fwd/trap in the driver** — addresses and fields correct.
- **The 1024 QMG-DN-hw_trap wedge (0x9234c04c)** — correct counter/direction; but it **saturates** at
  1024 (trap credit). Deltas or fwd/trap RATIOS computed across the pin under-count traps — valid
  only in a wedge-free window (which #476 used: hw_trap 5–864 < 1024).

### DISCARD / RE-MEASURE
- **DISCARD the 75 % l3_en=0 / 11 % l3_en=1 split** (bug #1) — cross-bank artifact; superseded by
  VERDICT B. Do not carry the "parse-arm gap is the dominant gate" into the roadmap.
- **RE-MEASURE the DN HW-forward rate** on `cla_dn_fwd 0x9238c3cc` (lo16), not UP `0x9238c3c0`. The
  "~13–18 %" figure is UP-bank bleed; the direction-correct read hinted at ≈0 % DN data forward.
- **RE-READ** the driver `pipeline_stats` CLA line as the **DN bank + lo16-masked** before trusting any
  download number off it; fix SADM `drop` (→0x1c4228) and SDET `uni4` (→0x921c4178) in the driver.
- **Never** use the desIn l3_en/reason latch for a verdict on #476.

---

## Driver instrumentation-fix list (read-only audit; no edits made)
1. `pipeline_stats` CLA: add the DN bank (0x1cc3cc/d0/d4/dc), mask fwd/drop to lo16 (or split
   no_e8/e8), and read `acl_required`(hi16)/`acl_failed`(lo16) at 0x1cc3b8.
2. SADM drop offset `0x1c4208` → `0x1c4228`; decode the byte-packed pkt/uni/brd/multi fields; add the
   per-uni pass/drop entries.
3. SDET uni4 offset `0x4170` → `0x4178` (non-contiguous stride).
4. Add DN stage-ladder lines: SPA verdict 0x145c4/c8 (byte-packed), DPA verdict 0x1981... (0x9239810c),
   RED trap/drop 0x92344208/214/20c/218, PM recv/send/fwd/trap 0x9239c080/88/a0.
5. Correct DATASHEET reg-table: CLA counters are 16-bit; 0x…c3c0/c3c8 are packed no_e8/e8 pairs.
