# Stock-LIVE CPU→LAN egress oracle (2026-05-28)

The oracle run. Booted **factory stock** (cold DTR reset → cspstart → NAND;
this boot fell through to slot-B factory stock — netshell/devmem absent, so it
is the *pristine* working stock, not our custom slot-A rootfs). Got a root SSH
shell (`admin`/`UkuGPeyRDU`, paramiko `invoke_shell`; PTY works, only *exec*
channels wedge). Read live egress-path regs **while the device was actively
egressing** ICMP replies out MAC2/LAN3 (host floods `ping 192.168.1.1`).

## How to read regs on stock (recorded for next time)
- Tool: `/bin/fpga -r <wordidx> 1`. The arg is a **WORD INDEX** into the pon
  window: `wordidx = (phys - 0x92000000) / 4`. (e.g. MAC2 ctrl 0x92280000 →
  `fpga -r 0xa0000`.) `fpga -r 0x92280000` → "invalid reg".
- Output goes to the **kernel ring**, NOT stdout and NOT `/dev/logger_main`
  (that's the cspd *app* logger, binary-framed). Capture with
  `cat /proc/kmsg >/tmp/k & … ; grep 'fpga read' /tmp/k` →
  `<4>fpga read: reg=0x000a0000, value=0x00ba6003`.
- No `devmem`, no `memdump`, no `tail`/`head` on factory busybox v1.17.2.
- NB: device is in a **reboot cycle** (~1-2 min up) — slot-A header CRC churn
  from past mainline flashes; cspstart rejects A, boots B, something resets.
  Reads are safe (idempotent); just race the up-window. WRITES over MAC2 would
  kill your own SSH (you're connected through the port you'd disrupt).

## Stock-LIVE egress-path registers (MAC2 ACTIVELY EGRESSING)

All three pipeline counters track **identically** with the ping-reply count and
climb together (snapshot A=0x19d, snapshot B=0x257 — i.e. +186 between runs):

| reg (phys) | what | stock-LIVE (egressing) | mainline-live | match? |
|---|---|---|---|---|
| 0x9234c044 | QMG **sw_fwd** counter | **0x19d↑** (=TX cnt) | sw_fwd (also) | counts ✓ |
| 0x9234c048 | QMG hw_fwd | 0 | 0 | ✓ (NOT hw_fwd) |
| 0x9234c04c | QMG hw_trap | 0 | 0 | ✓ |
| 0x921d9164 | SOPC **send2smac2** | **0x19d↑** | 0 (never fires) | **frame arrives at SOPC on stock** |
| 0x92280714 | MAC2 TX byte cnt | 0x50443↑ | 0 | egressing |
| 0x92280718 | MAC2 **TX-OK cnt** | **0x19d↑** | 0 | egressing |
| **0x921d0054** | **TM UP-ring KICK** | **0x00000000** | (driver writes 1) | **stock never kicks the UP ring** |
| **0x921d0058** | **TM UP TX-consume/egress** | **0x00000000** | 0 | **0 on stock TOO** |
| **0x921d005c** | TM UP cursor | 0x00000000 | advances | stock doesn't use it |
| 0x921da04c | DSCH drop | 0 | 0 (after SCH fix) | ✓ |
| 0x921da040/044 | PP drop / RED drop | 0 / 0 | 0 / 0 | ✓ |

### ===> THE HEADLINE FINDING <===
**Stock's CPU→LAN egress does NOT go through the UP DMA TX descriptor ring.**
`TM[0x10054]` (kick), `TM[0x10058]` (TX-consume), `TM[0x1005c]` (cursor) are
**all 0** on stock even while it egresses 0x257 frames out MAC2. The frame path
is a pure switch-fabric fast-path:

```
CPU stack -> (CPU/internal port) -> QMG sw_fwd (0x9234c044++) ->
   SOPC send2smac2 (0x921d9164++) -> MAC2 TX (0x92280718++) -> wire
```

This re-frames the whole mainline hunt. The prior sessions read
`TM[0x10058]=0` as the failure ("HW reads desc, never egresses"), but **0 is
the stock-correct value** — stock never touches that ring for CPU egress.
Mainline is egressing on the WRONG path: it builds a 16B desc, kicks
`TM[0x10054]`, and waits for the UP-ring DMA path. Stock instead hands the
frame to the switch fabric as a software-forwarded packet (QMG sw_fwd), which
the SOPC then emits to the DA-resolved MAC. That is why mainline's frame
"passes QMG+DSCH but never reaches send2smacN": it's sitting in / consumed by
the UP-ring DMA path, which is not the path that feeds SOPC send2smacN.

## MAC2 (host/LAN3) block — stock-LIVE vs mainline

| phys | reg | stock-LIVE (egressing) | mainline-live | note |
|---|---|---|---|---|
| 0x92280000 | MAC2 ctrl | **0x00ba6003** | 0x00ba6003 | **MATCHES** (bits0,1 tx/rx-en + bit15 link-up) |
| 0x92280004 | IRQ_MASK | **0x00003fff** | 0x00000000 | stock sets, mainline 0 |
| 0x92280008 | ENABLE | **0x80000001** | 0x00000000 | stock sets bit31, mainline 0 |
| 0x9228000c | +0x0c | 0 | — | |
| 0x92280070 | +0x70 | **0x00000000** | (mainline writes) | LIVE=0 (idle-dump had 0xffff0000 — transient) |
| 0x922800b4 | +0xb4 | 0 | (mainline writes) | stock 0 |
| 0x922800e0 | iface +0xe0 | **0x00000000** | mainline writes 0x11200 | **stock NEVER sets the U-Boot direct-mux word** |
| 0x92280b00 | +0xb00 | 0x00002000 | — | boot default |
| 0x92280c20 | +0xc20 | 0 | (mainline writes) | stock 0 |
| 0x92280c50 | +0xc50 | 0 | (mainline writes) | stock 0 |

So **MAC2 ctrl already matches** between stock and mainline (0xba6003). The MAC
deltas are: stock has `IRQ_MASK=0x3fff` + `ENABLE=0x80000001`; mainline has both
0. BUT — per the prior sessions, simply enabling MAC2 in mainline causes the
STORM, and adding the U-Boot `+0xe0=0x11200` to stop the storm still doesn't
egress. The oracle now explains WHY: **the MAC was never the gate. The egress
PATH is.** With the fabric fast-path (not the UP ring), the MAC enable is the
*last* step, and the `+0xe0` direct-mux word must stay **0** (stock confirms
0xe0=0 on the egressing MAC).

## SOPC config — stock-LIVE (all defaults; no per-source egress matrix)
| phys | stock-LIVE | note |
|---|---|---|
| 0x921d9000 SOPC top | 0x04444444 | boot default (sp_rr_mode=0) |
| 0x921d9004 crc_pad | 0x00000000 | default |
| 0x921d9038 | 0x00000000 | transient handshake — 0 even while egressing |
| 0x921d9068 | 0x00000000 | transient handshake — 0 even while egressing |
SOPC has no source-gated egress matrix (confirmed). It emits to whatever
MAC the fabric routes to. Mainline already matches these.

## QMG decision: sw_fwd, NOT hw_fwd (settles the open question)
Stock-live: **sw_fwd (0x9234c044) counts the CPU egress; hw_fwd (048)=0,
hw_trap (04c)=0.** So Q-(2) in the task is answered: **stock does NOT hw_fwd
the CPU frame — it sw_fwds it**, exactly like mainline. The "sw_fwd vs hw_fwd"
theory is a dead end. (Note: there are two QMG aliases — the *counter* block at
0x9234c0xx, and a separate live block at 0x921cc0xx; the latter is HW-dynamic
queue state, not config — don't poke it.)

## SBRG / PP_BRG per-source forwarding — stock-LIVE vs mainline
Almost everything matches (all the landed fixes are stock-faithful). Remaining
divergences:

| phys | reg_id (sbrag) | stock-LIVE | mainline-live | note |
|---|---|---|---|---|
| 0x92388008 | reg10/11 (byte per port) | **0x0000dfdf** | 0x0000ff00 | **DIFF** — per-port recv/fwd byte; stock 0xdf,0xdf vs main 0xff,0x00 |
| 0x92388004 | pt_transfer_en | 0x040200ff | 0x040200ff | ✓ |
| 0x923881c0 | pt_smac_look_en | 0x000000ff | 0x000000ff | ✓ |
| 0x923882c0 | pt_da_lookup_en | 0x000000ff | 0x000000ff | ✓ |
| 0x92388340 | unknown_unicst_fwd | 0x015555ff | 0x015555ff | ✓ |
| 0x92388380 | pt_tls | 0x00000001 | 0x00000001 | ✓ |
| 0x923883c0..dc | isolation | fe fd fb f7 ef **df** ff ff | same | ✓ (CPU port5=0xdf) |
| 0x92388188 | fdb cfg | 0x00211b00 | 0x00211b00 | ✓ |
| 0x9238863c | — | **0x00000000** | 0xaaaaaaaa | mainline writes 0xaaaa…; stock leaves 0 |
| 0x923880b0 | FDB-A host slot bitmap | 0x00000108 | 0x00000108 | ✓ host MAC learned |

The only non-dynamic SBRG diffs are **0x8008 (0xdfdf vs 0xff00)** and
**0x863c (0 vs 0xaaaaaaaa)**. Worth aligning but neither is the egress gate
(the gate is the path, above).

## ANSWERS to the task's key questions
1. **Is MAC2 ENABLE actually set on stock, egressing without storming?** YES —
   `ENABLE=0x80000001`, `IRQ_MASK=0x3fff`, `ctrl=0xba6003`, and crucially
   **`+0xe0=0` (NO direct-mux word)**. The thing that makes `en` SAFE on stock
   is that egress goes through the FABRIC fast-path, not the UP ring + direct
   mux. Mainline storms because it enables the MAC *and* sets the U-Boot
   direct-mux `+0xe0=0x11200`, mixing two incompatible egress architectures.
2. **Does stock QMG hw_fwd the CPU frame?** NO. Stock uses **sw_fwd** (same as
   mainline). Dead end.
3. **The single config mainline lacks:** It is not a single register — it is the
   **egress PATH**. Stock egresses CPU frames through the switch fabric
   (sw_fwd→SOPC→MAC) with `TM[0x10054]` kick = 0; mainline egresses through the
   UP DMA descriptor ring (kicks `TM[0x10054]`). The frame mainline puts on the
   UP ring never reaches SOPC send2smacN because that ring is not what feeds
   SOPC for CPU-sourced LAN egress.

## POKE-TESTABLE HYPOTHESIS for mainline (concrete)
**H-PATH (highest):** mainline is using the wrong egress submission path. Stop
kicking the UP DMA ring for CPU→LAN TX and instead inject the CPU frame as a
**software-forwarded fabric packet** so it flows QMG sw_fwd → SOPC send2smac2.
The desc/ring is a red herring (TM[0x10058]=0 is stock-correct). Concretely, on
the live mainline:
1. Confirm the negative: with the driver's current UP-ring TX, read
   `TM[0x10054]`, `TM[0x10058]`, `TM[0x1005c]` during `txtest` — mainline kicks
   0x10054 / advances 0x1005c, but **stock leaves all three 0**. That mismatch =
   proof mainline is on the wrong path.
2. Find the CPU/IDM software-forward submission the stock kmod uses (the path
   that increments QMG sw_fwd **without** a UP-ring kick). Candidates: the
   IDM/CPU-port inject FIFO, or `pon_tm_net_tx` writing to a fabric inject reg
   rather than the UP descriptor ring. Trace the stock kmod's actual TX
   submit for a CPU-sourced LAN frame (it must write something that lands in
   QMG sw_fwd with 0x10054 untouched).
3. Then enable MAC2 the **stock** way (and ONLY that way): ctrl=0xba6003,
   IRQ_MASK=0x3fff, ENABLE=0x80000001, and **leave +0xe0/+0xc20/+0xc50/+0x070/
   +0xb4 all = 0** (no U-Boot direct-mux). This avoids the storm because the
   MAC is fed by the fabric, not the direct mux.

**H-8008 (secondary, cheap poke):** align `0x92388008` to stock's **0xdfdf**
(mainline=0xff00) and clear `0x9238863c` to 0 (mainline writes 0xaaaaaaaa).
These are per-port forward/recv-mask bytes; low odds of being the egress gate
but they are real stock-vs-mainline config diffs, easy to poke, do alongside
the MAC enable.

## Device left
On STOCK (NAND boot), reading only — no writes performed. Device is in its
slot-A-CRC reboot cycle; the main loop should reflash/boot mainline next.
Oracle raw values captured above are from MAC2 actively egressing (counters
0x19d→0x257 between runs).
