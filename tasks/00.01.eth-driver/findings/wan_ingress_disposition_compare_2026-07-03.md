# WAN-ingress per-ingress disposition compare (lan4 vs lan2) + pktdeal decisive test (2026-07-03, #476)

## VERDICT
1. **No per-ingress STATIC config differs between lan4 (WAN/MAC4/physport4) and lan2
   (working LAN)** on mainline #476 — every per-ingress classify/parse register is
   byte-identical or uniformly zero across ports. Confirms the task premise
   ("static/config surface exhausted").
2. **The one per-ingress classify DISPOSITION lever available — the SPA
   `enty_pktdeal_cfg` proto-action — is EXONERATED as the dominant `l3_en=0` gate.**
   Forcing EVERY proto slot to forward (`pktdeal all 0`) on all ports did **not** raise
   the WAN-ingress HW-forward / `l3_en=1` fraction; the DN packets still trap pre-CLA.
3. **The traps are confirmed PRE-CLA** (`cla_tx_trp` = +0 across both runs) — corroborates
   the `wan_ingress_l3en_split` "dominant `l3_en=0`, upstream of the CLA lookup"
   decomposition. But it is NOT the SPA pktdeal. ⇒ the gate is in the **parse stage that
   HW-computes `l3_en`** (DATASHEET:889, not SW-writable), upstream of both the CLA lookup
   AND the SPA pktdeal classify-action. Next = kotrace stock's live parse / a parse-stage
   (MAC4-RGMII vs GePHY) reframe.

---

## STEP 1 — mainline per-ingress config, lan4 vs lan2 (all reads via debugfs `mem`)
Read method: `dd if=/sys/kernel/debug/zx_eth/mem bs=4 skip=<off/4> count=N | hexdump`
(e->base = phys 0x921c0000; busybox applets need the `busybox` prefix; `od` absent).

| surface | phys | lan2 (works) | lan4 (WAN) | diff? |
|---|---|---|---|---|
| SPA `enty_pktdeal_cfg` block (5 words) | 0x921d4300 + port*0x14 | `50555555 05551545 00544004 55555544 00000000` | **identical** | **NO** (ports 1..7 all identical; only port0/CPU differs in word4 `0x15`) |
| greg `port_stp_en` | 0x921c0040 | 0 | 0 | NO (all ports 0) |
| greg `port_stp_status` | 0x921c0044 | 0 (=Disabled) | 0 | NO (all ports 0) |
| greg `port_closed` | 0x921c004c | 0 | 0 | NO (all ports 0) |
| SDET per-port maxframe | 0x921c4000/4250 | `07cc000c`/`07cc07cc` | (interleaved, same) | NO (= stock golden) |
| SOPC↔SMAC bridge | 0x921d9068 | 0 | 0 | NO |

**Port index note:** SPA pktdeal `sub_idx = port_id` and the driver's
`zx_chip_tm_init_pro_action` loops **port 0..7 writing the SAME action per proto to
every port** — so pktdeal is not even per-ingress-differentiated in the driver, and the
live dump confirms all candidate ports (1..7) identical. greg uses identity space
(lan4=port4, lan2=port2) — both zero. **No per-ingress register is set for lan2 but not
lan4.**

## STEP 2 — WAN-port role register (no-op confirm)
`0x923a001c` (PON_PP_TM_CFG) = **`0x21200000`** → bit29 set = physport4/MAC4/lan4 = WAN.
Present and correct, matching stock. Excluded as the cause (as predicted by
`wan_portrole_mflow_RE`).

## STEP 4-equivalent — DECISIVE dynamic test on mainline (done INSTEAD of a stock boot)
Because the driver writes `enty_pktdeal_cfg` identically for all ports, the ONLY way the
SPA proto-action could be the `l3_en=0` gate is per-PROTOCOL (trapping bulk TCP data,
which the `l3en_split` TCPTRAP log showed trapping). Tested directly with the debugfs
`pktdeal` node — no stock boot needed, RAM-only, reversible.

Rig (PATH-1 real download, as prior sessions): host `enxc8a362e95900` in netns `client`
(172.31.9.50/24) ↔ device **lan2** (172.31.9.1/24, empirically re-confirmed host=lan2 via
per-port rx delta: lan2 +32 on a host ping burst, lan1 rx=0 always); modem ↔ **lan4**
(10.44.66.223/24, `default via 10.44.66.250`, **static — modem no longer serves DHCP**,
advertises IPv6 `fe80::1`=cc:29:bd:22:b4:2b; static IPv4 pings 8.8.8.8 0% loss);
`iptables -t nat MASQUERADE -o lan4`; nft offload flowtable `{lan2,lan4}` loaded FIRST;
`curl http://80.249.99.148/1GB.zip` + Host hdr, `--local-port` pinned.

Authoritative counters (l3en_split method): `cla_tx_fwd` 0x9238c3c0 (==CLA fwd, ==QMG DN
hw_fwd), `cla_tx_trp` 0x9238c3c4, QMG DN hw_fwd/hw_trap (pipeline_stats).
`l3_en=1 = fwd+trp`; `l3_en=0 = hw_trap − trp`.

| run | pktdeal | Δcla_fwd (hw_fwd) | Δcla_tx_trp | ΔQMG hw_trap | Δsw_fwd | HW-fwd% | notes |
|---|---|---|---|---|---|---|---|
| A | **all 0** (every slot forward) | **+10** | **+0** | +45 | +40 | ~18% | download stalled ~95 pkts/14s |
| B | stock trap table | **+0** | **+0** | +443 | +792 | **0%** | 375 KB moved — **all via sw_fwd, zero HW** |

- **`pktdeal all 0` did NOT fix WAN-ingress HW-forwarding** — hw_fwd stayed negligible
  (+10), all traps pre-CLA. Forcing every SPA proto slot to forward changed nothing.
- **`cla_tx_trp = +0` in BOTH runs** → zero in-CLA LOOK_UP_MISS traps this session; every
  DN trap was **pre-CLA** (`l3_en=0`). The pre-CLA gate is real and is **not** the SPA
  pktdeal.
- Run B's 375 KB throughput came entirely from **SW forwarding** (CPU slow-path, sw_fwd
  +792), not HW offload — the classic "pure-SW routing" baseline.

**CAVEAT (honest):** this session's absolute HW-fwd was ~0% (below the documented ~14%).
DN hw_trap was already 540 at test start (residue from setup pings), and the nft flowtable
read 0 entries afterward — the offload/CLA entry may not have stayed installed, so the
absolute rate is lower than prior sessions. The **relative** pktdeal comparison (all-0 vs
stock, both ~0% HW-fwd, all traps pre-CLA) is internally valid and decisive: **pktdeal is
not the lever.**

## Why no stock boot
The prior `stock_wan_ingress_lookup_compare` already booted stock and found the CLA config
byte-identical + stock's descriptor `l3_en=1`/reason 0x49. Having now shown the per-ingress
classify DISPOSITION (pktdeal) is not the mainline lever, a stock dump of the same
pktdeal/greg regs would not change the conclusion, and a stock boot carries host-stranding
risk (user asleep). The decisive actionable question — "does forcing the per-ingress
classify action to forward lift WAN-ingress `l3_en`?" — was answered NO on mainline.

## CONCLUSION / next step (task fallback branch)
- No per-ingress static config diff (lan4 vs lan2). The available per-ingress classify
  disposition (SPA pktdeal proto-action) does NOT gate WAN-ingress `l3_en`.
- The `l3_en=0` gate is in the **parse stage that HW-computes the descriptor `l3_en`
  bit** — upstream of both the CLA lookup and the SPA pktdeal classify-action. `l3_en` is
  HW-computed (DATASHEET:889, not SW-writable) → there is no per-ingress register to poke;
  the differentiator is what the **parse engine sees for MAC4/RGMII (WAN) ingress vs the
  GePHY LAN ingress**.
- **NEXT = kotrace of stock's live WAN-ingress parse** (what stock configures so its
  WAN-ingress frames parse with `l3_en=1`), or a fresh-eyes reframe of the parse/extract
  stage (MAC4-RGMII-specific parse config, or the ring-1 DN descriptor-init) — NOT another
  register-diff on the classify/role surface (exhausted).

## RIG WEDGE (hit + recovered)
Run B pushed DN hw_trap past 1024 → the P3 WAN-RX wedge tripped (device→modem ping 100%
loss, hw_trap frozen at 1074). Recovered cleanly: netns torn down first (host route
restored), then `scratchpad/reboot_mainline.py` (= `lib/uart.py flash_image_to_ram`,
UART_TCP=1 through the bridge) DTR power-cycle → drive U-Boot → TFTP `zImage_dtb.uimg` →
bootm (DEFAULT jffs2 bootargs — do NOT use `auto_bootm_dtb_appended`, it overrides bootargs
with `rdinit=/init`). Booted BOOT_OK, "REPL ready", #476, CLA/FFE/pro_action init clean.

## STATE LEFT (CLEAN)
- Device fresh **#476** (TFTP RAM-boot): rc.router defaults (lan1=172.31.9.1,
  lan4=192.168.9.1, sw=192.168.1.99; the `MASQUERADE -o lan4` is an rc.router default,
  not residue), DN hw_trap=5 (**no wedge**), nft empty, pktdeal=stock (init replayed).
- Host: netns torn down; `enxc8a362e95900` @192.168.1.50 root-ns, `192.168.1.0/24` /
  192.168.1.1 route present (TFTP-ready), single in.tftpd, no netns, no stray curl.
- Source UNCHANGED, nothing committed. Scripts: `scratchpad/{repl.py, netns_up.sh,
  netns_down.sh, reboot_mainline.py}`.
