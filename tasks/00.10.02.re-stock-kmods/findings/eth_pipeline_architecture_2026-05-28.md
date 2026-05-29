# ZX279128S ethernet block — architecture map (2026-05-28)

Reconstructed from stock kmod decomp + U-Boot decomp + live tracing. This is the
"how the switch/TM actually moves a packet" reference. The SoC ethernet is an
integrated **L2 switch + GPON-style Traffic Manager (TM)**, not a simple MAC.

## MMIO layout (from DTS `ethernet@921c0000` + live)
DTS reg windows: `pon` = 0x92000000 (0x1c0000), `npp` = **0x921c0000 (0x200000)**
(covers 0x921c0000..0x923bffff), + sys_ctrl/pin_mux/pon_serdes.
Driver `e->base` = the npp window (0x921c0000). **All offsets below are
`e->base + off`; phys = 0x921c0000 + off.**

| block | e->base off (phys) | role |
|---|---|---|
| TM IRQ/queue | 0x0100 (0x921c0100) | TM[0x100] IRQ status/mask |
| BMU | 0x8000 (0x921c8000) | buffer mgmt unit (BP alloc/free), 5 instances |
| QMG | 0xc000 (0x921cc000) | queue manager (sw_fwd/hw_fwd/hw_trap) |
| TM DMA | 0x10000 (0x921d0000) | UP ring kick=0x10054 / DN=0x10064; consume cnts |
| SCH/DSCH | 0x14000 (0x921d4000) | downstream scheduler (token-bucket shaper, indirect RAM) |
| NPP (SIPC/SPA/SDET/SOPC) | 0x19000 (0x921d9000) | network proc; SOPC send2smacN = crossbar→MAC |
| RED | 0x184000-ish (0x92344000) | random-early-detect / congestion |
| PP ctrl | 0x1c0000 (0x923c0000?) see note | packet processor control (CPU_FWD etc.) |
| PP_BRG | 0x1c8000 (0x92388000) | bridge: FDB, VLAN, isolation, flood, learn |
| ETH_TM2 mux | 0x1e0000 (0x923a0000) | **U-Boot direct-egress mux** (0xe0=0x11 + MAC slots 0x78/7c). Mapped, but kmot/mainline leave it 0 (not clocked) |
| SMAC[i] | (i+1)*0x40000 | per-port MAC. MAC2=0xc0000 (0x92280000)=LAN3/host. ctrl+0x00 / IRQ_MASK+0x04 / ENABLE+0x08 / iface+0xE0 / TXcnt+0x714.. / RXcnt+0x780.. |
| IDM | (idm regs) | CPU-port DMA (idm0/idm1 netdevs, WiFi fwd) |

IRQs (DTS): tm=GIC36 (CPU↔switch ⭐), npp=35, idm=38, pon=66, pp=37. PHYs: 4
GePHYs on mdio@9a101000 (addr 10..13), driven by phy-zte-gephy (LDO/TX-DAC).

## TX path (CPU → LAN), the one we're fixing
```
CPU build 16B desc @ UP ring -> kick TM[0x10054]=1
  -> TM dequeues -> QMG (forward decision: sw_fwd vs hw_fwd)
  -> DSCH (per-queue token-bucket shaper: needs CREDIT or it DROPS)  <-- was the drop gate
  -> RED
  -> SOPC send2smacN  (egress-PORT pick / crossbar -> physical MAC[N])  <-- current gate
  -> SMAC[N] TX -> wire
```
DA routing: PP_BRG FDB lookup on dst-MAC → internal port; host MAC learned on
internal port 3 = MAC2/LAN3. Two egress ARCHITECTURES exist:
- **Fabric (stock kmod + our driver):** UP ring → fabric → PP_BRG DA-lookup → port.
- **Direct mux (U-Boot):** UP ring → ETH_TM2 mux (0x923a00e0=0x11) + MAC slots →
  MAC, bypassing the fabric. Simpler; proven working in U-Boot.

## RX path (works)
wire → SMAC[N] → CLA (classify, RX-side) → QMG → trap to CPU queue → IDM/NAPI →
netdev. Loopback detect: frame arriving with SMAC==own → counted as
tm_rx_loopback_drops (the CPU-TX-hairpin symptom).

## Pipeline counters (free-running readl, for stage tracing) — see pipeline_counter_map.md
CLA fwd/trap/drop 0x1cc3cc/d0/d4 · QMG sw_fwd/hw_fwd/hw_trap 0x18c044/48/4c ·
DSCH drop 0x1a04c, queues 0x1941fc/0x194200 · SOPC send2smac0..4 0x19915c..0x19916c ·
SMAC[N] TX 0x..0714/0718/071c · drops PP 0x1a040 / RED 0x1a044 / DSCH 0x1a04c.

## DSCH shaper indirect protocol (the SCH fix)
SCH RAM via TM[0x14014]=CMD (`addr | ramid<<22 | indRwEn<<27 | incrEn<<31`),
TM[0x14018]=DONE(poll bit0), TM[0x1401c]=DATA. Write = poll→cmd(write)→data.
Per-queue shaper: RAMID2 fill-rate, RAMID3 bucket-cap, addr=que+unit*8. Per-tcont:
RAMID5/6, addr=unit. Stock fills it (init default 1600000, then cspd refines via
`tc ... root sp ... linkspeed`). Mainline now replays the init default in zx_sch_init.

## Current status of each stage (mainline, 2026-05-28)
RX ✓. UP ring/desc ✓. QMG forwards ✓. **DSCH drop FIXED** (shaper credit). PP_BRG
flood/isolation/aging/FDB ✓ (host MAC learned port 3). **Open gate: SOPC** — frame
passes QMG+DSCH but reaches NO send2smacN and SMAC[N] TX never increments → the
fabric egress-port pick / SOPC handoff doesn't deliver to MAC2. MAC HW itself works
(U-Boot egresses via the direct mux). Note: enabling/reconfiguring the MAC in-driver
(after pon_reset wipes U-Boot's config) breaks RX / storms — U-Boot's MAC+direct-mux
config is self-consistent; mixing U-Boot-MAC with fabric-egress is not.

## Two ways forward
A. Crack the fabric SOPC egress (why send2smacN never fires for a CPU frame whose
   DA is FDB-resolved to port 3).
B. Adopt U-Boot's direct-mux egress: clock+program ETH_TM2 (0x923a00e0=0x11 + MAC
   slots 0x923a0078/7c) + QMG[0]=0x11 + U-Boot TX desc format (desc[0xc]=2, no 0xc9).
   Known-working architecture; bigger change.
