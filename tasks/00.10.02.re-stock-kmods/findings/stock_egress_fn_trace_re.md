# Stock CPU→LAN egress: empirical function trace (kotrace on stock)

**Status**: DONE — decisive empirical result
**Date**: 2026-05-28
**Method**: kotrace.ko (RAM prologue-patcher) live-insmod'd on factory stock,
ring dumped via `/proc/kotrace_dump` over SSH during a host ping.
**Raw dump**: `findings/eg_kotrace_dump.txt`

## TL;DR verdict

For every CPU→LAN egress frame (device ICMP reply out MAC2/LAN), stock fires
**exactly four functions, in this fixed order**:

```
pdt_ethdrv_send (switch)  →  pon_tm_net_tx (plat)  →  pon_tm_data_raw_send (plat)  →  soft_insert_tx_1desc (plat)
```

- **`soft_insert_tx_1desc` DOES fire — on every single egress frame.** The
  decomp's "obvious TX path" (`pon_tm_net_tx → pon_tm_data_raw_send →
  soft_insert_tx_1desc`) is the REAL submit path. It is NOT dead, NOT
  diverged. The path runs end-to-end into the 1-desc ring-insert.
- The submit-path entry is **`pdt_ethdrv_send`** (switch.ko), which calls
  `pon_tm_net_tx` (the "sw" netdev `.ndo_start_xmit`, dir-1).
- `swport_dev_xmit_fin`, `soft_insert_tx_multidesc`, `dma_tx_free`,
  `dma_ram_get` **did NOT fire** at all.

## Ordered firing (5 ICMP replies + a few extra CPU-TX frames = 8 iterations)

Each iteration is the identical 4-call sequence. From the ring (seq 0–31):

| seq | marker | runtime addr | resolved fn | module |
|----:|:------:|:-------------|:------------|:-------|
| 0 | S | bf196130 | **pdt_ethdrv_send** | switch |
| 1 | T | bf021c80 | **pon_tm_net_tx** | plat |
| 2 | R | bf021964 | **pon_tm_data_raw_send** | plat |
| 3 | 1 | bf0211ac | **soft_insert_tx_1desc** | plat |
| … | | | (repeats ×8) | |

Counts over the 5-ping window: each of the 4 fired **8×** (one per CPU-TX
frame); the other 4 targets fired **0×**.

Address resolution (runtime addr − module base = nm offset, all exact):
- plat base 0xbf018000, switch base 0xbf195000.
- pdt_ethdrv_send off 0x1130, pon_tm_net_tx 0x9c80, pon_tm_data_raw_send
  0x9964, soft_insert_tx_1desc 0x91ac — all match `nm <stock.ko>`.

## Captured args (r0–r3 at entry)

- **pdt_ethdrv_send(skb*, dev/ctx)**: r0 = skb (cad2bb18 / cd0a2380 / …,
  rotates per frame), r1 = cd06a800 (const — net_device or port ctx),
  r2 = bf1a703c (const, switch .data ptr).
- **pon_tm_net_tx(arg, dev)**: r0 = same skb ptr threaded from
  pdt_ethdrv_send, r1 = cd98c000 (const netdev), r2 = bf025c74 (const plat
  .data).
- **pon_tm_data_raw_send(skb, bp_buf, dir=1)**: r0 = skb, r1 = cffefbX0 (BP
  buffer ptr, **increments +0x10 each frame** — successive BMU buffers),
  r2 = 0x00000001 = **dir=1** (confirms the DN/raw-send direction).
- **soft_insert_tx_1desc(desc, n=1)**: r0 = cffefbX0 (same BP buf = the
  built descriptor), r1 = 0x00000001 (1 descriptor), r3 grows
  (0xf7d0→0x615… a seq/cursor).

## Reconciling with the "ring kick is flat" measurements (STATE #11–13)

This trace proves `soft_insert_tx_1desc` runs. Prior live measurement said
the ring-kick registers (TM[0x10054]/[0x10064] etc.) never tick. Both can be
true only if **`soft_insert_tx_1desc` does NOT actually write TM[0x10054/64]
on this path** — i.e. the decomp's belief that 1desc-insert ends in a TM ring
doorbell is the wrong inference, OR the doorbell it writes is the SMCT
CPU-port channel (0x921d00xx) rather than the TM DMA ring. The function fires;
the *register it pokes* is what needs pinning next. **Next step:** trace one
level deeper — splice the leaf reg-write helpers called *inside*
`soft_insert_tx_1desc` (e.g. via kotrace targeting its callees, or capture its
body with the write-watch tool) to see which doorbell address/value it emits.
That address should be the SMCT submit doorbell that read-only sweeps missed.

## Instrumentation method & reliability

- **Tool**: `tasks/99.01.linux-stockport/kotrace/kotrace.ko` — RAM
  prologue-patcher (replaces target fn first insn with `b thunk` after the
  kernel loader resolves symbols; thunk records marker+func_addr+r0..r3 to a
  ring; restores all prologues on rmmod).
- **Focused build**: I wrote `kotrace_targets_egress.h` (only the 8 candidate
  fns, unique markers) and built a focused kotrace so the ring is tiny and the
  live switch/plat modules are minimally disturbed. Header file kept alongside
  kotrace.c; the full 2157-fn `kotrace_targets.h` was restored after build.
- **Reliability: HIGH.** Clean, deterministic, repeating pattern; addresses
  resolve exactly; rmmod restored cleanly and the device kept forwarding.
- **Transport**: SFTP is unavailable on factory dropbear, so the .ko was
  pulled to /tmp (tmpfs) via the device's `tftp` client from the host tftpd
  (192.168.1.50), then `insmod`. Ring read via `cat /proc/kotrace_dump` over
  the paramiko interactive shell. UART markers also visible via the
  kmsg2uart bridge (user observed the `[ko: target … patched OK]` lines live).

### Build gotcha (for next time — saved ~30 min)
Debian `arm-linux-gnueabihf-gcc` is `--enable-default-pie`, so a plain build
emits a `_GLOBAL_OFFSET_TABLE_` reference → the 4.1.25 module loader rejects
with the useless `insmod: ... unknown symbol in module, or unknown parameter`.
**Fix:** build with `KCFLAGS="-march=armv7-a -fno-pic -fno-PIE"` (the
`-march=armv7-a` is needed so inline `dsb` assembles; keep the kernel's
`-msoft-float` — do NOT add `-mfpu=neon`/hard-float). With those flags the GOT
ref disappears and insmod succeeds.

## Device state / recovery note

**No persistent changes.** Everything was RAM-only:
- kotrace.ko was insmod'd then **rmmod'd** (RC=0, prologues restored, device
  still pings). /tmp copy deleted. Host tftp staging copy deleted.
- NAND untouched (rootfs is jffs2 ro; nothing written to slot A/B).
- Device remains factory stock (192.168.1.1), forwarding normally.
- Recovery if ever needed: just power-cycle (RAM-only patches vanish);
  STATE.md "Last-known-good" table applies unchanged.
