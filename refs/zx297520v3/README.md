# zx297520v3 — sibling-SoC reference trees (kernel #5 in KERNELS.md)

**The trees themselves are NOT here** — they were originally at
`ZTE/zx297520v3-mainline/*` (2.3 GB total) and deleted to save space.
All 5 are public GitHub git clones; re-clone any of them when needed.

## What this SoC is

**ZX297520v3** is a **sibling SoC to our ZX279128S** — same ZTE ZXIC
family, same internal architecture pattern, register layouts and clock
model overlap significantly (per winnt5's chinadsl analysis cited in
`docs/EXTERNAL_RESEARCH.md`).

Used in: cheap LTE routers — D-Link DWR-932M, Tecno TR118, Vodacom R310.

When our ZX279128S RE hits a wall on a specific register or peripheral,
**check how the sibling SoC handles it** — answers are often there in
slightly different form.

## The 5 trees (re-clone any of them as needed)

All public, no auth required. Standard `git clone <url>` recovers each.

| Tree | Size | Re-clone command | What it is / when to consult |
|---|---|---|---|
| **linux-3.4** | 639 MB | `git clone https://github.com/zx297520v3-mainline/linux-3.4.git` | Original vendor kernel (Linux 3.4) for ZX297520v3 — sister to our stock 4.1.25. **Best for RE cross-reference**: vendor-modified, has the proprietary drivers, can be compared against orca's vmlinux to spot ZXIC-family idioms. |
| **linux-5.10** | 1.3 GB | `git clone https://github.com/zx297520v3-mainline/linux-5.10.git` | Vendor's later kernel for the same SoC — useful for seeing how vendor evolved the drivers across kernel versions (or what they removed). |
| **openloader** | 408 KB | `git clone https://github.com/zx297520v3-mainline/openloader.git` | Vendor's stage-1 bootloader (sister to our cspstart). Small. Worth a look if our cspstart RE hits a confusing slot-selection / CRC quirk. |
| **u-boot** | 18 MB | `git clone https://github.com/zx297520v3-mainline/u-boot.git` | Vendor's U-Boot for the sibling SoC. **Compare against our `tasks/00.10.03.re-uboot/`** Ghidra analysis when stuck on a U-Boot command or env var. |
| **u-boot-mainline** | 407 MB | `git clone https://github.com/zx297520v3-mainline/u-boot-mainline.git` | Community port of mainline U-Boot for ZX297520v3 — pattern reference for "how would mainline-quality U-Boot support this SoC family?" Useful for the eventual OpenWrt port. |

Total if you clone all 5: ~2.4 GB.

## When you'd actually clone any of these

Cross-reference workflow when stuck:

1. You're RE'ing register `0xNNNNN` in our `ext/extracted/vmlinux.bin` or
   one of the `.ko`s, and Ghidra is silent.
2. Clone the relevant sibling tree (probably `linux-3.4` first — vendor
   original).
3. `grep -r "0xNNNNN" .` to find any reference, then read the surrounding
   code.
4. Often you'll find a named macro or a function that explains what the
   register does.
5. Cross-apply the insight to our ZX279128S work; promote any reusable
   finding to `tasks/00.10.0N.re-*/findings/`.

## When NOT to clone

- If your question is about the ZX279128S-specific behavior we've already
  RE'd → check `tasks/00.10.0N.re-*/findings/` first
- If your question is about mainline ZX296702 driver shape → check
  `tasks/00.10.04.mainline-archaeology/` first
- If you'd only `grep` once and move on — `gh api` works fine instead:
  ```sh
  gh search code --repo zx297520v3-mainline/linux-3.4 "0xNNNNN"
  ```

## See also

- `docs/KERNELS.md` "kernel #5 — Reference SoC trees" — operational view
- `docs/EXTERNAL_RESEARCH.md` — winnt5's analysis explaining why this SoC family overlaps with ours
- `refs/stefan-zx297520/README.md` — Stefan's mainline port for this same SoC family (also a git clone we deleted; re-clone command preserved there)
