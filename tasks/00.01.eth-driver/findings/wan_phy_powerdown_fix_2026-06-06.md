# WAN/RGMII link FIXED — ZX5201 BMCR power-down bug (2026-06-06)

## Symptom
On mainline the WAN/RGMII port (DSA lan4, MAC4, external ZX5201 PHY @ MDIO addr 8) did NOT
link to the host NIC (enxc8a362 carrier=0), even though the SAME NIC+cable links fine on
stock (nbif1 @ 1000/FD, 341 Mbit/s). Blocked testing LAN→WAN HW offload on mainline.

## Root cause (VERIFIED LIVE via the new debugfs `mdio` node)
`zx_wan_zx5201_config()` (zx-eth-main.c) ended with `mdiobus_write(8, 0, v | 0x800)`,
commented "power-up (stock plat:3317)". But BMCR (reg0) **bit11 = POWER-DOWN** (standard +
ZX5201). So it left the PHY POWERED DOWN. Live read confirmed: phy8 reg0 (BMCR) = **0x1940**
(bit11 set), BMSR (reg1) = 0x7949 (link bit2=0, AN-complete bit5=0 → link down).

## Fix (validated live, then put in the driver)
Clear bit11 + enable/restart autoneg: `mdiobus_write(8, 0, (v & ~0x800) | 0x1200)`.
Live test: wrote `8 0 0x1340` via debugfs mdio → BMCR settled 0x1140 → **host enxc8a362
carrier=1, speed=1000** immediately. Driver patched (zx_wan_zx5201_config) — pending rebuild.

## New tooling
debugfs `mdio`: `echo "<phy> <reg>" > /sys/kernel/debug/zx_eth/mdio` reads (logs `mdio R phyN regX = V`);
`echo "<phy> <reg> <val>"` writes. phy 8 = ZX5201 WAN (page 9 via the 0x10/0x11 indirect).

## STILL BROKEN — next layer: MAC4 RX datapath
PHY link is now UP (carrier) but **data doesn't pass**: host enxc8a362=192.168.9.50 → device
lan4 (192.168.9.1) ping = 100% loss. So the MAC4 RX-admit / WAN-MAC datapath enable is the
next layer (stock DEFERS the WAN MAC enable to capWAN provisioning — finding wan_port_bringup_re.md:
`MAC4 ctrl |= 3` + ENABLE reg `0x80000001` at mac4+0x08; MAC4 base = e->base+0x140000 = phys
0x92300000, ENABLE = 0x92300008). Also note stock's zx5201_config has an extra `product_vid==' '`
block (reg 0x17 tweaks + b409/b407/b406/b408 page-9 writes) that mainline skips — may matter for
the data path. NEXT: enable the MAC4 RX datapath + re-test ping, then the LAN→WAN offload.

## Cabling (after user simplified to 1 LAN + 1 WAN)
enx2c99 = LAN (a GePHY port; also the U-Boot TFTP port — put 192.168.1.50 here to boot, NOT enx6c70).
enxc8a362 = WAN (lan4/RGMII/ZX5201). enx6c70 = disconnected.

## MAC4 RX datapath — progress (still unsolved, next layer)
After the PHY-link fix (carrier=1, 1000/FD), host→device lan4 ping still 100% loss. Tried LIVE
(poke/mdio on #432) — NONE fixed the ping:
- MAC4 full smac_init regs (mac4 base = 0x92300000): ENABLE 0x92300008=0x80000001, IRQ_MASK
  0x92300004=0xffff, serializer/PHY-iface 0x923000e0=0x00011200 (RGMII mode). (ctrl 0x92300000
  the driver already forces 0xba6003 at boot.) NOT applied yet (RMW, zcon reads flaky):
  mac+0xd00 &= ~0x2 (store-fwd), mac+0xd30 &= ~0x20 (flow-ctrl).
- product_vid PHY block (phy9 0x17=0x1b50; phy8 page-9 b409/b407/b406/b408=0): no effect.
⇒ The block is NOT the MAC registers — it's the INGRESS RX-admit pipeline for the WAN port
(SPA admit for port 4 / the per-port bridge+forward config / SOPC ingress bridge — the egress
work enabled SOPC for TX only). NEXT: RE the WAN-port ingress RX-admit (compare a working LAN
port's SPA-admit + bridge config vs MAC4's); localize with the device lan4 rx_packets counter
(needs reliable device access — zcon UART floods/hangs; consider reading via the kmsg2uart or a
fresh boot). The PHY-link fix (driver-patched) is the validated win regardless.

## MAC4 RX localization (2026-06-06): device receives ZERO on WAN RX
Host-side tcpdump (reliable): host enxc8a362=192.168.9.50 ARPs "who-has 192.168.9.1" repeatedly,
device sends NO reply. Device-side: lan4 rx_packets = 0 while the host ARPs. ⇒ the WAN frames
never reach the lan4 netdev — the break is at MAC4 RX (hardware/RGMII RX) OR the DSA RX-demux/tag
(frames hit the conduit but aren't demuxed to lan4), NOT just the L3/admit. PHY link is up
(carrier=1 both sides), so it's MAC/RGMII-RX or fabric-RX-admit, not the PHY.
NEXT (systematic, fresh boot for reliable access): (a) check conduit `sw` rx_packets while the
host ARPs — if sw rx climbs but lan4=0 → DSA demux/tag issue for the WAN port; if sw rx=0 too →
MAC4/RGMII RX or fabric-admit. (b) compare the full RX path config of a WORKING LAN port (lan2,
which RXes fine) vs MAC4/WAN: the SPA per-port admit, the RGMII RX clock/delay (pin_mux/sys_ctrl),
mac+0xd00/0xd30 (store-fwd/flow-ctrl, not yet tried), and the fabric ingress port-enable for
regport 5 (=WAN). The egress (TX) path was solved separately; RX-admit for the WAN uplink is the
gap. zcon UART is flaky/floods — use a fresh boot + read at idle, or kmsg2uart.

## WAN RX chain FULLY LOCALIZED (2026-06-06, kernel #433, PHY fix baked + auto-up at boot)
Read via pipeline_stats (cat = reliable; zcon needs ~16s wait + separate cats, NO $() substitution;
poke-peek printk does NOT reach UART — kmsg2uart not auto-started on fresh boot). Host ARP burst →:
  PHY link        ✓ carrier=1 1000/FD AT BOOT (driver PHY fix works)
  MAC4 RGMII RX   ✓ smac4 RX_pkts=48, no crc/ovf/wdog errors  (RGMII RX hardware WORKS)
  SPA admit       ✓ uni4 SPA_rcv=0x00001d1d climbs            (SPA receives the WAN frames)
  QMG DN          ✓ sw_fwd=28 (hw_trap=13)                    (QMG forwards DN→SW)
  SIPC/RED        ✗ RED[0x1a044]=94 drops, SIPC drop=0x05080000 → conduit sw rx_packets=0
⇒ The WAN (uplink/MAC4) ingress uses the DOWNSTREAM (DN, network→CPU) TM path; frames reach the QMG
(forwarded to SW) but are DROPPED at SIPC/RED before the conduit netdev — so lan4 rx=0 and the device
never sees/replies to WAN ARP. The LAN ports (lan0-3) ingress via the UP path (works → CPU). The DN→CPU
delivery (SIPC ring / RED) for the WAN port is the remaining gap — NOT the MAC, PHY, SPA, or QMG.
NEXT: RE the DN→CPU SIPC/RED config (compare the DN RX-desc ring / SIPC setup vs the working UP path;
the SIPC drop 0x05080000 + RED 0x1a044 are the smoking gun). Likely the DN RX descriptor ring / BPPE
for the CPU isn't provisioned, or RED/SIPC thresholds drop DN-to-CPU. This is a TM-pipeline (DN path)
bring-up, separate from the PHY/MAC fix. Counters: RED 0x9231a044, SIPC drop in QMG dump, SADM 0x921c4208.

## WAN RX dies at QMG-ingress RED (same mechanism as the LAN RED-wedge) — 2026-06-06
Per user hint ("read the docs, they were about LAN"): the RED-wedge RE (redwedge_debug_state.md,
memory zte-redwedge-unicast-cpu) localized LAN port1 unicast→CPU drops at the SAME counter
RED[0x1a044]=0x921da044, "RED rejects at ingress-to-QMG". Delta test confirms the WAN is the same:
WAN burst → RED[0x1a044] +12, but QMG DN sw_fwd / hw_trap UNCHANGED → the WAN/DN frames are
RED-rejected BEFORE the QMG fwd/trap split (at QMG-ingress enqueue). Disabling the 0x92344000 RED
block (RED_CFG 0x92344004=0) did NOT help → the reject is the QMG-side RED (zx_tm_red_init via
0x921c4014 per-queue), NOT the 0x92344000 out-buffer block. For the WAN it drops from a CLEAN BOOT
(not a load/relink wedge like LAN) → the DN/WAN CPU-queue's RED per-queue cfg is wrong from the start
(zx_tm_red_init loops q=0..399/0..383 — the DN-path queue for the WAN uplink may be outside the
configured set or mis-typed). 
NEXT: find the QMG ingress queue the WAN/DN frames enqueue to (vs the working LAN/UP queues q2/q4/q5),
read/compare its RED per-queue cfg (RED indirect read: cmd 0x921c4014=q|type<<22|rw<<27, data 0x921c401c),
and provision it (zx_red_set_queue_cfg for that q/type) — then re-test WAN ping. This is the same hard
QMG/RED block the LAN redwedge hit; the LAN RE's lever list (RED disable, QMG thd raise, per-queue
re-apply) was inconclusive for the wedged state but the WAN (clean-boot mis-config) may yield to a
correct per-queue provision. NOTE: I left the 0x92344000 RED block disabled (0x92344004=0) — reboot
restores; re-enable or reboot before relying on LAN/egress.

## READS UNBLOCKED + QMG/RED wall (2026-06-06)
**Reliable reads fix:** the flaky zcon reads were a CONSOLE LOGLEVEL issue, NOT UART flood:
`echo 8 > /proc/sys/kernel/printk` on the device → poke-peek/mdio pr_info now reaches the UART
console → zcon captures them. (Do this first thing after every boot for register reads.)
QMG config read (loglevel 8): 0x9234c000=0x03f40fa0, c004=0x00000002, c008=0, c00c=0x000003ff,
c010=0x00000faa. RED drop counter 0x921da044=0xb4 and climbs +N per WAN ARP burst.
**WALL:** the WAN RX→CPU is blocked at the QMG-ingress RED reject (drop 0x921da044) on the DN path.
This is the SAME QMG/RED/OPC block the LAN port1 RED-wedge RE hit (memory zte-redwedge-unicast-cpu,
redwedge_debug_state.md) and that RE was INCONCLUSIVE — a latched/mis-provisioned HW state with NO
public datasheet (Sanechips in-house IP). The QMG/RED register fields (thresholds, per-queue share,
DN-vs-UP queue domains) aren't decoded. Cracking the WAN RX needs either the QMG/RED register map
(datasheet/deeper stock decomp of red_set_queue_cfg/qmg + the DN queue→share mapping) or a TM/QMG
soft-reset lever. This is the same hard wall for both LAN-wedge-recovery and WAN-RX-bring-up.
**State of the WAN port:** PHY link FIXED + baked (host 1000/FD at boot); MAC4 RGMII RX + SPA admit
WORK; only the DN→CPU QMG/RED delivery is blocked. TX/egress (CPU→MAC4) was solved earlier.

## ★★★ WAN RX→CPU ROOT CAUSE FOUND (2026-06-06, user hint "check main"): dual-RX-ring, DN uses ring 1
The git history (main commit ce365bd13 "tm[0x4068] bit14 ring-selector") revealed TWO RX rings per
queue, packed in the per-q count tm[0x10100+q*4]: LOW-16 = ring 0, HIGH-16 = ring 1. SMOKING GUN
(live, WAN flood): q7 count 0x9235011c = **0x000d0000** → HIGH-16=13 pending (ring 1), LOW-16=0.
zx_tm_napi_poll reads `pending = status & 0xffff` (ring 0 ONLY) → sees 0 on q7 → NEVER drains ring 1
→ the WAN/DN frames pile in q7/ring1 until the ring fills → dropped (the "RED" drop was the ring
filling). **LAN/UP ingress uses ring 0 (q2/q4/q5); WAN/DN ingress uses ring 1 (q7).** The driver
only implements ring-0 draining → WAN RX→CPU never reached the conduit (lan4 rx=0).
FIX: drain ring 1 in zx_tm_napi_poll — read HIGH-16 pending (status>>16), consume ring-1 descriptors,
release with tm[0x4068] bit14=1 (the ring-1 selector). Need the ring-1 RX-desc base (separate from
rxdesc_cpu/ring0). This is a real dual-ring RX feature; the DN→CPU path was simply never drained.

## ★★★★ WAN RX→CPU ROOT CAUSE (REAL, 2026-06-06): the DN RX ring (ring 1) was never drained
User lead ("we solved this for LAN — use the findings + main commits"). RE (2 subagents, stock decomp
+ git history → findings/wan_dn_ingress_to_cpu_re.md). PROVEN:
- The chip has TWO RX descriptor rings per queue, packed in TM[0x10100+q*4]: LOW16 = ring 0 (UP/LAN),
  HIGH16 = ring 1 pending COUNT (DN/WAN). (iter30's "HIGH16=cursor" was WRONG.)
- Single HW base TM[+0xF0]; HW derives ring1 = ring0_region + 0x20000 (stock pon_tm_queue_init). No
  separate ring-1 base reg. Both share the one BP pool. Release: TM[0x4068] bit14 = ring (0/1).
- Stock pon_tm_net_poll drains BOTH rings; mainline zx_tm_napi_poll read ONLY LOW16 → the WAN/MAC4
  uplink (DN path) frames piled in ring 1 (live q7 = 0x000d0000, HIGH16=13 pending) and were NEVER
  drained → WAN RX→CPU never worked (lan4 rx=0). This is the DN-path mirror of main commit ce365bd13
  (which fixed only the ring-0/UP release). The RED/SIPC "drop" I chased was the symptom (ring 1 full).
- All the per-port LAN fixes (c37e6168f port_vlan_filter i<10, trap-queue port<8, 88e1ba385 MAC4) DO
  include regport 5 — so it was NOT a per-port loop bound; it was the missing ring-1 (DN) drain.
FIX IMPLEMENTED (zx-eth-main.c, compiles): rxdesc_dn_cpu = rxdesc_cpu + 0x20000 (+ rx_head_dn[8]);
zero both rings (0x40000) in zx_tm_alloc_pools; zx_tm_napi_poll now loops ring 0 then ring 1
(pending = ring?status>>16:status&0xffff; desc_base/heads per ring; release bit14=ring). Pending HW test.

## ✅✅✅ WAN RX→CPU WORKS (2026-06-06) — dual-ring DN drain CONFIRMED ON HW
Booted the dual-ring fix: host enxc8a362=192.168.9.50 → device lan4 (192.168.9.1) ping =
**20/20 received, 0% loss, 11.4ms avg.** lan4 rx_packets climbs (34); q7 TM[…011c] HIGH-16
drained to 0 (ring 1 DN frames consumed). The WAN port is now FUNCTIONAL end-to-end:
PHY link (power-down fix) + MAC RX + SPA admit + **ring-1 DN drain** (RX→CPU) + TX/egress
(earlier). THE WAN NEVER WORKED BEFORE; it works now. Two driver fixes this session:
(1) zx_wan_zx5201_config BMCR power-down bit11 clear (+AN); (2) zx_tm_napi_poll drains RX ring 1
(HIGH-16, DN path) — rxdesc_dn = rxdesc + 0x20000, release tm[0x4068] bit14=1.
NEXT: with WAN RX→CPU working, set up the proper LAN→WAN routed rig with a REAL matured iperf3 flow
(bidirectional, conntrack ESTABLISHED) and finally test the HW offload (CLA+PM recipe) for the real
LAN→WAN case — the condition the FFE is designed for (earlier offload tests used user→user + hping3).
