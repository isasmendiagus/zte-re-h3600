# Stock CLA (classifier) indirect-RAM dump — golden reference

Captured live from the ZTE H3600 stock kernel (NAND) via the RELIABLE reg-read path:
`fpga -r <widx>` → value printed to `/dev/logger_main` as `fpga read: reg=0x.., value=0x..`
(NOT /proc/kmsg). CLA indirect read: write CMD `0x9238c014 = addr | (ram_id<<22) | (1<<27)`,
then read 17 data words at `0x9238c01c` (widx 0xe3007..0xe3017). Warmup throwaway read per addr.
Script: `dump_cla_stock.py` (this dir) — run with the device on STOCK (NAND); edits the `plan=[...]` list to pick ram_id/addr ranges. Each line: `ramN a0xADDR: w0 w1 ... w16`.

## Field decode (from decomp, cla_ram_layout_re.md)
- **ram0** (byte-extractor, portless): `extract_index0..15`, `ext_mode`. word[4] = ext_mode/flags.
- **ram1** (rule-TCAM, 160 ent, 17w): w0..w3 = 128-bit match VALUE, w4.. = winmask;
  w14 = action (bit25 0x02000000 = up/down direction variant seen); byte0x39 bit5 = inport_mask flag.
- **ram2-6** (hash/result, per-inport, 520 ent, 15w): addr picks bank
  (0..0xff→ram2, 0x100..0x17f→ram3, 0x180..0x1bf→ram4, 0x1c0..0x1ff→ram5, 0x200..0x207→ram6).
  **inport = (byte[0x0e] & 0x3f) << 6 | (byte[0x0d] >> 2)**; CLA inport = REGPORT (logical port1 = regport2).
  trap action: cpu_qid = byte6; valid_en/direct in byte[0x10].
- **ram7** (per-(ptype,port) cpu trap-queue): data[0] = qid.

## Per-regport ram2 addresses (for comparing the FAILING port1 vs a working port)
- regport2 (= logical port1, FAILS): `0x21 0x93 0x121 0x193 0x221 0x293 0x321 0x393`
- regport3 (= logical port2, works): `0x79 0xcb 0x179 0x1cb 0x279 0x2cb 0x379 0x3cb`

## NOTE — CLA is BACK IN SCOPE (2026-06-01)
The prior "CLA exonerated" verdict (cla_ram_layout_re.md) rested on the premise that port1 dies
UPSTREAM of CLA (at SDET). That premise was REFUTED: port1 frames pass MAC→SPA→SDET and drop at
`drop_PP` (0x921da040), the forwarding/trap stage AT/after the CLA. So this stock CLA dump is the
golden to diff against mainline's per-regport2 classification. See port1_drops_at_PP_re.md.

## FINDINGS (2026-06-01) — stock golden regport2 vs regport3 (both WORK on stock)
From `cla_stock_regport2-vs-3_2026-06-01.txt` (ram2, fpga reliable read):
```
regport2 (=logical port1): 01005055 00154000 80000408 90000817 00000042 000000e0 ...  inport=2 valid/dir=0x42
regport3 (=logical port2): 01005055 00154000 80000408 80000c17 80000043 00c20001 ...  inport=3 valid/dir=0x43
```
Stock regport2 entry is VALID and byte-identical to regport3 except the inport byte (word3 `08` vs `0c`)
and outport byte (word4 `42` vs `43`) — exactly as a working per-port entry should differ. **This is the
golden: a working port1 (regport2) CLA classification entry.**

## CLA hypothesis is LIVE (NOT refuted) — correction
Earlier I "refuted" the CLA by adding a verify-retry to zx_cla_write_entry and seeing port1 still drop.
That test was INVALID: the verify read-back itself aliased (CLA init reported 163 fail; reads came back
zeroed) — so the fix never actually corrected the writes; it just failed verification. ⇒ port1 still
dropping does NOT exonerate the CLA. The coherent live hypothesis:
  mainline replays a 780-entry CLA image but the indirect WRITE is flaky (observed word0 corruption +
  163 verify-fails) → mainline's regport2 classification entry may be CORRUPTED → port1 frames not
  trapped → drop_PP. Stock's regport2 entry (above) is the golden it should match.

## NEXT STEP
Reliably read MAINLINE's regport2 ram2 entry (addrs 0x21/0x93/0x121/...) and diff vs this stock golden.
Caveat: mainline `clapeek` read was unreliable on the polluted/bad-CLA build — retry on a CLEAN build
WITH a warmup throwaway read per addr (the stock fpga path used `fpga -r 0x73000` warmup; clapeek did
not). If mainline regport2 != golden → confirmed CLA replay corruption → fix the replay handshake
PROPERLY (not the broken aliased-verify). Then re-test port1 forwarding.
