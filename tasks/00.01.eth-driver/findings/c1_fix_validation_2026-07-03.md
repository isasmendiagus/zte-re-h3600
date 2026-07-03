# C1 fix — build, boot, residual capture, regression retest, clean handoff (2026-07-03)

**VERDICT: The C1 config-alignment fix is APPLIED, BUILT (#468), BOOTED, and VALIDATED
on HW with ZERO regression.** `zx_ffe_arm`'s `idx9[4]` was changed `0x00150151 →
0x00150001` (aligns ram0[9] word4 to `zx_ffe_table.h` `zx_ffe_index[9]` + the packer's
`extr_index` low byte `0x90`). The residual datum from the C1 reconciliation is now
captured: **ram0[9] word4 reads `0x00150001` both BEFORE and AFTER a DSA tc-flower add**
— byte-identical — so `zx_ffe_arm` can no longer set the FFE selection wrong, whether or
not its `ram0[9]` write commits. All four multi-flow hardening behaviours reproduce
exactly as on #466 (match-forward / selective / collision-reject / overflow-decline),
with 0 real Oops/BUG/panic. Device left clean on #468, REPL alive, rig intact.

Device: mainline **#468** (`Linux 6.6.0 #468 Fri Jul 3 05:08:22 UTC 2026`, cross-compiler
`arm-linux-gnueabi-` — note #466 was `-gnueabihf-`, confirming a fresh image), fresh DTR
boot, RAM-only, NO reboot. trap_dmac[0] @0x921d41a0 = 0 (cleared). DSA up: lan1 + lan4
Link Up 1Gbps/Full. lan1=172.31.9.1/24, lan4=192.168.9.1/24, ip_forward=1 (rc.router).
CLA FFE extract init: 82 ok / 0 fail. Counters: cla_tx_fwd 0x9238c3c0, cla_tx_trp
0x9238c3c4. Host rig: enxc8a362e95900 = 192.168.1.50/24 (tftp) + 172.31.9.50/24; raw L2
injection via `/usr/local/bin/python3-netraw scratchpad/rawflow.py <dst> <dport> 400`
(pins the exact 5-tuple src 172.31.9.50:50010 → dst 192.168.9.50:<dport>, matching the
driver's HW-hash key builder which uses the full 5-tuple incl. sport).

---

## STEP 1 — BUILD + BOOT ✅
- Source already carried the fix (`zx-dsa.c:695` `idx9[5] = {…, 0x00150001}`, with an
  explanatory comment block at :678-687). The rule is still written to slot `0x98`
  (`zx_cla_wr(p,1,0x98,rule90,17)`) — inert/harmless since bit8 is now disabled; only the
  `ram0[9]=0x00150001` enable-bit-0 selection matters.
- Rebuilt via `scripts/build_slotA.py` (make all → stage `.ko` to /tmp/initramfs_extract →
  re-embed zImage → wrap `tftp/zImage_dtb.uimg`). The trailing `slotA body exceeds NAND
  write size` error is only the NAND-flash step (we TFTP-boot the uimg, not flash) — the
  uimg was written by mkimage first (05:08, 14,941,783 B). The `.ko` was untouched by this
  built-in-only fix (staged md5 unchanged from #466).
- DTR-boot: `UART_TCP=1 python3 lib/uart.py auto_bootm_dtb_appended`. Confirmed fresh
  banner **#468**, trap_dmac cleared, REPL responsive, DSA links up.

## STEP 2 — RESIDUAL DATUM (the one open C1 point) ✅
`clapeek ram0 9` reads all 9 words `93929190 97969594 9b9a9998 9f9e9d9c 00150001 0 0 0 0`.

| when | ram0[9] word4 |
|---|---|
| BEFORE any tc-flower (conduit probe value) | **0x00150001** |
| AFTER installing one DSA tc-flower on lan1 (zx_ffe_arm ran) | **0x00150001** |

The two reads are **byte-identical**. dmesg confirms `zx_ffe_arm` executed on the flower
add (`[phase6] FFE extract armed (ram1[0x98] + ram0[9] fast-enable)`) and the recipe
installed (`raw=0xf6d5 buckets ram2[0xd5]/3[0x155]/4[0x195]/5[0x1d5]/6[0x205] rc=0`).

**Interpretation:** whether `zx_ffe_arm`'s `ram0[9]` write commits through the DSA mapping
or is dropped (the C1-reconciliation open question), the live value is `0x00150001` in
both cases — the correct, HW-validated selection (enable bit 0 → rule 0x90 → matches the
stored `extr_index` low byte 0x90). The fix makes the arm correct-by-construction: the
old `0x00150151` (which would select slot 0x98 → LOOK_UP_MISS) can never be the live
value again. The identical before/after reading is consistent with the arm write landing
on the same value the conduit already set (no observable change to the register).

## STEP 3 — REGRESSION RETEST ✅ (all match the #466 baseline; NO regression)
Counters read via `poke` debugfs; flows injected as 400-pkt raw L2 UDP bursts.

**(a) match forwards / non-match traps:**
- dport53 (installed, raw 0xf6d5): cla_tx_fwd 0x0→0x190 (**+400 exact**), trp flat → FORWARD.
- dport9999 (not installed): fwd flat, trp 0x57→0x1e7 (**+400 exact**) → TRAP.

**(b) two distinct flows coexist + selective:**
- +dport100 (raw 0x810c, ram2[0x0c], distinct from 0xd5): installs rc=0.
- dport53 fwd +400, dport100 fwd +400 (both coexist), dport8888 (not installed) trp +400
  → selective forwarding.

**(c) collision-reject, first flow untouched:**
- dport200 (raw 0x455c, way0 0x5c) installs rc=0.
- dport3002 (raw 0x335c, way0 0x5c) DECLINED: `offload declined: CLA bucket collision
  cookie=c4986800 raw 0x335c (way0 0x5c already owned) -> stays in SW` (tc EOPNOTSUPP).
- dport200 STILL forwards +400 (not clobbered); dport3002 traps +400 (no HW entry).

**(d) overflow declines cleanly:**
- Filled the tracker to exactly **32** (`tc filter show` = 32 handles). Further adds
  DECLINED: `offload declined: flow table full (max 32) … -> stays in SW` (7 observed,
  distinct raws 0x1d53/0xb32e/0x13a9/…). No leak (reserve runs before any CLA write).
- Post-overflow dport53 still forwards +400 exact → table intact, no corruption.

**0 real Oops/BUG/Call-trace/panic** all session (the 2 crash-regex hits are the benign
boot lines `printk: debug: …`, "bug:" as a substring of "debug:").

## STEP 4 — LEFT CLEAN ✅
- `tc qdisc del dev lan1 clsact` (rc=0) → all test filters removed via the ownership-checked
  untrack path; lan1 back to `noqueue`, 0 filters. CLA tracked-flow buckets zeroed.
- Final state: #468 running, REPL alive; trap_dmac[0]=0; lan1+lan4 UP/LOWER_UP noqueue;
  lan1=172.31.9.1/24, lan4=192.168.9.1/24, ip_forward=1. Host rig intact (192.168.1.50 +
  172.31.9.50). WAN/PPPoE untouched. No wedge (light test flows on a fresh boot).
- Driver source: `zx-dsa.c` fix in place; NOT committed (per instruction).

## Conclusion
C1 is downgraded from a latent hazard to RESOLVED-by-alignment. The fix is byte-for-byte
the FFE config every validated HW forward (#456/#462/#464/#466) rode on, so it carried
zero regression risk — confirmed empirically here on #468. The residual reconciliation
datum is closed: ram0[9] word4 = 0x00150001 before and after a DSA flower add.
