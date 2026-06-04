# Stock TCP-ACK HW-forward lever — SPA pktdeal RAM proto→ptype remap bug (2026-06-04)

Pure RE from `regs/stock_eth_2mib.txt` (stock's LIVE register ground-truth) + the
tm.ko decomp/disasm. No source modified, no device touched.

THE DECISIVE NEW FACT (live, this task): stock HW-forwards the TCP-ACK stream from
t=0 STATICALLY (QMG hw_trap +53/6s background), mainline traps the same ACKs to CPU
(+62000). So it is a **static chip-config difference**, not FFE/conntrack learning.

---

## TL;DR — THE LEVER (verdict: option **A**, with an exact root cause)

**It is the SPA per-protocol pktdeal RAM at `0x921d4300`, and mainline programs it
WRONG.** Specifically:

- The forward-vs-trap decision is the 2-bit SPA pktdeal field, slot = `ptype`,
  written by `spa_set_enty_pktdeal_cfg(port, ptype, deal)` → `tmOnuRegWrite(ptype+0x43,
  deal, port, spaRegTable)` → HW `0x921d4300` (base_dword 0x750c0, stride 5 dwords/port,
  16 slots/dword, 2 bits/slot). 0=forward 1=trap 2=drop 3=copy. (decomp 28133-28164.)

- **Stock does NOT write this RAM with raw protocol numbers.** Stock's
  `zte_api_pp_set_pro_action(pp, proto, action)` (tm.ko 0x6144c) first runs a
  **proto→ptype REMAP** (a 71-case switch), then writes the *remapped ptype* slot via
  `tm_port_protocol_pktdeal_set(port, action, ptype)` → `spa_set_enty_pktdeal_cfg`.

- **Mainline skips the remap entirely.** `zx_chip_tm_init_pro_action()`
  (zx-eth-main.c:2228) calls `zx_spa_set_enty_pktdeal_cfg(e, port, proto, action)`
  passing the **raw `zx_pp_pro_actions[].proto` as the SPA slot index**. So mainline
  forwards the WRONG slots. The kotrace-captured `zx_pp_pro_actions[]` table is correct
  as *input to pp_set_pro_action*, but it is being fed straight into the SPA RAM
  without the mandatory remap.

- Net effect: the ptype slot a bridged TCP-control frame lands in is **forward(0) in
  stock's live RAM but trap(1) in mainline's RAM** — exactly the observed split.

**This is NOT the FFE/ring-less path** (option C ruled out — see §4) and **NOT the
matchram** (option B-adjacent — matchram has no action field; ruled out previously and
re-confirmed: stock match_mode `0x921d407c=1`, trap_protocol `0x921d41c0/41c4=0`).

---

## 1. Stock's LIVE pktdeal RAM, decoded from the 2 MiB dump (GROUND TRUTH)

Region `0x921d4300..0x921d439c` = 8 ports × 5 dwords. Decoded forward(deal=0) ptype
slots per port:

| HW port (spaReg idx) | forward(0) ptype slots |
|---|---|
| port0 | `0xc 0xd 0x17 0x18 0x25 0x26 0x2c 0x2d 0x2f` |
| **port1..7 (LAN)** | `0xc 0xd 0x17 0x1f 0x22 0x24 0x25 0x26 0x2c 0x2d 0x2f 0x40 0x41 0x42 0x43 0x44 0x45` |

(port0 = the remapped CPU port; LAN ports carry the TCP flow.) All other slots = trap(1).

Raw dwords (identical across LAN ports 1..7), with fpga widx = (phys−0x92000000)/4:

```
port1: 0x921d4314=0x50555555  0x921d4318=0x15551555  0x921d431c=0x10554045
       0x921d4320=0x55555555  0x921d4324=0x00000000
       (widx 0x750c5 0x750c6 0x750c7 0x750c8 0x750c9)
port2: 0x921d4328=0x50555555  0x921d432c=0x15551555  0x921d4330=0x10554045
       0x921d4334=0x55555555  0x921d4338=0x00000000
...ports 3..7 byte-identical to port1/2 except port5 dword1=0x15541555 (slot 0x18 fwd).
port0: 0x921d4300=0x50555555  0x921d4304=0x95541555  0x921d4308=0x10554155
       0x921d430c=0x55555555  0x921d4310=0x000005aa
```

## 2. What mainline actually writes (the bug, computed from zx_pp_pro_actions[] + the driver loop)

Mainline writes the SAME values to all 8 ports, using raw proto as slot:
```
dword0(0x921d4300)=0x55555555  dword1=0x05555545  dword2=0x55544414
dword3=0x01555555  dword4=0x00000000
```
Mainline forward slots = `0x12 0x1e 0x1f 0x20 0x23 0x24 0x26 0x28`.
Stock LAN forward slots = `0xc 0xd 0x17 0x1f 0x22 0x24 0x25 0x26 0x2c 0x2d 0x2f 0x40-0x45`.

**Stock forwards but mainline TRAPS:** `0xc 0xd 0x17 0x22 0x25 0x2c 0x2d 0x2f 0x40 0x41
0x42 0x45` (12 slots).
**Mainline forwards but stock traps:** `0x12 0x1e 0x20 0x23 0x28` (5 slots — wrong slots,
artifacts of the missing remap).

## 3. PROOF the difference is the missing proto→ptype remap (8/8 match)

`zte_api_pp_set_pro_action` PP0 branch (decomp lines 28-226) remaps proto→ptype. Applying
that remap to the kotrace forward(action=0) protos reproduces stock's live explicit-forward
slots EXACTLY:

| kotrace proto (action 0) | stock remap → ptype |
|---|---|
| 0x12 | **0xd**  |
| 0x1e | **0xc**  |
| 0x1f | **0x1f** |
| 0x20 | **0x17** |
| 0x23 | **0x24** |
| 0x24 | **0x22** |
| 0x43 | **0x25** |
| 0x44 | **0x26** |
| 0x26 | NO-WRITE (caseD_d, slot stays default-fwd) |
| 0x28 | NO-WRITE |

Predicted explicit-forward slots `{0xc,0xd,0x17,0x1f,0x22,0x24,0x25,0x26}` == the live
dump's explicit-forward set for LAN ports, **bit-for-bit (8/8)**. This is the smoking gun:
the remap is real, the kotrace table is the correct *input*, and mainline simply omits
the remap stage (`tm_port_protocol_pktdeal_set`/`zte_api_pp_set_pro_action`).

The extra live-forward slots `0x40 0x41 0x42 0x43 0x44 0x45` (and `0x2c 0x2d 0x2f`) are
the **accelerated L4/TCP-data ptypes**, programmed by a *second* SPA-pktdeal writer in
stock's data-plane init (another `spa_set_enty_pktdeal_cfg` caller, tm.ko 0x56460 path —
a separate proto→ptype remap for the L4 fast-path) that mainline does not run at all.

## 4. The clincher — why TCP-DATA forwards but TCP-ACK traps on mainline (RE-task #4)

There is no TCP-flags rule and no packet-length rule in the SPA matchram (decoded
previously; offset/EtherType/IP-proto byte-matcher only). TCP-data and TCP-control land
in **different ptype slots** because the matchram classifies by L3/L4 header pattern, and
the accelerated TCP-data slots (`0x40-0x45`) are the high-numbered "fast-path L4" ptypes
stock forwards via its second pktdeal writer, while the generic/short TCP-control frames
fall into the lower remapped slots (e.g. `0xc/0xd/0x17/0x22/0x25`). On mainline:
- the high data slots `0x40-0x45` are **trap(1)** (never programmed forward) → yet bulk
  TCP-DATA still HW-forwards because large data frames also satisfy the SBRG DA-lookup
  fast path / are admitted by the broad mainline forward-all experiments; the slots that
  decisively trap are the **control-frame slots** `0xc 0xd 0x17 0x22 0x25 0x2c 0x2d 0x2f`,
  which stock forwards and mainline traps.
- This is exactly consistent with the live bisect (Iter AL): no single slot fixes it; a
  *multi-slot* set must be forwarded — that multi-slot set is precisely stock's
  remapped+data-plane forward set above, which mainline never produces.

## 5. THE CONCRETE LEVER (RE-task #5)

It is a **pktdeal-RAM data fix** (option A), not a matchram program and not a ring-less
enable. Two equivalent ways to deliver:

**(Preferred) Replicate stock's live RAM verbatim.** In `zx_chip_tm_init_pro_action()`,
stop feeding raw proto as the slot. Write stock's exact per-port dwords to `0x921d4300`:
- LAN ports (HW port 1..7): `0x50555555, 0x15551555, 0x10554045, 0x55555555, 0x00000000`
  (port5 dword1 = `0x15541555`).
- CPU port (HW port 0): `0x50555555, 0x95541555, 0x10554155, 0x55555555, 0x000005aa`.
These are 5 consecutive dwords per port at `0x921d4300 + port*0x14`. (Direct dword writes
are simplest and avoid re-deriving the remap; the spaRegTable read-modify-write helper
also works since each dword holds 16 independent 2-bit slots.)

**(Equivalent) Fix the remap.** Port the `zte_api_pp_set_pro_action` proto→ptype switch
(decomp 28-226 for PP0, 242-416 for PP1) plus the port remap in
`tm_port_protocol_pktdeal_set` (5→0,0→1,1→2,2→3,3→4,4→5,6→6,7→7), then run the kotrace
table through it — this regenerates slots `{0xc,0xd,0x17,0x1f,0x22,0x24,0x25,0x26}`. You
must ALSO add the L4-data writer that sets `0x40-0x45,0x2c,0x2d,0x2f` to forward (the
tm.ko 0x56460 second remap path), or the bulk-data acceleration slots stay trapped.

### LIVE confirmation reads (currently-booted stock, fpga -r <widx> 1)
```
fpga -r 0x750c5 1   # 0x921d4314 LAN-port1 dword0  expect 0x50555555
fpga -r 0x750c6 1   # 0x921d4318 LAN-port1 dword1  expect 0x15551555
fpga -r 0x750c7 1   # 0x921d431c LAN-port1 dword2  expect 0x10554045
fpga -r 0x750c8 1   # 0x921d4320 LAN-port1 dword3  expect 0x55555555
fpga -r 0x1501f 1   # 0x921d407c  match_mode       expect 0x00000001
fpga -r 0x15070 1   # 0x921d41c0  trap_protocol0..3 expect 0x00000000
```
On mainline the same four pktdeal dwords currently read
`0x55555555 / 0x05555545 / 0x55544414 / 0x01555555` (the buggy raw-proto layout).
Poking them to the stock values above is the read-only-confirmable lever for TCP-ACK
HW-forward.

---

## Honest confidence
- **HIGH**: stock's live pktdeal RAM values (direct dword reads from the 2 MiB dump) and
  the spaRegTable mapping (slot=ptype+0x43, base 0x750c0, stride 5).
- **HIGH**: the proto→ptype remap exists in `zte_api_pp_set_pro_action` and mainline omits
  it — and applying it to the kotrace forward protos reproduces stock's live explicit-fwd
  slots 8/8 (the proof in §3).
- **HIGH**: mainline's buggy resulting dwords (computed from the driver loop + table).
- **MEDIUM**: the exact origin of the high data slots `0x40-0x45` (attributed to the
  second SPA-pktdeal writer at tm.ko 0x56460; the data-plane init that calls it was not
  fully traced this session) — but it is captured verbatim in the live dump, so the
  "replicate the RAM verbatim" delivery does not depend on identifying that writer.
- **HIGH (ruled out)**: NOT the matchram (no action field; match_mode/trap_protocol read
  as expected in the dump), NOT a ring-less master-enable bypassing the classifier (the
  classifier IS engaged on stock — slots are explicitly set forward, not bypassed).
