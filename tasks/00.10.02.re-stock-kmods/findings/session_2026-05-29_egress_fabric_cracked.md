# TX-egress: FABRIC GATE CRACKED — frames reach MAC2 TX; final gap = MAC→PHY MII (2026-05-29)

Read this FIRST to resume. Supersedes `session_2026-05-28_tx_egress_state.md` for the
egress problem. Full journey in STATE.md #21.

## TL;DR
The months-long "CPU→LAN frame dies before any physical MAC" gate is **SOLVED**. CPU→LAN
frames now traverse the entire switch fabric (`QMG sw_fwd → RED → DSCH → SOPC send2smac2 →
MAC2 TX counter`), routed only to MAC2 (host port), zero drops. **The only thing left is the
last hop: MAC2 → GePHY → copper** (MAC counts TX, host NIC sees nothing, no errors).

## The two fixes (both in `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`)

### 1. MAC init-order wipe (real bug)
Probe runs `zx_npp_init → zx_smac_init_port` (~L4753) BEFORE `zx_eth_init_pon_chip →
pon_reset(0xffffffff)` (~L4763). pon_reset WIPES the MAC block (MASK/ENABLE/+0xe0 → 0).
`adjust_link` then only re-wrote `MAC_REG_CONTROL`, never the full smac_init. Live-confirmed:
MAC2 MASK=0, ENABLE=0 after boot. **FIX**: in `zx_eth_adjust_link`, on link-UP call
`zx_smac_init_port(e, i)` (full re-init: CTRL+MASK+ENABLE+iface+NPP-enable) instead of just
CTRL. Verified: MAC2 now boots MASK=0x3fff / ENABLE=0x80000001 with no pokes.

### 2. THE egress-port hint (the fabric gate)
**kotrace of LIVE stock egress** (`tasks/00.01.eth-driver/scripts/kotrace_egress_capture.py`,
host ping → device ICMP replies, 136/136 frames identical) showed the egress call chain:
```
pdt_ethdrv_send → pon_tm_net_tx → pon_tm_get_next_txdesc(1)
  → pon_tm_data_raw_send(skb, desc, dir=1) → pon_tm_bmu_alloc_bp → soft_insert_tx_1desc(desc, dir=1)
```
The DN-branch descriptor (decomp plat:6834+, DA-known) encodes the **egress port** as
`desc[2:3] = ((port + 0x28) & 0x3f) << 4` (plat:6848). **Mainline hardcoded `0`** → the switch
fabric had no destination port → SOPC never selected a MAC → `send2smac2=0`. Setting the hint
(`zx_eg_port`, default 4 = stock's lan_up_port) → frames now reach `SOPC send2smac2` and the
`MAC2 TX` counter (+N each, only smac2). Module param `zx_eg_port` (uint, 0644) is added but
NOT exposed at `/sys/module/zx279128_eth/parameters/` (built-in) — set via kernel cmdline
`zx279128_eth.zx_eg_port=N` or rebuild to sweep.

Working-to-MAC config: **UP ring + DUAL kick (shared ring, UP_BASE=DN_BASE=txdesc_dma) +
desc[0]=0xc9 + egress-port hint**. (The DN-ring rewrite — desc[0]=0x80, separate dndesc base,
single 0x10064 kick — was implemented then REVERTED: it didn't reach QMG and hit warm-boot
pending pollution; see below.)

## Address-map saga RESOLVED (closes #11–#15)
The "stock egresses ring-lessly / all rings flat" conclusion was the **wrong-base read**:
prior oracles read `0x921d00xx` (= SMCT, npp+0x10000) instead of the REAL TM ring at
`0x9235xxxx` (tm_base+0x10000). Measured correctly this session
(`tm_ring_correct_base_remeasure.py`): during stock egress, **DN consume `0x92350068`=0x00000001
(high16=0)**, DN kick=1, UP ring 0, **QMG sw_fwd climbs +166**. So: the DN ring IS used; the
egress signal is QMG sw_fwd, NOT a ticking ring counter; `tm[0x10068]` sits at ~0x00000001.

## Falsified this session (don't re-chase)
- **DN tcont shaper credit**: mainline DN tcont (RAMID 0xe/0xf) was WIDE-OPEN (0x1fffff/0x7ffffff
  = HW default), NOT 0; poking it DOWN to stock values only caused drop_DSCH. (`sch_shaper_dump.py`)
- **SOPC↔MAC bridge enable** 0x19068: writable, latches (bits[4:0]); set it → still no egress.
- **Egress-block clock-gating**: control reg 0x19004 latches+restores cleanly → not gated.
- **MAC-enable alone** (Journey #18/#19 PM/SPA direct config): necessary but not the gate.

## FINAL GAP — MAC2 → PHY → copper
MAC2 counts frames TX'd (`TX_frames 0x92280718` +40, `TX_bytes 0x92280714` +2720) but:
- host `tcpdump` (broad, no filter) sees ZERO device-originated frames;
- host NIC `rx_packets`/`rx_errors`/`rx_crc_errors` ALL unchanged → **not bad-CRC/BP-flush**
  (ruled out — the frames aren't arriving at all, errored or not).
So the GePHY isn't driving copper on TX (RX through the same MAC2+PHY works → link up).
Cause = MAC↔PHY MII TX interface. MAC2 MII regs (zx_smac_init_port [Iter21] U-Boot-derived):
+0x70=0x300002 ✓, +0xb4=0x4000 ✓, but **+0xc20=0 (exp 0x32), +0xc50=0 (exp 0xa8),
+0xb00=0xff01 (exp 0x10ff11)** — though +0xe0/+0xc20/+0xc50 may be write-once (read 0 ambiguous).

## Resume plan
1. RE why the `+0xc00`-block MII writes don't land on MAC2 (write-once? clock-gated sub-block?
   wrong order in adjust_link's smac_init re-run? GePHY TX-side config?). Compare stock MAC2
   MII state + GePHY (MDIO 9a101000 addr 12) during working egress vs mainline.
2. Confirm whether MAC2 +0xc20/+0xc50/+0xb00/+0xe0 are write-once-consumed (then they're fine
   and the gap is the PHY TX/MII clock) or genuinely unset (then fix the smac_init write path).
3. Once MII TX drives copper → on-wire egress. Then refine: the priming-frames-needed quirk,
   and reconcile UP-vs-DN (kotrace says stock uses DN; UP works for us — likely both egress
   with the port hint, but match stock for upstreaming).

## Device state
Mainline in RAM (power-cycle → stock). Source has both fixes (MAC init-order + egress-port).
Bridge on :9999. Build = UP/dual-kick shared-ring + egress-port=4. New scripts in
`tasks/00.01.eth-driver/scripts/`: kotrace_egress_capture.py, tx_egress_oracle.py,
sch_shaper_dump.py, mainline_egress_verify.py, mainline_dn_tcont_test.py, mainline_mac_enable_test.py.
Golden stock profiles in `tasks/00.01.eth-driver/captures/stock_state/`.
