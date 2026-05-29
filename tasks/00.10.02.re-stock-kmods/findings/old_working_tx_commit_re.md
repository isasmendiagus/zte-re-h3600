# Old working CPU→LAN TX commit — git archaeology

**Date:** 2026-05-28 · **Type:** investigation, no code change
**Question:** Did CPU→LAN TX egress (device → wire) ever actually work before "eth refactor #38"? If so, what did the TX submit path do differently?

## Answer: YES, it worked. Wire-confirmed on 2026-05-24, BEFORE refactor #38 (started 2026-05-26).

### Commit timeline (chronological, `git log --reverse`)
| Date | Hash | What |
|---|---|---|
| 05-24 13:12 | **`a3e6a8017`** | "Phase 4 COMPLETE: PING BIDI WORKS — TX desc[2..3] egress port fix" |
| 05-24 23:37 | **`3955d6cae`** | "frame must go at bp_buf+16 — wire-test confirmed" (200 device frames on wire) |
| 05-24 23:47 | **`2ad931ed8`** | "milestone: ping bidi WORKS on mainline driver" — **best working state** |
| 05-26 16:47 | `8a57adac2` | eth refactor #38 **Phase 1.a** (refactor STARTS here) |
| 05-27 14:52 | `bd3bc21a3` | "TX also broken at wire level — ZERO frames" (regression, AFTER refactor) |
| 05-27 14:57 | `915120431` | "HW won't consume TX descriptors — switch fabric egress wedged" |

The working TX is in the OLD monolithic driver `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c` (refactor #38 later renamed/rewrote it to `zx-eth-main.c`). TX worked from `a3e6a8017`..`2ad931ed8`, then regressed sometime after refactor #38 began.

### Evidence it was REAL wire egress (not loopback)
`ping_bidi_works_2026-05-24.txt` is a tcpdump on the HOST NIC (`enxc8a362e95900`). It shows device-originated frames arriving at the host: ARP Reply `192.168.1.99 is-at f4:f6:47:0f:42:64` and many `ICMP echo reply` from the device MAC. Device→wire→host frames received = TX egress genuinely worked. (Heavy DUPs = switch flooding/amplification, but egress itself was real; ~60% loss.)

## Working TX submit mechanism (`2ad931ed8`, fn `zx_sw_xmit`)
- **Ring/DMA:** ONE physical TX descriptor ring `txdesc_cpu/txdesc_dma` (1024 × 16B, `dma_alloc_coherent`). Crucially BOTH ring-base regs pointed at the SAME ring:
  - `tm_write(TM_REG_DMA_TX_UP_BASE=0x10050, txdesc_dma)`
  - `tm_write(TM_REG_DMA_TX_DN_BASE=0x10060, txdesc_dma)`  ← both = txdesc_dma
- **Kick register + base:** `tm_base = e->base + TM_OFF (0x180000)`. **DUAL kick every frame:**
  - `tm_write(e, 0x10054, 1)` — UP queue kick
  - `tm_write(e, 0x10064, 1)` — DN queue kick
  - Commit comment: single-kick (UP only) = 100% loss; **dual-kick = working 60% loss.** This is load-bearing.
- **Frame placement:** `memset(bp_buf,0,16); memcpy(bp_buf+16, skb->data, len)` — frame at BP+16 (HW 16-byte prefix). Same as current.
- **Descriptor (16B):** `desc[0]=0xc9`; `desc[2..3]=((port+0x28)&0x3f)<<4` with **port=0** → `0x280`; `*(u32*)(desc+4)=0x00010000`; `*(u32*)(desc+8)=(bp>>7)&0x7f | (len&0x3fff)<<9 | (0x21<<24)`; `desc[7]=(bp&0x7f)<<1`; `desc[12..13]=len-encoding` (no `|3`).
- **Extra setup:** real HW BMU allocator (`215b4c7bd`), HW FDB seed of self-MAC, and **bulk fpga.bin replay DISABLED** (`ZX_BULK_REPLAY=0`) — the 11456 replay writes clobbered config and killed TX. No explicit DSCH/QMG queue programming beyond stock-table init.

## Key DIFF vs current `zx_sw_xmit` (`zx-eth-main.c`)
| | Working `2ad931ed8` | Current |
|---|---|---|
| Rings | ONE ring, UP_BASE=DN_BASE=`txdesc_dma` | TWO separate rings: UP=`txdesc_cpu`, DN=`dndesc_cpu` |
| Desc written to | `txdesc_cpu` (the shared ring) | `dndesc_cpu` (DN ring only) |
| Kick | **BOTH** `0x10054` + `0x10064` | **ONLY** `0x10064` (DN) |
| desc[0] | `0xc9` | `0x80` |
| port hint | port=0 → desc[2..3]=`0x280` | port=4 → `0x2c0` |
| desc[12..13] | len enc, no fwd-class | `| 3` fwd-class added |

**Most likely culprit for "fetched-but-not-drained-to-QMG":** current submits on the DN ring and kicks ONLY DN (`0x10064`). The proven-working code kicked BOTH queues against a single shared ring; the commit explicitly recorded that UP-only single-kick = 100% loss. The DN-only single-kick regression mirrors that exact failure mode. Recommended first test: point UP_BASE and DN_BASE at the same ring, write the desc once, and dual-kick `0x10054`+`0x10064` (and revert desc[0] to 0xc9 / port=0 to match the known-good state).
