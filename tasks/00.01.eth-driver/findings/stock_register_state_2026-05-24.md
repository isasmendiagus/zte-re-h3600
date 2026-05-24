# Stock register state — running snapshot (2026-05-24)

Captured from device running stock kernel + kotrace.ko after full boot.
Method: `memdump <phys_addr> <size>` via SSH, tftp'd to host. Per-block
captures live at `tasks/00.01.eth-driver/captures/fpga/{pp,tm,npp}_block_stock.txt`
(text format: one line per dword `ADDR VAL\n`). Captures dir is gitignored.

## Per-port classifier blocks (PP +0x000..0x1FFF)

PP has 8 identical per-port config blocks, each 0x400 bytes:
- port 0 @ +0x000
- port 1 @ +0x400
- port 2 @ +0x800
- ...
- port 7 @ +0x1c00

Key fields per port (verified for port 0, identical for others):

| Offset | Value | Notes |
|---|---|---|
| +0x00 | 0x01 | enable? |
| +0x04 | 0x02abfc8d | |
| +0x08 | 0x01 | |
| +0x0c | 0x00640064 | |
| +0x20 | 0x00000fff | full 12-bit VLAN mask |
| +0x24 | 0x00000106 | same as +0x2c |
| +0x28 | 0x01070104 | **same value our pon_pp_ctrl_init writes** (per stock RE) |
| +0x2c | 0x00000106 | **NOT BIT(25)** — our mainline CPU_FWD is wrong |
| +0x30 | 0x00000101 | |
| +0x34 | 0x00010001 | |
| +0x3c | 0x00000106 | |
| +0x40 | 0x01030101 | |
| +0x44 | 0x00000106 | |
| +0x48 | 0x00111111 | |

**Critical fix needed**: our driver writes `PP[0x2c] |= BIT(25)` for CPU forwarding. Stock has `0x00000106` (bits 1, 2, 8) at +0x2c for *every* port block — NOT bit 25. Our interpretation of this register is wrong.

## Port isolation masks (PP +0x83c0..0x83dc)

```
PP[+0x83c0] = 0xfe   port 0 → block egress to port 0 (self)
PP[+0x83c4] = 0xfd   port 1 → block self
PP[+0x83c8] = 0xfb   port 2 → block self
PP[+0x83cc] = 0xf7   port 3 → block self
PP[+0x83d0] = 0xef   port 4 → block self
PP[+0x83d4] = 0xdf   port 5 → block self
PP[+0x83d8] = 0xff   port 6 (CPU) → block ALL egress
PP[+0x83dc] = 0xff   port 7 (CPU) → block ALL egress
```

**Semantics**: bit N set = "block egress to port N".

- Ports 0..5: HW default (no self-loop) preserved.
- Ports 6,7 (CPU): stock OR's with 0xdf. Initial value had bit 5 set already → 0x20|0xdf=0xff. So CPU ports cannot egress to anywhere via this register.

**Our mainline writes** `port_isolate(6, 0xdf)` directly (assignment, not OR) — wrong; we get 0xdf instead of 0xff, leaving bit 5 cleared = allowing egress to port 5.

## Other PP globals

| Offset | Value | Comments |
|---|---|---|
| PP[0x8004] | 0x040200ff | |
| PP[0x8008] | 0x0000dfdf | (we don't set this) |
| PP[0x8050] | 0x0000000a | **stock has only 0xa**; we write 0xfffffffa per decomp (decomp may be wrong/stale) |
| PP[0x8080] | (sample) | |

## SBRG HW FDB

Found 1 stock call at boot: `sbrg_add_mactable(slot=0x12, mac_ptr, mac_ptr, port=1)`.
That's the device's own MAC, registered at slot 0x12 with port=1. Region
PP[0x8400..0x8500] suspected for HW FDB table — needs deeper scan.

## Kotrace probe trace (8081 events captured)

From the new probes we added:
- `cla_set_oth_l3_pkt_action_cfg(0)` — 1 call (act=0)
- `spa_set_enty_pktdeal_cfg(entity 0..7, slot 0..58, 1, 1)` — 465 calls
- `sbrg_add_mactable(0x12, mac, mac, 1)` — 1 call
- `sbrg_change_portmask(0, 0, 0x7, 1)` — 1 call (mask=0x7 = ports 0,1,2)

**Did NOT fire** during init:
- `cla_set_local_ipv4_addr` ← KEY for HW ARP/ICMP responder
- `cla_set_local_ipv6_addr`
- `cla_set_cpu_queue_id`
- `dpa_set_protocol_cpu_pps_en`
- `dpa_set_protocol_pkt_aly_en`
- `spa_set_cpu_untag_pri/svid`

→ These are called later (probably when userland configures IP) or via
   a different code path (cspd direct register writes). Re-capture after
   triggering network reconfig.

## Implementation priorities for mainline driver

1. **Fix PP[0x2c]**: stop writing `BIT(25)`. The actual CPU_FWD config is
   `0x00000106` per-port-block, not bit 25 of a single global register.
2. **Fix port_isolate semantics**: use OR not assign, target ports 6,7 to
   end at 0xff (block CPU egress via this mask).
3. **Replicate `spa_set_enty_pktdeal_cfg`** loop: 8 entities × 58 slots
   with args `(entity, slot, 1, 1)`.
4. **Call `sbrg_add_mactable`** equivalent for our own MAC at probe time.
5. **Implement `sbrg_change_portmask(0, 0, 0x7, 1)`** — port mask 0x7
   means ports 0,1,2 allowed.
6. Set `cla_set_oth_l3_pkt_action_cfg(0)` to match stock default action.
7. Re-capture kotrace after WAN/IP reconfig to catch the remaining
   functions (cla_set_local_ipv4_addr etc.).

## Captures
All at `tasks/00.01.eth-driver/captures/fpga/` (gitignored):
- `pp_block_stock.txt` (256KB, 65536 dwords PP @ 0x92380000)
- `tm_block_stock.txt` (256KB, TM @ 0x92340000)
- `npp_block_stock.txt` (1MB, NPP @ 0x921c0000)
- `fpga_stock_working.bin` (4 MiB binary — older capture from when stock was working)
- `topcrm_stock.txt`, `range_9fe_stock.txt`, `pon_low_stock.txt`
- Raw kotrace dump: `tftp/kotrace_phase5b.txt` (8081 lines)
