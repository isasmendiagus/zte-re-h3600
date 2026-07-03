# HW L3 forward — two-gate model + executable runbook (2026-06-28)

Purpose: get HW L3 flow-offload forwarding working. This doc reconciles the
real committed state with the (partly stale) session briefing, eliminates one
hypothesis, and gives a step-by-step device runbook whose FIRST step is a
read-only confirmation that needs no firmware RE.

## Ground truth (verified against the repo, not the briefing prose)
- Branch `phase6-hw-offload`, HEAD `a13779544` (2026-06-28) is the latest; no
  newer branch/worktree. The briefing's `aa9cfb17` / `a65c3e08` are **agent IDs,
  not commits** (same 8-hex format as the agent IDs in
  `ffe_forward_arm_hypothesis_2026-06-24.md`). The "it forwarded once at
  aa9cfb17" anchor is therefore an unsaved subagent run, not a reproducible
  committed state — do not treat it as a known-good to bisect toward.
- The briefing's 2026-06-28 findings files (`trap_dmac_clear_HW_FORWARD`,
  `trap_reason_decoded`, `cla_fullblock_diff_stock_vs_452`, …) and the
  `zte-*` memory entries it cites **do not exist on disk.** Real newest findings
  are dated 2026-06-24.

## The two-gate model (packet path: ingress → SPA parser → CLA classify → forward)
- **Gate 1 — SPA `trap_dmac` (bootROM-loaded).** The bootROM fills the SPA
  parser's `trap_dmac` table (phys `0x921d41a0`, 4 slots × 8B) with the device's
  own port MACs. While set, a routed/transit packet whose DST-MAC is "one of
  mine" is trapped **at the parser, upstream of the CLA**, with
  `action_rsn = 0x3f (UDF_DMAC0)` → never treated as L3 (`l3_en=0`), never
  submitted to the CLA forward classify (`acl_required` stays flat at 0).
  **FIX = write 0 to the slots** → `zx_eth_clear_spa_trap_dmac()`
  (drivers/net/ethernet/zte/zx-eth-main.c:6091, called from probe ~:5964).
  **This fix IS committed in HEAD a13779544** ("SPA gate fix").
- **Gate 2 — CLA hash `LOOK_UP_MISS`.** Hypothesis (per briefing prose, NOT yet
  confirmed in a committed doc): after the clear, the packet reaches the CLA hash
  lookup and the reason advances `0x3f → 0x54 (LOOK_UP_MISS)` — i.e. it is now
  L3/submitted, but the forward entry isn't found at the bucket the HW hashes the
  live 5-tuple to. `cla_tx_fwd` (0x9238c3c0) stays 0; `cla_tx_trp` (0x9238c3c4)
  climbs.

## Why the older "dynamic-provisioning dead-end" framing is STALE
The exhaustive REFUTATIONS in `ffe_forward_arm_hypothesis_2026-06-24.md`
(acl_required flat, l3_en=0, "never submitted") were all measured **before** the
SPA `trap_dmac` gate was found and cleared. If the gate-1 clear does what the
model says, the submit/`l3_en` problem is already solved and the live blocker is
the gate-2 hash miss — a far more tractable problem than dynamic L3 routing
provisioning.

## Hypothesis ELIMINATED this session (no RE needed): DSA frame layout / parse offset
The `tag_zte` tagger conveys the port **out-of-band in the DMA descriptor**, not
prepended into the frame bytes (zx-dsa.c:11-14). A routed transit packet
(host lan2 → device → modem lan4) ingresses as a **plain ethernet frame with no
DSA tag**, so the HW parser sees standard header offsets. Therefore a tag/offset
mismatch CANNOT explain `l3_en=0` for transit — same raw frame, stock gets
`l3_en=1`. The difference is parser config/state, which the gate-1 clear
addresses. Framing hypothesis is dead for the transit case.

## Datasheet now documents the live registers (done this session)
`tasks/00.10.02.re-stock-kmods/findings/DATASHEET.md` CLA section gained a
"live forward/trap counters + descriptor latches" subsection (`0x9238c3b8`
acl_required, `0x9238c3c0` cla_tx_fwd, `0x9238c3c4` cla_tx_trp, `0x9238c3e0/e8/ec`
desIn latch w/ action_rsn code table, `0x9238c260` gparsehashkey), plus the
`trap_dmac` bootROM semantic in the SPA section.

---

# RUNBOOK (execute from a FRESH session — shell works there)

Rig (memory zte-device-access): host NIC `enxc8a362e95900` on lan2 (PP inport 3);
modem `10.44.66.250` MAC `cc:29:bd:22:b4:2b` on WAN/lan4 (regport 5).
Boot wraps zImage+dtb; verify a fresh boot by kernel banner/build#, NOT uptime.
Console helper: `/tmp/zcon.py "<cmd>" <wait_seconds>`. NEVER reboot/sysrq — DTR only.

## STEP 1 (DECISIVE, read-only) — confirm the gate-1 clear works on current HEAD
1. Boot current HEAD (already contains the trap_dmac clear):
   `UART_TCP=1 python3 lib/uart.py auto_bootm_dtb_appended`
   Confirm banner/build#. Confirm driver loaded (`cat /proc/modules` shows zx279128_eth).
2. Bring up the routed transit rig: device lan2=172.31.9.1/24, lan4 toward modem,
   ip_forward=1, route to 192.168.9.0/24 (or the modem subnet) out lan4, next-hop
   MAC = cc:29:bd:22:b4:2b. Host route forces the test flow through the device.
3. Read BEFORE counters via the driver debugfs poke iface:
   `acl_required` 0x9238c3b8 (hi16), `cla_tx_fwd` 0x9238c3c0, `cla_tx_trp`
   0x9238c3c4, `hw_trap` 0x9234c060.
4. Run the transit flow: UDP 172.31.9.50:50010 → 192.168.9.50:53 (ingress lan2
   inport 3, egress lan4 regport 5). ~300+ packets.
5. Read AFTER counters + the `desIn` action_rsn (0x9238c3e8 bits[29:23]).

INTERPRETATION:
- **acl_required CLIMBS and action_rsn = 0x54 (LOOK_UP_MISS)** → gate 1 CONFIRMED
  solved by the trap_dmac clear. Proceed to STEP 2 (hash-bucket placement).
- **acl_required FLAT at 0, action_rsn still = 0x3f** → the clear isn't reaching
  the LIVE classifier (e.g. raw poke vs the required indirect spaRegTable write,
  cf. the pktdeal finding that raw poke of 0x921d4300 doesn't update the live
  classifier). Fix: route the clear through the indirect SPA write path; re-test.

## STEP 2 (only if STEP 1 shows 0x54) — fix the CLA hash bucket placement
The forward entry exists in all 520 buckets (fill520) but the lookup still misses
→ the live key the HW computes doesn't resolve to a bucket holding a *matching*
entry (key/inport bytes differ), OR the valid bit/word3 of the matched bucket is
off for the live key.
1. During the flow, read the live HW-computed key from the **gparsehashkey latch
   0x9238c260** (the SW key-builder is byte-exact vs this — confirmed).
2. Compute the bucket the HW would land on (hash_poly_config 0x9238c090 / the CLA
   hash engine `ZX_CLA_HASH_TRIG` 0x2c0 path) and read that exact ram2 bucket
   back; verify the stored entry's key bytes + inport (byte 0x10) + word3 valid
   match the live 5-tuple. The standing suspect (per 06-24 findings) is the
   **inport field** of the ram2 entry not matching the lan2 ingress (fill520 used
   the WAN-side default byte0x10=0x49).
3. Install the entry with the CORRECT inport for lan2/regport, re-test; watch
   `cla_tx_fwd` climb + `cla_tx_trp` stop.

## STEP 3 — wire it into the driver (decision B plumbing)
Once a manual install forwards, move the install into the offload path:
`zx_install_l3_recipe()` (zx-dsa.c:750) already has the 5-tuple + next-hop MAC +
ingress/egress regport. Add a netfilter conntrack `IPS_CONFIRMED` hook (currently
ABSENT — grep-confirmed no nf_register_net_hook / flow_offload in the driver) that
calls the install on flow confirmation, so the HW arms each routed flow at runtime.

## Note on the cyber-use-case exemption
Only needed if STEP 2 turns out to require deep stock-firmware RE or a live stock
MMIO trace (those trip a model-level cyber safeguard). STEP 1 and the hash-bucket
read in STEP 2 need NEITHER — they're plain counter/register reads on our own
driver. Pursue the exemption (claude.com/form/cyber-use-case; GPL interop, owner
hardware) only if the hash-key debug bottoms out into needing stock internals.
