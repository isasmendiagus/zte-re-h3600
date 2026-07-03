# HW flow-offload — performance notes / known issues (2026-07-03)

The HW L3 flow-offload is **functionally validated end-to-end** on real internet traffic
(delivery + NAT + live conntrack auto-offload + real resolved next-hop + bidirectional HW
forwarding). This doc records the **performance** status and the known issues, separate from the
functional milestone.

## Current performance state
A real download through the device (LAN client → route+NAT → WAN/modem → internet) **works and is
HW-offloaded**, but throughput has been limited by the issues below. As each is fixed the flow moves
from "CPU-bound slow-path" toward "HW line-rate, CPU idle."

## Issue P1 — nft flowtable offloaded only ONE direction (FIXED)
On Linux 6.6 the nft flowtable offload path is **unidirectional**: `nf_flow_table_offload.c`
`flow_offload_rule_add()` pushes the REPLY direction to the driver only when
`NF_FLOW_HW_BIDIRECTIONAL` is set, and that flag is set *only* by the tc `act_ct` path — never by the
nft flowtable path (`nft_flow_offload_eval` → `flow_offload_add`). Result: only the ORIGINAL (upload)
direction offloaded; every reply/download packet fell to the SW slow-path.
**Fix (staged):** `net/netfilter/nft_flow_offload.c` — `__set_bit(NF_FLOW_HW_BIDIRECTIONAL, &flow->flags)`
before `flow_offload_add()`. Both directions now install (verified: distinct UP/DN 5-tuples, egress
ports, next-hop MACs). This is a generic netfilter change (candidate for upstreaming).

## Issue P2 — single shared PM next-hop slot: UP/DN clobber (FIX CODED, validating)
The driver wrote the PM flow_info / next-hop / sub_ram / cmd_ram to a **hardcoded slot (5)** for every
flow AND both directions (`zx_ft_install_recipe`), so the upload entry (next-hop = modem MAC, egress
lan4) and the download entry (next-hop = client MAC, egress lan2) overwrote each other → one direction
always had the wrong next-hop → its packets missed the HW forward and crawled on the SW path. Secondary:
`zx_ft_pack_cla` hardcoded `cla[1]` → `cmd_flow_id`(byte0x04)=0, inconsistent with the PM slot.
**Fix (coded, under validation):** per-(flow,direction) PM-slot allocation — `zx_ft_flow_reserve`
assigns `pm_slot = ZX_FT_PM_BASE + tracking_index`; `zx_ft_install_recipe` writes PM at `pm_slot`;
`zx_ft_pack_cla` threads `pm_slot` into `cla[1]` byte0x04 so each CLA entry points at its own PM slot;
destroy frees the slot. Expected result: both directions HW-forward ~100% → the download runs at
HW rate with the CPU near-idle. (This is the review's H3 caveat, now resolved for the FT path.)

## Issue P3 — WAN-RX one-wrap wedge (related, reboot-only HW latch)
The WAN/lan4 RX→CPU path halts at exactly 1024 frames: the RED CPU-trap queue fills its 1024
out-buffer and RED then demotes further traps to sw_fwd. Four software unwedge attempts all failed →
it's an internal HW accounting state, reboot-only clear. **This is a SYMPTOM of trapping to CPU** — it
only bites when packets aren't being HW-forwarded. Once P1+P2 make the flow HW-forward (packets bypass
the CPU trap), the trap queue stops filling and the wedge does not trigger for offloaded traffic. On a
fresh boot the 1024-frame budget is enough to establish + offload a flow before the wedge. So P3 is
effectively cured by working offload; no standalone fix is required for the offload use-case.

## Other robustness items (from the code review — documented, not perf-critical)
- H1: the DSA-side `cls_flower_add` lacks proto/family/daddr validation (the FT side has it) — add it so
  IPv6/ICMP/L2 flower+redirect rules are declined rather than installing a garbage recipe.
- M1: no locking on the flow table / the stateful CLA hash engine; the FT path runs in an unbound
  workqueue (not rtnl) — add a mutex around the reserve/install/untrack + hash-engine sequence.
- M2: REPLACE with a changed 5-tuple doesn't clear the old CLA buckets (stale HW).
- M3: the built-in binder calls the conduit module's `zx_pm_ops` pointers with no RCU/module-ref
  synchronization (module-unload UAF risk).
- L: entries write 15 of 17 words (stale tail); CLA writes lack the readback-verify the PM path has.
See findings/offload_code_review_2026-07-03.md for the full ranked list.

## Bottom line
Functionally: **HW offload routing works end-to-end on real traffic.** Performance: P1 fixed, P2 fix
coded + validating (the two that gate download throughput), P3 cured-by-offload. Once P2 validates
fast, the offload is both correct and performant; the remaining items are hardening.

---
## UPDATE (2026-07-03, build #472) — P2 fixed but NOT the gate; the real blocker is the CLA hit-rate (offload currently NET-NEGATIVE)
The per-direction PM-slot fix (P2) is **implemented + validated** (dmesg: UP pm_slot=8 nh=modem eg_rp=5; DN pm_slot=9 nh=client eg_rp=3 — distinct slots, correct next-hops, no clobber; ownership-destroy frees both). **But it did NOT cure the crawl** — it sits downstream of the real gate.

**A/B control on the same 1 GB download (decisive):**
- nft flowtable + `flags offload` (HW path): **~16 B/s** (crawl), WAN `QMG DN hw_trap` climbed to **1024 (pinned) = the WAN-RX trap wedge**, modem ARP then failed.
- nft flowtable removed (pure SW routing): **~20 KB/s**, no wedge.
⇒ **Enabling the HW offload is currently WORSE than pure SW routing (net-negative).**

**Root cause = low CLA hit-rate on real traffic.** Over the download, DN: hw_fwd Δ+13 vs sw_fwd Δ+39 / hw_trap Δ+47 → only ~13% of DN packets HW-forward; ~87% MISS the hash-compare/verdict → trap → fill the RED trap queue → the 1024 wedge. UP never HW-forwards either (UP hw_fwd=0). This is the SAME ~13% ratio as before the PM-slot fix, confirming P2 was not the throughput gate.

**Why ~13% for a real flow when a pinned single UDP flow hit ~100%?** UNRESOLVED — this is the new #4 blocker and the clear next target. Hypotheses to test: (a) the real flow's packets vary something that changes the extracted key per-packet (only a subset hash to the installed bucket); (b) TCP data/large-MTU packets extract differently than the small pinned test packets; (c) a WAN-ingress-specific extract/verdict difference; (d) the installed DN entry only matches a fraction (offset/window mismatch on real headers); (e) intermittent eviction/re-classify. Need per-packet analysis of which DN packets hit vs miss (read gparsehashkey + desOut per packet, and correlate with packet size/flags).

**⇒ P4 (NEW, the real perf gate): raise the real-traffic CLA hit-rate from ~13% to ~100%.** Until then, do NOT enable the offload flowtable in production (it's net-negative + trips the WAN wedge). The functional offload (a matched flow DOES HW-forward) remains validated; the issue is that most real-traffic packets don't match.
