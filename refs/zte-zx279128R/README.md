# ZTE ZX279128R reference material

Source: dumped from a ZTE ZX279128R sibling modem (provided 2026-05-26).
Same family as our ZX279128S (R vs S variant), same Cortex-A9 SMP +
PON/NPP/TM/PP/IDM/SW HW blocks.

## Files

- `zx279128R.dts` — full devicetree from the sibling unit (per-block layout)
- `zx279128R_boot.log` — full stock kernel boot log
  (mirrored from <https://pastebin.com/raw/nKQu5bMJ>, 3540 lines)
- `findings.md` — extracted facts cross-referenced against our driver

## Why this matters for our project

Our current driver lumps every HW block (PON, NPP, IDM, TM, PP, on-chip
switch) into one monolithic ethernet controller with a single 2 MiB
ioremap. This sibling DTS is **authoritative evidence** that the
upstream-correct shape is per-block DT nodes — each block its own
driver / compatible / reg / interrupts.

## Cross-reference table — sibling block → our driver

| Block | Sibling DT compatible | Address | Our driver's view |
| --- | --- | --- | --- |
| PON-side regs | `zte,zx27912x-pon` | `0x92000000`, multiple sub-regs | `eth->pon_early` ioremap |
| MDIO bus | `zte,zx279128s-mdio` | `0x9a101000 0x18` | **NOT USED** — we never read PHY link |
| NPP main | `zte,zx279128s-npp` | `0x921c0000 0x8000` | inside `eth->base` 2 MiB lump |
| NPP secondary | (same node) | `0x921cc000 0x34000` | inside `eth->base` |
| IDM main | `zte,zx27912x-idm` | `0x921c8000 0x4000` | inside `eth->base` |
| IDM secondary | (same node) | `0x92334000 0x4000` | inside `eth->base` |
| SW (switch) | `zte,zx279127-sw` | `0x92300000 0x34000` | **NOT EXPLICITLY USED** — some writes land here via lumped ioremap |
| TM | `zte,zx279128s-tm` | `0x92340000 0x40000` | `TM_OFF=0x180000` from `eth->base` ✓ |
| PP main | `zte,zx27912x-pp` | `0x92380000 0x40000` | `PP_OFF=0x1c0000` from `eth->base` ✓ |
| PP secondary | (same node) | `0x92140000 0x40000` | inside `eth->pon_early` — used unknowingly |
| GePHY (4 ports) | `zte,zx279128s-gephy` | `0x9b000000 + i*0x100000` | **NOT MAPPED** — we never touch the actual PHYs |
| TOPCRM | `zte,ZX279127-topcrm`+`syscon` | `0x94000000 0x1000` | `eth->topcrm`, hardcoded ioremap |

## Discovered HW we were missing

1. **`sw@92300000`** — on-chip switch is its own register block.
   Some scattered TM-block writes we couldn't explain are likely
   writes to SW.

2. **`mdio@9a101000`** + **`gephy@9b000000` (4× 0x100000)** — actual
   PHY control regs. Our driver never touches them, which explains
   why link-state changes and auto-negotiation aren't detected.

3. **`pp@92380000` has a secondary region at `0x92140000`** — PP
   has registers inside the PON window too. Some of the stock writes
   we attribute to "PON_TAIL" may actually be PP writes.

## How to use this reference

- Treat as **read-only** authoritative source for HW layout
- When writing our DT binding YAML / DTS, mirror the per-block
  structure here (not our current monolithic lump)
- When auditing remaining anonymous stock_table writes, cross-check
  the offset against the table above to figure out which block it
  belongs to

This DTS is the closest thing to "vendor reference DT" we have. ZTE
will not provide an official one (we've asked).
