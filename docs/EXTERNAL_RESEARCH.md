# EXTERNAL_RESEARCH — third-party RE work this project builds on

We did NOT discover this hardware from scratch. Multiple prior projects
documented the H3600P boot chain, AES rootfs encryption, and the ZX-family
SoC layout. This doc catalogs **who did what before us** so you can go
read their work when stuck.

**All of the below is external — not authoritative for our specific
unit.** Useful as bootstrap material and sanity check. When something
conflicts with our `ext/` golden source, trust `ext/`.

## Primary sources

### orca.pet — Marcos del Sol Vives' H3600P writeup

- **URL**: https://orca.pet/zteh3600p/
- **What it gave us**:
  - Boot chain documentation (bootloader → cspstart → kernel)
  - NAND partition layout
  - AES-128-ECB rootfs encryption key derivation
  - First public mention that `chip_tm_init` is the missing piece for LAN→CPU
- **Archived in zxic**: `refs/orca-h3600p/kernel.elf` (his unstripped kernel ELF)
- **Status**: bootstrap material. Read this FIRST if you're new to the project.

### XYUU on kanxue.com

- **URL**: https://bbs.kanxue.com/thread-276970.htm (Chinese; needs Google Translate)
- **Status**: paywalled — kanxue.com requires registration for some pages.
- **What it gave us**:
  - Full RE of the firmware header structure
  - AES rootfs cipher details
  - Confirmation that older firmware versions use CRC32 only (no real RSA)
  - Confirmation that stock `.ko` files are not stripped (Ghidra-friendly)
- **GitHub mirror of derived scripts**: https://github.com/enoymuss/h3600-root
  - Works up to H3600 P16_TR variant; does NOT work on the Digi P5 variant (ours)
- **Status**: the canonical technical RE thread for this family.

### winnt5 on chinadsl.net

- **URL**: https://www.chinadsl.net/thread-169478-1-1.html (Chinese; usually readable without login)
- **What it gave us**:
  - Comparative analysis of mainline ZX296702 vs proprietary ZX279128S
  - Confirmation that the two SoCs share most register layouts and clock model
  - This is **why our OpenWrt-port plan** (resurrect mainline ZX code, adapt) is plausible
- **Status**: cited in `tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md`.

### Stefan's ZX297520v3 port

- **Archived in zxic**: `refs/stefan-zx297520/` (README + 2 defconfigs)
- **What it is**: A working-ish mainline Linux port for the sibling SoC
  ZX297520v3 (D-Link DWR-932M, Tecno TR118, Vodacom R310).
- **Why it matters**: Same family, same techniques. His patterns
  (mach-zx layout, clock tree, GPIO/IRQ wiring, qspi NAND, ramdisk init)
  are the closest thing to a blueprint for our future OpenWrt port.

## Secondary references

### OpenWrt forum support request

- **URL**: https://forum.openwrt.org/t/support-for-zx279128s/196946
- **Status**: posted, **no useful response**. Mentioned so you don't
  re-post the same question.

### GPL source from sibling ZTE devices (compressed-away)

Two GPL releases from other ZTE devices were collected during the
GPL hunt (in the now-compressed `gpl_hunt/` sibling tree):
- `Orange_MC801A_OpenSource_zte.tgz` — SDX55-based modem
- `ZTE_NH8091_opensource_code.tgz` — IPQ8074-based router

**Neither is the H3600/ZX279128S source we asked for** (which ZTE/Digi
never provided — see memory `gpl_legitimacy_context`). They're from
unrelated platforms (Qualcomm SoCs). Kept as evidence ZTE *can* release
source when they want to; not as code reference.

## How these tie back to our work

| External finding | Where we use it |
|---|---|
| orca's boot chain doc | `docs/ARCHITECTURE.md`, `docs/NAND_LAYOUT_AND_BOOT.md` |
| orca's AES key derivation | Memory `aes_key_discovered`; our key `H36000e71071c440` derived this way |
| XYUU's header structure | `tasks/00.03.nand-flash/README.md` BootPara field offsets |
| winnt5's ZX296702-vs-ZX279128S | `tasks/00.10.04.mainline-archaeology/KERNEL_ARCHAEOLOGY_ES.md` table of reusable drivers |
| Stefan's port patterns | `tasks/00.openwrt-port/` (future work blueprint) |

## Trust hierarchy when sources disagree

```
1. ext/ (our device, dumped/extracted with our tools)        ← authoritative
2. Our docs (ARCHITECTURE.md, NAND_LAYOUT_AND_BOOT.md, etc.) ← derived but verified
3. orca, XYUU, winnt5 (external RE)                          ← bootstrap material
4. Stefan, OpenWrt forum, GPL tarballs                       ← cross-reference only
```

External sources accelerated our work by years. They are **not**
substitutes for verifying findings against our actual hardware.
