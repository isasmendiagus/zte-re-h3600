# TX-egress state — SESSION HANDOFF (2026-05-28, night)

Read this FIRST to resume. Full chronology is STATE.md journey #9–#19. (This supersedes the
earlier 2026-05-28 content in this file — several "fixes" listed there were later shown by
the macro red-team review to NOT be the gate.)

## Goal & status
Mainline Linux 6.6 ethernet driver for ZTE H3600 (ZXIC ZX279128S), to run OpenWrt.
**RX works end-to-end. CPU→LAN TX egress does NOT work** — the device puts **0 packets on
the physical wire** (host tcpdump, even broadcast). This is the only blocker.

## The gate, precisely (live-confirmed)
A CPU-sourced frame reaches **QMG sw_fwd** (counter 0x9234c044 increments) but **loops back
to the CPU** (`TM RX ... ingress=2 delivered`) — it never reaches a physical MAC's TX.
- Host is on **MAC2** (only MAC2 has ctrl=0xba6003 + RX-ok counting host frames; MAC2 TX-ok
  stays 0; MAC0/1/3/4 ctrl=0). So we target the right port; "wrong port" is ruled out.
- SOPC send2smac2 (0x921d9164) and MAC2 TX-ok (0x92280718) NEVER increment for CPU egress.
- Even BROADCAST (FDB-independent flood) doesn't egress → it's NOT FDB.

## KEY reframe (macro red-team, MACRO_review_tx_egress.md)
The old "ping bidi WORKS" commit (2ad931ed8) was an **ILLUSION** — replies arrived in one
~1ms burst (a buffer flush), not real round-trips. **TX never cleanly worked.** Don't chase
that baseline.

## Ruled out — do NOT re-try (all tested, runtime AND boot-time)
- UP/DN/IDM DMA rings (all 3 ring consume-counters live-confirmed 0 during stock egress;
  the TM ring base is at tm_base+0x10000=0x92350000, NOT npp+0x10000=0x921d0000 — an
  address-map error that confounded early reads; see ADDRESS_MAP_ERROR_tm_ring_2026-05-28).
- Shared-ring + dual-kick (0x10054+0x10064) — replicated, reaches QMG, no egress.
- Flood bitmap PP[0x92388340]=0xff5555ff + broadcast gates — no egress.
- SOPC config / isolate table PP[0x83c0] — verified already-correct; not the gate.
- PON_PP_TM_CFG 0x923a001c bit29 — already set (0x21200000).
- The full **PM/SPA direct config** (0x921e0054=0xc0, 0x921e01a0=0x8, 0x921d407c=1, in-port
  rules) — poked at runtime AND set at boot via new `zx_pm_spa_init()` — STILL no egress.
**→ ALL direct config (runtime + init) is exhausted. The QMG→SOPC→physical-MAC-TX step
never activates for a CPU-sourced frame, no matter what config reg we set.**

## Two remaining hypotheses
1. **SPA match-RAM** (RECOMMENDED next — most tractable, fits the symptom). The SPA
   source-port classifier match-RAM (indirect, ram_id 0, ~11 entries) is the ONLY config
   never populated. If the CPU/source-port match entry is absent, the classifier won't
   authorize the CPU→physical forward → frame loops to CPU. Access: indirect port
   CMD 0x921d4014 / DONE 0x921d4018 bit0 / DATA 0x921d401c..30 (derive the read/write
   encoding from the decomp spa_* accessors; leftover stock cmd 0x01400007 = ram_id5/addr7
   shows the field layout). Next step: read stock's live match-RAM (boot stock, indirect-
   read) → replicate at init in zx_pm_spa_init(). Recipe + caveats: pm_spa_init_recipe_re.md,
   cpu_source_port_egress_re.md, stock_spa_match_ram_dump_re.md (if it gets written).
2. **Fundamental: egress half clock/power-gated** (HARD + UNCERTAIN — pursue only if #1
   fails). The ETH_TM2 mux (0x923a0000) is confirmed clock-gated (writes don't latch;
   ungate never found — TOPCRM[0x08] edge + [0x0c] re-assert failed). BUT: the SOPC block
   (0x921d9xxx) reads fine (clocked) and MAC2 does RX (clocked), so the fabric egress path
   is NOT obviously clock-gated; and ETH_TM2 is the U-Boot *direct-mux* path (different from
   the fabric SOPC path). So #2 is speculative. uboot_direct_egress_plan.md,
   eth_egress_clock_reset_re.md.

## Methodology notes (learned the hard way this session)
- **tcpdump is the only trustworthy judge** of egress (counters gave 2 address-map errors +
  a /proc/kmsg read-drop bug). `tcpdump -i enxc8a362e95900 -e -nn 'ether src f4:f6:47:0f:42:64'`.
- Live poke/peek over **localhost:9999** REPL (one busybox applet/line; `sh -c` for redirects;
  `memdump <phys> <len>` len≤8; poke via `echo "<phys> <val>" > /sys/kernel/debug/zx_eth/poke`).
  The UART **bridge** (tasks/00.04.02.uart-bridge/uart_bridge.py, serves 9999/9998) must be
  running — restart it if 9999 refuses (stock-boot agents kill it / leave the boot script
  holding the tty: `kill` it, free /dev/ttyUSB0, relaunch the bridge).
- Build `tasks/00.01.eth-driver/scripts/build_slotA.py`; boot `tftp_boot_mainline.py` (RAM,
  non-destructive). Stock-boot recipe (DTR→cspstart→NAND, SSH admin/UkuGPeyRDU, /bin/fpga -r
  <(phys-0x92000000)/4>): see stock_dn_ring_REMEASURE_re.md.
- Workflow: delegate RE to subagents (write findings to this dir), but VERIFY their address
  claims vs decomp (decomp_all_*.c) + the stock dump (findings/regs/stock_eth_2mib.txt,
  "<phys> <val>" lines) before acting — agents have been wrong on addresses repeatedly.

## Device state right now
Mainline build with `zx_pm_spa_init()` (PM/SPA init), booted (RAM/TFTP), REPL live on :9999,
host on MAC2. Source has this session's TX edits (dual-kick shared-ring zx_sw_xmit + PM/SPA
init) — kept as stock-faithful even though not sufficient. Branch `main`, uncommitted.

## Recommended resume plan
1. Read stock's live SPA match-RAM (hypothesis #1) → replicate it at init in zx_pm_spa_init().
   Test port-agnostic (tcpdump for any device-src frame on the wire).
2. If that egresses → success (update STATE+ROADMAP, write a success finding).
3. If not → it's likely #2 (egress clock/power) or deeper; reassess — clock-tree RE is hard
   and the relevance is uncertain, so weigh it against pausing for a different approach.
