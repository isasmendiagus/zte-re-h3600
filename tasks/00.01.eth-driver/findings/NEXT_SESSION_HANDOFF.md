# ZTE H3600 HW flow-offload — next-session handoff (2026-06-29)

Paste the block below as the opening prompt of a fresh Claude Code session to continue this work.

---

```
ZTE H3600 HW flow-offload — continuation session.

CONTEXT (read these first, they hold the full state):
- Memory index: .claude/.../memory/MEMORY.md — read the whole index, then at minimum:
  zte-flowoffload-framework, zte-roadmap, zte-redwedge-unicast-cpu, zte-cla-ram-layout,
  zte-cla-hw-hash-engine, zte-port-numbering, zte-datasheet, autonomous-iterate-until-done.
- Findings dir: tasks/00.01.eth-driver/findings/ — esp. the 2026-06-28 files
  (trap_dmac_clear_HW_FORWARD, trap_reason_decoded, cla_fullblock_diff_stock_vs_452,
  cla_dport_packer_bug_AND_452_lookup_regression, cla_hw_extracted_key_VS_stored).
- Driver: linux-v6.6 branch phase6-hw-offload, HEAD a13779544. Files: drivers/net/dsa/zte/zx-dsa.c
  (built-in), drivers/net/ethernet/zte/zx-eth-main.c (conduit module), include/linux/dsa/zte.h.
  NOTE the driver source tree lives at /home/ubuntu/Projects/MYSELF/ZTE/linux-v6.6 (not the cwd).

OBJECTIVE: mainline Linux 6.6 DSA driver where the CPU configures (routing/NAT/fw/DHCP) and the
HARDWARE forwards (flow offload), matching stock's hybrid model. End goal OpenWrt. Binary RE is the
legitimate path (GPL device, owner's hardware, ZTE unresponsive).

WHERE WE ARE — TWO GATES IN SERIES, first one open, stuck on the second:
A packet path is: ingress → SPA parser → CLA classifier (hash lookup) → forward/egress.
  Gate 1 (SOLVED): SPA trap_dmac table (phys 0x921d41a0, 4 slots×8B) held device MACs from bootROM
    fuses and trapped to-me packets at the parser with action_rsn=0x3f (UDF_DMAC0). Stock clears it;
    mainline now does too (zx_eth_clear_spa_trap_dmac in zx-eth-main.c). PROVEN by the trap-reason
    flip 0x3f→0x54 in the CLA desIn latch (0x9238c3e8 word2 bits[29:23]).
  Gate 2 (THE BLOCKER): after the gate fix, packets reach the CLA hash lookup and return
    LOOK_UP_MISS (action_rsn 0x54) → trapped to CPU instead of forwarded. cla_tx_fwd (0x9238c3c0)
    stays 0; cla_tx_trp (0x9238c3c4) climbs.

WHAT'S PROVEN CORRECT (so the miss is NOT these):
  - Hash key builder is byte-exact (HW gparsehashkey latch 0x9238c260 matches our computed key).
  - The ram2 forward entry is byte-identical to a stock forward entry, present in all 520 buckets.
  - CLA config registers are byte-identical to stock (full-block diff; outspace_cfg 0x9238c094 = 0x4
    on both stock and mainline).
  - The gate is open (trap_dmac=0, packet reaches the CLA).

KEY FINDING (just settled — bisect): we saw it forward ONCE mid-session (commit-era aa9cfb17,
cla_tx_fwd +500), but that is NOT reproducible. Reproducing aa9cfb17's EXACT install+flow from a
clean cold boot MISSES on BOTH the #452 build AND the June-6 parent a41efb318. So:
  - It is NOT a code regression between June-6 and #452 (parent fails identically).
  - aa9cfb17's forward required some INTRA-BOOT operation done earlier in that one live boot that
    "armed" the CLA hash-lookup engine. The install tables ALONE are not sufficient.
  - The missing piece is a dynamic OPERATION (a trigger/commit/enable write or sequence), NOT a
    static config value (config is identical to stock). Stock does it at boot/first-packet; our
    driver doesn't. THIS IS THE UNKNOWN.

NEXT STEP (recommended): MMIO-trace stock's FFE at the trap→forward transition. Stock forwards from
a clean cold boot, so stock performs the enabling op. Use the stock kotrace tooling to capture
stock's register writes at the instant a flow goes from trapping (1st packet) to forwarding (2nd
packet) — that capture should reveal the "arm-the-lookup" operation we're missing. Alternative:
replay aa9cfb17's full intra-boot poke sequence (incl prior agents a65c3e08 etc.) on a clean boot to
narrow which op flips trap→forward — slower, more archaeology.

OPERATING MODE & SAFETY (hard rules):
  - You are the ORCHESTRATOR / persistent context-holder. Delegate heavy work (captures/builds/decomp)
    to background subagents; do quick reads/coordination yourself. Iterate autonomously until done;
    at a true dead-end launch a fresh-eyes agent. Escalate to the user only on real strategy forks.
  - CONTROLLED MODE on the device: exactly ONE agent touches the device console at a time, no fan-out,
    don't probe the console while an agent owns it.
  - NEVER reboot/sysrq the device — it HALTS (no PSCI/watchdog). Recover/boot ONLY via DTR hardware
    reset. Every boot is a full power-off→power-on DTR pulse; NO warm/soft boot, no cross-boot state.
  - Don't break egress / don't disturb capWAN/WanConnection (real DIGI PPPoE on the modem).
  - Frame RE prompts to subagents as benign driver bring-up / hardware-init (adversarial
    "trap/bypass/gate" wording trips a safeguard false-positive).
  - sudo is passwordless on this host (NOPASSWD). Use `sudo` directly.
  - Commit only when the user asks; commit messages end with:
    Co-Authored-By: Claude Opus 4.8 (1M context) <noreply@anthropic.com>

RIG / DEVICE ACCESS (see memory zte-device-access):
  - UART bridge: tasks/00.04.02.uart-bridge/uart_bridge.py (data :9999, DTR ctl :9998).
  - Console helper: /tmp/zcon.py "<cmd>" <wait_seconds>.
  - Boot: UART_TCP=1 python3 lib/uart.py auto_bootm_dtb_appended (DTR-boots the wrapped zImage).
  - Build chain for the MODULE driver (critical — easy to get wrong): compile-check .o → relink
    zx279128-eth.ko → strip --strip-debug → cp .ko to BOTH tasks/00.01.eth-driver/initramfs/lib/modules/
    AND /tmp/initramfs_extract/lib/modules/ → make zImage → wrap (cat zImage + the h3600 dtb | mkimage
    -A arm -O linux -T kernel -C none -a 0x42000000 -e 0x42000040) → DTR-boot. Verify a FRESH boot by
    the kernel banner/build#, NOT uptime (uptime is bogus on this board). initramfs busybox MUST be
    the soft-float build (no-VFP CPU) — the hard-float one SIGILLs all userspace.
  - Host NIC enxc8a362e95900 is on lan2 (PP ingress port2/inport=3). Modem 10.44.66.250
    (MAC cc:29:bd:22:b4:2b) on WAN/lan4 (regport 5).
  - Test flow that should forward: UDP 172.31.9.50:50010 → 192.168.9.50:53, ingress lan2 (inport 3),
    egress lan4 (regport 5), next-hop MAC cc:29:bd:22:b4:2b.
  - Useful counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4, hw_trap 0x9234c060,
    acl_required hi16 0x9238c3b8.

START BY: confirming the live device build/state (banner, trap_dmac, counters) without disturbing an
agent, then launch the stock MMIO-trace effort (or the alternative if you judge better). Document every
result in findings/ + update memory. Keep iterating in controlled mode until cla_tx_fwd climbs (HW
forward end-to-end) or the enabling op is isolated.
```
