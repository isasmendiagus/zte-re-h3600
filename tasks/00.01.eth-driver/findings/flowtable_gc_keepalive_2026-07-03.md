# nft-flowtable GC keepalive (FLOW_CLS_STATS) — IMPLEMENTED + VALIDATED: it stops the GC churn but is NOT the throughput fix (2026-07-03, build #476)

## TL;DR

Implemented the standard HW-offload stats contract: the driver's flow_block now
handles **FLOW_CLS_STATS** and reports `lastused = jiffies` (keepalive) for a
resident tracked flow, so the `nf_flow_table` GC refreshes `flow->timeout` and does
**not** age out / tear down the HW entry while it is installed.

**Result on real PATH-1 downloads (#476):** the GC destroy/re-install churn is
**suppressed** — destroys now happen only at genuine flow teardown (curl exit),
never mid-transfer, and the HW entry stays resident throughout. **But the download
is still the same ~38–52 B/s crawl (1159 bytes = HTTP headers only), DN ~14–16 %
HW-fwd, UP 0 %.** ⇒ **The GC churn was NOT the dominant throughput gate.** With the
entry now provably resident the DN bulk data still LOOK_UP_MISSes / traps for the
large majority of packets — the same P4 hit-rate gate the `pos32` finding isolated.
The fix is correct and worth keeping (it implements the mlx5/mtk_ppe stats contract
and removes a real churn source), but it does not deliver the fast download.

## The hypothesis (from pos32_ingress_fix_2026-07-03.md)

HW-forwarded packets bypass the CPU, so the `nf_flow_table` core sees no activity →
GC ages the flow out (`FLOW_CLS_DESTROY`) → re-installs on the next trapped packet
(`FLOW_CLS_REPLACE`). #474 measured 80 installs / 44 destroys / 22 dels in one short
download ⇒ the entry was resident only ~17 % of the time → ~17 % hit. Standard fix:
handle `FLOW_CLS_STATS` and report the flow's activity (lastused) so the core
refreshes the timeout and does not GC it.

**Confirmed the driver did NOT handle FLOW_CLS_STATS before this change**
(`zx_ft_setup_cb` had only REPLACE/DESTROY; the DSA `zx_dsa_cls_flower_stats` was a
`return -EOPNOTSUPP` stub). The core path that consumes it (verified in-tree,
6.6): `nf_flow_table_core.c:nf_flow_offload_gc_step` → for a live HW flow calls
`nf_flow_offload_stats` → `flow_offload_work_stats`:
`flow->timeout = max(flow->timeout, lastused + flow_offload_get_timeout(flow))`.
With no STATS report `lastused` stays 0, the timeout is never pushed, the flow
expires → teardown. The STATS cls `cookie = (unsigned long)&flow->tuplehash[dir].tuple`
is stable across REPLACE/DESTROY/STATS per direction, so a cookie lookup in
`ft_flows[]` works.

## The code change (build #476, NOT committed)

- **`drivers/net/ethernet/zte/zx-eth-main.c` (FT / conduit = the tested path):**
  new `zx_ft_flower_stats(e, cls)` — looks up `cls->cookie` in `ft_flows[]`; if a
  used entry matches, calls
  `flow_stats_update(&cls->stats, 0, 0, 0, jiffies, FLOW_ACTION_HW_STATS_DELAYED)`
  (lastused = now keepalive; pkts/bytes = 0) and returns 0; otherwise returns
  `-EOPNOTSUPP` (never refresh a flow we don't own). Wired a `FLOW_CLS_STATS` case
  into `zx_ft_setup_cb`.
- **`drivers/net/dsa/zte/zx-dsa.c` (built-in, mirror):** `zx_dsa_cls_flower_stats`
  changed from the `-EOPNOTSUPP` stub to the same keepalive over `priv->flows[]`.
  (The DSA tc-flower path is the manual test path — its filters persist until
  userspace deletes them, so it is not GC-churned like the FT path; the mirror is
  for consistency / `tc -s filter`.)

**Per-flow HW counter investigation:** the CLA exposes **no** per-flow / per-bucket
HW hit counter indexable by `pm_slot` — only the global `cla_tx_fwd` (0x9238c3c0) /
`cla_tx_trp` (0x9238c3c4) and the QMG DN/UP fwd/trap counters, plus a per-entry
age bit (ram2 byte0x10 bit6, per the inport finding). So pkts/bytes are reported 0
and the keepalive is unconditional for a resident tracked flow. **Caveat (as
designed):** a pure keepalive means the flow will not age on idle while our entry is
installed — it relies on conntrack teardown (which fires `FLOW_CLS_DESTROY`, seen
cleanly at curl-exit below) and the 32-entry cap. Acceptable for validating
throughput. `FLOW_ACTION_HW_STATS_DELAYED` matches the GC-poll cadence (mtk_ppe
pattern); `flow_offload_work_stats` does not validate `used_hw_stats`.

Both compile clean (only pre-existing unused-function warnings). Built #476
(soft-float `arm-linux-gnueabi-`; two vmlinux links from the built-in + module
two-phase build → banner `#476`), DTR-booted, driver init healthy.

## On-device validation (PATH-1 real internet, #476)

Rig: device `lan2=172.31.9.1/24` (host client), `lan4=10.44.66.223/24` → modem
`10.44.66.250` (`cc:29:bd:22:b4:2b`), MASQUERADE out lan4, FORWARD lan2↔lan4,
`ip_forward=1`. Host `enxc8a362e95900` in netns `client` = `172.31.9.50/24` via
`172.31.9.1` (anti-leak: `ip route get 80.249.99.148 = via 172.31.9.1`). nft offload
flowtable `{lan2,lan4} flags offload; ct state established flow add`. Target
`http://80.249.99.148/1GB.zip` (Host: ipv4.download.thinkbroadband.com).
Device→8.8.8.8 and client→8.8.8.8 (SW NAT) both 0 % loss on the fresh boot.
**Gotcha this boot:** rc.router puts the client subnet + FORWARD rules on **lan1**,
but the host physically ingresses on **lan2** (verified: `lan2` rx_packets climbs
under host traffic, lan1 flat) — moved `172.31.9.1` to lan2, added lan2↔lan4
FORWARD; and **lan2 boots admin-down** (`ip link ... <BROADCAST,MULTICAST>`, qdisc
noop) → `ip link set lan2 up` (else client ARP FAILED).

Three real downloads (fresh boot, no pre-baseline SW download):

| run | throughput | bytes | recipe installs | destroys / dels | DN Δhw_fwd / Δsw_fwd / Δhw_trap |
|---|---|---|---|---|---|
| 1 | **38 B/s** | 1159 | 28 | 4 / 2 (at exit only) | +12 / +33 / +42 |
| 2 | **41 B/s** | 1159 | 28 | ~2 / 2 (at exit only) | +12 / +31 / +33 |
| 3 (port-pinned) | **52 B/s** | 1159 | 28 | ~4 / 2 (at exit only) | +12 / +24 / +36 |

- **Churn stopped.** Compare #474: 80 installs / **44 destroys / 22 dels** *during*
  the session. #476: the only `flower destroy` / `flow del` lines appear at
  ~T+curl-exit (e.g. `flow del cookie=… cleared raw=0x… rc=0` right after the 22–30 s
  window), **never interleaved between the REPLACE lines during the transfer** —
  i.e. the GC teardown-while-active is gone and the HW entry stays resident.
- **Throughput unchanged** — still stalled at 1159 bytes = HTTP response headers
  only, ~38–52 B/s (identical to the pre-fix ~38 B/s; net-negative vs the ~53 KB/s
  pure-SW baseline). DN ~14–16 % HW-fwd; UP 0 % (every UP packet traps). CLA
  fwd[0x1cc3c0] climbs 1:1 with DN hw_fwd only.
- **No wedge.** DN hw_trap rose gently across all three runs to 369, far below the
  1024 P3 ceiling; device `ping 10.44.66.250` stayed 0 % loss throughout. (The
  keepalive removing the destroy churn may itself reduce trap pressure vs #474,
  which pinned 1024.)

### Residual observations
- **The 28 REPLACEs/run persist WITHOUT interleaved destroys** — this is a *benign*
  refresh, not the old churn: trapped DN packets re-enter the SW flow-offload hook
  (`nf_flow_offload_ip_hook`) for the already-offloaded flow → `NF_FLOW_HW_REFRESH`
  → GC re-issues `FLOW_CLS_REPLACE`, which re-writes the *same* entry (rc=0, resident
  throughout). So the re-REPLACE is a *symptom* of the DN packets trapping, not a
  cause of absence. It would disappear once DN actually HW-forwards.
- **New datum — a driver LOOPBACK-drop of DN bulk data:** ~1 line/run
  `LOOPBACK drop #1 src=f4:f6:47:0f:42:64 dst=c8:a3:62:e9:59:00 ethertype=0800
  len=1506 ingress=4` — a full-MTU IPv4 DN data frame ingressing WAN (port 4) with
  the device's *own* switch MAC as source is dropped by a driver loopback guard.
  Only 1/run, so not the dominant gate, but worth a look: why does a bulk DN packet
  carry the device switch MAC as src, and can the loopback guard mis-drop legitimate
  DN data?
- **desOut trap reason inconclusive this run:** `poke 0x9238c39c = 0x96000000` for
  the DN flow installed at slot **0x96** (raw 0xdd96) — the high byte equals the
  slot, so this register appears to latch the last-processed slot rather than cleanly
  expose the documented `[29:23]` reason field; I did not force a decode. Prior
  findings established desOut = **0x54 LOOK_UP_MISS** via the stock gparsehashkey
  tooling for exactly this resident-entry-DN-trap scenario.

## Verdict

The GC-churn hypothesis is **confirmed as a real effect and now fixed** (the entry
stays resident), but it is **confirmed NOT to be the throughput gate**: with the
entry resident the DN bulk data still misses/traps ~85 % and the download still
crawls. This lands on the pos32 finding's fallback branch exactly ("entry stays
resident but still ~17 % miss → that's important"). The remaining, dominant gate is
the **DN LOOK_UP_MISS with a byte-exact entry at the provably-correct resident
slot** (the P4 hit-rate / #452 engine-compare saga), unchanged by both the pos32 and
the keepalive fixes.

**Keep the change** — it correctly implements the HW-offload stats contract, is
harmless, and removes a genuine churn source (which will matter once the hit-rate
gate is solved). It is simply orthogonal to the throughput crawl.

## Next leads (the real P4 gate)
1. **A/B tc-flower (DSA, LAN-ingress, reportedly ~100 %) vs the FT path (~15 %)** for
   the SAME 5-tuple on #476 — if DSA hits and FT misses with both entries resident,
   the gate is FT-entry-write-specific; if both miss, it is the engine-level
   LOOK_UP_MISS.
2. The engine-level bucket-compare LOOK_UP_MISS with a resident entry (the
   #452/#456 saga) — read desOut cleanly with proper gparsehashkey tooling for a DN
   packet at the confirmed-resident slot.
3. Investigate the DN LOOPBACK-drop guard (does it ever eat legitimate bulk DN data?).

## Left clean
Host: netns `client` torn down, `enxc8a362e95900` back in root ns @192.168.1.50,
`192.168.1.0/24` TFTP route restored (not stranded), in.tftpd healthy. Device
DTR-rebooted to pristine **#476** (RAM test config wiped: no nft, no MASQUERADE, no
modem route, lan2/lan4 back to rc.router defaults; the fix is baked into the #476
uimg so it survives the re-TFTP). Driver source edited (zx-eth-main.c + zx-dsa.c);
**NOT committed**.
