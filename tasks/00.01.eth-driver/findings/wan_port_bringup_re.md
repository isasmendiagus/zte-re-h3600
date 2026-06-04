# ZX279128S WAN ethernet port bring-up (stock RE)

**Status: static RE of stock kmods (plat-zxylzb_9128S.ko, tm.ko) + binary data extraction +
cross-check vs mainline zx-eth-main.c. 2026-06-04. Pure RE — no source/device modified.**

GOAL: determine exactly how stock brings up the 5th copper GE jack (the WAN ethernet port,
separate from the 4 yellow LAN jacks) so we can add it to the mainline driver.

---

## TL;DR (the answer)

| Question | Answer |
|---|---|
| **Which MAC is the WAN** | **MAC4** (`smac4`). LAN0..3 = MAC0..3; WAN = the leftover MAC4. |
| **WAN PHY** | An **external dual-page PHY ("ZX5201") at MDIO address 0x08** (companion page at 0x09), on the **same** MDIO bus `0x9a101000`. It is `uni_phy[4]` in stock's table. |
| **SerDes?** | **NO.** The copper WAN jack does **not** use `pon_serdes` (0x9fe00000). That block is the **GPON fiber** SerDes and is only initialized when `g_pon_work_mode == 0x10` (fiber/p2p mode), gated by `lan_up`. WAN ethernet is pure RGMII-class MAC4 ↔ external MDIO PHY. |
| **Switch-fabric port or standalone?** | **Switch-fabric uplink port.** WAN = logical port 4 = greg/phys 4 = regport 5 = uni 4 = phys-MAC 4. Stock additionally marks it the **`lan_up_port` (=4)** "WAN/p2p" port: `tm_set_pp_wan_cfg(4)` + the PP CPU-fwd / TX egress-hint use `lan_up_port`. It is in the fabric, but flagged as the uplink. |
| **Bring-up driver** | A 200ms-equivalent **polling timer** (`extphy_timer_func`), NOT IRQ — same model the mainline DSA driver already adopted (`PHY_POLL`). |

---

## 1. WAN MAC index — MAC4 (DEFINITIVE)

The chip has 5 MACs. Stock's per-MAC functions all gate `param_1 < 5` / `4 < param_1 → return`
(e.g. `pon_npp_smac_enable`, `switch_smac_get_rx_flow_crtl` plat:3036,3111). The MAC register
window is uniform: **`mac_base(N) = npp_base + (N+1)*0x40000`**, i.e. MAC4 = `npp_base + 0x140000`.

Port-index map (from `port_numbering_map_re.md`, live-confirmed): **logical port4 = WAN = greg/phys 4
= regport 5 = uni 4 = phys-MAC 4 = desc-egress hint 0x2c**. LAN0..3 = MAC0..3. So **WAN = MAC4**,
the only MAC the mainline driver does not init (`ZX_NUM_MACS 4` skips it, eth-main:233).

`smac_init` (stock plat:2272) is **byte-identical for every MAC** — it only differs by the
`param_1*0x40000` window — so MAC4 bring-up is the *same* code as LAN, just `port=4`:
```
smac_init(N):  // N=4 for WAN
  npp[(N+1)*0x40000 + 0x40000] = 0xbae003   // MAC_REG_CONTROL  (mac+0x00)
  npp[... + 0x40004]           = 0xffff      // MAC_REG_IRQ_MASK (mac+0x04)
  npp[... + 0x40008]           = 0x80000001  // MAC_REG_ENABLE   (mac+0x08)
  npp[... + 0x400e0]           = &PTR_caseD_47  // serializer/PHY-iface (mac+0xe0 = 0x00011200)
  npp[... + 0x40d00] &= ~0x2                  // mac+0xd00 tsf/store-fwd
  npp[... + 0x40d30] &= ~0x20                 // mac+0xd30 rsf/flow-ctrl
```
(Mainline `zx_smac_init_port` eth-main:1267 is the richer U-Boot-faithful variant of this; it
works for MAC0..3 and will work verbatim for MAC4 with `port=4`.)

## 2. The WAN PHY — external MDIO PHY at address 0x08 (NOT a SerDes, NOT a 5th GePHY)

Stock's PHY-address table, **extracted from the kmod binary** (`uni_phy`, GLOBAL OBJECT @ .data
off 0x88, 5 bytes; file off `0x11694+0x88`):
```
uni_phy[5] = { 0x0a, 0x0b, 0x0c, 0x0d, 0x08 }
               gephy0 gephy1 gephy2 gephy3  WAN
```
- `uni_phy[0..3] = 0x0a..0x0d` = the 4 internal GePHYs (LAN0..3) — matches mainline.
- **`uni_phy[4] = 0x08`** = the WAN PHY's MDIO address. **Same MDIO bus `0x9a101000`.**
- `lan_up_port` (GLOBAL @ .data off 0x2c8) = **0x04** → indexes `uni_phy[4] = 0x08`.

The WAN PHY is initialized by **`zx5201_config()`** (plat:3224), which writes MDIO addresses
**8 and 9** (a two-page external PHY — page 0x08 is the "ZX5201", page 0x09 its config page):
```
zx5201_config():                       // WAN external-PHY magic init
  // clears bits in CRM reg uRamf060000c (0xf060000c &= 0xffe7f7ff) around the access
  mdio_write(8, 0x12, 0x8402)
  mdio_write(9, 0x16, 0x0a0f);  mdio_write(9, 0x1b, 0x0800)
  mdio_write(8, 0x1d, 0x0355)
  mdio_write(8, 0x10, 0xb62d);  mdio_write(8, 0x11, 0x0006)   // indirect reg 0xb62d = 6
  mdio_write(9, 0x12, 0x0004)
  v=mdio_read(9,0x15); u=mdio_read(9,0x14)
  mdio_write(9, 0x11, (v & 0xc1ff) | 0x2800);  mdio_write(9, 0x10, u)
  mdio_write(9, 0x12, 0x0204)
  v=mdio_read(9,0x16); mdio_write(9, 0x16, (v & 0xfff3) | 4)
  if (product_vid == ' ') {            // board-variant gate
    v=mdio_read(9,0x17); mdio_write(9,0x17, v & 0xfff9)
    v=mdio_read(9,0x17); mdio_write(9,0x17, v & 0xfffe)
    mdio_write(8,0x10,0xb409); mdio_write(8,0x11,0)   // indirect 0xb409=0
    mdio_write(8,0x10,0xb407); mdio_write(8,0x11,0)
    mdio_write(8,0x10,0xb406); mdio_write(8,0x11,0)
    mdio_write(8,0x10,0xb408); mdio_write(8,0x11,0)
  }
```
After `zx5201_config()`, stock powers up the WAN PHY:
`v=mdio_read(uni_phy[4]=8, 0); mdio_write(8, 0, v | 0x800)` (plat:3317, restart-autoneg/power-up).

> ⚠️ Mainline's comment "MAC4 (RGMII **WAN**)" (eth-main:233) is half-right: the MAC side is
> RGMII-class, but the PHY is an **MDIO-addressable external PHY at 0x08**, not a fixed-link.
> It must be probed/configured over MDIO like the GePHYs (different magic regs though).

## 3. The SerDes (0x9fe00000) is NOT in the WAN-ethernet path

`pon_serdes` is the **GPON fiber** SerDes. Its init (`reg_def_set` plat:8231, `serdes_mode_set`
plat:7924, band-cal `pon_serdes_base+0x44` in `zx_pon_clk_reset_init` plat:8266) is only reached
via `zx_pon_clk_reset_init(1)` / `zx_pon_clk_reset()` in `init_module`, and the second is gated by:
```
g_pon_work_mode = zte_get_pon_mode();
if (g_pon_work_mode == 0x10) lan_up = 1;     // 0x10 = fiber/p2p uplink mode
...
if (lan_up != 0) { pp[0x2c] |= 1<<(lan_up_port+0x19); zx_pon_clk_reset(); }  // fiber only
```
`serdes_mode_set` modes 1/3 program PON-specific lane/PRBS/band settings; `serdes_set_*_prbs`,
`serdes_rx_ready` etc. confirm this is the optical-line SerDes. On this **copper H3600** the WAN
jack is electrical RGMII↔MDIO-PHY; the SerDes is dead (matches DATASHEET:211 "fiber SerDes, NOT
dumped, copper-only"). **No SerDes init is needed to bring up the copper WAN jack.**

## 3b. PIN_MUX (0x94200000) — stock NEVER writes it (DEFINITIVE)

Task: "what pinmux value does stock set to route MAC4's RGMII to the WAN pads?"
**Answer: none.** Stock maps the pinmux window but performs **zero writes** to it.

- `init_module` (plat:8952) does `pin_mux_base = of_iomap(node, 3)` then only ever **printk's**
  it (plat:8964). Grep for `pin_mux_base` across the entire plat kmod returns exactly those two
  hits — map + printk, **no stores**. tm.ko and switch.ko contain **no** `pin_mux`/`0x94200000`
  reference at all.
- DTS confirms the iomap index: pon/eth node `reg-names = "pon","npp"/"top_crm","sys_ctrl",
  "pin_mux","pon_serdes"` (dtsi:205) → index 3 = pin_mux @ **0x94200000** (dtsi:203). Same in both
  stock and mainline.
- **Implication:** the RGMII pads for MAC4 are routed by the **bootloader/U-Boot (or hardware
  default straps)**, not by the runtime kmod. The mainline driver therefore does **not** need a
  pinmux write to bring up the WAN jack — consistent with the live symptom that the external PHY
  already gets L1 link (pads are already muxed; only the MAC4 datapath is uninitialized).
- Caveat: this is recoverable only as far as the kmod goes. If a future board needs the mux set,
  it would live in U-Boot, which was not dumped/analyzed here.

## 4. Stock's exact WAN MAC bring-up sequence

### 4a. One-time init (`pon_npp_smac_init`, plat:3273) — boot
```
gephy_ldo_init()                          // LDO arm, 4 GePHYs (LAN)
for N in 0..3:                            // NOTE: loops LAN only here
    mdio_write(uni_phy[N], 0x10, 0x8001); mdio_write(uni_phy[N], 0x11, 0)
    smac_init(N); npp[(N+1)*0x40000] |= 2
phy_process(0)
add_timer(gephy_ldo_timer, +200 jiffies → gephy_ldo_timer_func)   // temp/LDO watch
register_phy_int()                        // 4 GePHY IRQs
zx5201_config()                           // <-- WAN external PHY init (MDIO 8/9), see §2
add_timer(extphy_timer, +10 jiffies → extphy_timer_func)          // <-- WAN link poller
uni_phy_stat[4] = 0xffffffff
v = mdio_read(uni_phy[4]=8, 0); mdio_write(8, 0, v | 0x800)        // WAN PHY power-up
```
So at boot stock initializes the WAN **PHY** (zx5201_config + power-up) but defers the WAN **MAC**
bring-up to the poller (extphy_timer_func), which fires on WAN link.

### 4b. WAN link-up bring-up (`extphy_timer_func`, plat:3137) — every 10 jiffies, port = lan_up_port = 4
```
p   = lan_up_port (=4)
st  = mdio_read(uni_phy[4]=8, 0x1a)        // PHY link/speed status (via reg0x1e paging)
if (st & 0x380) == uni_phy_stat[4]:        // unchanged & up
    pon_npp_smac_enable(4)                 // MAC4 |= 3  (keepalive re-enable)
elif (st & 0x40) == 0:                     // link DOWN
    uni_phy_stat[4] = 0xffffffff; pon_npp_smac_disable(4)   // MAC4 &= ~3
else:                                      // link state CHANGED → full bring-up
    decode speed (idx 0/1/2 = 10/100/1000) + duplex from (st>>9)
    pon_reset(1 << (4+6) = 1<<10)          // pulse MAC4 serializer reset (pon_base+8 bit10)
    smac_init(4)                           // re-init MAC4 (same code as §1)
    pon_npp_smac_config_speed_duplex(4, speed, duplex)   // see 4c
    smac_sopc_mode_switch(4, duplex)       // SOPC<->MAC bridge + 0x19038, see 4d
    pon_npp_smac_enable(4)                 // MAC4 |= 3
    uni_phy_stat[4] = st & 0x380
```

### 4c. `pon_npp_smac_config_speed_duplex(port=4, speed, duplex)` (plat:2737)
Writes MAC4 ctrl `npp[(4+1)*0x40000 = 0x140000]`:
```
if speed==2 (1G):  ctrl = (ctrl & ~0x8000) | 0x2000      // bit13 gigabit
else:
    if duplex==0:  ctrl = (ctrl & ~0x2000) | 0x8000      // bit15
    else:          ctrl |= 0xa000
    if speed==1 (100M): ctrl |= 0x4000  else ctrl &= ~0x4000   // bit14
```

### 4d. The MAC→fabric admit gate (`smac_sopc_mode_switch(port=4, duplex)`, plat:2290)
This is the WAN equivalent of the `0x19068`/SOPC admit the mainline driver already drives for LAN:
```
// wait (≤5 spins) for SOPC<->MAC READY bit (port+5) to assert, then enable:
for 5: if (npp[0x19068+4] & (1<<(4+5)=bit9)) { npp[0x19068+4] |= (1<<4); break }  // dma_cfg_byteorder+4
npp[0x19038] = (npp[0x19038] & ~(1<<(4+0x10)=bit20)) | (duplex!=1)<<bit20         // 0x19038 half/full
```
(`dma_cfg_byteorder` is the offset of the SOPC bridge reg block; `+4` → `npp+0x19068` region. The
READY bit for MAC4 is **bit 9** (port+5), the enable bit is **bit 4** (port).)

PP/TM WAN flagging (tm.ko): `tm_set_p2pmode(4)` (tm:35981) sets `lan_up_port=4` and calls
`tm_set_pp_wan_cfg(4)` → `fpga[0xe8007] |= 1<<(4+0x19) = bit29` (PON_PP_TM_CFG WAN-accept), and the
TX egress-hint / PP CPU-fwd use `lan_up_port+0x28`/`+0x19` (desc hint 0x2c0 for port4).

## 5. WAN is a switch-fabric uplink port (not a standalone CPU-attached MAC)

WAN = logical port 4 lives in the same switch fabric as LAN0..3 (greg/STP slot 4, regport 5,
uni 4, CLA inport regport5, isolation slot regport5). It is **not** a separate routed netdev at the
HW level. Stock additionally tags it the **uplink** via `lan_up_port=4` (PP WAN-cfg bit29, TX
egress-hint, CPU-fwd bit). Whether it's bridged with LAN or used as an L3 WAN is a *software/bridge*
policy (the userland nas/PPPoE netdev), not a different HW datapath — at the silicon level it is one
of the 5 fabric MAC ports, distinguished only by the `lan_up_port` WAN flag and its external PHY.

---

## 6. Concrete mainline driver changes (zx-eth-main.c / DTS)

### 6a. zx-eth-main.c
1. **Bump MAC count to include MAC4**: `#define ZX_NUM_MACS 4` → consider a separate path for MAC4
   so the LAN loop stays 0..3 but `zx_smac_init_port(e, 4)` is also called (the function is already
   port-generic; `mac_off(4,..)` = `npp_base+0x140000` is correct).
2. **Grow `gephy[4]` → `gephy[5]`** (eth-main:379) and attach a 5th PHY at MDIO **0x08**.
3. **Port `zx5201_config()`** (§2) as a `phy_init`/`config_init` for the WAN PHY (it is NOT a
   zte-gephy; it's the external "ZX5201" two-page PHY at addr 8/9 — likely a new tiny phy driver or
   a fixup keyed on its PHY ID). Then power it up: `mdio reg0 |= 0x800`.
4. **WAN link bring-up** = the existing `zx_smac_init_port(4)` + a `config_speed_duplex(4)` + the
   SOPC admit for MAC4 (READY bit9, enable bit4 in 0x19068; 0x19038 bit20 duplex). The driver's
   existing per-link keepalive (eth-main:3315 SOPC re-assert loop, currently `i<4`) should extend to
   include i=4. Since GePHY IRQs don't fire (and the WAN PHY is polled by stock too), use **PHY_POLL**
   for the WAN PHY — exactly the model already adopted for the GePHYs.
5. **WAN uplink flags**: set `lan_up_port=4` semantics — PP WAN-cfg `fpga[0xe8007] |= bit29`
   (`tm_set_pp_wan_cfg`), and ensure the TX egress-hint for WAN frames uses MAC-index 4 (desc hint
   `(4+0x28)&0x3f = 0x2c`). (Only needed if you route traffic out the WAN port.)
6. **Do NOT touch pon_serdes / zx_pon_clk_reset** for the copper WAN — that's the fiber path
   (`g_pon_work_mode==0x10` only).

### 6b. DTS (zx279128s.dtsi)
- Add a 5th MDIO child under `mdio@9a101000`: `wanphy: ethernet-phy@8 { reg = <0x08>; };` (compatible
  for the ZX5201 external PHY, or fixed-link + a fixup).
- Add it to `zte,gephys = <...>, <&wanphy>;` (or a separate `zte,wanphy = <&wanphy>;`) so the driver
  attaches/inits the 5th PHY.
- No SerDes node change needed (the `<0x9fe00000 0x100000>` reg entry is already present but unused
  for copper WAN).

---

## Key citations
- `uni_phy[5]={0a,0b,0c,0d,08}`, `lan_up_port=0x04`: extracted from
  `ext/kmodules_dump/plat-zxylzb_9128S.ko` .data (uni_phy @off0x88, lan_up_port @off0x2c8).
- `decomp_all_plat_zxylzb_9128S.c`: `smac_init`@2272, `smac_sopc_mode_switch`@2290,
  `config_speed_duplex.part.0`@2737, `pon_npp_smac_enable/disable`@2769/2782, `zx5201_config`@3224,
  `pon_npp_smac_init`@3273, `extphy_timer_func`@3137, `serdes_mode_set`@7924, `reg_def_set`@8231,
  `zx_pon_clk_reset_init`@8266 (band-cal +0x44 @8328), `init_module`@8891 (lan_up/serdes gate @8906/8937).
- `decomp_all_tm.c`: `tm_set_p2pmode`@35981 (`lan_up_port`), `tm_set_pp_wan_cfg`@35970 (bit29).
- mainline: `zx-eth-main.c` `ZX_NUM_MACS 4 /* skip MAC4 (RGMII WAN) */`@233, `mac_off`@413,
  `zx_smac_init_port`@1267, per-link SOPC keepalive@3315, `gephy[4]`@379; DTS gephy nodes
  `zx279128s.dtsi`@261-281, `zte,gephys`@225.
- `port_numbering_map_re.md` §4 (logical4=WAN=MAC4=regport5=uni4); DATASHEET:211 (SerDes copper-dead).
