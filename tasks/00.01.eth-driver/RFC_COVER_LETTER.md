# [RFC PATCH 00/N] net: zte: zx279128s integrated Ethernet driver

This is a *request for comments* on bringing the ZTE ZXIC ZX279128S
on-chip Ethernet block into mainline Linux. The series is currently
~12 patches covering an MDIO controller driver, a custom GePHY driver,
the per-SoC Ethernet driver, DT bindings, and supporting reference
material. The driver boots, links the four built-in GePHYs, and
delivers RX traffic to the host on real hardware; some features (TX,
DSA-style switching) are explicitly **incomplete** and we're soliciting
direction before going further.

## Why an RFC and not a v1 patch series

* **The hardware is GPL-licensed but the SDK isn't shipped.** ZTE,
  Digi, and CHN — between them the OEM, distributor, and silicon
  vendor — have all refused our SDK source requests, pointing at each
  other. Every register write in the driver was reverse-engineered
  from stock binaries via Ghidra + a custom kernel-level tracer
  (kotrace.ko, in our development tree). We want maintainer signal on
  what's an acceptable shape for a driver built this way before
  polishing the series.

* **Big chunks of init are still anonymous register replay.** 30 % of
  the captured stock-init writes are now named C functions; 70 % go
  through a generic apply_block() walker against a generated header.
  We have a roadmap to name the rest but the work depends on PON-side
  .ko decomp + runtime kotrace that we haven't finished. We'd like to
  know if the current shape is acceptable for a v1, or if we need to
  hold the series until everything is named.

* **Architecturally the right shape is DSA.** The SoC has an on-chip
  4-port switch + a CPU conduit; mainline's DSA framework is the
  natural fit. The current submission is **monolithic** — `eth0`
  ("sw" CPU port) + `idm0`/`idm1` (wifi conduit) live in one platform
  driver. DSA conversion is multi-week and we'd rather get review
  signal on the rest before committing to it. RFC explicitly asks
  whether reviewers will accept a non-DSA v1 or require the split
  first.

## Hardware summary

* SoC: ZTE ZXIC ZX279128S, ARM Cortex-A9 SMP @ 1 GHz, 256 MiB DDR.
* Ethernet: 4× MAC[0..3] + on-chip switch (SW) + Packet Processor (PP)
  + Network Packet Processor (NPP) + IDM DMA ring + Traffic Manager
  (TM). Built-in MDIO controller drives four internal GePHYs at
  addresses 10..13 (PHY ID 0x84b95031).
* Sibling reference: ZX279128R (same family, slightly different
  variant). DTS for that unit is in our repo under refs/ and was the
  primary cross-check for our address map.

## What's in the series

(N to be filled in once split into per-patch commits.)

  0001  dt-bindings: net: add zte,zx279128s-mdio.yaml
  0002  net: mdio: add ZTE ZX279128S MDIO bus driver
  0003  net: phy: add ZTE ZX279128S internal GePHY driver
  0004  dt-bindings: net: add zte,zx279128s-eth.yaml
  0005  net: ethernet: zte: new zx279128-eth driver
  0006  ARM: dts: zte: add zx279128s.dtsi
  0007  ARM: dts: zte: add zx279128s-h3600.dts (board)
  0008+ data tables that drive stock-init replay (separate patches
        because each is ~1 MB of generated data)

## What boots / what doesn't

End-to-end verified on a ZTE H3600 (the consumer product based on
ZX279128S):

  * Kernel boots cleanly, no Oops/panic
  * mdio-zte registers the bus
  * 4 × ZTE GePHY drivers bind at MDIO 10..13
  * phy_init_hw() runs LDO + TX-DAC analog power-up on each
  * eth driver completes stock-init replay (22 363 writes)
  * RX path delivers ARP / mDNS / IPv6 ND frames to the CPU netdev

Known broken / incomplete:

  * **TX → wire**: frames leave eth0 and the driver thinks they were
    sent (TX descriptors recycled, BMU credits replenish), but they
    never show up at the laptop on the other end of the cable.
    Pre-existing, predates this series; we suspect a misconfigured
    cla_set_dn_unknown_da_action or a missing PP_BRG write.
  * **PHY link status**: phy_init_hw runs config_init but nothing
    later starts the PHY (no phylink_connect) so cable detect /
    autoneg state never reaches userspace.

## RE evidence pointers

For each non-trivial write the driver makes, our development repo has
either:

  * a Ghidra-decompiled stock C source (`tasks/00.10.02.re-stock-kmods/
    findings/decomp_all_*.c`)
  * a kotrace runtime capture during stock init
  * a manual cross-check against the sibling ZX279128R DTS or boot log
    (`refs/zte-zx279128R/`)

Pointers are inline in the source via comments. We're happy to publish
the trace evidence alongside the patches if reviewers want — it's just
not normally included in a netdev submission.

## Asks for the RFC

1. Is "monolithic platform driver, DSA conversion as v2" acceptable,
   or do we need DSA shape before any merge consideration?
2. Is "30 % named, 70 % captured-table replay" acceptable for the
   initial driver, with a roadmap to keep naming more?
3. Are the two generated headers (`zx_stock_bursts.h` ~1.2 MB,
   `zx_npp_twin_data.h` ~50 KB) acceptable in-tree, or do we need to
   split them out / drop them entirely?
4. The .data hardcoded vendor MAC template inside the NPP twin-pair
   init (lifted from a stock capture on a specific unit's host MAC)
   — keep, generate dynamically, or punt to userspace?
5. Any preferred shape for the PHY driver's `config_init` extended-
   register pokes that we should follow instead of the inline
   {addr, val} array?

Thanks for any feedback.

Agustin Isasmendi <infra@quecomere.com>
