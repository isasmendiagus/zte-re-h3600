# Session 2026-05-25 — full findings + path forward

End-of-day consolidation of everything learned. Supersedes the morning's
`session_2026-05-25.md` (which is preserved for the chronology).

## Code state at end-of-day

| Commit | Subject | What's in it |
|---|---|---|
| `f496dc853` | workflow: fix silent build-pipeline drop + unreliable boot DTR | `build_slotA.py` auto-refresh, `tftp_boot_mainline.py` atomic DTR + wait_for_marker, `docs/ITERATE.md` update |
| `ff0327bdd` | eth: bp_idx 10-bit + BMU credit fix + STATS dump + SBRAG helpers (gated) | All driver `.c` changes today. SBRAG flood-policy experiment is in this commit (gated by call site in probe) — pending revert in the next iteration. |
| `d5b8a3fe8` | re: 3 more .ko decomp + function index + session_2026-05-25 findings | This doc + `dump_all_concat.py` + `decomp_all_{shellproc,patch,kudp}.c` + `ALL_KMOD_FUNCTIONS.txt` + `FUNCTION_INDEX.md` |

The driver runtime state described below ("RUN1 10% / 0 DUPs" etc.) is
what you get when you check out `ff0327bdd` and rebuild via the
`build_slotA.py` from `f496dc853`. To go back to the last "pre-broken-
flood-policy" state without reverting fully, see the "Concrete next
steps" section below — step 2 is just removing one call line.

## TL;DR

- **TX path works**. 48/50 echoes returned in RUN3 of a 50-ping burst. The
  "loss" we kept chasing was an artifact; the real problem is duplicates
  (158+ DUPs by RUN3) — the same packet reaching the host multiple times.
- **The DUPs explanation is unverified.** Five agents agree the most
  plausible cause is the switch FDB lookup being un-armed → unknown-DA
  fallback → flood, BUT this has never been confirmed by `tcpdump -e`
  on the host. The "switch flood" story is hypothesis, not observation.
- **Build pipeline + boot script were silently broken** for the first
  half of the day. Both fixed; doc updated.
- **The replay (`fpga.bin`, 22 363 writes from another unit) is the
  meta-bug.** Round-2 reviewer named it; it's still in the code. Every
  register-write hypothesis we test is layered on top of that swamp.
- **Concrete next experiment** (consensus across 5 agents):
  (a) `tcpdump -eni` on host during a 50-ping burst to *observe* DUP
      structure (src-MAC, ingress port, timestamp delta);
  (b) extract stock DTB from `tftp/zImage_dtb.bin` to rebuild the
      `fpga_base → physical` translation table;
  (c) THEN port the `tm_pon_pp_initial` init burst (decomp_all_tm.c
      L43597-43643) — the missing FDB-lookup-arm + aging-cycle setup.

---

## What got fixed (real wins, kept in the repo)

| Fix | Before | After | Where |
|---|---|---|---|
| `tftp_boot_mainline.py` DTR reliability | 300 ms client-side pulse via TCP wrapper, racy | Atomic DTR_HIGH→sleep(2s)→DTR_LOW via bridge ctl port 9998 | `tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py` |
| `tftp_boot_mainline.py` TFTP wait | Fixed 120 s sleep — too short on retransmit, would inject bootm mid-stream | `wait_for_marker("Bytes transferred", 300 s)` polled in bridge log | same |
| `build_slotA.py` initramfs refresh | `make zImage` silently re-embedded the stale `.ko` because `make` didn't detect the .c change. Lost ~1.5 hours of false experiments. | Auto-detect .c→.ko staleness, rebuild .ko, copy to `/tmp/initramfs_extract/lib/modules/`, rebuild zImage | `tasks/00.01.eth-driver/scripts/build_slotA.py` step 0 |
| `bp_idx` decode in NAPI | 7-bit (`desc[7]>>1`) — dropped garbage to IP stack when `bp_idx >= 128` | 10-bit (`(desc[7]>>1) \| (desc[8]<<7)`) per stock `pon_tm_net_poll` L8754 | `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c` napi_poll |
| BMU credit refill | `(tm[0x80dc] >> 8) & 0x3f` gave 1 credit | `(tm[0x80dc] >> 3) & 0x3f` per stock L5842; gives ~34 | same, `zx_bmu_free_bp` |
| Periodic STATS dump | One-shot at 30 s | Periodic 5 s tick; one compact line; correlatable with ping-run boundaries | same, `zx_bmu_dump_fn` |
| `docs/ITERATE.md` | Documented the old broken boot command | Documents the new boot script + bridge prerequisite | `docs/ITERATE.md` |
| `tasks/00.10.02.re-stock-kmods/findings/ALL_KMOD_FUNCTIONS.txt` | didn't exist | 16 334-line index of every symbol in every stock .ko via `arm-linux-gnueabi-nm` | new file |
| `tasks/00.10.02.re-stock-kmods/findings/FUNCTION_INDEX.md` | didn't exist | Coverage table + prefix index + grep recipes | new file |
| Ghidra decomp of 3 more .ko | only 5 .ko (tm/switch/plat/idmfdb/zx_ponreg) | now 8 — added `shellproc`, `patch`, `kudp` (`ghidra/dump_all_concat.py` orchestrates this) | new `decomp_all_{shellproc,patch,kudp}.c` |

## What got tested and gave NO useful signal

These are the "experiments that wasted cycles because of the build-pipeline
bug" — listed only so we don't redo them blindly.

- BMU `pp_bmu_free_bp` call on every consumed RX → double-free → 100 %
  loss (since reverted; the function code is kept, the call is gated).
- Conditional `pp_bmu_free_bp` only on LOOPBACK drops → no effect on
  symptom (still degraded RUN2+).
- Dynamic FDB learning disabled → no effect on DUPs.
- `zx_fdb_add` using CRC-16/XMODEM hash (vs IBM) → tests inconclusive,
  the kernel running was actually the old stale .ko for most of these.
- `zx_sbrag_add_mac` write to `fpga_base + 0x388814` → wedged PP block
  silently — that physical address is NOT what we thought.
- `zx_sbrg_set_unknown_unicast_flood_policy(e, 0x20)` (bitmap CPU-only at
  PP[0x8340] bits 24..31) → made DUPs WORSE (RUN3 went from 158→321),
  because PKTDEAL=0 (drop) was overlaid by accident.

## Test data we actually have (real kernel, real fresh boot)

Three 50-ping runs back-to-back, 10 s apart, then 30 s idle before RUN3:

| Build | RUN1 loss / dups | RUN2 loss / dups | RUN3 loss / dups |
|---|---|---|---|
| baseline (post build-pipeline-fix) | 10 % / 0 | 6 % / 95 | 4 % / 158 |
| + flood-policy PP[0x8340]=0x20000000 (broken) | 18 % / 87 | 10 % / 154 | 2 % / 321 |

Pattern: as more frames flow, DUPs grow, *loss* falls (because more
copies = more chance one arrives intact). The fundamental signal is
**DUPs always > 0 by RUN2 and grow with traffic**.

## What the 5 agents found

We spawned 5 separate agents today for fresh perspectives. The
consensus is striking.

### Agent 1 — RE deep-dive on `sbrg_set_unknown_unicst_*` family
- My `PKTDEAL=1` understanding was wrong. The value `1` means
  **"normal lookup"**, not "flood" (0=drop, 1=lookup, 2=trap-CPU,
  3=flood).
- My `FWD=0x20` (only CPU enabled) **DISABLED** lookup on LAN ports,
  pushing every unknown-DA to the fallback action → flood, explaining
  why the experiment made DUPs worse.
- Real fix-path he proposed: **arm the MAC FDB lookup**.
  - `cla_set_mac_req_ctrl_config(1)` (global)
  - `sbrg_set_pt_da_lookup_en(port, 1)` for each port
  - `cla_set_dn_unknown_da_action_cfg(1)` (fallback action = trap-CPU, NOT
    flood). (Note: agent 4 later corrected `0x600` to `1` here.)

### Agent 2 — Strategic / pivot question
- **Stay on mainline, hard cap one more focused experiment.**
- MAC-lookup-arm is necessary but **probably not sufficient** —
  there's still the unknown sbrag physical address that needs RE.
- Pivot to T9.01 stockport would discard real wins (RX/TX/NAPI/build
  pipeline/boot script/all decomp data) and still leave us at the same
  unknown address.
- Verdict: one more cycle. If sbrag is located + FDB armed + DUPs
  persist → **then** pivot.

### Agent 3 — Code-review pass for subtle bugs
Found 20 concrete bugs (`B1..B20`). High-confidence ones:
- **B10/B11/B20**: `pp_bmu_free_bp` is **required** per stock decomp
  (L8819, L8788, L8703). Our "HW auto-recycles on desc-ack" theory is
  contradicted by stock. The earlier double-free disaster was from
  calling it on the wrong path (probably loopback drops with wrong
  SOP semantics), not from the call being categorically wrong.
- **B7**: Missing `dma_rmb()` / `net_invalid_cache` on RX desc reads.
  ARM Cortex-A9 with non-coherent DMA → we may read partial / stale
  desc → mis-decode `bp_idx`/`len` → misread BP → garbage delivered →
  DUPs amplification.
- **B6**: Same for BP buffer reads before `memcpy(skb_put(...), bp+16, len)`.
- **B1**: TX `tx_head` wraps without checking `tx_done`. After 1024
  TX we silently overwrite descs HW hasn't consumed → HW may re-fetch
  the mutated desc with stale `bp_idx` + new `len` → DUPs.
- **B18**: TX desc `port` hint hardcoded to 0. Stock encodes it as
  `((lan_up_port + 0x28) & 0x3f) << 4`. May need to be 5 (CPU).
- **B16/B17**: IRQ unmask race + non-atomic RMW on `IRQ_MASK`. Could
  starve NAPI under load.

### Agent 4 — Stock init-sequence diff
- **Kotrace only covered switch.ko (chip_tm_init sub-tree). tm.ko's
  own modprobe path was NEVER captured.** Stock's `tm_pon_pp_initial`
  (decomp_all_tm.c L43597-43643) runs at tm.ko load — BEFORE
  chip_tm_init — and contains the **golden init burst**:
  ```
  sbrg_set_macaddr_age_en(1)
  tm_mac_aging_cycle_set(300)
  for port in 0..7:
      sbrg_set_pt_learn_mode(1, port)
      sbrg_set_pt_da_lookup_en(port, 1)         ← THE missing flood gate
      sbrg_set_unknown_unicst_fwd(port, 0)
      sbrg_set_pt_tls(port, 0)
  // overrides for port 0:
  sbrg_set_unknown_unicst_fwd(0, 1)
  sbrg_set_pt_tls(0, 1)
  ```
- **`cla_set_dn_unknown_da_action_cfg = 1`** (not `0x600` as Agent 1
  initially said — that was `r1`, an unrelated arg). The function clamps
  `act_val ≤ 3`, so the only meaningful value is 0/1/2/3.
- **`cla_set_mac_req_ctrl_config(0)`** — stock calls with arg `0`
  (DISABLED globally). So MAC lookup isn't done at this gate; it's
  done per-port via the sbrg path.
- Several other registers we miss: `tm_mac_da_look_ena_set(port, 1)`
  (also `da_look_ena` per port from tm.ko), `tm_mac_learn_mode_set`,
  `sbrg_set_pt_smac_look_en`, `zte_api_sw_other_set_onu_mtu(port, 2000)`.

### Agent 5 — Side-by-side stock TX/RX byte-level comparison
- **`pp_bmu_free_bp` MUST be called per consumed RX BP** (#7). Stock
  does both `soft_release_rx_desc` AND `pp_bmu_free_bp`. Our comment
  "HW auto-recycles on desc-ack" is provably wrong.
- **Stock writes the frame at BP offset +0, NOT +16** (#6). Our `+16`
  is empirical; the "16-byte HW prefix" we observe in RX BPDUMPs may
  be from BPPE pool overlap (i.e. reading the wrong `bp_idx` and
  getting padding from an adjacent BP), not a true HW header.
  **This is potentially a fundamental layout misunderstanding.**
- **Stock has TWO RX rings per queue** (#10). Our impl services
  only ONE. We may be missing half the RX descriptors.
- **No `dma_rmb()` / cache invalidate on RX desc reads** (#8) — same
  finding as Agent 3 B7.
- **No `dma_sync_for_cpu` on BP reads** (#9) — same as Agent 3 B6.
- **No TX ring-full check / no `tx_done` consumption** (#4) — same as
  Agent 3 B1. Stock has `pon_tm_get_next_txdesc` with explicit
  outstanding-count + check.
- Stock distinguishes SOP vs continuation in `tm[0x4068]` bit 3.
  Our `zx_tm_release_rx_desc_raw` always sends `sop=1`. For
  single-buffer packets this is OK, but combined with the missing
  `pp_bmu_free_bp` it likely explains the slow BP leak.

### Agent A (holistic HW audit)
- **The golden init burst is `tm_pon_pp_initial`** (same conclusion
  as Agent 4, arrived at independently).
- IDM block: `idm_fdb_hook_xmit` is stock's pre-HW SW port-selection.
  We bypass it and let HW decide. With FDB lookup not armed (Agent 4)
  → HW always picks flood.
- 4 missing IRQs (PP/NPP/IDM/PON). Only TM GIC 68 wired. PP IRQ may
  signal FDB-miss events that stock services for learning.
- MAC4 (RGMII external) is in the flood set by default. On H3600 the
  RGMII pin probably floats / has no peer, so this is harmless on this
  unit — but it's an unbounded variable.
- MDIO: we never touch it. GEPHYs were initialized by U-Boot; we never
  re-init or observe link state. If a port flaps, we'd silently keep
  flooding to it.

### Agent B (RE coverage audit)
- **HUGE surface untapped:**
  - **`cspd`** — 2.8 MB unstripped ARM ELF, the userspace daemon that
    actually programs the switch via `/dev/zx_ponreg` ioctls. NEVER
    decompiled. This is where `wanLogicPort`, `tm_set_p2pmode`, all the
    per-deployment config gets pushed.
  - **`fpga`** — 5.9 KB ARM ELF user tool for `/dev/zx_ponreg`. NEVER
    decompiled. Would expose the ioctl protocol so we could script
    live HW reads on the stock device.
  - **Vendor PDF** — `ext/ZTE_ZXIC ZX279128S ONU 芯片 硬件手册 V1.0
    2018.pdf` — the OFFICIAL hardware reference manual (Chinese).
    **Never opened.** May contain the canonical register map.
  - **Stock DTB** — embedded in `tftp/zImage_dtb.bin`, never extracted
    and diff'd against our DTS. Would give canonical `reg = <...>`
    cells for `pon`/`npp`/`pp`/`tm`/`idm` nodes (9 ioremap regions in
    stock vs 1 in our mainline).
- **Runtime paths never kotraced:** `pon_tm_data_raw_send`,
  `pon_tm_net_tx`, `pon_tm_net_poll`, `zx_pon_pp_int`, `idm_net_int`,
  `tm_pon_pp_brg_initial`. Kotrace today covers init only.

### Agent C (holistic systems audit)
- **The replay (`fpga.bin`) is the meta-bug.** 22 363 writes from
  another unit (different MAC, different DDR map) layered on top of
  our explicit init + dynamic FDB learn + post-replay pointer re-patch
  = a state space that's not mentally simulable. **Every hypothesis we
  test is layered on this swamp; until it's deleted, no register-write
  experiment is falsifiable.**
- **`fpga_base ≠ eth@921c0000`** — stock has 9 ioremap regions (`pon`/
  `top_crm`/`sys_ctrl`/`pin_mux`/`pon_serdes` + `npp`/`pp`/`tm`/`idm`),
  mainline has 1. Today's SBRAG wedge was the first destructive
  manifestation; it will keep happening until we rebuild the
  translation map. The decomp tables (`base_dword`, `sbragRegTable`)
  are encoded in an address space we have not mapped.
- **"DUPs = switch flood" is hypothesis, not observation.** Host has
  one cable. A flood inside the chip cannot magically appear 3× on a
  single wire. Untested alternatives: CPU-port loopback that escapes
  our LOOPBACK heuristic → kernel IP regenerates reply; dynamic learn
  flipping routing mid-frame; BMU bp double-read (the missing
  `pp_bmu_free_bp`). `tcpdump -e` on the host would resolve this in
  30 s and we never did it.
- **DSA refactor** is the right long-term architecture (5-port HW
  switch with a CPU port — exactly what `drivers/net/dsa/mt7530.c`
  models). Comparable effort to completing the current approach.
  Defer until a stable monolithic baseline exists.
- **24-hour DONE definition:**
  1. Delete `fpga.bin` replay entirely. See what breaks.
  2. `tcpdump -eni` during a 50-ping burst; classify DUPs by src-MAC
     and arrival timestamp delta. Write the answer.
  3. Rebuild the `fpga_base → physical` map by extracting the stock
     DTB and diffing against ours.

## Module decomp added today

| Module | Funcs | Outcome |
|---|---|---|
| `shellproc.ko` | 72 | Generic shell-via-/proc (`/proc/shell` + utilities for `dump_task_fd`, `get_ksyms_address`, `usyms_lookup_*`). **NOT** the live-HW-state dumper Agent B hoped for. Of limited direct use but a possible debug entry. |
| `patch.ko` | 15 | Runtime kernel patcher; the function it patches is `__l2c210_op_pa_range` (PL310 L2 cache controller). **STRONG HINT** that this SoC has a known cache-coherency erratum that the vendor works around. **This corroborates Agents 3 B6/B7 and 5 #8/#9**: missing `dma_rmb()` / `dma_sync_single_for_cpu` in our driver could be exactly the bug. |
| `kudp.ko` | 45 | Voice/RTP UDP packet tracer (`udp_add_media`, `udp_rtptrace_*`, `udp_tx_data`). VoIP-only. **Not useful** for the eth path. |

Files now at:
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_shellproc.c` (77 KB)
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_patch.c` (5 KB)
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_kudp.c` (32 KB)
- New script `ghidra/dump_all_concat.py` (generates these — reusable on any imported .ko)

## What's pending in the driver (uncommitted right now)

- `zx_bmu_free_bp` function defined but never called (lines ~2389-2413
  of `zx279128-eth.c`). Earlier call site reverted.
- `zx_sbrag_add_mac` defined but unused; addresses (0x388014..0x388024)
  are PROBABLY correct (same physical address as `PP_BRG_RAM_*` per the
  math check) — the only thing that made the earlier test wedge was a
  typo (`0x388814` instead of `0x388014`). Now reverted to `0x388014`.
- `zx_sbrg_set_unknown_unicast_flood_policy(e, 0x20)` call exists in
  probe path and currently writes `PP[0x8340] = 0x20555500`. **This
  was the broken experiment Agent 1 identified.** Should be reverted
  to NO call OR rewritten to also enable per-port DA-lookup.
- `zx_sbrg_hash` (CRC-16/XMODEM, 8-byte reversed mac+vlan) defined but
  `zx_fdb_add` uses the OLD `zx_crc16` (IBM polynomial). The reverted
  state isn't fully baseline.

## Concrete next steps (consensus across all agents)

Ordered by ROI / safety.

### 1. Observe the DUPs before chasing them (~5 min, ZERO risk)
On the host, before next ping test:
```bash
sudo tcpdump -eni eth0 'icmp' -w /tmp/dups.pcap &
ping -c 50 -i 0.3 192.168.1.99
# in another window:
tcpdump -ner /tmp/dups.pcap | head -30
```
For each ICMP echo seq number, count the replies and note source MAC
+ arrival timestamp delta. If all DUPs have the same src-MAC and are
~0 ms apart → flood from a single egress. If different src-MAC or
larger deltas → CPU loopback re-TX or HW responder. **Until we know
which, every "FDB fix" is a guess.**

### 2. Restore the driver to known-good baseline (~10 min)
- Revert the `zx_sbrg_set_unknown_unicast_flood_policy(e, 0x20)` call
  in probe to NO call. The PKTDEAL=0 default may be wrong but our
  attempt to "fix" it was worse.
- Confirm 10 % / 0 DUPs RUN1 result reproducible.

### 3. Apply the safe code-review fixes (~30 min)
From Agent 3 + Agent 5:
- **B7**: `dma_rmb()` before reading RX desc bytes. One line; pure
  correctness; possibly addresses the patch.ko-confirmed L2 cache
  erratum.
- **B6**: `dma_sync_single_for_cpu(e->dev, bp_dma + bp_idx*BP_SIZE,
  len, DMA_FROM_DEVICE)` before `memcpy` from BP buffer.
- **B18** (optional): change TX desc `port` hint from 0 to 5 (CPU).
  One line; either fixes or breaks RUN1 within one test cycle.

### 4. Port the `tm_pon_pp_initial` init burst (~1 h)
Verbatim from `decomp_all_tm.c` L43597-L43643. Specifically:
- `tm_mac_aging_cycle_set(300)`
- `sbrg_set_macaddr_age_en(1)`
- For port 0..7:
  - `sbrg_set_pt_learn_mode(1, port)`
  - `sbrg_set_pt_da_lookup_en(port, 1)`
  - `sbrg_set_unknown_unicst_fwd(port, 0)` then override port 0=1
  - `sbrg_set_pt_smac_look_en(port, 1)`

All resolve to writes against `sbragRegTable` — physical address window
already verified (PP_BRG_RAM_* base, +0x8014/+0x8018/+0x801C/+0x8020/
+0x8024 for CMD/BUSY/D0/D1/D2). Use the existing `zx_brg_ram_set` /
`zx_brg_ram_get` (they implement the indirect protocol identical to
stock's `sbrg_set_indreg_wr` once given the right ram_addr/mem_id).

### 5. The deeper experiments (only if 1-4 don't get to clean ping)
- Extract stock DTB from `tftp/zImage_dtb.bin` via
  `binwalk` + `dtc -I dtb -O dts`. Compare to ours.
- Decompile `cspd` (2.8 MB) in Ghidra — most likely contains the
  per-deployment config writes (`wanLogicPort`, hash mode, table sel).
- Read the Chinese vendor PDF for canonical register map.
- Kotrace `pon_tm_net_tx` + `pon_tm_data_raw_send` during stock ping —
  capture the actual TX desc bytes and BP write address.

### 6. Pivot decision
If after steps 1-5 we still have DUPs → **pivot to T9.01 linux-stockport**
or refactor as a Linux DSA driver. The current monolithic approach has
demonstrated TX functionality; if the FDB / flood story still can't be
nailed down with all of the above, the cause is likely deeper than RE
of a single API surface and a different architecture is justified.

## Pointers / cited paths

- Driver: `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`
- Today's tested boot script: `tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py`
- Today's build pipeline: `tasks/00.01.eth-driver/scripts/build_slotA.py`
- Function index (all .ko): `tasks/00.10.02.re-stock-kmods/findings/{ALL_KMOD_FUNCTIONS.txt, FUNCTION_INDEX.md}`
- Stock decomps: `tasks/00.10.02.re-stock-kmods/findings/decomp_all_*.c`
  (now 8 modules)
- Block diagram (shared by user): `refs/zte-block-diagram-from-user.png`
  (described inline in this doc + `session_2026-05-25.md` original)
- Architecture data flow: `tasks/00.01.eth-driver/findings/ARCHITECTURE_FLOWS.md`
- Round-1 and round-2 reviewer notes:
  `tasks/00.01.eth-driver/findings/independent_review_{,round2_}2026-05-24.md`
- HW blocks inventory: `tasks/00.10.02.re-stock-kmods/findings/HW_BLOCKS_INVENTORY.md`

## Key files referenced from stock decomp

- `decomp_all_tm.c:43597-43643` — `tm_pon_pp_initial` (the golden init burst)
- `decomp_all_tm.c:6987-7100` — `sbrg_set_unknown_unicst_*` family
- `decomp_all_tm.c:6228` — `sbrg_set_pt_da_lookup_en`
- `decomp_all_tm.c:8204` — `sbrg_hash` (CRC-16/XMODEM)
- `decomp_all_tm.c:10706` — `sbrg_add_mactable`
- `decomp_all_plat_zxylzb_9128S.c:5821` — `pp_bmu_free_bp`
- `decomp_all_plat_zxylzb_9128S.c:6596` — `pon_tm_data_raw_send` (stock TX)
- `decomp_all_plat_zxylzb_9128S.c:8703` — `pon_tm_net_poll` (stock RX)
- `decomp_all_patch.c` — patch.ko's `l2x0_patch` (cache erratum workaround,
  supports the hypothesis that we're missing cache barriers)
