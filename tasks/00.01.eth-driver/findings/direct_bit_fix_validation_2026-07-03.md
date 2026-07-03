# `direct`-bit fix end-to-end validation — WAN-ingress verdict bit is applied+installed but does NOT fix the download (2026-07-03, build #478)

## VERDICT
The `cla[4] |= 0x20` (`direct` verdict bit, byte0x10 bit5, `0x49`→`0x69`) fix is **correctly
built, correctly gated, and correctly installed** into the download-direction (WAN-ingress /
`is_wan`) CLA entry. The FT/conduit binder engages for **both** directions. **BUT the real
download still crawls exactly as before** (stalls at the HTTP response headers, ~57–77 B/s).
⇒ The `direct` bit is **NOT** the download-speed blocker. The WAN-ingress DN data packets still
**MISS the CLA lookup** (they never reach the resident entry), so the verdict bit — which only
matters on a lookup *hit* — is never consulted for them.

This is a clean negative result: the fix does what it says at the entry level, but the actual
gate is upstream of the verdict (the WAN-ingress lookup miss, `wan_ingress_data_hitrate` #472).

## Build / boot
- Built via `build_slotA.py` (make all → module `.ko` re-embedded into `/tmp/initramfs_extract`
  → `make zImage` → uImage wrap → `tftp/zImage_dtb.uimg`). Two vmlinux links (make all + make
  zImage) bumped the kernel build counter from #476 → **#478** (task said "#477"; the exact
  number is just the kbuild link counter — this is the fresh build carrying the fix).
- RAM-booted via `scratchpad/reboot_mainline.py` (DTR power-cycle → U-Boot TFTP → bootm). Fresh
  banner confirmed: `Linux (none) 6.6.0 #478 Fri Jul  3 16:19:38 UTC 2026`. REPL responsive.
- Both source edits confirmed present before build:
  - `zx-eth-main.c:2348` `zx_ft_pack_cla`: `cla[4] = (ip_proto<<24) | (is_wan ? 0x69 : 0x49)`
  - `zx-dsa.c:831`     `zx_cla_pack_entry`: same.
  - FT gate: `is_wan = eg_regport != ZX_WAN_REGPORT` (zx-eth-main.c:2449).

## Rig (PATH 1, real internet via the modem) — reproduced from `acl_required_fork_settler`
- Host `enxc8a362e95900` ↔ device **lan2** (confirmed by per-port rx: lan2 rx climbed, lan1/lan3=0).
- Device: `lan2=172.31.9.1/24`, `lan4=10.44.66.223/24`, `default via 10.44.66.250`,
  `MASQUERADE -o lan4`, `FORWARD` accept lan2↔lan4, `ip_forward=1`. Device→8.8.8.8 = **0% loss**.
- Host anti-wifi-leak netns `client` (`enxc8a362` moved in; `172.31.9.50/24`, default via
  `172.31.9.1`) via `scratchpad/netns_up.sh`. client→8.8.8.8 through the router = **0% loss**
  (SW-routed; ttl decremented) — the software path is healthy.
- nft offload flowtable loaded BEFORE the download:
  `table inet ft { flowtable f { hook ingress priority 0; devices={lan2,lan4}; flags offload; }
   chain ftfwd { type filter hook forward priority 0; ct state established flow add @f; } }`
- Target: `http://80.249.99.148/1GB.zip` + `Host: ipv4.download.thinkbroadband.com`,
  pinned `--local-port 40000`.

## Result 1 — the FT binder ENGAGES for BOTH directions (recipe fires)
dmesg during an established download (loglevel 8):
```
[phase6/ft] recipe: proto=6 172.31.9.50:40000->80.249.99.148:80 eg_rp=5 wan_ing=0
    nh=cc:29:bd:22:b4:2b pm_slot=8 -> raw=0x1ce1 buckets ram2[0xe1]/... rc=0     (UP / upload)
[phase6/ft] recipe: proto=6 80.249.99.148:80->10.44.66.223:40000 eg_rp=3 wan_ing=1
    nh=c8:a3:62:e9:59:00 pm_slot=9 -> raw=0x9609 buckets ram2[0x09]/... rc=0     (DN / download)
```
Both fire repeatedly as conntrack re-promotes the flow. UP egresses regport 5 (WAN, nh=modem MAC);
DN egresses regport 3 (lan2, nh=host MAC). `wan_ing` gated correctly (DN=1, UP=0).

## Result 2 — the installed DN entry carries `direct=1` (word4 = 0x..0069); UP unchanged (0x..0049)
Caught resident by hammering `clapeek` during an active flow (the conntrack entry ages between
sparse retransmits, so a single peek usually reads 0 — a tight peek loop catches it):
```
DN  ram2[0x09]: 03005044 fa11c009 00000608 00000000 06000069 9450f900 df0a2c63 40005042 0000009c
UP  ram2[0xe1]: 03005044 fa11c008 00000608 00000000 06000049 32ac1f00 9450f909 509c4063 00000000
                                            word4 ^^^^^^^^
```
- **DN word4 = 0x06000069** → byte0x10 = **0x69 = 0x49 | 0x20** = `direct` bit SET. **Fix landed.**
- UP word4 = 0x06000049 → 0x49, `direct` NOT set — correct (upload is not is_wan).
- word1 low byte = 0x09 (DN, WAN ingress-keying) vs 0x08 (UP) — the ingress-keying field, matches
  the fork-settler's `fa11c009`/`fa11c008` observation. The DN entry sits in bucket ram2[0x09]
  (raw 0x9609) = the same WAN-keyed bucket the fork-settler and `wan_ingress_data_hitrate` found.

## Result 3 — the download is STILL a crawl (the fix does not speed it up)
Four independent downloads (rate-limited 1M, pinned port 40000), all identical:
| run | HTTP | bytes | speed |
|---|---|---|---|
| dl1 | 200 | 1159 | 77 B/s |
| dl2 | 200 | 1159 | 57 B/s |
| dl3 | 200 | 1159 | (stalled) |
| dl4 | 200 | 1159 | 64 B/s |

Every run stalls at **1159 bytes = the HTTP response headers only**; the bulk body never arrives.
This is byte-for-byte the documented crawl (`wan_ingress_data_hitrate`: "reliably stalls at
~1161 bytes … 116–193 B/s"). The `direct` bit did not change the outcome.

## Result 4 — counters: DN still trapping (~11% forward), packets still MISS the lookup
Cumulative DN bank across the download session (peeked via `poke` read / dmesg):
| counter | phys | value | meaning |
|---|---|---|---|
| CLA DN fwd (download-forward) | 0x9238c3cc | **26** | forwarded DN packets |
| CLA DN trap | 0x9238c3d0 | **202** | trapped DN packets |
| CLA DN drop | 0x9238c3d4 | 0 | not dropped downstream |
| QMG DN hw_fwd | 0x9234c048 | 34 | |
| QMG DN hw_trap | 0x9234c04c | **227** | (well below the 1024 wedge cap) |
| acl_required (hi16) | 0x9238c3b8 | 130 | reached the CLA |
| acl_failed (lo16) | 0x9238c3b8 | **70** | **LOOKUP MISS** |
| CLA UP fwd | 0x9238c3c0 | 46 | upload/ACK direction FORWARDS |

- DN forward rate ≈ 26/(26+202) ≈ **11%** — unchanged from the pre-fix crawl regime.
- `acl_failed = 70` climbs with the load ⇒ the WAN-ingress DN data packets **reach the CLA and
  FAIL the lookup (miss)**. Because they miss, they never land on the resident entry — so the
  `direct` verdict bit on that entry is irrelevant to them. **The verdict bit can only help a
  lookup HIT; the blocker is the lookup MISS.**
- The `download-forward` counter (0x9238c3cc) does climb a little (+26 total, +7/+~1 per burst)
  but never 1:1 with the load — the forwards are the sparse packets that happen to hit.

## Result 5 — upload forwards, no wedge, device healthy
- CLA UP fwd = 46 (climbs) ⇒ the LAN-ingress upload direction (TCP ACKs client→server)
  HW-forwards, consistent with the fork-settler TEST3 (LAN-ingress = 100% hit).
- QMG DN hw_trap = 227 « 1024 ⇒ **no P3 wedge**. Device `ping 10.44.66.250` = **0% loss**
  throughout and after. WAN-RX→CPU alive.

## CONCLUSION + next target
The `direct`-bit fix is verified correct at the entry/binder level (DN word4=0x69, both dirs bind)
but is **not sufficient** for a fast download. The real, still-open blocker is the **WAN/RGMII-
ingress CLA lookup MISS**: the DN data packet's HW-extracted hash key does not select the bucket
where the (correct, valid, `direct`-flagged) entry is resident, so it misses → traps → the transfer
stalls. This is exactly the gate localized in `wan_ingress_data_hitrate_2026-07-03` (pos32 key bit)
and re-confirmed by `acl_required_fork_settler` (in-CLA lookup miss = Verdict B). The verdict-bit
fix addresses a downstream stage that these packets never reach.

**NEXT = fix the WAN-ingress lookup MISS** (the key-extraction / bucket-selection for RGMII-ingress
DN data), not the verdict. Candidate angles from the prior findings: the `pos32` WAN-ingress key
bit vs the driver's installed slot; per-ingress way-probe (install all 5 ways ram2..ram6 vs way0);
windata compare-field vs the WAN-extracted key bytes. Until the DN data HITS the entry, the
`direct` bit does nothing for real downloads (keep it — it is correct and harmless, and it will be
required once the lookup hits).

## State left clean
- Device on **#478**, alive, NOT wedged (hw_trap 227«1024, modem ping 0% loss).
- nft ruleset **flushed empty**. Host `enxc8a362e95900` restored to root ns @ **192.168.1.50/24**,
  tftp route to 192.168.1.1 restored (netns `client` deleted). Single in.tftpd bound to
  192.168.1.50:69. Device network is the RAM-boot working config (non-persistent; a fresh boot
  re-runs rc.router defaults). Source edits present, **NOT committed**.
