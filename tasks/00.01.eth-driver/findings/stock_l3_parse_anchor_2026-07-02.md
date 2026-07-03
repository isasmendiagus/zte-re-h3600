# STOCK L3-parse → CLA-extract handoff — DIRECT stock reads (2026-07-02)

## Headline (overturns the task's working hypothesis)

The task premise was: mainline's extract key is empty because mainline lacks the L3
parse-anchor that stock publishes — specifically that stock enables DPA parse types
{2,3,4,5} (0x1FC0) for the L3/L4 parse while mainline can't (HW-clamped to 0x10C0).

**REFUTED by direct stock reads.** Stock's DPA protocol-analysis-enable is
**0x000010C0 — BYTE-IDENTICAL to mainline**, NOT 0x1FC0. Stock's own init
(`tm_pon_pp_dpa_initial`) *tries* to enable all 7 types (would be 0x1FC0) but the write
is clamped by HW to 0x10C0 exactly as on mainline. Types {2,3,4,5} are **OFF on stock
too**, yet stock parses IPv4/TCP perfectly and publishes a valid L3 anchor
(l3_offset_v4=14). So the parse-enable is **not the discriminator**, and there is **no
DPA knob to add on mainline**. The parse→extract handoff config is identical on both;
the mainline empty-key is a *symptom of the packet never being submitted* to the extract
engine (the standing upstream-submit / l3_en gate), not a broken/absent L3 anchor.

Device confirmed STOCK: `Linux H3600 V9 4.1.25 #2 SMP Thu Feb 17 2022 armv7l`, `/bin/fpga`
present. All reads read-only (`fpga -r` via `/dev/logger_main` capture). No reboot, no
writes, WAN untouched.

---

## TASK 1 — DPA protocol-analysis-enable, DIRECT stock read

Read recipe: `fpga -r <widx> 1` (widx=(phys-0x92000000)/4), captured on `/dev/logger_main`.

| phys | widx | STOCK value | meaning |
|---|---|---|---|
| **0x92398000** (DPA aly_en) | 0xe6000 | **0x000010C0** | bits {6,7,12} set ⇒ parse types **{0,1,6} ON, {2,3,4,5} OFF** |
| **0x92398014** (protocol_cpu_pps_en) | 0xe6005 | **0x0000001F** | cpu_pps_en bit0 ON |

**STOCK == MAINLINE (0x10C0).** (Mainline baseline on record: 0x92398000=0x000010C0,
0x92398014=0x1F — see ffe_forward_arm_hypothesis TEST A.) Not 0x1FC0.

Full non-zero scan of 0x92398000..0x923980ff (widx 0xe6000..0xe603f):
```
0x92398000 (e6000) = 0x000010c0   DPA protocol_pkt_aly_en  (types 0,1,6)
0x92398014 (e6005) = 0x0000001f   protocol_cpu_pps_en
0x92398024 (e6009) = 0x000005dc   = 1500 (parse max-len / MTU)
0x92398050 (e6014) = 0x00c04077
0x92398080..0x923980c4 (e6020..e6031) = 0x00688688  (18 identical words — per-type/per-slot cfg)
```
All other words in the range = 0. (These DPA cfg words were not previously dumped on
mainline for byte-diff; but the decisive parse-enable at 0x92398000 is identical.)

**Mechanistic proof the clamp hits stock too:** `tm_pon_pp_dpa_initial` @decomp:43094
runs `iVar5=0; do dpa_set_protocol_pkt_aly_en(iVar5,1); while(iVar5!=7)` (lines
43119-43124) — i.e. it *requests* types 0..6 ON = bits[12:6] = **0x1FC0**. The reg reads
back **0x10C0** on stock ⇒ HW silently drops types 2-5 (bits 8-11) on stock exactly as it
does on mainline (ffe TEST A: writing 0x1FC0/0xFFFFFFFF reads back 0x10C0). The clamp is
not a mainline defect; both firmwares land at 0x10C0 and both forward fine at that value.

`dpa_set_protocol_pkt_aly_en(type_id, act_val)` @decomp:14927 → `tmOnuRegWrite(type_id,
val, 0, dpaRegTable)`; per-type bit at 0x92398000 shift 6+type_id. **No port argument →
the parse-enable is GLOBAL, not per-ingress-port** (answers TASK 4: there is no per-port
parse-enable to differ; the only per-port DPA state is TPID selection —
`dpa_set_tpid_i_sel_i`, 9 ports × 4 × 4, VLAN-tag parsing, which shifts the L3 offset only
for tagged frames).

---

## TASK 2 — the L3-offset descriptor field (the offset_type=2 anchor)

The descriptor carries an explicit parsed **`l3_offset_v4`** byte-offset field (plus
`l3_offset_v6` / `l3_offset_v6_last`, `l2_offset`, `l4_offset`, `l5_offset`). It appears
in every descriptor decoder (spa_info_show @65746, adm @65928, PrintBrgDesc @66399/66494,
pm_info_show @64114). The ones the CLA extract engine sees:

- **CLA desIn** ("descriptor enter into cla module") decoder @decomp:68056, reads 7 words
  from base **fpga 0xe30f8 = phys 0x9238C3E0** upward. Field bit-math @68121-68130.
- **CLA desOut** ("descriptor handled by cla module") @decomp:67958, base **fpga 0xe30e5
  = phys 0x9238C394**.

**desIn word layout (7 words from 0xe30f8):**
| word | fpga widx | phys | carries |
|---|---|---|---|
| 0 | 0xe30f8 | 0x9238C3E0 | pkt_len, pmau, head_len, inport |
| 1 | 0xe30f9 | 0x9238C3E4 | (inport hi bits) |
| 2 | 0xe30fa | 0x9238C3E8 | ssid, direction, action, action_rsn |
| 3 | 0xe30fb | 0x9238C3EC | **l3_en, ip_flag, ipv4_flag, tcp_flag, udp_flag** |
| **4** | **0xe30fc** | **0x9238C3F0** | **extend_flag, l2_offset, l3_offset_v4, l3_offset_v6, l3_offset_v6_last** |
| 5 | 0xe30fd | 0x9238C3F4 | **l4_offset, l5_offset**, outer_pri/vid |
| 6 | 0xe30fe | 0x9238C3F8 | ram_id |

**⇒ The L3-header anchor = `l3_offset_v4`, CLA desIn word4, fpga widx `0xe30fc` /
phys `0x9238C3F0`.** Decode (desIn variant @68123): `l3_offset_v4 = (word4 << 0xf) >>
0x18` = bits[9:16] = `(word4 >> 9) & 0xff`. (`l4_offset = (word5<<0x17)>>0x18 =
(word5>>1)&0xff`; `l2_offset = (word4<<0x17)>>0x18 = (word4>>1)&0xff`.)

### STOCK live value (device forwarding/processing IPv4 traffic, 4 stable passes)

desIn snapshot (rock-steady across all reads):
```
word3 (0xe30fb) = 0x81610841
word4 (0xe30fc) = 0x00001c18   ← L3-offset word
word5 (0xe30fd) = 0x00000044
```
Decoded:
- **l3_offset_v4 = (0x1c18 >> 9) & 0xff = 0x0E = 14**  ← IPv4 header at byte 14 (= Eth 14). VALID.
- l4_offset = (0x44 >> 1) & 0xff = 0x22 = **34** (= 14 + 20 IPv4 hdr → TCP/UDP at byte 34). VALID.
- l3_offset_v6 = 0, l3_offset_v6_last = 0 (not v6), l2_offset = (0x1c18>>1)&0xff = 12.
- word3 flags: **l3_en=1, ip_flag=1, ipv4_flag=1, tcp_flag=1** (fully L3/L4-classified IPv4/TCP packet).

And **gparsehashkey** (fpga 0xe3098 / phys 0x9238C260) was populated and *changing per
snapshot* (word0 stable 0x4b000000; words 0xe309c/0xe309d cycled
0x8001294e/0x4532800c → 0x80018da0/0xe0de800c → 0x800109f4/0x648c800c →
0x8001b3c8/0xbab6800c) — i.e. the extract engine is **actively running and emitting a
distinct non-zero hash key per packet**, anchored on the valid l3_offset_v4=14.

**⇒ Stock's parser publishes a valid L3 anchor (l3_offset_v4=14) and the extract engine
consumes it to build a real per-packet key. Confirmed live.**

---

## TASK 3 — parse→extract linkage (decomp trace)

- **offset_type is a per-window field of the CLA extract rule (ram1)**, 3 bits each, at
  rule bytes 0x3c..0x43 (`cla_set_extra_rule_table` @decomp:2872, decode @3000-3035:
  `offset0_type = param_2[0x3c]&7`, etc). The captured stock/mainline boot rule
  (ram1[0x90]/[0x98]) has **offset_type = 2 for all 7 windows** (word15 = 0x00092492 —
  see stock_extraction_config §B). offset_type=2 = **L3-header-relative** — the extract
  engine anchors each window at `l3_offset_v4` (the descriptor field above); offset_type=0
  would be frame/L2-relative (`l2_offset`).
- **What publishes the anchor:** the fixed-function **parser (DPA)** computes
  l2_offset/l3_offset_v4/l4_offset and the l3_en/ip/ipv4/tcp/udp flags per packet and
  writes them into the descriptor. It is enabled by the global aly_en at 0x92398000; the
  IPv4 L3/L4 parse that yields l3_offset_v4=14 / l4_offset=34 is done by the **always-on**
  types that are set on both firmwares (bit6 = type0 = IPv4 parse, ON in 0x10C0).
- **Do types {2,3,4,5} = the L3/L4 parse for TCP/UDP? NO.** They are OFF on both stock and
  mainline (0x10C0), yet stock's descriptor shows ipv4_flag=1, tcp_flag=1, l3_offset_v4=14,
  l4_offset=34. Therefore the IPv4/TCP/UDP L3/L4 parse is **not** gated by types 2-5; it is
  done by the enabled type0 (bit6). Types 2-5 are auxiliary protocols (MPLS/PPPoE/nested
  encaps, etc.) that neither firmware needs for plain routed IPv4 transit.
- **What must be true for the anchor to be valid + consumed:** the packet must be parsed as
  IPv4 (type0, on both) AND — critically — must be **submitted to the CLA forward/ACL
  classify** (l3_en=1 / acl_required++). The extract engine that fills gparsehashkey runs
  on the *submit/forward* path; a *trapped* packet never reaches it, so its stale
  gparsehashkey reads zero regardless of how good the parse was.

---

## SYNTHESIS — the single most-likely stock-vs-mainline difference + the minimal knob

**The parse→extract handoff is byte-identical stock ↔ mainline. There is NO knob in it to
change.** Concretely identical on both:
1. DPA parse-enable 0x92398000 = 0x10C0 (both; stock's init requests 0x1FC0 → HW clamps to
   0x10C0 on stock too).
2. protocol_cpu_pps_en 0x92398014 = 0x1F (both).
3. CLA extract rule ram1[0x90/0x98] with offset_type=2 all-windows (both — stock_extraction_config §B).
4. The parser publishes l3_offset_v4/l4_offset correctly for IPv4 (stock: 14/34, verified;
   the same parser runs on mainline — it is not reconfigured by the driver).

**Therefore the empty mainline extract key is NOT a parse-anchor problem.** It is the
downstream signature of the **already-known upstream gate**: on mainline the transit packet
takes the per-inport **TRAP** disposition (SPA-classify/SDET) and is **never submitted** to
the CLA extract/forward engine → gparsehashkey is never written → reads its stale/zero
latch. Direct corroboration on record: a mainline trapped transit packet has **l3_en=0**
(descriptor probe, ffe_forward_arm_hypothesis / agent a8117571), while stock forwarding has
**l3_en=1** (and here, l3_en=1 with a live changing gparsehashkey). l3_en is HW-computed
(to-me compare + parse flags + L3 routing context), NOT SW-armed by any DPA/extract config —
so it cannot be fixed by writing the parse or extract tables.

**Minimal writable knob for the parse→extract handoff: NONE exists / none needed.**
- Do **not** chase the DPA reg: 0x92398000 is HW-clamped to 0x10C0 on both, and stock does
  not "get past the clamp" — it *also* reads 0x10C0 and forwards fine. Types 2-5 are
  irrelevant to IPv4/TCP routing.
- Do **not** rewrite the CLA extract rule: it is already identical and correct
  (offset_type=2, anchor = l3_offset_v4).
- The real lever is the **upstream submit / l3_en=1 decision** for the routed transit flow
  — i.e. the dynamic CPU-routing / SPA-classify disposition path documented in
  zte-flowoffload-framework and the ffe findings. Once a genuinely-routed packet is
  submitted (l3_en=1) on mainline, the *unchanged* parser will publish l3_offset_v4 and the
  *unchanged* extract engine will build a valid key — exactly as on stock (same config).

**Recommended next step (on mainline):** stop treating the empty key as a config bug. With
a genuinely-routed, *submitted* flow (l3_en=1 — the whole point of the standing "wire the
dynamic CPU-routed path / fix SPA submit disposition" work), read CLA desIn word4
(0xe30fc / 0x9238C3F0) → confirm l3_offset_v4 populates (it will) and gparsehashkey goes
non-zero. If a submitted packet still reads l3_offset_v4=0, only then is there a parser
problem — but every read here says the parser is not the gate. The gate is the submit/l3_en
decision, which is upstream of this entire handoff.

---

## Register quick-reference (all verified this session unless noted)
```
0x92398000  widx 0xe6000  DPA protocol_pkt_aly_en   STOCK=0x10C0  (== mainline; types 0,1,6)
0x92398014  widx 0xe6005  protocol_cpu_pps_en        STOCK=0x1F    (== mainline)
0x9238C3E0  widx 0xe30f8  CLA desIn word0 (base)     pkt_len/inport
0x9238C3EC  widx 0xe30fb  CLA desIn word3            STOCK=0x81610841 (l3_en=1,ipv4=1,tcp=1)
0x9238C3F0  widx 0xe30fc  CLA desIn word4  ← L3 ANCHOR  STOCK=0x00001c18 → l3_offset_v4=14
0x9238C3F4  widx 0xe30fd  CLA desIn word5            STOCK=0x00000044 → l4_offset=34
0x9238C394  widx 0xe30e5  CLA desOut word0 (base)
0x9238C260  widx 0xe3098  gparsehashkey (12 words)   STOCK=live, non-zero, per-packet changing
```

## State left behind
Device on STOCK, healthy, WAN as-found (untouched). All access read-only (`fpga -r` +
CLA/DPA reads via /dev/logger_main). No writes, no flash, no reboot. `/tmp/r.bin` scratch
left on device (harmless).
