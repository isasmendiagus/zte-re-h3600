# ZX279128S MDIO controller protocol (RE'd from vmlinux)

Source: disassembly of `zx_mdio_read` (@`c0017370`) and `zx_mdio_write`
(@`c00174c4`) in `tasks/00.10.01.re-vmlinux/vmlinux.elf`.

## Hardware

- Physical address : `0x9a101000`
- Window length    : `0x18` (24 bytes, 6 u32 registers)
- DT binding       : `zte,zx279128s-mdio` (per sibling 279128R DTS)

## Register map

| Offset | Direction | Use |
| --- | --- | --- |
| `+0x00` | ? | Not touched by stock read/write |
| `+0x04` | W | **Write data** — u16 value to send to PHY |
| `+0x08` | R | **Read data** — u16 value returned by PHY |
| `+0x0c` | ? | Not touched |
| `+0x10` | R/W | **Done status** — write 0 to clear, HW sets non-zero on completion |
| `+0x14` | R/W | **Control** — op + phy_addr + reg_addr + GO |

## Control register (+0x14) bit fields

| Bits | Field | Notes |
| --- | --- | --- |
| 0..4   | reg_addr  | 5-bit PHY register address |
| 5..9   | phy_addr  | 5-bit PHY device address (`phy << 5`) |
| 10     | OP_WRITE  | Set for write (0x400) |
| 11     | OP_READ   | Set for read (0x800) |
| 14     | GO        | Set last to kick off (0x4000); HW does not auto-clear |

## Transaction sequence (read)

```c
spin_lock_bh(&mdio_lock);

ctl = readl(base + 0x14) & ~0x4000;   /* clear GO */
writel(ctl, base + 0x14);

(void)readl(base + 0x10);              /* drain status reg */
writel(0, base + 0x10);                /* clear done */

ctl = readl(base + 0x14) & ~0xc00;     /* clear OP bits */
writel(ctl, base + 0x14);
writel(readl(base + 0x14) | 0x800,     /* set OP_READ */
       base + 0x14);

ctl = readl(base + 0x14) & ~0x1f;      /* clear reg field */
writel(ctl | reg, base + 0x14);        /* set reg */

ctl = readl(base + 0x14) & ~0x3e0;     /* clear phy field */
writel(ctl | (phy << 5), base + 0x14); /* set phy */

writel(readl(base + 0x14) | 0x4000,    /* set GO — kick */
       base + 0x14);

for (i = 0; i < 10000; i++)            /* poll done */
    if (readl(base + 0x10) != 0)
        break;
/* if i == 10000, stock printk()s a timeout error but continues */

writel(0, base + 0x10);                /* clear done */
writel(readl(base + 0x14) & ~0x4000,   /* clear GO */
       base + 0x14);

val = readl(base + 0x8) & 0xffff;      /* read data */

spin_unlock_bh(&mdio_lock);
return val;
```

## Transaction sequence (write)

Same shape as read with two changes:

1. OP bit is `0x400` (WRITE) instead of `0x800` (READ).
2. Before kicking GO, the write data goes into `+0x04`:

```c
writel(val, base + 0x04);
```

3. After GO completes, no read of `+0x08` — the function just clears
   done and returns.

## Compatible Linux idiom

In mainline kernel style this is a straightforward `struct mii_bus`
driver: ioremap one window, register a bus, expose `read`/`write` ops.
Use `readl_poll_timeout` instead of the open-coded 10000-iteration
loop, and a `struct mutex` instead of the spinlock (mdiobus callbacks
are documented sleepable).

## Caveats

- The 10000-iteration timeout in stock has no actual delay between
  reads; on a 1 GHz Cortex-A9 that's ~30 μs at best. We should use a
  proper `readl_poll_timeout(..., 1, 1000)` for ~1 ms timeout with
  short delays.
- Bits 12-13, 15-31 of `+0x14` are not explicitly touched in stock — we
  preserve them via read-modify-write to be safe.
- `+0x00` and `+0x0c` are likely "MDIO ID / version" and a clock
  divider, respectively (common pattern for similar controllers).
  Stock doesn't program them at runtime → either preset by U-Boot, or
  in the stock_init writes we already replay.
