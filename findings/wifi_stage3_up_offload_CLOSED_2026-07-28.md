# WiFi Stage-3 UP offload (WiFi client → WAN upload): fabric key/verdict/csum fixes VALIDATED on HW — hit-rate 99.9%+, 3-4x SW throughput; NEW sustained-load fabric wedge OPEN (2026-07-28)

Status: **UP mechanism CLOSED — the CLA lookup-miss chain is fully fixed and
HW-validated end-to-end via the production nft path.** One NEW, separate issue
found and characterized (not root-caused): sustained fabric-ingress HW
forwarding wedges the fabric after a variable volume (~20k-72k frames);
reboot-only recovery. `ftwifi` stays default OFF. Builds #539-#542 (final =
#542), same rig as `wifi_stage3_up_cla_keymiss_forensics_2026-07-28.md`.

## Verdict on the proposed 3-part fix (forensics doc)

Verified adversarially against source + decomp + live HW before implementing:

| Part | Proposed | Verdict |
|---|---|---|
| 1. ram0[6]/[7] `index_valid = 0x00150001` | boot init, mirrors ram0[9] | **CORRECT** (live-confirmed at boot via clapeek; group 7 value was already live-tested in forensics) |
| 2. `zx_ft_build_key` kb[3] = 0x38 (idm1) / 0x30 (idm0) | | **CORRECT** (`ex_rule_id = word0 >> 23`; 24/24 live captures byte-exact vs model) |
| 3. `zx_ft_pack_cla` extr_index 0x70/0x60 (byte0x10 nibble 7/6) | keep valid_en+direct | **CORRECT on the nibble, WRONG on `direct`** — see below |

**Two gaps the proposal didn't cover** (both implemented):
- *No gating mechanism*: the claim "the ingress ring is known from the
  wifi_bind node the install path already consults" was false — the install
  path resolves only the EGRESS dev. Fixed by matching the nf_flow_table
  rule's `FLOW_DISSECTOR_KEY_META ingress_ifindex` (always emitted by
  nf_flow_table_offload.c) against a bind-time-cached `wlan_ifindex` in the
  dispatch node (integer compare, no pointer deref).
- *Hash-consistency plumbing*: reserve-time collision hashes, uninstall/
  untrack and the DESTROY path all key off `raw` — a `key_hdr` parameter now
  threads through build_key/flow_hash/flow_hash_poly0/pack_cla/install_recipe
  and the fttest white-box hook (optional 7th arg, hex key_hdr).

## TWO additional root causes found on HW (the fix as proposed still missed 100%)

With parts 1-3 implemented exactly as proposed, the live fabric key was
byte-exact == the installed key (24/24 latch captures) and fill520 put a
matching entry in ALL 520 buckets — **still 100% LOOK_UP_MISS**. Two more
defects were pinned live:

### A. `direct=1` breaks the fabric-ingress key-compare (entry word4)
fill520 sweeps with single-field variants:
- `0x061?0067` (direct=1, da_known=0): MISS
- `0x061?0047` (direct=0, da_known=0): **MATCH** (acl_fail stops) but frames
  black-hole (no forward action)
- `0x061?0047 | da_known` (= `0x06100047`, direct=0, da_known=1): **MATCH +
  CLA forward verdict fires** (cla_up_fwd == injections)

⇒ fabric-ingress entries must pack **`direct` CLEAR, `da_known` SET**
(`cla[4] = proto<<24 | 0x0010004n`). eth entries keep `direct=1` (0x69) —
required by the WAN-ingress compare and the proven eth-UP recipe.

### B. PM TTL-edit leaves a stale IP checksum on nat=fwd flows (flow_info bit4)
With A fixed, HW-forwarded frames reached the host WIRE with correct DMAC
(da_known → next-hop rewrite ran), correct tuple, ttl 63 — and
**`bad cksum` off by exactly 0x100** (the TTL decrement, never folded) → the
receiving kernel silently dropped every frame. Same defect class as Phase-C
R1 (there it was repaired in SW at the CPU dispatch; UP egresses the wire
directly, so it must be fixed HW-side). Fix: `zx_ft_build_flow_info` now sets
`ip_chk_en` (bit4, stock's choice) whenever `hl_ttl_en` is set, not only for
NAT flows. (SMAC stays the client MAC — cosmetic, receivers don't check.)

## The complete landed fix (all in zx-eth-main.c + zx_ffe_table.h)

1. `zx_ffe_index` groups 6/7: `index_valid 0x00150055 → 0x00150001`.
2. `ZX_FT_KEY_HDR_ETH 0x48` / `ZX_FT_KEY_HDR_IDM(idm) = 0x30|idm<<3`;
   `key_hdr` threaded through the whole key/hash/pack/install chain.
3. `zx_ft_wifi_ing_hdr()`: META ingress_ifindex → bound-vif key_hdr
   (ftwifi-gated; eth flows and ftwifi=0 byte-identical to pre-fix).
4. `zx_ft_pack_cla`: extr nibble = `key_hdr>>3`; fabric entries pack
   `0x0010004n` (direct CLEAR + da_known), eth keeps `0x0?10006?`/0x49.
5. `zx_ft_build_flow_info`: `ip_chk_en` unconditional (with hl_ttl_en).
6. NO poly-0 write for fabric UP entries (see below); `has_raw0` stays
   DN-only everywhere.
7. fttest `install` gained an optional key_hdr argument (white-box testing).

## Open item RESOLVED: fabric probes the poly-1 way set

Zeroing the poly-0 ram2 slot mid-run under active HW forwarding changed
nothing (1.69 → 1.68 MB/s, acl_fail 0) ⇒ **fabric-ingress lookups probe the
poly-1 5-way set, exactly like GePHY LAN ingress**; only WAN/RGMII ingress
consults the poly-0 slot. The extra poly-0 write was removed from the driver.

## A/B numbers (production nft path, phone → host-WAN-subnet TCP push)

| Run (build #542, clean boot) | ftwifi | MB/s | hit-rate | notes |
|---|---|---|---|---|
| FINAL_A_sw | 0 | 0.46 | 0% (7842 miss / 8001 inj) | slow path (inject→trap→dispatch→SW) |
| FINAL_B_hw | 1 | **1.44 (3.1x)** | **99.94%** (9 miss / 15468 inj) | qmg_dn_hw +21986 (both dirs on HW) |
| long run (#541) | 1 | **2.2-2.3 sustained ~50 s, 69.9 MB** | ~100% (acl_fail flat) | 71825 frames HW-forwarded, then the wedge (below) |

DN sanity (final binary, clean boot, ftwifi=1): phone HTTP download
**9.62 MB/s, dn_hw +110,566, traps +6, acl_fail +2** — DN not regressed
(≥ Phase-C's 7.93 MB/s; ip_chk_en is redundant-but-harmless there since the
CPU dispatch already repairs csums).

## ⚠ NEW OPEN ISSUE: sustained fabric-ingress forwarding wedges the fabric

After a variable volume of HW-forwarded fabric-INGRESS frames (observed
onsets: ~19.6k, ~22k, ~71.8k frames / 25-70 MB across three boots),
throughput drops to zero and the fabric is left in a corrupt state:

- HW-forward counter freezes; subsequent lookups MISS (acl_fail 1:1).
- Trapped fabric frames stop dispatching: noparse/nobind (corrupt trap
  descriptors); the gparsehashkey latch reads degenerate repeating patterns
  (`45000000 00000001 ...` — raw IP bytes where the key header should be).
- Even the pure SW path (ftwifi=0) is dead afterwards; ICMP still works
  (ICMP rides the stack, never the fabric — the rx_handler injects TCP data
  only).
- `idm1` down/up does NOT recover; only reboot does.
- At one wedge onset the 0x921cc008 FIFO gauge stepped 0x111011→0x222211
  (pre-run 0xddd011) — lead, not conclusion.
- DN direction (fabric EGRESS) moved 110k frames without wedging ⇒ the leak/
  corruption is specific to fabric-ingress forwarding. Smells like the RED
  bit6 charge-accounting family (a buffer charged at fabric-ingress admission
  that the WAN-egress never refunds), but that RE is a separate session.

**Consequence**: `ftwifi` stays default OFF; UP offload is mechanism-complete
but not endurance-safe. Root-causing the wedge is the single blocker to
flipping it on.

## Regress guard

`scratchpad/regress.py wifi_up_fabric_key` (white-box fttest+clapeek, no
AP/client needed): boot ram0[6]/[7]/[9] values; fabric-keyed install packs
extr-7 + da_known + no-direct + no poly-0; eth packing byte-identical
(0x06100069); destroys clear way0. `_fttest_install` updated for the new
`key_hdr=` field in the fttest log line.

## Tools added (scratchpad/)
- `upab.py` — UP-direction A/B (host WAN sink measures received B/s; phone
  nc push; paced counter snapshots).
- `uphold.py` — hold a retransmit flow for CLA probing (start/probe/stop).
- `uptest.py` — one-shot discrimination runs (fill520/slot variants with
  w3/w4 field overrides; found root-cause A).

## Method notes / gotchas (for reuse)
- fill520 commits reliably (clapeek-verified) and is THE tool for
  "address vs compare" splits: all-bucket coverage kills every hashing
  hypothesis in one run.
- The entry INPORT field (cla[3], bytes 0x0d/0x0e) was tested (values 7 and
  others) — NOT part of the fabric compare failure; irrelevant here.
- Phone toybox has no wget/curl; use the Phase-C `echo GET | toybox nc` idiom.
- Post-wedge, do NOT trust latch captures or trap-parse stats — everything
  fabric-side is corrupt; discriminate rig-vs-device with ICMP (stack path).

## Device end state (left SAFE)
Build #542 RAM-booted; ftwifi=0; idm1 DOWN; AP + udhcpd running, client
associated; nft flowtable rig loaded (inert with ftwifi=0 for DN, UP installs
eth-keyed = harmless-miss); fabric healthy (last boot saw only the DN sanity
run, no wedge); host: return-route present, no DROP rules left, http.server
on :8080 was pre-existing and left running.
