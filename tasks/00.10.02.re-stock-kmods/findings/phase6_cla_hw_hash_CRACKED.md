# Phase 6 — the REAL CLA HW hash slot function (CRACKED, static decomp)

2026-06-04, branch phase6-hw-offload. This supersedes the earlier `cla_list_hash_addr_gen`
(CRC-32 0x04C11DB7) lead — that function is **only the SW shadow-list hash** (tm_findFastIdxByTuple,
for dedup), NOT the slot the chip uses. The HW slot is computed by `cla_acl_hash_addr_gen`.

## Call chain for the slot
`zte_api_fast_l3_session_add → … → cla_get_hash_poly_config(cfg)` (READ the chip poly cfg) `→
aclGetAvailableHashAddr_constprop_13(mode_sel, KEY, cfg, &slot) → cla_acl_hash_addr_gen(hash_mode,
KEY, &h16)` (per hash-way) `→ cla_set_hash_table(slot & 0x7fff, entry)`.
(tm.c: aclGetAvailableHashAddr @52343; cla_acl_hash_addr_gen @4154; cla_get_hash_poly_config @805;
cla_set_hash_table @3368.)

## cla_acl_hash_addr_gen(hash_mode, key, &out) — the hash (tm.c:4154)
1. Copy the **45-byte (0x2d) KEY into a stack buffer in REVERSE** byte order (abStack_55[0x2c-i]=key[i]).
2. Byte-wise CRC-32, MSB-first, **init 0, no final XOR**, over the 45 reversed bytes:
   `h = table[(b ^ (h>>24)) & 0xff] ^ (h<<8)`. The polynomial table is selected by **hash_mode**:
   - mode 0 → `crctable_04C11DB7`  (poly 0x04C11DB7 — standard CRC-32 / Ethernet)
   - mode 1 → `crctable_1EDC6F41`  (poly 0x1EDC6F41 — CRC-32C / Castagnoli)
   - mode 2 → `crctable_F4ACFB13`  (poly 0xF4ACFB13 — CRC-32K / Koopman)
   - mode 3 → `crctable_32583499`  (poly 0x32583499 — CRC-32Q)
3. `*out = h & 0xffff` (16-bit raw hash).

## aclGetAvailableHashAddr (tm.c:52343) — mask + multi-way probe
- `cla_get_outspace_cfg(&ACL_OUT_SPACE_SEL)`, `ACL_OUT_HASH_NUM` → ways = `1 << (2 - ACL_OUT_HASH_NUM)`.
- mask `m = (0x400 << (6 - ACL_OUT_SPACE_SEL)) - 1`.
- For each hash-way i (poly word `cfg[0xc + 4*(i+1)]` → hash_mode): compute h16, then
  `slot = (h16 & m & (m >> (2-ACL_OUT_HASH_NUM))) << (2-ACL_OUT_HASH_NUM) | way_index`.
- Probe: if `s_aclHashUsedCnt[slot + 0x208] == 0` (free) → take it (`slot | 0x80010000`), else next way.
- ⇒ slot depends on the chip's **poly cfg + outspace cfg (HW registers)** AND on collisions (probing).

## The KEY (45 bytes, param_2) — STRUCTURED, includes the ports
From the field-decode printks (aclGetAvailableHashAddr 52374-52436 / cla_acl_hash_addr_gen 4166-4250):
- byte0 bits[4:0] = **outport**; outport/inport span bytes0-2: `inport = b1<<3 | b0>>5 | (b2&1)<<11`
- byte2: tag_level [b2<<28>>29], l2_type [b2<<26>>30], pppoe_flag [b2<<25>>31]
- ex_rule_id = `b3<<1 | b2>>7`; ex_rule_mode = `b3>>7`; direct = `b4 & 1`
- **extra_data0..19** = 20 × 16-bit fields, packed from byte4 up: `dataN = b[4+2N+1]<<7 | b[4+2N]>>1 |
  (b[4+2N+2]&1)<<15`. These hold the extracted packet bytes (the 5-tuple: src/dst IP, ports, proto)
  — the exact extra_dataN ↔ 5-tuple-byte mapping is set by the ram0 extract config + the key builder
  (NEXT to pin: find where param_2 is built before aclGetAvailableHashAddr).

## Why the earlier CRC-list test failed (now fully explained)
(a) wrong function (list-shadow vs acl-HW), (b) wrong input (40-byte session+4 tuple vs this 45-byte
structured+reversed key), (c) the key includes inport/outport → port-numbering-dependent, (d) multi-way
+ collision probing. All four are real; the simple test could never have matched.

## Implication for mainline (Stage 2b is now computable)
slot for a flow = `cla_acl_hash_addr_gen(mode, build_key(5tuple, mainline_inport, mainline_outport))`
masked per the HW outspace cfg, first free way. To replicate we need, on mainline:
1. **Read the poly cfg + outspace cfg HW registers** (cla_get_hash_poly_config / cla_get_outspace_cfg
   target regs) — gives hash_mode(s), ACL_OUT_HASH_NUM, ACL_OUT_SPACE_SEL. Read once on mainline.
2. **Pin the key builder** (extra_dataN ↔ which 5-tuple byte; outport/inport encoding) — decomp the
   caller that fills param_2 (the buffer passed to aclGetAvailableHashAddr).
3. Implement the 4 CRC tables + reversal + mask in the driver; compute the slot for a chosen flow with
   MAINLINE ports; clawrite ONE ram2 entry there; isolated hw_trap test.

VERIFY shortcut available: once we read the live poly cfg + know the key layout, recompute the slot for
a captured stock flow and check it equals the captured slot (0x48/0x5a/...) — confirms the model end to
end without needing kotrace deref.

## UPDATE 2026-06-04d — there is a HW HASH ENGINE (use it directly, skip CRC reimpl)
The stock `/proc/tm/shell` command `calculatehashaddr` (cla_info_store @tm.c:67678) does NOT compute the
slot in SW. It packs the 45-byte key into words, then:
```
fpga_write_reg(0xe30b0, key_word0);
for i in 0..11: fpga_write_reg(0xe30b1 + i, key_word[1+i]);   // 12 more words
slot = fpga_read_reg(0xe30bf);                                 // "calculate hash addr is :0x%x"
```
⇒ a dedicated **HW hash engine**: write the 13-word key to fpga words **0xe30b0..0xe30bc**, read the
slot from **0xe30bf**. The SW cla_acl_hash_addr_gen (4-poly CRC) is just a mirror of this HW block.
### Register offsets (driver-relative, e->base = phys 0x921c0000)
- fpga word W → phys 0x92000000 + W*4. So:
  - key in:  0xe30b0..0xe30bc → phys 0x9238C2C0..0x9238C2F0 → **e->base + 0x1CC2C0 .. +0x1CC2F0** (13 words)
  - slot out: 0xe30bf        → phys 0x9238C2FC          → **e->base + 0x1CC2FC**
- These sit right next to the CLA indirect iface (CLA_REG_CMD = e->base+0x1CC014) — same CLA block,
  already mapped by the driver. NO new ioremap needed.
### calculatehashaddr key packing (29 hex args → 45-byte key) — for the key BUILDER
sscanf 29 hex args -> {arg0=outport(&0x1f); arg1<<5 region; arg2&7=tag?, arg3&3, arg4&1, arg5&0xff;
then args6.. = extra_data0..19 as 16-bit values bit-packed with a 1-bit shift (matches the extra_dataN
decode `dataN = b[2N+1]<<7 | b[2N]>>1 | (b[2N+2]&1)<<15`)}. The 5-tuple→extra_dataN mapping comes from
tm_acl_get_fastHashRule (fills the 20 ushorts local_51..local_2b in tm_acl_fast_add_v4v6 @52583-52602).
### Why stock readback failed (tooling, NOT a blocker)
`fpga -r 0xe30bf` returns rc=0 but emits NO logger_main line (only some widx ranges log; or the
write+read must be same driver-open as in calculatehashaddr). The shell's printk doesn't reach
logger_main, and the stock UART console is silent. ⇒ VERIFY ON MAINLINE instead: debugfs `poke` reads
any reg. Plan: on mainline write a test key to base+0x1CC2C0.. and read base+0x1CC2FC; confirm the engine
returns a slot. Then the driver: build key from 5-tuple+mainline ports → HW-hash → write ram2[slot].

### MAINLINE READINESS CONFIRMED (static, 2026-06-04)
- npp window = 0x921c0000 + 0x200000 (2MB) → covers up to 0x923c0000, so the hash engine
  0x9238C2C0/0x9238C2FC IS mapped (zx-eth-main.c:21).
- debugfs `poke` (zx_poke_write @4312): 2 args `<phys> <val>` = WRITE (+readback print); 1 arg = PEEK
  read; validates phys ∈ [0x921c0000, 0x923c0000) & aligned. ✓ Both write+read available.
- RECIPE on mainline: write key `poke 0x9238C2C0 <w0>` … `poke 0x9238C2F0 <w12>` (13 words), then read
  slot `poke 0x9238C2FC` (peek) → kmsg → UART :9999. First test: vary the key, confirm the slot changes
  (engine live). Then match a stock flow's key fields → expect a known slot. Then driver integration.
