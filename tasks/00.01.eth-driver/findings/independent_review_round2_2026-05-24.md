# Independent review — round 2 (2026-05-24, ~23:10)

Second opus agent review after Phase 5f (canary + real BMU allocator)
results: BMU bypass was NOT the smoking gun. TX descriptor accepted, BMU
working, FDB seeded — still 0 frames on wire.

## Key correction the reviewer gave

**Our `zx_fdb_add` writes to the WRONG TABLE.**

- `zx_fdb_add` (eth.c:413-453) writes to `PP_BRG_RAM_*` via
  `zx_brg_ram_set`. That's the **VLAN/per-port-membership** table.
- Stock's `sbrg_add_mactable` (decomp_all_tm.c:10706) uses indirect
  access through `sbrg_get_indreg_wr_cfg` (decomp_all_tm.c:8405) →
  `tmOnuRegWrite(..., &sbragRegTable)`. That's the **MAC FDB** the switch
  fabric actually consults on egress.
- Our `entry[1] = 0xF0` and `entry[0] = 1<<port` encoding don't match
  stock's kotrace-captured `port=1` literal r0 arg either.

→ Even though we see "FDB add: bucket=456 slot=0 rc=0", we're writing
zeros into a VLAN table slot, NOT populating the MAC FDB the switch reads.

## The bulk replay critique (still standing)

- `fpga.bin` replays 11456 entries AFTER our init AFTER `zx_fdb_add`.
- Replay covers PP block 0x380000-0x3b0000 — which INCLUDES `PP+0x8014`
  area where our (wrong-table) FDB writes go.
- So our seeded FDB entries are likely overwritten by stock's snapshot
  zeros at those buckets anyway.
- Plus: replay snapshot is from a running stock unit (different MAC,
  different runtime cursors). May be writing wrong state for our boot.

## Three things to check that weren't on my list

1. **PHY link state on the egress MAC**:
   - Stock's `lan_up_port=0` → MAC0 (= one of 4 RJ45 jacks)
   - I never read BMSR.LinkStatus via `zx_mdio_read(uni_phy[0], 1)`
   - If port 0 PHY has no link → frames count on TX_DONE but never leave

2. **`greg_port_closed` / `greg_port_need_authen`** (HW_BLOCKS_INVENTORY.md:25):
   - Explicit "kill switch" bits stock turns off
   - I've never written greg_* registers at all
   - Default may be "closed" → switch counts TX but drops on egress

3. **Which physical RJ45 jack is the host cable plugged into?**
   - Device has 4× RJ45 → PHY 0..3 → MAC 0..3
   - If cable is in jack 2 but `lan_up_port=0`, frames go to unconnected
     port → counts increment, wire silent

## Reviewer's pivot threshold

Current state of effort:
- ~10 iterations on TX-bidi already
- Real-BMU fix, desc-format fixes, FDB-seed, dual-kick → none worked
- Each new experiment adds state without reducing uncertainty

Budget: **3 more experiments before pivoting to 4.1 stockport (T9.01)**.
Specifically:
1. **Disable bulk fpga.bin replay** (highest leverage, removes 11456 unknowns)
2. **Call real `sbrg_add_mactable` via sbrag indirect protocol**
3. **Kotrace stock `pon_tm_net_tx` during a live ping** (capture working TX bytes)

If after these 3 → still 0 wire frames, **stop and pivot to 4.1 stockport**.

## Architectural verdict

> The replay strategy is fundamentally a dead-end at this depth.
> Replay was useful for cheaply waking RX, but the more state you
> accumulate the harder it is to reason about which write does what.
> The combination of "23k blind register writes from another unit" +
> "explicit init in code" + "dynamic FDB learning at L1950" +
> "post-replay re-patch of 4 of 16 DDR pointers" is a state-space you
> cannot mentally simulate. Every test changes 11456+ side-effects.
>
> The cleaner architecture: delete `fpga.bin` entirely, drive every
> register from named init functions matching stock kmod function names
> 1:1 (`sbrg_*`, `cla_*`, `spa_*`, `greg_*`). Yes, this is Phase 7.
> Bring it forward — it's not refactoring, it's the only way to make the
> system debuggable.

## Cited files

- `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c:413-453` — wrong-table `zx_fdb_add`
- `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c:2890-2967` — bulk replay block (to disable for experiment #1)
- `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c:2371-2376` — FDB seed (likely clobbered)
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c:8405` — sbrg_get_indreg_wr_cfg (indirect protocol)
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_tm.c:10549-10700` — sbrg_lookup_mactable (egress consumer)
- `tasks/00.10.02.re-stock-kmods/findings/HW_BLOCKS_INVENTORY.md:25` — greg_port_closed (never written)
