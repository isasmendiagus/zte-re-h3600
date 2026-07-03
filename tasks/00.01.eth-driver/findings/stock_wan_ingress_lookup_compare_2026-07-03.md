# STOCK vs mainline — WAN-ingress HW-forward lookup compare (2026-07-03)

## VERDICT: the CLA WAN-ingress **lookup config is BYTE-IDENTICAL** stock↔mainline.
The ~86 % mainline WAN-ingress DN miss is **NOT a lookup-config difference** and
**NOT a per-ingress way/bank probe difference** (there is no per-ingress lookup
register — the CLA lookup config is entirely GLOBAL). Ranked leads **(a)** and
**(b)** are REFUTED as the cause. The differentiator is **UPSTREAM of the CLA
lookup**: the DN/WAN-ingress parse-route stage that produces the descriptor
`l3_en` / trap-reason (stock → forward, mainline → LOOK_UP_MISS). This corroborates
the `stock_extraction_config` Synthesis and points at lead **(c)** (the ring-1 DN
parse/pipeline), not the CLA.

---

## Method (non-destructive; NO NAND writes; kotrace-flash deliberately skipped)
- Device was on mainline **#476** (clean). Read its live CLA config first, then DTR
  passive power-cycle → **stock NAND autoboot** (`Linux H3600 V9 4.1.25`, `/bin/fpga`).
- **Stock ground-truth download rig:** host `enxc8a362e95900` = 192.168.1.50 is a LAN
  client of stock `br0` (192.168.1.1); stock WAN = `nbif1`, `default via 10.44.66.250`
  (the modem), internet up (device ping 8.8.8.8 / 80.249.99.148 = 0 % loss). Anti-leak:
  host `ip route add 80.249.99.148/32 via 192.168.1.1 dev enxc8a362e95900` (verified
  `ip route get` → via 192.168.1.1, not wifi). `curl … http://80.249.99.148/1GB.zip`
  (Host: ipv4.download.thinkbroadband.com).
- Stock register reads: `/bin/fpga -r <widx> 1` → `/dev/logger_main` (warmup + batches,
  printk-rate-limit safe) via `scratchpad/stock_wan_capture.py {cfg,ctr}`.
- Mainline reads: debugfs `mem` dd/od (base 0x921c0000).
- Task's kotrace step (step 3) was **skipped by design**: post-boot kotrace on stock is
  possible but the bake-in needs a patched-rootfs NAND flash, which conflicts with the
  hard constraint "Do NOT modify stock NAND." The equivalent "what stock configures"
  evidence was obtained STATICALLY from the stock tm.ko/switch.ko decomp
  (`tasks/00.10.02.re-stock-kmods/findings/decomp_all_{tm,switch}.c`) + live register
  reads on both firmwares — see below.

## GROUND TRUTH CONFIRMED — stock HW-forwards the WAN-ingress download at ~99 %
`cla_tx_fwd` (0x9238c3c0) / `cla_tx_trp` (0x9238c3c4) across a live download:

| | baseline (idle) | during DL (~7 s) | Δ |
|---|---|---|---|
| cla_tx_fwd | 0x0 | **0x6f9d = 28573** | **+28573** |
| cla_tx_trp | 0x147 = 327 | 0x24b = 587 | +260 |

⇒ **stock forwards 28573 / (28573+260) ≈ 99.1 %** of WAN-ingress DN packets.
The `curl` completed the **full 1 GB at 37.2 MB/s** through the stock box. Mainline (all
prior sessions, same rig) forwards **~14 %** (~38–52 B/s crawl). Same box, same modem,
same target, same cabling — **stock is line-rate, mainline is ~14 %.**

## CLA LOOKUP CONFIG — byte-identical (LIVE, both firmwares)
| phys | name | mainline #476 (live) | stock V9 (live) |
|---|---|---|---|
| 0x9238c080 | cla_config | **0x00000600** | **0x00000600** |
| 0x9238c088 | l3_mtu | 0x00007fff | 0x00007fff |
| 0x9238c090 | hash_poly_config | **0x00e400e4** | **0x00e400e4** |
| 0x9238c094 | **outspace_cfg** | **0x00000004** | **0x00000004** |
| 0x9238c098 | up/dn_mtu | 0x7fff7fff | 0x7fff7fff |
| 0x9238c138/13c | dn_multi/broad_flow | 0 | 0 |
| 0x9238c140/144 | up/dn_unicast_flow | 0 | 0 |
| 0x9238c160/164 | up/dn_default_bucket | 0 | 0 |

- **`outspace_cfg = 0x4` on BOTH** → `outer_space_sel = 0`, `outer_hash_num = 1`
  (`cla_set_outspace_cfg(hash_num,space_sel)` writes reg = `space_sel&3 | (hash_num&3)<<2`).
  **There is NO per-ingress-port outspace/hash register** — `cla_set_outspace_cfg` takes
  no port; the outer hash config is a single global register. Lead (a) ("WAN-ingress
  probes a different way-set / bank") has no HW mechanism: the probe config is not
  per-ingress, and it is identical.
- **`cla_config = 0x600` on BOTH** (`cla_set_config` bit map): `v6rd_del_en`(b10)=1,
  `dslite_del_en`(b9)=1; and **all of** `up_unicast_ctrl`(b15)=`dn_unicast_ctrl`(b14)=
  `dn_multicast_ctrl`(b13)=`dn_broadcast_ctrl`(b12)=`trap_acl_en`(b17)=`modify_en`(b16)=
  `age_mode`(b3)=`outport_sel_en`(b2) = **0**. Identical.
- `hash_poly_config = 0x00e400e4` on both (drives the CRC slot calc).

(Only observed live diff: mainline `0x9238c0fc`/`0x100`/`0x104` held `0x9609`/`0x24904111`/
`0x01004851` while stock read 0 — this is **residue** of a prior flow on the long-running
mainline (0x9609 = the last DN raw), not a config difference; stock was a fresh boot.
`up_l2_uni_default_flow` is a default-action reg, not a lookup gate.)

## STATIC INIT PROOF (what stock CONFIGURES — the kotrace answer, obtained from decomp)
- `tm_pon_pp_cla_initial` (decomp_all_tm.c:42727) is stock's CLA init. It reads config,
  then sets **`up_unicast_ctrl=0, dn_unicast_ctrl=0, dn_multicast_ctrl=0,
  dn_broadcast_ctrl=0, mac_req_ctrl=1, v6rd_del_en=1, dslite_del_en=1`** and
  `cla_set_outspace_cfg(2,0)`; `chip_tm_init` (decomp_all_switch.c:265) later sets
  `tm_cla_outspace_cfg_set(1,·)` → **outer_hash_num ends at 1** (0x4). `mac_req_ctrl`(b11)
  is set at init but reads 0 live on BOTH (cleared later). ⇒ stock's programmed CLA lookup
  config == mainline's, exactly, at init AND live.
- **Install mechanism** (`tm_acl_v2.c`, `cla_set_hash_table` callers ~53488/53526): stock
  computes the slot from `cla_get_hash_poly_config` (same poly 0x00e400e4) via
  `aclGetAvailableHashAddr_constprop_13(space 0→1→2)` and installs **one** entry at the
  first-available slot. Mainline writes 5 fixed ways (ram2..ram6). With `outer_hash_num=1`
  the HW probes **only way0/ram2**, which both firmwares populate correctly (mainline's
  entry proven resident+valid at ram2[0x09] with real hits in `wan_ingress_perpacket_key`).
  ⇒ the multi-way vs single-slot install difference is inert; not the gate.

## THE ACTUAL DIFFERENTIATOR — upstream of the CLA lookup (parse-route / l3_en)
Reliable counters say stock's CLA *matches+forwards* ~99 % while mainline's CLA
LOOK_UP_MISSes ~86 % with an **identical config and a correct resident entry**. The only
remaining variable is what the packet looks like when it *reaches* the CLA lookup:
- Stock descriptor latch during forwarding: `desIn2` reason (0x9238c3e8) `[29:23]` moved
  from idle **0x2c** → **0x49 = OTHERS (catch-all → FORWARD)** during the download;
  `desIn3` `l3_en` bit6 = **1**.
- Mainline (prior + DATASHEET:889/ `stock_extraction_config` Synthesis): trapped DN
  descriptor reason **0x54 = LOOK_UP_MISS**, **`l3_en = 0`**.
- (Caveat: the `desIn*` latches are shared/not per-packet — the AUTHORITATIVE signal is
  the fwd/trap counters above; the reason/l3_en are corroborating.)

⇒ On mainline WAN-ingress, ~86 % of DN transit packets arrive at the CLA **without a valid
L3 parse anchor (`l3_en=0`)** → LOOK_UP_MISS → trap; the ~14 % that DO parse (`l3_en=1`)
hit the (correct, resident) entry and forward. Stock parses ~99 % as L3-routable →
forward. This is a **DN/WAN-ingress (ring-1) parse-route problem, not a CLA lookup-config
problem** — matching lead (c), and exactly the "no valid parsed-L3 anchor" mechanism the
`stock_extraction_config` Synthesis predicted.

## AGING (task step 2)
`cla_config` `age_mode` bit3 = **0 on BOTH** stock and mainline ⇒ stock does **not** enable
global aging in cla_config. The per-flow HW activity signal is the per-entry `ram_id 8`
aging bit (already RE'd in `zte-flowoffload-framework` / `stock_ffe_aging_perflow_stats_RE`);
that is the path to make the #476 keepalive conditional, and it is independent of this gate.

## PROPOSED FIX (concrete direction)
**Do NOT change any CLA lookup register** — they are proven identical and correct.
The fix is to make mainline's **WAN-ingress DN (ring-1) datapath deliver packets to the CLA
with `l3_en=1` / a valid L3-parse anchor**, the way stock does. Concretely, on the mainline
side, investigate:
1. The **DN ring-1 ingress/parse path** (SPA/DPA parse-result → descriptor `l3_en`/L3-offset)
   for WAN/RGMII ingress — why does mainline set `l3_en=0` for ~86 % of WAN-ingress DN
   transit frames? (per-packet, since ~14 % do get `l3_en=1`).
2. Read the mainline descriptor `l3_en` (0x9238c3ec bit6) + reason (0x9238c3e8 [29:23])
   for a WAN-ingress DN packet during a download and compare 1:1 with the stock 0x49/l3_en=1
   captured here — that pins whether the fix is a parse-enable, an RGMII-ingress class bit,
   or a ring-1 descriptor-init the DN NAPI path drops.

## STATE LEFT (CLEAN)
- Device **restored to mainline #476** (TFTP RAM-boot via `tftp_boot_mainline.py`,
  "REPL ready", sw=192.168.1.99, WAN up, 5 GePHYs, no nft, no default route, rc.router
  defaults, debugfs OK). No wedge.
- **Stock NAND UNTOUCHED** — read-only fpga access + the standard CLA indirect read cmds
  only; stock WAN/config not modified; device `/tmp/r.bin` removed.
- Host: anti-leak `80.249.99.148/32` route removed, `enxc8a362e95900` @ 192.168.1.50
  root-ns, `192.168.1.0/24` route present, single in.tftpd (TFTP-ready), no netns, no
  lingering curl.
- Driver source UNCHANGED; nothing committed.
- Scripts: `scratchpad/{stock_wan_capture.py, repl.py, stock_read.py, dump_cla_block_stock.py}`.
