# PM (G.988 port-mapper) @ 0x921e0000 — full RE of in/out-port rules, g988 modes, g988 rule-RAM (2026-06-01)

Analysis only (decomp + mainline + reg-table cross-check). Did NOT touch the device.
Companions: `pm_spa_init_recipe_re.md`, `cpu_source_port_egress_re.md`,
`ingress_datapath_architecture_re.md`, `port_numbering_map_re.md`,
`pp_pm_table_re.md`, memory `zte-spa-matchram-not-gate`.

KEY SOURCES:
- decomp setters: `pm_set_g988_mode` tm:22911, `pm_set_g988_cpu_drop_staen` tm:22957,
  `pm_set_g988_cpu_not_drop_staen` tm:22992, `pm_set_g988_inport_equal_outport_staen`
  tm:23027, `pm_set_in_port_rule_valid` tm:23061, `pm_get_in_port_rule_valid` tm:23108,
  `pm_set_out_port_rule_valid` tm:23147, `pm_get_out_port_rule_valid` tm:23194,
  `pm_set_port_cfg` tm:23422, `pm_check_g988_rule` tm:23581, `pm_add_g988_rule`
  tm:23618, `pm_select_g988_reg` tm:23643, `pm_set_g988_cfg` tm:23722,
  `tm_pm_g988_rule_set` tm:47749.
- init loop: `tm_pon_npp_pm_initial` tm:43376.
- access primitive: `tmOnuRegWrite/Read` tm:35358/35339.
- reg table: `zx_pmregtable[]` linux-v6.6/.../zx-fpga-reg-tables.h:365-383.
- mainline replica: `zx_pm_spa_init` zx-eth-main.c:4706-4732.

---

## 0. Address model (verified)

`tmOnuRegWrite(reg_id, val, idx, table)` does an RMW (tm:35358):
`phys = 0x92000000 + (base_off + stride*idx)*4` ;
`*phys = (*phys & ~(mask<<shift)) | ((val & mask)<<shift)`.
`base_off`/`stride` are **32-bit word** indices (byte = word*4). mainline `e->base =
0x921c0000`, `npp_write(e,off,val)=writel(val, e->base+off)` so `npp_off = phys − 0x921c0000`.

### `zx_pmregtable[]` fully decoded → physical PM register/RAM map

| reg_id | base_off (word) | phys byte | npp_off | shift | mask | stride | maxsub | meaning |
|---|---|---|---|---|---|---|---|---|
| 0 | 0x78005 | 0x921e0014 | 0x20014 | 0 | 0x0fffffff | 0 | 0 | indirect_rw_cmd (g988-RAM indirect access; NOT used by initial) |
| 1 | 0x78006 | 0x921e0018 | 0x20018 | 0 | 0x1 | 0 | 0 | indirect_rw_status (poll bit0) |
| 2 | 0x78007 | 0x921e001c | 0x2001c | 0 | 0xffffffff | 1 | 14 | indirect_rw_data[0..14] (+4/idx) |
| **3** | 0x78015 | **0x921e0054** (idx0); +4/idx | 0x20054 | **2** | **0x3** | **1** | 3 | **g988_mode[idx]** bits[3:2]; idx0=0x54,idx1=0x58,idx2=0x5c |
| 4 | 0x78015 | 0x921e0054 | 0x20054 | 5 | 0x1 | 0 | 0 | g988_cpu_drop_staen (bit5) |
| 5 | 0x78015 | 0x921e0054 | 0x20054 | 4 | 0x1 | 0 | 0 | g988_cpu_not_drop_staen (bit4) |
| **6** | 0x78060 | **0x921e0180**+idx*4 | 0x20180 | 0 | 0xf | 1 | 8 | **in_port_rule_valid[idx]**: val=`port \| valid_en<<3` |
| **7** | 0x78068 | **0x921e01a0**+idx*4 | 0x201a0 | 0 | 0xf | 1 | 8 | **out_port_rule_valid[idx]**: val=`port \| valid_en<<3` |
| 8 | 0x78075 | 0x921e01d4 | 0x201d4 | 0 | 0x1 | 0 | 0 | flow_sta_en |
| 9 | 0x78075 | 0x921e01d4 | 0x201d4 | 1 | 0x1 | 0 | 0 | flow_sta_pkt_len_sel |
| 10 | 0x78075 | 0x921e01d4 | 0x201d4 | 2 | 0x1 | 0 | 0 | flow_sta_read_clear_en |
| 11 | 0x78075 | 0x921e01d4 | 0x201d4 | 3 | 0x1 | 0 | 0 | flow_sta_cnt_mode |
| 12 | 0x78075 | 0x921e01d4 | 0x201d4 | 4 | 0x1 | 0 | 0 | flow_sta_fwd_only_en |
| **13** | 0x78092 | **0x921e0248**+idx*4 | 0x20248 | 0 | 0xffffffff | 1 | 64 | **g988 rule-RAM[0..64]** (65 entries; format §3) |
| 14 | 0x780e0 | 0x921e0380 | 0x20380 | 0 | 0xffffffff | 1 | 16 | zte_index_cfg[0..16] |
| 15 | 0x780f0 | 0x921e03c0 | 0x203c0 | 0 | 0xffffffff | 1 | 16 | zte_index_cfg(2)[0..16] |
| **16** | 0x78015 | 0x921e0054 | 0x20054 | **7** | **0x3** | 0 | 0 | **g988_inport_equal_outport_staen** (bits[8:7]) |

Note reg3/4/5/16 all live in the **same word 0x921e0054** (the "g988 ctrl" word).
g988_mode (reg3) at idx0 also lands in 0x54 bits[3:2]; idx1→0x58, idx2→0x5c.

---

## 1. The PM init loop — `tm_pon_npp_pm_initial` (tm:43376)

```
for (i = 0; i < 8; i++) {            // tm:43390-43395
    pm_set_in_port_rule_valid (i, i, 0);   // reg6 idx=i  val = i|0<<3 = i  (valid_en=0)
    pm_set_out_port_rule_valid(i, i, 0);   // reg7 idx=i  val = i|0<<3 = i  (valid_en=0)
}
pm_set_g988_mode(0,0); pm_set_g988_mode(1,1); pm_set_g988_mode(2,3);  // tm:43397-9
// then:
zte_api_set_port_rule({mode=1,valid=1,port=5});   // tm:43406 -> out-port rule for logical CPU 5
zte_api_set_g988_cpu_not_drop_staen(0);           // tm:43407  reg5 bit4 = 0
zte_api_set_g988_inport_equal_outport_staen(1);   // tm:43408  reg16 bits[8:7] = 1 (bit7=1)
```

`zte_api_set_port_rule({1,1,5})` → `tm_pm_port_rule_set` → `tm_pm_port_get(5)` maps
**logical CPU port 5 → physical 0**, then `pm_set_port_cfg({type=1,valid=1,port=0})`
takes the out-port branch → `pm_set_out_port_rule_valid(0,0,1)` → reg7 idx0 = `0|1<<3`
= **0x08** at 0x921e01a0. This is the single enabled rule. (tm:23422 out-branch.)

### Setter semantics & validation

- **`pm_set_in_port_rule_valid(port_num, cfg_num, valid_en)`** (tm:23061):
  `tmOnuRegWrite(6, port_num | valid_en<<3, cfg_num, …)`. Validates `port_num<8`,
  `cfg_num<8`, `valid_en<2`. **Stored value = `port_num | (valid_en<<3)`** at
  reg6 idx=`cfg_num`. So each 4-bit entry = `{valid_en[3], port[2:0]}`. The "index"
  (cfg_num) is a rule slot 0..7; the value's low 3 bits are the **raw logical port**.
- **`pm_set_out_port_rule_valid(port_num, cfg_num, valid_en)`** (tm:23147): identical
  shape on reg7.
- **`pm_get_in_port_rule_valid(port_num,*out)`** (tm:23108): scans all 8 slots,
  finds the one whose `value & 7 == port_num`, returns its `bit3` (valid_en). Confirms
  the **low 3 bits are the port id, bit3 is the valid flag**, and the 8 slots are a
  CAM-like list keyed by port.
- **`pm_set_g988_mode(mode_idx, mode_val)`** (tm:22911): `tmOnuRegWrite(3, mode_val,
  mode_idx, …)` → bits[3:2] of word `0x54 + mode_idx*4`. Validates `mode_idx<3`,
  `mode_val<3` (mode_idx2 allows val up to 3). The three modes select what the g988
  rule-RAM matches on (see §3 — mode 0=in_port only, 1=+vlan, 2=+pri, 3=+vlan+pri).
- **`pm_set_g988_cpu_drop_staen` / `_cpu_not_drop_staen`** (tm:22957/22992): word 0x54
  bit5 / bit4 — drop / don't-drop policy for CPU-destined frames.
- **`pm_set_g988_inport_equal_outport_staen(stamode)`** (tm:23027): word 0x54
  bits[8:7], `stamode<3`. Governs counting/handling when computed in_port==out_port
  (the CPU hairpin case).

---

## 2. The "source→allowed-egress authorizer" role — is the PM the ingress→CPU gate?

**No — the PM is a forwarding/egress AUTHORIZER and statistics matrix, not the
per-ingress-port MAC→SPA admit gate. It does NOT block port1 ingress.** Evidence:

1. **The in-port/out-port "rules" are a CAM keyed by port value, not a per-port
   enable.** Both `pm_set_*_rule_valid` store `port|valid<<3` and `pm_get_*` looks the
   port up by value (tm:23133). They authorize *forwarding pairs*; a port being absent
   from the list does not silently sink that port's frames at the MAC→SPA stage (which
   is upstream of the whole NPP fabric).
2. **Ports 0/2/3 work with mainline's idx0-only out-port config** (only 0x201a0=0x08,
   idx1-7 valid_en=0) AND with the in-port rules all valid_en=0. If a missing out-port
   rule blocked a port's ingress→CPU, ports 0/2/3 would also die — they don't. ⇒ The
   out-port rule is **not** the per-ingress gate; out-port idx0 (=physical 0, the CPU
   egress) is what authorizes the *CPU egress* leg, shared by all ingress ports.
3. **`inport_equal_outport_staen`** + **cpu_not_drop** (word 0x54 = 0xc0) are the
   knobs that actually matter for the CPU loopback symptom (per `cpu_source_port_egress_re.md`),
   and they are **global**, not per-port.
4. The g988 rule-RAM (reg13, §3) IS per-(in_port) — but mainline leaves it at HW reset
   (all 0, valid=0 → matches nothing) and `tm_pon_npp_pm_initial` **never installs any
   entry** (`pm_add_g988_rule` is only reachable via `pm_set_g988_cfg`/`tm_pm_g988_rule_set`,
   which the initializer does not call). Stock at boot **also** leaves 0x921e0248=0
   (`pm_spa_init_recipe_re.md`: live `921e0248 00000000`). So **neither stock nor
   mainline installs a g988 rule at boot** → it cannot be the differentiator that
   makes port1 die while ports 0/2/3 pass.
5. The per-ingress-port loss is upstream: port1 dies at the **MAC1→SPA admit handoff**
   (SPA rcv_uni1 low, SDET uni1≈2 vs 229/230), which is *before* SPA/SDET/CLA/QMG —
   the entire PM fabric is downstream of that. The PM is **EXONERATED** for port1.

**Numbering:** PM in-port/out-port rule values use **raw logical** port (0..7; CPU
logical 5 → physical 0 via `tm_pm_port_get`). The g988 rule-RAM `in_port` field is
likewise the raw value passed to `tm_pm_g988_rule_set` (logical). This matches
`port_numbering_map_re.md` rows 42-43 ("PM rules = raw logical"). NOT regport, NOT uni.

---

## 3. The g988 rule-RAM @ 0x921e0248 (reg13) — entry format DECODED

65 entries (idx 0..64), one 32-bit word each at `0x921e0248 + idx*4`. The mode of an
entry is implicit in its **slot range** (`pm_select_g988_reg` tm:23643):
mode 0 → slots 0..7, mode 1 → slots 8..15, mode 3 → slots 16..63 (mode 2 shares the
mode-0/1 lookup path; only modes 0/1/3 get dedicated slot ranges).

Bit layout (from `pm_add_g988_rule` write tm:23625 + `pm_check_g988_rule` read tm:23589,
cross-checked):

| bits | field | source |
|---|---|---|
| [20] | **valid** | write `param[1]<<20`; read `(x<<0xb)>>0x1f` (pm_select_g988_reg tm:23703) |
| [19] | **byte / "type" flag** (param[2], a single byte 0/1) | write `param[2]<<19`; read `(x<<0xc)>>0x1f` |
| [18] | **direction** (0=us,1=ds) | write `param[3]<<18`; read `(x<<0xd)>>0x1f` |
| [17:15] | **in_port** (0..7, raw logical) | write `param[4]<<15`; read `(x<<0xe)>>0x1d` |
| [14:12] | **pri** (0..7) — modes 2 & 3 only | write `param[5]<<12`; read `(x<<0x11)>>0x1d` |
| [11:0] | **vlan_id** (0..0xffe) — modes 1 & 3 only | write `param[6] (& 0xfff)`; read `x & 0xfff` |

Per-mode the writer ORs in only the relevant fields (tm:23627-23635):
mode0 = valid+byte+dir+in_port; mode1 = +vlan; mode2 = +pri; mode3 = +vlan+pri.

`tm_pm_g988_rule_set` param array (tm:47749, field names from printk tm:64302):
`[0]=mode (derived from which of vlan/pri are 0xffff "wildcard"), [1]=valid,
[2]=byte/type, [3]=direction, [4]=in_port, [5]=pri, [6]=vlan_id`. The mode is computed:
both wildcard→0, vlan-only→1, pri-only→2, both→3 (tm:47774-47787).

**Indirect-access caveat:** unlike the other PM regs, the g988 rule-RAM is written by
direct `tmOnuRegWrite(0xd, …, idx, …)` (reg13 is a normal strided register, NOT the
indirect cmd/status/data trio reg0/1/2). So 0x921e0248+idx*4 is directly MMIO
read/writeable. (The reg0/1/2 indirect block at 0x14/18/1c is a *separate* facility
not exercised by any PM-rule path in the initializer.)

**Is it per-port? Could port1's entry be missing?** It is per-(in_port) by the bits[17:15]
field, BUT it is a **positive match→action** table: an absent entry = no match = the
*default* G.988 forwarding applies (same as ports 0/2/3, which also have no entry).
A missing port1 entry therefore behaves exactly like ports 0/2/3 (which work). It can
only differ if stock installed an entry for SOME ports but not port1 — and stock
installs NONE at boot (live 0x921e0248=0). ⇒ Not port1-relevant.

---

## 4. Mainline `zx_pm_spa_init` vs stock — what is OMITTED + correctness bugs

| stock pm_initial action | mainline does it? | note |
|---|---|---|
| in-port rules idx0..7 = i (valid_en=0) | ✅ `0x20180+i*4=i` (loop) | OK |
| out-port rules idx0..7 = i (valid_en=0) | ⚠️ **OMITTED idx1..7** | mainline only sets idx0 (next row). idx1-7 left at HW reset (0). Stock primes them = 1..7 (valid_en=0) — **cosmetic** (valid_en=0 either way; the low-3-bit port id differs but valid=0 so inert). |
| out-port rule idx0 = 0x08 (port0 valid_en=1) | ✅ `0x201a0=0x08` | OK — the load-bearing CPU-egress authorizer |
| g988 mode idx0=0, idx1=1, idx2=3 (bits[3:2]) | ⚠️ **WRONG BIT FIELD** | see bug below |
| ctrl 0x54 = inport_eq=1, cpu_not_drop=0 (→0xc0) | ✅ `0x20054=0xc0` | OK (literal incl. unexplained bit6) |
| g988 rule-RAM (0x921e0248) | not written | matches stock (stock also leaves 0) — OK |
| flow_sta regs (0x201d4) | not written | cosmetic stats — OK |

### BUG (decode-level, NOT port1-relevant): g988_mode bit position
Stock `pm_set_g988_mode(idx,val)` writes `val` into **bits[3:2]** (reg3 shift=2,
mask=0x3) of `0x54+idx*4`. Mainline writes the **full word**:
`0x20058 = 0x1` and `0x2005c = 0x3` — i.e. into **bits[1:0]**, leaving bits[3:2]=0.
To faithfully replicate stock, mainline should write `0x20058 = (1<<2) = 0x4` and
`0x2005c = (3<<2) = 0xc` (and idx0 0x20054 bits[3:2]=0, already 0). This mis-set is
harmless to the port1 anomaly (g988 mode only matters once a g988 rule-RAM entry is
installed, which neither side does), but it IS a fidelity bug worth fixing.

**Net:** mainline's PM init reproduces the load-bearing state (out-port idx0=0x08,
ctrl=0xc0). The only true omission is out-port idx1-7 priming (inert, valid_en=0) and
the g988-mode bit-field bug (latent). **No PM omission is port1-specific.**

---

## 5. Concrete read/poke test (phys + correct port space)

All PM rule values are **raw logical** port space (port1 = value 1, NOT regport/uni
remapped). The rule *slots* (idx) are plain 0..7.

### TEST A — confirm the PM rule arrays + ctrl (read)
```
mem 0x921e0180   # in-port rule idx0..7 are at +0/+4/.. ; expect 0x0,0x1,..,0x7 (valid_en bit3=0)
mem 0x921e0184
... (through 0x921e019c)
mem 0x921e01a0   # out-port idx0 — EXPECT 0x00000008 (port0, valid_en bit3=1)
mem 0x921e01a4   # out-port idx1 — mainline 0x0 / stock 0x1 (both valid_en=0 → inert)
mem 0x921e0054   # ctrl — EXPECT 0xc0 (bit7 inport_eq=1, bit6 set, bit4 cpu_not_drop=0)
mem 0x921e0248   # g988 rule-RAM slot0 — EXPECT 0x00000000 (no rule installed, both stock+mainline)
mem 0x921e0058   # g988 mode idx1 — bug check: mainline=0x1 (bits[1:0]); stock-correct=0x4 (bits[3:2])
mem 0x921e005c   # g988 mode idx2 — mainline=0x3; stock-correct=0xc
```
Expected: confirms PM identical to stock except the two g988-mode words (bug) and
out-port idx1-7 (inert). If so, PM is byte-equivalent on the load-bearing fields →
**PM exonerated for port1 by inspection.**

### TEST B — install a port1-specific g988 in-port rule and watch for change (poke)
Build a mode-0 (in_port-only) ALLOW rule for in_port=1 in slot 0, then re-run the
port1 RX test:
```
# entry = valid(1)<<20 | byte(0)<<19 | dir(?)<<18 | in_port(1)<<15
# downstream/ds = dir bit18=1 ; upstream/us = 0. Try ds first:
poke 0x921e0248 0x00148000     # valid=1(b20) dir=1(b18) in_port=1(b15..17)=1<<15=0x8000  -> 0x100000|0x40000|0x8000
# (0x100000 | 0x40000 | 0x8000 = 0x148000)
# enable g988 mode0 lookup is already mode0 default (slot0 in 0..7 range)
```
Expected observable: if the PM in-port match were the gate, this would change SPA
`rcv_uni1` / SDET `uni1` transport count for port1. **Predicted: NO change** (PM is
downstream of the MAC→SPA admit loss). A null result further exonerates the PM and
keeps focus on the MAC1→SPA admit handoff. (If it DOES change, the PM is implicated —
unlikely given §2.)

> Numbering reminder (from `port_numbering_map_re.md` row 39): port1 on PM = raw
> logical **1**. Do NOT use regport2 here (that's a regport/CLA/isolation space). The
> g988 in_port field [17:15]=1 is logical port1.

---

## 6. Conclusion

- The PM block is **fully decoded**: 17 reg_ids, all physical addresses + bitfields
  (§0), the in/out-port rule CAM (value=`port|valid<<3`, §1), g988 modes (word 0x54
  bits[3:2] strided), ctrl word 0x54 (drop/not-drop/inport_eq), and the 65-entry g988
  rule-RAM at 0x921e0248 with full bit layout (§3).
- The PM is a **forwarding/egress authorizer + G.988 match table**, downstream of the
  MAC→SPA admit stage where port1 actually dies. Its per-port surfaces (in-port rule
  CAM, g988 rule-RAM) are **positive-match/authorize** structures whose absence yields
  the *default* behavior — identical for port1 and the working ports 0/2/3. Stock and
  mainline both leave the g988 rule-RAM empty at boot.
- **PM is EXONERATED for the port1 ingress→CPU anomaly.** No PM omission in mainline
  is port1-specific. The only mainline defects found are (a) out-port idx1-7 not primed
  (inert) and (b) the g988-mode bit-field bug (latent, harmless). Focus remains on the
  **MAC1→SPA admit handoff**.

---

## DATASHEET updates

The PM table (DATASHEET.md:628-650) is mostly correct. Apply these corrections/additions:

1. **FIX line 648 (g988 rule-RAM bitfield decode is wrong).** Current text says
   "bit20=valid,b18-19 in,b15-17 out". Replace with the verified layout:
   ```
   | `0x921e0248` | 13 | RW | [31:0] | g988 rule-RAM[0..64] (65 ent, +0x4/idx): [20]=valid [19]=byte/type [18]=direction(0=us,1=ds) [17:15]=in_port(raw logical) [14:12]=pri(mode2/3) [11:0]=vlan_id(mode1/3). slot ranges: mode0=0..7, mode1=8..15, mode3=16..63. Direct MMIO (not via indirect cmd reg0/1/2). | ✅ |
   ```
   (decomp `pm_add_g988_rule` tm:23625, `pm_check_g988_rule` tm:23589, `pm_select_g988_reg` tm:23643)

2. **CLARIFY line 641/642 (in/out-port rule value encoding).** Append to the meaning:
   `value = port[2:0] | valid_en<<3; slot idx 0..7 is a CAM, low 3 bits = raw logical port, bit3 = valid_en. Lookup by port value (pm_get_*_rule_valid tm:23108/23194).`

3. **CONFIRM line 637 (g988_mode) — strided across 0x54/0x58/0x5c.** Append:
   `idx0→0x921e0054, idx1→0x921e0058, idx2→0x921e005c, each bits[3:2] (shift=2,mask=3). mode val 0=in_port-only,1=+vlan,2=+pri,3=+vlan+pri.`

4. **ADD a note to the PM summary (line 212 / 1214) and to line 630:**
   `PM is a downstream forwarding AUTHORIZER + G.988 match table, NOT the per-ingress MAC→SPA admit gate. in/out-port rules and g988 rule-RAM are positive-match structures; absence = default behavior (same for all ports). g988 rule-RAM (0x921e0248) is left EMPTY at boot by BOTH stock and mainline (live 0x921e0248=0). PM EXONERATED for the port1 ingress anomaly.`

5. **ADD mainline-fidelity note (PM section):**
   `mainline zx_pm_spa_init (zx-eth-main.c:4725-4726) writes g988 modes into the WRONG bit field: 0x20058=0x1 / 0x2005c=0x3 set bits[1:0], but stock pm_set_g988_mode targets bits[3:2] → correct values are 0x20058=0x4 and 0x2005c=0xc. Latent (harmless until a g988 rule-RAM entry is installed). mainline also omits out-port rule idx1-7 priming (inert, valid_en=0).`

6. **ADD reg-window note:** word `0x921e0054` is shared by reg_id 3 (g988_mode idx0,
   bits[3:2]), 4 (cpu_drop bit5), 5 (cpu_not_drop bit4), 16 (inport_equal_outport bits[8:7]).
   Stock-live composite = 0xc0 (bit7=inport_eq, bit6=unexplained/power-on default, bit4=0).
