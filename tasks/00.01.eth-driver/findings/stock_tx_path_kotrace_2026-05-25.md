# Stock TX path captured via kotrace v2 — 2026-05-25

Status: **WORKING TX TRACE OBTAINED** on stock 4.1.25.

## Method

1. Boot stock kernel + canonical 00.02 rootfs (no kotrace baked in).
2. Wait for SSH (br0 + cspd up, ping bidi 0% loss).
3. tftp-push `kotrace.ko` (v2: 2157 fns from kt_modules) + `insmod`.
   Patches ~1500 functions live, including the TX path in
   `plat_zxylzb_9128S.ko`.
4. `echo > /proc/kotrace_dump` — reset ring (write handler added 2026-05-25).
5. `ping -c 5 -i 0.5 192.168.1.1` from host.
6. `cat /proc/kotrace_dump` — exfiltrate via SSH.

Raw capture: `captures/stock_tx_5pings_2026-05-25.txt` (5167 lines).
Resolution tool: `scripts/analyze_kotrace.py` (maps func_addr →
symbol via the UART patching log).

## TX call sequence per packet

Per icmp-echo-reply from the device to host (one of 5):

```
pdt_ethdrv_send(r0=skb_or_dev, r1=netdev, r2=cb1, r3=pdt_ethdrv_send)
  pon_tm_net_tx(r0=skb, r1=dev, r2=cb, r3=pon_tm_net_tx_addr)
    pon_tm_get_next_txdesc(r0=1, r1=0, r2=desc_idx, r3=desc_idx)
    pon_tm_data_raw_send(r0=skb, r1=&bp_buf, r2=1, r3=&bp_buf)
      pon_tm_bmu_alloc_bp(r0=?, r1=&bp_buf, r2=1, r3=&bp_buf)
    soft_insert_tx_1desc(r0=&bp_buf, r1=1, r2=cb, r3=tx_seq)
```

Then periodic (every ~10 ms, decoupled from per-packet):

```
pon_tm_timer_func(r0=0, r1=&pon_tm_timer_data, r2=0, r3=…)
  pon_tm_check_tx_done_nolock(r0=1, r1=0, r2=desc_idx, r3=desc_idx)
```

## Variable evolution across the 5 pings

Per-packet incrementing values (from rows 5141..5153 of the capture):

| Packet | get_next_txdesc r2/r3 | data_raw_send r1 (bp_buf) | soft_insert r3 |
|---|---|---|---|
| 1 | 0x4d7 | 0xcfff1e60 | 0x8a12 |
| 2 | 0x4d8 | 0xcfff1e70 | 0x8a16 |
| 3 | 0x4d9 | 0xcfff1e80 | 0x8a1a |
| 4 | 0x4da | 0xcfff1e90 | 0x8a1e |
| 5 | 0x4db | (via check_tx_done) | — |

Confirmed mechanics:
- **desc_idx** increments by 1 per packet (in r2 and r3 — same value
  emitted twice; probably one is in, one is out).
- **bp_buf** address increments by 0x10 = 16 bytes per packet. Matches
  the BMU's bp slot stride.
- **tx_seq** increments by 4 — could be HW-side TX FIFO id or a
  hardware-issued timestamp tick.
- **pon_tm_check_tx_done_nolock** runs from the per-instance timer
  (`pon_tm_timer_func`), NOT inline with TX — it drains the HW done
  counter on a separate schedule.

## Stock vs mainline — register-level mismatch

### `soft_insert_tx_1desc` decomp

```c
void soft_insert_tx_1desc(undefined4 param_1, int param_2) {
  dma_cache_maint(param_1, 0x10, 1);   // flush 16-byte desc to RAM
  if (param_2 == 0) tm[0x10054] = 1;   // upstream kick
  else              tm[0x10064] = 1;   // downstream kick
}
```

**Direction selection**: `pon_tm_data_raw_send` passes `direction` through.
Our trace shows direction=1 (DN) for LAN-side ICMP replies. The
mainline driver kicks ONLY `tm[0x10054]` (UP) and has the DN kick
commented out — yet ping-bidi has been working. Hypothesis: in the
current mainline init, switch routing forces packets onto the UP queue
regardless, so the UP kick happens to drain LAN replies; under load
this might fall apart. Add DN kick when `skb`-direction is to LAN port,
or just dual-kick like the earlier baseline did.

### `pon_tm_check_tx_done_nolock` decomp

```c
void pon_tm_check_tx_done_nolock(int param_1) {
  if (param_1 != 1) net_txq[16] -= tm[0x10058] & 0xffff;  // UP done
  else              net_txq[44] -= tm[0x10068] & 0xffff;  // DN done
}
```

Subtracts HW done-counter from an SW outstanding counter. Stock runs
this from `pon_tm_timer_func` (independent of the TX kick path).
Mainline reads `tm[0x10058]` in STATS but never explicitly drains
`tm[0x10068]` — could explain why STATS shows `tx_done=0` even when
wire emissions ARE happening (we're reading the wrong counter for
LAN traffic).

## Differences from mainline driver

Mainline `zx279128-eth.c` already has the bp_buf+16 wire-format fix
(commit 3955d6cae) and the real `zx_bmu_alloc_bp` (commit 215b4c7bd).
Open deltas to investigate:

1. **`soft_insert_tx_1desc`** — stock calls a sw-side descriptor-ring
   helper that the mainline driver never invokes. The function takes
   (bp_buf*, 1, cb, tx_seq). Sequence-counter rotation may be the
   piece feeding stock's `pon_tm_check_tx_done_nolock` — if mainline
   never inserts to that ring, the HW done-counter can't be paired
   with a software outstanding-tx record, which would explain why
   `tm[0x10058]` reads 0 in mainline STATS.
2. **`pon_tm_get_next_txdesc` arg shape**: stock passes (1, 0, &out, &out)
   — both args 2 and 3 alias. Probably one is in (a tx-class id) and
   the other is an out-pointer for the desc_idx. The fact that they
   share the same address means the function writes into and reads
   from the same slot. Worth disassembling its prologue to confirm.
3. **`pon_tm_timer_func` cadence**: drains tx_done independently of
   tx submission. Mainline's BMU credit refill should be hooked into
   this path, not the TX kick path.

## Next steps

- Disassemble `pon_tm_data_raw_send`, `pon_tm_bmu_alloc_bp`, and
  `soft_insert_tx_1desc` to determine the exact register writes they
  emit (we have the C decomp in `decomp_all_plat_zxylzb_9128S.c`).
- Add `soft_insert_tx_1desc` equivalent to mainline TX or determine
  why we can survive without it.
- Wire `pon_tm_check_tx_done_nolock` semantics into mainline's NAPI
  poll so HW tx_done counter actually drains.

## Tooling additions (this session)

- `kotrace.c`: thunk now masks `ring_idx` to `RING_IDX_MASK` BEFORE the
  `<<5` shift — fixes silent OOB writes past `ring_buf` once the ring
  wraps. Suspected root cause of the boot hangs we saw when v2 (~2k
  patches) was baked into the rootfs.
- `kotrace.c`: each thunk now records the function address at
  `ring_entry+20`. Marker chars are first-letter-of-name and ambiguous
  (~166 different 'p' functions); the addr makes every entry uniquely
  resolvable.
- `kotrace.c`: `/proc/kotrace_dump` accepts writes — `echo > …`
  zeroes the ring so we can capture a clean delta around a specific
  event (5-ping bursts here).
- `kotrace.c`: `kotrace_exit()` now restores the original first
  instruction of every patched function before freeing — `rmmod
  kotrace` no longer crashes the device.
- `generate_kotrace_targets.py`: fixed the `plat-zxylzb_9128S.ko`
  hyphen-to-underscore mismatch (kernel reports module names with `_`,
  insmod translates `-`→`_` at load time). Without this, the entire
  TX-path module was being silently skipped at v2 walk.
- `scripts/analyze_kotrace.py`: host-side dump resolver — reads UART
  patching log + dump file, emits resolved one-liner per ring entry.
