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
│   ├─ (no sub-folders yet; open work in research/*.md)
│   │  ─ research/rx_path_dead.md            🔥 WIP — the eth-driver blocker
│   │  ─ research/printk_injection_methodology.md   open — RE methodology
│   │  ─ findings/                            (empty; promote answered research here)
│   └─ Linked TaskList: #53, #87, #89, #90, #91, #92, #93, #103, #104
│
├── 00.02 stock-shell        tasks/00.02.stock-shell/            ✅ DONE-ENOUGH
│   └─ Linked TaskList: #100, #101
│      (cspd-patch + kmsg2uart bridge → persistent UART on stock kernel.
│       Used as RE oracle for 00.01.)
│
├── 00.03 nand-flash         tasks/00.03.nand-flash/             📚 REFERENCE
│   └─ Doc-only bundle: NAND layout, BootPara CRC rules, every flash
│      script's role, DTR mod, RAM-vs-NAND mode, slot-A-vs-B policy.
│      Read before any NAND write. No scripts of its own.
│
├── 00.04 mainline-kernel    (not created yet — placeholder for the kernel
│                             wrap/build/persist work distinct from the
│                             driver itself; may stay merged with 00.01)
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
