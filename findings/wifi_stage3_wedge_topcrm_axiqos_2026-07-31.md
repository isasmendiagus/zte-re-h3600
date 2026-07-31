# Wedge #2, session 2026-07-31e — top_crm REFUTED; a real stock-kernel divergence (AXI QoS @0x00a20000) found + landed, but it is NOT the pool gate and **NOT the wedge fix**; wedge #2 remains OPEN

> **READ §7 FIRST.** The A09 candidate survived 205k HW-forwarded frames in
> one run and then wedged at **inj=1,755 on the very next fresh boot of the
> identical build**. Wedge #2 is **NOT fixed**, `ftwifi` stays **default
> OFF**, and — the load-bearing lesson — **a single clean endurance run is
> not evidence of a fix**: onset variance on one unchanged build spans
> 1.7k → >205k frames.

Predecessor: `findings/wifi_stage3_wedge_bmu_pool_2026-07-28.md` (+ its
2026-07-31d addendum). Memory: `zte-wifi-up-offload`.

Task hypothesis under test: *the BMU packet-buffer engine is unclocked /
held in reset on mainline → it never produces its DDR BP pool (`bppe_cnt`
@0x92348080 = 0 on mainline vs ~8112 on stock) → HW-forwarded fabric
frames leak BPs off a ~15-entry on-chip margin → fabric starvation halt at
~1k frames. The fix is the un-RE'd top_crm/sys_ctrl clock/reset bit that
enables the BMU engine.* Success oracle: `bppe_cnt` → ~8112.

**Verdict: the oracle was NOT met, and the top_crm branch of the
hypothesis is positively refuted.** Details below, all measured on HW.

---

## 1. top_crm is NOT the gate — refuted by direct comparison

Live mainline dump (`/bin/memdump 0x94000000 0x100`, fresh RAM-boot) is
**byte-identical** to the stored stock capture
`tasks/00.01.eth-driver/captures/fpga/topcrm_stock.txt` — all 64 words:

```
94000004 000001fb   94000008 1ff7ffff   9400000c 005179e0   94000010 0000b114
94000014 cffffbf7   94000048 0ffedfff   9400004c 0003cfff   94000050 08040ca2
94000054 14000000   ... (everything else 0 on BOTH)
```

The stock capture is a full 4 KiB dump and is **all-zero above +0x54**, so
there is no unexamined top_crm register left. There is no top_crm bit that
mainline leaves clear and stock sets. This closes the primary thread named
by the task.

(Consistent with `tasks/00.10.02.re-stock-kmods/findings/eth_egress_clock_reset_re.md`,
which had already concluded mainline replicates essentially the whole SoC
clock tree — TOPCRM[0x08] b4/b5 pulse, ref_clk PLL, SERDES band cal,
sys_ctrl bit11, pon_reset, TOPCRM[0x0c]|=0x1e0.)

## 2. What IS divergent: the AXI bus-matrix / QoS block @ phys 0x00a20000

Found by re-reading the *vmlinux* RE rather than the kmod RE:
`static_analysis_vmlinux_platform_init.md` **[vm-05]**. Stock's
`zx279128_init_machine` (vmlinux 4.1.25 @0xc06390f4, **arch_initcall 3**)
writes five registers in this order, each separated by
`outer_cache.sync()`:

| off | stock value | mainline live (before fix) |
|---|---|---|
| +0x80 | `0x40000001` | **0** |
| +0x84 | `0xBFFFFFFF` | **0** |
| +0x88 | `0x1F0F1F0F` | **0** |
| +0x78 | `0x1F0F1F0F` | **0** |
| +0x00 | `0x0D000000` | `0x01000000` |

**Every field stock programs was unset on mainline.** This is a genuine,
previously untouched divergence, and the reason it survived so many
stock-parity audits is structural: stock programs it from the **kernel's
machine init**, not from any kmod, so it never appears in the kmod replay
table that mainline's parity work is built against.

Shape reading: `0x1F0F1F0F` = four 8-bit priority/threshold fields;
`+0x80`/`+0x84` behave as a set/clear pair (writing `0x40000001` then
`0xBFFFFFFF` nets bit30 set). Live poke also showed **+0x8c mirrors +0x88**
(paired register). This is the shape of interconnect QoS / arbitration
weights.

Landed as **[A09] `zx_soc_axi_qos_init()`** in `zx-pon-plat.c`, called
first from `zx_pon_plat_init` so it runs before any datapath block is
touched (matching stock's arch_initcall ordering). Boot log:
`[A09] SoC AXI QoS programmed (stock machine-init parity): [0x00]=0x0d000000 [0x78]=0x1f0f1f0f [0x80]=0x40000001 [0x88]=0x1f0f1f0f`
at t=62s, i.e. before BMU init at t=70s. Commit `cb10a8b4d`.

## 3. …but it is NOT the pool gate either — `bppe_cnt` stays 0

Tested **both** ways on HW:

- **Live post-boot poke** (busybox `devmem`, all 5 values latched, box
  stayed alive): `bppe_cnt` 0 → 0 on all 5 BMU instances.
- **Landed pre-datapath in the driver** (correct stock ordering, verified
  by the t=62s log line): boot-log oracle still reads
  `bppe_cnt=0 bppi_cnt=10 (stock-healthy ~8112/~79)`.

So the AXI QoS block is stock parity worth having, but it does not prime
the pool.

## 4. Additional refutation this session: the BMU re-init edge

New tool `scratchpad/bmu_reinit.py` (paced through `ab_ctrs.zc`; a fast
poke batch overruns the UART console and hangs the CPU). It drives, live
and entirely in poke range, the full documented engine edge:

```
BMU_INIT=0 (all 5) → CTRL1/CTRL2/BUCKETS_M1/JUMBO_BUCK rewritten
                   → producer cursors 0x8048=POOL<<16, 0x804c=JUMBO<<16
                   → BMU_INIT=1 (all 5)      [then alloc-kick x4, then initsat+retoggle]
```

Result — nothing moves the pool:

```
[baseline]       init=0x1 bppi_ptr=0xc300b9 r8044=0x0 bppe_ptr=0x0 bppe_cnt=0x0 bppi_cnt=0xa  bpstat=0x111
[post-reinit]    init=0x1 bppi_ptr=0xc600ba r8044=0x0 bppe_ptr=0x0 bppe_cnt=0x0 bppi_cnt=0xc  bpstat=0x111
[post-kick]      init=0x1 bppi_ptr=0xc600be r8044=0x0 bppe_ptr=0x0 bppe_cnt=0x0 bppi_cnt=0x8  bpstat=0x115
[post-initsat]   init=0x1 bppi_ptr=0xc700bf r8044=0x0 bppe_ptr=0x0 bppe_cnt=0x0 bppi_cnt=0x8  bpstat=0x115
```

Two things this buys us:

1. **It kills the DMA/WC-cache-flush theory properly.** The previous
   session refuted it by reading the DDR list *later* and finding it
   intact — which does not prove it was intact at the INIT edge. Here the
   INIT 0→1 edge is driven long after boot, with the list provably already
   in DDR, and the engine still ingests nothing. Stock's
   `dma_cache_maint(bppe,0x20000,1)` vs mainline's `dma_wmb()` is not the
   difference.
2. `bpstat` (0x80dc) bit30 — set on stock (`0x40000111`), clear on mainline
   (`0x00000111`) — did **not** appear after any re-init/kick/initsat, and
   the alloc-kick moved `bppi_cnt` **down** (0xc→0x8) with no refill.
   Confirms the earlier localization: the DDR→on-chip prefetch never runs,
   and bit30 is the read-only "engine has a DDR pool" status.

## 5. Standing contradiction that the next session should resolve first

The "BP starvation" mechanism in the predecessor doc is **not consistent
with the HW ledger**, and this should be confronted before more effort
goes into priming the pool:

- The BMU alloc/release ledger (`0x8090`/`0x8098`, HW-counted) is
  **balanced** at wedge onset (constant boot offset, no drift) — measured
  in the predecessor session and again at idle here (alloc−rls ≈ −16
  constant across all 5 instances). A per-frame BP leak would show as
  unbounded drift. It does not.
- A ~15-BP margin with a one-BP-per-frame leak predicts a wedge at ~15
  frames, not at the measured 967.
- The alloc path demonstrably works on mainline (RX/TX/12 GB of eth
  HW-offload) with `bppe_cnt=0` from boot, so "pool empty" is the *normal*
  mainline operating state, not an onset condition.

So `bppe_cnt=0` is better read as a **long-standing mainline condition**
than as the wedge's proximate cause. It remains a real stock divergence
worth fixing, but the causal link to wedge #2 is unproven and partly
contradicted.

## 6. State of the fix thread

- top_crm: **closed/refuted** (§1).
- SW priming of the pool: **closed/refuted** (predecessor, on live stock:
  the cursor/level regs are engine-maintained and SW-write-immune) and now
  also via the re-init edge (§4).
- AXI QoS @0x00a20000: **real divergence, landed** (§2), **not the pool
  gate** (§3).
- Remaining untested lead for the pool, in priority order:
  1. **bppe table placement.** Stock puts bppe at carve+0 (`0x4C000000`,
     jumbo +0x10000, ACL +0x20000, flow +0x420000). Mainline matches stock
     on ACL/flow offsets but puts bppe at **carve+0x2700000**
     (`0x4E700000`) — chosen to coincide with the FT PM-external carve
     base, which is exactly what forced fix #1b (pm_ext was memsetting the
     BPPE head). Carve+0..+0x20000 is an unused hole of precisely the size
     stock's bppe region occupies. Moving bppe back to carve+0 is both
     stock parity and removes the pm_ext overlap; it also tests whether
     the engine's bppe base has an address/window constraint. **Cheap,
     untried, highest value.**
  2. sys_ctrl (0x94100000) live diff — no stock capture exists yet (this
     session's stock-boot step was not needed once top_crm came back
     identical; a stock capture of *this* block is the one still missing).
  3. Per-stage vanish localization at onset (0x921cc044 SIPC→SPA handoff +
     the mainline-only BMU distress counters 0x8050=8 / 0x8054=0xa /
     0x80e0=0xfb1 / 0x80e4=0x3b0, all 0 on stock and climbing with
     traffic).

## 7. ⚠⚠ ENDURANCE A/B — A09 is NOT the wedge fix, and single-run endurance results are WORTHLESS

Two endurance runs of the **same A09 build**, same rig, same tool
(`endur2.py`, throttled ~1 MB/s continuous phone→WAN upload, ftwifi on,
idm1 up) — the shape that produced the historical 967/965 onsets:

| run | boot | start inj | outcome |
|---|---|---|---|
| 1 | warm (device had already pushed 82k frames) | 82,332 | **PASSED 205,463** — ~148k genuinely HW-forwarded frames (dfwd 27k–31k per 12 s window), BMU ledger flat (−11→−18), no wedge |
| 2 | **fresh boot** of the identical build | 944 | **TRUE WEDGE at inj=1,755** (dn_trap frozen at 0x47 under 5 host pings) |

**Verdict: A09 does NOT fix wedge #2.** Run 1's survival was environmental,
not causal — exactly the confounder to worry about, since the predecessor
doc notes the onsets happen in *retransmit-heavy windows* driven by the
flaky modem-WiFi leg, and run 1's link was healthy. `ftwifi` stays
**default OFF**. A09 is retained purely as verified stock parity (§2, and
now confirmed against live stock — see below), not as a fix.

**The methodological lesson is the most valuable output of this session:**
one clean endurance run — even 205k frames, 200× the onset — is NOT
evidence that this wedge is fixed. The onset variance on a *single
unchanged build* spans 1.7k → >205k. Any future claim of "wedge fixed"
needs **several fresh-boot runs**, and a fresh boot is mandatory (run 1
was warm and started 82k frames deep, already past the hazard window).

### Live-stock confirmation of the A09 values (the capture the task wanted)

Read read-only over SSH from a live stock box (`/bin/devmem2`; note stock's
busybox 1.17 has **no `head`**, which silently broke a first attempt).
Stock LIVE matches the static RE **exactly**, and matches post-fix mainline
byte-for-byte:

```
00a20000 0d000000     00a20078 1f0f1f0f     00a2007c 1f0f1f0f
00a20080 40000001     00a20084 bfffffff
00a20088 1f0f1f0f     00a2008c 1f0f1f0f
```

So `+0x7c` mirrors `+0x78` and `+0x8c` mirrors `+0x88` on stock too (the
mirroring seen live on mainline is real HW behaviour, not an artifact), and
`+0x84` genuinely *retains* `0xbfffffff` rather than acting as a
write-only clear. Also captured: stock `sys_ctrl` (0x94100000) is zero
across +0x00..+0x1c except **+0x10 = 0x100** — so the A06 "clear bit11
(0x800)" step is consistent with stock and sys_ctrl holds no other
divergence in that window.

### Wedge-2 signature at the run-2 onset (unchanged from the predecessor)

```
BMU:  all 5 inst: pool=0/0 avail=0 alloc=194 rls=205 alloc-rls=-11   (BALANCED)
QMG:  dn_sw=0x1b dn_hw=0xb2e dn_trap=0x47(FROZEN) up_sw/up_hw/up_trap=0
RED:  fwd_in=0xb4a fwd_out=0xb49  trp_in=0xaa trp_out=0xa5  drop=0x6
      pp_drop=0x4  sadm_pass=0  sadm_drop=0  mac2_tx=0xf
```

Balanced ledger + `bppe_cnt=0` + everything else healthy — i.e. the
resource is **absent, not over-charged**, and *not* a BP leak. This is
further evidence for §5: `bppe_cnt=0` is a benign long-standing condition,
and the BP-starvation story does not explain this wedge.

### New characterization worth chasing (hypothesis, n small — do not over-trust)

Every post-fix-#1 onset now on record is **early**: 967, ~965, and 1,755 —
all within ~1–2k frames of the flow starting on a fresh boot. The much
larger onsets (19.6k–71.8k) all predate fix #1 and belong to the
double-free bug. Run 1 entered already 82k frames deep and never wedged.
That shape is a **cold-start / first-few-thousand-frames hazard** (an
init-ordering or warm-up race, or a first-consumption of something
uninitialized), *not* a wear-out/leak. If it holds, the right experiment is
to instrument the first ~2k HW-forwarded frames on a fresh boot rather than
to run long endurance tests at all — which would also make each iteration
minutes instead of an hour.

## 8. ★★ THE REAL LOCALIZATION: 0x921cc008 is a SIPC occupancy gauge that fills to saturation and halts the fabric

This is the most valuable result of the session. Enabled by the §7
reframing (the wedge is early ⇒ a 1-minute repro), the new tracer
`wedge_coldstart.py` samples a deliberately small 9-register set every ~3 s
from flow start. It caught the collapse in the act:

```
r12-r16  sipc_008=0xddd011   up_fwd +2434,+2371,+2310,+2433,+2352   healthy
r17      sipc_008=0xeee011   up_fwd +2345
r18      sipc_008=0xfff011   up_fwd +2419      <-- SATURATED
r19      sipc_008=0xfff011   up_fwd +2268
r20      sipc_008=0xfff011   up_fwd  +657      <-- collapse begins
r21      sipc_008=0xfff011   up_fwd    +1
r22-r25  sipc_008=0xfff011   up_fwd     0      dead
r26      sipc_008=0x111011   up_fwd  +905      <-- WRAPS -> brief recovery!
r27-r29  sipc_008=0x111011   up_fwd     0      dead for good
```

**Mechanism**: `0x921cc008` bits[23:12] are three 4-bit gauges that climb in
lockstep with HW-forwarded fabric traffic (~2-3k frames per step). The
fabric halts the moment they saturate at `0xf`. The wrap back to `0x1` frees
headroom and buys a brief, partial recovery burst before saturating again.
Nothing else moved first: `bmu_e0/e4` were pinned at 0xfb1/0x3b0 the whole
run and `sipc_drop` was static at 0x80000, so this is the **first** stage to
go, not a downstream symptom. It also retro-explains the predecessor's
one-off note ("0x921cc008 stepped 0x111011→0x222211 at one onset") — same
register, now with the full progression and the causal link.

**Stock comparison** (`sipc_diff.py`, vs `captures/fpga/npp_block_stock.txt`):
stock reads `0x921cc008 = 0x00000399` — the three high nibbles are **000**,
i.e. on stock this resource drains. 10 registers in the block differ.

### …but the block is READ-ONLY, and SIPC config parity is exact

Tested live on the wedged box (`unwedge_test.py`): writes to `0x921cc008`
(→0x399), `0x921cc040` (→stock 0x01980000) and `0x921cc03c` (→stock 0x318)
are all **deaf** — every readback unchanged, box stayed wedged. So those
registers are HW **status**, and they differ from stock because the *state*
differs, not because mainline misprograms them. Confirmed from the decomp:

- `pon_npp_sipc_init()` is literally `npp[0xc000] = 0x11` — exactly what
  mainline's `npp_write(e, NPP_REG_SIPC_INIT, 0x11)` does.
- The whole `zx_sipcregtable` is 2 entries, both at `0x921cc000`: bit0 =
  `sipc_set_rx_en`, bit2 = `sipc_set_cpu_up_en`. Live, **both** stock and
  mainline read `0x921cc000 = 0x00000011` (rx_en=1, cpu_up_en=0).

So there is **no SIPC configuration divergence at all**. The gauge fills
because something downstream never releases the resource.

### What the resource almost certainly is (next session starts here)

The stock symbol names around this block are decisive:
`sipc2cpu_ful_cnt_up`, `sipc2cpu_ful_cnt_dn`, `sipc2cpu_aful_cnt_up`,
`sipc2cpu_aful_cnt_dn` ("SIPC→CPU FIFO full / almost-full"), plus
`sipc_desc_full_err` / `sipc_desc_empty_err`.

⇒ Hypothesis: **HW-forwarded fabric frames still enqueue an SIPC→CPU
descriptor that mainline never consumes.** Mainline's RX path drains the TM
rings; if the SIPC→CPU descriptor ring is a separate producer/consumer pair
that only stock services, then every HW-forwarded frame leaks one slot until
the ring is full and the fabric stalls. This fits every observation:
SW-forwarded traffic is fine (the CPU consumes it), eth HW-offload is fine
(trap-all → CPU consumes), and only ports-6/7 fabric HW-forwards leak. It
also matches the ~2-3k-frames-per-step fill rate against a small ring.

Concrete next steps: RE `tm_pon_npp_sipc_initial` and the `sipc2cpu_*`
counter accessors to find (a) the SIPC→CPU descriptor ring's base/producer/
consumer registers, and (b) whether stock arms an auto-discard/auto-release
for frames not destined to the CPU. Use `wedge_coldstart.py` as the oracle —
a candidate fix is right if `sipc_008` stops climbing, which is visible in
~1 minute instead of an hour of endurance.

## 9. Tooling / rig notes

- `scratchpad/bmu_reinit.py` — live BMU engine re-init/kick/initsat probe
  (`reinit|kick|initsat|all`), paced for the console.
- busybox `devmem` **is** present on the mainline initramfs → arbitrary
  phys read/write for out-of-poke-range blocks (top_crm, 0x00a20000).
  `/bin/memdump <phys> <len>` for bulk reads. The debugfs `poke` path
  remains the right tool inside `[0x921c0000,0x923c0000)`.
- Endurance harness gotcha that cost a cycle here: **never pipe
  `endur2.py` through `tail`** — it buffers until exit, so a long run is
  completely blind. Run it unbuffered (`python3 -u … > log`) and tail the
  log.
- `wifi_up.py all --adb --offload` brought the AP + phone + nft rig up
  cleanly; the documented gotcha still applies — it binds the vif but
  never ups idm1, so **`ip link set idm1 up`** is required or UP injection
  is silently off.
