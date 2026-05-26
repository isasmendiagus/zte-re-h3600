# Stockport → Mainline refactor plan (task #38)

**Input**: `tasks/00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md`
— the SHARED stock init-flow knowledge captured 2026-05-26 from live
SHIM_TRACE + kotrace + Ghidra. **Read that doc first**.

**Goal of task #38**: replace the ~480 KB of binary replay blobs
(`fpga.bin`, `stock.bin`, `cla.bin`, `pm.bin`) in our mainline driver
with explicit C code, derived from the stock init flow we now
understand. Result: an upstream-quality driver, no opaque firmware,
no fragile bulk-replay edge cases (e.g. the DUPs storm we hit before
commit `2a9ec34af`).

## Why the current bulk replay is fragile

The replay was captured from a single boot of stock cspd. Issues:

1. **Snapshot at a single instant** — if stock was mid-update, some
   regs are at the in-between value. Random "sometimes ping, sometimes
   DUPs" before the FDB-write-order fix.
2. **No timing/order** — replay does writes in dump order. Some HW
   blocks REQUIRE specific ordering (the FDB D2→D1→D0 case).
3. **Indirect tables invisible** — stock writes to RAM via an indirect
   addr+data register pair. Direct MMIO dump captures only the last
   pair's residual state, not the table contents.
4. **Not portable** — assumes our exact SoC stepping + firmware version.
5. **Not upstreamable** — kernel-upstream won't accept opaque blobs.

## What we have to refactor (current zx279128-eth.c structure)

**Current driver** (commit 5c8705feb): 3,483 lines C +
`replay_stock`/`replay_cla`/`replay_pp_pm` tables.

The driver already has some explicit functions for blocks we
understand:

| Function | What it does | Status |
|----------|-------------|--------|
| `zx_pp_init()` | PP global init | ✅ partial — has verbatim replay for offsets 0x00–0x118 |
| `zx_npp_init()` | NPP global init | ✅ partial |
| `zx_idm_init()` | IDM RX/TX setup | ✅ explicit |
| `zx_smac_init_port()` | SMAC bank per port | ✅ explicit |
| `zx_tm_bmu_init()` | BMU pool setup | ✅ explicit |
| `zx_brg_*` | Bridge FDB ram ops | ✅ explicit (the D2→D1→D0 fix lives here) |
| `zx_sbrag_*` | Secondary bridge | ✅ explicit |
| `zx_pp_pm_*` | PP per-MAC ram | ⚠️ uses `zx_pp_pm_apply_replay` |
| `zx_cla_*` | Classifier | ⚠️ uses `zx_cla_apply_replay` |
| stock replay | The big 22k blob | ❌ totally opaque |

## Refactor strategy (incremental, low risk)

For each block in stock's init flow, replace its bulk-replay portion
with explicit C derived from kotrace traces + Ghidra decomp.

### Phase 1 — replace `zx_cla_apply_replay()`

**Map**: stock's tm.ko `aclRamInit()` → mainline `zx_cla_apply_replay`.

Stock does:
```c
memzero(0xf1020000, 4 MiB);   /* zero ACL RAM bank 1 */
memzero(0xf1420000, 1 MiB);   /* zero ACL RAM bank 2 */
for each acl idx 0..N:
    cla_set_extra_index_table(idx, ...)
    cla_get_indirect_rw_status()
```

Our equivalent (today):
```c
zx_cla_apply_replay(e);   /* loops cla.bin entries */
```

**Refactor**:
1. Zero the ACL RAM via explicit `memset_io` to the ioremap'd ACL RAM
2. Call `zx_cla_set_extra_index_table()` (new function we write) once
   per ACL slot, with parameters derived from the `decomp_all_tm.c`
   Ghidra output of `cla_set_extra_index_table`.
3. Delete `cla.bin` from initramfs + `zx_cla_apply_replay()` from
   driver.

Estimated 4-6h. Lowest risk because ACL RAM init is mostly zero-fill.

### Phase 2 — replace `zx_pp_pm_apply_replay()`

**Map**: stock's plat.ko PP per-MAC ram setup → mainline `zx_pp_pm_apply_replay`.

Stock writes to PP per-MAC RAM (PM = "per-MAC"). The MAC entries are
populated during sw_init_switch's `pdt_ethdriver_init` and as part of
the chip_tm_init flow.

**Refactor**:
1. Identify the few MAC entries that actually matter — kotrace-trace
   stock during stock boot to capture which PM offsets get written.
2. Write `zx_pp_pm_set_cpu_mac()` (already exists) for each MAC, with
   explicit values.
3. Delete `pm.bin`.

Estimated 2-3h.

### Phase 3 — chip_tm_init explicit port (biggest win)

**Map**: stock's switch.ko `chip_tm_init()` → mainline currently relies
on bulk `stock.bin` replay for ~22k regs.

Stock's `chip_tm_init` (Ghidra decomp in
`tasks/00.10.02.re-stock-kmods/findings/decomp_all_*.c`) does TM block
init (sched/shape/queues). We need to:

1. Identify each register block written:
   - TM schedule table (probably ~256 entries × N tables)
   - TM port shaper config
   - TM queue mappings
   - TM CAM lookup config
2. Replace bulk replay with explicit table generators in C.
3. Use DT for the variable parts (num_ports, queue counts).

Estimated 1-2 days. Highest value (~80% of the 22k stock regs).

### Phase 4 — sbrg/dpa/spa/sdet init (tasks #40, #41)

These are remaining stock subsystems:
- **dpa** (Destination Processing Agent) — HW responder for ICMP/ARP
- **spa** (Source Processing Agent) — CPU port frame handling
- **sdet** — frame-length detection
- **greg** — global egress reg port state

Each block: capture kotrace at stock init → replace bulk with explicit.

### Phase 5 — MDIO + PHY support

Currently `zx_mdio_read/write` are stubs returning 0xffff. To get real
PHY behavior:

1. Map the MDIO controller in switch.ko's MMIO region (from
   `decomp_all_switch.c` find which MMIO it uses).
2. Implement a real `mdiobus` per kernel `phy.h` standards.
3. Register phy_drv for the actual PHY chips (4 ext + 1 internal).
4. Replace forced `netif_carrier_on()` with proper PHY state machine.

Estimated 4-6h. Unlocks hot-plug, auto-neg, ethtool reporting.

### Phase 6 — DT bindings

1. Document `zte,zx279128s-eth` binding in
   `Documentation/devicetree/bindings/net/zte,zx279128s-eth.yaml`.
2. Move per-board hardcoded values (BMU pool sizes, port count, etc.)
   to DT.
3. Validate against the `zx279128s.dtsi` we created for stockport.

Estimated 2-3h.

## What stockport gave us that makes this possible

| Tool | Output | How we use it |
|------|--------|---------------|
| **SHIM_TRACE** in stockport | 16,340 events with caller resolution | "What functions does stock CALL at boot?" |
| **kotrace** on stockport | 214 in-place patches across 5 stock kmods | "What ARG values do those calls receive?" |
| **regtracer** on stockport | Poll-based MMIO diff | "What HW regs change in steady state?" |
| **Ghidra decomp** | Decompiled C for every stock function | "What does each function do?" |
| **vmlinux-to-elf** | 43,215 stock symbols | "Where is each ZTE-added kernel function?" |
| **netdev_probe** | struct net_device offsets | "Stock layout vs ours — by how much?" |

For any specific function we want to RE during the refactor, we can:
1. Find it in `tasks/00.10.02.re-stock-kmods/findings/decomp_all_*.c`
2. Cross-reference its callers via `ARG_SIGNATURES.json`
3. If needed live, boot stockport + load kotrace with the function in
   its target list → trigger the path → read /proc/kotrace_dump

## Execution order recommended

```
1. Phase 1 (cla refactor)     — easiest, builds confidence
2. Phase 5 (MDIO + PHY)        — independent of others, fixes hot-plug
3. Phase 3 (chip_tm_init)      — biggest blob, biggest win
4. Phase 2 (pp_pm refactor)    — easier with TM understanding
5. Phase 4 (sbrg/dpa/spa/sdet) — final cleanup
6. Phase 6 (DT bindings)       — upstream prep
```

Total estimate: 4-7 days for full refactor.

## Risks + mitigations

| Risk | Mitigation |
|------|-----------|
| Refactor breaks PING BIDI | Keep `bulk_replay` flag at build-time. Refactored blocks can be enabled one-by-one. |
| Some stock writes are essential but we miss them | Compare pre/post-refactor MMIO trace via regtracer — if any reg changed, investigate. |
| HW state inconsistent during transition | After each phase: full reboot test, ping flood test (100+ pings), iperf TCP+UDP. |
| DUPs storm returns | Run `tcpdump -i eth0` during ping flood, count duplicates. If >0, investigate FDB write order in the refactored path. |

## Cross-references

- **Source data**: `tasks/00.10.02.re-stock-kmods/findings/eth_init_flow_2026_05_26.md`
- **Decomp**: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_*.c`
- **Stockport build**: `tasks/99.01.linux-stockport/` (still-usable live oracle)
- **Current driver**: `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`
- **Replay blobs**: `tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay/`
- **PING BIDI commit** (the win that made refactor worth doing): `2ad931ed8`
- **0 DUPs commit** (the fix that made it reliable): `2a9ec34af`
