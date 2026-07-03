# CLA windata packer DERIVED & PROVEN CORRECT — but #456 cannot content-match a nonzero key (2026-07-02)

Device: mainline **#456** (`Linux (none) 6.6.0 #456 Thu Jul 2 19:04:20 UTC 2026`), live, NO reboot.
Rig: host `enxc8a362e95900` = 172.31.9.50/24 on device **lan1** (also 192.168.1.50/24 tftp);
device lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1; route 192.168.9.0/24 via 172.31.9.1;
static gw ARP 172.31.9.1→f4:f6:47:0f:42:64. Flow: UDP **172.31.9.50:50010 → 192.168.9.50:53**.

## HEADLINE

The windata packer is **definitively derived and PROVEN CORRECT** by two independent methods
that reconcile exactly. **But the derived-correct per-flow entry MISSES on #456** — the gate is
NOT the windata layout. It is the previously-documented **#452/#456 CLA hash-lookup ENGINE
regression**: on this boot the lookup **only ever ACCEPTS a match when the extracted key is zero**
(rule 0x98 empty-extraction → zero-windata catch-all forwards). A byte-exact-correct nonzero
5-tuple entry, with the live HW-extracted key confirmed matching field-for-field, is REJECTED
(LOOK_UP_MISS 0x54). This session **disproves the cla_gate2 "packing gate" hypothesis** and
re-confirms the engine/init regression with a rigorous fresh analysis.

## STEP 1 — the windata→offset table (both methods, RECONCILED)

**Definitive layout for a v4 UDP/TCP 5-tuple** (windataN = LE16 at entry byte `0x13 + 2N`):

| field | windata | entry byte | value = | example (our flow) |
|---|---|---|---|---|
| proto | windata0 @0x13 | 0x13/0x14 | proto in LOW byte, hi byte 0 | 0x0011 |
| srcIP[0:1] | windata1 @0x15 | 0x15/0x16 | (src[0]<<8)\|src[1] = srcIP>>16 | 0xac1f |
| srcIP[2:3] | windata2 @0x17 | 0x17/0x18 | src&0xffff | 0x0932 |
| dstIP[0:1] | windata3 @0x19 | 0x19/0x1a | dstIP>>16 | 0xc0a8 |
| dstIP[2:3] | windata4 @0x1b | 0x1b/0x1c | dst&0xffff | 0x0932 |
| sport | windata5 @0x1d | 0x1d/0x1e | ntohs(sport) | 0xc35a |
| dport | windata6 @0x1f | 0x1f/0x20 | ntohs(dport) | 0x0035 |
| (unused) | windata7..19 | 0x21..0x3a | 0 | 0 |

Each windata is stored as a native u16 whose VALUE equals the packet's 16-bit window read in
**network (big-endian) order**. In little-endian entry-byte terms that is byte0x13=proto,
byte0x14=0, byte0x15=src[1], byte0x16=src[0], … i.e. the IP octets appear byte-swapped-per-u16.

### Method (a) — decode of the CAPTURED STOCK entry + its live key (authoritative)

The task's `ram2[0x99]` is stock's **downstream/reverse** entry (src 80.249.99.148, dst
10.44.66.222, sport 80, dport 0xeb2c). Byte-decoding it (LE words → byte stream, windataN @
0x13+2N):
`windata0=0x0006(proto)`, `windata1=0x50f9`, `windata2=0x6394`, `windata3=0x0a2c`,
`windata4=0x42de`, `windata5=0x0050`, `windata6=0xeb2c` — exactly {TCP, src 80.249.99.148,
dst 10.44.66.222, sport 80, dport 60204} in the table layout above.

**PROOF the layout is the actual compare layout:** I bit-extracted stock's LIVE downstream
`gparsehashkey` `4c000000 a1f2000d 1458c728 00a085bc 000191e0` (extra_data fields at bit
`33+16·n`): field0=0x06, **field1=0x50F9**, … The stored `ram2[0x99].windata1 = 0x50F9`
**exactly equals** the extracted field1. Stock stored byte-aligned windata @0x13 and it
HW-forwarded → byte-aligned @0x13 **is** the correct compare layout. (The bit-33 anchor is only
the extracted-key packing; the stored entry is plain byte-aligned, no shift.)

### Method (b) — `tm_acl_get_fastHashRule` (@0x57218) + the driver's already-correct packer

The v4 branch (`param_1==0`, lines 213–234) scatter-copies the flow-key descriptor
(`memcpy(auStack_78, param_2+0x60, 0x50)`) into `param_4[0x13,0x15,0x17,…]`. Reconstructed, it
produces the SAME field→offset mapping as the table. The mainline driver's
**`zx_ft_pack_cla()` (zx-eth-main.c:2293) already implements this byte-exactly** — for our flow
it emits the proven #444 entry:
`03005044 fa11c000 00000608 80000000 11000049 32ac1f00 32c0a809 35c35a09`
(windata0@0x13=0x0011, windata1@0x15=0xac1f, …, windata6@0x1f=0x0035). ✔ matches method (a).

**⇒ Both methods reconcile. There is no "other layout" to try — the packer is settled and the
production code (`zx_ft_pack_cla`) is already correct.** The raw-5-tuple→15-word packer:
```
w0=0x03005044; w1=0xfa11c000; w2=0x00000608; w3=0x80000000(valid);
w4=(proto<<24)|0x00000049; w5=(s3<<24)|(s0<<16)|(s1<<8);
w6=(d3<<24)|(d0<<16)|(d1<<8)|s2; w7=((dp&0xff)<<24)|((sp>>8)<<16)|((sp&0xff)<<8)|d2;
w8=(dp>>8)&0xff; w9..w14=0.   (s=ntohl(src) octets s0..s3; d=ntohl(dst); sp/dp=ntohs)
```

## STEP 2 — build + test on #456 (rule 0x90 forced)

Setup (all RAM-only via debugfs): PM re-installed (ram1[5]=`c0a80932 bd22b42b 0000cc29`,
ram0[5]=`0de80005 0014035c`, ram6[5]=`00000005`, ram3[5]=`00800000`); `ram0[9]` word4 forced
`0x00150001` (rule 0x90); entry via `fill520` (520/520) + verified at bucket **0xd5**
(`clapeek ram2 0xd5` = the entry, byte-exact); `hashcalc(48000000 583e0022 81501265 86b41265
0000006b)` → raw **0xf6d5 → bucket 0xd5** ✓. Live `gparsehashkey` during the flow confirmed
`48000000 583e0022 81501265 86b41265 0000006b` (ex_rule_id 0x90, nonzero 5-tuple), key words
5..11 = 0 (only 7 windows — no windata7+ mismatch).

400-pkt bursts (pinned src 172.31.9.50:50010), counters cla_tx_fwd `0x9238c3c0`,
cla_tx_trp `0x9238c3c4`, acl_required `0x9238c3b8` (hi16=submitted / lo16=trapped),
desOut rsn `0x9238c39c` (bits[29:23]):

| entry (word3 / word4 / w5..w7) | acl hi16 Δ | cla_tx_fwd Δ | cla_tx_trp Δ | desOut rsn |
|---|---|---|---|---|
| base 5-tuple `80000000`/`11000049`/tuple | +407 | **0** | +406 | 0x54 MISS |
| +da_known `80000000`/`11100049`/tuple | +~409 | **0** | +409 | 0x54 MISS |
| +da_known+direct `80000000`/`11100069`/tuple | +~400 | **0** | +~400 | 0x54 MISS |
| **X1: nonzero key + ZERO windata** `80000000`/`00000049`/0 | +400 | **0** | +400 | 0x54 MISS |

All MISS. The exact winning template does not exist on #456 for a nonzero key.

## STEP 3 — selectivity NOT reached; but the FORWARD CHAIN is proven working

**Positive control (rule 0x98 empty-key + zero-windata catch-all):** cla_tx_fwd **+400** and
**MAC4 TX-ok `0x92300718` +400** (0x0424→0x05b4) — 400/400 packets physically egress lan4/WAN
with the PM index-5 next-hop rewrite. So the whole downstream chain (verdict → PM next-hop →
lan4 wire egress) is intact; the ONLY broken element is the nonzero content-match.

## VERDICT — it is the ENGINE, not the packing

Four data points on #456 pin the failure precisely:

| extracted key | stored windata | result |
|---|---|---|
| ZERO (rule 0x98 empty) | zero | **FORWARD** (400/400, incl. wire) |
| ZERO (rule 0x98) | nonzero | MISS (cla_gate2 CONTROL a) |
| NONZERO (rule 0x90) | zero | MISS (X1 this session) |
| NONZERO (rule 0x90) | **byte-exact-correct** 5-tuple | **MISS** ← smoking gun |

The engine performs a genuine content compare (it rejects zero-key vs nonzero-windata), yet the
effective compared windata behaves as **always zero**: it ACCEPTS only when the extracted key
is zero and REJECTS a provably-correct nonzero match. Since (i) the layout is proven correct by
stock's own matched fwd/key pair, (ii) `zx_cla_write_hash` stores words at the same data_ids as
stock's `cla_set_hash_table` (descending, CMD-first) and clapeek reads them byte-exact, (iii)
the extraction produces the correct nonzero key live, and (iv) da_known/direct/extra-windows are
all ruled out — the gate is the **#452→#456 CLA hash-lookup ENGINE / init-operation regression**
(config-register-identical to stock per the earlier full-block diff; lives in a CLA
indirect-RAM field or a dropped init-OP in the #444→#452 driver refactor).

## Recommendation for productization / next session

- **The packer is DONE.** `zx_ft_pack_cla` (raw 5-tuple → 15-word entry, table above) is
  byte-correct and needs no change. A fresh stock capture of a controlled 5-tuple would only
  re-confirm this layout — it is already proven; that fallback is **not** the bottleneck.
- **The real blocker = the nonzero-compare engine regression.** Next step is the
  **#444→#452 driver-code bisect** of the PM-ops-bridge / FFE-arm refactor for a
  reordered/dropped CLA hash-table init-OP, and/or a **stock↔#456 diff of the CLA INDIRECT RAMs
  during a live nonzero hash HIT** (occupancy/valid bitmap, ram0 extract-index, per-bank state)
  — NOT any entry-content or direct-register change (both exhausted).
- Interim capability: the rule-0x98 zero-key **catch-all forward** works end-to-end on #456
  (forwards all classify-submitted routed transit) — usable as an explicit "offload-everything"
  mode, but NOT per-flow selective until the engine regression is fixed.

## State left behind (device healthy, NO reboot)
- Device on **#456**, alive; UART bridge + REPL responsive; console loglevel 8.
- **ram0[9] RESTORED to `0x00150051`** (clapeek readback-confirmed).
- ram2 hash banks **cleared** (fill520 all-zero → valid_en off → inert; no active catch-all).
- PM ram0/1/6[5]=installed, ram3[5]=0x00800000 (RAM-only, harmless without a matching entry).
- Host rig intact: `enxc8a362e95900` has 192.168.1.50/24 **and** 172.31.9.50/24; route
  192.168.9.0/24 via 172.31.9.1; static ARP 172.31.9.1→f4:f6:47:0f:42:64. No reboot, no flash.
