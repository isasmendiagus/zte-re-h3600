# IDM CPU-port → fabric forwarding RE (2026-05-28)

**Question:** IDM DMA consumes the descriptor (`npp+0x8044` +3) but the frame
never reaches QMG sw_fwd (`0x9234c044`=0). What stock fabric/forwarding config
does mainline OMIT between "IDM consume" and "QMG"?

**TL;DR — top hypothesis:** Stock, in LAN-only mode (`lan_up==1`), sets the
**`PON_PP_TM_CFG`** register = **phys `0x923a001c`** (= fpga reg-id `0xe8007`)
to enable the **WAN/CPU port → TM fabric forwarding** bit
`1 << (lan_up_port + 0x19)`. With `lan_up_port = 4` that is **bit 29
(0x20000000)**; the live stock dump reads `0x923a001c = 0x21200000` and the boot
log shows it transition `0x21200000 → 0x23200000` (adds bit 25 too). **Mainline
NEVER writes `0x923a001c`** — it explicitly reasoned this write away as
"not the boot path" (zx-eth-main.c:1082-1086, 1296-1299). That reasoning is wrong
for the H3600: it IS a LAN-only ONT (`g_pon_work_mode==0x10` → `lan_up=1`). The
CPU-port frames are consumed by IDM DMA but the TM/PP fabric is not told to
forward CPU/WAN-port traffic, so they die before QMG. Note `0x923a001c` lives in
the **ETH_TM2 block (0x923a0000)** which is **clock/reset-gated** (see
`fpga_access_and_egress_clock_re.md`) — the write only latches after the TOPCRM
reset-deassert edge.

---

## Decomp evidence chain

### 1. The device is in lan_up mode → the lan_up-only forwarding writes run
`init_module` @ plat:8889 (`decomp_all_plat_zxylzb_9128S.c`):
```c
g_pon_work_mode = zte_get_pon_mode();
if (g_pon_work_mode == 0x10) lan_up = 1;          // plat:8906-8907  (H3600 = LAN-only)
...
if (lan_up != 0) {                                 // plat:8937  <-- THIS BRANCH RUNS
    *(uint*)(pp_base + 0x2c) |= 1 << ((lan_up_port + 0x19) & 0xff);   // plat:8938-8940
    zx_pon_clk_reset();                            // plat:8941
}
```
(The `"mac learn:..." + pp_base + 0x2c` in the decomp is a Ghidra string-cast
artifact; the string is at offset 0, so the access is `pp_base + 0x2c`.)

### 2. PON_PP_TM_CFG is set by tm_set_pp_wan_cfg (the real fabric gate)
`tm_set_p2pmode` @ tm.c:35981 → `tm_set_pp_wan_cfg` @ tm.c:35962:
```c
void tm_set_p2pmode(uint port){ lan_up_port = port; tm_set_pp_wan_cfg(port & 0xff); }
void tm_set_pp_wan_cfg(int port){
    uVar1 = fpga_read_reg(0xe8007);                // "PON_PP_TM_CFG=0x%x"
    fpga_write_reg(0xe8007, uVar1 | 1 << ((port + 0x19) & 0xff));   // tm.c:35972
    // "after PON_PP_TM_CFG=0x%x"
}
```
`fpga_read_reg(id) == readl(0x92000000 + id*4)` (confirmed in
`fpga_access_and_egress_clock_re.md`). So:
- **reg-id `0xe8007` → phys `0x92000000 + 0xe8007*4 = 0x923a001c`.**
- `0x923a001c` is at `pp_window(0x92388000) + 0x1801c`, inside the **ETH_TM2
  egress region (0x923a0000)**.
- bit = `1 << (lan_up_port + 0x19)`; `lan_up_port=4` → `1<<29 = 0x20000000`.

`tm_set_p2pmode` is driven by `sw_set_p2pmode`/`sw_set_uni_as_wan` (switch.c:2256,
2717, 4407, 4442) during switch `init_module`. Boot log (`eth_init_flow_2026_05_26.md:109`):
`PON_PP_TM_CFG=0x21200000 → after = 0x23200000`.

### 3. Live stock dump confirms the value (regs/stock_eth_2mib.txt)
```
923a0000 00000000   923a0004 00000001   923a001c 21200000   923a0020 4eb20000
923a00e0 00000000   <- direct-mux OFF (fabric path, matches oracle)
9238802c 00000000   <- pp[0x2c] reads 0 live (NOT the active gate)
921c8000 020f6766   <- IDM CONTROL bit25 set (mainline already matches)
```
`0x923a001c = 0x21200000` = bits **{29, 24, 21}**. Bit 29 = the
`lan_up_port=4` WAN/CPU forwarding-enable. (`pp[0x2c]` reads 0 live, so the
init_module `pp[0x2c]` write is NOT the durable gate — **`PON_PP_TM_CFG` is**.)

---

## Answers to the 4 questions

**Q1 — what classifies/forwards an IDM CPU frame into the fabric (→ QMG sw_fwd)?**
The CPU/WAN port must be enabled in **`PON_PP_TM_CFG` (0x923a001c)** via
`bit (lan_up_port+0x19)` (bit 29 for port 4). This is the per-(WAN/CPU)-port
"forward into TM" enable. Without it the IDM DMA still consumes descriptors
(`npp+0x8044` advances) but the PP/TM fabric never accepts the CPU-port packet,
so QMG sw_fwd stays 0 — exactly the live symptom. (The IDM CONTROL reg
`npp+0x8000=0x020f6766` and ring bases are NOT the gate; mainline already
matches those. Per-port egress masks `TM[0x4040]=0x3ff` and `NPP[0x19068]` SOPC
bridge are also already present per `tx_consume_engine_re.md`.)

**Q2 — descriptor egress_port field (skb cb[0xb7] → word1 bits[31:28])?**
For the LAN/bridge host path it is **0 / "let FDB decide"**. cb[0xb7] is only set
to an explicit port by the WiFi→IDM forward RX path `idm_fdb_recv_handle`
(idmfdb:16, `cb[0xb7]=param[3]`) and consumed in `idm_fdb_forward` — that is the
**RX/ingress** ssid, not a TX egress override for routed/bridged host frames. For
CPU→LAN, leave word1 bits[31:28]=0; PP_BRG DA-lookup routes dst-MAC to MAC2
(oracle: `send2smac2` 0x921d9164 counts on stock).

**Q3 — does the LAN/br0 netdev use `idm_net_tx` or `pon_tm_net_tx`?**
**`pon_tm_net_tx`** — NOT `idm_net_tx`. The `sw` (LAN) and `pon` netdevs are
created by `pon_tm_net_register` (plat:6385) which binds
`pon_tm_net_netdev_ops`; only `idm0`/`idm1` use `idm_net_register` +
`idm_net_netdev_ops`. `pon_tm_net_tx` (plat:6719), in the `sw` (dir=0) +
`lan_up==1` branch (plat:6790), builds a 16-byte TM desc with egress port
`((lan_up_port+0x28)&0x3f)<<4` and calls
`pon_tm_data_raw_send(skb,desc,0)` → `soft_insert_tx_1desc` →
**`tm_base+0x10054 = 1`** (UP-ring kick).

> **This directly contradicts the prior `stock_cpu_lan_inject_path_re.md`
> conclusion** that LAN egresses via the IDM ring. It does NOT. It uses the TM
> UP ring. It ALSO contradicts the oracle's `TM[0x10054]==0`-while-egressing
> reading. Reconciliation: the oracle was a *different* (slot-B factory) boot and
> either (a) read a stale/aliased 0x921d0054, or (b) that boot's `lan_up`/desc
> path differed. The decomp is unambiguous: `pon_tm_net_tx` DOES kick
> `TM[0x10054]` whenever `pon_is_registered()` (plat:7712, always returns 1).
> **The egress path is the UP ring + PON_PP_TM_CFG gate, not the IDM ring.**
> (The user's current IDM-ring xmit is therefore on a path stock does not use
> for LAN egress — which independently explains why it dies: even with a correct
> ring, the CPU-port is not enabled in PON_PP_TM_CFG.)

**Q4 — what does mainline's init OMIT?**
The single highest-value omission: **`PON_PP_TM_CFG` (0x923a001c) is never
written.** Mainline deliberately skips both bit-25/29 writes (comments at
zx-eth-main.c:1082-1086 "lan_up ... is not the boot path" and 1296-1299 "stock
doesn't set bit 25 — wrong"). For the H3600 `lan_up=1`, so stock DOES set it.
Already-flagged but never landed in `tx_consume_engine_re.md:124-126`.
Secondary: the ETH_TM2 block (0x923a0000) is clock-gated — the write only sticks
after the TOPCRM[0x08] reset-deassert edge (`fpga_access_and_egress_clock_re.md`).

---

## Prioritized HYPOTHESIS + poke tests

**H1 (highest) — enable the CPU/WAN port in PON_PP_TM_CFG.**
The IDM/UP ring fetches the frame but the PP/TM fabric drops it because the
source (CPU/WAN) port is not forwarding-enabled. Set
`0x923a001c |= (1<<29) | (1<<25)` to match stock's `0x23200000`.

POKE TEST (run FIRST):
```
mem  0x923a001c                 # baseline — expect 0x00000000 (mainline) or 0x00200000/0x01200000
poke 0x923a001c 0x23200000      # stock final (bits 29,25,24,21)
mem  0x923a001c                 # MUST read back 0x23200000
# then re-run txtest 3 and read:
mem 0x921c8044                  # IDM consume (+3 expected, as before)
mem 0x9234c044                  # QMG sw_fwd  <-- WANT THIS TO MOVE NOW
mem 0x921d9164                  # SOPC send2smac2
mem 0x92280718                  # MAC2 TX-OK
```
- If `0x923a001c` does **not** read back `0x23200000` → the ETH_TM2 block is
  clock-gated. Do the TOPCRM reset edge first
  (`fpga_access_and_egress_clock_re.md` §"Exact gate sequence": TOPCRM[0x0c]|=0x1e0;
  TOPCRM[0x08]&=~0x30; |=0x20; |=0x10; SYSCTRL[0x10]&=~0x800), then re-poke.
- If it reads back but QMG sw_fwd still 0 → also set the init_module pp[0x2c] bit:
  `poke 0x9238802c (cur | (1<<29) | (1<<25))` and re-test.

**H2 (only if H1 makes sw_fwd move but nothing egresses) — match the stock TX
path, not the IDM ring.** Stock LAN egress is `pon_tm_net_tx` → UP ring
(`TM[0x10054]` kick) with desc egress-port `((lan_up_port+0x28)&0x3f)<<4`
(=`(4+0x28)&0x3f = 0x2c → <<4`), NOT `idm_net_tx`. If the IDM ring path cannot be
made to forward even with PON_PP_TM_CFG set, switch the LAN xmit back to the
UP-ring path (mainline `zx_sw_xmit`) which is the architecturally-correct stock
clone, and keep H1's PON_PP_TM_CFG enable. The IDM ring is for idm0/idm1
(WiFi/host-mgmt), not the bridged LAN data path.

**H3 (cheap, do alongside) — lan_up_port value.** Stock uses `lan_up_port=4`
(live `0x923a001c` bit 29 confirms). If you instead see the device configured
port 0, the bit would be 25. Setting `0x23200000` covers both (25 and 29).

### Register reference (phys ↔ npp/pp offset)
| name | phys | offset | stock value | mainline | gate? |
|---|---|---|---|---|---|
| PON_PP_TM_CFG | **0x923a001c** | pp+0x1801c / fpga 0xe8007 | **0x21200000→0x23200000** | **unset (0)** | **YES — the gate** |
| pp[0x2c] CPU_FWD | 0x9238802c | pp+0x2c | 0 live (write transient) | unset | secondary |
| IDM CONTROL | 0x921c8000 | npp+0x8000 | 0x020f6766 | 0x020F6766 ✓ | no (matches) |
| IDM TX kick | 0x921c8040 | npp+0x8040 | nframes<<16 | ✓ | no |
| IDM consume | 0x921c8044 | npp+0x8044 | +N consumed | ✓ | no |
| QMG sw_fwd cnt | 0x9234c044 | — | climbs w/ TX | 0 | symptom |
| ETH_TM2 direct-mux | 0x923a00e0 | — | **0** (fabric path) | leave 0 | keep 0 |
