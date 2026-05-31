# CLA classifier indirect-RAM layout (ram_id 0/1/2-6/7) — and why CLA is NOT the port1 gate

Status: RE from stock `decomp_all_tm.c` + live `clapeek`/`cladump` verification on the H3600 (2026-05-31).
(Moved here from the cross-session memory store so it lives with the kmod RE findings.)

## The CLA indirect interface
One indirect iface: `CLA_REG_CMD=0x1CC014` (`cmd = addr | ram_id<<22 | rw<<27`), 17 data slots @ `0x1CC01C`,
done bit @ `0x1CC018`. Driver's `zx_cla_write_entry`/`zx_cla_read_entry` (zx-eth-main.c:1994/2007) are
generic; the meaning of the 17 words depends entirely on `ram_id` — they select DIFFERENT tables:

| ram_id | stock fn (decomp_all_tm.c) | size / words | what it is | per-inport? |
|--------|----------------------------|--------------|-----------|-------------|
| 0 | `cla_set_extra_index_table` @0x14200 (:2650) | 16 ent, 5 words | byte-extractor descriptor (`extract_index0..15`, `ext_mode`) | **No** (portless; confirms zte-spa-matchram-not-gate) |
| 1 | `cla_set_extra_rule_table` @0x146e0 (:2870) | 160 ent, 17 words | rule TCAM: `winoffset0..19`+`winmask0..19`+flags. byte0x39 bit5=`inport_mask` FLAG, bit4=`outport_mask` (:2988-2991) | flag only, not a value |
| 2..6 | `cla_set_hash_table` @0x15a14 (:3366) | 520 ent, 15 words; addr picks bank (0..0xff→2, 0x100..0x17f→3, 0x180..0x1bf→4, 0x1c0..0x1ff→5, 0x200..0x207→6; :3496-3520) | classification RESULT/hash table — holds the actual **`inport` VALUE** + trap action | **Yes** |
| 7 | `cla_set_cpu_queue_id` @0x16980 (:3957) | trap-queue, data[0]=qid | per-(ptype,port) CPU trap-queue | per-port |

### Field offsets (ram2-6 hash/result table)
- `inport = (byte[0x0e] & 0x3f) << 6 | (byte[0x0d] >> 2)` (decomp:3399-3402)
- trap action: `cpu_qid` = byte6 field + `cpu_qid_rp_en` (:3458-3461); `valid_en`/`direct` in byte[0x10]
- Higher-level: `sw_acl_setMtchInfo` (decomp_all_switch.c:1035) sets the HFF flow inport at offset 0x9e = switch port (pon/ptm0 → 5).
- Remap: logical {0,1,2,3} → regport {1,2,3,4}; CLA inport = regport.

## port1 verdict: CLA is NOT the gate (static table + LIVE read both confirm)
`zx_cla_table.h` is a bit-exact boot snapshot (gen_cla_table.py). It has 724 ram1 + 56 ram2 entries
(NO ram3/4/5/6; ram7 generated at runtime). Decoded the 56 ram2 `inport` fields:
`inport 0(CPU)=16 (direct=1); inport 1/2/3/4/5 = 8 each`. regport2 (= logical port1, the FAILING port)
has 8 rule slots byte-identical to working regport3's 8 slots, differing only in the inport/outport bytes.

LIVE verification (clapeek, 2026-05-31): read regport2 (ram2 addrs 0x21/0x93/0x121) vs regport3
(0x79/0xcb/0x179). regport2 entries read back VALID (valid_en set, action present) — the indirect write
did NOT fail. Differences are word3 inport (`…0817` vs `…0c17`) + word4 outport (`…42` vs `…43`) as expected,
plus a word0 content difference (regport2 ~0x0100006d vs regport3 0x01005055) that is rule-content, not a
validity/action defect. Since the live port1 drop is UPSTREAM of CLA (SDET uni1 transport=2 vs uni2/3=229/230,
SIPC drop=0 — see port1_sdet_ingress_gate_re.md), the CLA is downstream of the drop and exonerated.

Snapshot caveat: the snapshot is port-SYMMETRIC (not biased to the capture-time active port), but only
56/520 ram2 slots were captured and ram3-6 are empty — mainline leaves the upper hash banks empty vs stock.
That is per-slot sparsity, not per-port, so it does not single out port1.

## clapeek/cladump recipe
`echo "<ram_id> <addr>" > /sys/kernel/debug/zx_eth/clapeek` → 17 words to kmsg. `cat .../cladump` → ram7
trap qid per (ptype,port). FAILING regport2 ram2 addrs: `21 93 121 193 221 293 321 393`; WORKING regport3:
`79 cb 179 1cb 279 2cb 379 3cb`.
