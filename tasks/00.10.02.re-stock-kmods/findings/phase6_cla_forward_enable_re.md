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

## ★★★ UPDATE 2026-06-05 — STOCK CLA CONFIG == MAINLINE (the forward-gate is NOT a config register)
Booted stock and read the CLA config block live via fpga -r (the subagent's stock values were
static-decomp INFERENCES, never read from the device). Live stock (which FORWARDS) vs mainline (traps):
| reg (phys / fpga) | stock | mainline | match? |
|---|---|---|---|
| config 0x9238c080 / e3020 | 0x00000600 | 0x00000600 | SAME |
| l3 mtu 0x9238c088 / e3022 | 0x00007fff | 0x00007fff | SAME |
| poly  0x9238c090 / e3024 | 0x00e400e4 | 0x00e400e4 | SAME |
| outspace 0x9238c094 / e3025 | 0x00000004 | 0x00000004 | SAME |
| up/dn mtu 0x9238c098 / e3026 | 0x7fff7fff | 0x7fff7fff | SAME |
| oth_l3 0x9238c0cc / e3033 | 0x00000000 | 0x00000000 | SAME |
ALL SIX MATCH. The subagent's inferred stock values (config 0xE00, outspace 0x8, MTU 0x3fff) were
WRONG — live stock = mainline exactly. ⇒ the CLA config block is DEFINITIVELY NOT the forward-gate;
stock forwards and mainline traps with byte-identical CLA config. The subagent's zx_cla_fast_forward_
enable() set NON-stock values (outspace 0x8 ≠ stock 0x4, MTU 0x3fff ≠ stock 0x7fff) — REVERTED (removed
the function + call from zx-eth-main.c; FFE extract init kept).
### New direction (config diff exhausted)
Since every static CLA config reg matches, the stock-forwards-vs-mainline-traps difference is NOT a
static register — it is DYNAMIC: stock's FFE software installs the per-flow forwarding STATE (the ram2
hardfast entry + likely SBRAG L3 route + the correct entry ACTION) when a flow is learned; mainline
writes a ram2 entry but it apparently isn't a valid FORWARD entry (or needs a companion SBRAG/da_known
state). PRIME LEAD: decode the ram2 entry ACTION fields — our entry (copied from the stock fwd template
+ substituted 5-tuple) may actually be a TRAP entry, or be missing da_known/direct/act_val=forward.
That alone explains CLA fwd=0 with the entry written everywhere. (Subagent RE in progress on this.)
Secondary: confirm on stock whether CLA fwd[0x9238c3c0] climbs during a routed flow (CLA-hash path) or
stays 0 (then stock forwards routed flows via SBRAG, not the CLA hash — meaning we targeted the wrong
table for L3 routing).

## ★★★★ UPDATE 2026-06-05 — 520-SLOT TEST: gate is UPSTREAM of the hash consult (definitive)
Wrote the (verified-forward) ram2 entry at ALL 520 hash slots across EVERY bank
(ram2[0..0xff]+ram3[0..0x7f]+ram4[0..0x3f]+ram5[0..0x3f]+ram6[0..7]), restored outspace to stock 0x4,
sent the matched routed flow. RESULT: **CLA fwd[0x9238c3c0] delta = 0, hw_trap +80** — still 100% traps.
Combined with: (entry = valid forward, agent-decoded) + (CLA config block byte-identical to stock) +
(extract ram0/ram1 present + run at boot) + (now: entry at every possible bucket in every bank), the
ONLY remaining explanation is that **the CLA never CONSULTS the hash for this flow — an ingress stage
UPSTREAM of the hash lookup traps the packet first.** The entire CLA hash-forward path we built this
session (extract tables, hash engine, write protocol, key builder, per-flow entry) is correct but
NEVER REACHED.
### Where the upstream gate lives (next RE)
The packet path: MAC RX → SPA admit → ingress classify (extract-rule SELECT → ram1 → ram2 hash) → fwd.
CLA fwd=0 means the classify never reaches/acts-on the hash. Upstream candidates, in order:
1. **The ingress extract-rule SELECT** — what makes a packet USE extract-index 9 / a populated ram1
   rule on INGRESS (the HW front-end per-port/per-ptype → extract-index mapping), distinct from the
   ram0/ram1 TABLES (which are present). If mainline never configures the ingress→extract SELECT, the
   hash stage is skipped → trap. RE: how the HW picks the extract path per packet (parser/port config),
   not the API tables.
2. **SPA pktdeal** (0x921d4300, per-(port,ptype) trap/forward) — the #36 merged fix forced the
   forward-slot set to deal=0 for TCP ACKs (CPU-forward); for user→user HW-forward the routed flow's
   ptype may still be deal=trap, trapping BEFORE the CLA. Needs the indirect write
   (zx_spa_set_enty_pktdeal_cfg), not a direct poke.
3. The per-port routing / fast-forward mode set at capWAN/routing provisioning on stock.
DEFINITIVE METHOD (deferred earlier, now clearly needed): kotrace stock ingress for a HW-forwarded
routed flow to see which stage/register makes stock consult the hash + forward, vs mainline trapping —
the static config diff is exhausted (everything matches) so only the live forward path reveals the gate.
