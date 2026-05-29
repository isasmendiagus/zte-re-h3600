# Stock init flow — `zx_ponreg.ko` static analysis

Walk of `tasks/00.10.02.re-stock-kmods/findings/decomp_all_zx_ponreg.c`
(4KB decomp, smallest of the 5 kmods).

## Summary

`zx_ponreg.ko` is a **trivial FPGA register access kmod**. It owns one
global `pon = 0xf4000000` (kernel virtual address pre-mapped by U-Boot or
the platform init), exports `fpga_read_reg(idx)` / `fpga_write_reg(idx,
val)` as helpers for other kmods (`tm.ko`, `switch.ko` depend on this kmod
per `lsmod`), and registers a char device (major 222 = 0xde) for userspace
access to FPGA registers via ioctl.

**No HW init writes from this kmod.** It only provides the access
primitive.

## Functions

### [fn-00] `fpga_module_init` @ decomp_all_zx_ponreg.c:104 — entry

What it does: hardcodes `pon = 0xf4000000` (the kernel VA of the FPGA
register block; assumes someone else already iomap'd it — likely U-Boot
or a static iotable mapping), then registers a char device for ioctl
access.

HW writes: **none**.

Sub-calls:
- `__register_chrdev(0xde, 0, 0x100, "fpga", &fpga_ops)` — register major 222

In mainline? **N/A** — this is a userspace debug interface. The kernel-side
read/write helpers (`fpga_read_reg`, `fpga_write_reg`) are just dereferences
of `pon + idx*4` and don't need to be replicated as a separate driver.

### [fn-01] `fpga_read_reg(int idx)` @ decomp_all_zx_ponreg.c:3

```c
return *(u32 *)(pon + idx*4);
```

Direct memory read. Used by other kmods.

### [fn-02] `fpga_write_reg(int idx, u32 val)` @ decomp_all_zx_ponreg.c:12

```c
*(u32 *)(pon + idx*4) = val;
```

Direct memory write. Used by other kmods (notably `switch.ko`'s
`sw_alarm_init` makes ONE direct call to write reg 0xd3000).

### [fn-03] `fpga_ioctl` @ decomp_all_zx_ponreg.c:40 — userspace access

What it does: handles ioctl 0 (read N regs starting at reg) and ioctl 1
(write one reg). Reads 12 bytes from user (reg_idx, value, count), then
does N reads or 1 write at `pon + reg*4`.

HW: pass-through to fpga_read_reg / fpga_write_reg.

In mainline? **N/A** — debug interface only.

### [fn-04] `fpga_module_exit` @ decomp_all_zx_ponreg.c:126 — cleanup

```c
__arm_iounmap(pon);          // unmap the FPGA region
__unregister_chrdev(0xde, ...);
```

Note: this calls `__arm_iounmap` on `pon`, suggesting `pon` WAS ioremap'd
elsewhere. But `fpga_module_init` doesn't call `ioremap`. Either:
- The ioremap happens in another kmod that ran first
- The `0xf4000000` is a statically-mapped region (iotable_init from
  platform code in cspd or the kernel itself)

## Conclusions

- This kmod is a **passive helper**. Init does nothing relevant to the
  ethernet data path.
- The interesting global `pon = 0xf4000000` is a clue: it's the kernel VA
  of the FPGA register block. Switch.ko's lone direct write
  `fpga_write_reg(0xd3000, 0x1f40fa0)` (per switch_ko_init doc [fn-10])
  targets `0xf4000000 + 0xd3000*4 = 0xf4334c00` virtual.
- Mainline doesn't need a port of zx_ponreg; the helpers it exports are
  trivial.

## Cross-refs

- Used by `tm.ko` — see `static_analysis_tm_ko_init.md` (pending)
- Used by `switch.ko` — see `static_analysis_switch_ko_init.md` [fn-10]
