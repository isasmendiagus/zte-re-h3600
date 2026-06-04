# Phase 6 / Stage 0a-deeper — HFF ⇄ existing CLA RE reconciliation + forward-entry layout

2026-06-04, branch phase6-hw-offload. Reconciles the new HFF chain (ffe_hardfast_install_re.md +
ffe_hardfast_regwrites_re.md) with the PRIOR CLA RE (cla_ram_layout_re.md + memory zte-cla-ram-layout).
**Big result: Phase 6 is heavily de-risked — the CLA write primitive and a live-read tool already
exist in our mainline driver.** The HFF hardfast install and the ingress classification we RE'd in
May write the SAME table (CLA ram2-6 hash) via the SAME indirect interface.

## What we ALREADY had (cla_ram_layout_re.md, 2026-05-31) — confirmed = the HFF target
- **CLA indirect interface** ✅: `CLA_REG_CMD=0x1CC014` (cmd = addr | ram_id<<22 | rw<<27),
  17 data slots @ `0x1CC01C`, done bit @ `0x1CC018`. (npp_base 0x921c0000 → these are offsets.)
- **Driver already implements it** ✅: `zx_cla_write_entry` / `zx_cla_read_entry`
  (linux-v6.6/.../zx-eth-main.c:1994/2007) — generic 17-word CLA indirect read/write.
- **Live read tool** ✅: debugfs `clapeek` (`echo "<ram_id> <addr>" > .../clapeek` → 17 words to kmsg)
  and `cladump`. So we can READ any CLA hash entry on our own running driver — ground truth for free.
- **ram2..6 = `cla_set_hash_table` @ tm.c:3366** = the classification/result HASH table; 15 words/ent;
  internal-hash addr banks (0..0xff→2, 0x100..0x17f→3, 0x180..0x1bf→4, 0x1c0..0x1ff→5, 0x200..0x207→6).
- Prior entry-field notes (the INGRESS/trap view): `inport=(byte[0x0e]&0x3f)<<6|(byte[0x0d]>>2)`;
  trap action `cpu_qid`+`cpu_qid_rp_en`; `valid_en`/`direct` in byte[0x10]. And the bridge note:
  `sw_acl_setMtchInfo` (switch.c:1035) sets the HFF flow inport at descriptor +0x9e (switch port; pon→5).

## Reconciliation: ingress-classification vs L3-hardfast use the SAME ram2-6 hash
The May RE looked at ram2-6 as the per-inport ingress classifier (trap-action entries). Stage 0a-deep
showed the L3 HFF hardfast (tm_acl_fast_add_v4v6 → cla_set_hash_table) writes the SAME ram2-6 table,
but with a **forward/redirect action** (egress uni/gemport) instead of a CPU-trap action. Same table,
two entry "flavours" (key always = the classifier tuple; action = trap OR forward).
- internal hash = cla_set_hash_table (ram2-6, slot&0x7fff); external hash = `cla_set_external_hash_table`
  @ tm.c:3792 (separate larger table, slot&0xffff) used when the internal banks are full.

## Forward-action entry layout (tm_acl_get_fastHashRule @ tm.c:49213, builds param_4 from flow param_2)
param_4 = the CLA hash entry bytes (≤ ~0x13 used of the 15-word entry); param_2 = flow descriptor:
- **egress target (the forward action)**: flow+0xb2 = target UNI/gemport port (validated; else
  "Invalid target uni port!" tm.c:~49383). Encoded into `param_4[1]` (low nibble) + `param_4[2]`
  (tm.c:197-207). flow+0xb0/0xb1 also feed param_4[0]/[1] (tm.c:142-150).
- **direction/mode**: flow+0x10 (==0 / ==1 switch decides uni-port encoding; tm.c:151,201).
- **action/valid byte**: `param_4[0x10]` gets `(flow+0x10 & 1)<<5` (tm.c:111) — consistent with the
  prior `valid_en/direct in byte[0x10]`. `param_4[0x12]` bit2 = (flow+0x10==0) (tm.c:103).
- field at flow+0x10 also → `param_4[0xe]=(v<<6)`, `param_4[0xf]|=(v>>2)` (tm.c:121-122) — the
  inport-like field (prior note had this at 0xd/0xe for the trap entries; forward uses 0xe/0xf).
- param_4[3..9] = misc flags from param_3 + bVar1/2/3 (priority/proto/len-changed g_pktLenChged etc.).
- NAT: the rewrite is keyed by the flow descriptor's optional field (+0x9d==0xff sentinel in the
  session struct, ffe_hardfast_install_re.md) — exact NAT-rewrite bits in the entry = still ❓
  (resolve via 0b koprobe, capture a stock NAT flow's entry).

## ⇒ What this means for the Linux backend (Stage 1-2)
We can program a HW forward by writing a ram2-6 hash entry with `zx_cla_write_entry` (already in the
driver): key = the flow's classifier tuple, action = egress uni/port (param_4[1..2]) + valid byte
0x10. We can VERIFY with clapeek (read the slot back) and with pipeline_stats/hw_trap (CPU goes flat).
The hash slot/address computation (cla_get_hash_poly_config + aclGetAvailableHashAddr) is the main
thing still to pin for self-computed slots — OR sidestep it initially by reading where stock places a
known flow (clapeek) and matching.

## UNKNOWNS → next
- 0b koprobe/clapeek GROUND-TRUTH: on stock, establish one iperf flow LAN→WAN; kotrace
  cla_set_hash_table + tm_acl_get_fastHashRule to capture the exact entry bytes + slot; OR read it
  back. Confirms the forward-entry bit layout + NAT-rewrite fields + the slot/hash.
- the hash function (cla_get_hash_poly_config polynomial + aclGetAvailableHashAddr) — for computing
  our own slot (Stage 2+).
- 0c Linux flow_offload/flowtable hooks; 0d design (Linux 5-tuple+action → this ram2-6 forward entry).
