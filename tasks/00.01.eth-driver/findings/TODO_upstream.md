# zx279128-eth — pending cleanups for upstream submission

Snapshot at refactor #38 Phase 31 (commit 368a1e412, 2026-05-26).

## Driver is currently …

```
$ wc -l linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c
3735

$ <zx_eth_probe span>
117 lines  (was 313 lines at start of the extraction series — Phase 21)
```

The probe body is now mostly a sequence of named init helpers.
Generic stock-table replay (`zx_eth_apply_stock_init`) and the TM
bring-up (`zx_eth_init_tm_subsystem`) are the two biggest single
calls. Both have proper doc comments.

## Mandatory before RFC submission

| # | Description | Estimated effort |
| --- | --- | --- |
| **10b-pon** | ✅ Phase 41 (commit b4bb802ff). `zx_eth_init_extra_mmio` now derives both pon_early and fpga_base from the DT "pon" resource via `platform_get_resource_byname`. Boot gate passed. | DONE |
| **10b-topcrm** | ✅ Phase 44 (commit 37aef7e09). of_parse_phandle("zte,topcrm") + of_iomap + devm-tracked iounmap. void __iomem* preserved, all 13 readl/writel sites unchanged. ZX_TOPCRM_BASE constant deleted. Boot gate passed. | DONE |
| **32** | Sweep "2026-05-2X" date-stamps and "Phase 4" dev-cycle phrasings from comments. Keep technical content; drop archaeology. ~25 sites. | 1-2 h |
| **33** | Run `scripts/checkpatch.pl --strict` on the four new/touched files and fix style issues. | 1-2 h |
| **34** | Add the `compatible = "zte,zx279128s-eth"` line to `MAINTAINERS`. | 5 min |
| **35** | RFC cover letter — see the template in `tasks/00.01.eth-driver/findings/driver_architecture.md` for the structure; expand into a netdev-style cover-letter. | half a day |
| **36** | `git format-patch` the series, run `scripts/get_maintainer.pl` per patch, prepare `git send-email` config. | 1 h |

## Optional but worth considering before RFC

| # | Description | Why |
| --- | --- | --- |
| 37 | Convert the in-driver "zx_stock_apply_block" into a per-block u32 array (still generic) but in **one** header file instead of stock_bursts.h being 1.2 MB. Big improvement for source tarball size. | A reviewer running `make zx279128-eth.o` shouldn't see a 1 MB generated header. |
| 38 | ⚠️ Partial — Phase 43 (commit d35ec4408) removed 870 KB of dead `*-regs.h` triplets that were orphan. The remaining live headers (zx_stock_bursts.h, zx_npp_twin_data.h, zx_*_table.h) still sit alongside .c source. Moving them to a `data/` subdir is still on the wish list. | Reviewers may still push back on the 1.1 MB zx_stock_bursts.h. |
| 39 | ✅ Phase 42 (commit 3c7400d1b). Downgraded expected -1 and -3 returns to dev_dbg in zx_table_write; -2 and -4 still warn (real bugs). Per-port replay aggregate count stays at dev_info. | DONE |
| 40 | Stop registering `eth0` (`sw` netdev) + `idm0`/`idm1` from the same platform driver. The right shape is a DSA switch driver that exposes per-port netdevs (`swp0..swp3`). | Reviewers will ask. |

## Long horizon (post-RFC)

- DSA conversion (`drivers/net/dsa/zte/zx_switch.c`). Per-port netdevs with phylink. Multi-week effort. Probably needed for v2-v3 review.
- Name the remaining 15 469 anonymous stock_init writes (PON_B, PON_TAIL singletons, TM/PP_FUC scattered). Needs PON-side .ko decomp + kotrace of stock during boot. Months of part-time RE.
- Phase 6 throughput numbers (#37 in TASKS_TREE). Useful for the cover letter performance section.
- Fix ping bidi — the TX path emits frames but ARP doesn't make it back to the laptop. Pre-existing, separate from the refactor.

## Verification gate every refactor must pass

Every commit on this branch must:

1. Build clean: `python3 tasks/00.01.eth-driver/scripts/build_slotA.py` succeeds.
2. Boot clean via TFTP: kernel reaches the REPL prompt without Oops/panic.
3. Driver completes init: dmesg contains:
   - `mdio-zte 9a101000.mdio: ZTE MDIO bus registered`
   - 4× `ZTE ZXIC ZX279128S GePHY ... ZTE GePHY bound (PHY ID 0x84b95031)`
   - 4× `... config_init (LDO arm + TX DAC drive enable)`
   - `PHY init complete (4 GePHYs)`
   - `TM ready: IRQ=20, sw netdev up, ...`
   - `ZX279128S ethernet ready (IRQ=..., base=..., CPU_PORT=5)`

`Unable to handle kernel paging request` or any `Oops` is an automatic
revert.

## File-by-file delta summary (Phase 11 → 31)

| File | Lines | Purpose |
| --- | --- | --- |
| drivers/net/mdio/mdio-zte.c | +193 | new MDIO bus driver |
| drivers/net/phy/phy-zte-gephy.c | +115 | new PHY driver |
| drivers/net/ethernet/zte/zx279128-eth.c | -50 net | extraction + cleanup |
| arch/arm/boot/dts/zte/zx279128s.dtsi | +30 | mdio node, gephy children, zte,gephys handles |
| Documentation/devicetree/bindings/net/zte,zx279128s-eth.yaml | +110 | new binding YAML |
| Documentation/devicetree/bindings/net/zte,zx279128s-mdio.yaml | +45 | new binding YAML |
| drivers/net/mdio/Kconfig + Makefile | +8 | MDIO_ZTE entry |
| drivers/net/phy/Kconfig + Makefile | +8 | ZTE_GEPHY entry |
| refs/zte-zx279128R/ | +4100 | sibling DTS + boot log + findings |
| tasks/00.01.eth-driver/findings/ | +500 | architecture docs, MDIO/PHY/stock-table writeups |
| tasks/00.01.eth-driver/scripts/ | +500 | gen_npp_twin_data, gen_stock_bursts updates, etc. |
