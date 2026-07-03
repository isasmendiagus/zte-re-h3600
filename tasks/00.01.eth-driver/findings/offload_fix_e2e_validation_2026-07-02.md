# Flow-offload fix — END-TO-END validation on a fresh boot (2026-07-02)

**VERDICT: ✅ The compiled-in fix produces a GENUINE SELECTIVE per-flow HW forward
end-to-end, driven by the DRIVER'S OWN tc-flower install path.** Matching flow
HW-forwards on the wire; non-matching flow traps. Reproduced twice.

Device: mainline **#458** (`Linux (none) 6.6.0 #458 Thu Jul 2 23:20:44 UTC 2026`),
fresh DTR boot, RAM-only, NO reboot after boot.

---

## Build (Step 1) — both driver units rebuilt with the fix

- Confirmed the orchestrator's 3 source edits in place before building:
  - `zx-eth-main.c:2310  zx_ft_pack_cla  cla[3] = 0;`
  - `zx-dsa.c:725        zx_cla_pack_entry cla[3] = 0;`
  - `zx_ffe_table.h:131  zx_ffe_index id=9 word4 = 0x00150001`
- `make -C linux-v6.6 ... O=build all` (built-in zx-dsa → vmlinux; module zx279128-eth.ko).
- Stripped `--strip-debug`, copied the .ko **identically** (md5 `ba4326e4…`) to BOTH
  `/tmp/initramfs_extract/lib/modules/` and `tasks/00.01.eth-driver/initramfs/lib/modules/`.
- `make zImage` (re-embed initramfs) → wrapped `zImage + h3600.dtb` via mkimage to
  `tftp/zImage_dtb.uimg` (14.25 MiB). Build number **#458** (> #456).

## Boot (Step 2) — fresh boot confirmed

- DTR-booted via `lib/uart.py auto_bootm_dtb_appended` (host had 192.168.1.50 + 172.31.9.50).
- Banner `#458 ... 23:20:44` (new). dmesg init markers all present:
  - `SPA trap_dmac filter cleared (match stock; enables HW L3 forward)`
  - `[zx-dsa] PM ops registered by conduit`
  - trap_dmac regs 0x921d41a0..bc all read **0** (verified via memdump).

## Init fix took (Step 3) — ram0[9] armed rule 0x90 at boot

- `clapeek ram0 addr0x9` immediately after boot:
  `93929190 97969594 9b9a9998 9f9e9d9c **00150001** …`
  → word4 = **0x00150001**. Proves `zx_ffe_table.h` change compiled into the module
  and the driver armed rule 0x90 at init.

## Install path (Step 5) — the DRIVER'S tc-flower path fired end-to-end

The kernel lacks `CONFIG_NET_ACT_PEDIT` and busybox `ip` has no `neigh add`, so the
next-hop MAC could not be injected via tc; the driver used its seeded fallback nh-MAC
(this only affects the egress dst-MAC rewrite, NOT the forward decision — both forward
and wire egress are proven below).

- Attaching clsact+flower to the **conduit `sw`** (zx_eth_setup_tc → zx_ft_install_recipe)
  did NOT bind (filter add → `Operation not supported`, cb never fired). The conduit
  flow_block path was not exercised this run.
- Attaching to the **DSA user port lan1** (the standard DSA path, `ds->ops->cls_flower_add`
  = `zx_dsa_cls_flower_add` → `zx_install_l3_recipe` → the fixed `zx_cla_pack_entry`)
  **WORKED**. Commands:
  ```
  tc qdisc  add dev lan1 clsact
  tc filter add dev lan1 ingress protocol ip flower skip_sw ip_proto udp \
     src_ip 172.31.9.50 dst_ip 192.168.9.50 src_port 50010 dst_port 53 \
     action mirred egress redirect dev lan4
  ```
- dmesg (driver built the entry itself — NOT a manual clawrite):
  ```
  [phase6] cls_flower_add port1 ing=1 ... proto=17 172.31.9.50:50010 -> 192.168.9.50:53
  [phase6]   act[0]=REDIRECT dev=lan4
  [phase6] FFE extract armed (ram1[0x98] + ram0[9] fast-enable)
  [phase6] recipe: proto=17 ...:50010->...:53 in_rp=2 eg_rp=5 nh=6c:70:cb:b6:81:69 -> 520/520 CLA buckets
  ```
- CLA entry the driver installed — `clapeek ram2 addr0x0`:
  `03005044 fa11c000 00000608 **00000000** **11000049** 32ac1f00 32c0a809 35c35a09 0…`
  → **word3 = 0** (packer fix compiled in), byte0x10=0x49 + byte0xf=0x00 ⇒
  **extr_index low byte = 0x90** — byte-identical to the proven #456 recipe entry.

## Measurement (Step 6) — selective forward, reproduced

Counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp 0x9238c3c4, MAC4(lan4)-TX 0x92300718.
Flow generated from the host pinned to src 172.31.9.50:50010 → 192.168.9.50, 400 pkts.

| step | cla_tx_fwd | cla_tx_trp | MAC4-TX | result |
|---|---|---|---|---|
| baseline | 0x000 | 0x089 | 0x00a | — |
| +400 **matching** dport **53** | **0x190 (+400)** | 0x089 (flat) | **0x19a (+400)** | **HW FORWARD** |
| +400 **non-match** dport **5555** | 0x190 (flat) | 0x223 (+410) | 0x19a (flat) | **TRAP (selective)** |
| +400 **matching** dport **53** (2nd) | **0x320 (+400)** | 0x229 (+6 bg) | **0x32a (+400)** | **HW FORWARD (reproduced)** |

- Matching flow: cla_tx_fwd climbs **exactly +400** AND MAC4/lan4 wire-TX climbs
  **exactly +400**, trap FLAT — packets physically egressed lan4 in hardware.
- Non-matching flow (same src/dst IP + sport, only dport differs): forward + wire-TX
  FLAT, trap climbs — genuine content-selective 5-tuple hash hit, not a catch-all.

## Notable: ram0[9] = 0x00150151 also forwards (zx_ffe_arm concern resolved)

`zx_dsa_cls_flower_add` calls `zx_ffe_arm()` (zx-dsa.c:671) which **rewrites ram0[9]
word4 → 0x00150151** (re-enabling rules 0x94/0x96/0x98 alongside 0x90), overwriting the
init's 0x00150001. Live readback after install confirmed ram0[9] = **0x00150151**.
This does **NOT** break forwarding: rule **0x90** (v4-5tuple, bit0) stays enabled and is
the rule the HW selects for a clean v4 UDP 5-tuple, so the entry's extr_index 0x90 still
matches → the selective forward above happened with ram0[9]=0x00150151. ⇒ **The decisive
fix is the packer `word3=0` (extr_index=0x90); forcing rule 0x90 via ram0[9]=0x00150001
is NOT required for this flow.** (The `zx_ffe_arm` 0x00150151 write is therefore benign
for v4-5tuple offload; it could be tidied to 0x00150001 for consistency, but it is not a
blocker.)

## tc-flower status (what works / what's missing for full auto-offload)

- WORKS: DSA user-port flower offload (`tc filter add dev lanN ingress flower skip_sw …
  action mirred egress redirect dev lanM`) → driver builds+writes the CLA/PM recipe itself
  and HW-forwards selectively. This validates the built-in `zx-dsa` packer fix compiled in.
- Missing for a fully-automatic offload from userspace tc:
  1. `CONFIG_NET_ACT_PEDIT` is **not set** in the build .config, so the NAT/eth-dst-rewrite
     next-hop MAC cannot be supplied via `tc pedit`; the driver used a seeded fallback MAC.
     Enable NET_ACT_PEDIT (or populate the egress neigh) to control the wire dst-MAC.
  2. Attaching clsact/flower to the **conduit `sw`** does not bind the driver's
     `zx_ft_setup_cb` block (filter add → EOPNOTSUPP). Only the DSA user-port
     `ds->ops->cls_flower_add` path is currently reachable from userspace tc. The intended
     conduit `TC_SETUP_FT` (nf_flow_table/conntrack) auto path was not exercised here.
  3. The zx-eth-main.c `zx_ft_pack_cla` packer was not directly exercised (conduit block
     didn't bind), but it is source-identical to the validated zx-dsa packer (both cla[3]=0).

## State left behind (device healthy, NO reboot)

- Device on **#458**, alive; UART bridge running (ports 9998/9999). Console loglevel 8.
- lan1 clsact + flower offload rule left installed (forwarding the test 5-tuple); CLA
  520-bucket entry present. Other traffic traps normally (verified). Datapath healthy.
- Host rig intact: enxc8a362e95900 has 192.168.1.50/24 + 172.31.9.50/24; route
  192.168.9.0/24 via 172.31.9.1; static ARP 172.31.9.1→f4:f6:47:0f:42:64.
- ram0[9] = 0x00150151 (driver's zx_ffe_arm value; forwards fine). Not committed.
