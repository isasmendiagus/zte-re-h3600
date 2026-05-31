# port1 silent MAC→fabric ingress drop — SDET per-uni admit stage (RE)

**Status: NEW LEAD (static RE, untested on HW). Date: 2026-05-31. Branch: eth-dsa.**

Follow-up to `multiport_root_cause_macinit.md`. That doc proved (a) multi-port DSA works
for ports 0/2/3 + hotplug, and (b) port1/jack2 is a genuine, reproducible, config-invisible,
SILENT drop at MAC1→fabric: MAC1 RX-ok climbs with clean frames (0 CRC/align err), SIPC drop
counters (0x921cc004/cc008) stay 0, QMG hw_trap stays 0, `rx_per_ingress[port1]=0` while
port2=9 / port3=12 on the SAME boot. No counter anywhere registered the drop.

This RE pass found **a per-port stage on the MAC→classifier path that the mainline driver
never initializes at all**: the SDET (frame-detect / VLAN-admit) block.

---

## 1. The stock MAC→SIPC ingress datapath (per-port stages)

All FPGA regs are WORD-indexed: `phys = 0x92000000 + word_off*4`.
(npp / e->base = 0x921c0000 = 0x92000000 + 0x1C0000; confirmed zx-eth-main.c:2086.)

```
SMAC[N] RX ─► SPA (per-uni rcv) ─► SDET (per-uni frame validate/VLAN admit) ─► CLA ─► SADM ─► RED ─► QMG-up ─► SIPC ─► CPU
```

Source of the stage map: `decomp_all_tm.c:46180-46399` (upstream-statistics dumper) +
`findings/mac_to_cpu_path_re.md:197,280-342`.

Per-port (per-uni) gates on the MAC→classifier handoff:

| Stage | Stock fn / init | Per-uni register(s) (real phys) |
|---|---|---|
| SPA per-uni receive | `spa_set_up_reg_pkt_en(i,1)` loop 0..0x4d in `tm_pon_npp_spa_initial` (decomp_all_tm.c:43301) | rcv_uniN sop/eop = word 0x75173+N → **0x921D45CC + N*4** |
| **SDET per-uni admit** | **`tm_pon_npp_sdet_initial` (decomp_all_tm.c:43182)** | see table below |
| SIPC (shared, NOT per-port) | `sipc_set_rx_en(1)`/`sipc_set_cpu_up_en(0)` (decomp_all_tm.c:43211) | ctrl 0x921cc000 bit0/bit2 |
| SMCT (shared, NOT per-port) | smct gauges only | 0x921d0000/04/08 (uni/pp/ppmove PMAU) |

SIPC and SMCT are single shared blocks (not per-port addressed) — they cannot discriminate
port1 from port2/3, consistent with the earlier SIPC-poke disproof. **The only per-port admit
state between MAC-RX and the classifier is SPA per-uni pkt_en and the SDET per-uni block.**

### SDET register map (block @ 0x921c4000; sdetgRegTable; reg-id selected by PORT)

`sdet_set_maxframe_length(port,len)` (decomp_all_tm.c:24470) calls
`tmOnuRegWrite(reg_id=port, val=len, idx=0, &sdetgRegTable)` — i.e. the **port number is the
reg_id**, so ports 0..4 hit 5 distinct interleaved words. `tm_pon_npp_sdet_initial` loops
ports 0..4 writing maxframe=0x3000 (plus minframe, down-maxframe). Reg table:
zx-fpga-reg-tables.h:513.

| field | reg_id | word | phys | bits | stock-live value |
|---|---|---|---|---|---|
| maxframe[port0] | 0 | 0x71000 | **0x921C4000** | [29:16] | `0x07cc000c` (max=0x07cc, min=0x0c) |
| maxframe[port1] | 1 | 0x71094 | **0x921C4250** | [13:0] | `0x07cc07cc` |
| maxframe[port2] | 2 | 0x71094 | **0x921C4250** | [29:16] | (same word as port1) |
| maxframe[port3] | 3 | 0x71095 | **0x921C4254** | [13:0] | `0x07cc07cc` |
| maxframe[port4] | 4 | 0x71095 | **0x921C4254** | [29:16] | (same word as port3) |
| c_tpid (VLAN admit) | 14 | 0x7103c | **0x921C40F0** | [15:0] | `0x00008100` |

Stock-live values from `findings/regs/stock_eth_2mib.txt:4097` (0x921c4000) and the
0x921c4250/4254/40f0 lines.

### SDET per-uni DROP counters (the silent-drop oracle — never read by mainline)

From the stats dumper loop `iVar5 = 0x71058..0x7105c` (decomp_all_tm.c:46211-46234):
- `sdet uniN egress_transport_cnt / drop_cnt` = word **0x71058+N → 0x921C4160 + N*4**,
  each `[7:0]=transport`, `[23:16]=drop` (uni0=0x921C4160 … uni3=0x921C416C; uni4 @ 0x7105e=0x921C4178).
- `UNIn_DROP_HPMAU_CNT` = word 0x73061+N → **0x921CC184 + N*4** (decomp_all_tm.c:46245).
- `sdet_shor_drop_cnt` = word 0x73009 → **0x921CC024** (decomp_all_tm.c:46240).

These are exactly the counters that would log a SILENT SDET-stage drop that the SIPC drop
counters miss.

---

## 2. What mainline mis-sets / skips for port1 (ranked)

### #1 (highest) — mainline NEVER initializes the SDET block at all
`zx_sdetgregtable` is *defined but unused*; its only .c reference is the regdump TODO at
**zx-eth-main.c:4200** (`(TODO) sdet uniN egress_transport_cnt / drop_cnt [need NPP_Sdet offsets]`).
`zx_npp_init` (**zx-eth-main.c:1269-1313**) runs SPA-init (`NPP_REG_SPA_INIT=0`), SIPC (`0x11`),
SMCT (`0xB`/`0x3810`), per-MAC bring-up, UOPC — but has **no equivalent of stock's
`tm_pon_npp_sdet_initial`**. So every SDET per-uni field (maxframe ports 0-4, c_tpid,
smac_md_level, soft-VID, soam_drop) is left at reset/bootloader value. SDET sits exactly
between MAC-RX and the SIPC/classifier; a wrong per-uni maxframe / VID-admit there drops frames
SILENTLY (no SIPC counter) — registering only in the SDET per-uni `egress_drop_cnt`
(0x921C4160+N*4) and `UNIn_DROP_HPMAU_CNT` (0x921CC184+N*4), counters mainline never reads.
Best fit for "MAC1 RX climbs, SIPC drop=0, QMG hw_trap=0, 0 to fabric."

**Why only port1, despite byte-identical config:** the per-port maxframe fields are *interleaved
in shared 32-bit words* — port1 = 0x921C4250[13:0], port2 = the SAME word [29:16]. A reset /
bootloader residual or partial write can leave one half dead while the other (port2) works, and
a debugfs "per-port" dump that reads a whole word can show them identical when the half-words
actually differ. port0 lives in a different word (0x921C4000). This interleaving is the
mechanism by which port1 differs from port2 while "reading identical."

### #2 — logical→regport remap mis-target
Driver has `port_remap[8] = {1,2,3,4,5,0,6,7}` (**zx-eth-main.c:689**) used for FDB/D2 unicast
encoding so DSA logical port1 → **regport 2**. `zx_smac_init_port` and the (absent) SDET/SPA
per-uni init use the *raw* port index, not this remap. If the fabric's uni numbering follows
regport (logical1 = uni2) but the driver indexes per-uni state / diagnostics by raw port, port1's
actual fabric uni is mis-targeted (never admitted), while "port1" in the driver points elsewhere.

### #3 (lower) — SPA per-uni `spa_set_up_reg_pkt_en`
Stock enables it 0..0x4d; mainline does only the bare `NPP_REG_SPA_INIT=0`. SPA *pktdeal* was
confirmed identical earlier, but SPA per-uni *pkt_en* (a different field) was not confirmed set.

SIPC/SMCT ruled out as the gate (shared, not per-port; SIPC poke already disproven).

---

## 3. Concrete tests

### Step A — localize the silent drop (read-only, definitive)
With port1+port2+port3 up on one boot, during a ping to port1 (poke writes literal phys in
`[0x921c0000, 0x923c0000)`):
```
devmem 0x921C4160   # SDET uni0 [7:0]=trans [23:16]=drop
devmem 0x921C4164   # SDET uni1   <-- port1
devmem 0x921C4168   # SDET uni2
devmem 0x921C416C   # SDET uni3
devmem 0x921D45CC   # SPA rcv_uni0 (sop/eop, +N*4 for uniN)
devmem 0x921CC184   # UNI0_DROP_HPMAU (+N*4 for uniN)
devmem 0x921CC024   # sdet_shor_drop_cnt
```
- SPA rcv_uni1 climbs but SDET uni1 trans=0 / drop>0 (or UNI1_DROP_HPMAU>0) → **SDET admit drop confirmed (#1)**.
- SPA rcv_uni1=0 while uni2/3 climb → SPA pkt_en or regport-remap mis-target (#2/#3).

### Step B — read per-port maxframe words, compare halves
```
devmem 0x921C4000   # stock 0x07cc000c
devmem 0x921C4250   # stock 0x07cc07cc  (port1=lo16, port2=hi16)
devmem 0x921C4254   # stock 0x07cc07cc
devmem 0x921C40F0   # stock 0x00008100  (c_tpid)
```
Any port1 half (0x921C4250[13:0]) reading 0 / differing from stock = smoking gun.

### Step C — fix to try (poke first, then driver edit)
Replicate `tm_pon_npp_sdet_initial`:
```
devmem 0x921C4000 32 0x07CC000C
devmem 0x921C4250 32 0x07CC07CC
devmem 0x921C4254 32 0x07CC07CC
devmem 0x921C40F0 32 0x00008100
```
Re-ping port1. **Expected:** `rx_per_ingress[port1]` starts climbing AND SDET uni1
egress_transport_cnt (0x921C4164[7:0]) increments — MAC1 now forwards to fabric.

Driver edit (permanent): add `zx_sdet_init(e)` called from `zx_npp_init` after the SPA/SIPC
oneliners (zx-eth-main.c:1295), writing the four words to `e->base + 0x4000/0x4250/0x4254/0x40F0`,
mirroring stock maxframe=0x07cc + c_tpid=0x8100. If Step A points to SPA/remap instead, also
loop `spa_set_up_reg_pkt_en` for all unis and make per-uni init use `port_remap[port]` (regport),
not raw port.

---

## Key references
- `linux-v6.6/.../zx-eth-main.c:1269` (zx_npp_init — no SDET init), :1226 (zx_smac_init_port),
  :689 (port_remap {1,2,3,4,5,0,6,7}), :4200 (SDET TODO), :2086 (word*4 addr formula).
- `linux-v6.6/.../zx-fpga-reg-tables.h:513` (zx_sdetgregtable, UNUSED), :535 (sipc), :609 (smct).
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c:43182` (tm_pon_npp_sdet_initial),
  :43444 (tm_pon_npp_initial — calls sdet/sipc/sopc/spa initials in order), :24470
  (sdet_set_maxframe_length: port==reg_id), :35356 (tmOnuRegWrite addr formula),
  :46180-46399 (upstream-statistics per-uni counter offsets).
- `tasks/00.10.02.re-stock-kmods/findings/regs/stock_eth_2mib.txt:4097` (live SDET 0x921c4000),
  +lines 0x921c4250/4254/40f0.
- `tasks/00.10.02.re-stock-kmods/findings/DATASHEET.md:386` (SDETG block, base 0x921c4000),
  :411/420 (SIPC/SMCT).
- `tasks/00.01.eth-driver/findings/mac_to_cpu_path_re.md:197,280-389` (pipeline stages + counter phys).

## Bottom line
Mainline omits the entire stock SDET bring-up (`tm_pon_npp_sdet_initial`), leaving the per-uni
frame-validate/VLAN-admit stage between MAC-RX and the SIPC/classifier uninitialized. SDET is the
only per-port admit gate on that path whose drop is invisible to the SIPC counters, and its
per-port maxframe fields are interleaved in shared words (port1 + port2 share 0x921C4250) —
exactly the conditions for a silent, config-invisible, port1-only drop. Confirm with the SDET
per-uni counters at 0x921C4160+N*4 (never read before), then poke the four stock SDET words and
watch `rx_per_ingress[port1]` climb.

## LIVE TEST 2026-05-31 — localized to MAC→SDET (SPA stage), upstream of SDET
RE agent B pointed at SDET. Live-tested with port1/2/3 cabled. Results:
- SDET maxframe word 0x921C4250 = 0x07cc07cc (CORRECT, = stock; port1 low16 + port2 high16 both OK).
  So the "SDET maxframe uninitialized" hypothesis is WRONG — it reads the stock value.
- SDET per-uni transport/drop counters (0x921C4160+N*4, uni=logical port): FIRST HARD per-port signal!
    uni0(port0,no cable)=0 | uni1(port1,FAILS)=transport 2, drop 0 | uni2(port2)=229 | uni3(port3)=230
  MAC1 RX-ok=88 but only 2 reached SDET uni1, and SDET drop=0 → port1's frames are NOT dropped AT the
  SDET; they don't REACH it. The drop is UPSTREAM of SDET, in the SMAC→SPA→SDET path (SADM/SPA stage).
- SPA rcv_uni counters (0x921D45CC+N*4) are byte-packed/interleaved (e.g. 0xe5e5e6e6 = uni2/3 sop/eop
  ~229/230); port1's region low — consistent with SPA not passing port1.
RULED OUT now: SDET (maxframe correct, drop=0), CLA (downstream), SIPC (downstream/shared), HW, static
config. The silent port1 drop is in the SMAC→SPA admit stage (between MAC-RX and SDET). NOTE mainline's
zx_pm_spa_init writes SPA up pkt-enable 0x14000=0xffffffff/0x14004=0xffffffff/0x14008=0x3fff, but stock
loops spa_set_up_reg_pkt_en(i,1) for i=0..0x4d (78 entries) — mainline may not enable port1's per-uni/
per-entry SPA receive. NEXT: compare SPA per-entry/per-uni receive-enable + any SPA/SADM drop counter,
stock vs mainline, for port1's uni. The SDET per-uni transport counter (0x921C4164) is now the live
discriminator (was 2; should climb to match uni2/3 when fixed).
