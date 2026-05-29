# Per-port STP / forwarding-state register — RE (ZTE ZX279128S)

Decomp-only. Sources: `decomp_all_tm.c`, `decomp_all_switch.c`,
mainline `zx-fpga-reg-tables.h` (authoritative RE'd reg table),
stock dump `regs/stock_eth_2mib.txt`.

## TL;DR
- **Per-port STP/forwarding-state reg = gregRegTable subblk `port+0x2b`**
  (decomp `greg_set_port_stp_rstp_status`, tm.c:22312).
- subblks 0x2b..0x31 (table reg_id 43..49) → **base_off DWORD 0x70011**,
  **mask 0x7, shift = port*3** → all 7 ports packed in ONE word.
- **phys = 0x92000000 + 0x70011*4 = `0x921c0044`** (3 bits/port).
- **FORWARDING = value 4** (0=Disabled,1=Blocking,2=Listening,3=Learning,4=Forwarding).

## 1. Register address + how derived  (CONFIDENCE: HIGH)
Path: switch.ko `sw_mac_set_onu_stpaction` → `zte_api_sw_mac_set_onu_stpaction`
(tm.c:58668) → `spa_set_stp_action` (tm.c:26469) — BUT that is a **global**
action reg (`tmOnuRegWrite(7,action,0,&spaRegTable)`, no port index), NOT
per-port. The **per-port** STP/forwarding state is the `greg_*` group:
- `greg_set_port_stp_rstp_status(port,status)` → `tmOnuRegWrite(port+0x2b, status, 0, &gregRegTable)` (tm.c:22312). This is THE per-port forwarding-state write.
- companions: `greg_set_port_stp_en` subblk `port+0x1d` (tm.c:22190);
  `greg_set_port_sel_stp_rstp` subblk `port+0x24` (tm.c:22252, 0=STP,1=RSTP);
  `greg_set_port_closed` subblk `port+0x39` (tm.c:22444).

Address resolution (`tmOnuRegWrite`→`tmOnuGlbRegValidation` tm.c:35317): entry =
`gregRegTable + subblk*0x1c`; field +8 = fpga reg_id (= base_off), and
`fpga_read_reg(id)=*(0x92000000+id*4)` (tm.c:35369). gregRegTable contents are
initialized data (not in the .c dump) but are RE'd verbatim in mainline
`zx-fpga-reg-tables.h:zx_gregregtable[]`:
- reg_id 43..49 (=subblk 0x2b..0x31): base_off=0x70011, mask=0x7, shift=0,3,6,9,12,15,18 → 7 ports × 3 bits, one word @ **0x921c0044**.
- reg_id 57..63 (=subblk 0x39..0x3f, port_closed): base_off=0x70013, mask=1, shift=port → @ **0x921c004c**.
- reg_id 29..35 (=subblk 0x1d.., port_stp_en): base_off=0x70010 @ **0x921c0040**.

NOTE: the greg block is at e->base = phys **0x921c0000** (NOT 0x9238c000).
⚠ `sopc_egress_port_gate_re.md:131` claimed greg port-state @ 0x9238c14c — that
is WRONG (conflated greg with a PP offset). Corrected here against the
authoritative mainline table + the matching stock-dump word.

## 2. Indexing + port remap  (CONFIDENCE: HIGH)
greg uses **physical port 0..6** (7 ports). Logical→physical remap
(`tm_port_stp_status_set` tm.c:37917): 0→0,1→1,2→2,3→3,4→4, **6→5, 7→6**;
**logical 5 = invalid/rejected** (default case → error). In mainline, CPU port
is **logical 5** (`ZX_CPU_PORT 5`) — so the CPU port has NO greg STP-status
slot; greg ports 0..6 are the LAN/MAC switch ports. MAC2/host maps via the
logical 6/7→physical 5/6 entries. Field offset within the word = phys_port*3.

## 3. Encoding — FORWARDING value  (CONFIDENCE: MEDIUM-HIGH)
3-bit field (mask 0x7). Validation in `greg_set_port_stp_rstp_status`
(tm.c:22300-22322): STP mode (sel=0) accepts status `< 5` → 5 states.
Standard IEEE-802.1D ordering the SDK passes through unchanged
(`tm_port_stp_status_set` switch is identity on the value):
**0=Disabled, 1=Blocking, 2=Listening, 3=Learning, 4=Forwarding**.
=> **FORWARDING = 4**. (⚠ MEDIUM: the literal "Forwarding"/"Blocking" name
strings are not in the decomp printks; encoding inferred from the 5-state
<5 validation + 802.1D convention. The RSTP branch sel=1 has a different
accept set, tm.c:22322.)

## 4. Stock-dump cross-check  (CONFIDENCE: HIGH)
`regs/stock_eth_2mib.txt`:
- `921c0044 00000000` — STP-rstp-status word: **all 7 ports = 0 = Disabled**.
- `921c0040 00000000` — port_stp_en: STP disabled on all ports.
- `921c004c 00000000` — port_closed: all ports = 0 = OPEN (not closed).
- `921c0048 00000000` — sel_stp_rstp.

Interpretation: stock runs with STP **disabled** (stp_en=0), so the
stp_rstp_status field is dormant/0 and forwarding is gated elsewhere (port_closed=0
= all open). There is **no distinct "CPU-port" greg slot** (CPU=logical 5 has no
phys mapping). MAC2/host = phys port 5/6 → also 0. So stock value for CPU-port
and MAC2-port STP-state words = **0x00000000** (STP off, ports open/forwarding by default).

## 5. Does mainline write it?  (CONFIDENCE: HIGH)
**No.** `zx-eth-main.c` never references `zx_gregregtable` (grep: 0 hits) and
never writes 0x921c0040/44/48/4c or calls any stp/port-state setter. The
gregRegTable is defined in the header but unused. Mainline relies on the HW
default (STP off, all ports open) — matching the stock live state — so the
per-port forwarding-state reg is effectively a no-op for the LAN path and does
not need to be programmed to FORWARDING. (The actual CPU↔LAN egress gating in
mainline is done via PP_BRG flood/isolate + sbragRegTable, not greg STP.)
