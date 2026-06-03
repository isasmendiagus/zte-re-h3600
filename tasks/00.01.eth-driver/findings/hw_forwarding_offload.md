# HW bridge offload — overnight loop working state (branch hw-bridge-offload)

GOAL (user, 2026-06-03 night): leave the driver functional + tested for ALL THREE — ① ping
② bridge comm (lan<->lan) ③ good perf/streaming — with **HW FORWARDING, not CPU**. Stop the loop
only when all 3 work. Document + commit every iteration. Resolve by morning.

## What works / what's the blocker (from the port1-redwedge-debug investigation, now merged to main)
- ① ping: ✅ (clean boot, bidirectional).
- ② bridge comm: ✅ functional but via SOFTWARE bridge (CPU) — offload_fwd_mark fix (tag_zte.c,
  merged main 8bc9beb32) + flood masks poked. CPU-bound, wedges under load. NOT HW.
- ③ perf/HW forwarding: 🔴. The switch traps EVERYTHING to CPU (QMG UP hw_trap climbs, hw_fwd=0).
  A 30MB bridge stream pushed tm_rx +573 (1:1 = CPU/SW bridge), <7Mbit, then WEDGED.

## Key facts established
- sbrag L2-fwd ENABLE regs are ALREADY ON in mainline: transfer_en 0x92388004[7:0]=0xff,
  smac_look_en(learning) 0x923881c0[7:0]=0xff, da_lookup_en 0x923882c0[7:0]=0xff, learn_mode
  0x923881c4=0x5555. vlan_chk 0x92388008=0x0000ff00.
- FLOOD masks were OFF; poking them enabled SW-bridge ARP: brdcst_fwd_en 0x92388300[15:8] (was 0
  → poke 0xff), unknown_ucast_fwd 0x92388340[31:24] (was 0x01 → poke 0xff). (unknown_mcast
  0x923882d4[31:24], unkmul_portmask 0x923882d8 x9, multicst_md 0x92388180[1].)
- DESPITE all the above ON, frames still trap to CPU (hw_trap, not hw_fwd). ⇒ the CLA/pipeline
  traps to CPU BEFORE the L2-forward engine, OR the FDB isn't populated so DA lookup misses.
- forward-vs-trap lever = the "pktdeal" values: sbrg_set_pt_smac_lookfail_pktdeal (stock=0),
  sbrg_set_unknown_unicst_pktdeal, sbrg_set_unknown_multicst_pktdeal, + da_lookup. pktdeal 2b/port
  (stock 0x5555 = "1" each). Need the meaning of pktdeal values {fwd/flood/trap/drop}.
- QMG counters: UP hw_fwd=0x9234c05c, hw_trap=0x9234c060, sw_fwd=0x9234c054; DN hw_fwd=0x9234c048.
  HW forwarding = hw_fwd should climb (it's 0 now).

## PLAN (iterate; document+commit each)
1. Clean boot. Check QMG **hw_fwd** during a bridge forwarding test: if hw_fwd>0 the switch CAN
   HW-forward (just need it primary); if hw_fwd=0 the CLA traps before forward.
2. Check if the switch HW FDB (sbrag) actually LEARNS source MACs during traffic (read it back).
   If not learning → DA always misses → trap/flood (no HW fwd). Find why learning doesn't populate.
3. Find the CLA/pktdeal config that makes KNOWN-unicast hw_fwd instead of trap (RE
   decomp_all_tm.c cla_* / sbrg_set_*_pktdeal bodies for the value meanings; the stock per-port
   loop @43590 is the blueprint). POKE-test it live (tm_rx FLAT + hw_fwd climbs + throughput high
   + no wedge = success).
4. CODE it on hw-bridge-offload: implement .port_bridge_join (dsa_switch_ops) that programs the
   switch to HW-forward bridged ports + the flood-mask enable in driver code; restore
   offload_fwd_mark (correct once HW forwards); keep a STATIC trap entry for the CPU MAC so
   to-CPU (mgmt/ARP-to-device) still works. RISK: wrong un-trap breaks CPU connectivity — keep the
   CPU-MAC trap + test ping-to-device after every change.
5. Rebuild (build_slotA.py) + boot (uart.py auto_bootm_dtb_appended) + VERIFY all 3: ping,
   bridge comm (HW: tm_rx flat), sustained throughput (no wedge, >>7Mbit).

## TOOLS / GOTCHAS
- Device mainline (RAM-boot). Rebuild: `python3 tasks/00.01.eth-driver/scripts/build_slotA.py`
  (make all + zImage + tftp/zImage_dtb.uimg). Boot: stop bridge `fuser -k /dev/ttyUSB0`, then
  `nohup python3 lib/uart.py auto_bootm_dtb_appended >/tmp/boot.log 2>&1 &`; wait ~3min for
  "C-init REPL ready"; then `fuser -k /dev/ttyUSB0`; restart `nohup python3
  tasks/00.04.02.uart-bridge/uart_bridge.py &`. NEVER pkill -f a pattern in my own cmdline (self-
  kill exit 144) — use fuser.
- REPL :9999 (simple spaced cmds). peek/poke: `echo 0x<phys> [val] > /sys/kernel/debug/zx_eth/poke`,
  read `dmesg|grep peek`. TM reg phys = 0x92340000+off; sbrag phys = 0x92388xxx direct.
- Host: sudo -S available (password provided by the user this session). netns fwd test = jack2
  (enxc8a362e95900->lan1) + jack4 (enx6c70cbb68169->lan3); device br0=lan1+lan3; nsA=10.0.0.1
  nsB=10.0.0.2; stream nsA->nsB. (jack3 enx2c99 vanished from USB — ignore it.)
- C-init leaves IP on conduit sw + lanN DOWN; for bridge test: brctl addbr br0 + addif lan1 lan3.
- NEVER touch main / break egress. Test on HW before asserting. Commit+document each iteration.
