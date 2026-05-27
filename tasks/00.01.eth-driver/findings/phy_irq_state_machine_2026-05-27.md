# PHY-link → MAC.ctrl state machine — validated on live stock

Empirically captured 2026-05-27 ~07:47 UTC on factory pristine stock
firmware (slot A flashed from `ext/extracted/uImage` +
`ext/partitions/07_rootfs.bin`). Cable swaps on LAN 4 = PHY[3] = MAC[3]
(a port nobody had touched since boot — gives us a clean virgin
state). SSH access on stock, reads via `/bin/devmem2`.

## The state machine (verified end-to-end)

| Step | Action | `MAC[3].ctrl` | `gphy3` IRQ count |
|---|---|---|---|
| 0 | Virgin — never linked | `0xBAE000` | 0 |
| 1 | Cable plug in LAN 4 → link UP first time | `0xBA6003` | 1 |
| 2 | Cable unplug → link DOWN | `0xBA6000` | 2 |
| 3 | Cable plug → link UP again | `0xBA6003` | 3 |

Key observations:
- **Bit 19 is sticky**. Set on init (`0xBAE000`), cleared on first
  link UP. Once cleared, **NEVER returns to 1** for the rest of the
  device's uptime.
- **Bits 0+1 toggle with every link change**: SET on UP, CLEAR on DOWN.
- **Each link change fires exactly one PHY IRQ** (gphy[N] counter
  ticks by 1 per transition).

## IRQ mapping (verified via `/proc/interrupts` on stock)

```
 27:          0  GIC  67 Level  pon_npp
 28:          0  GIC  70 Level  idm
 29:       2448  GIC  68 Level  pon_tm        ← active during ping (~constant rate)
 31:          4  GIC  71 Level  gphy0         ← matches LAN 1 plug events count
 32:          0  GIC  72 Level  gphy1         ← never touched
 33:          1  GIC  73 Level  gphy2         ← single plug-in for LAN 3
 34:          3  GIC  74 Level  gphy3         ← 1 UP + 1 DOWN + 1 UP this experiment
```

GIC base 32 (= IRQ_OFFSET in DTS) so SPI numbers are:
- gphy0 → SPI 71 → DT cell `<GIC_SPI 0x47>`
- gphy1 → SPI 72 → DT cell `<GIC_SPI 0x48>`
- gphy2 → SPI 73 → DT cell `<GIC_SPI 0x49>`
- gphy3 → SPI 74 → DT cell `<GIC_SPI 0x4a>`

## PHY register semantics (per stock decomp + cross-check)

From `tasks/00.10.02.re-stock-kmods/findings/decomp_all_plat_zxylzb_9128S.c`:

| Reg | Function | How stock uses it |
|---|---|---|
| `0x18` | Interrupt enable | `mdio_write(phy, 0x18, 0x0005)` in `register_phy_int` |
| `0x1a` | Status / link-change latch | Read twice (latch clear + settled); bit 6 = link UP, bits 7-9 = speed code |
| `0x1e` | Page select | Saved+restored around 0x1a read in `extphy_timer_func` (may need to be 0 for raw status reg) |

Status bit decode:
- `(status & 0x40)` → link UP/DOWN
- `(status & 0x380) >> 7` → 3-bit speed code:
  - 0,1 = 10M
  - 2,3 = 100M
  - 4,5 = 1000M
- duplex (extracted via `extphy_timer_func` ladder): 0=half / 1=full per low bit of speed code

## MAC.ctrl semantics — corrected interpretation

Previous comments in mainline driver said "bit 13 cleared on link up"
(misread). Actual:

```
nibble 4 (bits 16-19):
  init / never-linked:  e = 0xE  →  bits 17, 18, 19 set
  linked-or-was-linked: 6 = 0x6  →  bits 17, 18 set, bit 19 clear

nibble 0 (bits 0-3):
  enabled:  3 = 0x3  →  bits 0, 1 set (RX+TX enabled per smac_enable)
  disabled: 0 = 0x0  →  bits 0, 1 clear (per smac_disable)
```

The three observed values:
- `0xBAE000` — fresh init, never linked, RX+TX off
- `0xBA6003` — link UP, RX+TX on, post-first-link
- `0xBA6000` — link DOWN, RX+TX off, post-first-link (bit 19 sticky-clear)

## Implementation plan (mainline driver)

### `phy-zte-gephy.c` — add IRQ support

```c
#define ZTE_GEPHY_INT_ENABLE_REG  0x18
#define   ZTE_GEPHY_INT_LINK_EVT   0x0005

#define ZTE_GEPHY_STATUS_REG      0x1a
#define   ZTE_GEPHY_STATUS_LINK    BIT(6)
#define   ZTE_GEPHY_STATUS_SPEED   GENMASK(9, 7)

static int zte_gephy_config_intr(struct phy_device *phydev)
{
    u16 val = (phydev->interrupts == PHY_INTERRUPT_ENABLED)
              ? ZTE_GEPHY_INT_LINK_EVT : 0;
    return phy_write(phydev, ZTE_GEPHY_INT_ENABLE_REG, val);
}

static irqreturn_t zte_gephy_handle_interrupt(struct phy_device *phydev)
{
    int status;

    /* Stock reads 0x1a twice — first read clears latch, second gets
     * the settled state. */
    status = phy_read(phydev, ZTE_GEPHY_STATUS_REG);
    if (status < 0)
        return IRQ_NONE;
    /* (no latch ack write — bit 6 reflects current state) */

    phy_trigger_machine(phydev);
    return IRQ_HANDLED;
}
```

Add to phy_driver struct:
- `.config_intr = zte_gephy_config_intr,`
- `.handle_interrupt = zte_gephy_handle_interrupt,`
- `.flags |= PHY_IS_INTERNAL` (already there)

### `zx279128-eth.c` — wire MAC ctrl on link change

Two options for hooking the link-change event:

**Option A (cleaner)**: attach each PHY to the sw netdev via
`phy_attach_direct()` and set `adjust_link`. phylib's state machine
calls our adjust_link whenever it observes a state change (driven
by the PHY IRQ via handle_interrupt → phy_trigger_machine).

**Option B (simpler)**: store the 4 phy_device pointers, register
a notifier or directly poll their `link` field after the
phy_trigger_machine. Since we already have phy_init_hw() in
zx_eth_init_phys, just add phy_request_interrupt() after.

For PoC we'll go with Option A. Our `adjust_link` callback:

```c
static void zx_eth_adjust_link(struct net_device *ndev)
{
    /* Called by phylib state machine on link state change for any
     * attached PHY. We have 4 PHYs attached, find which one's state
     * changed by walking sw_dev->phydev list. */
    struct zx_eth *e = *(struct zx_eth **)netdev_priv(ndev);
    int i;

    for (i = 0; i < 4; i++) {
        struct phy_device *phy = e->gephy[i];
        if (!phy) continue;
        if (phy->link != e->phy_was_link[i]) {
            u32 ctrl = phy->link ? 0xBA6003 : 0xBA6000;
            writel(ctrl, e->base + mac_off(i, MAC_REG_CONTROL));
            netdev_info(ndev, "PHY[%d] link %s → MAC[%d].ctrl=%#x\n",
                        i, phy->link ? "UP" : "DOWN", i, ctrl);
            e->phy_was_link[i] = phy->link;
        }
    }
}
```

### DT — add 4 GIC IRQs for the gephys

```dts
mdio: mdio@9a101000 {
    ...
    gephy0: ethernet-phy@a {
        reg = <10>;
        interrupts = <GIC_SPI 0x47 IRQ_TYPE_LEVEL_HIGH>;
        interrupt-parent = <&gic>;
    };
    gephy1: ethernet-phy@b { reg = <11>; interrupts = <GIC_SPI 0x48 IRQ_TYPE_LEVEL_HIGH>; };
    gephy2: ethernet-phy@c { reg = <12>; interrupts = <GIC_SPI 0x49 IRQ_TYPE_LEVEL_HIGH>; };
    gephy3: ethernet-phy@d { reg = <13>; interrupts = <GIC_SPI 0x4a IRQ_TYPE_LEVEL_HIGH>; };
};
```

phylib will pick up the `interrupts` property and wire each PHY's
IRQ automatically when we call phy_request_interrupt().

## Verification post-implementation

Once shipped, the test on mainline (with cable on LAN 3):
1. Boot → `MAC[2].ctrl` should be `0xBAE000` (init default)
2. /init brings up sw → adjust_link fires (PHY[2] was already up) →
   `MAC[2].ctrl = 0xBA6003`
3. Run ping host → device — should reach driver's NAPI poll now
4. Unplug cable → `MAC[2].ctrl = 0xBA6000`, ping stops
5. Replug → `MAC[2].ctrl = 0xBA6003`, ping resumes
