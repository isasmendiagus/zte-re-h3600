# SMCT CPU-port channel: register-layout map + submit mechanism (2026-05-28)

DECOMP-ONLY RE. Goal: find HOW the CPU submits a frame into the SMCT CPU-port
channel whose gauges 0x921d0040 / 0x921d004c tick live during egress, given the
UP/DN/IDM ring kicks (0x10054/0x10064/0x8040) are all flat live.

Sources read this session (line refs): `decomp_all_plat_zxylzb_9128S.c`
`dma_cfg_byteorder`@6165, `dma_ram_get`@6184, `dma_tx_free`@6212,
`soft_insert_tx_1desc`@6232, `soft_insert_tx_multidesc`@6247,
`pon_tm_dma_init`@6277, `pon_tm_check_tx_done_nolock`@6360,
`pon_tm_data_raw_send`@6596, `pon_tm_get_next_txdesc`@6687, `pon_tm_net_tx`@6719,
`ffe_learn_skb`@9767, `pon_npp_smct_init`@3333, `pon_npp_idm_init`@4340,
init seq @2244-2256, `pon_npp_sipc_init`@2260; `decomp_all_tm.c`
`greg_set_smct_ram_init`@22086, `smct_*_pmau`@25388-25560;
`regs/stock_eth_2mib.txt`.

## ADDRESSING (re-confirmed, two independent checks)
`npp_base == tm_base == phys 0x921c0000`. The "SMCT block" = `npp_base+0x10000`
= **phys 0x921d0000**. Proof: `pon_npp_smct_init` (plat:3338-3340) writes
`npp_base+0x10000=0xb`, `+0x10004=0xb`, `+0x10010=0x3810`; init@2254 writes
`npp_base+0x10008=0x80`. The 2MiB stock dump reads back exactly 0x921d0000=0xb,
+04=0xb, +08=0x80, +10=0x3810, +18=0x1. The block is named "smct" by its init fn.

## FULL SMCT/DMA REGISTER MAP (phys = 0x921d0000 + off; every decomp ref found)
| off | phys | written/read by (line) | meaning |
|---|---|---|---|
| +0x00 | 0x921d0000 | smct_init:3338 =0xb | ctrl/mode |
| +0x04 | 0x921d0004 | smct_init:3339 =0xb | ctrl |
| +0x08 | 0x921d0008 | init:2254 =0x80 | channel depth = 128 |
| +0x10 | 0x921d0010 | smct_init:3340 =0x3810 | base/cfg |
| +0x14 | 0x921d0014 | dma_ram_get:6195 (W cmd) | indirect-RAM cmd: `idx | 0x8000000 | sel<<22` |
| +0x18 | 0x921d0018 | dma_ram_get:6194,6198 (R bit0) | indirect-RAM DONE/READY (bit0=1) + enable |
| +0x1c | 0x921d001c | dma_ram_get:6199 (R) | indirect-RAM DATA out |
| +0x20/24 | ..0x20/24 | dma_init:6288/89 =0x20 | thresholds |
| +0x28/2c | ..0x28/2c | dma_init:6283/84 =1 | enable bits |
| +0x30 | 0x921d0030 | dma_init:6285 =50000 | timer/quanta |
| +0x34 | 0x921d0034 | dma_init:6286 =0x40 | threshold |
| +0x3c | 0x921d003c | dma_init:6299 =0x400040 | hi/lo watermark |
| **+0x40** | **0x921d0040** | **NONE — not read/written anywhere in decomp** | **HW-maintained free-level/head (LIVE 0xXYXY)** |
| +0x44/48 | ..0x44/48 | NONE | (flat) |
| **+0x4c** | **0x921d004c** | **`dma_tx_free` ONLY (6221 R-guard, 6222 W)** | **TX-buffer FREE doorbell, guard bit 0x200000** |
| +0x50 | 0x921d0050 | dma_init:6290 (W base) | UP ring desc base (DRAM) |
| +0x54 | 0x921d0054 | soft_insert_tx_1desc:6239 | UP ring KICK (flat live) |
| +0x58 | 0x921d0058 | check_tx_done:6366 (R&0xffff) | UP ring tx-done count |
| +0x60 | 0x921d0060 | dma_init:6294 (W base) | DN ring desc base (DRAM) |
| +0x64 | 0x921d0064 | soft_insert_tx_1desc:6242 | DN ring KICK (flat live) |
| +0x68 | 0x921d0068 | check_tx_done:6369 (R&0xffff) | DN ring tx-done count |
| +0x388 | 0x921d0388 | dma_init:6299/6298 =0x131217 | misc cfg |

So there are exactly TWO software desc rings (UP +0x50, DN +0x60). There is NO
third per-channel base/kick in 0x10040-0x4c. The 0x40/0x4c pair is NOT a ring —
it is the channel's HW free-level (0x40) + a software FREE doorbell (0x4c).

## SUBMIT MECHANISM — best supported hypothesis (confidence MEDIUM-HIGH)

1. **0x40 is HW-maintained, NOT a CPU submit.** No decomp instruction anywhere
   reads or writes `+0x10040`. The live "ticking" 0xXYXY is the hardware
   updating the channel free-level/head as it drains — i.e. the sweep saw the
   HW consumer side, not a CPU doorbell. (confidence HIGH — exhaustive grep.)

2. **0x4c is the post-egress FREE doorbell, not the inject.** `dma_tx_free`
   (plat:6214) writes `+0x4c = bp | 0x200000 | q<<12 | port<<20`, guarded by
   `(+0x4c & 0x200000)==0`. Bit 0x200000 = "request pending". This RECYCLES a
   transmitted buffer back to the pool AFTER egress; its low byte moving live is
   consistent with per-frame buffer frees, not frame submit. (confidence HIGH.)

3. **The actual frame SUBMIT is NOT in this decomp module.** `dma_tx_free` and
   `dma_ram_get` have ZERO C callers (grep of all 8 files), and `ffe_learn_skb`
   (plat:9767, switch:14063, idmfdb:2222) decompiles to a `halt_baddata()` PLT
   import thunk in the 0x2c1xx/0x2f1xx band — its BODY lives in another
   binary/module not in this corpus. The CPU-port inject is almost certainly a
   **function reached via that import/dispatch (FFE or an SMCT data-mover whose
   body is the missing thunk)**, OR an indirect-RAM write counterpart to
   `dma_ram_get` (a `dma_ram_set` using the same +0x14/+0x18/+0x1c port) that
   does not exist as a named symbol here. There is NO `dma_tx_alloc/send` in the
   decomp. (confidence MEDIUM — negative-space + thunk evidence.)

4. **`pon_tm_net_tx`→`pon_tm_data_raw_send`→`soft_insert_tx_1desc` is genuinely
   the WRONG path** for the live reply (re-read this session): it does
   BMU-alloc + memcpy + ring KICK 0x54/0x64 only — all flat live. It does NOT
   touch 0x40/0x4c or the indirect-RAM port. (confidence HIGH — confirms prior.)

5. **`smctRegTable`/`smct_*_pmau`/`greg_set_smct_ram_init` are a RED HERRING.**
   Those (tm:22086, 25388+) go through `tmOnuRegWrite/Read` indirection and
   program the TM packet-monitoring-accounting-unit (PMAU) and GREG RAM-init —
   a different "SMCT" (statistics) than the 0x921d0000 MMIO FIFO block. Not the
   submit. (confidence HIGH.)

## CONCRETE CONFIRMATION TESTS (read-only stock, same corrected method)
- **A — is +0x4c a per-frame free?** During `ping -c 100 -i 0.05`, double-read
  `fpga -r 0x74013 1` (0x921d004c) AND poll bit 0x200000: if it pulses set→clear
  per frame and the low 12 bits = a BP index that also appears in BMU 0x800c,
  then +0x4c = `dma_tx_free` running ⇒ a SOFTWARE TX path IS executing (refuting
  "no SW TX"), and the submit is its sibling (look harder for a `dma_ram_set`).
- **B — single-frame pulse on +0x40.** `ping -c 1`, capture +0x40 (0x74010)
  delta. If it steps by a fixed quantum per frame, it is head/tail of depth-128
  (+0x08=0x80) ⇒ confirms HW-drained channel, submit is upstream (FFE/SIPC).
- **C — indirect-RAM probe.** Read `fpga -r 0x74006 1` (+0x18) for bit0; if 1,
  issue `dma_ram_get`-style read via +0x14/+0x1c to dump the channel descriptor
  RAM idle vs egressing — the descriptor that changes IS the submitted frame,
  proving the submit writes channel RAM (indirect), not an MMIO doorbell.
- **D — mainline parity (the actionable one):** mainline must replicate
  `pon_npp_sipc_init` (0x921cc000=0x11) and the full `pon_tm_dma_init` block
  (NOTE: in stock_eth_2mib.txt the 0x10020-0x3c/0x50/0x60/0x388 cfg is ALL ZERO
  — that dump's boot never ran `pon_tm_dma_init`). Verify on the live STOCK box
  whether those regs are nonzero during real egress; if zero, the rings are
  genuinely unconfigured and the inject CANNOT be a ring — corroborating the
  FFE/indirect-RAM submit hypothesis.

## HONEST STATUS
- HIGH: SMCT register map above is complete and decomp-grounded; 0x40 is
  HW-maintained (no SW accessor); 0x4c is a buffer-FREE doorbell (`dma_tx_free`);
  the +0x50/+0x60 rings are the only two SW desc rings; the visible SW-TX path is
  not the live one; `smctRegTable` PMAU is unrelated.
- MEDIUM: the per-frame frame-SUBMIT itself is NOT a register in 0x10040-0x4c and
  is NOT present as a C body in this corpus — it is behind the `ffe_learn_skb`
  import thunk and/or an unseen indirect-RAM `dma_ram_set` writing channel RAM.
  Could not pin the exact write; tests A-C above will resolve which.
- Could NOT fully pin the submit because the decisive function body is a
  halt_baddata import thunk (missing binary), not because of an address error.
