# Driver code-gen demo — `tm_port_isolate_set` end-to-end

Worked example showing how to combine
[`captures/kotrace_p3c_full_args.txt`](captures/kotrace_p3c_full_args.txt)
+ [`linux-v6.6/drivers/net/ethernet/zte/zx-fpga-reg-tables.h`](../../../linux-v6.6/drivers/net/ethernet/zte/zx-fpga-reg-tables.h)
+ one objdump session to mechanically generate one of the missing
driver pieces.

---

## Inputs

### From runtime trace (Phase 3c)

Marker `Y` (tm_port_isolate_set) appears 8 times with args:

```
port=0  mask=0xffffff01
port=1  mask=0xffffff02
port=2  mask=0xffffff04
port=3  mask=0xffffff08    (inferred from pattern)
port=4  mask=0xffffff10
port=5  mask=0xffffff20    (?)
port=6  mask=0xffffff40    (?)
port=7  mask=0xffffff80    (?)
```

(Each port masks itself out of the per-port destination set; standard ONT port-isolation.)

### From static disasm (`objdump --disassemble=tm_port_isolate_set`)

```
push {r3, lr}
mov  r2, r0           ; r2 = port (saved)
mov  r3, r1           ; r3 = mask (saved)
cmp  r0, #7
ldrls pc, [pc, r0,lsl#2]   ; jump table by port
b error_out                ; default: bail
.word 0x36a70  ; port 0  → loads r1=#0
.word 0x36a78  ; port 1  → loads r1=#1
.word 0x36a08  ; port 2  → loads r1=#2 (wait — see below)
.word 0x36a48  ; port 3  → loads r1=#3
.word 0x36a50  ; port 4  → loads r1=#4
.word 0x36a58  ; port 5  → loads r1=#5
.word 0x36a60  ; port 6  → loads r1=#6
.word 0x36a68  ; port 7  → loads r1=#7

common:
  mvn  r3, r3                   ; ~mask
  ubfx r2, r3, #5, #1           ; bit 5
  lsl  r0, r3, #1
  and  r3, r3, #0xc0
  and  r0, r0, #0x3e
  orr  r0, r2, r0
  orr  r0, r0, r3
  bl   sbrg_set_isolate_pt_cfg(r0=transformed_mask, r1=port_via_table)
  ...
```

So tm_port_isolate_set boils down to:
```c
sbrg_set_isolate_pt_cfg(transform_mask(mask), port);
```

### From static disasm of `sbrg_set_isolate_pt_cfg`

```
push {r4, r5, r6, lr}
mov  r5, r0   ; save transformed_mask
mov  r4, r1   ; save port
cmp  r0, #0xff
cmpls r1, #7
bls valid
... fail path ...
valid:
  ldr r3, [global];  cmp r3, #6;  bhi alt_path
  mov r0, #0x39        ; reg_id = 57
  mov r1, r5           ; value = transformed_mask
  mov r2, r4           ; sub_idx = port
  movw/movt r3, =sbragRegTable
  bl tmOnuRegWrite     ; → does fpga_write_reg(table[57].base + table[57].stride*port,
                       ;                       (current_val & ~mask_bits) | (val << shift))
```

### From decoded `sbragRegTable[57]`

Grep the generated header for reg_id=57:

```c
{ .reg_id =  57, .mode = 3, .base_off = 0x000e21c0, .max_sub_idx = 8, .stride = 0x00000010 },
```

(Hypothetical — needs verification by looking at sbragRegTable's actual entry 57.)

So the actual register write for `tm_port_isolate_set(port, mask)`:

```
addr = (0x000e21c0 + 0x10 * port) * 4   (multiply by 4 — FPGA index → byte off)
     = 0x388700 + 0x40 * port           (byte offset within FPGA window)
     = (in mainline) fpga_base + addr
val = transform_mask(mask)
read_modify_write(addr, val, table[57].mask, table[57].shift)
```

## Mainline driver function

```c
#include "zx-fpga-reg-tables.h"

/* Equivalent of stock tm_port_isolate_set(port, mask).
 * Called 8 times during chip_tm_init, once per port.
 * mask is a bitmap of ports this port is NOT allowed to talk to. */
static int zx_tm_port_isolate_set(struct zx_eth *e, int port, u32 mask)
{
    const struct zx_fpga_reg *r;
    u32 inverted, transformed;

    /* Transform per the stock bit-fiddling we transcribed above */
    inverted = ~mask;
    transformed = ((inverted >> 5) & 1)                 /* bit 5 */
                | ((inverted << 1) & 0x3e)              /* bits 1..5 */
                | ( inverted       & 0xc0);             /* bits 6..7 */

    /* Look up the register descriptor for sbragRegTable[57] */
    if (57 >= ZX_SBRAGREGTABLE_COUNT)
        return -EINVAL;
    r = &zx_sbragregtable[57];
    if (port > r->max_sub_idx)
        return -ERANGE;

    /* Write via the FPGA window */
    zx_fpga_write(e->fpga_base, r->base_off + r->stride * port, transformed);
    return 0;
}
```

And in our driver's chip_tm_init replay:

```c
/* Per Phase 3c trace — sw_init_switch → ... → tm_port_isolate_set ×8 */
static const u32 isolate_masks[8] = {
    0xffffff01, 0xffffff02, 0xffffff04, 0xffffff08,
    0xffffff10, 0xffffff20, 0xffffff40, 0xffffff80,
};
for (port = 0; port < 8; port++)
    zx_tm_port_isolate_set(e, port, isolate_masks[port]);
```

## Generalising

Repeat this exercise for each of the 41+ `sbrg_*`, `tm_port_*`, `tm_*`, `adm_*`, `cla_*` inner functions:

1. From kotrace_p3c trace: `(marker, count, distinct arg patterns)`
2. From objdump: identify the few-line transformation it does + the
   `tmOnuRegWrite(REG_ID, ..., TABLE)` call
3. From `zx-fpga-reg-tables.h`: look up `(reg_id, base_off, stride, mode)`
4. Write the C equivalent — 10-30 lines per function

~40 functions × ~30 min each = ~20 hours of mechanical work.

Could be largely script-generated: a Python tool that:
- Reads objdump output for a function
- Detects the `mov rX, #imm`/`movw rX, =label` patterns that set the
  4 args of tmOnuRegWrite
- Emits the C equivalent stub

That tool itself = maybe 3-4 hours to write.

## What's NOT yet validated

- Sample reg_id=57 (.base_off, .stride) values are guessed in this doc —
  needs `head -57 sbragRegTable_entries.txt` from the generated header.
- The "transform_mask" bit-fiddling — copied from disasm but not tested
  on hardware.
- mainline ioremap'ing fpga_base = 0x92000000 size 4 MiB — needs DT
  binding addition or hardcode in our driver's probe.

But all of these are testable individually: write the function, build,
RAM-boot kernel, write the register, read it back, compare to stock.
