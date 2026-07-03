# 🎉 MILESTONE — HW flow-offload working on mainline (2026-07-02, overnight)

**Read this first in the morning.** Selective per-flow L3 hardware forwarding now works on the
mainline Linux 6.6 DSA driver, driven by standard `tc flower`. CPU configures, hardware forwards,
CPU idle — the core goal of this whole effort.

## What was achieved (validated end-to-end, reproduced)
On build **#458** (fresh DTR boot), the **driver itself** installs a HW-forward recipe via the DSA
user-port tc-flower path:
`tc filter add dev lan1 ingress flower skip_sw ... action mirred egress redirect dev lan4`
→ `zx_dsa_cls_flower_add` → `zx_install_l3_recipe` → `zx_cla_pack_entry`.

Measured (2 independent bursts):
- matching flow (UDP 172.31.9.50:50010→192.168.9.50:53) → `cla_tx_fwd +400` AND lan4/MAC4 TX +400
  (physical wire egress), no CPU trap.
- non-matching flow (dport 5555) → traps, no forward.

Genuine content-selective 5-tuple hash hit — not a catch-all.

## Root cause of the multi-week block (it was NOT what we thought)
It was never an "engine regression", a hidden enabling-operation, or intra-boot state. The CLA hash
lookup engine was healthy all along. Two concrete bugs:

1. **`word3` of the ram2 entry is NOT a valid bit** — it is the high part of the `extr_index` field
   (`extr_index = byte0x10<<4 | byte0xf>>4`, decomp `cla_set_hash_table:3444`). The stock-captured
   value `0x80000000` made `extr_index` low byte = `0x98`, but the flow classifies under extract rule
   `0x90` → `0x98 != 0x90` → `LOOK_UP_MISS` on *every* packet, regardless of perfect windata/slot/fill.
   **This was the load-bearing bug.**
2. `ram0[9]` extract-index arming selected rule `0x96` (a volatile per-packet key) instead of the
   clean 5-tuple rule `0x90` in some paths.

## The fix (3 edits, STAGED — NOT committed, per instruction)
Branch `phase6-hw-offload`, tree `linux-v6.6` (note: its git worktree gitdir link is currently broken —
`git` from the tree errors; the edits are on disk regardless):

1. `drivers/net/ethernet/zte/zx-eth-main.c` — `zx_ft_pack_cla`: `cla[3] = 0x80000000;` → `cla[3] = 0;`
2. `drivers/net/dsa/zte/zx-dsa.c` — `zx_cla_pack_entry`: `cla[3] = 0x80000000;` → `cla[3] = 0;`  (load-bearing)
3. `drivers/net/ethernet/zte/zx_ffe_table.h` — `zx_ffe_index` id=9 word4 `0x00150051` → `0x00150001`
   (arm only clean rule 0x90). NOTE: `zx_ffe_arm` (zx-dsa.c:671) overwrites `ram0[9]` back to
   `0x00150151` on DSA install, and the forward still works — so #3 is effectively redundant/inert.
   Reconcile in review: either drop #3 or make `zx_ffe_arm` consistent. #2 is the essential fix.

## Remaining work for a production router (not yet done)
1. **nf_flow_table / conntrack AUTO-offload** — the last mile. Real established connections should
   auto-install (no manual tc). The conduit's `ndo_setup_tc` TC_SETUP_FT flowtable block does not bind
   yet (attaching flower to conduit `sw` → EOPNOTSUPP); only the DSA user-port `cls_flower` path is
   reachable from userspace. Needs the flowtable binding + next-hop MAC from the neigh table
   (`CONFIG_NET_ACT_PEDIT` is also off, so tc couldn't inject the next-hop MAC — a seeded fallback was
   used; conntrack path takes the MAC from the flow, so this is a tc-manual limitation).
2. **NAT rewrite offload** (stock does SNAT/DNAT in HW via the PM cmd_ram microcode).
3. **The WAN-RX one-wrap-wedge + CPU→LAN egress-wedge** — separate driver bugs that block building a
   real bidirectional conntrack-ESTABLISHED flow on mainline (needed to exercise #1 for real traffic).
4. Multi-flow scale test (many concurrent distinct 5-tuples).

## Key findings trail (this session)
post_trapdmac_submit_regime → mainline_extract_paradox → cla_second_gate → cla_gate2_packing_test →
cla_windata_packer → cla_hashhit_vs_defaultflow (root cause) → offload_fix_e2e_validation (this win).
Memory: `zte-flowoffload-framework` (full trail), `zte-roadmap`.

---
## Overnight update (2026-07-03) — productization progress + status of all fronts
- ✅ **Multi-flow HW classifier (#462):** per-slot hash placement (replaced the fill520 hack) + real flow-destroy. 2+ concurrent tc-flower flows coexist & forward selectively; delete invalidates one without touching the other. CLA hash lookup is MULTI-WAY (entry written to all 5 banks ram2-6 at the flow's hash).
- ✅ **nf_flow_table / conntrack AUTO-offload plumbing wired (#464):** added `.ndo_setup_tc=zx_eth_setup_tc` to `zx_sw_netdev_ops` (the conduit `sw` — the fatal missing wire) + `NETIF_F_HW_TC` on sw + fixed a latent oops (sw vs idm priv layout). The FT block now BINDS (was EOPNOTSUPP); the `zx_ft_*` binder fires. (Linux 6.6 has no FLOW_BLOCK_BINDER_TYPE_FT — nf_flow_table binds via CLSACT_INGRESS, already handled.)
- ⛔ **WAN-RX one-wrap wedge — root-caused + CLOSED (reboot-only HW latch):** WAN/lan4 RX→CPU halts at exactly 1024 because the RED CPU-trap queue fills its 1024 out-buffer and RED demotes further traps to sw_fwd. It's an internal HW accounting state; 4 software unwedge methods all failed → reboot-only clear. **This is a symptom of trap-everything; HW offload is the durable fix (offloaded flows don't trap → queue never fills).** A fresh boot gives a 1024-frame budget — enough to establish+offload one flow.
- **BLOCKED on hardware for live real-world validation:** only ONE host NIC is cabled (→ lan1). To prove end-to-end delivery + fire a LIVE conntrack auto-offload + test NAT, the user must **cable a 2nd host NIC to lan2 or lan3** (NOT lan4/WAN) with a real responder, OR use the WAN path within the fresh-boot 1024-frame budget. Also need a static `nft` binary in the initramfs (busybox has none) to create an offload flowtable.
- **Remaining features (not yet done):** NAT rewrite offload (PM cmd_ram microcode — under RE); the CPU→LAN egress-priming issue (non-deterministic, orthogonal).
- **All changes remain STAGED, uncommitted**, on branch phase6-hw-offload (tree linux-v6.6; its git worktree gitdir link is broken — edits are on disk).

---
## Code review of the staged diff (2026-07-03, agent af03d80b) — READ BEFORE COMMITTING
Full report: findings/offload_code_review_2026-07-03.md. NO code was changed overnight (the validated diff is preserved intact — fixes below need your reconciliation / real-NIC testing). Ranked:

- **C1 (CRITICAL, but CONTRADICTED — reconcile first):** DSA-side `zx_ffe_arm` (zx-dsa.c:682-698) still writes `ram1[0x98]` + `ram0[9]=0x00150151`, not the corrected `0x00150001`/rule-`0x90`. The reviewer argues this makes HW pick a volatile-key rule → LOOK_UP_MISS, breaking both paths (ram0[9] is a shared global reg). **BUT our multi-flow tests ran through the DSA cls_flower→zx_ffe_arm path and forwarded fine on #462/#466, and finding ab6205e5 explicitly recorded "zx_ffe_arm sets 0x00150151 but forward still works."** So either the DSA path isn't hitting zx_ffe_arm, or ram0[9]=0x00150151 is actually fine (rule 0x90 stays enabled+selected for a v4 5-tuple). ACTION: reconcile empirically (read live ram0[9] after a DSA cls_flower install + confirm forward) before changing anything; the SAFE cleanup is to make zx_ffe_arm share one source of truth with zx_ffe_table.h regardless.
- **H1 (HIGH):** zx_dsa_cls_flower_add lacks proto/family/daddr validation (the FT side has it) → IPv6/ICMP/L2 flower+redirect installs a garbage all-zero recipe. Safe additive fix: mirror the FT-side validation (decline unsupported).
- **H2 (HIGH):** DSA side uses a hardcoded fallback next-hop MAC when resolution fails (ignores zx_resolve_nh_mac); FT side correctly declines. ⚠ NOTE: our fictional-dst test method RELIES on this fallback — fixing H2 (decline on unresolved) is correct for production but means the fictional-dst rig will stop "forwarding" (expected). Test with a REAL resolvable next-hop.
- **H3 (HIGH / design):** next-hop is NOT per-flow — both binders write a fixed PM slot 5 and hardcode cmd_flow_id=0. Multiple flows to DIFFERENT next-hops overwrite each other. Same-next-hop multi-flow is fine (what we tested). Needs per-flow PM slot allocation + cmd_flow_id threading.
- **M1 (MED):** no locking on flows[]/ft_flows[] or the stateful CLA hash engine; the FT path runs in an unbound workqueue (not rtnl) → reserve/install/untrack + hash key/trigger/read can race. Add a mutex around the install/destroy critical section (mind the call contexts).
- **M2:** REPLACE with a changed 5-tuple updates raw but doesn't clear the old CLA buckets (stale HW). M3: built-in binder calls the conduit module's zx_pm_ops pointers with no RCU/module-ref → unload UAF risk. M4: tc redirect egress port is computed but not programmed into the recipe (defaults lan1) — relates to H3.
- **LOW:** entries write 15 of 17 words (stale tail); hash==0 not sanity-checked; per-flow dev_info should be dev_dbg; CLA writes lack the readback-verify the PM path has.
- **Verified SOUND:** way-slot bank math + bounds; hash-key builder bounds; packer endianness + the word3=0 / dport-hi-at-0x20 fixes; zx_eth_setup_tc idm-vs-sw priv discrimination; zx_pm_commit null-check + probe ordering; zx_flow_reserve overflow/collision + release-on-failure + del-untracked-cookie; the ram0[9]=0x00150001 change scoping.

## EXACT next steps for you (to finish real-world validation)
1. **Cable a 2nd host NIC to device lan2 or lan3** (NOT lan4 = the live WAN modem), give it its own subnet + a real responder (`nc`/iperf3). This unblocks: (a) end-to-end delivery proof (packets arrive with the rewritten next-hop MAC + TTL-1), (b) firing a LIVE conntrack auto-offload, (c) NAT-on-wire — all currently blocked because only lan1 is cabled.
2. **Add a static `nft` binary to the initramfs** (busybox has none) to create an `offload` flowtable for the auto-offload test.
3. Reconcile C1 + decide on H1/H2/H3/M1-M4 fixes (all documented above).
4. The WAN-RX one-wrap wedge is a reboot-only HW latch cured by offload — a fresh boot gives a 1024-frame budget, enough to establish+offload one flow.

---
## C1 RESOLVED (2026-07-03, build #468) — device left clean
The CRITICAL review item is FIXED + VALIDATED. zx-dsa.c zx_ffe_arm idx9[4] aligned 0x00150151→0x00150001. On #468: clapeek ram0[9] word4 = 0x00150001 BOTH before and after a DSA tc-flower install (byte-identical) → correct-by-construction, the bad 0x98-selecting value can never be live. Regression retest all pass (match forwards / 2 coexist / collision-decline / overflow-decline / no oops). Device left CLEAN + healthy on #468 (rig intact, no wedge). Remaining review items (H1 input-validation, H2 decline-on-unresolved-nh, H3 per-flow next-hop, M1 locking, M2-M4) are DOCUMENTED above — not fixed overnight (need real-NIC testing / design decisions).
Housekeeping: the linux-v6.6 tree's git worktree gitdir link is stale (.git → nonexistent linux-v6.61) — fix before committing. (Edits are safely on disk.)

## Realistic completion path with the CURRENT cabling (WAN→modem + 1 host NIC on a LAN jack)
Best real-world test = LAN client → device (route+MASQUERADE) → WAN/lan4 → modem 10.44.66.250 → internet. A working internet connection through the device WITH cla_tx_fwd climbing proves delivery+resolved-next-hop+NAT+auto-offload at once (no 2nd NIC, no modem-side capture needed). Caveats: WAN-RX 1024-frame wedge (use a FRESH boot + low-rate flow — enough to establish+offload one flow, which then HW-forwards past the wedge) + CPU→LAN egress priming. Needs a static nft in initramfs for the offload flowtable. Fallback for a clean isolated delivery capture: cable a 2nd host NIC (spare enx2c9975313ea9) to a 2nd LAN jack for LAN→LAN.
