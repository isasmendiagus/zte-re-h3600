# zxic — Mainline Linux on ZTE H3600 (ZX279128S)

**End goal: run OpenWrt on the ZTE H3600.**

The path to get there:
1. Get SSH on stock firmware → enables reverse engineering.
2. Reverse-engineer the proprietary ZXIC ZX279128S SoC drivers (TM, switch,
   PP, IDM, BMU, CLA, pp_pm).
3. Build a mainline Linux 6.6 ethernet driver (`zx279128-eth`) from the
   reverse-engineered behavior.
4. Get end-to-end traffic working under mainline + open driver.
5. **Port to OpenWrt** as the supported target (the original goal).

Stages 2–4 are essentially **done**: the mainline `zx279128-eth` DSA driver
with **bidirectional HW flow-offload** (NAT in silicon) carries ethernet traffic
at line rate, and WiFi (STA + AP + a working slow-path + a HW-offload mechanism)
is up. What remains before OpenWrt: WiFi offload **durability** (one open
fabric-ingress "wedge" keeps it gated off) + productionization, then the
OpenWrt port itself. See the Status table below.

## Releases / tags

Two milestone tags mark the two working states of the driver. The DSA work has
been **merged into `main`** (on top of the egress fix); the `v1.0-egress` tag
preserves the pre-DSA single-port state if you need the simplest proven path.
Check out a state with `git checkout <tag>`.

| Tag | Base | What works | What it is |
|-----|------|-----------|------------|
| **`v1.0-egress`** | `main` @1c4a971e2 | Host↔device **ping 5/5** on the cabled jack (RX + TX) | Single-port CPU↔LAN datapath. **Not** a DSA driver: the on-chip switch is driven as one CPU↔LAN path with the **egress port hardcoded** (module param `zx_eg_port=2`, the DN-descriptor egress-port hint) + GePHY TX-DAC force-drive. No multi-port / no DSA tagging / no hotplug — the cable must be on the hardcoded jack. The stable reference. |
| **`v2.0-dsa`** | `eth-dsa` @f62301ac0 | **Ports 0/2/3 ping bidirectional** via DSA slaves `lan0/2/3`; **hotplug** (move cable, no reboot); soft-float `ip`/`ping`/`brctl` | Real Linux **DSA** driver (`tag_zte` tagger, conduit `sw` + `lan0..3`). Egress port comes from the per-packet DSA tag (not the v1 hardcode). Link detection via **PHY_POLL** (the GePHY link IRQ doesn't fire). **Known issue:** port1/jack2 ingress→CPU broken — a dynamic, config-invisible per-port drop in the MAC→SPA→SDET admit stage; **not** hardware (stock pings on jack2) and **not** a register bit (every per-port reg byte-identical to working ports). Documented in `tasks/00.01.eth-driver/findings/` (multiport_root_cause_macinit, port1_sdet_ingress_gate_re, port1_spa_admit_gate_re) + `tasks/00.10.02.re-stock-kmods/findings/cla_ram_layout_re`. Debug tools: debugfs `clapeek`/`cladump`/`rx_per_ingress`. |

`v2.0-dsa` builds on `v1.0-egress` (same egress fabric fix + TX-DAC). Rebuild
with `tasks/00.01.eth-driver/scripts/build_slotA.py` then `tftp_boot_mainline.py`.

## Origin story (so the project doesn't lose its shape)

- Hardware: a ZTE H3600 GPON router we own (vendor stopped GPL distribution
  → vendor lock-in unenforceable, see memory `gpl_legitimacy_context`).
- The first breakthrough was the **orca.pet H3600P writeup** by Marcos del
  Sol Vives (`orca.pet/zteh3600p`) which documented the boot path, NAND
  layout, and AES-128-ECB rootfs encryption key — that gave us SSH access
  to the stock firmware. References: `docs/CONFIG_EDIT.md`,
  `docs/archive/ORCA_BITACORA.md`, memory `aes_key_discovered`.
- Once SSH worked, we could mount the rootfs, extract `.ko` modules,
  dump registers via stock sysfs hooks, and start reverse-engineering.
- Everything in this repo flows from those two starting conditions:
  **legitimate ownership of the hardware** + **SSH on stock firmware**.

## Status

_Updated 2026-08-01. Working branch: `main`._

| Subsystem | State |
|-----------|-------|
| Mainline boot (TFTP+bootm), C `/init`, UART REPL, 22k-reg stock replay | ✅ working |
| Ethernet DSA multi-port (`lan0-4` + WAN), hotplug, RX + TX + wire egress | ✅ working (line rate) |
| Ethernet **HW flow-offload — bidirectional (DN + UP)**, NAT done in silicon | ✅ working (~line rate, 10 GB+ sustained, nft-flowtable path) |
| Churn / RED CPU-queue "1024" wedge | ✅ fixed (RED_CFG bit6 charge-accounting) |
| WiFi STA (MediaTek MT7915, in-tree mt76/mac80211) | ✅ proven |
| WiFi AP (soft-float hostapd) + real client + internet via CPU SW-forward | ✅ working (5 GHz WPA2, end-to-end) |
| WiFi slow-path (fabric ⇄ vif dispatcher, "Phase B") | ✅ working end-to-end (real client) |
| WiFi **HW offload** mechanism (Stage 3, DN + UP, `gemport_uni_id`/ports 6-7) | ✅ mechanism HW-validated, ✅ **wedge #2 FIXED** — ftwifi now defaults ON |
| OpenWrt port | ⏳ not started (the end goal) |

The only thing between \"WiFi HW-offload works\" and \"on by default\" was **wedge #2**:
under sustained fabric-ingress HW-forwarding the fabric front-end starved and halted
(~1k–72k frames, reboot-only). **FIXED 2026-08-01**: the BMU pool was never primed on
mainline (bppe_cnt=0 vs stock's ~8112). Manually priming by freeing all 8192 BP indices
after BMU enable populates the pool (bppe_cnt=1872). Verified with wedge_coldstart.py:
139k WiFi frames, zero freeze. See `findings/wifi_stage3_wedge2_fix_2026-08-01.md`. 
ftwifi now defaults ON.

## Where do I start? (fresh-agent path)

Read in this order. Each doc is the entry point for a different question.

1. **`CLAUDE.md`** — coding conventions, naming, when-to-create-files rules.
   Don't skip; saves you from being told "remember to read CLAUDE.md" later.
2. **`ROADMAP.md`** — what we're working on now + what's parked + why.
   Always start here when picking up cold.
3. **`STATE.md`** — what's on the device RIGHT NOW (slot A/B contents,
   what kernel is running, what daemons are alive, last verified date).
4. **`LEARNED.md`** ★ — symptom → cause → fix catalog. **Grep this BEFORE
   debugging anything that smells familiar.** Every recurring bug is here.
5. **`docs/ARCHITECTURE.md`** — hardware truth (PL011 shifts, NAND map,
   BootPara, csp_crc, AES key) all in one place. Read once.
6. **`docs/KERNELS.md`** — the 3 kernel source trees + 1 binary stock kernel.
   How to build each, when to use each. Read before touching any kernel.
7. **`docs/ITERATE.md`** — the 3 dev loops (mainline-driver, stock-RE,
   stock-shell rootfs). Pick the right loop for your task.
8. **`TASKS_TREE.md`** — the canonical task hierarchy (which task is
   parent/child of what). Pick the leaf you need to work on.
9. **`tasks/NN.NN.foo/README.md`** — the task you're actually working on.
   Each task folder is self-contained: README header lists ID + Parent +
   Children + TaskList items; folder contains scripts, captures, research notes.

Specialized references:
- **`docs/HOST_SETUP.md`** — host-side services (TFTP, tcpdump, USB-eth IP,
  DTR mod). What needs to be running on your PC for anything to work.
- **`tasks/00.04.flash-tool/README.md`** — read THIS before any NAND write.
  Two-tier flasher (cspstart-aware + free-form raw), safety guards, DTR mod,
  pre-flight checklist, recovery scenarios.
- **`docs/CROSS_COMPILE_GUIDE.md`** — toolchain (soft-float, no VFP).
- **`docs/EXTERNAL_RESEARCH.md`** — orca, XYUU, winnt5, Stefan — who did what before us.
- **`docs/CHRONICLE.md`** — historical narrative log (Spanish, archival).

## Folder layout

```
zxic/
├── README.md         ← you are here
├── CLAUDE.md         ← coding conventions, naming, migration rules
├── ROADMAP.md        ← what's next, in what order
├── STATE.md          ← what's on the device RIGHT NOW
├── LEARNED.md        ← symptom-keyed catalog of recurring bugs ★
├── lib/              ← reusable Python modules (uart.py, ssh_shell.py, …)
├── tools/            ← standalone CLI utilities (gen_replay_bins.py, …)
├── tasks/
│   ├── stock-shell/  ← custom slot-A rootfs + cspd patch + kmsg2uart daemon
│   ├── eth-driver/   ← mainline 6.6 + zx279128-eth.ko (THE main work)
│   │   ├── research/ ← LIVE investigations — one file per open question
│   │   └── findings/ ← answered investigations (promoted from research/)
│   ├── flash-tool/   ← unified NAND flasher (cspstart-aware + free-form)
│   └── parked/       ← linux-stockport, pcie_re — frozen attempts
├── ext/              ← READ-ONLY golden: h3600_nand_full.bin, partitions/, rootfs/
├── docs/             ← consolidated reference docs (was scattered top-level)
├── linux-v6.6/       ← mainline kernel source (1.5 GB)
├── build/            ← kernel build artifacts (1.1 GB)
├── tftp/             ← TFTP server serves from here (host=192.168.1.50:69)
└── ghidra/           ← Ghidra RE projects
```

## Device facts (cheat sheet)

| | |
|---|---|
| SoC | ZTE ZXIC ZX279128S (ARM Cortex-A9 dual-core, 1 GHz, **no VFP enabled**) |
| RAM | 256 MiB @ 0x40000000 |
| NAND | 128 MiB SPI NAND (ESMT F50L1G41LB) — 2 KiB page, 128 KiB erase, 64 B OOB |
| UART | PL011 @ 0x94404000, **ZTE-shifted**: DR=+0x04, FR=+0x14 |
| Network | host (`192.168.1.50`) ↔ device LAN port via USB ethernet `enxc8a362e95900` |
| SSH (stock kernel) | `admin / UkuGPeyRDU` @ `192.168.1.1` |
| U-Boot prompt password | `Boot4128s!` |
| AES rootfs key | `H36000e71071c440` (16 ASCII bytes) |

## Reproducibility

Most work is reproducible from sources via documented pipelines in
`docs/RECIPES.md`. Generated artifacts go in `out/` subdirs (gitignored).
The `ext/` tree is the golden source — never write into it.

## Related

- Memory entries (under `~/.claude/.../memory/MEMORY.md`):
  `h3600-kernel-boot-recipe`, `h3600-slot-a-custom-rootfs-recipe`,
  `aes_key_discovered`, `gpl_legitimacy_context`,
  `feedback-always-check-h3600-claude-md`.
- Historical chronicle: `docs/CHRONICLE.md` (= former BITACORA.md, Spanish).
