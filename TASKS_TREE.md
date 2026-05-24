# TASKS_TREE — the canonical task hierarchy

The dotted-decimal prefix in each folder name IS the parent chain.
This file is just the human-friendly view. Update it whenever you add,
rename, or re-parent a task folder.

For the naming convention itself, see `CLAUDE.md` "Task folder naming".

---

## Active tree

```
00 openwrt-port              tasks/00.openwrt-port/              📋 PLANNED (root goal — stage 5/6)
├── 00.01 eth-driver         tasks/00.01.eth-driver/             🚧 ACTIVE — RX dead, TX intermittent
│   ├── 00.01.01 fix-lief-rel-sections                            ✅ DONE — LIEF #661 patch
│   │       Fix to LIEF's silent section-drop on ARM REL files.
│   │       Forward decl + REL fast-path delegation.
│   ├── kotrace/                                                  ✅ WORKING — RAM-patch tracer
│   │       Idea A. Loader-notifier kmod that patches switch.ko's
│   │       .text in RAM at MODULE_STATE_COMING. Sidesteps the bug
│   │       classes documented in findings/ko_splice_bugs.md.
│   │       First init trace captured 2026-05-23.
│   ├─ research/rx_path_dead.md             🔥 WIP — the eth-driver blocker
│   ├─ research/printk_injection_methodology.md   superseded by kotrace/
│   ├─ findings/ko_splice_bugs.md           why on-disk LIEF splicing fails
│   ├─ findings/idea_a_kotrace.md           the working tracer + init trace
│   └─ Linked TaskList: #53, #87, #89, #90, #91, #92, #93, #103, #104
│
├── 00.02 stock-shell        tasks/00.02.stock-shell/            ✅ DONE-ENOUGH
│   └─ Linked TaskList: #100, #101
│      (cspd-patch + kmsg2uart bridge → persistent UART on stock kernel.
│       Used as RE oracle for 00.01.)
│
├── 00.04 flash-tool         tasks/00.04.flash-tool/             ✅ DONE
│   │  Unified NAND flasher (kernel/rootfs/both/header/raw subcommands).
│   │  Lives entirely inside the task folder per CLAUDE.md "rule of two".
│   │
│   ├── 00.04.01 tftp-port-probe tasks/00.04.01.tftp-port-probe/  ✅ DONE
│   │      Confirmed ZTE U-Boot 2013.04 fork does NOT support
│   │      tftpdstp / tftpdstport / tftp_port → sudo in.tftpd
│   │      stays. Captured cspstart's csp_crc log as a bonus.
│   │
│   └── 00.04.02 uart-bridge tasks/00.04.02.uart-bridge/          🚧 PoC
│          UART-over-TCP daemon: own /dev/ttyUSB0 long-running,
│          re-publish on tcp/9999 (data) + tcp/9998 (DTR ctl) +
│          /tmp/uart_bridge.log. Unblocks concurrent UART access
│          for flash + monitor + kotrace. Integration into flash.py
│          via UART_TCP=1 env-var is TaskList #29.
│
├── 00.07 wifi               tasks/00.07.wifi/                   ✅ DONE
│      MT7915 WiFi 6 on internal PCIe. Custom DesignWare PCIe glue
│      driver `pcie-zx279128s.ko` enables the bus; mainline `mt76` /
│      `mt7915e` drives the radio. wlan0 STA mode + internet verified
│      2026-05-04. MSI broken for this geometry → `pci=nomsi` workaround.
│

├── 00.06 platform-drivers   tasks/00.06.platform-drivers/       📋 PLANNED (cherry-pick catalog)
│   │  Umbrella for resurrecting removed-from-mainline ZX SoC drivers.
│   │  6 known cherry-picks; clk is the urgent one (blocks scaling
│   │  beyond the brute-replay hack in eth driver).
│   │
│   ├── 00.06.01 clk-driver         tasks/00.06.01.clk-driver/         🎯 PLANNED (urgent)
│   │       Resurrect clk-zx296702.c + adapt with our clk-zx279128s.c
│   │       Unblocks proper clk_get() for every future driver.
│   │
│   └── (future: 00.06.02 gpio, 00.06.03 dma, 00.06.04 platsmp,
│                00.06.05 pm-domains, 00.06.06 dt-bindings)
│
├── 00.05 firmware-load      tasks/00.05.firmware-load/          📚 REFERENCE
│   │  Methods catalog: how to get code onto a fresh device. Decision
│   │  tree + comparison table. Per-method children below.
│   │
│   └── 00.05.01 rop-no-uart tasks/00.05.01.rop-no-uart/         ✅ WORKING
│          Pre-auth RCE via stock httpd's rsaDecryptWithoutKeyFile bug.
│          Includes task-local Ghidra project at ./ghidra/ (httpd RE).
│          (Future siblings: 00.05.02 web-upload-haikui — placeholder)
│
└── 00.10 explore            tasks/00.10.explore/                🔬 KNOWLEDGE BASES (umbrella)
    │  Umbrella for discovery/RE tasks. They produce LEARNING, not
    │  implementation. Each owns a Ghidra project + findings/ markdown.
    │  Rules of engagement (append-only, fork-to-experiment) live here.
    │
    ├── 00.10.01 re-vmlinux         tasks/00.10.01.re-vmlinux/          🧠 stock kernel
    ├── 00.10.02 re-stock-kmods     tasks/00.10.02.re-stock-kmods/      🧠 stock .ko collection
    ├── 00.10.03 re-uboot           tasks/00.10.03.re-uboot/            🧠 U-Boot
    └── 00.10.04 mainline-archaeology tasks/00.10.04.mainline-archaeology/ ✅ DONE
           Spanish-language survey of removed-from-mainline ZX support.
           Drives the OpenWrt port resurrection plan.
           (Future siblings: 00.10.05 re-cspd, 00.10.06 re-web-admin,
            00.10.07 re-pcie, 00.10.08 re-wifi — when needed)
```

```
99 parked                    (no folder — 99 is just the category prefix)
└── 99.01 linux-stockport    tasks/99.01.linux-stockport/        ⛔ PARKED
       Vanilla 4.1.25 + kprobes attempt. Pivoted to printk-injection
       methodology (in 00.01/research/) instead.
```

---

## When to add a new node

Apply the rule from CLAUDE.md:

- **New folder** when the subtask has its own scripts, captures, or build artifacts.
- **`research/<topic>.md` in the parent** when it's just notes / hypotheses / open questions.

Numbering: leave gaps (01, 05, 10) at each level so insertions don't cascade renames.

---

## When to update this file

- New task folder created → add a row in the right subtree, update parent's `**Children**:` line
- Task re-parented → move row in tree, fix `**Parent**:` line in its README, sed-fix path refs in scripts/docs
- Task done / parked → update the status emoji in the row (and the README's `**Status**:` line)
- New TaskList entry created → if it belongs to an existing task, just add the `#NN` to that task's `Linked TaskList:` row; if it spans multiple tasks, mention both
