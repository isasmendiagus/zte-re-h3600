# WiFi UP CLA lookup-miss ROOT-CAUSED: fabric ingress extracts under ram0-group-7's VOLATILE rule 0x76, not the 5-tuple rule the installer keys for (2026-07-28)

Status: **root cause localized with live byte-exact evidence; concrete fix proposed;
NOT implemented/validated (per task scope).** Same device state as
`findings/wifi_stage3_up_offload_groundwork_2026-07-28.md` (build #538, still up
from that session — no reboot needed this pass).

## ★★★ HEADLINE

The UP hardfast entry misses 100% for fabric-ingress (idm/WLAN) frames because
the HW extracts their hash key under **ex_rule_id 0x76** — the per-inport
group-7 raw-window rule whose 17 words are **byte-identical to rule 0x96**, the
already-known "VOLATILE per-packet key" rule — while the installer builds, hashes
and tags the entry for **rule 0x90** (v4-5tuple). The 0x76 key includes IP
total-length, IP-ID, IP-checksum and TCP-seq, which change on every packet, so
**no static entry can EVER hit** (this is not a one-bit context mismatch; the key
layout itself is per-packet volatile). This is the exact same failure mode as the
wired 2026-07-02 mis-rule bug (0x96 picked over 0x90), which was fixed by
restricting ram0[**9**] index_valid — but that fix was applied ONLY to group 9;
the per-inport fabric group **7** (and 6) still carries the stock power-on value.

With group 7 temporarily forced to its clean rule (**0x70**, byte-identical to
0x90), the fabric-ingress extracted key becomes byte-stable and **matches
`zx_ft_build_key(..., is_wan=false)` EXACTLY except word0** (`0x38000000` = rule
0x70 header vs the driver's `0x48000000` = rule 0x90 header) — i.e. after the
rule-select fix, the residual installer change is exactly one header byte
(kb[3]) plus the entry's extr_index field.

## Evidence chain (all live, #538, this session)

### 0. Anti-chimera capture primitive (new, reusable)
`scratchpad/upkey.py`. One 48-byte read of debugfs `zx_eth/mem` at offset
0x1cc260 (`dd bs=48 skip=39266 count=1`) = a single `memcpy_fromio` in
`zx_mem_read` → an ATOMIC 12-word gparsehashkey snapshot (the 2026-07-28
per-word chimera is structurally impossible). Traffic isolation = the
**UP-direction mirror of the 2026-07-03 kill-client-retransmit trick**: phone
`toybox nc` to host `10.44.66.133:9099` (host wlo1, WAN subnet), handshake +
first segment ACK normally (SW path — the rx_handler's TCP-data-only filter
keeps control frames off the fabric), then `iptables -A INPUT -p tcp --dport
9099 -j DROP` on the host → every later data segment gets no ACK → TCP
retransmits the same data frame for minutes → with idm1 up each retransmit is a
fabric-ingress injection (tx_injected climbed 129707→129741 across the runs)
and the ONLY repeating CLA-parsed packet carrying our tuple.

### 1. Fabric-ingress frames select rule 0x76 (live, repeatable)
29 latch samples across two live captures (plus the stale latch from the
previous session's upload, still resident at session start) ALL show word0 =
`0x3b000000` → **ex_rule_id = 0x76**, inport-in-header = 0. Decoded under the
raw-window model, the live-flow samples (conn 192.168.50.10:36342→10.44.66.133:9099)
read:

| field | sample A | sample B | sample C | meaning |
|---|---|---|---|---|
| smac | ba:00:b1:26:83:24 | same | same | phone MAC (bit1 of byte1 masked by the rule's winmask; real MAC ba:02:...) |
| ethertype/ver | 0800 / 4500 | same | same | fixed |
| **ip_len** | **00b4** | **01d3** | **0134** | **VOLATILE** |
| **ip_id** | **e255** | **e253** | **e254** | **VOLATILE** |
| frag/ttl_proto | 4000 / 4006 | same | same | fixed |
| **ip_csum** | **188b** | **176e** | **180c** | **VOLATILE** |
| sip/dip | c0a8320a / 0a2c4285 | same | same | 192.168.50.10 / 10.44.66.133 ✓ |
| sport/dport | 8df6 / 238b | same | same | 36342 / 9099 ✓ |
| tcp_seq_hi | 3fb4 | 3fb4 | 3fb4 | volatile per flow |

⇒ the hash input differs packet-to-packet within one flow. 100% LOOK_UP_MISS is
the only possible outcome, independent of anything the installer writes.

### 2. Why 0x76: ram0 group 7 still has the stock index_valid
Live clapeek (== `zx_ffe_table.h`, the verified stock byte-exact boot table):
- `ram0[7] = 73727170 77767574 7b7a7978 7f7e7d7c 00150055` → index_valid lo16
  0x0055 enables rule slots {0,2,4,6} = {0x70,0x72,0x74,0x76}; the HW picks the
  HIGHEST enabled = **0x76** (same selection behavior as the 2026-07-02 finding).
- `ram0[9] = ... 00150001` → the wired fix (only 0x90) — group 9 only.
- `ram1[0x76]` live == table == **byte-identical to ram1[0x96]** (the volatile
  rule); `ram1[0x70]` == **byte-identical to ram1[0x90]** (clean L3-relative
  v4-5tuple). Same identities hold for group 6: 0x66==0x96, 0x60==0x90.

Group mapping: stock `tm_acl_l2_fast_init` writes rules `(p<<4)+n` per PORT
p=1..8 — group 7 = fabric port 7 = **idm1** (exactly the ring our vif is bound
to, ssid4), group 6 = idm0. Wired v4 traffic demonstrably uses group 9 instead
(all prior wired captures: rules 0x90/0x96) — whatever steers eth ingress into
the v4-fast group 9 does NOT apply to fabric ingress, which lands in its
per-inport group.

### 3. Forced-clean-rule A/B: the key model is otherwise EXACT
Diagnostic force (restored after): `clawrite 0 7 73727170 77767574 7b7a7978
7f7e7d7c 00150001` (write twice — first-write-doesn't-commit quirk; clapeek
verified). Fresh capture (new conn, sport 41752): **24/24 samples byte-stable**:
```
HW (rule 0x70 forced): 38000000 8150000c 14586415 4630850a 00004717 0...
zx_ft_build_key(wan=0): 48000000 8150000c 14586415 4630850a 00004717 0...
```
- Words 1-11 IDENTICAL (proto 6, 192.168.50.10:41752→10.44.66.133:9099,
  straight tuple order — the groundwork session's "reversed-tuple" chimera
  hypothesis is REFUTED, it was a mixed-packet artifact).
- **pos32 = 0** for fabric ingress (no WAN-style ingress-domain bit; LAN-like).
- word0: HW bakes the SELECTED rule id into the hashed header — 0x70 vs 0x90.
- HW hashcalc: rule-0x70 key → raw **0x8de8**; the installer's 0x90-form →
  raw **0x0da4**. Disjoint buckets — and even at the right bucket the entry's
  extr_index (0x90) would fail the rule-id compare (per the 2026-06-28 finding,
  extr_index must equal the packet's ex_rule_id).

### 4. Ruled out (this session + carried)
- Reversed tuple in the fabric key — NO (chimera artifact; straight order).
- pos32/ingress-domain context bit — NO (fabric = 0, same as GePHY).
- inport leaking into the key header — NO (word0 inport bits = 0 in all samples).
- da_known/FDB (carried from groundwork) — not the gate.
- Key-field packing beyond word0 — byte-exact match once the rule is clean.

## THE PROPOSED FIX (not implemented — next session)

Mirror of the proven 2026-07-02 group-9 fix, applied to the fabric groups, plus
the one-byte installer change:

1. **Boot init** (where `zx_ffe_table.h` is applied): write ram0[**6**] and
   ram0[**7**] word4 = `0x00150001` (restrict fabric ingress to the clean
   5-tuple rule 0x60/0x70). Same shape as the existing ram0[9] entry; loses v6
   (0x72) / v4-3tuple (0x74) fast-classify for fabric ingress — same tradeoff
   already accepted on the wired path since 2026-07-02.
2. **`zx_ft_build_key`**: for flows whose INGRESS is a bound WiFi vif, set
   `kb[3] = 0x38` (idm1-bound vif; `0x30` if idm0) instead of 0x48; keep
   `is_wan`=false (pos32=0 — verified live). The ingress ring is known from the
   wifi_bind node the install path already consults.
3. **`zx_ft_pack_cla`**: the entry's extr_index must be 0x70 (resp. 0x60), i.e.
   cla[4] byte0x10 low nibble 0x7 instead of 0x9 (0x…69 → 0x…67 keeping
   valid_en+direct, byte0x12 da_known bit unchanged per the up_idx_fix rules).
4. Install at the poly-1 5-way slots of the new raw (LAN-like, pos32=0). ⚠ ONE
   RESIDUAL UNKNOWN (validation, out of scope here): whether the fabric-ingress
   lookup probes the poly-1 way set (like GePHY) or the poly-0 ram2 slot (like
   WAN/RGMII). Cheap to cover both at install if the A/B shows a residual miss.

Expected A/B signature when implemented: qmg_up_hw carries the bulk,
qmg_up_trap ~flat, desOut no longer 0x54 for injected frames.

### Open sub-question (does NOT block the fix)
Stock's power-on ram0[7] is also 0x00150055, yet stock HW-forwards WiFi — stock
must reconfigure the rule-select at WLAN bring-up (or steer fabric ingress into
a v4-fast group) via a path we haven't traced. The proposed fix doesn't depend
on finding it (the 2026-07-02 pattern is proven on this silicon), but a stock
WLAN-up CLA diff would tell us stock's exact choice if the A/B surprises.

## Method notes / gotchas (for reuse)
- `upkey.py idle|capture|model|decode` codifies everything above; the latch
  block read is console-safe (no printk involvement; od output only).
- The gparsehashkey latch survives idle periods indefinitely (the stale
  previous-session key was still resident days later) — background WAN/IPv6
  chatter did NOT clobber it on this rig; each retransmit re-latches.
- Rule 0x76's winmask drops bit1 of SMAC byte1 (phone `ba:02:...` extracted as
  `ba:00:...`) — cosmetic here, but don't use the 0x76-window SMAC for MAC
  matching.
- clawrite first-write-doesn't-commit: write twice + clapeek verify (hit again
  live this session).

## Device end state (left SAFE)
Build #538 still RAM-booted (uptime preserved, no reboot this session);
**ram0[7] RESTORED to stock `...00150055`** (clapeek-verified); ram0[9] still
`...00150001` (the standing wired fix); no CLA hash entries written (forensics
used only the latch + hashcalc engine); **idm1 DOWN** (rx_handler inert = SW
baseline); ftwifi=0; AP + udhcpd running, client associated (ba:02:b1:26:83:24);
nft flowtable rig from the groundwork session still loaded (inert with ftwifi=0);
qmg_dn_trap=0x1f46 cumulative/healthy, qmg_up_trap=0. Host: :9099 DROP rule
removed, my /24 return-route removed (pre-existing `192.168.50.100/32 via
10.44.66.223 dev wlo1` from the previous session left untouched), NIC/TFTP
untouched. Driver source UNCHANGED.
