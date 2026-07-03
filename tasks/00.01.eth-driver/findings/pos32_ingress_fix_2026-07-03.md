# pos32 ingress-aware CLA hash fix — IMPLEMENTED + slot-match PROVEN, but NOT the throughput payoff (2026-07-03, build #474)

## TL;DR

The WAN-ingress `pos32` hash-key fix from `wan_ingress_data_hitrate_2026-07-03.md` is
**implemented in both key builders and PROVEN correct on-device**: the DN/reply entry now
hashes to the exact bucket a WAN-ingress packet probes (byte-exact key match, installed
slot == live HW hashcalc, both directions). **But it did NOT make the download fast.** At
the now-correct slot the lookup still MISSES for the large majority of real-traffic packets
(DN ~17 % hit, UP 0 % hit), the offloaded flow stalls (~38 B/s, worse than the ~53 KB/s
pure-SW baseline), and the DN CPU-trap budget fills → the P3 WAN-RX wedge (hw_trap=1024)
re-trips. **So `pos32`/slot-mismatch was a real bug and is fixed, but it was NOT the (whole)
throughput gate.** The dominant remaining gate is a byte-exact-entry-at-correct-slot lookup
MISS on the FT/flowtable path for real multi-packet traffic (the unresolved P4 hit-rate
problem), compounded by heavy flowtable install/destroy churn.

## The code change (build #474)

Made the CLA hash-key builders ingress-aware so the DN/reply entry (matched at WAN/RGMII
ingress) is installed at the bucket the WAN extraction probes (`kb[4] |= 1`, i.e. key bit
pos32 = 1), while GePHY LAN-ingress entries keep pos32 = 0.

- **`drivers/net/ethernet/zte/zx-eth-main.c` (FT / conduit module = the tested path):**
  - New `#define ZX_WAN_REGPORT 5` (lan4 = MAC4 = RGMII modem uplink; `zx_regport[4]=5`).
  - `zx_ft_flow_hash(..., bool is_wan)` — after `kb[3]=0x48;` add `if (is_wan) kb[4] |= 1;`.
  - `zx_ft_install_recipe` derives `is_wan = (eg_regport != ZX_WAN_REGPORT)` and passes it
    to the hash. (A routed flow's DN/reply entry egresses toward a LAN port, so its matching
    packets ingress the WAN; the UP entry egresses the WAN port so it ingresses LAN.)
  - `zx_ft_flower_replace` computes `eg_regport = zx_ft_egress_regport(odev)` once, up-front,
    and feeds the SAME `is_wan` to the reserve-time hash and the install (so reserve slot ==
    install slot). Added `wan_ing=%d` to the recipe log line.
- **`drivers/net/dsa/zte/zx-dsa.c` (built-in, mirror):**
  - New `#define ZX_WAN_REGPORT 5`.
  - `zx_cla_flow_hash(..., bool is_wan)` — same `if (is_wan) kb[4] |= 1;`.
  - Here `is_wan` is derived from the ACTUAL ingress port: `zx_install_l3_recipe` uses
    `in_regport == ZX_WAN_REGPORT`; `zx_dsa_cls_flower_add` uses
    `zx_regport[port & 7] == ZX_WAN_REGPORT`. (Ingress-port-based is more precise and keeps
    the local LAN-ingress tc-flower tests unchanged: they inject on a GePHY port → pos32 = 0.)

Both drivers compile clean. Build #474 (`Linux 6.6.0 #474`), DTR-booted, driver init healthy
(SPA trap_dmac cleared, CLA init 1804 ok / FFE 82 ok, DSA tree up, lan1/lan4 1Gbps).
Nothing committed.

## Airtight on-device proof that the slot fix is CORRECT

Rig: PATH 1, real internet. Device `lan2=172.31.9.1/24` (host client), `lan4=10.44.66.223/24`
→ modem `10.44.66.250` (`cc:29:bd:22:b4:2b`), MASQUERADE out lan4, FORWARD lan2↔lan4,
`ip_forward=1`. Host `enxc8a362e95900` in netns `client` = `172.31.9.50/24` via `172.31.9.1`
(no wifi leak, `ip route get <pub> = via 172.31.9.1`). nft offload flowtable `{lan2,lan4}
flags offload; ct state established flow add`. Target `http://80.249.99.148/1GB.zip`
(Host: ipv4.download.thinkbroadband.com). Device→8.8.8.8 verified 0 % loss on a fresh boot.

For a live flow (client ephemeral port 46198; MASQUERADE preserved the port):

| direction | driver recipe (dmesg) | live HW-extracted key (gparsehashkey 0x9238c260) | hashcalc |
|---|---|---|---|
| UP (lan2 ingress, pos32=0) | `172.31.9.50:46198->80.249.99.148:80 eg_rp=5 wan_ing=0 raw=0x1668` | `48000000 583e000c a1f21265 68ecc728 000000a1` | **0x1668** |
| DN (lan4 ingress, pos32=1) | `80.249.99.148:80->10.44.66.223:46198 eg_rp=3 wan_ing=1 raw=0x9980` | `48000000 a1f2000d 1458c728 00a085be 000168ec` | **0x9980** |

- The driver's DN key (rebuilt offline for port 46198 with pos32=1) is **byte-identical** to
  the live WAN-ingress extraction: `48000000 a1f2000d 1458c728 00a085be 000168ec`.
- **Installed DN slot 0x9980 == live WAN-ingress hashcalc 0x9980** (was the crux: before the
  fix the driver would install at the pos32=0 slot and the WAN packet probes pos32=1 → miss).
- **UP slot 0x1668 == live UP hashcalc 0x1668** too.
- pos32 confirmed live: UP key word1 low byte `0x0c` (pos32=0), DN `0x0d` (pos32=1) — exactly
  the wan_ingress finding's signature; `is_wan` (eg_rp != 5) selects it correctly.

⇒ The pos32 slot-mismatch identified by the prior finding is **closed and proven**: both
directions' entries now land at the exact bucket the HW probes on ingress.

## Why the payoff still did NOT happen (the honest result)

Despite byte-exact key + slot match in BOTH directions, real traffic still mostly MISSES:

- Over a 15 s download window: **DN hw_fwd Δ+11, sw_fwd Δ+25, hw_trap Δ+29** (≈17 % HW-fwd);
  **UP hw_fwd = 0** (every UP packet traps). `CLA fwd[0x1cc3c0]` climbs 1:1 with DN hw_fwd
  only (+11). `smac4 good_uc` ≈ 77 over the window — the transfer barely moves.
- Download throughput with offload: **~38 B/s (1159 bytes = HTTP headers only, stalled)** vs
  **~53 KB/s pure-SW** (baseline, flowtable removed, same boot). So the offload is still
  **net-negative** (≈1400× worse), exactly as the pre-fix state.
- The DN CPU-trap budget fills (most DN data traps, not HW-forwards) → **QMG DN hw_trap pins
  at 1024 = the P3 WAN-RX wedge re-trips**, after which the device's own `ping 10.44.66.250`
  and the client's internet both die (reboot-only clear). This wedge tripping is itself proof
  the DN data is still trapping, not HW-forwarding.
- Heavy flowtable **install/destroy churn**: 80 `recipe:` installs / 44 `flower destroy` /
  22 `flow del` across the session — the FT flow does not stay stably offloaded.

### What this means
`pos32` (slot mismatch) was a genuine bug and is fixed + proven, but it is **not** the
dominant throughput gate. The dominant gate is that a **byte-exact-correct entry at the
provably-correct slot still returns LOOK_UP_MISS for the large majority of real-traffic
packets on the FT/flowtable path**, in BOTH directions (UP 0 %, DN ~17 %). This is the same
signature as the older `#452/#456` "engine rejects a byte-exact nonzero key" regression and
the `PERFORMANCE_NOTES` **P4** ("raise the real-traffic hit-rate to ~100 %") — now shown to
persist **after** the slot is corrected, so P4 ≠ pos32. Consistency check on the windata
compare (task point 4): the stored windata is byte-aligned @0x13 (proto/IPs/ports, per
`cla_windata_packer`); pos32 (key bit 32, BELOW the proto field at bit 33) is not part of the
byte-aligned compare window, so there is no windata byte to also set — pos32 legitimately
affects only the hash/slot. The residual miss is therefore NOT a missing windata-pos32 bit.

## Next leads (for P4, the real remaining gate)
1. **FT-vs-DSA A/B on #474.** The DSA tc-flower path reportedly hits ~100 % for a pinned
   flow; the FT/flowtable path hits ~17 %. Install the SAME 5-tuple via DSA tc-flower on #474
   and measure — if DSA hits and FT misses, the gate is FT-path-specific (entry write
   difference, or the install/destroy churn leaving the entry absent most of the time).
2. **Flowtable churn.** 80 installs/44 destroys for a handful of connections ⇒ the flow keeps
   being torn down + re-offloaded. Likely the flowtable GC sees no HW-forwarded packets (they
   trap) → marks the flow idle → destroy → re-add. Instrument the FT setup_cb REPLACE/DESTROY
   cadence; a flow that is present only ~17 % of the time would alone explain ~17 % hit.
3. **desOut trap reason** for a DN packet at the correct slot (0x9238c39c bits[29:23]); if
   0x54 LOOK_UP_MISS with the entry confirmed resident, it is the engine-compare regression,
   not placement.
4. P3 wedge remains the hard failure mode whenever DN data traps in bulk; a real fix needs
   the QMG-DN trap-credit-return RE (`wan_rx_onewrap_wedge`) OR ~100 % DN HW-forward so the
   trap queue never fills.

## Left clean
Device DTR-rebooted to pristine **#474** (RAM-only config wiped on boot: no nft, no
MASQUERADE, no modem route; rc.router defaults; the 1024 wedge cleared by the reboot). Host:
netns `client` torn down, `enxc8a362e95900` back in root ns @192.168.1.50, `192.168.1.0/24`
TFTP route restored, in.tftpd healthy. Driver source edited (zx-eth-main.c + zx-dsa.c);
**NOT committed**.
