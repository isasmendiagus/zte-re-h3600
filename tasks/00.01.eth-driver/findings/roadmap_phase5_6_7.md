# Phase 5 / 6 / 7 — Post-Phase-4 roadmap

Phase 4 (ping bidi PoC) closed 2026-05-24. Next phases to take this
from "proven once" to "production-quality mainline upstream".

---

## Phase 5: Stabilize ping bidi
**Goal**: `ping -c100 192.168.1.99` shows ≥95% reception, 0 DUPs.

**Current state**: 40% packet loss, many DUPs, ARP cycling between
REACHABLE/STALE/INCOMPLETE/FAILED. Root cause: TX desc[2..3] hardcoded
to port=0 + no FDB learning means switch floods/drops frames.

**Plan**:
1. **Extract ingress port from RX descriptor.** Stock HW puts port info
   in desc somewhere. Find it by dumping desc bytes for known-port frames
   (e.g., ARP from host arriving on UNI 0).
2. **Dynamic FDB learning in napi_poll.** When we deliver an skb, capture
   `(src_mac, ingress_port)` and call `zx_fdb_add(mac, vlan=0, port=ingress)`.
   `zx_fdb_add` is already implemented (uses brg_ram_set protocol).
3. **Per-skb port lookup in zx_sw_xmit.** Replace hardcoded port=0 with
   FDB lookup of dst MAC. Need to add `zx_fdb_lookup(dst_mac) → port`
   helper (mirrors `zx_fdb_add` but with read).
4. **Fallback for unknown MAC.** If FDB miss, use a "flood UNI ports"
   port code in desc[2..3]. Stock probably has a special bit pattern.
   Investigate by tracing stock for broadcast ARP TX.

**Acceptance**: 95%+ ping success rate, 0 DUPs, ARP stable in REACHABLE.

**Estimated effort**: 4-8 hours.

---

## Phase 6: Throughput + TCP testing

**Goal**: iperf3 ≥100 Mbps sustained, no driver errors.

**Plan**:
1. Install iperf3 in mainline initramfs (currently has busybox + ssh + memdump).
2. Run iperf3 server on mainline, client on host.
3. Measure baseline throughput. Compare against stock (~gigabit).
4. Profile bottlenecks:
   - `cat /proc/interrupts` after iperf — IRQ rate
   - `cat /sys/kernel/debug/zx_eth/stats` — BMU drops, tm_rx_dropped
   - perf top inside mainline (need perf in initramfs)
5. Tune:
   - TX desc ring size (currently 128) — bump to 256/512?
   - NAPI budget (currently 512)
   - BP pool size (currently 1024 × 2304 = 2.3 MiB)
   - DMA coalescing if HW supports it
6. Add ethtool stats so userspace can monitor.

**Acceptance**: ≥100 Mbps sustained iperf3 TCP, ≤1% packet loss.

**Estimated effort**: 6-12 hours.

---

## Phase 7: Mainline-quality refactor

**Goal**: Clean RFC patch series for net-next.

**Plan**:
1. **Replace bulk replay with explicit init.** Each of 25k stock register
   writes in `fpga.bin` needs documenting (or removing if not needed):
   - Use kotrace on stock to capture exact init sequence
   - Convert to explicit `tm_write(...)` calls in driver
   - Drop the fpga.bin firmware blob entirely
2. **Standard net_device_ops**:
   - `ndo_get_stats64` with proper 64-bit counters
   - `ndo_set_mac_address`
   - `ndo_change_mtu`
   - `ndo_set_rx_mode` (promisc/multicast filter)
   - `ndo_validate_addr`
3. **ethtool_ops**:
   - `get_drvinfo`, `get_link`, `get_link_ksettings`, `get_strings`,
     `get_ethtool_stats`, `set_ringparam` etc.
4. **Devicetree bindings**:
   - `Documentation/devicetree/bindings/net/zte,zx279128s-eth.yaml`
   - Document each `reg`, `interrupts`, `interrupt-names` entry
5. **Cleanup**:
   - Remove diagnostic `pr_emerg` / `dev_info` floods
   - Remove C-init REPL initramfs hack (use real initramfs)
   - Remove kotrace dependency from runtime
   - Remove all `2026-05-24` comments
6. **Build cleanliness**:
   - `scripts/checkpatch.pl --strict` clean
   - sparse clean
   - smatch reviewed
   - `CONFIG_ZX279128S_ETH` Kconfig
   - `MAINTAINERS` entry
7. **Patch series for netdev@**:
   - Cover letter
   - 5-15 patches, each topic-focused
   - Pre-RFC review on linux-arm-kernel@ for ARM platform code
   - RFC submission to netdev@vger.kernel.org

**Acceptance**: RFC posted, no immediate NACK from netdev maintainers.

**Estimated effort**: 20-50 hours.

---

## Order

Strict: 5 → 6 → 7. Phase 5 unblocks 6 (need stable ping for TCP).
Phase 6 unblocks 7 (need throughput baseline to know we didn't regress
during cleanup).

Phase 5 is the highest immediate value — without it, the driver is a
demo, not a tool. Phases 6+7 turn it into something the mainline ZTE
H3600 OpenWRT port can actually use.

---

## Phase 5 in-session attempt results (2026-05-24)

Tried, didn't reach 95% acceptance criteria but made measurable progress:

| Experiment | Loss | DUPs/5pings | Notes |
|---|---|---|---|
| Phase 4 final baseline (port=0 hardcode) | 40% | 70 | Proven workable |
| + dynamic FDB learn (added) | 40% | 252 | No measurable improvement |
| desc[2..3]=0 (no port hint) | 100% | n/a | WORSE — HW needs port indicator |
| Back to port=0 + FDB learn code | 20% | 277 | Slightly better reception, worse DUP count |

**Conclusion**: stability requires what we don't have:
1. Kotrace of stock's TX path during host ping → see actual desc[2..3]
   bytes stock uses for unicast replies
2. Implementation of switch's FDB hash function correctly (our brg_ram_set
   protocol may not match HW exactly)
3. Port mask logic for "send to actual ingress port of original frame"
   rather than fixed port=0

**Recommendation**: Phase 5 needs runtime trace work before more code
changes. Phase 6 (iperf) and Phase 7 (mainline cleanup) are blocked
until Phase 5 reaches 95%+ stability.
