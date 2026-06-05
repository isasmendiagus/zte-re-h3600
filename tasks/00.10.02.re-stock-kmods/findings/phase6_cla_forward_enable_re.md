# Phase 6 — CLA forward-enable RE (the last switch from trap-all → hash-forward)

## Question
With the FFE extract tables (ram0/ram1) ported + running at boot and the per-flow ram2 entry written,
a routed flow STILL traps 100% and `CLA fwd[0x9238c3c0]=0` — the CLA never makes a forward decision.
What enables the CLA forward/hash-consult path?

## RE (subagent, static decomp) — where the CLA global config is set
- The FFE-init caller `aclRamInit.part.6` (tm.c:54670, calls the inits under `if (g_fast_opti)`) writes
  NO CLA mode/enable register. `cla_set_trap_acl_en_config` is never called. So the enable is NOT in
  the FFE-init path.
- The real CLA global init is `tm_pon_pp_cla_initial` (tm.c:42727), writing 5 config regs; mainline
  replicates only 2. The 3 mainline never wrote: outspace cfg (0x9238c094), l3/up/dn MTU-length
  (0x9238c088 / 0x9238c098). Prime suspect: **outspace 0x9238c094 = 0x8** (ACL_OUT_HASH_NUM/SPACE_SEL,
  the hash-out slot mapping).

## ★ ON-DEVICE TEST (interactive session) — both candidates REFUTED
Peeked the LIVE values (current FFE-init build) — they are NOT zero (the subagent's reset assumption
was wrong), but DO differ from stock:
| reg | phys | mainline (live) | stock | note |
|---|---|---|---|---|
| cla config     | 0x9238c080 | 0x00000600 | ~0xE00 | missing bit11 0x800; trap_acl_en(bit17)=0 (not trapping) |
| l3 mtu         | 0x9238c088 | 0x00007fff | 0x3fff | already large (not 0) |
| poly cfg       | 0x9238c090 | 0x00e400e4 | (matches) | validated earlier |
| outspace cfg   | 0x9238c094 | 0x00000004 | 0x8 | HASH_NUM 1 vs 2 — real diff |
| up/dn mtu      | 0x9238c098 | 0x7fff7fff | 0x3fff3fff | already large |
| oth_l3_action  | 0x9238c0cc | 0x00000000 | 0 | matches |

Tested by LIVE poke (ram2 entry already at all 256 buckets), then 80-SYN routed flow:
- poke outspace 0x9238c094 = 0x8 → **CLA fwd still 0**, flow traps (+93). REFUTED.
- poke config 0x9238c080 = 0xE00 (set bit 0x800) → **CLA fwd still 0**, flow traps (+93). REFUTED.

⇒ Neither the outspace cfg nor the config bit11 is the forward-gate. The CLA fwd counter is stubbornly
0 even with extract tables present, a matching entry at every bucket, and stock-matching config regs.
The trap-all is deeper than the obvious CLA config registers (consistent with the long deadend history,
which now holds EVEN WITH the extract chain present).

## Status of the subagent's code
`zx_cla_fast_forward_enable()` (zx-eth-main.c) writes outspace=0x8 + MTUs=0x3fff (stock parity, RMW,
conservative). KEPT for stock-config parity (and outspace=0x8 makes the slot mapping match stock, useful
for the eventual bucket computation), but it is NOT the forward-gate (HW-refuted above).

## NEXT RE TARGET (the definitive method)
Static decomp of CLA config regs is exhausted. The forward-gate must be found by **live stock kotrace /
register diff at the moment stock forwards a routed flow**: boot stock, provision capWAN (routing), run
a LAN→WAN flow that HW-forwards (CLA fwd climbs on stock), and capture the FULL CLA + SADM + SPA +
parser config region that differs from mainline — OR kotrace the stock ingress decision for a forwarded
packet. Candidates to focus the diff: the parser/ingress→fast-path SELECT (what routes a packet INTO
the CLA hash stage vs the trap path), the SADM forward routing (SADM drop counter 0x1c4208 was huge in
pipeline_stats), and any per-port "fast/acl forward" mode bit. The hash side + extract are done; this is
purely "what makes the CLA consult+forward vs trap."
