# ZX279128S DSA — upstream submission notes

State of the `eth-dsa` branch (16 commits) and what's needed before it can go to
`netdev@vger.kernel.org`. Honest status: code-complete + checkpatch-clean, but
**NOT yet HW-verified and NOT yet probing** (the P1 conduit refactor is pending).
Do not submit until the blockers below clear.

## Hard blockers before ANY upstream submission
1. **HW verification.** Every DSA op is spec-backed (RE'd from stock) but only
   compile-tested. Must verify on the device (run dsa_verify.py after P1) — at
   minimum: lanN appear, ping on lan2 = 0% loss, FDB/STP/VLAN/isolation
   readback matches. Upstream will not take unverified register pokes.
2. **P1 conduit refactor** (dsa_conduit_refactor_guide.md) — without it the driver
   doesn't probe, so nothing is testable.
3. **The base conduit driver is not upstream.** DSA needs a conduit netdev; ours is
   `zx-eth-main.c`, which itself isn't merged. The DSA series DEPENDS on the eth
   driver landing first (or being submitted together as a larger series). This is
   the biggest practical hurdle — it's a whole SoC ethernet + switch stack.

## Suggested submission ORDER (independent → dependent)
1. **PHY driver** `phy-zte-gephy.c` — self-contained phylib driver, checkpatch-clean,
   already has a MAINTAINERS entry. Can go FIRST, standalone, lowest risk. (Needs a
   dt-binding for the PHY if not already covered.)
2. **MDIO bus** `mdio-zte.c` (+ binding) — also fairly standalone.
3. **Ethernet / CPU-port (conduit)** `zx-eth-main.c` (+ bindings) — the big one; the
   DSA conduit. Likely the longest review.
4. **DSA switch + tagger** — `net/dsa/tag_zte.c`, `drivers/net/dsa/zte/`, the DSA
   binding, the DSA_TAG_PROTO_ZTE enum. Depends on #3.

## How the 16 eth-dsa commits map to upstream patches (squash plan)
- tag_zte + enum + header + Kconfig/Makefile → 1 patch "net: dsa: add ZTE tag driver".
- zx-dsa.c skeleton + all per-port ops (squash the P0/P3/hash/isolation/review
  commits; they were incremental WIP) → 1–2 patches "net: dsa: add ZTE ZX279128S
  driver" (+ maybe a separate FDB/VLAN patch).
- DT binding → folded with the driver patch (bindings usually precede the driver).
- MAINTAINERS → folded into the driver patch.
- The conduit changes (P1, once done) → part of the eth driver series, not the DSA one.
Drop the WIP/"checkpatch"/"plan"/"review" commits — squash into clean logical patches
with proper commit messages (the RE provenance can go in the cover letter, not every
commit).

## Things reviewers will flag (fix before/with submission)
- **VLAN attr** 2-bit encoding is best-effort (untagged?2:3) — confirm the real
  semantics or restrict to the verified case.
- **FDB single-way** — stock uses a 4-way set per hash; we use way 0 only. Either
  implement the 4-way walk or document the limitation.
- **Register windows** — zx-dsa devm_ioremaps NPP/PP non-exclusively, overlapping the
  conduit. Upstream wants this via syscon/regmap shared with the conduit, or DT reg
  with proper resource ownership. Refactor before submission.
- **zx_phys_port()** identity stub — fine for user ports; document/handle the full
  getPort remap if any non-1:1 port is exposed.
- Hardcoded phys bases (0x921c0000/0x92388000) → must come from DT `reg`.
- The internal-tag approach (4-byte stripped-by-conduit) is unusual — the cover
  letter should explain why (out-of-band descriptor port, no in-band tag) so
  reviewers understand it's not a normal in-frame tagger.

## Cover-letter skeleton (for when ready)
- What the hardware is (ZX279128S SoC, integrated 4-port switch + CPU-port DMA).
- Why DSA + why the out-of-band internal tag.
- What's verified on HW (fill in after the bench session).
- The dependency on the eth conduit driver.
- RE provenance (GPL stock kernel) — note it's clean-room-ish from the vendor GPL
  release; be precise about licensing/provenance for upstream.
