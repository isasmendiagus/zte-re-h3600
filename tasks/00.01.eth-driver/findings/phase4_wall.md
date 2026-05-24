# Phase 4 — autonomous wall + path forward

After Phase 3c (4738 entries with args across 58 traced fns) the
autonomous /loop hit a structural wall trying to actually port chip_tm_init
to the mainline driver. This doc explains why + what to do next.

## The wall

Tracing the call chain by hand for `tm_port_isolate_set` (the simplest
case, called 8 times with simple per-port args):

```
zte_api_sw_port_set_port_isolatemask(port, mask, cb, 0xff)
  └─ tm_port_isolate_set(port, mask)               ← Phase 3c traces this
     └─ (per-port jump table on r0=port)
     └─ sbrg_set_isolate_pt_cfg(transformed_mask, r1)
        └─ tmOnuRegWrite(REG_ID=0x39, val, sub_idx, flag)
           └─ tmOnuGlbRegValidation(REG_ID, &desc_out)
              └─ returns pointer into a DESCRIPTOR TABLE keyed by REG_ID
           └─ fpga_read_reg(desc.base + desc.scale * sub_idx)
           └─ apply mask + value
           └─ fpga_write_reg(addr, new_val)
```

Every zte_api_* function bottoms out at `tmOnuRegWrite(REG_ID, ...)`,
where **REG_ID is an opaque integer** (0..~512) that maps to a hardware
address via a descriptor table stored in tm.ko's `.rodata`.

Without that table → no hw address → no way to write the C equivalent.

We tried patching `tmOnuRegWrite` itself (Phase 3d) so the runtime args
would have included the resolved hw address — but the thunk overhead in
that hot path (374 call sites × many invocations) broke chip_tm_init.

## What we have

Plenty, even without the descriptor table:

- **4738-entry trace** with full args for 58 functions (`captures/kotrace_p3c_full_args.txt`)
- **Per-function distinct-arg patterns** (`captures/kotrace_p3c_analysis.txt`)
- **`def_ptl_pkt_action` table** extracted as a usable C header
  (`linux-v6.6/drivers/net/ethernet/zte/zx-pp-pro-actions.h`)
- **VLAN ethertypes** identified: 0x8100 (802.1Q), 0x88a8 (S-VLAN), 0x9100 (QinQ), 0x9200 (custom)
- **PP buffer pool size**: 0x1f40 = 8000
- **Per-port isolate masks** (8 values)
- **Per-port broadcast/unicast/multicast modes**

## To unblock — three options ranked by ratio of payoff to effort

### Option A (recommended) — extract the descriptor table from tm.ko once

Open `tasks/00.10.02.re-stock-kmods/ghidra/` (already has tm.ko imported),
find `tmOnuGlbRegValidation`, follow the table reference, dump the table
as a C array. ~2-4 hours one-shot, never need to repeat.

The table is keyed by REG_ID (integer 0..~512); each entry probably:
- `base`: u32  — the actual MMIO offset within the TM block
- `stride` or `scale`: u32 — multiplied by sub_index
- `mask`: u32 — applied to value
- `shift`: u8 — applied before/after mask
- Plus validation bits

Once extracted as a C header `zx-tm-reg-table.h`, every future
`tmOnuRegWrite(REG_ID, val, sub_idx, flag)` translates trivially:
```c
const struct zx_tm_reg *r = &zx_tm_regs[REG_ID];
u32 addr = r->base + r->stride * sub_idx;
u32 v = (readl(tm_base + addr) & ~r->mask) | ((val << r->shift) & r->mask);
writel(v, tm_base + addr);
```

That single helper + the descriptor table + the Phase 3c trace = we can
generate the entire chip_tm_init replay automatically.

### Option B — patch tmOnuRegWrite via a less-invasive instrumentation

Instead of kotrace's `b thunk` patch (which adds ~50ns and apparently
breaks timing on hot paths), implement a smaller in-place capture:
- replace the function's first 4 bytes with `bl __our_capture_stub`
  where __our_capture_stub is in module_alloc'd memory next to tm.ko's text
- our stub uses ARM A32's PC-link semantics (lr = call site) to know
  the caller — useful for distinguishing call contexts
- only enabled briefly via a sysfs trigger, not at boot

Cost: 4-8 hours. Removes the boot-time timing dependency by capturing
post-init via deliberate trigger.

### Option C — accept partial port, brute-force the rest

The existing driver already does HEAVY static replay (`cla.bin`,
`pm.bin`, `stock.bin`). Add ONE MORE replay: dump the final state of
every PP/TM register from a working stock boot via `devmem` + a script,
generate `tm_state.bin`, replay at probe time.

This is what got us most of the way already. The missing piece is
ORDER-DEPENDENT writes — some registers can only be written when
others have certain values, or trigger one-shot effects when written.

Phase 3c trace tells us the ORDER. Replay in that order, using state
snapshots, may be enough. Less precise than Option A but doesn't need
tm.ko table extraction.

Cost: 1-2 days, low certainty of success.

## Recommended sequence

1. **Now (one-shot, ~2h)**: Option A — extract the descriptor table.
   This unlocks Options A and B for all future work.
2. **Then (mechanical, ~1-2 days)**: write a Python script that consumes
   `kotrace_p3c_full_args.txt` + the descriptor table → emits C source for
   a `zx_chip_tm_init_replay()` function with all 4738 calls' equivalent
   `writel`s. Add to driver, RAM-boot test.
3. **If RX still dead**: trace more sub-functions (use Phase 3c kotrace,
   add more targets carefully — vlantable_add and the leaf reg helpers
   are off-limits per Phase 3c/3d failures).

The autonomous /loop cannot do step 1 — needs Ghidra UI work.
