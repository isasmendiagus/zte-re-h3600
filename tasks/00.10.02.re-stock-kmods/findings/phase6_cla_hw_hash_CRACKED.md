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
