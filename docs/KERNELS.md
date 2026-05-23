# KERNELS — where each kernel lives, how to build, why it exists

This project juggles **3 kernel source trees + 1 binary-only stock kernel**.
They serve different purposes — don't confuse them.

| # | Tree | Version | Role | Active? |
|---|------|---------|------|---------|
| 1 | `zxic/linux-v6.6/` | 6.6 (pinned LTS) | **Main driver dev kernel** — our `zx279128-eth.c` lives here. Booted via TFTP/bootm for Loop A iter. | ✅ HOT |
| 2 | `ext/extracted/{uImage,zImage,vmlinux.bin}` | 4.1.25 (stock binary) | Stock factory kernel — runs on slot A/B unless we override. No source. Used as RE target. | ✅ HOT (on device) |
| 3 | `tasks/99.01.linux-stockport/linux-4.1.25/` | 4.1.25 (vanilla + ZTE-ish patches) | Failed attempt to rebuild a stock-compatible kernel WITH kprobes/ftrace. Parked. | ⛔ PARKED |
| 4 | torvalds/linux upstream (fetch on demand — recipes in §4) | upstream master | Source of the ZX-platform cherry-picks for the OpenWrt port | 🔬 RESEARCH |
| 5 | `refs/zx297520v3/README.md` (catalog — trees themselves not local; re-clone on demand) | sibling SoC | Reference trees for the related ZX297520v3 SoC. Cross-reference for RE. | 📚 REFERENCE |

---

## 1. Mainline 6.6 — the one you'll actually build

**Location**: `zxic/linux-v6.6/`
**Defconfig**: `arch/arm/configs/zx279128s_defconfig`
*(Don't confuse with upstream's `h3600_defconfig` — that's for the Compaq iPAQ
H3600 PDA from 2000, a naming coincidence. Ours is `zx279128s_defconfig`.)*
**Build dir** (out-of-tree): `zxic/build/`
**Toolchain**: `arm-linux-gnueabi-` (soft-float — see note below)

### One-time setup

```bash
sudo apt install gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi \
                 u-boot-tools bison flex libelf-dev libssl-dev
```

### Build the kernel + driver + DTB

```bash
cd ~/Projects/MYSELF/ZTE/zxic/linux-v6.6

# First time, or after defconfig change:
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build zx279128s_defconfig

# Build kernel image + DTBs + modules:
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build \
     zImage dtbs modules -j$(nproc)
```

Output:
- `../build/arch/arm/boot/zImage` — kernel image
- `../build/arch/arm/boot/dts/zte/zx279128s-h3600.dtb` — device tree
- `../build/drivers/net/ethernet/zte/zx279128-eth.ko` — our driver

### Wrap as uImage (what U-Boot's `bootm` expects)

ZTE U-Boot's `bootm` only takes ONE argument — DTB must be **appended** to the
zImage, not passed separately:

```bash
cd ../build/arch/arm/boot
cat zImage dts/zte/zx279128s-h3600.dtb > /tmp/zImage_dtb.bin
mkimage -A arm -O linux -T kernel -C none \
        -a 0x42000000 -e 0x42000040 \
        -d /tmp/zImage_dtb.bin \
        ~/Projects/MYSELF/ZTE/zxic/tftp/zImage_dtb.uimg
```

- `-a 0x42000000` = load address (RAM base + 32 MiB offset)
- `-e 0x42000040` = entry address (load + 64 B uImage header)

### Boot (RAM-only — no NAND write)

```bash
cd ~/Projects/MYSELF/ZTE/zxic
nohup python3 -u lib/uart.py auto_bootm_dtb_appended \
      > /tmp/boot.log 2>&1 &
```

See `docs/ITERATE.md` Loop A for the full iter cycle.

### Why soft-float for the kernel toolchain?

The kernel itself doesn't care about userspace VFP ABI (kernel is always
built with `-msoft-float` regardless of toolchain triple). BUT — the
toolchain installs `libgcc.a` that the kernel links against, and on Debian
the `-gnueabihf` package's `libgcc.a` assumes VFP. Stay on `-gnueabi-`
for everything in this project to avoid surprises. Userspace requires
soft-float anyway (no VFP on this Cortex-A9), so one toolchain covers both.

---

## 2. Stock kernel — binary-only, on-device

**Location of binaries** (extracted from NAND once, kept read-only):
```
ext/extracted/uImage        3.5 MiB — full uImage from slot A
ext/extracted/zImage        3.5 MiB — zImage payload
ext/extracted/vmlinux.bin   6.9 MiB — uncompressed ELF (use this in Ghidra)
refs/orca-h3600p/firmware/extracted.dts        — DTS reconstructed from running kernel
refs/orca-h3600p/firmware/extracted.dtb        — its compiled form
```

**Version**: 4.1.25 (per `strings vmlinux.bin | grep '^Linux version'`).

**There is no buildable source for this kernel.** ZTE/Digi never released
the GPL source despite request (see memory `gpl_legitimacy_context`).
The factory binary is what it is.

### What you can do with it

| Goal | How |
|------|-----|
| Read kernel symbols / addresses | `vmlinux.bin` in Ghidra (load at `0xc0008000` for ARM kernel base) |
| Trace what stock drivers do at runtime | **Binary-patch `.ko` files** to inject `printk` calls — see `tasks/00.01.eth-driver/research/printk_injection_methodology.md` |
| Use kprobes / ftrace | **You can't** — `# CONFIG_KPROBES is not set`, `# CONFIG_FUNCTION_TRACER is not set` in stock config |
| Get kernel printk on UART | `kmsg2uart` daemon (already running on stock-shell rootfs) — see `tasks/00.02.stock-shell/` |
| Rebuild the stock kernel | Parked — see #3 below |

### The .ko files you'll be patching

```
ext/rootfs/kmodule/{plat-zxylzb_9128S, switch, tm, idmfdb, …}.ko
```

These are factory binaries. Reverse-engineered in Ghidra under `ghidra/`.

---

## 3. Stockport (parked) — rebuilding 4.1.25 with debug tools

**Location**: `tasks/99.01.linux-stockport/`

**What it was**: vanilla `linux-4.1.25.tar.xz` + ZTE board-file port +
4 EXPORT_SYMBOL patches + KGDB/KPROBES/FTRACE enabled, with the goal of
loading factory stock `.ko` files on it and using debug tooling that the
factory kernel lacks.

**Why parked**: full source-level recreation of ZTE's downstream patches
proved too brittle. We pivoted to the printk-injection methodology
(#2 above) which gives observability without needing a custom kernel.

**Build script + critical knobs** (preserved for posterity):
```
tasks/99.01.linux-stockport/build.sh
```

The knobs documented in that file's header are **gold** — if you ever
need to build any 4.1.25 variant for this hardware, they save days:

- **Toolchain**: hard-float Buildroot GCC 7.3 at
  `~/toolchains/armv7-eabihf--glibc--stable-2018.11-1`. Newer GCC (13.x)
  breaks 4.1.25 asm macros and lacks `armv7-a` hard-float support.
- **LOADADDR**: `0x40008000` (stock convention — mainline's `0x42000000` hangs bootm).
- **PHYS_OFFSET**: `0x40000000` (must be set explicitly; `ARM_PATCH_PHYS_VIRT`
  default-off in our cfg).
- **CONFIG_ARCH_ZX=y** (provides `mach-zx` + DEBUG_LL with ZTE-shifted PL011
  offsets; `olddefconfig` silently turns this OFF — re-pin every time).
- **CONFIG_UNINLINE_SPIN_UNLOCK=y** (else stock `.ko` can't resolve
  `_raw_spin_unlock`).
- **INITRAMFS_SOURCE**: `/tmp/initramfs_stockport` (bundles init + .ko's into uImage).

**Patches applied to vanilla 4.1.25** for stock-.ko compat:
- `kernel/kallsyms.c` — `EXPORT_SYMBOL(kallsyms_lookup)`
- `kernel/pid.c` — `EXPORT_SYMBOL(find_task_by_vpid)`
- `arch/arm/kernel/traps.c` — `EXPORT_SYMBOL(show_stack)`
- `.config` — `CONFIG_UNINLINE_SPIN_UNLOCK=y`

### Don't resurrect this without a strong reason

Use the printk-injection methodology instead. See
`tasks/00.01.eth-driver/research/printk_injection_methodology.md`.

---

## 4. Upstream master (torvalds/linux) — OpenWrt-port cherry-pick source

**Location**: NOT stored locally. Fetch on demand when openwrt-port
work starts. Source: `git@github.com:torvalds/linux.git`

**Purpose**: source of the ZX296702 platform-driver commits we need to
**cherry-pick back** (they were removed from mainline in Jan 2021,
commit `89d4f98ae90d`, Arnd's `ARM: remove zte zx platform`). Every
cherry-pick we'd ever need is catalogued in
`tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md`
(commit-by-commit table with hashes + dates + authors + file paths).

**The reusable bits** (per the archaeology report):
- `drivers/clk/zte/clk-zx296702.c` — clocks (commit `5a4658081226`)
- `drivers/gpio/gpio-zx.c` — GPIO (commit `e7aa6d8c1ba2`)
- `drivers/dma/zx_dma.c` — DMA controller (commit `e3fa9841d309`)
- `arch/arm/mach-zx/platsmp.c` — SMP boot (in commit `acede515b3a5`)
- `arch/arm/mach-zx/zx296702-pm-domain.c` — power domains (commit `4c2c2e39713b`)
- `drivers/mmc/host/dw_mmc-zx.c` — MMC (if H3600 uses DW-MSHC; uncertain)

### How to get the commits when you need them (4 options, easiest first)

| | Recipe | Best for |
|---|---|---|
| **A** | `cd zxic/linux-v6.6 && git remote add upstream git@github.com:torvalds/linux.git && git fetch upstream && git cherry-pick <hash>` | **Recommended.** Fold upstream as a remote into our working v6.6 tree; cherry-pick directly into the branch you build from. No separate clone dir. |
| **B** | `git fetch upstream <hash> && git cherry-pick FETCH_HEAD` | Single-commit recipes; minimal bandwidth. |
| **C** | `gh api /repos/torvalds/linux/commits/<hash>.patch \| git am --3way` | No git remote needed; useful in CI / scripts. |
| **D** | `git clone --depth=10000 git@github.com:torvalds/linux.git /tmp/upstream` | Full local clone for exploratory `git log` queries (≈ what we used to have at ZTE/linux/; ~6.5 GB). |

Use A for the actual platform-driver tasks. The archaeology doc has all
the hashes you'll need — paste them directly.

### Why we don't keep the clone

Used to live at `ZTE/linux/` (8.2 GB). Deleted on 2026-05-23 — pure
convenience, every commit is reachable via the recipes above and the
archaeology doc captures everything we'd want to look at. ~30 min to
re-fetch via option A when you actually start cherry-picking.

### Helper scripts + patches (archived inside zxic)

```
tasks/00.openwrt-port/scripts/setup_fork.sh    — creates a fork branch with resurrected ZX code (STALE — needs path fixes)
tasks/00.openwrt-port/scripts/build_kernel.sh  — wraps the fork build (STALE; has exit guard so it won't run)
tasks/00.openwrt-port/kernel-patches/          — OUR patches for {clk, configs, dts, mach-zx}
```

**Status**: STALE. Written before the `H3600 → zxic` rename and before
recipe option A was the recommendation. Treat as design reference. When
openwrt-port becomes active, the cherry-pick + patch flow uses recipe A
above, not these scripts.

---

## 5. Reference SoC trees (re-clone on demand)

**Location**: `refs/zx297520v3/README.md` — catalog only. The actual
trees (2.3 GB total) are not stored locally; clone any of them when
needed via the documented commands.

The catalog covers 5 GitHub-hosted trees for **ZX297520v3** (sibling SoC):

| Tree | Size when cloned | Use case |
|---|---|---|
| `linux-3.4` | 639 MiB | Original vendor kernel (sister to our stock 4.1.25) |
| `linux-5.10` | 1.3 GiB | Vendor's later kernel |
| `openloader` | 408 KiB | Vendor stage-1 bootloader |
| `u-boot` | 18 MiB | Vendor U-Boot |
| `u-boot-mainline` | 407 MiB | Community port (OpenWrt-relevant pattern) |

ZX297520v3 is the **same internal ZXIC family** as our ZX279128S (per
chinadsl winnt5 thread; register layouts and clock model overlap). When
something looks weird on the ZX279128S, check these trees for analogous
code — often the answer is there in a slightly different form.

See `refs/zx297520v3/README.md` for the decision tree on when to clone
which one + the exact `git clone` commands.

---

## Quick decision tree

```
"I want to change the eth driver and test it"
  → kernel #1 (zxic/linux-v6.6) — Loop A in docs/ITERATE.md

"I want to know what stock kernel/driver does at runtime"
  → kernel #2 (binary), Loop B (printk-splice into .ko)

"I want to add kprobes to the stock kernel"
  → NO. Use Loop B instead. (#3 is parked for a reason.)

"I want to port to OpenWrt / find reusable mainline drivers"
  → kernel #4 (fetch upstream per §4 recipes); read tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md first

"I'm stuck on a register and need to see how a sibling SoC handles it"
  → kernel #5 (refs/zx297520v3/README.md — re-clone as needed)
```

---

## See also

- `docs/CROSS_COMPILE_GUIDE.md` — toolchain choices (soft-float, ABI verification)
- `docs/ITERATE.md` Loop A — full edit→build→flash→test cycle commands
- `docs/ARCHITECTURE.md` — hardware truth (PL011 shift, NAND, AES, CRC)
- `tasks/00.03.nand-flash/README.md` — how to flash any kernel image to slot A
- `../INFORME_ZXIC_KERNEL.md` — Spanish kernel-archaeology report (which old mainline drivers to resurrect for OpenWrt port)
- `tasks/99.01.linux-stockport/build.sh` — the gold knobs if you ever need to build 4.1.25
