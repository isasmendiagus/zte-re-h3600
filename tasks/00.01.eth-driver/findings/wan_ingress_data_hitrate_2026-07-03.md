# WAN-ingress (lan4) DATA hit-rate — the decisive experiment (2026-07-03, build #472)

## VERDICT: **(B)** — WAN-ingress DN DATA extracts a **wrong-slot key and MISSES.**

There IS a WAN-ingress-specific data-plane gate. It is **not** merely the control-packet→P3
wedge. The download-direction (DN, server→client) bulk-data packets ingress lan4/MAC4/RGMII
and the HW **extracts a CLA hash key that differs from the driver-installed key by exactly one
bit** → they hash to a different bucket → LOOK_UP_MISS → trap/drop → the transfer stalls.

## Rig (PATH 1, real internet through the modem)
- Device mainline **#472**, fresh DTR boot. Cabling determined empirically each boot via per-port
  `rx_packets` under a host ping burst: **host `enxc8a362e95900` ↔ netdev `lan2`** (lan2 shows
  kernel `no-carrier` but forwards via PHY_POLL — the #470 discovery), **modem ↔ `lan4`**
  (`fe80::1 = cc:29:bd:22:b4:2b`). lan1/lan3 dead.
- Device: `lan2=172.31.9.1/24`, `lan4=10.44.66.223/24`, `default via 10.44.66.250`,
  `iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE`, `FORWARD` accept `lan2<->lan4`
  (rc.router policy is DROP). Device→8.8.8.8 verified 0% loss.
- Host: anti-wifi-leak netns `client` (moved `enxc8a362` in; `172.31.9.50/24`, default via
  `172.31.9.1`; `ip route get <pub-ip>` → via 172.31.9.1, no wifi leak).
- Offload: `table inet ft { flowtable f { hook ingress priority 0; devices={lan2,lan4};
  flags offload; } chain ftfwd { type filter hook forward priority 0; ct state established
  flow add @f; } }`. Both dirs install (P1 fix works).
- Target: `http://80.249.99.148/1GB.zip` + `Host: ipv4.download.thinkbroadband.com`
  (tele2 is IPv6-only now; thinkbroadband is IPv4 with large files).
- Reads (independent of console printk, so console kept at `printk=3` to avoid the BPDUMP flood):
  QMG/CLA counters via `cat pipeline_stats`; registers via `busybox dd if=.../zx_eth/mem
  bs=4 skip=$((<phys-0x921c0000>/4)) count=N | busybox od -An -tx4`; HW hash via
  `echo "<12 words>" > .../hashcalc; dmesg | grep hashcalc`.

## The behaviour
- Every download **reliably stalls at ~1161 bytes = the HTTP response headers only**; the bulk
  body never arrives. Rate 116–193 B/s (the documented crawl). Conntrack shows the flow
  `[HW_OFFLOAD]`. Removing the flowtable = normal SW routing (bulk streams). ⇒ offload is
  net-negative and it is the DN bulk **data** that does not get through.
- Cumulative DN split over a download session: `hw_fwd`≈18–23 %, rest `sw_fwd`+`hw_trap`
  (same ~13–18 % ratio as every prior run). WAN `QMG DN hw_trap` climbs to **1024 and pins =
  the P3 wedge**, after which even the device's own `ping 10.44.66.250` fails (WAN-RX→CPU dead).

## The decisive key evidence (the crux)
`gparsehashkey` (0x9238c260, 12 w) latches the last packet through the CLA forward-hash. It
latches BOTH directions, so each captured key must be classified UP vs DN. Decode confirmed by
rebuilding the driver's key (`zx_cla_flow_hash`, base bit 33 + 16·n, field = value<<1 because
base is odd):

- **UP** (lan2/GePHY ingress, client→server) key = `48000000 583e000c a1f21265 <sport<<1>c728
  000000a1`. Low byte of word1 = **0x0c → key-bit pos32 = 0**. Matches the driver builder
  exactly ⇒ UP keys are correct (would hit).
- **DN** (lan4/WAN/RGMII ingress, server→client) key = `48000000 a1f2000d 1458c728 00a085be
  0001<dport<<1>`. Low byte of word1 = **0x0d → key-bit pos32 = 1**. Words 2–3 are byte-identical
  to the driver builder; the **only** difference from the correct key is that extra pos32 bit.
  **24/24 DN captures across distinct flows were all `a1f2000d` (pos32 = 1) — universal.**

`pos32` is bit0 of key word1, i.e. the bit immediately before the proto field that the driver
places at base bit 33. It is a **WAN-ingress-only** bit: LAN-ingress (UP) never sets it and the
driver never sets it.

### Airtight single-flow proof (flow DN 80.249.99.148:80→10.44.66.223:38304, installed raw=0x7b38)
- driver key (pos32=0) `48000000 a1f2000c 1458c728 00a085be 00012b40` → **hashcalc = 0x7b38**
  = EXACTLY the installed entry raw (validates the builder and confirms the driver installs at
  the pos32=0 slot 0x38).
- actual WAN-ingress DN key (pos32=1) `48000000 a1f2000d …` → **hashcalc = 0x3e4e ≠ 0x7b38**
  (slot 0x4e ≠ 0x38).

⇒ A WAN-ingress DN data packet probes bucket 0x4e; the driver installed the entry in bucket
0x38 → **no match → LOOK_UP_MISS → trap**. This is a *data* miss (the captured keys are clean
5-tuple data keys — they show none of the TCP-flag "1010-repeat" corruption; the difference is
one deterministic ingress-dependent bit, not a flags artifact).

## Why this is a genuinely new result
The #472 LAN-ingress study proved LAN data hits 100 % and the only per-packet variance was TCP
control flags (benign). This run tested the previously-untestable WAN-ingress path and found a
**second, data-plane gate that is specific to lan4/RGMII ingress**: the CLA hash key for a
WAN-ingress packet carries an extra bit (pos32) that the GePHY LAN-ingress path and the driver's
key builder do not. So the offload is **not** "complete modulo P3" — the DN data-plane is broken
at WAN-ingress independent of the control-packet/wedge story.

## Fix guidance (concrete)
The driver's `zx_cla_flow_hash` / `zx_ft_flow_hash` build every entry with `kb[4] bit0 = 0`
(pos32=0). That is correct for lan2/GePHY-ingress entries (UP) but **wrong for the DN/reply
entry, which is matched at lan4/WAN ingress**. The WAN/RGMII ingress parser adds a bit at key
position 32 (an ingress-port-derived bit). Make the key builder **ingress-aware**: when the
entry's match ingress is lan4/MAC4 (the reply/download direction, `eg_rp` toward LAN), set
`kb[4] |= 1` before hashing **and** in the stored windata used for the bucket compare, so the
installed slot matches the WAN-ingress extraction. Then WAN-ingress DN data will hit → forward.
(Verify the same bit for any other RGMII/WAN-side ingress; GePHY LAN ports keep pos32=0.)
Open sub-question: identify pos32's exact HW meaning (likely an inport/port-tag bit folded into
the hashed key) so the driver replicates it from the flow's ingress port rather than a hardcode.

Residual note: DN `hw_fwd` is not exactly zero (~18 %); a minority of DN packets still forward
(first-packet timing before the entry settles, or hash collisions into an occupied bucket). The
dominant, reproducible behaviour is miss, and the mechanism is proven.

## Left clean
Device DTR-rebooted to pristine **#472** (no nft, no MASQUERADE, no modem route, rc.router
defaults: lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1; **no wedge**, DN hw_trap=5, REPL
alive). Host: netns `client` torn down, `enxc8a362e95900` back in root ns @192.168.1.50
(tftp-ready). **Rig gotcha hit + fixed:** the netns move/flush deleted the host's
`192.168.1.0/24` connected route, so U-Boot TFTP replies were routed out wifi (`*T T`); restored
with `ip route add 192.168.1.0/24 dev enxc8a362e95900 src 192.168.1.50` + one clean `in.tftpd`.
Driver source UNCHANGED, nothing committed.
