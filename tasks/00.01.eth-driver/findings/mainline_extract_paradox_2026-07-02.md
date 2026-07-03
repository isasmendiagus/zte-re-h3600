# Mainline CLA extract "zero-key" paradox — CRACKED: it's RULE SELECTION, not a zero key (2026-07-02)

## Headline (resolves the paradox)

On a **fresh** mainline #456 boot the CLA hash-key extraction **works** and produces a
**non-zero, live** `gparsehashkey` for the submitted UDP flow. The "all-zero key" from the
prior session was **not reproducible on a clean boot** — it was an artifact of that session's
polluted CLA indirect state. The real gap is **CLA extract-RULE SELECTION**, governed by the
**indirect** RAMs (`ram0[9]` index_valid + `ram1[*]` rules) that the mainline driver **never
loads** (it replays only the DIRECT-register stock dump). The bootROM leaves an index_valid of
`0x00150051` whose highest-priority enabled rule is **0x96 — a non-L3-relative rule that
extracts a per-packet VOLATILE key**. Stock's userland CLA-init instead enables rule **0x98**
(a copy of the clean L3-relative 5-tuple rule) as the highest index → clean matchable key.

**Forcing the clean rule on mainline (ram0[9] word4 → 0x00150001, rule 0x90 only) instantly
produced the byte-clean, perfectly stable 5-tuple key** `48000000 583e0022 81501265 86b41265
0000006b` — identical in form to stock's. So the extract engine, parser anchor, and rule 0x90
are all correct and present on mainline; only the **rule-selection config** was wrong.

**Caveat (a SECOND, separate gate remains):** even with the clean stable key AND the byte-exact
5-tuple entry filled into all 520 buckets, `cla_tx_fwd` stayed **0** (every packet still
LOOK_UP_MISS/trapped). So the extract fix is **necessary but not sufficient** — the previously
documented CLA hash-**lookup/compare** gate (zte-flowoffload-framework "#452 lookup regression")
is still open, now with a confirmed-clean key upstream of it.

Fresh boot confirmed: banner `Linux (none) 6.6.0 #456 Thu Jul 2 19:04:20 UTC 2026`; dmesg
`[79.898] SPA trap_dmac filter cleared`; `[83.386] PM ops registered`. Rig: host
enxc8a362e95900=172.31.9.50/24 on lan1 (the carrier/ingress port this boot), device lan1=
172.31.9.1, lan4=192.168.9.1, ip_forward=1. Host uses a static ARP for the gateway
(172.31.9.1→f4:f6:47:0f:42:64) to bypass the port1 CPU-ARP wedge; the HW-classify path needs no
CPU. Flow submission confirmed: acl_required climbs 1:1 with flow packets.

Register access via debugfs `/sys/kernel/debug/zx_eth/`: `poke` (peek/poke), `mem` (binary
window, one correlated 512-B `memcpy_fromio` read per sample), `clapeek`/`clawrite` (CLA
indirect), `hashcalc`, `fill520`.

---

## STEP 2 — correlated samples, UDP flow (DEFAULT ram0[9]=0x00150051 → HW picks rule 0x96)

Flow: UDP 172.31.9.50:50010 → 192.168.9.50:53, sustained. Each row is one 512-byte correlated
read (gparsehashkey 12w @0x9238c260 + desIn w3/w4/w5 + desOut0 + acl/fwd/trp).

| # | gparsehashkey (w0..w9) | desIn w3 | w4 | l3_en | l3off_v4 | acl | fwd | trp |
|---|---|---|---|---|---|---|---|---|
|1|`4b000000 c5d39000 1000b200 00888a00 8001a88c ce6c8022 1265583f 12658150 006b86b4 00000060`|82610841|00001c18|1|14|06dc06dc|0|00000749|
|2|`4b000000 c5d39000 1000b200 00888a00 8001ab24 cbd48022 1265583f 12658150 006b86b4 00000060`|82610841|00001c18|1|14|07260726|0|00000793|
|3|`4b000000 c5d39000 1000b200 00888a00 8001adc2 c9368022 1265583f 12658150 006b86b4 00000060`|82610841|00001c18|1|14|07710771|0|000007de|
|4|`4b000000 c5d39000 1000b200 00888a00 80015d40 19ba8022 1265583e 12658150 006b86b4 00000060`|82610841|00001c18|1|14|36aa36aa|0|0000372a|
|5|`4b000000 c5d39000 1000b200 00888a00 80015ffc 16fe8022 1265583e 12658150 006b86b4 00000060`|82610841|00001c18|1|14|36f536f5|0|00003775|
|6|`4b000000 c5d39000 1000b200 00888a00 800162c0 143a8022 1265583e 12658150 006b86b4 00000060`|82610841|00001c18|1|14|373f373f|0|000037bf|

- word0 = **0x4b000000 → ex_rule_id 0x96** (`((w0>>16)<<17)>>24 = 0x96`).
- desIn w3=0x82610841: **l3_en=1** (bit6 low byte), **udp_flag set** (high byte 0x82; cf. TCP=0x81 below). w4=0x1c18 → **l3_offset_v4 = 14 (VALID)**, l4_offset=34, l2_offset=12.
- **words 4-5 CHANGE every read** (8001a88c/ce6c → 8001ab24/cbd4 → …) = a per-packet
  volatile/hash-timestamp field baked INTO the extracted key. Words 1-3 and 6-9 are stable.
- acl climbs 1:1 (submitted); fwd=0, trp climbs (all LOOK_UP_MISS — no matching entry).

**The key is NON-ZERO and live.** At the very first pre-flow idle read it was **all-zero**
(`00000000 …`), so the flow POPULATED it. But it carries a **volatile field** (rule 0x96's
anchor) → every packet of the same flow hashes differently → no stored entry can ever match.

### Staleness verdict (the task's core question)
- Fresh-boot idle (before any flow): gparsehashkey = **all zero** (never extracted).
- During the UDP flow: **non-zero**, concurrent with a valid anchor (desIn l3_en=1,
  l3_offset_v4=14, udp_flag) on **every** sample.
- After the flow stops: the stable key CONTENT latches (held); desIn drops to l3_en=0.
- **⇒ The zero key is NOT real for a clean mainline.** The prior "all-zero mid-burst" reading
  was an artifact of that session having written `ram0[9]=0x00150151` (enabling rule 0x98) while
  `ram1[0x98]` was EMPTY → HW selected rule 0x98, the rule extracted nothing → word0=0x4c
  (ex_rule_id 0x98) + words1-11 zero (exactly the prior finding's value). Same root cause,
  different symptom.

---

## STEP 3 — TCP flow (raw SYNs, src 172.31.9.50:50011 → 192.168.9.50:53)

| # | gparsehashkey (frozen) | desIn w3 | w5 | l3_en | acl | fwd | trp |
|---|---|---|---|---|---|---|---|
|1-4|`4b000000 c5d39000 1000b200 00888a00 80018602 f0f68022 1265583f 12658150 006b86b4 00000060`|**81610841**|00006c44|1|**3b283b28 (FROZEN)**|0|4107→41e6 (climbs)|

- desIn w3=**0x81610841**: high byte **0x81 → tcp_flag** (vs UDP's 0x82 udp_flag) — the flag
  correctly reflects the L4 protocol. l3_en=1, l3off_v4=14 valid.
- **acl_required FROZEN** and **gparsehashkey FROZEN** (its volatile counter stops), yet **trp
  climbs** ⇒ the TCP SYNs ENTER the CLA (desIn updates) but are **trapped pre-classify** and are
  **NOT submitted to the forward/extract engine**. This is the **TCP_SYN trap** (trapPktType
  0x5a) — by design so the CPU sees the handshake for conntrack.
- **UDP vs TCP difference:** UDP data packets are submitted to classify (extract runs); bare TCP
  SYNs are not (SYN trap). This is NOT a mainline defect — a real established TCP data flow would
  be submitted like UDP. I have no responder at 192.168.9.50, so I could not establish a real TCP
  connection to test data-packet extraction; the UDP result already proves the extract engine.

---

## STEP 4 — localize the "zero"/wrong key (the decisive probes)

### CLA indirect config, FRESH boot (clapeek), vs stock
| entry | FRESH mainline | stock (findings/stock_extraction_config) |
|---|---|---|
| ram0[9] word4 (index_valid) | **0x00150051** → rules {0x90,0x94,0x96} | **0x00150151** → {0x90,0x94,0x96,**0x98**} |
| ram1[0x90] (5-tuple, L3-rel) | `22038608 000058a1 00 00 f00ff000 ff.. 0fffffff 0.. 00700000 **00092492**` (offset_type=2 all) | identical |
| ram1[0x94] (3-tuple) | `22038608 00000001 … 00500000 00002492` | (present) |
| ram1[0x96] (volatile) | `e1828406 16284880 01e3868c 00264889 fff00000 ff.. **db6db6db 00036db6**` (offset_type≈6, NOT L3-rel) | (present) |
| ram1[0x98] (clean 5-tuple) | **ALL ZERO (empty)** | `22038608 000058a1 …` = clean rule |

**⇒ localization:** the "zero"/volatile key is **NOT** a packet-bytes problem and **NOT** an
L3-relative-anchor failure. The L3-relative 5-tuple rule (0x90, offset_type=2) is present and
correct on mainline. The failure is that **HW selects rule 0x96** (highest-index enabled rule;
0x96 uses a non-L3-relative anchor → volatile key). Stock selects rule 0x98 (== clean 0x90) as
its highest index. The selection is set by the **indirect ram0[9]/ram1** the driver never writes.

### 4-negative / positive controls (bounded reversible ram0[9] edits)
- **Force rule 0x90** (`ram0[9] word4 = 0x00150001`), UDP flow, 3 reads — ALL identical & STABLE:
  `gparsehashkey = 48000000 583e0022 81501265 86b41265 0000006b 00000000×7`
  word0=**0x48 → ex_rule_id 0x90**; words 5-11 zero; **no volatile field**. desIn unchanged
  (82610841 / l3off 14). This is the clean L3-relative 5-tuple key, exactly stock's form.
  (Frame-relative variant in the task, STEP 4b, was unnecessary — the L3-relative rule 0x90 is
  proven working; the volatile rule 0x96 is the culprit, not the anchor type.)

### End-to-end forward test (with the clean key) — SECOND GATE EXPOSED
- With rule 0x90 forced, installed the byte-exact 5-tuple entry into all 520 buckets:
  `fill520: 03005044 fa11c000 00000608 80000000 11000049 32ac1f00 32c0a809 35c35a09 0×7`.
- windata verified to match the packet's L3-relative windows byte-for-byte:
  N0..N6 (LE16 @ ram2 byte 0x13+2N) = {0x0011, 0xac1f, 0x0932, 0xc0a8, 0x0932, 0xc35a, 0x0035}
  = {proto UDP, src 172.31.9.50, dst 192.168.9.50, sport 50010, dport 53}.
- hashcalc(clean key) → raw 0xf6d5. fill520 covers all buckets so slot is irrelevant.
- **RESULT: cla_tx_fwd stayed 0, trp kept climbing.** LOOK_UP_MISS despite clean key + correct
  windata in every bucket. ⇒ reproduces the documented **#452 hash-lookup/compare gate**,
  now upstream-clean.

---

## Best single hypothesis + next concrete test

**Hypothesis (extract paradox — SOLVED):** the mainline empty/wrong key is a **CLA
extract-rule-SELECTION** bug. The driver replays only DIRECT registers, so the **indirect**
`ram0[9]` index_valid keeps the bootROM default `0x00150051`, whose highest-priority enabled
rule is **0x96 (non-L3-relative → volatile key)**. Stock's CLA-init sets `0x00150151` and loads
`ram1[0x98]` with the clean L3-relative 5-tuple rule, so its highest index (0x98) extracts a
clean matchable key. **Fix (driver, static, one-time at CLA init):** either (a) write
`ram0[9]` so the highest enabled index is the clean 5-tuple rule — e.g. `0x00150011` or
`0x00150001` (drop rule 0x96; rule 0x90 is already present & correct, no ram1 write needed), OR
(b) load `ram1[0x98]` = ram1[0x90] and set `ram0[9]=0x00150151` to mirror stock exactly.
Prefer (a): it needs no indirect-rule content, just the correct index_valid.

**Next concrete test (the residual SECOND gate):** with rule 0x90 forced (clean key) — the
present state minus my restore — the byte-exact entry in all 520 buckets still MISSES. This is
the separate CLA hash-lookup/compare verdict gate (zte-flowoffload-framework). The clean-key
result now lets that be chased without the extract confound. Sharpest next probe: MMIO-trace
stock's CLA lookup at the moment a flow flips trap→forward, OR diff the per-bucket
occupancy/used-count indirect field (ram2..ram6 metadata) stock-vs-mainline while stock
forwards — the compare verdict most likely depends on an occupancy/enable bit that fill520's
15-word entry write does not set. The key/windata/slot are all now proven correct.

---

## State left behind (device healthy, NO reboot)
- Device on **mainline #456**, fresh boot, console REPL + UART bridge alive, rig intact
  (host 172.31.9.50 on lan1, static gw ARP; lan1=172.31.9.1, lan4=192.168.9.1, ip_forward=1).
- **ram0[9] RESTORED to default 0x00150051** (readback-confirmed).
- `fill520` left the 5-tuple entry in ram2..ram6 (RAM-only, INERT — all LOOK_UP_MISS; clears on
  next DTR boot). No ram1 edits were made. All other access read-only (poke-peek / mem / clapeek).
- Host NIC moved from 192.168.1.50 (U-Boot TFTP) to 172.31.9.50 — restore to 192.168.1.50 before
  the next DTR TFTP boot (tftpd binds 192.168.1.50:69).
