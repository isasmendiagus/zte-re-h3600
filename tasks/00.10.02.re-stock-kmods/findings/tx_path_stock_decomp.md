# TX path — stock `pon_tm_data_raw_send` + `pon_tm_net_tx` + `soft_insert_tx_1desc`

Source: Ghidra headless decompile (Jython script) of `plat-zxylzb_9128S.ko`,
captured 2026-05-24. Full raw decomp:
[`decomp_pon_tm_2026-05-24.txt`](decomp_pon_tm_2026-05-24.txt).

## Descriptor byte map (what stock writes to a 16-byte TX desc)

`pon_tm_net_tx` initializes:
- `*puVar3 = 0x80;` → desc[0..3] = `80 00 00 00`
- `*(u8*)puVar3 = 0xc9;` → desc[0] = `c9` (overrides byte 0)
- `puVar3[1] = 0x10000;` → desc[4..7] = `00 00 01 00` (so desc[6] = 1)
- `puVar3[2] = 0x1000000;` → desc[8..11] = `00 00 00 01` (so **desc[11] = 0x01** — VALID bit)
- `puVar3[3] = 0;` → desc[12..15] = 0

Then `pon_tm_data_raw_send(skb, desc, dir)` patches it:
- `desc[11] = (desc[11] & 1) | 0x20;` → **desc[11] becomes 0x21**, NOT 0x01
- `desc[7] = (desc[7] & 1) | ((bp_idx & 0x7f) << 1);` → low 7 bits of bp_idx into bits 1..7
- `desc[8] = bp_idx >> 7;` → high bit of bp_idx into desc[8] bit 0
- `*(u32*)(desc+8) = (*(u32*)(desc+8) & 0xff8001ff) | (len << 9);`
  → bits 9..22 of dword carry 14-bit len, preserving bp_hi and desc[11]

So final stock TX desc[11] = **0x21** (bit 0 = VALID, bit 5 = format/CPU marker).

Our driver currently writes **0x01** only — bit 5 missing. This is the
top-suspect for the intermittent ping bidi.

## Length field — two encodings, both = len for normal packets

`desc[12..13]` (LE u16): `(desc[12..13] & 3) | (len << 2)`
`desc[8..11]` (LE u32): adds `len << 9` into bits 9..22

For small packets (`len < 0x40` AND param_3==0 AND `desc[14] & 1 == 0`):
- zeropad to 0x40 via `__memzero(__dest + __n);` (so bp_buf gets the pad)
- `desc[12..13] = (desc[12..13] & 3) | 0x100;` (= 0x40 << 2)
- `desc[8..11] |= (0x40 << 9);`

So short ARP/ICMP (42 / 84 bytes) get padded to 64 in BMU AND in desc.
Our driver pads to 0x21 = 33 — **too short by 31 bytes**.

## Single kick — NOT both UP and DOWN

`soft_insert_tx_1desc(desc, dir)` is just two lines:
```c
dma_cache_maint(desc, 0x10, 1);
if (dir == 0) TM[+0x10054] = 1;  // upstream
else          TM[+0x10064] = 1;  // downstream
```

**Stock kicks ONE register per skb, never both.** Our driver kicks both,
which doubles the BMU-pool churn and likely causes duplicate egress.

## TX direction selection

`pon_tm_net_tx` calls `pon_tm_get_next_txdesc(0)` (upstream ring). All
LAN-egress packets go UP-stream from CPU. The DN ring is for received
GPON traffic going BACK to GPON line (we don't have GPON, so DN is
effectively unused for our use case).

→ Our driver should call only `TM[+0x10054] = 1`.

## CPU-port marker — desc[0] = 0xc9

Initial dword write puts `0x80` at desc[0], then byte write puts `0xc9`.
0xc9 = `1100 1001` — likely CPU/upstream source marker. We currently
write `desc[0] = 0x80`. Worth investigating if 0xc9 makes any difference.

## Ethertype filter — special-case for OAM/802.1X-ish

```c
ethertype = bswap16(*(u16*)(skb->data + 12));
if (ethertype == 0x884c || ethertype == 0x8899) {
    // ZTE OAM / vendor — skip the QoS path
} else {
    // normal path — go through dev_qos_select_queue
}
```

Not relevant for ICMP/ARP traffic; ignore for now.

## Action items (in order of likelihood-of-fix)

1. **Set desc[11] = 0x21** (was 0x01) — highest priority, missing bit 5
2. **Pad short packets to 0x40** (was 0x21) — under-padded by 31 bytes
3. **Kick only TM[+0x10054]** (was both UP+DN) — may eliminate DUPs
4. Try desc[0] = 0xc9 (was 0x80) — CPU marker
