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

## ★ UPDATE 2026-06-04e — HW HASH ENGINE VERIFIED WORKING ON MAINLINE
Booted mainline, drove the engine via debugfs poke. WORKING PROTOCOL:
1. Load 12 key data words to **0x9238c2c4 .. 0x9238c2f0** (fpga 0xe30b1..0xe30bc) — the 45-byte key.
2. **Trigger**: write `1` to **0x9238c2c0** (fpga 0xe30b0) — this latches + computes (it is a control
   reg, NOT key data; writing deadbeef read back 0x3 = idle/status). MUST load data FIRST, trigger LAST.
   (My first attempts returned 0 because I wrote the trigger reg before loading the data.)
3. Read the 16-bit hash from **0x9238c2fc** (fpga 0xe30bf).
RESULTS (mainline, no extra init needed — the engine is live out of the box):
- key=0 → hash 0x0000 ; key(pattern 0x11..0xcc) → 0x4a15 (deterministic, repeated) ;
  key(w0=1) → **0x6f41** = low16 of CRC-32C poly 0x1EDC6F41 ⇒ confirms a lane uses hash_mode=1 and the
  engine == the cla_acl_hash_addr_gen CRC model.
⇒ The driver computes the slot in HW: write the 12-word key (built from 5-tuple+ports) to
0x9238c2c4.., trigger 0x9238c2c0=1, read raw hash @0x9238c2fc, then apply the aclGetAvailableHashAddr
mask `(0x400<<(6-ACL_OUT_SPACE_SEL))-1` + way bits to get the ram2 slot. NO CRC reimpl, NO engine init.
NEXT: (a) read ACL_OUT_SPACE_SEL/ACL_OUT_HASH_NUM (cla_get_outspace_cfg reg) on mainline for the mask;
(b) pin the 12-word key BUILDER (extra_dataN↔5-tuple from tm_acl_get_fastHashRule + the calculatehashaddr
packing); (c) wire into cls_flower_add: build key→HW-hash→slot→clawrite ram2→isolated hw_trap test.

## UPDATE 2026-06-04f — the KEY EXTRACT MAPPING (v4) decoded (tm_acl_get_fastHashRule @49445-49465)
For an IPv4 flow, tm_acl_get_fastHashRule writes the flow's 5-tuple into the ENTRY/KEY extra_data
region param_4[0x13..0x1f] (param_4 = the 15-word buffer; its bytes 0x13+ become the key's extra_dataN,
repacked by the caller tm_acl_fast_add_v4v6 @52631-52703 with the 1-bit-shift). Source = the flow
descriptor param_2:
- `uVar5 = *(u32*)(param_2 + 0x64)` (IP_A), `uVar9 = *(u32*)(param_2 + 0x6c)` (IP_B)
- `*(u32*)(param_2 + 0x74)` = the two L4 ports (low16 + high16)
- `*(u32*)(param_2 + 0x60)` byte>>0x10 → param_4[0x13]
Writes (each a ushort, little-end byte0+byte1*0x100):
- param_4[0x13] = (param_2[0x60]>>16)&0xff                 [misc: proto/flags]
- param_4[0x15] = IP_A bytes [ (uVar5>>8)&ff , uVar5&ff ]   ; param_4[0x17] = IP_A [ (uVar5>>24), (uVar5>>16) ]
- param_4[0x19] = IP_B bytes [ (uVar9>>8)&ff , uVar9&ff ]   ; param_4[0x1b] = IP_B [ (uVar9>>24), (uVar9>>16) ]
- param_4[0x1d] = port_lo16(*(param_2+0x74)) ; param_4[0x1f] = port_hi16(*(param_2+0x74))
⇒ v4 key uses ~7 extra_data shorts (extra_data0..6): {misc, IP_A.hi, IP_A.lo, IP_B.hi, IP_B.lo, portX,
portY}; extra_data7..19 = 0. (The IPv6/other branch @49430-49442 fills param_4[0x1f..0x37] = more shorts.)
OPEN (resolve empirically on mainline w/ the 4 captured sport->slot pairs): which IP is src vs dst
(0x64 vs 0x6c), port order at 0x74, and the byte-endianness into the key — build the key both ways,
run mainline `hashcalc`, pick the combo whose raw hash masks to the captured slot. Then the MASK:
try M∈{0xff,0x1ff,0x3ff,0x207} so all 4 (sport->slot) pairs reproduce.

### Stage 2b assembly status — discovery DONE, remaining = assembly
HAVE (verified): HW hash engine (zx_cla_hash_raw), CLA write protocol (zx_cla_write_hash), key
structure (45B: outport/inport/tag/l2/pppoe/ex_rule/direct/extra_data0..19), v4 extract mapping.
TODO (mechanical): (a) python/C key-builder = pack {mainline outport,inport, extra_data from 5-tuple}
into 12 words w/ the 1-bit-shift; (b) find mask via the 4 captured pairs on mainline hashcalc;
(c) cls_flower_add: build key->zx_cla_hash_raw->slot->build 15-word ram2 entry->clawrite; (d) isolated
hw_trap test.

## ★★ UPDATE 2026-06-04g — STOCK vs MAINLINE hash CONTRAST: IDENTICAL (config validated)
User asked: shouldn't we contrast mainline's hash against stock (and can we even read stock?). Answer:
YES on both. The earlier `fpga -r 0xe30bf` "no output" was the WRONG PROTOCOL (trigger before load) —
with the correct sequence the engine computes and the read LOGS fine on stock via /dev/logger_main.
Drove BOTH engines (stock via fpga -w/-r, mainline via debugfs hashcalc) with identical keys:
  key [0xdeadbeef, 0x12345678] → stock 0xd738 == mainline 0xd738
  key [1]                      → stock 0x6f41 == mainline 0x6f41
  key [0,0,1]                  → stock 0x1665 == mainline 0x1665
⇒ **mainline's CLA hash engine is configured IDENTICALLY to stock** (same poly cfg, not uninitialized).
CONSEQUENCES (de-risks Stage 2b):
- the captured stock (sport→slot) pairs (0x5a/0x48/0x35/0x0a) are VALID ground truth for mainline;
- mainline's install-time hash (engine) == its ingress-time packet hash (same silicon block) — so an
  entry written at engine-computed slot is where the HW will look on ingress;
- we now have a stock hash oracle too: load 0xe30b1..0xe30bc via fpga -w, trigger fpga -w 0xe30b0 1,
  read fpga -r 0xe30bf (logs to /dev/logger_main with the right protocol).
Stock-driver fpga recipe (verified): zero 0xe30b1..0xe30bc, write key words, write 0xe30b0=1, read 0xe30bf.

## ★★ UPDATE 2026-06-05 — slot-sweep NEGATIVE → ram2-alone insufficient; ram0/ram1 extract chain MISSING on mainline
End-to-end slot-sweep on mainline (hashcalc-verified key builder, branch phase6-hw-offload):
- Built the v4 key + the 15-word ram2 fwd entry for a real flow (192.168.9.50:40000->172.31.9.50:5201
  TCP, ingress lan4). KEY EXTRACT byte-order pinned by matching the captured stock template: entry/key
  shorts = [proto, IP_A.hi=(o0<<8|o1), IP_A.lo=(o2<<8|o3), IP_B.hi, IP_B.lo, sport, dport] (natural
  order, NO bswap). Offline CRC-32C == HW engine confirmed for this flow's key (raw 0xf8ad etc.).
- Wrote the entry at all 6 inport-candidate buckets (mask 0xff: 0x89/0x6a/0x41/0xa2/0xc6/0x25) — all
  were EMPTY pre-write (no clobber). Drove 60 SYNs on the matched 5-tuple + 60 on a control sport.
- RESULT: matched-flow hw_trap delta = 60, control delta = 60 → **NO forward; the flow still traps
  every packet, identical to control.**
- ROOT CAUSE (confirmed): `clapeek ram0 0x9` on mainline = ALL ZEROS. The stock extract descriptor
  (ram0[0x09] = 93929190 97969594 9b9a9998 9f9e9d9c 00150051) is ABSENT on mainline. Without the ram0
  extract config + a ram1 rule to trigger it, the HW never computes the ram2 hash for routed flows and
  traps everything — exactly the long-standing "CLA traps all" deadend (memory zte-hw-forwarding-deadend).
### Conclusion / re-scope
A HW forward needs the FULL classification chain, not just a ram2 entry:
  (1) ram0 extract config (so the HW pulls the same packet bytes my key-builder assumes),
  (2) a ram1 rule that matches the flow class and routes it into the ram2 hash (with MAINLINE ports),
  (3) the ram2 forward entry at the computed slot.
The verbatim-replay set all three but with STOCK ports (clobbered mainline's classifier). Stage 2b's
real remaining work = parameterize ram0 + ram1 for mainline (extract config can reuse stock's
ram0[0x09]; the ram1 rule needs mainline winoffsets/inport), THEN the ram2 entry + slot from the
(now-validated) HW hash. The hash engine, write protocol, key builder, and extract byte-order are all
validated; the gap is the ram0/ram1 enablement of the hash path.
Tools added: scripts/hw_slot_sweep.py (key/entry/bucket builder), scripts/hw_slot_sweep_run.py (sweep).
