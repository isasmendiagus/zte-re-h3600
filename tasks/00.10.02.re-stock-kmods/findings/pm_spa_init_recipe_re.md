# PM + SPA init recipe — exact writes mainline must add to replicate stock CPU→physical egress (2026-05-28)

DECOMP + STOCK-DUMP cross-check only. Did NOT touch device/build/git.
Companions: `cpu_source_port_egress_re.md`, `MACRO_review_tx_egress.md`,
`sopc_spa_cpu_egress_re.md`.

## Ground rules / address model (verified)
- `fpga_read_reg(id)/fpga_write_reg(id) = *(0x92000000 + id*4)`.
- `tmOnuRegWrite(reg_id, val, idx, table)` (decomp tm:35358): entry is 0x1c bytes,
  `+8`=base_off, `+0xc`=mask, `+0x10`=shift, `+0x14`=stride. It does a **RMW**:
  `phys = 0x92000000 + (base_off + stride*idx)*4`,
  `*phys = (*phys & ~(mask<<shift)) | ((val & mask)<<shift)`.
- Reg-table base_offs from `linux-v6.6/.../zx-fpga-reg-tables.h`:
  `zx_pmregtable` @365, `zx_sparegtable` @629.
- Mainline driver maps `e->base = 0x921c0000`; `npp_write(e,off,val)=writel(val,
  e->base+off)` (zx-eth-main.c:391). So **NPP-relative off = phys − 0x921c0000.**
- Every row below is tied to a decomp line AND a `regs/stock_eth_2mib.txt` line.

---

## A. The PM (G.988 port-mapper) block — `tm_pon_npp_pm_initial` (tm:43376)

Trace (all RMW via `tmOnuRegWrite`, all DIRECT MMIO — no indirect protocol used by
the initializer; the PM indirect cmd/done/data block at reg0/1/2 = 0x921e0014/18/1c
is only used by `pm_add_g988_rule`, which `pm_initial` never calls, so the g988
rule-RAM at 0x921e0248 stays 0 — confirmed `921e0248 00000000`):

| # | decomp setter (line) | reg_id / base_off | phys | RMW value | stock-dump line | kind |
|---|---|---|---|---|---|---|
| A1 | `pm_set_in_port_rule_valid(i,i,0)` i=0..7 (tm:23061, called tm:43391) | 6 / 0x78060 stride1 | 0x921e0180+i*4 | val=`i\|0<<3` = i | `921e0180..019c = 0..7` ✓ | direct RMW |
| A2 | `pm_set_out_port_rule_valid(i,i,0)` i=0..7 (tm:23147, tm:43392) | 7 / 0x78068 stride1 | 0x921e01a0+i*4 | val=`i\|0<<3` = i | `921e01a4..01bc = 1..7` ✓ | direct RMW |
| A3 | `pm_set_g988_mode(0,0)/(1,1)/(2,3)` (tm:22911, tm:43397-9) | 3 / 0x78015 stride1 | 0x921e0054/58/5c | bits2-3 = 0 / 1 / 3 | `921e0054 b2-3 = 0` ✓ | direct RMW |
| A4 | `zte_api_set_port_rule({1,1,5})`→`tm_pm_port_rule_set`(tm:47679)→`tm_pm_port_get(5)=0`(tm:47642)→`pm_set_port_cfg({1,1,0})`(tm:23422, out-branch)→`pm_set_out_port_rule_valid(0,0,1)` | 7 / 0x78068 idx0 | **0x921e01a0** | **val=`0\|1<<3` = 0x08** | **`921e01a0 00000008`** ✓ | direct RMW |
| A5 | `zte_api_set_g988_cpu_not_drop_staen(0)` (tm:22992, tm:43407) | 5 / 0x78015 sh4 | 0x921e0054 b4 | bit4 = 0 | `921e0054 b4 = 0` ✓ | direct RMW |
| A6 | `zte_api_set_g988_inport_equal_outport_staen(1)` (tm:23027, tm:43408) | 0x10 / 0x78015 mask3 sh7 | 0x921e0054 b7-8 | **bit7 = 1** (val 1 → `1<<7`=0x80) | `921e0054 = 0xc0` (b7=1) ✓* | direct RMW |

Net composite at **0x921e0054**: pm_initial sets b4=0, b7=1 → **0x80**.
Stock-live is **0xc0** (b6 AND b7). *bit6 (0x40) is NOT produced by pm_initial — it
is unmapped at base 0x78015 in `zx_pmregtable` (only sh2/4/5/7 exist) and is set by
power-on default or another subsystem. **FLAG/UNRESOLVED (below).** For faithfulness
write the literal stock value 0xc0 rather than only 0x80.

**Load-bearing for CPU→physical egress (the actual gate):**
- **A4** (`921e01a0 = 0x08`): enables the OUT-port forwarding rule for physical
  port 0 (valid_en bit3). This is the one enabled rule; all others stay invalid.
  This authorises a forwarding-pair whose OUT port is physical 0. **HIGH** this is
  the core authorizer.
- **A6** (`921e0054` bit7 inport_equal_outport_staen=1) + **A5** (bit4
  cpu_not_drop=0): control how the fabric treats a frame whose computed in-port ==
  out-port (the CPU-hairpin case the experiment shows) and the cpu-drop policy.
  **HIGH** that this pair governs the loop-to-CPU symptom.
- A1/A2/A3 are **state-priming/cosmetic** — they put the rule arrays into the known
  identity-invalid baseline (en=0) and set the 3 match modes; they don't open
  egress by themselves, but A4 assumes A2 ran first (it overwrites idx0).

**Caveat (physical-port index, MEDIUM):** A4 enables physical port **0** (logical
CPU port 5 → phys 0 via `tm_pm_port_get`). Whether MAC2/the host's egress port is
physical 0 on THIS unit is NOT provable from decomp; verify by diffing live
`0x921e01a0..01bc` on mainline-vs-stock and setting bit3 on the host's egress idx.

---

## B. The SPA source-port classifier — `tm_pon_npp_spa_initial` (tm:43271)

| # | decomp (line) | reg_id / base_off | phys | value | stock-dump | kind |
|---|---|---|---|---|---|---|
| B1 | `spa_set_up_reg_pkt_en(i,1)` i=0..0x4d (tm:26271, tm:43301) | 0 / 0x75000 stride1 (idx by i/32) | 0x921d4000..400c | per-bit set, → all-1s in range | `921d4000/04 ffffffff, 4008 00003fff` ✓ | direct RMW |
| B2 | `spa_set_dn_reg_pkt_en(i,1)` i=0..0x52 (tm:26322, tm:43304) | 1 / 0x75010 stride1 | 0x921d4040..404c | per-bit set | `921d4040/44 ffffffff, 4048 0007ffff` ✓ | direct RMW |
| B3 | RMW `fpga_write_reg(0x75015, x \| 0x3000000)` (tm:43315-6) | direct id 0x75015 | 0x921d4054 | OR-in 0x3000000 | `921d4054 03ff05dc` (b24-25 set) ✓ | direct |
| B4 | `spa_set_match_mode(1)` (tm:26715, tm:43328) | 0x12 / 0x7501f mask3 | **0x921d407c** | **0x1** | **`921d407c 00000001`** ✓ | direct RMW |
| B5 | `spa_set_matchram(entry)` ×11 from `_LANCHOR1`+`DAT_0004eee4` (tm:26131, tm:43356) | **indirect** (ram_id 0) | 0x921d4014/18/401c..30 | see protocol below | RAM not MMIO-readable; cmd readback `921d4014 01400007` | **INDIRECT** |
| B6 | `spa_set_hashram(i,entry)` i=0..7 (tm:26029, tm:43363) | **indirect** (ram_id 5) | same window | see protocol | last cmd left `921d4014=01400007` = ind=0,ram_id=5,addr=7 ✓ | **INDIRECT** |

(B1/B2 also touch up-pps/dft_pri/802x_trap/pkt_filter via direct RMW — counter/QoS
priming, NOT the egress gate; omitted for brevity, all cosmetic.)

**Load-bearing:** **B4** `spa_set_match_mode(1)` → `921d407c = 1` enables the
source-port match classifier (mainline default 0 = disabled). **HIGH** this must be
set for the classifier to consult the match-RAM at all. **B5** (match-RAM contents)
is what the classifier matches against; if the CPU source-port rule lives there it
is load-bearing too — but its contents come from opaque `_LANCHOR1` blob (see FLAG).
B1/B2/B3/B6 are priming/QoS = cosmetic for this gate.

### SPA indirect-RAM protocol (the cmd/done/data ports) — for B5/B6
Same shape as SCH/DSCH shaper. Three direct regs in `zx_sparegtable`:
- **cmd**  reg4  base 0x75005 → **phys 0x921d4014**: write
  `ram_addr + ram_id*0x400000 + ind_rw_en*0x8000000`
  (decomp `spa_set_indirect_rw_cmd` tm:25957; i.e. `addr | ram_id<<22 | rw<<27`).
- **done/status** reg5 base 0x75006 → **phys 0x921d4018**: poll bit0==0 ("access
  done"), up to 0x13 tries (decomp `spa_get_indirect_rw_status` tm:25979 + spin
  loops tm:26174 / 26058).
- **data** reg6 base 0x75007 stride1, idx0..5 → **phys 0x921d401c..0x921d4030**:
  6 data words (`spa_set_indirect_rw_data(id,val)` tm:26015, RMW per idx).

Write sequence for one match-RAM entry (rule_num N), from `spa_set_matchram`
(tm:26171-26257): (1) poll done==0; (2) cmd READ-prefetch `(rw=1,ram=0,addr=N>>2)`;
(3) read back 6 data words; (4) OR the new 8-byte entry into the right sub-field of
those 6 words (entry packing depends on `N & 3` slot, tm:26206-26248); (5) cmd WRITE
`(rw=0,ram=0,addr=N>>2)`; (6) write the 6 data words back. hashram (B6) uses
ram_id=5, only 2 data words (`spa_set_indirect_rw_data(1,*)`/`(0,*)`, tm:26076).

---

## C. CRITICAL correction to prior doc — the device-MAC entry is NOT in the SPA match-RAM
`cpu_source_port_egress_re.md` claimed `921d4120/4124` = "device MAC in the SPA
match-RAM". **That is wrong.** Those phys map to **direct** registers
`zx_sparegtable` **reg22 (base 0x75048, stride 2)** and **reg23 (base 0x75049,
stride 2)** — the **ONU-MAC-addr table**, written by `spa_set_onu_mac_addr`
(tm:26870) as `tmOnuRegWrite(0x16, mac[2]<<24|mac[3]<<16|mac[4]<<8|mac[5], num)` and
`tmOnuRegWrite(0x17, mac[0]<<8|mac[1], num)`. Decode of stock:
`921d4120 470f4264 / 921d4124 0000f4f6` = `f4:f6:47:0f:42:64` (slot0), slots 1/2 at
+8/+16 = …65/…66. These are **direct writes at phys 0x921d4120 + slot*8 (+0/+4)**.

**Implication:** mainline ALREADY does this — `zx-eth-main.c:1864` writes
`ZX_SPA_ONU_MAC_BASE 0x14120` (= e->base 0x921c0000 + 0x14120 = 0x921d4120). So the
device-MAC entry is NOT a missing piece; do not re-derive it as indirect RAM.

---

## ORDERED recipe to ADD to mainline init (after `zx_npp_init`, before bring-up)
NPP-relative offsets (off = phys − 0x921c0000) for `npp_write(e, off, val)`.
All are DIRECT writes except B5/B6 (indirect). PM/SPA setters are RMW in stock, but
since mainline starts from power-on defaults, the literal stock values below are
correct to write directly:

1. SPA up-pkt-en:  `0x14000=0xffffffff; 0x14004=0xffffffff; 0x14008=0x00003fff`  (B1)
2. SPA dn-pkt-en:  `0x14040=0xffffffff; 0x14044=0xffffffff; 0x14048=0x0007ffff`  (B2)
3. SPA 0x14054 RMW: `|= 0x03000000` (stock-live 0x03ff05dc)                       (B3)
4. **SPA match_mode: `0x1407c = 0x00000001`**  ← LOAD-BEARING                     (B4)
5. SPA match-RAM: 11 indirect writes, ram_id=0 (protocol §B). **needs `_LANCHOR1`** (B5)
6. SPA hash-RAM: 8 indirect writes, ram_id=5                                      (B6)
7. PM in-port rules: `0x20180+i*4 = i` (i=0..7)                                   (A1)
8. PM out-port rules: `0x201a0+i*4 = i` (i=0..7)                                  (A2)
9. PM g988 mode: `0x20054 b2-3=0; 0x20058 b2-3=1; 0x2005c b2-3=3`                 (A3)
10. **PM out-port rule idx0: `0x201a0 = 0x00000008`**  ← LOAD-BEARING (overwrites step 8 idx0) (A4)
11. **PM ctrl: `0x20054 = 0x000000c0`** (cpu_not_drop b4=0 + inport_eq b7=1; b6 unexplained, copy literal) ← LOAD-BEARING (A5+A6)

### The load-bearing subset (if minimizing):
- **`0x201a0 = 0x08`** (PM out-port rule port0 valid)  — A4
- **`0x20054 = 0xc0`** (PM inport_equal_outport_staen=1, cpu_not_drop=0)  — A5+A6
- **`0x1407c = 0x01`** (SPA match_mode=1)  — B4
- plus the SPA match-RAM (B5) IF the CPU source rule is encoded in `_LANCHOR1`.
The rest (A1/A2/A3, B1/B2/B3/B6, hash-RAM) are state-priming/QoS = cosmetic for the
CPU→physical egress gate. (These three load-bearing pokes are exactly POKE-TEST
P1/P2/P3 from `cpu_source_port_egress_re.md`, now traced to their decomp origin and
confirmed against the stock dump.)

---

## FLAGS / things I could NOT fully pin
1. **`_LANCHOR1` / `DAT_0004eee4` match-RAM payload (UNRESOLVED).** The 11 match-RAM
   entries (0x160=352 bytes) and the 12-entry `DAT_0004eee4` copy are external data
   blobs not inlined in this decomp. The match-RAM is indirect-only, so it is NOT
   visible in `stock_eth_2mib.txt` (only the leftover cmd `921d4014 01400007` is).
   **Cannot reproduce the exact entry bytes from this decomp alone.** To get them:
   read `_LANCHOR1` from the tm.ko .rodata, OR read the RAM back live via the
   indirect READ protocol (§B) on a stock unit. Whether a CPU-source-port rule even
   lives here (vs. being implicit in match_mode=1 + the PM rule) is unconfirmed —
   the experiment may pass on the 3 load-bearing direct writes alone.
2. **PM ctrl bit6 (0x40) at 0x921e0054 (UNRESOLVED).** Stock = 0xc0 but
   `tm_pon_npp_pm_initial` only produces 0x80 (bit7). Bit6 is unmapped in
   `zx_pmregtable` at base 0x78015 and is set by power-on default or another writer.
   Mitigation: write the literal 0xc0 to be stock-faithful.
3. **Physical-port index for the host (MEDIUM).** A4 enables physical port 0; the
   host/MAC2 binding is not provable from decomp. Verify by live diff of
   `0x921e01a0..01bc` and set valid_en (bit3) on the host's egress-port idx.
4. **SPA indirect entry packing (LOW risk, documented).** The per-slot bit packing
   in `spa_set_matchram` (tm:26206-26248, switch on `N&3`) is transcribed but dense;
   re-derive carefully when implementing the indirect writer, or just replay the
   raw 6-word data captured from a live stock read rather than re-encoding.

## Confidence
- **HIGH**: address math, reg-table decode, the 3 load-bearing direct writes
  (0x201a0=0x08, 0x20054=0xc0, 0x1407c=0x01) — each tied to a decomp line AND an
  exact stock-dump line.
- **HIGH**: device-MAC is reg22/23 direct (0x921d4120/4124), already done by
  mainline; prior "match-RAM" claim corrected.
- **MEDIUM**: host physical-port index for A4.
- **UNRESOLVED**: match-RAM payload bytes; PM ctrl bit6 origin.
