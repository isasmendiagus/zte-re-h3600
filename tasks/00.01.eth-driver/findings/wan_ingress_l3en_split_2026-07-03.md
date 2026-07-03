# WAN-ingress l3_en split — is the ~14% HW-forward RATE-DEPENDENT? (2026-07-03, build #476)

## VERDICT: **NOT rate-dependent.** The gate is a **per-packet WAN-ingress L3-parse-arm gap**
that persists even at **<1 packet/s**. Parser *saturation is REFUTED*: lowering the rate does
**not** raise the forward fraction toward 100 %, and raising the load *raises* the fraction
(the opposite of saturation). The ~86 % "miss" decomposes as **~75 % l3_en=0** (packets that
never reach the CLA lookup — the dominant, upstream gate) + **~11 % l3_en=1-but-CLA-trap**
(the VERDICT-B engine miss). Both are per-packet, rate-independent.

---

## Rig (PATH 1, real internet via the modem) — set up this session
- Device mainline **#476** (pristine boot each measurement).
- Cabling (empirical, per-port `rx_packets` under a host ping burst): host `enxc8a362e95900`
  ↔ device **lan2**; modem ↔ device **lan4** (10.44.66.250 gw, 8.8.8.8 0 % loss).
- Device: `lan2=172.31.9.1/24`, `lan4=10.44.66.223/24`, `default via 10.44.66.250`,
  `nat POSTROUTING -o lan4 MASQUERADE`, `FORWARD accept lan2↔lan4`, ip_forward=1.
- Host anti-leak: netns **client** (only `enxc8a362e95900`; `172.31.9.50/24`, default via
  172.31.9.1) → no wifi leak possible.
- Offload: `table inet ft { flowtable f { hook ingress priority 0; devices={lan2,lan4};
  flags offload; } chain ftfwd { hook forward; ct state established flow add @f; } }`.
- Target `http://80.249.99.148/1GB.zip` + `Host: ipv4.download.thinkbroadband.com`, curl
  `--local-port` pinned per run so the DN slot is deterministic.
- DN entry installed (dmesg recipe, both dirs): `80.249.99.148:80 -> 10.44.66.223:<port>`
  eg_rp=3 **wan_ing=1** raw=0x9609 (port 40000) / 0x3874 (port 40001), rc=0.

## Measurement method — the descriptor latches are STALE on #476; use the COUNTER decomposition
- The task's suggested latches read **constant / unusable** on #476 regardless of the actual
  ~25–31 % l3_en=1 fraction:
  - `l3_en` 0x9238c3ec = **0x80010803** → bit6 = **0** (constant).
  - `reason` 0x9238c3e8 = **0x88b00000** → bits[29:23] = **0x11** (constant, not 0x54/0x49).
  ⇒ these are shared/last-packet latches, NOT a usable per-packet l3_en/reason on this build.
  (Confirms the prior "desIn2 decode stale on #476" caveat.)
- **AUTHORITATIVE = the HW counters** (read via debugfs `poke`/`mem`; all consistent):
  - `cla_tx_fwd` 0x9238c3c0 = CLA **forward** verdicts (== QMG DN `hw_fwd` == `CLA fwd[0x1cc3c0]`).
  - `cla_tx_trp` 0x9238c3c4 = CLA **trap** verdicts — packets that **reached the CLA lookup**
    (l3_en=1) but got trapped.
  - QMG DN `hw_trap` (pipeline_stats) = **ALL** DN packets trapped to CPU.
- **The decomposition (verified self-consistent at every checkpoint):**
  - **l3_en=1** count = `cla_tx_fwd + cla_tx_trp`  (reached the CLA lookup)
  - **l3_en=0** count = `QMG hw_trap − cla_tx_trp`  (trapped with **no** CLA verdict = never looked up)
  - check: (fwd+trp) + (hw_trap−trp) = hw_fwd + hw_trap = total DN  ✓ (72+211=283=34+248;
    163+367=530=95+435).
  - `cla_tx_trp` is consistently a *small fraction* of `QMG hw_trap` (37/248, 68/435) — if it
    counted all traps it would equal `hw_trap`; it doesn't → it counts only the l3_en=1 CLA-trap
    subset. (Stock corroborates: stock cla_tx_trp≈587 while forwarding 28573 at 99 % ⇒ stock has
    ~no l3_en=0 population; mainline's large hw_trap−cla_tx_trp gap is the l3_en=0 excess.)

## Results — the l3_en split (authoritative counters)
| checkpoint | cla_fwd | cla_trp | QMG hw_trap | l3_en=1 | l3_en=0 | **HW-fwd %** | **l3_en=1 %** |
|---|---|---|---|---|---|---|---|
| after unlimited + partial 5k | 35 | 37 | 248 | 72 | 211 | **12.4 %** | **25 %** |
| after 5-parallel burst | 95 | 68 | 435 | 163 | 367 | **17.9 %** | **31 %** |

- **HW-forward fraction ≈ 12–18 %** — confirms the ~14 % figure.
- **But the ~86 % miss splits into two gates:** ~**75 % l3_en=0** (never reach the CLA lookup —
  dominant) + ~**11 % l3_en=1-but-CLA-trap**. Of the l3_en=1 packets, only ~**half** actually
  forward (35/72, 95/163) — the residual CLA miss with a resident valid entry = VERDICT B.

## THE RATE TEST (the big question) → NOT rate-dependent; saturation REFUTED
Effective WAN-ingress DN packet rate is throttled by the trap-induced loss itself (TCP collapses),
so all single-flow downloads crawl. That is exactly what lets us test the low-rate limit:

| condition | eff. ingress rate | window HW-fwd % | window l3_en=1 % |
|---|---|---|---|
| single unlimited (self-throttled crawl) | ~4 pkt/s | ~10–16 % | ~25 % |
| single **`--limit-rate 5k`** (5× slower) | ~0.9 pkt/s | ~14 % | ~25 % |
| **5 parallel** unlimited (higher aggregate load, first ~6 s burst) | burst | ~24–40 % | ~37 % |

- At the **lowest achievable rate (~0.9 pkt/s)** the forward / l3_en=1 fraction stays ~14 % / ~25 %
  — it does **NOT** climb toward 100 %. If this were parser saturation, a near-idle rate would
  parse ~100 %. It does not.
- Pushing the **load higher** (5 parallel) *raises* the l3_en=1 fraction to ~37 % and forward to
  ~24–40 % (then the flows also collapse to a crawl). Higher rate → **higher** parse success, the
  **opposite** of saturation (looks like a fresh-burst / pipeline-batching effect: back-to-back
  packets parse better than a trickle).
- ⇒ **The gate is a per-packet parse-arm gap, not a throughput/saturation limit.**

## First-vs-steady
Roughly **steady** ~11–18 % across the whole session — there is no "first N packets forward then
drop to 0". If anything, a **fresh burst** forwards at a *higher* fraction (~24–40 %) that decays
as the flow settles into the crawl. The gate is a persistent *partial* pass, not a one-shot arm.

## Correlation with packet content (TCPTRAP driver log — first 50 trapped IPv4-TCP frames)
The driver logs every trapped TCP frame (`zx-eth-main.c:3860`) with len/flags/payload/desc:
- Trapped DN packets **#6–#25 are ALL full-MTU data**: `len=1506 ihl=20 thl=32 payload=1440
  ingress=4`, flags `0x18` (PSH,ACK) then `0x10` (ACK). Identical **desc[4..b]=`00 00 29 4a 00
  c4 0b 20`** across every one.
- ⇒ the miss is **uniform on bulk data** — NOT size-selective, NOT flag-selective, NOT the
  SYN/FIN/RST control-packet key-corruption artifact. It is a **data-plane per-packet gate**,
  consistent with VERDICT B (identical key/slot/resident entry, still misses).

## LAN-ingress comparison
The download's **UP** direction (client→server, LAN/lan2 ingress) HW-forwarded **0 %** here
(QMG UP `hw_fwd=0`) — but that is the *known separate FT-UP-path* issue, not a clean parse test.
The clean **LAN-ingress data = 100 %** result stands from `hitrate_rootcause_2026-07-03.md`
(DSA tc-flower, fixed 5-tuple, 100 % across every data-plane variation). ⇒ the gate is
**WAN-ingress-specific**, as before.

## Conclusion / fix direction
- **The fix is NOT "the WAN-ingress parser saturates" / a throughput limit.** The forward
  fraction does not improve at the lowest rate and does not degrade under higher load.
- **It is a per-packet WAN-ingress L3-parse-arm gap:** ~75 % of WAN-ingress DN packets arrive at
  the CLA with **l3_en=0** (no valid L3 parse anchor → trapped *without* a CLA lookup),
  independent of rate — even at <1 pkt/s. This is **upstream of the CLA** (the DN/ring-1
  parse-route), matching `stock_wan_ingress_lookup_compare_2026-07-03.md`.
- A **secondary ~11 %** reach the CLA (l3_en=1) but still trap — the VERDICT-B engine miss
  (`wan_ingress_perpacket_key_2026-07-03.md`). Both losses are per-packet, rate-independent.
- **NEXT:** fix the mainline WAN/RGMII DN (ring-1) ingress parse so l3_en=1 like stock (the ~75 %
  gate); the residual ~11 % is the CLA engine non-determinism (VERDICT B).

## State left (CLEAN)
- Device **fresh #476** (DTR RAM-boot): empty nft, rc.router defaults (lan1=172.31.9.1,
  lan4=192.168.9.1, sw=192.168.1.99), no default route, no MASQ/FORWARD residue, QMG DN
  hw_trap=6 (**no wedge**), debugfs OK.
- Host: netns `client` torn down; `enxc8a362e95900` back in root ns @192.168.1.50 with the
  `192.168.1.0/24` route restored (TFTP-ready); single `in.tftpd`; no stray curl.
- Driver source UNCHANGED; nothing committed.
- Scripts: `scratchpad/{netns_up.sh, netns_down.sh, repl.py}`; sampler `/tmp/samp.sh` (device, RAM).

## Rig / procedure gotchas (for the next agent)
- **1024 DN-trap wedge is one-shot per boot.** QMG DN `hw_trap` pins at 1024 (reboot-only, RED
  soft-reset does not clear it). **Do NOT run any SW-only curl/ping download before loading the
  nft offload flowtable** — pure-SW routing traps *every* DN packet and fills the budget in
  seconds (cost 2 reboots this session). Protocol that works: boot → device rig → `nft -f` the
  offload flowtable → the **first** download is the measured one.
- With offload loaded, a single unlimited download self-throttles to a crawl and does **not**
  reach 1024 (peaked ~449) — you get a clean, wedge-free measurement window.
- REPL is line-based (no heredoc): write the nft ruleset to a device file with `printf`, then
  `nft -f /tmp/ft.nft`. `printk=8` floods the UART with BPDUMP/TCPTRAP debug and corrupts
  command-output parsing — set `printk=4` for counter reads, bump to 7 only for `poke` peeks.
- netns move deletes the host `192.168.1.0/24` route → restore it (+ NIC to root ns @192.168.1.50)
  before every DTR boot or TFTP fails `*T T`.
