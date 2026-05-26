# linux-stockport — vanilla 4.1.25 + ZTE shim → live oracle for stock RE

**ID**: 99.01
**Parent**: 99 (parked-work category prefix)
**Children**: none (atomic — kotrace + netdev_probe + testmod + zte_shim + qemu live here as siblings)
**TaskList items**: #57 (in_progress) + #58/#59/#60 completed
**Status**: ✅ BOOTS — full module chain loads + eth0 created. **Used as live oracle for `tasks/00.10.02.re-stock-kmods/` and the mainline driver refactor (#38).**

## What this is

Vanilla `linux-4.1.25` + 4 EXPORT_SYMBOL patches + custom `mach-zx` board file + `zte_shim.ko` providing the ~45 kernel-resident symbols ZTE built into their downstream vmlinux. The 6 stock `.ko` files (memlog/regtracer/zte_shim/zx_ponreg/plat/tm/switch/idmfdb) load successfully against this kernel. `eth0` netdev is created and bound to `192.168.1.1/24`.

This gives us a **live oracle**: we can boot it, trigger any stock code path via netshell or kotrace, and capture exactly what stock does without needing ZTE's source.

## State (2026-05-26)

```
✅ Kernel builds + boots (vanilla 4.1.25, ZTE mach-zx, full iotable)
✅ 8 modules load cleanly (in init.norm order)
✅ 14 sequential walls solved (see findings/)
✅ SHIM_TRACE captures 16k boundary calls per boot with caller resolution
✅ kotrace patches 214 in-place functions across plat/tm/switch/idmfdb/zx_ponreg
✅ eth0 created + UP + IP 192.168.1.1/24 assigned
⚠️ "link is not ready" — our zx_mdio_read returns fake 0xffff (no real PHY talk)
⚠️ busybox missing arping applet (cosmetic)
```

## Layout

```
99.01.linux-stockport/
├── README.md                ← this file
├── build.sh                 ← canonical build: shim + kernel (uImage) + deploy
├── linux-4.1.25/            ← vanilla 4.1.25 source + our patches
│   ├── arch/arm/mach-zx/    ← board file (full 20-entry static iotable)
│   ├── arch/arm/boot/dts/   ← zx279128s.dtsi + h3600 board DTS
│   └── usr/initramfs_data.cpio.gz  ← embedded initramfs
├── zte_shim/                ← OUR shim module (~45 exports, kernel-resident emul)
├── kotrace/                 ← kotrace.ko built against stockport kernel (~260 KB)
├── testmod/                 ← memlog.ko + regtracer.ko + sbrgdump.ko
├── netdev_probe/            ← diagnostic: prints struct net_device offsets
├── patched_kmods/           ← binary-patched stock .ko's (currently: switch.ko netdev_ops fix)
├── qemu/                    ← scaffold for qemu-system-arm iteration (not built yet)
├── findings/                ← discoveries from the live boot
│   ├── stockport_revival_2026_05_26.md         ← the 14-wall journey
│   ├── external_tooling_prior_art_2026_05_26.md ← FirmSolo/abidiff/vmlinux-to-elf survey
│   └── (additional findings as we add them)
└── linux-4.1.25.tar.xz      ← upstream source tarball (golden)
```

## Quick reference

### Boot + capture

```sh
# Build kernel (and shim, if shim source changed)
./build.sh kernel

# Deploy to TFTP
./build.sh deploy

# Boot via UART (TCP bridge, so multiple consumers can watch)
UART_TCP=1 python3 ../../lib/uart.py auto_bootm_stockport
```

### What ends up loaded at boot

`init.sh` (lives at `/tmp/initramfs_stockport/init` — embedded in the uImage by `CONFIG_INITRAMFS_SOURCE`) loads modules in this order:

```
memlog → regtracer → netdev_probe → zte_shim → zx_ponreg →
plat-zxylzb_9128S → tm → switch → idmfdb → kotrace
```

After load:
- `ip link set sw0/eth0 up`
- `ip addr add 192.168.1.1/24 dev sw0/eth0`
- `netshell` started on port 9001 (raw TCP shell for live introspection)
- `cat /proc/kotrace_dump` dumped to kmsg (first 200 lines)

### Live introspection

Once booted with a netdev UP, from the host:

```sh
nc 192.168.1.1 9001          # raw TCP shell on the device
# > cat /proc/regtrace        ← MMIO reg diff since BASELINE
# > cat /proc/kotrace_dump    ← per-target call+args trace
# > cat /proc/memlog          ← captured printks
# > lsmod
# > ip link
```

UART_TCP=1 also streams to `/tmp/uart_bridge.log` (append-only), useful for running `tail -f` from another terminal.

## Findings — where the knowledge lives

| Finding type | Location |
|---|---|
| Mechanics of the stockport (walls, fixes, build) | `findings/stockport_revival_2026_05_26.md` |
| External tooling surveyed (FirmSolo, abidiff, ...) | `findings/external_tooling_prior_art_2026_05_26.md` |
| **What stock DOES at init — call graph, register sequences, ZTE-added symbols catalog** | **`../00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md`** ← canonical knowledge base |
| **How to use those findings in the mainline driver refactor** | **`../00.01.eth-driver/findings/stockport_to_mainline_refactor_plan.md`** |
| Stock kmod decompiled C | `../00.10.02.re-stock-kmods/findings/decomp_all_*.c` |
| Stock vmlinux symbols | `../00.10.01.re-vmlinux/vmlinux.elf` (vmlinux-to-elf output) |

## Critical knobs (must survive olddefconfig)

```
CONFIG_ARCH_ZX279128S=y
CONFIG_MACH_ZX279128S=y
CONFIG_DEBUG_LL=y
CONFIG_DEBUG_LL_UART_PL01X=y
CONFIG_DEBUG_UART_PHYS=0x94404000        # ZTE-shifted PL011
CONFIG_DEBUG_UART_VIRT=0xf0704000
CONFIG_DEBUG_LL_INCLUDE="debug/pl01x.S"
CONFIG_PHYS_OFFSET=0x40000000
CONFIG_ARM_APPENDED_DTB=y
CONFIG_ARM_ATAG_DTB_COMPAT=y
CONFIG_INITRAMFS_SOURCE=/tmp/initramfs_stockport
LOADADDR=0x40008000
```

4 EXPORT_SYMBOL patches to vanilla 4.1.25:
- `kallsyms_lookup` — kernel/kallsyms.c
- `find_task_by_vpid` — kernel/pid.c
- `show_stack` — arch/arm/kernel/traps.c
- `_raw_spin_unlock` — fix via CONFIG_UNINLINE_SPIN_UNLOCK=y or direct patch

Toolchain: `~/toolchains/armv7-eabihf--glibc--stable-2018.11-1` (Buildroot GCC 7.3). System gcc won't build 4.1.25 — armv6/asm-macro incompatibilities.

## When to use stockport

| Question | Use stockport? |
|----------|---------------|
| "What does stock function X actually call?" | YES — boot + add X to kotrace target list + dump |
| "What HW regs does stock write during op Y?" | YES — boot + trigger Y + read /proc/regtrace |
| "What is the layout of stock struct Z?" | YES — write a probe module (like netdev_probe) |
| "What's the right value for fake_board_info[+0xN]?" | YES — kotrace stock + observe what gets read |
| "How does my mainline driver refactor compare?" | YES — boot both, compare regtrace output |
| "Implement a new feature for mainline" | NO — mainline driver is its own task (00.01) |

## Why stockport vs. our own driver

The mainline driver (`tasks/00.01.eth-driver/` → `linux-v6.6/.../zx279128-eth.c`) is the production target. Stockport is the **knowledge source** that informs it. They are complementary:

- Mainline = ship-ready, modern kernel, our code, upstreamable goal
- Stockport = live museum where the original stock binary runs and we can watch

Refactor of the mainline (task #38) uses stockport's captured init flow as its specification. See `../00.01.eth-driver/findings/stockport_to_mainline_refactor_plan.md`.

## Don't resurrect blindly

If you're reaching for stockport to debug something:
1. Can it be solved with `kotrace` on the live stock device (`tasks/00.01.eth-driver/kotrace/`)? That's the lighter path.
2. If you need a custom vmlinux (because the question is about kernel internals): yes, use stockport.
3. If you need to test a hypothesis about init order or symbol semantics: yes, use stockport.

The build cycle here is ~50s kernel rebuild + 4 min device boot. The live-device kotrace approach is much faster but limited to what stock code paths are reachable.

## Related

- `../00.10.02.re-stock-kmods/` — shared knowledge base for stock .ko's (where eth_init_flow_2026_05_26.md lives)
- `../00.10.01.re-vmlinux/` — shared knowledge base for stock vmlinux (vmlinux.elf with 43k symbols)
- `../00.01.eth-driver/` — mainline driver work (primary consumer of stockport knowledge)
- `../00.02.stock-shell/` — patched stock-shell rootfs (predecessor to stockport)
- `../../docs/KERNELS.md` — all three kernel trees we have
