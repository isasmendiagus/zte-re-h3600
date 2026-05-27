# [Iter 15] NPP write gaps are phantom — runtime already matches stock

Validation run 2026-05-27. The 4 "missing NPP writes" flagged in
`stock_init_sequence_analysis_2026-05-27.md` table line 178-182 were
re-checked at runtime via memdump.

## Bench reads on running mainline (post Iter 14 boot)

```
NPP[+0x04]    = 0xffffffff   ← matches stock target ✓
NPP[+0x40]    = 0x00000000   ← stock decomp says |= 0x300, runtime is 0
NPP[+0x48]    = 0x00000000   ← matches stock target ✓
NPP[+0x10008] = 0x00000080   ← matches stock target ✓
```

3 of 4 are already at stock-expected values (warm-boot inheritance or
mainline init writes). Only NPP[+0x40] differs from the decomp's
`|= 0x300` claim.

## NPP[+0x40] test

Tried setting bits 8+9 from REPL:
```
/bin/busybox devmem 0x921c0040 32 0x300
/bin/memdump 0x921c0040 4
921c0040 00000000   ← write did NOT stick
```

**HW-locked from direct write.** Same pattern as PP[0x2c] upper bits.

## Verification mainline already accounts for this

Mainline driver `zx-eth-main.c:1258` explicitly comments:
```c
/* stock NPP[0x40] = 0 → don't OR 0x300 */
```

The author already determined that stock's RUNTIME state for NPP[0x40]
is 0, not 0x300 — the decomp's OR-in must get rejected by the same
HW-lock that rejects mainline writes, OR the OR-in was conditional on
state we don't know about. Either way: mainline matches stock runtime.

## Conclusion

Iter 15 = no driver change required. The "missing NPP writes" gap was
a phantom — RE'd from static decomp but not present at runtime.

Cross-ref stock_init_sequence_analysis_2026-05-27.md should be updated
to reflect that NPP[+0x40] is in the "decomp says X but runtime is Y"
category alongside PP[0x2c] bit 29.

## Recurring HW-lock pattern

| Reg | Decomp says | Runtime is | Mainline matches |
|---|---|---|---|
| PP[0x2c] bit 29 (lan_up_port=4) | `\|= BIT(29)` | bit 29 stays 0 | ✓ matches (also can't write) |
| NPP[+0x40] bits 8+9 | `\|= 0x300` | stays 0 | ✓ matches (also can't write) |

The HW-lock for both is the same mystery. Stock SOMETIMES sees these
bits set in its OWN running state (per earlier findings) but neither
stock-on-our-device nor mainline can set them via direct write. There
must be a "write enable" / "config commit" register stock toggles
before these writes — not yet RE'd.

## Next iter targets

Pivot to A17: stock has TWO netdevs ("sw" and "pon"). Mainline only
has "sw". Stock's `pon_tm_net_open` (decomp 6519) has open-gated
behavior: `if strcmp(name,"pon")==0 → mask &= ~3`. There may be more
PON-netdev-specific HW setup we're missing. The TX consume wedge could
be tied to HW expecting a "PON link up" handshake.

Cross-ref:
- `stock_init_sequence_analysis_2026-05-27.md` table line 178-182
- `mainline_gap_matrix.md` [A17]
- `iter11_a11_not_tx_cause_2026-05-27.md` (PP[0x2c] HW-lock prior finding)
