# Stockport revival — 2026-05-26 attempt

**Goal**: boot vanilla 4.1.25 + ZTE mach-zx port, insmod stock kmods
(zte_shim + zx_ponreg + plat + tm + switch + idmfdb), get networking
up. Pass 1 only — kprobes/ftrace not enabled yet.

**Outcome**: 5 crashes peeled back, all but the last fixed. Stuck at
crash #5 (tm.ko ACL RAM hardcoded virtual address) — needs deeper RE
of stock vmlinux init path before further progress.

## Boot reached

```
zte_shim → 40 symbols loaded
zx_ponreg → fpga driver registered (major=222)
plat-zxylzb_9128S init:
  - reserve_mem inited
  - pon_base / top_crm_base / sys_ctrl_base / pin_mux_base / pon_serdes_base ioremap'd
  - 5 IRQs adquired: pon=20, npp=21, idm=22, tm=23, pp=24
  - clock + serdes + rxpll OK
  - pon_tm_init OK (NAPI added, DMA_DN_DESC_CNT=0x1584)
  - pon_pp_init OK
  - pon_npp_init OK (idm_desc_init d096d000/4fb68000)
  - 4 SMACs init OK (mac 0..3)
  - mac 0 phy status: 1000M full-duplex
  - mac 4 phy status: 10M half-duplex  ← via extphy_timer_func
  ✓ plat init returned 0
tm.ko init:
  - tm_devReg OK
  - tmUsrInterfaceCreate OK (TM Module SYS FS Init ended successfully)
  - tm_initial begin → tm_sdk_init → aclRamInit
  ⛔ __memzero(0xf1020000, 4 MiB) → page fault
```

## Five crashes encountered (4 fixed, 1 wall)

### #1 — gephy_ldo_init at virt 0xf0807000 → static iomap missing
**PC**: `gephy_ldo_init+0x2c [plat]`. `*pgd=00000000` for `0xf0807000`.
Stock plat hardcodes `0xf080?000` virtual addresses for the gephy LDO
regs. Our `mach-zx/zx279128s.c` only mapped the UART region (1 entry).

**Fix**: extended `zx_io_desc[]` from 1 to 13 entries (the full stock
iotable_init recovered from `ext/extracted/vmlinux.bin` by anchoring on
the known UART entry and reading neighbours). See zx279128s.c.

### #2 — smac_init at npp_base+0x40000 → DTS reg too small
**PC**: `smac_init+0x20 [plat]`. `*pgd=4f805811, *pte=0`. plat does
`npp_base = of_iomap(npp_node, 0)` which uses DTS `reg` size. Our DTS
had `reg = <0x921c0000 0x40000>` (256 KiB) but smac_init writes up to
`npp_base+0x100d30`.

**Fix**: DTS `reg = <0x921c0000 0x180000>` (1.5 MiB). Right-bound by
TM at 0x92340000.

### #3 — phy_process at GIC virt 0xf0101100 → more static iomap missing
**PC**: `phy_process+0x80 [plat]`. Address `0xf0101100` is the cortex-A9
GIC distributor ICDICPR (clear pending), accessed via the `0xf0100000 →
0x00800000` iomap entry that stock has but we didn't (until fix #1
added all 13 entries).

**Fix**: included via fix #1's full iotable rebuild.

### #4 — smac_init(4) from extphy_timer_func → 5th MAC bank
**PC**: `smac_init+0x20` from `extphy_timer_func+0x17c`. The extphy
timer (started by pon_npp_smac_init) handles mac=0..4 (5 MACs total,
not 4). For mac=4 we hit `npp_base+0x140000` which fell exactly at end
of 0x140000 mapping from fix #2.

**Fix**: bumped DTS NPP `reg` size from 0x140000 to 0x180000 (1.5 MiB,
covers smac 0..4 fully).

### #5 ⛔ tm.ko aclRamInit at 0xf1020000 — STUCK

**PC**: `__memzero` from `aclRamInit.part.6 [tm]`. tm.ko hardcodes:
```
    50490: e34f0102 movt r0, #0xf102 ; r0 = 0xf1020000
    50494: e3a01501 mov  r1, #0x400000 ; 4 MiB
    50498: bl __memzero
    504a0: e34f0142 movt r0, #0xf142 ; r0 = 0xf1420000
    504a4: e3a01601 mov  r1, #0x100000 ; 1 MiB
    504a8: bl __memzero
```

The ACL RAM at virt 0xf1020000 / 0xf1420000 has no obvious iomap entry
in our vmlinux scan. There IS a placeholder-looking entry at the end
of the iotable array: `virt=0xf1000000 phys=0x00000000 len=0x520000
type=0`. `pfn=0` is suspicious — suggests stock reserves the virtual
range but maps actual physical addresses via a runtime mechanism we
don't have.

**Hypotheses for stock's mechanism (untested)**:
1. `init_machine` callback does additional `iotable_init()` or
   `__arm_ioremap_pfn()` calls — we'd need to RE the stock init
   sequence past `setup_arch()`.
2. zte_shim or plat sets up the mapping via `__arm_ioremap()` with
   force-virtual (rare API).
3. A CSP/PDT init layer in stock cspstart pre-sets-up MMU page tables
   before kernel takes over — we don't have any of that code.

Neither orca's vmlinux.bin nor our `ext/extracted/vmlinux.bin` shows a
classical `iotable_init` entry for 0xf1xxxxxx → real-phys.

## Files changed in this attempt

- `tasks/99.01.linux-stockport/build.sh` — TFTP_DIR path fix
  (`zxic/tftp` → `tftp` after project rename)
- `tasks/99.01.linux-stockport/linux-4.1.25/arch/arm/mach-zx/zx279128s.c`
  — `zx_io_desc[]` expanded from 1 to 13 entries (full stock iotable
  recovered from vmlinux.bin)
- `tasks/99.01.linux-stockport/linux-4.1.25/arch/arm/boot/dts/zx279128s.dtsi`
  — NPP `reg` size 0x40000 → 0x180000

## Next-step options

| Option | Cost | Confidence |
|--------|------|------------|
| RE stock vmlinux to find 0xf1xxxxxx phys mapping | 4-8h | Medium (stock vmlinux has CSP layer we don't have source for) |
| Skip tm.ko load + observe what plat alone provides | 30 min | Useful as diagnostic, won't give networking |
| Pivot back to kotrace post-boot capture (already works) | 0 | High — we already get 32k+ entries this way |
| Patch tm.ko binary to skip aclRamInit (similar to auto_patch_plat.py approach) | 2-3h | Medium — moves the wall but each function may have its own MMIO assumptions |

## Latent issue: struct net_device offset 0x1DC

Diagnostic from `netdev_probe.ko`:
```
sizeof(struct net_device) = 1152 (0x480)
offsetof(net_device, dev_addr)  = 0x1D0
offsetof(net_device, _rx)       = 0x1D4
target offset is 0x1DC          ← stock plat reads this
```

Stock plat accesses some net_device field at 0x1DC which falls between
`_rx`/`_tx` in our kernel's struct layout — likely a different field
in stock's downstream kernel. **Not hit yet** (plat crashed in MMIO
before getting to netdev creation). Will become blocking after the
0xf1020000 wall is overcome. `auto_patch_plat.py` exists for binary-
patching this kind of struct-offset mismatch.
