# WiFi Stage-3 UP direction (WiFi→WAN offload) — injection leg FIXED + validated; CLA UP lookup miss root-cause NARROWED (2026-07-28)

Status: **partial — groundwork landed, blocker identified.** Same session/rig as
`wifi_stage3_phaseC_R1_validation_2026-07-25.md` (build #538 for the UP work).
The vif→fabric injection leg is now robust on HW; UP hardfast entries install
via the production path; the remaining blocker is the CLA UP lookup MISSING
for fabric-ingress frames (key/extraction mismatch, forensics below).

## What LANDED (validated live on #538)

### 1. rx_handler header restoration (real bug, fixed)
`zx_wifi_rx_handler` runs post-eth_type_trans (skb->data = L3, mac header
pulled) but `zx_idm_xmit` DMA-maps `skb->data` verbatim → every injected frame
entered the fabric HEADERLESS. Fixed with the bridge's
`br_dev_queue_push_xmit` pattern (verify mac_header position + `skb_push(ETH_HLEN)`).
Retro-explains the Phase-B.2 trap-parser "offset-hunt"/noparse fragility.
Validated: trap-parser noparse went from flaky (12 trapped SYNs, 0
re-dispatched, dead connection) to **0 noparse across 30k+ frames, 100%
re-dispatch** (tm_rx_fabric ≈ tm_rx_dispatched exactly).

### 2. TCP-data-only injection filter (design fix)
The rx_handler now injects ONLY IPv4 TCP data frames; ARP/DHCP/ICMP/IPv6/EAPOL
and TCP SYN/FIN/RST stay on the SW stack. Rationale (both HW-proven): the
hardfast traps TCP control by design (they'd round-trip pointlessly), and
making the HANDSHAKE depend on the fabric→trap→re-dispatch leg made connects
flaky. With the filter: connects always work; established data rides the
fabric; a 40 s 28 MB-offered upload runs continuously via the shuttle
slow path (~0.5 MB/s, mac4_tx +14.5k) — and the download DN direction of the
same session HW-forwards concurrently (qmg_dn_hw +12k = the upload's ACKs).

## The BLOCKER: CLA UP lookup misses for fabric-ingress frames

Facts (all live, #538):
- UP entry installs cleanly via production nft path (`eg_rp=5 wan_ing=0`,
  raw=0x9e3d, rc=0) and was live during a 40 s upload.
- 16-17k data frames/run enter the fabric with proper L2 headers
  (tx_injected), ingress fabric port 7 (idm1, ssid4).
- `qmg_up_hw = 0` ALWAYS; every frame traps back (fabric→TM→re-dispatch→
  stack→lan4 = the working slow path). `desOut` action_rsn = 0x54 LOOK_UP_MISS.
- **da_known/FDB ruled out as sufficient**: `fdbadd 5 00:0c:43:26:59:97`
  (vif MAC → CPU port, rc=0) changed nothing.

### Key forensics (gparsehashkey latch, phys 0x9238c260..28c)
- Calibration during a HW-HITTING DN download: the latch reproduces our
  key layout EXACTLY (`proto<<1|is_wan` at byte4, then sip/dip/sport/dport
  16-bit fields at pos 33+16n) — latch is faithful.
- During an upload (mixed UP-injected + DN-ACK traffic) the capture is a
  **CHIMERA**: the latch updates per packet and the 12 words are read
  sequentially (paced pokes), so different words come from different
  packets. ⚠ Do not decode a mixed-traffic capture as one key.
- The chimera's non-ACK fields fit a **reversed-tuple layout**
  ({dip,sip,dport,sport} where we pack {sip,dip,sport,dport}) in 5/7
  fields — suggestive but NOT proven (chimera). A swapped-tuple fttest
  install test was attempted live but the flow's install kept getting
  **declined by the ram6 8-bucket collision** (stale tracked flows own
  bucket 0x200), so the hypothesis is still open.

### Next session's tools (specified, not built)
1. **`idmtx` debugfs injector**: craft a full 802.3+IPv4+TCP data frame for an
   arbitrary tuple and inject via `zx_idm_xmit` with an ssid tag. With the rig
   otherwise quiet, gparsehashkey then yields a CLEAN single-packet
   fabric-ingress key → byte-diff vs `zx_ft_build_key` output answers the
   layout question definitively (incl. slot0/proto and the pos32 context bit).
2. **`ft_flows` dump debugfs** (already flagged in the R1 findings): the ram6
   stale-collision noise now actively blocks UP iteration — need
   cookie/raw/pm_slot/age visibility + possibly a flush knob.
3. Then: fix `zx_ft_build_key` (or the install path) for WiFi-UP flows to
   match the fabric-ingress extraction, and re-run the upload A/B
   (expect qmg_up_hw to carry the bulk, mac4_tx at rate, traps flat).

## Device end state (left SAFE)
Build #538 RAM-booted; ftwifi=0; **idm1 DOWN** (rx_handler inert → exact SW
baseline; only up it for UP-offload testing); no synthetic flows; AP + udhcpd
running, client associated; DN offload validated on this build too (same
driver as #537 + the two rx_handler changes); host listeners stopped.
