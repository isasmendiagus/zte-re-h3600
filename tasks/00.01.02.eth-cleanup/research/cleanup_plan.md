# Code Cleanup for Upstream — Plan (2026-08-01)

## Driver stats
- zx-eth-main.c: 9,287 lines (monolith)
- Total runtime code: ~11,832 lines (5 .c files)
- Total static data headers: ~19,050 lines (8 .h files)
- Grand total: ~30,882 lines

## S1 — Must do before upstream (~12-18 hrs)

### S1.1 Fix 14 checkpatch ERRORs
Lines 3278, 3288-3291: trailing statements on same line as 'if'. Lines 4814-4818: trailing statements + else-after-brace. Extract deeply-nested error paths.

### S1.2 Demote ~60 dev_info() → dev_dbg()
Audit 96 dev_info + 31 pr_info calls. Keep only probe summary, major errors, link state. Convert per-sub-block init confirmations, register readbacks, open/stop to dev_dbg.

### S1.3 Sync DT binding schema
Update zte,zx279128s-eth.yaml to match 5 reg windows + 5 interrupts actually in use.

### S1.4 Dead code removal
- CRC-16 legacy function (line 717)
- module_param(zx_tx_dualkick) — legacy
- module_param(zx_eg_port) — legacy
- zx_ff_no_unicst_flood() — superseded by PP_BRG_PKTDEAL

### S1.5-1.8 Misc
- netdev_info → netdev_dbg on registration
- phydev_info → phydev_dbg in config_init
- 420 lines >80 columns → reflow
- msleep <20ms → usleep_range()
- missing kernel-doc on probe/remove

## S2 — Should do (~28-55 hrs)

### S2.1 Dedup CLA/PM code
zx-eth-main.c and zx-dsa.c have identical CLA/PM indirect accessor functions. Extract into shared zx-eth-cla-pm.c.

### S2.2 Dedup flow tracking
ft_flows[] in eth + flows[] in DSA are identical structs. Unify in include/linux/dsa/zte.h.

### S2.3 Dedup FDB functions
Same SBRAG indirect engine, different base offsets. Verify correct offset, unify.

### S2.4 Split monolith (~9,200 → <2,000 lines main)
Extract into: zx-eth-tm.c, zx-eth-pp-cla.c, zx-eth-flow.c, zx-eth-idm.c, zx-eth-sw.c, zx-eth-link.c, zx-eth-fdb.c, zx-eth-debugfs.c. Migrate one at a time, verify boots.

## S3 — Nice to have (~16-31 hrs)
- Table compression (reduce zx_stock_bursts.h from 15K to ~8-10K lines)
- Convert replay blocks to named init
- Performance: NAPI weight 512 documentation, msleep→usleep_range
- Debugfs consolidation: group dev tools under dev/ subdirectory
- Kernel-doc on all exported symbols
