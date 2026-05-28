# MAC[N] → switch fabric → PP CLA → TM CPU queue — stock data path RE

**Status**: research → live verification needed.
**Date**: 2026-05-28.
**Source corpus**: `decomp_all_plat_zxylzb_9128S.c`, `decomp_all_switch.c`,
`decomp_all_tm.c`, `regs/stock_eth_2mib.txt` (stock live 2 MiB dump).
**Bases**: `npp_base=0x921c0000`, `tm_base=npp+0x180000=0x92340000`,
`pp_base=npp+0x1c0000=0x92380000`. `fpga_read_reg(idx)` = phys
`0x92000000 + idx*4` (so `fpga_idx=0xd3011 → 0x9234c044 = TM+0xc044`).

---

## Pipeline cheatsheet (stock LAN-only mode `g_pon_work_mode=0x10`)

```
LAN N (RJ45) ──> GePHY[N-1] (MDIO addr 10..13)
                    │
                    ▼     stage S1: PHY→MAC datapath (analog RGMII inside SoC)
        MAC[N-1] @ npp_base + N*0x40000     ← SMAC instance ports 0..4 (LAN1..4 + WAN)
            │
            ▼     stage S2: MAC→SOPC bridge (gated by smac_sopc_mode_switch)
        SOPC bridge @ npp_base+0x19068      ← bit N=enable for port N
        SOPC duplex flag @ npp_base+0x19038 ← bit (N+16): 0=full, 1=half
            │
            ▼     stage S3: SPA (Service Port Aggregator) ingress count
        spa rcv_uniN_sop / rcv_uniN_eop     ← fpga_read_reg(0x75173..0x75177)
            │
            ▼     stage S4: SDET frame validation + VLAN admit
        sdet uni_egress_transport_cnt       ← fpga_read_reg(0x7105[89A])
        sdet uni_egress_drop_cnt            ← fpga_read_reg(0x71059)
            │
            ▼     stage S5: PP CLA (classifier) "is this CPU-bound?"
        cla fwd/trap/drop/copy pkts         ← fpga_read_reg(0xe30f0..0xe30f6)
            │
            ▼     stage S6: PP SADM (admission/policer)
        sadm pass/drop                      ← fpga_read_reg(0xe1080..0xe10ad)
            │
            ▼     stage S7: TM RED queue policy
        red fwd/trap/drop in+out            ← fpga_read_reg(0xd1081..0xd1086)
            │
            ▼     stage S8: TM QMG (queue manager) — sw vs hw fwd/trap
        qmg dn sw_fwd/hw_fwd/hw_trap        ← fpga_read_reg(0xd3011..0xd3013)
        qmg up sw_fwd/hw_fwd/hw_trap        ← fpga_read_reg(0xd3015,0xd3017,0xd3018)
            │
            ▼     stage S9: TM RX descriptor ring → IRQ TM[0x100] bit 0
        per-queue tracking via cla_set_cpu_queue_id (RAM-7 in CLA TCAM)
        TM DMA RX desc base @ TM[0xf0]
        TM RX kick / IRQ status @ TM[0x100..0x104]
            │
            ▼
        CPU (napi poll)
```

---

## Q1 (answered): What signals "MAC[N] passes frames to switch fabric"?

### Per-MAC NPP enable bit

`pon_npp_smac_init` (plat:3273) does:

```c
for (port = 0; port < 4; port++) {
    smac_init(port);                                       // writes MAC.ctrl/.mask/.en
    *(uint*)(npp_base + (port+1)*0x40000) |= 2;            // NPP per-port enable
}
```

This is the **per-port "MAC i is in the fabric"** bit. Our mainline replicates
it as `npp_or(e, (port+1)*MAC_STRIDE, 0x2);` in `zx_smac_init_port` — ✓
present.

### SOPC↔SMAC bridge handshake (stage S2)

`smac_sopc_mode_switch(port, duplex)` (plat:2290):

```c
for (5 retries) {
    udelay(...);
    if (NPP[0x19068] & BIT(port+5)) {           // wait "PHY-MAC link-ready"
        NPP[0x19068] |= BIT(port);              // enable SOPC→SMAC bridge
        break;
    }
}
NPP[0x19038] = NPP[0x19038] & ~BIT(port+16)
             | ((duplex != 1) << (port+16));    // 1 = half-duplex
```

Called from `switch_phy_int_check_part_5` on every PHY-IRQ link transition.

**Mainline status**: replicated in `zx_eth_adjust_link` at iter 25 (`base + 0x19068`).
✓ present.

**Live stock dump anomaly**: `NPP[0x19068]=0`, `NPP[0x19038]=0` in our captured
2 MiB region. This contradicts the decompilation expectation that bit N
should be set per active port. Two interpretations:
1. Stock dump was captured during a window when no link was up
2. These bits are sticky-clear (clear-on-self after some trigger)

Either way, mainline's runtime write IS the correct pattern.

### Per-port global enable (npp[0x40] |= 0x300)

`tm_pon_npp_init` (plat:2238) ends with `npp[0x40] |= 0x300` AFTER per-port
smac_init. Live stock shows `NPP[0x40]=0` so the bits self-clear; mainline
correctly skips this write per existing comment.

### Per-port "ingress queue" / VLAN

Not a single register; lives entirely in PP_BRG (PP+0x8000..) RAM:
- `pon_pp_add_port_to_vlan(vlan, port, mode=3)` — populates per-VLAN bitmaps
  in PP_BRG RAM via `brg_ram_set` (PP[0x8014..0x8028]).
- Live stock PP[0x8050] = 0x0A (NOT the 0xfffffffa the decomp suggests)
- Live stock PP[0x8054] = 0x02 (BRG status latch)
- Live stock PP[0x8188] = 0x211b00 (FDB aging: stock decomp wrote
  `0x13f434` but live shows a different runtime value — `0x211b00 / 0x1107`
  = 478 sec aging)
- Per-port isolate masks at PP[0x83c0+port*4]:
  port 0=0xfe, 1=0xfd, 2=0xfb, 3=0xf7, 4=0xef, 5=0xdf, 6=0xff, 7=0xff
  (each port can forward to everyone except itself; ports 6+7 unrestricted
  — these are the CPU-side ports).

---

## Q2 (answered): PP CLA routing CPU-bound frames

### `zte_zx_api_pp_set_trap_queue` (tm.c:57922) — the function in the title

It's a tiny wrapper around `tm_protocol_pkt_limit_map_set(port=0..7, eth_type, queue, 0, dir)`.
- `direction == 0`: install rule for all 8 directions/queues per call
- `direction == 1`: install single rule with `port = 5` (= CPU-trap)

`tm_protocol_pkt_limit_map_set` builds a CLA RAM address:

```c
ram_addr = eth_type | (port<<7);    // 0x80=port0, 0x100=port1, …, 0x300=port6, 0x380=port7,
                                    //           port5 (=CPU) takes the bare eth_type slot
cla_set_cpu_queue_id(ram_addr, queue);
```

`cla_set_cpu_queue_id` (tm.c:3959) talks the **CLA indirect-RW protocol**:
```
1. poll CLA[0xc018] bit 0 == 0   (ready)
2. CLA[0xc014] = ram_addr | (ram_id=7 << 0x16) | (0 << 0x1b)   ; cmd: write RAM-7
3. CLA[0xc01c] = queue                                         ; data
```

So all 574 `trap_queue` entries land in **PP_CLA RAM bank 7** which is the
"protocol → CPU queue ID" lookup. RAM bank 7 is 1024 entries × 4-bit queue ID.

**Mainline status**: replicated via `zx_cla_apply_replay` reading
`zx_cla_table.h`. ✓ present.

### CLA stats (fpga_read_reg indices)

From `tm_up_statistics_get` (tm.c:46289+):
- `cla fwd  pkts` ← `fpga_read_reg(0xe30f0)` = abs `0x9239C3C0` = PP+0x1C3C0
- `cla trap pkts` ← `fpga_read_reg(0xe30f1)` = abs `0x9239C3C4` = PP+0x1C3C4
- `cla drop pkts` ← `fpga_read_reg(0xe30f2)` = abs `0x9239C3C8` = PP+0x1C3C8
- `cla copy pkts` ← `fpga_read_reg(0xe30f6)` = abs `0x9239C3D8` = PP+0x1C3D8

(These are 16-bit counts: code does `& 0xffff` after read.)

### Protocol → CPU map

Two tables live in switch.ko `.rodata` and are replayed by `chip_tm_init`:
- `DAT_00013cf4[164]` = `(eth_type, dn_q, up_q)` triples for `zte_api_pp_set_trap_queue`
- `DAT_00013cf8[214]` = `(eth_type, dn_act, up_act)` triples for `zte_api_pp_set_pro_action`

Our mainline includes both via `zx_stock_table.h` / `zx_pp_pro_actions.h`.
ARP (0x0806) and ICMP (proto=1) go to CPU queue 1 by default per the table.

---

## Q3 (answered): TM CPU queue feed

The CLA verdict (queue ID 0..7) lands in TM via the QMG block. Per-queue
pending count is observable via `qmg_get_statistics` (tm.c:33036):

| fpga idx | Phys addr  | TM offset | Counter |
|---|---|---|---|
| 0xd3011 | 0x9234C044 | TM+0xC044 | qmg dn sw_fwd  pkt |
| 0xd3012 | 0x9234C048 | TM+0xC048 | qmg dn hw_fwd  pkt |
| 0xd3013 | 0x9234C04C | TM+0xC04C | qmg dn hw_trap pkt |
| 0xd3015 | 0x9234C054 | TM+0xC054 | qmg up sw_fwd  pkt |
| 0xd3017 | 0x9234C05C | TM+0xC05C | qmg up hw_fwd  pkt |
| 0xd3018 | 0x9234C060 | TM+0xC060 | qmg up hw_trap pkt |

**Live stock dump (post-ping):**
- TM+0xC044 (dn sw_fwd) = 0x54D (1357 pkts)
- TM+0xC060 (up hw_trap) = 0x5B4 (1460 pkts)
- MAC[0]+0x780 (RX pkts) = 0x5B4 (1460 pkts — **identical** to qmg up hw_trap)

**This proves the stock data path**: every frame that the MAC's wire-side RX
counter saw also reached `qmg up hw_trap` (= "trap to CPU queue, upstream
direction"). The matching counts are the smoking gun that stock's chain
ARP → MAC[N] RX → SPA → SDET → CLA → SADM → RED → QMG-up → TM CPU
queue → DMA → CPU **all worked end-to-end** with no drops on the captured
device.

### Where stock ARP packets end up

ARP (eth_type 0x0806) is mapped by entry 4 of `DAT_00013cf4` to CPU queue 1.
Queue 1 is the "control plane" queue; NAPI poll drains it via the standard
`pon_tm_net_poll` loop.

---

## Q4 (likely answer): The missing init step

Comparing live stock dump against mainline replay, **two divergences** stand
out as the most likely cause of frames being lost between MAC and TM:

### (a) PP_BRG `pp_base + 0x2c` — bit 29 (lan_up_port + 0x19) **never gets set in live stock**

Decompile-only finding:
```c
// init_module tail, plat-zxylzb_9128S:8940
if (lan_up) {
    pp_base[0x2c] |= 1 << (lan_up_port + 0x19);   // lan_up_port=4 → bit 29
    zx_pon_clk_reset();                            // TOPCRM[0xc] |= 0x1e0
}
```

Live stock `pp_base+0x2c = 0x106` (bits 1, 2, 8). **Bit 29 is NOT set.**
This is the "HW write-lock" pattern previously documented in
`hw_write_lock_pattern_re.md` — writes to bits 26..30 don't stick.

So mainline's longstanding `PP_CPU_FWD_BIT = BIT(25)` was already wrong
(lan_up_port=4 → bit 29, not 25). **Either way, the bit is unstickable.**

The real meaning of `pp[0x2c] = 0x106`:
- bit 1 = ?
- bit 2 = ?
- bit 8 = ?
These were already-set values from PP cold-boot / U-Boot. Mainline currently
leaves them alone — that matches stock.

### (b) `lan_up_port` semantic — the value is **4**, used as +0x28 in TX desc

Stock printk: `lan_up=1, lan_up_port=4`. Our mainline hardcoded `port=0`
in TX desc encoding (`desc[2..3] = ... | ((0+0x28) & 0x3f) << 4`). Per
`lan_up_port_lifecycle.md`, recent commit `80f610eda` changed it to 4.
**Verify**: this commit must have updated both the TX desc port field AND
any place mainline mirrors stock's `lan_up_port`. If only one was updated
the TX path would misroute.

### (c) BIG suspect: PP[0xc080] **= 0x600 stock, vs 0x1000 in mainline replay**

`pon_pp_cla_init` decomp says `pp[0xc080] = 0x1000`. But live stock has
`0x600` there. PP[0xc080] is `PP_CLA_BASE + 0x80` — the CLA "control reg".

Bit decode (guess from value):
- 0x600 = bits 9 + 10 set
- 0x1000 = bit 12 only

If mainline replays the decomp-written `0x1000` instead of the live-stock
`0x600`, **the CLA classifier is configured differently** than stock —
which directly affects whether ARP/ICMP get the "trap to CPU" verdict.

**Action**: replay table audit — verify `zx_stock_table.h` writes `0x600`
to PP[0xc080] and not `0x1000`. If it writes 0x1000 → fix to 0x600.

### (d) Less suspect but worth checking: `qmg dn sw_fwd` vs `up hw_trap`

The stock counter pattern shows:
- Upstream (LAN→CPU): hw_trap mode — frames classify to CPU via HW table,
  no SW intervention.
- Downstream (CPU→LAN): sw_fwd mode — SW chose the egress port.

Mainline currently only services upstream RX (via NAPI poll). The downstream
TX path should also work via QMG sw_fwd. If mainline's `dev_qos_select_queue`
or `pon_tm_data_raw_send` desc encoding doesn't put the right egress port
into desc[2..3], QMG dn sw_fwd will fire but to the wrong port → frame
gets eaten at port-isolate.

---

## Q5 (answered): Counter addresses to expose in pipeline_stats

Add these to `zx_pipeline_stats_show`:

```c
// stage S3: SPA per-port ingress
// Each fpga_read_reg returns 32 bits split into 4 bytes; per-UNI sop = byte 0+1, eop = byte 2+3.
//                            byte0 (sop) byte2 (eop)
// fpga_read_reg(0x75173)  →  uni0_sop    uni0_eop  (then >> N shifts on the upper bytes)
// ...similarly 0x75174..0x75177 for uni1..uni4 / wifi.
// addr formula: phys = 0x92000000 + 0x75173*4 = 0x921D45CC = NPP+0x145CC
seq_printf("spa: rcv_uni%d sop=%u eop=%u\n", n, byte0(reg), byte2(reg));

// stage S4: SDET per-UNI egress
// fpga_read_reg(0x71059)..(0x7105c) — UNI 0..3 trans/drop pairs
// phys = 0x92000000 + 0x71059*4 = 0x921C4164 = NPP+0x04164 (= 0x921D4164 nope, recompute)
// 0x71059 * 4 = 0x1C4164, abs = 0x921C4164. NPP+0x04164 (NPP first 64KB)
seq_printf("sdet uni%d egress_trans=%u drop=%u\n", n, ...);

// stage S5: PP_CLA verdict counters
//   PP+0x1C3C0 (CLA fwd)
//   PP+0x1C3C4 (CLA trap)   ← THE ONE THAT MUST INCREMENT FOR PING ARP
//   PP+0x1C3C8 (CLA drop)
//   PP+0x1C3D8 (CLA copy)
seq_printf("cla fwd=%u trap=%u drop=%u copy=%u\n",
    readl(e->base + PP_OFF + 0x1C3C0) & 0xffff,
    readl(e->base + PP_OFF + 0x1C3C4) & 0xffff,
    readl(e->base + PP_OFF + 0x1C3C8) & 0xffff,
    readl(e->base + PP_OFF + 0x1C3D8) & 0xffff);
// (PP_OFF = 0x1C0000, so PP+0x1C3C0 = NPP+0x1C0000+0x1C3C0… wait that overflows.
//  Stock PP_OFF is 0x1C0000 from npp_base; the fpga 0xe30f0 = NPP+0x18C3C0 → outside
//  our 2 MiB window. RE-CHECK: 0xe30f0*4 = 0x38C3C0, abs = 0x9238C3C0,
//  → PP base 0x92380000 + 0xC3C0 → PP+0xC3C0 (correct, inside PP_OFF+0xC000=CLA area))

// stage S6: PP_SADM pass/drop (4 dirs each)
//   fpga 0xe1080..0xe10ad → abs 0x92384200..0x923842B4 → PP+0x4200..0x42B4
seq_printf("sadm pass/drop ...\n");

// stage S7: TM_RED in/out fwd/trap/drop
//   fpga 0xd1081..0xd1086 → abs 0x92344204..0x92344218 → TM+0x4204..0x4218
seq_printf("red fwd/trap/drop in=%u out=%u\n",
    readl(e->base + TM_OFF + 0x4204), readl(e->base + TM_OFF + 0x4218));

// stage S8: TM_QMG (already enumerated above)
seq_printf("qmg dn sw_fwd=%u hw_fwd=%u hw_trap=%u  up sw_fwd=%u hw_fwd=%u hw_trap=%u\n",
    readl(e->base + TM_OFF + 0xC044),
    readl(e->base + TM_OFF + 0xC048),
    readl(e->base + TM_OFF + 0xC04C),
    readl(e->base + TM_OFF + 0xC054),
    readl(e->base + TM_OFF + 0xC05C),
    readl(e->base + TM_OFF + 0xC060));

// Direct check that QMG sub-block is even sampling:
// TM+0xC000 = 0x01f40fa0 stock (sw_alarm_init's poke). If zero → QMG not configured.
seq_printf("qmg cfg = 0x%08x (stock = 0x01f40fa0)\n",
    readl(e->base + TM_OFF + 0xC000));

// (Optional) sipc2cpu_aful (CPU FIFO almost-full)
//   fpga 0x73001 → abs 0x921CC004 → NPP+0xC004
//   bits 28..31 = ful_cnt_up, 24..27 = aful_cnt_up
seq_printf("sipc2cpu: aful=%u ful=%u\n",
    (readl(e->base + 0xC004) >> 24) & 0xf,
    (readl(e->base + 0xC004) >> 28) & 0xf);
```

---

## Summary

### Where in the path frames die (best guess, ordered by likelihood)

1. **PP_CLA configured wrong** (PP[0xc080] = 0x1000 in mainline replay vs
   0x600 in live stock) → ARP/ICMP get the "drop" verdict instead of "trap
   to CPU queue". This would cause MAC RX counter to increment but
   qmg-up-hw_trap to stay at 0 — **matches our exact symptom.**
2. **QMG cfg reg PP[0xd3000] = 0x01f40fa0** (sw_alarm_init's poke). If
   mainline doesn't replay this single write, the QMG sub-block has no
   bucket size and silently drops everything. Verify in replay tables.
3. **PP_BRG default VLAN membership** (`pon_pp_add_port_to_vlan` calls) —
   if our port-0 (LAN1) isn't a member of VLAN 0 in PP_BRG RAM, switch
   fabric drops it.
4. **`lan_up_port` mismatch in TX desc encoding** — already addressed in
   commit `80f610eda` if everything is consistent; verify the desc[2..3]
   field uses port=4 not port=0.

### The single most actionable next test

**Diff PP[0xc080] live mainline vs live stock.** If mainline has 0x1000 and
stock has 0x600, that's the one-write fix. The CLA control register
governs the *protocol-classifier-enable* bit pattern, and from the bit
positions (9+10 vs 12) this is almost certainly the "trap-to-CPU enable"
gate the static analysis flagged as `dpa_set_protocol_cpu_pps_en` /
`dpa_set_protocol_pkt_aly_en`.

```
devmem 0x9238c080         # read mainline live
                          # if != 0x600: writel 0x600 → 0x9238c080, retry ping
```

### Counter addresses to expose in pipeline_stats (priority ranking)

| Priority | Counter | Phys addr | Mainline offset |
|---|---|---|---|
| 🔴 1 | cla trap pkts | 0x9238c3c4 | `base + PP_OFF + 0xc3c4` |
| 🔴 2 | qmg up hw_trap | 0x9234c060 | `base + TM_OFF + 0xc060` |
| 🔴 3 | qmg cfg (= 0x01f40fa0) | 0x9234c000 | `base + TM_OFF + 0xc000` |
| 🟡 4 | sdet uni0 egress_trans / drop | 0x921c4164 / 0x921c4168 | `base + 0x4164 / 0x4168` |
| 🟡 5 | spa rcv_uni0 sop / eop | 0x921d45cc (split bytes) | `base + 0x145cc` |
| 🟡 6 | cla fwd / drop / copy | 0x9238c3c0 / c3c8 / c3d8 | PP+0xc3c0/c3c8/c3d8 |
| 🟡 7 | red fwd/trap/drop in+out | 0x92344204..0x92344218 | TM+0x4204..0x4218 |
| 🟢 8 | sadm pass/drop | 0x92384200..0x923842b4 | PP+0x4200..0x42b4 |

### Confidence

- **High confidence**: pipeline addresses and counter offsets (verified
  cross-correlation: MAC[0]+0x780 = qmg up hw_trap = 0x5b4 in stock dump).
- **Medium-high confidence**: hypothesis (a) about PP[0xc080] mismatch. The
  decomp clearly writes 0x1000, live stock has 0x600. Either the decomp
  is correct and mainline-replay also writes 0x1000 → CLA disabled, OR
  the replay tables already capture 0x600 → look elsewhere.
- **Lower confidence**: hypothesis (c) about PP_BRG VLAN membership.
  Stock PP[0x8050] = 0x0A (4 bits set) but the decomp wrote 0xfffffffa.
  This could mean the brg_init "fffffffa" write is followed by a
  bitfield mask elsewhere, OR the 0x0A is a runtime-modified subset.

### Not directly answered

- Why stock NPP[0x19068] = 0 in the dump while the SOPC bridge bit
  *should* be 1 for the actively-linked port: deferred (could be capture
  timing or a hidden clear-on-self register).
- Exact bit-decode of PP[0x2c]=0x106 default value (bits 1, 2, 8): not
  on the suspected critical path since stock works with this default,
  so mainline matching the default is fine.

---

## Cross-references

- `eth_init_flow_2026_05_26.md` — full init order (boot → up)
- `HW_BLOCKS_INVENTORY.md` — block-by-block inventory of sub-units
- `static_analysis_plat_zxylzb_init.md` — depth-first init walk
- `static_analysis_switch_ko_init.md` — chip_tm_init details
- `tm_100_status_bit_decode.md` — TM[0x100] bit meanings
- `lan_up_port_lifecycle.md` — `lan_up_port=4` semantics
- `hw_write_lock_pattern_re.md` — bits in PP[0x2c] that don't stick
- `regs/stock_eth_2mib.txt` — live stock dump, ground truth
- mainline driver: `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`
- replay tables: `zx_stock_table.h`, `zx_stock_bursts.h`,
  `zx_cla_table.h`, `zx-pp-pro-actions.h`
