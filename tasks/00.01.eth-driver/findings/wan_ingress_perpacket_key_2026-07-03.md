# WAN-ingress per-packet DN key — the DECISIVE A-vs-B test (2026-07-03, build #476)

## VERDICT: **(B) ENGINE-LEVEL MISS with an IDENTICAL key + correct resident entry.**
**NOT per-packet key variance.**

The live WAN-ingress DN data-packet key is **byte-identical across 400 samples**, it
**hashes to exactly the slot where the driver installed the entry**, the entry is
**resident + valid throughout** — and yet **~86 % of WAN-ingress DN packets still
LOOK_UP_MISS**. So the residual miss is an *engine-level, WAN-ingress-specific lookup
non-determinism*, not a key problem and not a slot mismatch. The pos32/slot fixes
(#474/#476) were necessary and are correct; they are simply not sufficient.

---

## Rig (PATH 1, real internet via the modem) — all set up this session, empirically
- Device mainline **#476**, was already booted+clean (rc.router defaults). No reboot needed.
- **Cabling determined empirically** (per-port `rx_packets` under a host ping burst):
  host `enxc8a362e95900` ↔ device **lan2** (smac2; lan2 forwards via PHY_POLL, carrier blank);
  modem ↔ device **lan4** (WAN/RGMII/smac4, gw 10.44.66.250 reachable, 8.8.8.8 0 % loss).
- Device: `lan2=172.31.9.1/24`, `lan4=10.44.66.223/24`, `default via 10.44.66.250`,
  `iptables -t nat -A POSTROUTING -o lan4 MASQUERADE`, FORWARD accept lan2↔lan4, ip_forward=1.
- Host anti-leak: netns **client** (moved `enxc8a362e95900` in; `172.31.9.50/24`,
  default via 172.31.9.1). `ip route get <pub>` → via 172.31.9.1 (no wifi leak). SW path
  end-to-end verified (ping device+internet through the box).
- Offload: `table inet ft { flowtable f { hook ingress priority 0; devices={lan2,lan4};
  flags offload; } chain ftfwd { hook forward; ct state established flow add @f; } }`.
- Target `http://80.249.99.148/1GB.zip` + `Host: ipv4.download.thinkbroadband.com`, curl
  pinned `--local-port 40000` so the DN 5-tuple/slot is deterministic across runs.
- Reads via debugfs `mem` (fast, printk-independent): `busybox dd if=.../zx_eth/mem bs=4
  skip=471192 count=100 | busybox od -An -tx4 -v` (skip 471192 = (0x9238c260-0x921c0000)/4).
  Word map in that span: **gparsehashkey = words[0:12]**, CFW(0x9238c3c0)=word88,
  CTRP(0x9238c3c4)=word89, desIn2(0x9238c3e8)=word98.

## The flow (from the driver recipe log, deterministic with pinned port 40000)
- **DN entry** (download, server→client, WAN-ingress): `80.249.99.148:80 -> 10.44.66.223:40000`,
  eg_rp=3, **wan_ing=1** (pos32 fix applied), nh=host MAC, pm_slot=9, **raw=0x9609**,
  buckets ram2[0x09]/3[0x109]/4[0x189]/5[0x1c9]/6[0x201], rc=0.
- **UP entry**: `172.31.9.50:46304/40000 -> 80.249.99.148:80`, eg_rp=5, wan_ing=0, raw=0xa089.

## Step 1 — during a live download the DN gate reproduces hard
`pipeline_stats` mid-download (three independent runs, consistent):
- smac4 (WAN) RX ≈ 624 / 689 / 922 packets — DN data floods in fine.
- **QMG DN hw_fwd ≈ 63 / 78 / 127  vs  hw_trap ≈ 624 / 689 / 922**  ⇒ **~10–14 % hit, ~86–90 % miss.**
- `CLA fwd[0x1cc3c0]` == hw_fwd, `CLA drop[0x1cc3c8]=0` ⇒ the miss is at the **CLA lookup
  stage** (not a downstream drop): the CLA only issues a forward verdict for ~1/7 of DN pkts.
- UP: hw_fwd=0, all sw/hw_trap (UP offload separate story; not this gate).

## Step 2 — PER-PACKET KEY CAPTURE (the crux) → the key is CONSTANT
`gparsehashkey` (0x9238c260, 12 w) latches the last packet's HW-parsed key.

- **Naive sampling during the download caught the UP key 100 % (≈600 samples), never a DN key.**
  Reason (important gotcha, not a bug): the local netns client ACKs every DN segment within
  <1 ms, so at any coarse (~50 ms) sample the *UP ACK* is always the most-recent packet and
  overwrites the DN latch. gparsehashkey coarse-sampling **structurally cannot** catch DN while
  a fast local client ACKs. (This likely explains the historical "24/24 DN pos32=1" captures —
  those match the driver's install-time write to the hash-engine input 0x9238c2c4, see below.)
- **Fix: kill the client mid-transfer** → the server retransmits the unacked DN segment with
  **no ACK following** → gparsehashkey then latches the real WAN-ingress DN data key.
- **Result — 400/400 samples byte-identical:**
  `gparsehashkey = 48000000 a1f2000d 1458c728 00a085be 00013880 0 0 0 0 0 0 0`
  (word1 low byte `0d` ⇒ pos32=1, the WAN-ingress class bit; word4 `00013880` = dport 40000<<1).
  **DISTINCT KEYS = 1. Zero per-packet variance.** (The one known variance — TCP FIN/SYN/RST
  flag corruption — does not apply to bulk PSH/ACK data; refuted for the data plane.)

### Where the DN key does/doesn't appear (register semantics clarified)
- **0x9238c260 gparsehashkey** = live per-packet parse latch (dominated by UP under load).
- **0x9238c2c4** (CLA hash-engine key INPUT) held `a1f2000d …` = the driver's *install-time*
  key write (static leftover), NOT a per-packet latch. Wide dump 0x9238c200–0x9238c47c found
  the DN signature only there. There is **no separate "DN parse-key" register** in that block.

## Step 3 — hashcalc(live DN key) == installed slot  → same key, same slot
`echo '48000000 a1f2000d 1458c728 00a085be 00013880 0 0 0 0 0 0 0' > hashcalc`
→ **raw hash 0x9609** == the installed DN entry **raw 0x9609** (ram2[0x09]).
The live WAN-ingress DN data packet probes **exactly** the bucket the driver wrote.

## Step 4 — the entry is resident + VALID the whole time (rules out eviction/invalidation)
`clapeek 2 9` **during** an active download:
`03005044 fa11c009 00000608 00000000 06000049 9450f900 df0a2c63 40005042 0000009c`
= a correctly-formed DN entry (proto 6; server 80.249.99.148 in w5; client 10.44.66.223 in w6;
ports in w7/w8). Non-zero, matchable — and **127 packets did hit it**, proving valid_en is
effective. So the entry is genuinely resident + valid across the whole window (keepalive #476
works; no GC churn, no eviction).

## The airtight B chain
1. entry resident + valid (clapeek during traffic, and 127 real hits) ✔
2. live DN key byte-identical across 400 samples (zero variance) ✔
3. hashcalc(live DN key)=0x9609 == installed raw 0x9609 (same slot) ✔
4. yet ~86 % of these identical-key DN packets MISS at the CLA lookup ✔
⇒ **B: engine-level lookup non-determinism specific to WAN-ingress.** A (key variance) and the
slot-mismatch story are both refuted for the data plane.

## What this rules OUT (so the next agent doesn't re-chase)
- per-packet key variance / a second varying bit beyond pos32 — **NO** (400/400 identical).
- pos32 / slot mismatch — **NO** (key hashes to the installed slot).
- GC churn / eviction / invalid entry — **NO** (resident + valid during traffic; keepalive OK).
- external-SRAM hash regime (0xF1020000) — previously ruled out for the internal key
  (`cla_second_gate_2026-07-02.md`; outspace_cfg 0x9238c094=0x4 space_sel0/hash_num1,
  cla_config 0x9238c080=0x600). Not re-opened by this data.

## The specific NEXT LEAD (engine/regime, WAN-ingress-only)
The gate is: *same key, same slot, resident valid entry, LAN-ingress hits 100 % (prior proof),
WAN-ingress hits only ~10–14 %*. The differentiator is purely the **WAN/RGMII ingress lookup
path** vs the LAN/GePHY path. Hit rate is stable ~10–14 % (not 0, not 100) ⇒ a *partial /
non-deterministic* lookup, not a wholesale wrong-bank. Candidate mechanisms to chase, in order:
1. **Multi-way / bank-probe mismatch.** Driver writes 5 ways (ram2[0x09]…ram6[0x201]) for raw
   0x9609. Determine which (bank,slot) ways the *WAN-ingress* lookup actually probes vs the
   LAN-ingress lookup — if WAN probes a subset/rotates, that yields a partial hit rate. Read
   `ACL_OUT_SPACE_SEL/ACL_OUT_HASH_NUM` per-ingress (cla_get_outspace_cfg) and check whether the
   way-mask/hash_num differs by ingress class.
2. **Clean A/B (task 4a, not yet done identically):** install the *same* DN 5-tuple entry and
   drive it from LAN-ingress (DSA tc-flower on lan2) vs WAN-ingress; compare hit rate with the
   identical entry to isolate the pipeline as the sole variable.
3. **WAN DN ring-1 pipeline race.** WAN-ingress DN uses the ring-1 / DN NAPI path (the #of DN
   mirror fixed for RX). A race between the ring-1 ingress classify and the CLA lookup could let
   ~1/7 through. Correlate the 127 hits vs re-install timing.
4. **Per-entry aging not enabled in mainline:** ram_id 8 hit-bit at slot 0x09 read **0x0 across
   8 samples during 922 DN packets / 127 hits** ⇒ mainline likely never sets age_en/age_mode, so
   the aging table is not a usable per-hit signal until enabled (stock sets it; see
   `stock_ffe_aging_perflow_stats_RE`). Enable it if per-flow hit sampling is wanted later.

Minor anomaly (does not affect verdict): the descriptor **reason field** on #476 read 0x2c/0x11
from 0x9238c3e8 bits[29:23], not the DATASHEET's 0x54/0x49/0x3f — the desIn2 reason decode in
DATASHEET.md:888 may be stale for this build; use the CLA fwd/trap counters (0x1cc3c0/…) as the
authoritative hit/miss signal instead.

## Left clean
nft flowtable flushed; iptables MASQUERADE + FORWARD lan2↔lan4 removed; lan2 172.31.9.1 removed;
lan4 restored to 192.168.9.1/24; default route via modem removed; netns `client` torn down and
`enxc8a362e95900` returned to root ns @192.168.1.50 with the `192.168.1.0/24` route restored
(TFTP-ready). Device left on a fresh #476 boot, no wedge. Driver source UNCHANGED, nothing committed.
