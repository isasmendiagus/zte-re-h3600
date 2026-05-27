# [A11] fpga[0xd3000] link-state writer is NOT the TX-wedge cause

Hypothesis-validation experiment 2026-05-27 (Iter 11 of gap-matrix
loop). Tested whether the missing link-state writer for `fpga[0xd3000]`
is responsible for the TX-descriptor wedge ("HW won't consume TX
descriptors — switch fabric egress wedged", recorded in commits
`915120431` and `bd3bc21a3`).

## Test

1. TFTP-boot mainline (post Iter 10 refactor build). Stock ran on the
   previous power-cycle; SERDES warm-boot state inherited (now
   reproducible cold-boot via A03+A06).
2. From REPL, read fpga[0xd3000]:
   ```
   # /bin/memdump 0x9234c000 4
   9234c000 01f40fa0     ← link-DOWN init value
   ```
   This confirms gap A11 at runtime — PHY[0]+PHY[2] are link-UP per
   `adjust_link` callbacks (kernel log "PHY[0] link UP @ 1000/FD"), but
   the switch-alarm reg stayed at init value because mainline lacks
   the link-state-dependent writer that stock's
   `sw_port_alarm_kthread` runs.
3. Manually poke the link-UP value, no driver edits:
   ```
   # /bin/busybox devmem 0x9234c000 32 0x03f40050
   # /bin/memdump 0x9234c000 4
   9234c000 03f40050     ← link-UP value, write succeeded
   ```
4. Ping from host (`192.168.1.50`) → device (`192.168.1.99` on `sw`):
   ```
   PING 192.168.1.99 from 192.168.1.50: 56 bytes
   icmp_seq=1 Destination Host Unreachable
   icmp_seq=2 Destination Host Unreachable
   icmp_seq=3 Destination Host Unreachable
   5 transmitted, 0 received, 100% packet loss
   ```
5. Read TX/RX counters post-ping:
   ```
   tm_irq_count         = 0
   tm_rx_count          = 0
   tm_tx_count          = 11    ← unchanged from pre-poke (only stale
   tm_tx_dropped        = 3       IPv6 RA queue)
   tm_bmu_free_ok       = 0
   ```

## Conclusion

Writing `fpga[0xd3000] = 0x03f40050` alone does **not** unwedge TX.
`tm_irq_count` stays at 0 → TM IRQ never fires regardless. The reg is
the switch **alarm/LED** state, not a TX gate.

## Implication for the gap matrix

- A11 is still a gap (mainline lacks the link-state writer), but it's
  **cosmetic / monitoring**, not path-critical for TX. Re-rank from 🔴
  to 🟡 in the matrix.
- The TX-wedge cause must be elsewhere. Top candidates given
  `tm_irq_count == 0`:
  - **A07/A08/A09** — PON / NPP / TM IRQ registration. If the PON IRQ
    isn't actually routed, anything that gates the TM block can't fire.
    Worth checking that the new "pon" / "pp" IRQs in DT are actually
    `request_irq`'d (DT entries were added in [A02] but the request
    side may still be missing).
  - **A13** — `zte_zx_api_pp_set_trap_queue`. Without the protocol→CPU
    queue mapping, even if TM IRQ fired, frames wouldn't route to the
    CPU queue → tm_rx_count stays 0.

## Lesson learned

"Link-state-dependent" + "shared by all LAN ports" + "in switch.c" looks
like a TX-affecting reg at first glance, but the surrounding decomp
context (`sw_port_alarm_kthread`, `LedActionSet`, `g_LAN_ON_Flag`)
clarifies it's just for switch alarm/LED state tracking. Always read
the surrounding 50 lines of decomp before promoting a gap to "🔴
critical for TX".

## Driver state

No driver changes made (validation-first per project rule). The poked
value will reset to `0x1f40fa0` on next boot since mainline doesn't
have the writer.

Cross-ref:
- `tasks/00.01.eth-driver/findings/mainline_gap_matrix.md` [A11]
- `tasks/00.10.02.re-stock-kmods/findings/decomp_all_switch.c:4800-4830`
  (full link-state branch context)
- `tasks/00.10.02.re-stock-kmods/findings/static_analysis_zx_ponreg_init.md`
  ("sw_alarm_init") — confirms alarm-only semantics
