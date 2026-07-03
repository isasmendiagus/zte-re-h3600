# CLA real-traffic hit-rate — root-cause investigation (2026-07-03, build #472)

**HEADLINE:** For a fixed 5-tuple the CLA hit-rate is **100% on LAN-ingress across every
data-plane variation tested** (UDP/TCP, payload 0–1460 B, TCP options/timestamps, varying
seq, ~21 k pps, remote vs directly-connected dst). The HW-extracted hash key
(`gparsehashkey`) is a **pure, constant function of the 5-tuple** for those packets — the
top "per-packet key variance" hypothesis is **REFUTED for the data plane**. The **one**
per-packet key variance found is **TCP control flags**: any packet with **FIN, SYN, or RST**
set (the low 3 bits of the TCP flags byte) extracts a **corrupted key** (dst-IP + ports
mis-extracted) → hashes to the wrong bucket → **100% MISS/trap**; packets with only
ACK/PSH/URG extract the correct key → 100% hit. This is a HW-parser behaviour inside extract
rule `0x90`, **not** a driver key-builder bug (the builder and stored windata are
5-tuple-correct, proven by data packets hitting 100%).

The WAN-ingress (lan4) DN path — the direction that showed ~13% in the real download —
**could not be tested**: lan4 is occupied by the modem and there is no free host NIC on
lan2/lan3 (no carrier). See "Reconciliation / open" below.

---

## Rig / method
- Device: mainline **#472** (`Linux 6.6.0 #472`), fresh DTR boot, RAM-only. lan1=172.31.9.1/24,
  lan4=192.168.9.1/24, ip_forward=1, no nft, no wedge at start.
- Host `enxc8a362e95900` = 192.168.1.50 (+172.31.9.50/24 added for the test, removed after) is
  cabled to **lan1** (device MAC2, `f4:f6:47:0f:42:64`). Confirmed: a lan1-ingress
  `tc flower` matched injected frames (`in_rp=2`).
- Injector: `scratchpad/rawflow.py` via `/usr/local/bin/python3-netraw` — crafts full
  Ethernet+IPv4+{UDP,TCP} frames pinning an exact 5-tuple, with per-packet control of
  payload length, TCP flags, seq, and TCP-option words (data offset). New this session
  (the old rawflow.py was gone).
- Install path (proven DSA tc-flower): `tc qdisc add dev lan1 clsact` +
  `tc filter add dev lan1 ingress protocol ip flower skip_sw ip_proto {udp,tcp} src_ip …
  dst_ip … src_port … dst_port … action mirred egress redirect dev lan4`.
- Verdict counters via `poke` debugfs: `cla_tx_fwd 0x9238c3c0`, `cla_tx_trp 0x9238c3c4`.
  HW-extracted key `gparsehashkey 0x9238c260..0x28c` (12 words). Δfwd/Δtrap = hit/miss.

## Experiment 1 — per-packet key variance (the TOP hypothesis)
Installed UDP `172.31.9.50:50010→192.168.9.50:53` (raw 0xf6d5) and TCP `…:50010→…:80`
(raw 0x9d5a). Sent bursts varying one dimension; measured Δfwd/Δtrap; read `gparsehashkey`.

| variation (fixed 5-tuple) | result |
|---|---|
| 200 identical small UDP | fwd **+200 / 0** (100%) |
| 200 UDP, payload cycling 0,100,500,1000,1400 | fwd **+200 / 0** (100%) — **length not in key** |
| 200 identical small TCP (psh,ack) | fwd **+200 / 0** (100%) |
| 200 TCP varying seq + flags(psh,ack/ack) + length | fwd **+200 / 0** (100%) — **seq not in key** |
| 1000 UDP back-to-back (~21 k pps) | fwd **+1000 / 0** (100%) — **rate not the cause** |
| 500 full-MTU PSH,ACK + TS options + seqvary, gap 0 | fwd **+500 / 0** (100%) |
| PSH,ACK data-offset 5/6/8/10 (TCP options) | fwd **+50 / 0** each (100%) — **options not in key** |

`gparsehashkey` for these was byte-constant for a given 5-tuple:
`word0=0x48000000` (ex_rule_id 0x90) always; src/dst words identical; only proto+dport bits
change between the UDP and TCP tuples, exactly as the 5-tuple key builder predicts.
**⇒ No data-plane key variance. The 5-tuple key is stable and correct.**

## Experiment 2 — the ONE variance found: TCP control flags (decisive)
Same installed TCP flow, 50–100 pkts per flag set, `gap 0.004`, payload 0:

| flags | fwd | trap | verdict |
|---|---|---|---|
| ack | +50 | 0 | **HIT** |
| psh,ack | +50 | 0 | **HIT** |
| psh | +50 | 0 | **HIT** |
| urg,ack | +50 | 0 | **HIT** |
| **syn** | 0 | +51 | **MISS** |
| **syn,ack** | 0 | +50 | **MISS** |
| **fin** / fin,ack | 0 | +51/+52 | **MISS** |
| **rst** / rst,ack | 0 | +50/+50 | **MISS** |

Rule: **FIN(0x01) | SYN(0x02) | RST(0x04) set → MISS; otherwise HIT.**

HW-extracted key, single SYN vs single ACK (same 5-tuple, headers identical except the
flags byte):
```
ACK : 48000000 583e000c 81501265 86b41265 000000a1   (correct — matches UDP/PSH-ACK)
SYN : 48000000 583e000c 10101265 86b61010 000000a1   (words 2-3 corrupted = dst-IP + ports)
```
The proto + src-IP fields (words 0,1) are intact; corruption begins exactly at the dst-IP
field (bytes 10-14 = dstHi/dstLo/sport). A different key ⇒ a different hash slot ⇒ probes a
bucket with no entry ⇒ trap. This is **within** ex_rule 0x90 (word0=0x48 in both), so it is
the HW parser's field-extraction shifting on the control-flag bits, **not** a rule-selection
change and **not** the driver's key builder (which is 5-tuple-only and correct).

## Experiment 3 — eviction / persistence
`clapeek ram2[0xd5]` after all the above heavy traffic = byte-identical to install
(`03005044 fa11c000 00000608 00000000 11000049 32ac1f00 32c0a809 35c35a09`), valid. **No
eviction, no aging, no competing-entry churn.**

## Code check — FT (nft flowtable) path vs DSA path
`zx_ft_pack_cla`, `zx_ft_flow_hash`, `zx_ft_way_slots` (zx-eth-main.c) are **byte-identical**
to the proven `zx_cla_pack_entry` / `zx_cla_flow_hash` / `zx_cla_way_slots` (zx-dsa.c). The
FT path installs the same entry in the same buckets. So the real flow's entries were placed
correctly (consistent with the dmesg `[phase6/ft] recipe:` lines from the A/B run).

---

## Reconciliation with the reported ~13% real-download hit-rate — and what's still open
- **Steady bulk DATA packets hit 100%** on LAN-ingress (500/500 full-MTU PSH,ACK+TS). So the
  ~87% miss on the real download is **NOT** explained by data-packet key variance, rate, size,
  options, seq, or eviction — all refuted here.
- **The flag corruption fully explains why every SYN / SYN-ACK / FIN / RST misses.** This
  breaks/stalls TCP *connection setup and teardown* through the offload: the DN **SYN-ACK
  traps to the WAN-RX CPU queue**, directly feeding the P3 1024-frame wedge, and the handshake
  thrashes. A connection that barely establishes and then stalls (retransmit storms on
  corrupted control packets) is fully consistent with the observed ~16 B/s crawl and a
  "13% hw_fwd" that is really a trickle, not a steady data stream.
- **The residual (why bulk DN *data* would trap at ~87% in the real run) most likely lives in
  the untested WAN-ingress (lan4 / MAC4 / RGMII, RX ring 1) classification path** — a
  genuinely different ingress MAC/ring from lan1. This could not be exercised: lan4 is the
  modem and lan2/lan3 have no carrier (no free host NIC). **This is the #1 next experiment**
  and needs a rig change: a controllable sender on the lan4 side (e.g. temporarily re-cable a
  host NIC to the WAN jack, or a second LAN jack configured as the far side) to install a
  DN-direction entry (ingress lan4 → egress lan1) and measure Δfwd/Δtrap for WAN-ingress
  data packets in isolation.

## Fix guidance
- **TCP control-flag corruption:** for nft/tc flowtable offload this is **largely benign by
  design** — SYN/FIN/RST *should* take the slow path (CPU) so conntrack tracks state
  transitions; only ESTABLISHED data packets are meant to be fast-pathed, and those hit 100%.
  So it is **not** the throughput fix per se. Its real harm is second-order: the DN SYN-ACK
  trap feeds the P3 WAN-RX 1024 wedge. **Recommended:** (a) fix the P3 wedge (find a TM/RED
  soft-reset) so unavoidable control-packet traps can't wedge the RX ring; independently
  (b) if a HW fix for the flag-dependent extract is wanted, it is in extract rule 0x90's
  winoffsets/L4-offset handling (`zx_ffe_rules[0x90]` = `{0x22038608, 0x000058a1, 0,0,
  0xf00ff000, …}`) — a HW-parser tuning exercise, lower priority than the WAN-ingress gate.
- **The throughput gate is almost certainly WAN-ingress**, not the CLA key — pursue the
  WAN-ingress isolation experiment above before any further key/entry work.

## Left clean
- Device #472 running, all tc filters + clsact qdisc removed (`tc filter show` empty),
  routes intact (lan1=172.31.9.1, lan4=192.168.9.1), ip_forward=1, REPL alive, printk restored
  to `1 4 1 7`. **No wedge** (QMG DN hw_trap=864 < 1024, queue draining, device responsive).
  Not rebooted: no wedge existed, and a mainline re-TFTP (needs stopping the UART bridge +
  juggling the tftp NIC) carries more host-stranding risk than it removes.
- Host: `172.31.9.50/24` test IP removed; `enxc8a362e95900` back at **192.168.1.50** (tftp-ready);
  `enx2c99`/`enx6c70` left DOWN as found. No nft/MASQUERADE/modem-route residue was created.
- New tool `scratchpad/rawflow.py` (frame injector). Driver source UNCHANGED, nothing committed.
