# `lan_up_port` lifecycle — where it's set and used

Source: massive Ghidra decomp of plat-zxylzb_9128S.ko + switch.ko + tm.ko
captured 2026-05-24. See `decomp_all_*.c`.

## Setter

```c
// tm.ko @ 0x000464c0
undefined4 tm_set_p2pmode(uint param_1) {
    lan_up_port = param_1;
    printk("lan_up_port=0x%x\n", param_1);
    tm_set_pp_wan_cfg(lan_up_port & 0xff);
    return 0;
}
```

## Caller (where input comes from)

```c
// switch.ko @ 0x000164b4 — sw_other_set_wan_lan_switch
//   reads zte_api_sw_mac_set_port_macfiltermode[wanLogicPort]
//   feeds value to tm_set_p2pmode
sw_other_set_wan_lan_switch(mode) {
    if (wanLogicPort == 0xff) return 0;  // not configured → exit
    cVar1 = zte_api_sw_mac_set_port_macfiltermode[wanLogicPort];
    tm_set_p2pmode((uint)(byte)cVar1);
    // also fpga_write_reg(0xe8007, val & 0xc1ffffff)
}
```

So `wanLogicPort` (some config value) indexes into a per-port macfiltermode
table, and the result becomes `lan_up_port`.

## Consumers (where lan_up_port is read)

1. **TX path** (the one we care about): `pon_tm_net_tx` → desc port encoding
   ```c
   desc[2..3] = (desc[2..3] & 0xfc0f) | ((lan_up_port + 0x28) & 0x3f) << 4;
   ```

2. **MDIO/PHY operations**: lan_up_port indexes `(&uni_phy)[lan_up_port]`
   to access the PHY for status reads (`zx_mdio_read(uni_phy[lan_up_port], 0x1e)`).

3. **PON init bitmask**: `pp[0x2c] |= (1 << (lan_up_port + 0x19))`
   This is the per-port CPU forwarding enable. For lan_up_port=0 → bit 25.

4. **WAN config**: indirect via `tm_set_pp_wan_cfg(lan_up_port & 0xff)`.

## What our mainline driver does

- Hardcodes `port = 0` in TX desc encoding (matches lan_up_port=0).
- Writes `pp[0x2c] |= BIT(25)` at init (matches lan_up_port=0 → bit 25).
- **Already consistent with lan_up_port=0**.

## Why this DOESN'T explain the ping bidi issue

Our TX descriptor is now correct (desc[11]=0x21, desc[0]=0xc9, port encoding
matches lan_up_port=0). HW TM_UP_DONE counter increments after each TX kick.
But host doesn't receive replies.

→ Suggests the switch is sending TX to a port that doesn't reach host, OR
the switch reflects CPU TX back as loopback (which we see in LOOPBACK drops).

→ Next experiment to run: **register-state diff between stock and mainline**
for the PP block (0x92380000 + 0x40000) to find init differences in switch
routing config.
