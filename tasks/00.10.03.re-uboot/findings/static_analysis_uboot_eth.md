# U-Boot ethernet driver — static analysis

Static reverse-engineering of the ZTE H3600 U-Boot bootloader's
ethernet path. Goal: identify what HW state U-Boot leaves the chip in
when it hands off to the kernel, and whether the mainline kernel
driver port (`zx279128-eth.c`) overwrites or fails to set up state
that the stock kernel happens to inherit from U-Boot.

Source: `decomp_all_01_bootloader.c` (768 KiB image, 802 functions
loaded at virt `0x40e00000`, project `ghidra/h3600_uboot`).

Companion artifacts in this directory:
- `uboot_eth_periph_usage.txt` — full peripheral-base-address scan of all 802 functions
- `uboot_eth_decomp/FUN_*.c` — DAT-resolved decompilations of all ETH-relevant functions

Convention: each `DAT_xxxxxxxx` reference holds a 32-bit literal — the
companion files annotate it inline as `DAT_xxxxxxxx/*=0xVALUE[CLASS]*/`,
where CLASS identifies the peripheral block (MAC0, TM, MDIO, …).

---

## Summary

U-Boot uses a **5-port mini-switch model**: it brings up MAC[0..3]
(LAN1..LAN4) simultaneously via internal switch fabric. The TFTP /
ping path receives on any port. U-Boot does **not** use a single
"primary" MAC — packets are switched by the chip fabric.

| HW block | Base addr | Touched by U-Boot? |
|---|---|---|
| MAC[0..4] control / config / FIFO | `0x92200000 + N*0x40000` | ✅ ports 0..3 (LAN1..4) brought up; MAC[4] WAN untouched |
| MDIO | `0x9a101000` | ✅ register-based read/write w/ busy-poll |
| TM (Traffic Manager) | `0x92340000 / +0x4000 / +0x8000 / +0xc000` | ✅ FULL init: BMU pool, RX/TX descriptor rings, queue setup, 4 hash-table populations |
| ETH_NPP (Network Packet Processor) | `0x92350000` | ✅ config + MAC table base |
| ETH_TM2 (SFM/ACL block) | `0x923a0000` | ✅ MAC address table + 0xe0=0x11 |
| ETH_RESET / global | `0x92000008` | ✅ global per-port reset toggle |
| ETH_MISC | `0x92040000 / 0x921c0000 / 0x921cc000 / 0x921d4000 / 0x92380000 / 0x92388000 / 0x9238c000` | ✅ various block enable writes |
| TOPCRM (clocks) | `0x94000008 / 0x9400004c / 0x94000050` | ✅ chip clock-gate sequence |
| SYSCTRL | `0x94100010` | ✅ pin/mux select |
| PINMUX | `0x94200000` | ✅ touched by other init (not eth-specific) |
| SERDES | `0x9fe00000` | ✅ long PMA/PLL register sequence (epon-vs-gpon path) |
| L2CC (PL310) | `0x00c00000+0x100` | ❌ no touches detected; SoC may not expose PL310, or it stays off |
| GIC SPI enables | `0x80000100` | ✅ initialized by GIC infrastructure (not eth-specific) |

**Key facts:**
- Default env: `ethaddr=00:02:f7:ef:00:02`, `ipaddr=192.168.1.1`, `serverip=192.168.1.100`, `netmask=255.255.255.0` (and an alternate `ethaddr=00:41:71:00:00:50` recipe at file offset 0x51713).
- Driver registers ONE u-boot eth device (`eth_register`-style); MAC base in eth_device struct is `0x47f4af88` (post-relocation).
- Buffer pools live in DRAM: TM packet pool @ `0x41000000` (BMU slots, 0x800 bytes each, 2048 slots), TX descriptors @ `0x41800000`, RX descriptors @ `0x41a00000`, extra descriptor block @ `0x41b00000` + `0x41c00000`.

---

## Function index — U-Boot eth call graph

```
[boot]
 └── FUN_40e21050  "early_board_init"
      ├── FUN_40e40454  MDIO controller init
      │    ├── FUN_40e40094  configure MDIO @ 0x9a101000+0x14 (reset bits 14,15; enable bit 12)
      │    └── ... (helper alloc)
      ├── FUN_40e50998  ETH device-register (malloc 0x40, fill init/send/recv/halt vtable, copy MAC)
      │    └── strlen + linked-list insert
      ├── FUN_40e4fc7c  chip-clock + SERDES sequence
      │    ├── FUN_40e4fa08(0)  TOPCRM[0x94000050] &= 0x7fffffff; PLL setup via 40e4f580/40e4f700
      │    ├── TOPCRM[0x94000008] &= 0xffffffcf  (clear bits 4,5)
      │    ├── TOPCRM[0x94000008] |= 0x20         (set bit 5)
      │    ├── FUN_40e4fa9c            SERDES write sequence @ 0x9fe00000 (24 words)
      │    ├── TOPCRM[0x94000008] |= 0x10         (set bit 4)
      │    └── SYSCTRL[0x94100010] mux select
      └── FUN_40e40844  TOPCRM[0x9400004c] clear + write magic 0x1381b to 0x9a100004
                         (this is the MDIO/PHY pre-config that prints "addr 0x9400004c before/after")

[eth_init  (vtable callback: FUN_40e50440  @ 0x47f2fc40)]
 ├── FUN_40e4fe04                      eth init top-level (one-shot, guarded by static flag)
 │    ├── FUN_40e4fdcc(0xffffffff)    global per-port reset (clear all bits in 0x92000008, sleep 10, write 0xffffffff)
 │    ├── FUN_40e4fda4                main bring-up
 │    │    ├── FUN_40e50384            TM+BMU+NPP init
 │    │    │    ├── FUN_40e501f8       BMU/HASH table loader: 400+0x180+0x180 cmds via FUN_40e50060
 │    │    │    │    └── FUN_40e50060  TM[0x92344000] command-queue submit
 │    │    │    ├── FUN_40e50348       NPP descriptor base @ 0x92350000+0x50/0x60/0x3c (= 0x41b00000)
 │    │    │    │    └── FUN_40e502cc  NPP[0x92350000] mask + bring-up (with arg 1: pattern 0x2f0000)
 │    │    │    ├── FUN_40e4fe5c       BIG TM init:
 │    │    │    │    ├── TM[0x92348000][0] = 0
 │    │    │    │    ├── TM[0x92348000][1] = TM[2] = 0x0104c040
 │    │    │    │    ├── TM[0x92348000][0x16] = 0x3f
 │    │    │    │    ├── TM[0x92348000][0x17] = 0xf
 │    │    │    │    ├── populate 0x800 entries of byte-swap LUT at 0x417ffffe
 │    │    │    │    ├── populate 0x200 entries of byte-swap LUT at 0x41807ffe
 │    │    │    │    ├── TM[0x92340000][0xf4] = 0x41000000  (BMU base #1)
 │    │    │    │    ├── TM[0x92340000][0xf8] = 0x41400000  (BMU base #2)
 │    │    │    │    ├── TM[0x92340000][0xe8] = 0x41800000  (TX desc base)
 │    │    │    │    ├── TM[0x92340000][0xec] = 0x41808000  (TX desc end)
 │    │    │    │    ├── TM[0x92340000][0xfc] = 0x08000800  (TX desc count + size)
 │    │    │    │    ├── TM[0x92348000][0x12] = 0x8000000
 │    │    │    │    ├── TM[0x92348000][0x13] = 0x2000000
 │    │    │    │    └── TM[0x92348000][5]   = 0
 │    │    │    ├── FUN_40e4ff74       TM[0x92348000][0] = 1  (ENABLE TM)
 │    │    │    ├── TM[0x92340000][0xf0] = 0x41a00000  (RX desc base)
 │    │    │    ├── TM[0x92340000][4]    = 0x10        (RX enable bit?)
 │    │    │    ├── FUN_40e50978       chip MAC-table broadcast addr fill (FUN_40e4fd24 writes 0x923a0078/+0x7c x4) + FUN_40e5092c (descriptor table init w/ phys 0x41c00000)
 │    │    │    └── FUN_40e50a4c       SF/ACL[0x9234c000][4] = 0
 │    │    ├── FUN_40e50b0c            switch fabric init (PP block)
 │    │    │    ├── FUN_40e50b34       PP[0x92380000] = 2; mdelay(1)
 │    │    │    ├── FUN_40e50a9c       PP[0x92388000] FULL block init: writes to +4,+0x340,+0x344,+0x380,+0x63c,+0x1c0,+0x1c4,+0x188,+0x2c0,+0x300,+0x304 (vlan/flood/forwarding masks)
 │    │    │    ├── FUN_40e50a60       PP[0x9238c000] write to +0x80=0x309a, +0x88=0, +0xcc=1
 │    │    │    └── SF_ACL[0x923a0000] +0x10=0, +0x14=0
 │    │    ├── FUN_40e50f20            misc-block reset:
 │    │    │    ├── MISC[0x921c0000] +8 = 0xffffffff; mdelay(1); +0xc = 0xffffffff; mdelay(1)
 │    │    │    ├── FUN_40e50b84       priority/queue init: 8 loop calls + writes to MISC[0x921d4000] {+0, +1*4=0x8800, +0x40, +0x44, +0x1c0}
 │    │    │    ├── FUN_40e50ed4       4-port queue setup + FUN_40e50eb0
 │    │    │    ├── FUN_40e50f0c       MISC[0x921cc000][0] = 0x11
 │    │    │    └── MISC[0x921c0000] +0x48 = 0
 │    │    └── SF_ACL[0x923a0000] +0xe0 = 0x11
 │    ├── MISC[0x92040000] +0x18 &= ~3
 │    ├── MISC[0x92040000] +0x1c = 0xf
 │    └── mdelay(20)
 │
 ├── FUN_40e50c40(0)                   bring up port 0 (LAN1)
 ├── FUN_40e50c40(1)                   bring up port 1 (LAN2)
 ├── FUN_40e50c40(2)                   bring up port 2 (LAN3)
 └── FUN_40e50c40(3)                   bring up port 3 (LAN4)
       FUN_40e50c40(N):
         a. PHY read ZTE-vendor regs 0x1a (autoneg status) and 0x1e
         b. if link bit set (0x40):
              determine speed via masks 0x380 → 10/100/1000 lookup
              determine duplex via masks 5/4/1 → full/half
         c. FUN_40e4fdcc(1 << (N+6))   pulse port reset
         d. MAC[N][0]      = 0x00bbe003   (control init)
         e. MAC[N][2]      = 0x80000001   (enable bit + 1)
         f. MAC[N][0xe0]   = 0x00011200   (?)
         g. MAC[N][0xc20]  = 0x32         (?)
         h. MAC[N][0xc50]  = 0xa8         (?)
         i. MAC[N][1]      = 0xfffe       (?)
         j. MAC[N][0x70]   = 0x00300002   (rate / IFG?)
         k. MAC[N][0xb4]   = 0x4000
         l. MAC[N][0xb00]  = 0x0010ff11   (flow-ctrl?)
         m. FUN_40e50bd4(N, speed_idx, duplex_idx) → adjusts MAC[N][0] bits 13/14/15
         n. busy-wait on MISC[0x921d9068] bit (port-link-up) up to 5×1ms;
            then set MISC[0x921d9068] |= (1<<N)  (mark up)
         o. FUN_40e50c20(N) → MAC[N][0] |= 3  (TX+RX enable)

[eth_send  (vtable callback: FUN_40e50854  @ 0x47f30054)]
 ├── check free-slot counter in driver struct
 └── FUN_40e50730                      build packet:
       ├── FUN_40e4ff88                BMU alloc — read TM[0x92348000][0xc], TM[0x92348000][0x14]
       ├── packet copy to RAM @ (slot*0x800 + 0x41000010)
       ├── fill 16-byte descriptor (len, slot, prio)
       ├── flush cache via FUN_40e215f0 (dcache range flush)
       └── FUN_40e502f0                TM submit — TM[0x92344000][0x1fc] = ... and "tx kick"

[eth_recv  (vtable callback: FUN_40e50510  @ 0x47f2fd10)]
 └── for prio = 7 → 0:
       for each entry in RX queue:
         ├── read 16B descriptor at TM RX ring (base + prio*8 + idx*0x10)
         ├── compute packet addr = slot * 0x800 + 0x41000010
         ├── invalidate dcache range
         ├── FUN_40e4c3f4(buf, len)    deliver to U-Boot NetReceive
         ├── func_0x40e50170(prio,0,1,0) — return slot to queue
         └── func_0x40e4fff8(slot)     free BMU slot

[eth_halt  (vtable callback: FUN_40e50470  @ 0x47f2fc70)]
 ├── mdelay(100)
 ├── FUN_40e50e90(0)   MAC[0][0] &= ~1  (disable TX bit)
 ├── FUN_40e50e90(1)   MAC[1][0] &= ~1
 ├── FUN_40e50e90(2)   MAC[2][0] &= ~1
 └── FUN_40e50e90(3)   MAC[3][0] &= ~1

[bootm path — no eth interaction]
   bootm uses FUN_40e37aac (image relocate) → FUN_40e3e72c / FUN_40e3e988
   (set_kernel_cmdline / start_kernel). Neither path calls eth_halt or
   touches eth registers.
```

---

## Init sequence — chronological order

These writes occur at U-Boot boot time, in this order:

### Phase A — `FUN_40e21050` (board_init, very early)

1. `FUN_40e40454` — MDIO controller setup
   - `MDIO[0x9a101000][0x14] &= 0xffffbfff` (clear bit 14)
   - `MDIO[0x9a101000][0x14] &= 0xffff7fff` (clear bit 15)
   - `MDIO[0x9a101000][0x10] = 0`
   - `MDIO[0x9a101000][0x14] |= 0x1000` (enable bit 12)
   - `MDIO[0x9a101000][0x14] &= 0xffffdfff`
   - `MDIO[0x9a101000][0xc] = 0`

2. `FUN_40e50998` — register eth device in U-Boot core
   - allocates 64 bytes; fills `dev->init = 0x47f2fc40 (FUN_40e50440)`, `dev->halt = 0x47f2fc70 (FUN_40e50470)`, `dev->send = 0x47f30054 (FUN_40e50854)`, `dev->recv = 0x47f2fd10 (FUN_40e50510)`; copies MAC from env

3. `FUN_40e4fc7c(0)` — chip clock + SERDES bring-up
   - `TOPCRM[0x94000050] &= 0x7fffffff`
   - SERDES PLL via `FUN_40e4f700(TOPCRM[0x94000050], 1, 0x5d, 0x004fdf3b, 5, 3)` (gpon path)
   - mdelay(50)
   - `TOPCRM[0x94000008] &= 0xffffffcf` (clear bits 4,5)
   - udelay(100)
   - `TOPCRM[0x94000008] |= 0x20`
   - udelay(100)
   - `FUN_40e4fa9c` — SERDES 24-word write at `0x9fe00000` (PMA, clock, equalizer params)
   - `TOPCRM[0x94000008] |= 0x10`
   - `SYSCTRL[0x94100010] &= 0xfffff7ff; |= mux-bits from 0x9a107008`

4. `FUN_40e40844` — toggle bit 9 of `TOPCRM[0x9400004c]`, then `MDIO[0x9a100004] = 0x1381b`

### Phase B — `eth_init` (FUN_40e50440 via vtable, deferred until first `tftp`/`ping`)

5. `FUN_40e4fdcc(0xffffffff)` — global per-port reset
   - `_DAT_92000008 = 0`
   - mdelay(10)
   - `_DAT_92000008 = 0xffffffff`

6. `FUN_40e50384` — TM/PP/NPP init (see Function index above)

7. `FUN_40e50b0c` — PP block (`0x92380000`+) init (vlan, forwarding, hashing)

8. `FUN_40e50f20` — MISC block reset + queue priority + final config

9. `SF_ACL[0x923a0000][0xe0] = 0x11`

10. `MISC[0x92040000][0x18] &= ~3; +0x1c = 0xf`; mdelay(20)

11. For each port N=0..3: `FUN_40e50c40(N)`
    - PHY autoneg state read via MDIO addr from runtime table
    - port reset via `FUN_40e4fdcc(1<<(N+6))`
    - MAC[N] register config (control, FIFO, IFG, flow-ctrl)
    - MAC[N][0] |= 3 (enable TX+RX)

---

## Teardown — what happens at `bootm`

U-Boot `bootm` invokes `FUN_40e37aac` (image relocate + verify) and
then `FUN_40e3e72c`/`FUN_40e3e988` (set_kernel_cmdline + start_kernel).
Neither path calls `eth_halt` nor touches any peripheral in
`0x92xxxxxx`, `0x9a10xxxx`, `0x9fe00000`, or `0x94000000` (clock
gates).

`eth_halt` (FUN_40e50470) is only invoked through the U-Boot core
`eth_halt()` API, which is called at the end of `tftp`/`ping`
commands. The effect of `eth_halt` is minimal:

- 100 ms delay
- `MAC[0..3][0] &= ~1` (clear bit 0 of MAC control = disable bit)

That is the ONLY teardown. The following remain **enabled** at kernel
handoff regardless of whether `tftp` ran first:

- TOPCRM clock bits 4,5 of `0x94000008` (eth subsystem clocks ON)
- SERDES @ `0x9fe00000` (24 words still written)
- SYSCTRL `0x94100010` mux still set
- All the MISC-block initial writes (queue setup, hash tables)
- BMU pool at `0x41000000` populated in RAM (kernel inherits with
  un-cleared descriptors)
- The chip's per-port reset register `0x92000008 = 0xffffffff`
  (out of reset)
- The PP/NPP/SF blocks configured for full-switch operation

### Difference between TFTP-boot and NAND-boot

- **TFTP-boot path (operator types `tftp` then `bootm` from prompt)**:
  Phase A always runs. Phase B (eth_init) runs the first time the user
  types a network command. After `tftp` succeeds, `eth_halt` clears
  MAC enable bits, but all other state (TM, PP, NPP, SF, MISC, BMU
  pool in DRAM) **persists** into the kernel.
- **NAND-boot path (autoboot from saved bootcmd)**:
  Phase A still runs (board_init is unconditional). Phase B does
  **not** run — the autoboot bootcmd is `bootm 0x42000100` with no
  preceding tftp/ping. So eth_init's TM/BMU/PP/NPP/MISC writes
  **never happen**; only the MDIO controller init, SERDES, and
  TOPCRM clock-gate sequence from Phase A persist.

This is **critical**: in NAND-boot, U-Boot leaves the eth-chip's
register state mostly virgin (only Phase A items applied). The stock
kernel's `plat-zxylzb_9128S` + `tm.ko` modules then perform a full
`pon_reset` and re-init from scratch. So stock kernel does NOT depend
on U-Boot's Phase B eth_init.

---

## Compared to mainline driver port

Mainline `zx279128-eth.c` was found to leave `TM[0x10068]` high16
stuck at 7, `tm_irq_count=0`, and `bmu_alloc` returning "pool empty"
(see `tasks/00.01.eth-driver/findings/iter20_*` and
`stock_tx_path_kotrace_2026-05-25.md`). Key comparisons:

| U-Boot does | Mainline does | Stock kmods do |
|---|---|---|
| TM[0x92348000] BMU init: writes [0]=0, [1]=[2]=0x0104c040, [0x16]=0x3f, [0x17]=0xf, [0x12]=0x8000000, [0x13]=0x2000000 | partial — does not write the full sequence; `tm_irq_count=0` is consistent with [0x12]/[0x13] IRQ masks never set | ✅ (via tm.ko `tm_initial` → `fpga_write_reg`) |
| `TM[0x92340000][0xe8..0xfc]` populated with TX/RX desc base addresses (`0x41000000`, `0x41400000`, `0x41800000`, `0x41a00000`, `0x41c00000`) in 256 MiB DRAM region | mainline uses kernel-allocated DMA buffers; addresses differ | ✅ (stock allocates equivalent BMU pool via plat reservation) |
| `TM[0x92344000]` cmd-queue: 400 + 0x180 + 0x180 BMU population writes | mainline does not pre-populate BMU pool with descriptors | ✅ (stock does the equivalent) |
| `FUN_40e4fdcc(0xffffffff)` global eth-reset pulse on `_DAT_92000008` | mainline does not toggle `0x92000008` (this address is not in `mainline_eth/zx279128-eth.c`) | ✅ (stock `plat-zxylzb` has `pon_reset(0xffffffff)`) |
| Per-port reset via `_DAT_92000008 = 1<<(N+6)` pulse in link-up handler | mainline `zte_gephy_config_init` does not pulse this | ✅ |
| PP/NPP at `0x92380000 / 0x92388000 / 0x9238c000` configured for forwarding | mainline only configures the GeMAC; switch fabric is untouched | ✅ (stock switch.ko does this) |
| MISC `0x921c0000 / 0x921cc000 / 0x921d4000` queue priority + 8-step prio loop + `0x921cc000[0]=0x11` | mainline absent | ✅ |
| SF_ACL `0x923a0000[0xe0]=0x11` final enable | mainline absent | ✅ |

**However, the comparison is misleading** — these "U-Boot does ✓, stock
does ✓, mainline does ✗" rows do NOT mean mainline can rely on U-Boot
to set them. Reasons:

1. U-Boot's Phase B only runs in the `tftp+bootm` path, not autoboot.
2. Even after `eth_halt`, the stock kernel always does its own
   `pon_reset(0xffffffff)` (`plat-zxylzb_9128S` init_module) — which
   wipes everything U-Boot set up.
3. Stock kernel works fine from cold-boot-no-tftp, proving the kernel
   does not require U-Boot's eth state.

The TM init sequence U-Boot does is informative as a **mini reference
implementation** — much simpler than the full stock `tm_initial` — and
useful as a sanity-check baseline of "what does the bare minimum
TM+BMU+MAC config look like to TX/RX a single frame?".

---

## Verdict

**U-Boot is NOT a factor in the mainline-vs-stock kernel behavior.**

- U-Boot does NOT call `eth_halt` or any eth shutdown at `bootm`. But
  the persistent state it leaves (Phase A clocks + SERDES + MDIO + the
  Phase-B TM/PP/NPP/MISC writes, if `tftp` ran) is **wiped by the
  stock kernel's `pon_reset(0xffffffff)`** during `plat-zxylzb_9128S
  init_module`. So whatever U-Boot left, stock zeros it; mainline
  ought to do the same.
- In the autoboot/NAND-boot case (no tftp), U-Boot's Phase B doesn't
  even run, yet stock kernel works fine. This is direct empirical
  proof the kernel does not depend on U-Boot's eth_init.
- Mainline's TX/RX failures (`tm_irq_count=0`, BMU empty,
  `TM[0x10068]` stuck) reflect the kernel driver's **own missing
  init** of the TM/BMU/PP/NPP/SF blocks. The stock kernel sets these
  up itself via `tm.ko` (`tm_initial`) and `switch.ko` /
  `plat-zxylzb_9128S` — U-Boot doing or not-doing the same writes is
  irrelevant.

What U-Boot's eth driver DOES provide is a **simpler reference
implementation**. The writes U-Boot makes (this doc + `uboot_eth_decomp/`)
are a clean, minimal recipe for "get a working TX/RX through the chip
fabric without all the stock-kernel SDK abstraction layers". Mainline
could likely use these register sequences directly — particularly:

- The `TM[0x92348000]` setup at `FUN_40e4fe5c` (TX descriptor ring registration)
- The BMU pool populate loop at `FUN_40e501f8` (400 + 0x180 + 0x180 entries → `TM[0x92344000]`)
- The per-port MAC config at `FUN_40e50c40` (only 8 registers per MAC, no SDK)
- The PP block init at `FUN_40e50a9c` (single-shot enable: forwarding mask, VLAN, flood)
- The `SF[0x923a0000][0xe0] = 0x11` final enable

These match the operations stock does via the SDK helpers, just
without the SDK indirection. The address+value tables here are the
"ground truth" extracted from a working bare-metal eth driver.
