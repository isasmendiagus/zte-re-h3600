# External tooling + prior art for stock-kmod reuse — 2026-05-26

Triggered by hitting the 5th boot crash in the stockport revival pass
(tm.ko aclRamInit at `0xf1020000`). Before grinding through more RE by
hand, surveyed the public landscape for tools/frameworks that solve
parts of what we're doing. Two research passes — one ZTE-leaning, one
generic — yielded the same conclusion: **no turnkey framework, but
three concrete tools that can 10x specific sub-problems**.

## TL;DR — three actionable tools

| Tool | What it does | Our sub-problem it solves |
|------|--------------|----------------------------|
| **FirmSolo** (USENIX Security 2023) — github.com/BUseclab/FirmSolo | Scans every `.ko` in a firmware blob for `__ksymtab` / `__versions` / `vermagic`. Runs Kernel Configuration Reverse Engineering (K.C.R.E.) to infer a `.config` that, when applied to a chosen kernel source tree, produces a `vmlinux` whose exported-symbol set is a superset of every required symbol across every `.ko`. Covers ARM 32-bit Cortex-A9 + MIPS. | Skip weeks of manual `.config` bisection. Drop `ext/kmodules_dump/` into FirmSolo, get a starting config much closer to stock than what we have today. |
| **vmlinux-to-elf** (marin-m) — github.com/marin-m/vmlinux-to-elf | Scans a raw `vmlinux.bin` for the compressed kallsyms table, recovers function/variable symbols, infers arch/endianness/bit-width, emits a Ghidra-loadable ELF. | Improves `tasks/00.10.01.re-vmlinux/` for free. Also gives kotrace a clean kallsyms map for un-exported helpers (currently hand-curated in memory entries). |
| **abidiff / libabigail** — sourceware.org/libabigail | Diffs the KMI surface of two binaries (`.ko` vs `vmlinux`). On `__ksymtab` / `__ksymtab_gpl` only. Exit codes `4 = ABI changed`, `8 = incompatible`. | Replaces our hand-rolled `netdev_probe.ko` struct-offset prober. One command lists every struct/function where stock and our mainline build diverge — the exact shim surface area. |

## Other prior art surveyed (kept for context, lower priority)

- **Linux Backports project** (backports.docs.kernel.org). Production-grade "kernel API compatibility shim done at scale." Solves the inverse problem (run new drivers on old kernels) but the engineering pattern (`compat.h` + per-feature `.c` stubs gated by `LINUX_VERSION_CODE`) is directly transferable if we end up building a `zte_compat.ko`.
- **Linux livepatch** (kernel/livepatch/, mainline since 4.0). kpatch + kGraft converged onto ftrace as the redirection substrate. **kotrace is essentially a hand-rolled livepatch** — migrating to ftrace-based hooking (where available) would buy zero-trap-overhead patching + existing `/sys/kernel/tracing/` tooling. Blocked on stock kernel having `CONFIG_KPROBES_ON_FTRACE=n` (so this requires unparking stockport with the right config). Shadow variables (`klp_shadow_alloc`) solve struct-extension-without-ABI-break and could be useful if we ever need to add fields the stock kmod expects.
- **Android GKI / KMI** (source.android.com/docs/core/architecture/kernel/stable-kmi). Per-vendor symbol allowlist + libabigail-checked ABI stability. Not deployable but the architecture confirms "abidiff as CI gate" is the right pattern.
- **pahole + dwarves + gendwarfksyms** — production tools for DWARF struct comparison. Useful if we ever build mainline with `CONFIG_DEBUG_INFO_BTF=y` and want to diff layouts against stock.
- **kallsyms-extractor** (pagabuc) — extracts kallsyms-decompression routine and runs under Unicorn. Backup for vmlinux-to-elf when the table is encoded weirdly.
- **Stefan Doesinger's `zx297520-kernel`** (gitlab.com/stefandoesinger/zx297520-kernel). **Sibling SoC**, mainline 6.18 port, reimplementation-from-scratch (NOT binary reuse). Peripheral layout strongly correlated; **highest-EV single read** for our mach-zx work. Also `github.com/zx297520v3-mainline/{u-boot-mainline,zx297520v3-loader}`.
- **Asahi Linux `m1n1`** (github.com/AsahiLinux/m1n1) — "tiny bootloader + Python-driven remote control" methodology. Our `lib/uart.py` driving U-Boot is the seed of the same pattern. Worth enriching when we hit individual peripherals we can't reason about.
- **mmiotrace** — would have been perfect for our `0xf1xxxxxx` mystery (run stock under it, dump every MMIO access). **x86/x86_64 only**. Dead end for ARM.
- **RevNIC** (EPFL DSLab, EuroSys 2010) — academic "re-synthesize driver from observed behavior" approach. Overkill given we have a running stock and can `kotrace` it directly, but worth the mental model if a particular kmod resists Ghidra.
- **libhybris / Halium** — userspace shim only, doesn't help when you have the `.ko` but not the kernel.
- **ndiswrapper history** — successful Windows-NDIS-on-Linux, killed by maintenance burden. **Lesson: if shim surface > 50 functions, wrong abstraction point.** Keep our shim narrow.
- **FirmSolo's K.C.R.E. has academic-tier failure modes** (heuristic, not exhaustive). Even partial success = useful starting point.
- **GPL laundering risk** — `kallsyms_lookup_name` was unexported in 5.7 specifically to break GPL-only-symbol re-export shims. We're fine as long as our work is private/research; anything we publish needs care.

## What's NOT in the public landscape

- Any tool that scans a stock vmlinux for `iotable_init` arrays and emits a DT/mach-file (we hand-rolled this in `findings/stockport_revival_2026_05_26.md`).
- Any tool that automatically infers the physical address behind a `pfn=0` placeholder iotable entry. Manual options: dump `/sys/kernel/debug/kernel_page_tables` on live stock (requires `CONFIG_ARM_PTDUMP=y` in stock — likely off), or kotrace-hook `create_mapping` / `__arm_ioremap_pfn_caller` during stock boot.
- mmiotrace for ARM.
- BTF / CO-RE for pre-built closed `.ko` (only works for eBPF + DEBUG_INFO_BTF).

## Recommended order of attack (post-research)

1. **vmlinux-to-elf** on `ext/extracted/vmlinux.bin` — 10 minutes, free upgrade for `tasks/00.10.01.re-vmlinux/`. May surface the `init_machine` callback name that does the `0xf1xxxxxx` mapping (the symbol we're hunting).
2. **Stefan's `zx297520-kernel`** read — 30-60 minutes. Sibling SoC; if his mach-zx documents anything about the `0xf1xxxxxx` family we save hours.
3. **FirmSolo** on `ext/kmodules_dump/` — 1-2h setup, big upside if it works (mostly-correct .config).
4. **abidiff** on stock.ko vs our mainline-built equivalents — 30 minutes, gives the exact list of struct mismatches we'll hit AFTER the iomap wall (the latent `net_device@0x1DC` issue).
5. **kotrace-instrument live stock** (`create_mapping` / `__arm_ioremap_pfn_caller` hooks) — 2-3h, dump exhaustive runtime iomap. Use if 1-4 don't yield the `0xf1xxxxxx` answer.

## Cross-references

- `findings/stockport_revival_2026_05_26.md` — the 5-crash journey that motivated this research
- `../00.10.01.re-vmlinux/README.md` — direct beneficiary of tool #1 (vmlinux-to-elf)
- `../00.10.02.re-stock-kmods/README.md` — direct beneficiary of tools #2 (FirmSolo) and #3 (abidiff)

## Verdict

**No framework solves our exact problem end-to-end. We're at state of the art.** But three tools tackle distinct sub-problems we've been hand-rolling, and `vmlinux-to-elf` + `abidiff` are zero-risk free wins regardless of which path we pick next.
