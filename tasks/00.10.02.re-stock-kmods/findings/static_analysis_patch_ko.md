# patch.ko — static analysis

Reverse engineering of `ext/kmodules_dump/patch.ko`. Vendor kernel module
(GPL, author "baoxiaoyun", description "ZTE patch Module Drivers"). 5112
bytes, ARM EABI5 relocatable, vermagic `4.1.25 SMP mod_unload ARMv7`.

Module purpose: **runtime patch of two stock-kernel functions** —
`__l2c210_op_pa_range` (PL310 L2 cache PA-range op) and
`fixed_pci_read_u32` (vendor PCIe accessor) — both rewritten so that
PCIe reads and L2 cache maintenance share `l2x0_lock` more efficiently
via a chunked release pattern with a "PCIe access coming" doorbell flag.

Patching is done by overwriting the first 20 bytes of each target with
a fixed 5-instruction trampoline (a copy of the module-local
`hack_function0` skeleton with the replacement address inlined at
offset +16). After the in-memory poke, the module cleans L1 D-cache
over the patched range and invalidates the entire I-cache so the new
code is fetched.

Source artefacts: `objdump -dr ext/kmodules_dump/patch.ko`,
`objdump -t`, raw section dumps. Vmlinux cross-refs from
`tasks/00.10.01.re-vmlinux/vmlinux.elf`.

---

## Legend

- **HW writes**: register address + value the function pokes (mostly CP15)
- **Sub-calls**: nested function invocations (descended in same doc)
- **In mainline?**: ✓ replicated / ⚠ partial / ✗ missing / N/A
- **Severity if missing**: 🔴 likely path-breaking · 🟡 unclear · 🟢 informational

---

## Module layout

| Section | Size | Symbols |
|---|---|---|
| `.text`            | 0x268 | `patch_function` 0x000, `patch_function_name` 0x054, `patch_pci_read_u32` 0x07c, `patch_op_pa_range` 0x0bc, `l2x0_patch` 0x150, `invalid_l1_inst` 0x1f0, `invalid_icache_all` 0x220, `clean_l1_dcache` 0x22c, `hack_function0` 0x250 |
| `.init.text`       | 0x14  | `init_module` |
| `.exit.text`       | 0xc   | `cleanup_module` |
| `.data`            | 4     | `l2_lock_size` = `0x00000800` (2048 — chunk size in bytes) |
| `.bss`             | 8     | `pci_read_coming` (u32) @+0, `l2_lock` (raw_spinlock_t *) @+4 |
| `.rodata.str1.4`   | 0x5c  | "bug!!!,patch module ,exit\n" @+0, "l2x0_lock" @+0x1c, "__l2c210_op_pa_range" @+0x28, "patch module%d failed %d\n" @+0x40 |

Module-load init notifier wiring (`__this_module` / `init_module` /
`cleanup_module`) is standard — no .ctors or other glue.

External symbols imported from vmlinux (resolved at insmod):

- `printk`
- `_raw_spin_lock_irqsave`, `_raw_spin_unlock_irqrestore`
- `fixed_pci_read_u32` — exported in stock vmlinux at `0xc0014dec`
- `get_ksyms_address` — vendor wrapper around `kallsyms_lookup_name`
- `__aeabi_unwind_cpp_pr0`, `__aeabi_unwind_cpp_pr1` — unwind ABI helpers

---

## [fn-00] `init_module` @ patch.ko:.init.text+0x0 — module entry

What it does: tiny wrapper. Calls `l2x0_patch` to install both trampolines,
then `invalid_icache_all` to broadcast-invalidate every CPU's I-cache so
the just-overwritten kernel functions get re-fetched on the next call.
Returns 0 unconditionally (errors are absorbed by `l2x0_patch`, which
prints and returns 0 itself).

```
push {r3, lr}
bl   l2x0_patch
bl   invalid_icache_all
mov  r0, #0
pop  {r3, pc}
```

HW writes: **none directly** (delegated).

Sub-calls:
1. `l2x0_patch()` — [fn-04]
2. `invalid_icache_all()` — [fn-07]

In mainline? **N/A**. The whole module exists to compensate for a stock
vmlinux modification that mainline never received (see [fn-04]).

---

## [fn-01] `patch_function(void *target, void *replacement)` @ patch.ko:.text+0x000 — install trampoline

What it does: rewrites the first 20 bytes of `target` with a 5-instruction
ARM trampoline that calls `replacement` and returns to the caller. The
template is the first 16 bytes of the module-local `hack_function0`
function copied byte-for-byte into `target[0..15]`, with the replacement
address stored as a literal at `target[16..19]`. Before copying, L1
I-cache lines over the target range are invalidated (defensive
prefetch-drop); after copying, L1 D-cache lines are cleaned to PoC so
the I-fetch sees the new bytes. Caller (`l2x0_patch`) is expected to
follow up with a global `invalid_icache_all`.

Argument convention is `r0 = target`, `r1 = replacement`. Returns 0.

The 20-byte trampoline planted at the target:

```
+0x00: push {r4, lr}
+0x04: ldr  r4, [pc, #4]    ; loads target+0x10 = replacement addr
+0x08: blx  r4              ; tail-effective call; r0..r3 args pass through
+0x0c: pop  {r4, pc}
+0x10: .word replacement    ; written by `str r5, [r4, #16]` before the copy
```

Note `target[+0x14]` and beyond are untouched — only 20 bytes are
overwritten. Anything in the original function after byte 20 dies as
dead code (unreachable, since the trampoline returns from the `pop`).

Disassembly:
```
push   {r3,r4,r5,lr}
mov    r5, r1                 ; r5 = replacement
mov    r1, #20
mov    r4, r0                 ; r4 = target
bl     invalid_l1_inst        ; (target, target+20) — drop I-cache lines
movw/movt r3, =hack_function0 ; r3 = &template
mov    r0, r4
ldr    lr, [r3]               ; lr = template[0]
mov    r1, #20
ldr    ip, [r3, #4]           ; ip = template[1]
ldr    r2, [r3, #8]           ; r2 = template[2]
ldr    r3, [r3, #12]          ; r3 = template[3]
str    r5, [r4, #16]          ; target[+16] = replacement
str    lr, [r4]               ; target[+0]  = template word 0
str    ip, [r4, #4]           ; target[+4]  = template word 1
str    r2, [r4, #8]           ; target[+8]  = template word 2
str    r3, [r4, #12]          ; target[+12] = template word 3
bl     clean_l1_dcache        ; (target, target+20) — push writes to PoC
mov    r0, #0
pop    {r3,r4,r5,pc}
```

Subtle: the 5-instruction trampoline is constructed on the fly from
`hack_function0`'s preamble (the literal `nop`s at +0x10/+0x14 of that
symbol are NOT what becomes the address word — those nops live only in
the source module and are never copied; the address word is written
explicitly by `str r5, [r4, #16]`).

HW writes (CP15, indirect via sub-calls): ICIMVAU + BPIALLIS + DCCMVAC
over `[target, target+20)`. No MMIO.

Sub-calls:
- `invalid_l1_inst(target, 20)` — [fn-08]
- `clean_l1_dcache(target, 20)` — [fn-09]

In mainline? **✗ missing**. Severity 🟢 — mainline has no need for it
because mainline never installed the per-line `l2x0_lock` regression
this module patches around (see [fn-05]).

---

## [fn-02] `patch_function_name(const char *target_name, void *replacement)` @ patch.ko:.text+0x054 — symbol-resolving variant

What it does: convenience wrapper. Resolves `target_name` via
`get_ksyms_address` (vendor kallsyms wrapper). If resolution succeeds,
tail-calls `patch_function(addr, replacement)`. Otherwise returns
`-1` (`mvn r0, #0`).

```
push {r4, lr}
mov  r4, r1               ; r4 = replacement
bl   get_ksyms_address    ; r0 = name -> addr
cmp  r0, #0
beq  .fail
mov  r1, r4
pop  {r4, lr}
b    patch_function       ; tail call
.fail:
mvn  r0, #0               ; return -1
pop  {r4, pc}
```

HW writes: none.

Sub-calls:
- `get_ksyms_address` (extern, vendor wrapper for `kallsyms_lookup_name`)
- `patch_function` — [fn-01]

In mainline? **N/A** (helper that exists only because the module exists).

Note: this symbol is **defined but never used** by any other function in
this module. `l2x0_patch` resolves names manually via `get_ksyms_address`
inline rather than going through `patch_function_name`. Likely left over
from a refactor or kept as a publicly-callable helper for other vendor
modules to hook the same way.

---

## [fn-03] `patch_pci_read_u32(<ignored>, u32 *ptr)` @ patch.ko:.text+0x07c — replacement body for `fixed_pci_read_u32`

What it does: replacement for the stock kernel's `fixed_pci_read_u32`
accessor. Reads one u32 from `*ptr` under `l2x0_lock`, plus a doorbell
write — sets `pci_read_coming = 1` *before* taking the lock, clears it
after the read. The doorbell is observed by `patch_op_pa_range` (which
also holds `l2x0_lock` for long bursts of L2 maintenance) and causes
that function to drop the lock mid-burst so this read can make progress.

The `r0` argument is loaded but never used as a value — the real input
is `r1` (the pointer to the MMIO/PCI config word).

```
push {r4..r6, lr}
movw/movt r4, =.LANCHOR0     ; r4 = &pci_read_coming  (also &lock at +4)
mov  r3, #1
mov  r5, r1                  ; save ptr
str  r3, [r4]                ; pci_read_coming = 1   ← doorbell SET
ldr  r0, [r4, #4]            ; r0 = l2_lock pointer
bl   _raw_spin_lock_irqsave  ; returns flags in r0
mov  r1, r0                  ; r1 = flags (for the unlock below)
ldr  r6, [r5]                ; *** the actual u32 read ***
ldr  r0, [r4, #4]            ; r0 = l2_lock
mov  r3, #0
str  r3, [r4]                ; pci_read_coming = 0   ← doorbell CLEAR
bl   _raw_spin_unlock_irqrestore
mov  r0, r6
pop  {r4..r6, pc}
```

Compared to the stock `fixed_pci_read_u32` in vmlinux at `0xc0014dec`
(same logical shape — push, save lock-ptr to r5, take lock, read u32,
release lock, return) — the **only** behavioural difference is the
doorbell flag. The stock version doesn't set/clear `pci_read_coming`,
so the long-burst L2 op (the un-patched stock `__l2c210_op_pa_range`,
which already releases the lock between every line) doesn't need to
check it.

HW writes: **none directly**. The actual MMIO read is delegated to the
caller-supplied pointer.

Sub-calls:
- `_raw_spin_lock_irqsave`
- `_raw_spin_unlock_irqrestore`

In mainline? **✗ missing**. Severity 🟢 — mainline does not have a
`fixed_pci_read_u32` accessor at all; its PCIe drivers use `readl`
directly with no L2 cross-locking, because mainline `__l2c210_op_pa_range`
also takes no lock (the stock kernel's per-line-locked variant is what
created the need for cross-coordination).

---

## [fn-04] `patch_op_pa_range(void __iomem *reg, unsigned long start, unsigned long end)` @ patch.ko:.text+0x0bc — replacement body for `__l2c210_op_pa_range`

What it does: replacement for the stock kernel's `__l2c210_op_pa_range`,
which is the inner per-PA-line PL310 cache-op driver used by
`l2c210_inv_range` / `l2c210_clean_range` / `l2c210_flush_range`.
Iterates `start..end` in steps of 32 (cache line), writing each line
PA to `*reg` (which the caller selected to be one of the L2C-310
`*_LINE_PA` registers). The function holds `l2x0_lock` across chunks
of up to 2048 bytes (= 64 cache lines), then releases & reacquires
the lock at every chunk boundary, AND additionally releases the lock
mid-chunk whenever `pci_read_coming` is observed non-zero.

Chunk size is read from `.data:l2_lock_size` (initialised to 0x800);
nothing in this module rewrites it, but it being in `.data` rather than
`.rodata` means a future patch (or stock module-param mechanism — though
this module exports no parameters) could tune it at runtime.

Argument convention is the standard ARM AAPCS: `r0=reg, r1=start, r2=end`.
Returns void via the spin-unlock-irqrestore tail call.

```
push {r4..r8, lr}
movw/movt r6, =.LANCHOR0       ; r6 = &pci_read_coming
mov  r5, r0                    ; r5 = reg
ldr  r0, [r6, #4]              ; r0 = l2_lock
mov  r4, r1                    ; r4 = start
mov  r8, r2                    ; r8 = end
bl   _raw_spin_lock_irqsave    ; returns flags in r0
cmp  r4, r8
mov  r1, r0                    ; r1 = flags
bcs  .L_unlock                 ; start >= end → nothing to do

.L_chunk:
movw/movt r7, =.LANCHOR1       ; r7 = &l2_lock_size
ldr  ip, [r7]                  ; ip = chunk_size (0x800)
rsb  r3, r4, r8                ; r3 = end - start  (remaining)
cmp  r3, ip
addls ip, r4, r3               ; if remaining <= chunk_size: blk_end = end
addhi ip, r4, ip               ; else:                       blk_end = start + 0x800
b    .L_check

.L_line:
str  r4, [r5]                  ; writel(start, reg)  — issue one cache-line op
ldr  r3, [r6]                  ; r3 = pci_read_coming
add  r4, r4, #32               ; start += CACHE_LINE_SIZE
cmp  r3, #0
bne  .L_release_reacquire      ; doorbell: yield lock immediately
.L_check:
cmp  ip, r4
bhi  .L_line                   ; loop while start < blk_end

cmp  r4, r8
bcc  .L_release_reacquire      ; chunk done; if more remaining, yield+reloop

.L_unlock:
ldr  r0, [r6, #4]              ; r0 = l2_lock
pop  {r4..r8, lr}
b    _raw_spin_unlock_irqrestore   ; tail-call, returns via lr

.L_release_reacquire:
ldr  r0, [r6, #4]              ; r0 = l2_lock
bl   _raw_spin_unlock_irqrestore
ldr  r0, [r6, #4]              ; r0 = l2_lock
bl   _raw_spin_lock_irqsave
mov  r1, r0                    ; new flags
b    .L_chunk                  ; recompute chunk size and continue
```

The doorbell loop is the heart of the patch. `pci_read_coming` is set
by `patch_pci_read_u32` *before* it spins on `l2x0_lock`, so the
hand-off goes:
1. CPU A is mid-burst inside `patch_op_pa_range`, holding `l2x0_lock`.
2. CPU B enters `patch_pci_read_u32`, sets `pci_read_coming = 1` (no
   lock yet — this is a non-atomic store, but x86-style store-store
   ordering on ARM after a relaxed write is sufficient because B will
   then issue `_raw_spin_lock_irqsave` which carries an `smp_mb__before_spinlock`).
3. CPU B spins on the lock.
4. CPU A finishes its current line, observes `pci_read_coming != 0`,
   releases the lock.
5. CPU B grabs the lock, does its single u32 MMIO read, clears the
   flag, releases.
6. CPU A re-grabs, recomputes its chunk (since `start` advanced and
   `end` hasn't changed), continues.

So `pci_read_coming` is **not** a mutex (the lock is) — it's a
cooperation flag that lets a long L2 burst voluntarily yield mid-burst
to an urgent PCIe accessor. Without this, the stock-kernel
`__l2c210_op_pa_range` releases the lock after every single cache line
to give PCIe code a chance (62 release/reacquire pairs per 2 KiB),
which is the perf regression this module fixes.

Upstream Linux `__l2c210_op_pa_range` (both v4.1 and v6.6, `arch/arm/mm/cache-l2x0.c:178`):
```c
static void __l2c210_op_pa_range(void __iomem *reg, unsigned long start,
                                 unsigned long end) {
    while (start < end) {
        writel_relaxed(start, reg);
        start += CACHE_LINE_SIZE;
    }
}
```
— no lock at all. Mainline relies on the caller (`l2c210_inv_range`,
etc.) to hold `l2x0_lock` only around the unaligned head/tail writes
to `CLEAN_INV_LINE_PA`, NOT during the bulk loop. Mainline PCIe drivers
do not coordinate with the L2 controller because there's no observed
race on the platforms mainline supports.

Stock ZTE vmlinux `__l2c210_op_pa_range` (the function this module
overwrites) at `c0014cc0`:
```
push  {r4..r6, lr}
mov   r4, start ; r6 = end ; r5 = reg
.loop:
ldr   r0, =l2x0_lock
bl    _raw_spin_lock_irqsave
str   r4, [r5]            ; one cache line
ldr   r0, =l2x0_lock
add   r4, r4, #32
bl    _raw_spin_unlock_irqrestore
cmp   r6, r4
bhi   .loop
pop   {r4..r6, pc}
```
— ZTE added a full lock acquire/release **around every single cache
line**, presumably because they hit a SoC-specific race between L2 PA
ops and concurrent PCIe MMIO during early bring-up. That base-level
lock fixes the race but costs ~60-100x in throughput on long ranges.
This module is the second-round fix that chunks the lock acquires
while keeping the PCIe doorbell as the responsiveness escape valve.

PL310 errata this is *not*: the change has nothing to do with 588369
(clean+invalidate skip step), 727915 (by-way C+I races), 752271
(double-fill), 753970 (post-sync merge), 769419 (store buffer drain),
or any other published ARM errata. The bug appears to be a
**ZXIC-specific SoC integration issue** — likely a deadlock or SLVERR
on the AXI bridge when an L2C-310 PA-op transaction and a PCIe
configuration read overlap. No vendor write-up exists (GPL non-compliance,
see CLAUDE.md).

HW writes: `*reg = start` per cache line (the PL310 `INV_LINE_PA` /
`CLEAN_LINE_PA` / `CLEAN_INV_LINE_PA` register, chosen by caller).

Sub-calls:
- `_raw_spin_lock_irqsave`  (1 + N per yield)
- `_raw_spin_unlock_irqrestore` (1 + N per yield; final one is a tail call)

In mainline? **✗ missing**. Severity 🟡 — mainline does not have the
underlying race that motivated the patch, but if mainline ever exhibits
the same symptom on this SoC, it would need to be re-implemented. The
correct mainline place to add such a fix would be a DT property on the
`arm,pl310-cache` node combined with a new function pointer in
`l2c310_data` (similar to how erratum 588369/727915 are wired in
`__l2c_init`). Currently mainline has no such hook.

---

## [fn-05] `l2x0_patch(void)` @ patch.ko:.text+0x150 — install the two patches

What it does: the orchestrator. Resolves `l2x0_lock` and
`__l2c210_op_pa_range` via kallsyms, stashes the lock pointer into
`l2_lock` (so the other functions can find it), then takes the lock
itself and installs **both** trampolines (over `fixed_pci_read_u32`
and over `__l2c210_op_pa_range`) under it. Releases the lock and
returns 0. On kallsyms failure, prints "patch module%d failed %d\n"
with error code `-1` (l2x0_lock not found) or `-2` (op_pa_range not
found) and returns 0 anyway (best-effort).

```
movw/movt r0, =.LC0+0x1c       ; "l2x0_lock"
push  {r4..r6, lr}
bl    get_ksyms_address
subs  r3, r0, #0
beq   .err_lock                ; (r2 = ~0 = -1)

movw/movt r4, =.LANCHOR0       ; r4 = &pci_read_coming
movw/movt r0, =.LC1            ; "__l2c210_op_pa_range"
str   r3, [r4, #4]             ; l2_lock = ksym("l2x0_lock")
bl    get_ksyms_address
subs  r5, r0, #0
beq   .err_op                  ; (r2 = ~1 = -2)

ldr   r0, [r4, #4]
bl    _raw_spin_lock_irqsave   ; hold l2x0_lock during the patch
mov   r6, r0                   ; r6 = flags

movw/movt r1, =patch_pci_read_u32
movw/movt r0, =fixed_pci_read_u32
bl    patch_function           ; target=fixed_pci_read_u32, repl=patch_pci_read_u32

movw/movt r1, =patch_op_pa_range
mov   r0, r5                   ; r0 = &__l2c210_op_pa_range
bl    patch_function           ; target=__l2c210_op_pa_range, repl=patch_op_pa_range

ldr   r0, [r4, #4]
mov   r1, r6
bl    _raw_spin_unlock_irqrestore
mov   r0, #0
pop   {r4..r6, pc}

.err_lock:
mvn   r2, #0                   ; r2 = -1
.err_print:
movw/movt r0, =.LC2            ; "patch module%d failed %d\n"
mov   r1, #0                   ; "%d" module index (always 0)
bl    printk
mov   r0, #0
pop   {r4..r6, pc}

.err_op:
mvn   r2, #1                   ; r2 = -2
b     .err_print
```

Note that `patch_pci_read_u32` is reached by symbol relocation against
the module's own `.text` (movw/movt with `R_ARM_MOVW_ABS_NC patch_pci_read_u32`),
not via kallsyms. Same for `fixed_pci_read_u32`, which is imported as an
undefined symbol resolved by the module loader against vmlinux's
exported ksymtab entry (`__ksymtab_fixed_pci_read_u32` @ `0xc05e8c38`).

Holding `l2x0_lock` while overwriting the patched functions ensures no
CPU is mid-execution inside either target when the bytes change. Risky
without quiescing all CPUs — but the only callers that could be running
are blocked on `l2x0_lock` themselves (since both targets take it), so
the lock is sufficient.

HW writes: **none directly** (delegated). Note: each `patch_function`
call performs L1 D-cache cleans + I-cache invalidates over its target's
first 20 bytes, but `init_module` ALSO follows up with a global
`invalid_icache_all` which is necessary because `clean_l1_dcache` /
`invalid_l1_inst` only operate on the calling CPU's caches — the
companion `BPIALLIS` (in `invalid_l1_inst`) is the only inner-shareable
op, and it covers branch predictor, not I-cache lines. The global
ICIALLUIS in `invalid_icache_all` is what makes the patch visible to
the *other* CPU.

Sub-calls:
- `get_ksyms_address` (×2)
- `_raw_spin_lock_irqsave`
- `patch_function` (×2) — [fn-01]
- `_raw_spin_unlock_irqrestore`
- `printk` (error path only)

In mainline? **✗ missing**. Severity 🟢 — only meaningful in the
presence of the patched targets.

---

## [fn-06] `invalid_l1_inst(unsigned long start, unsigned long len)` @ patch.ko:.text+0x1f0 — CP15 I-cache + BP invalidate over range

What it does: per-line invalidate the current CPU's L1 I-cache over
`[start, start+len)`, then broadcast-invalidate branch predictor
(inner shareable). Signature is unusual: takes `len` not `end`, and
the first instruction `r1 += r0` converts `len` to `end` in place.

```
add   r1, r1, r0              ; r1 = end = start + len
bic   r0, r0, #31             ; r0 = start aligned down to 32B
dsb   sy
.loop:
mcr   p15, 0, r0, c7, c5, 1   ; ICIMVAU r0  — Invalidate I-cache line by MVA to PoU
add   r0, r0, #32
cmp   r0, r1
bcc   .loop

mov   r0, #0
mcr   p15, 0, r0, c7, c1, 6   ; BPIALLIS — Invalidate all branch predictors, IS
dsb   sy
isb   sy
mov   pc, lr
```

HW writes (CP15):
- ICIMVAU (`c7, c5, 1`) per 32-byte line in range — invalidate I-cache line by MVA, to PoU
- BPIALLIS (`c7, c1, 6`) — invalidate branch predictor, inner shareable

Sub-calls: none.

In mainline? **✓ replicated** in `arch/arm/mm/cache-v7.S::v7_inv_inst_range`
and the various `flush_icache_range` helpers, though mainline does NOT
expose this as a kmod-callable helper — modules use `flush_icache_range`
or `flush_cache_user_range`.

---

## [fn-07] `invalid_icache_all(void)` @ patch.ko:.text+0x220 — global I-cache invalidate

What it does: invalidates the entire L1 I-cache on **all** inner-shareable
CPUs. Used by `init_module` after patching to ensure the second CPU
also discards any prior fetches of the patched functions.

```
mov   r0, #0
mcr   p15, 0, r0, c7, c1, 0   ; ICIALLUIS — Invalidate I-cache All, IS
mov   pc, lr
```

HW writes (CP15):
- ICIALLUIS (`c7, c1, 0`) — invalidate I-cache all, inner shareable

Sub-calls: none.

In mainline? **✓ replicated** — same instruction is what
`__flush_icache_all` emits on ARMv7.

---

## [fn-08] `clean_l1_dcache(unsigned long start, unsigned long len)` @ patch.ko:.text+0x22c — CP15 D-cache clean over range

What it does: per-line clean L1 D-cache (writeback dirty lines) over
`[start, start+len)`, with bracketing `dsb sy` barriers. Used by
`patch_function` after writing the new instruction bytes — without this,
the I-fetch unit would see the old (stale) instructions because the
new bytes might still be sitting in L1 D-cache.

```
add   r1, r1, r0              ; r1 = end = start + len
bic   r0, r0, #31             ; r0 = start aligned
dsb   sy
.loop:
mcr   p15, 0, r0, c7, c10, 1  ; DCCMVAC r0  — Clean D-cache line by MVA to PoC
add   r0, r0, #32
cmp   r0, r1
bcc   .loop
dsb   sy
mov   pc, lr
```

HW writes (CP15):
- DCCMVAC (`c7, c10, 1`) per 32-byte line in range — clean D-cache line by MVA, to PoC

Sub-calls: none.

In mainline? **✓ replicated** in `arch/arm/mm/cache-v7.S::v7_clean_dcache_range`
and called via `flush_kernel_dcache_page` / `__cpuc_clean_dcache_area`.

---

## [fn-09] `hack_function0` @ patch.ko:.text+0x250 — trampoline template (DATA, not code)

What it is: structurally a 6-instruction function, but **never called**.
Exists only so that `patch_function` can copy its first 16 bytes (4
instructions) into the target as the trampoline body. The address `&hack_function0`
is loaded via `R_ARM_MOVW_ABS_NC` in `patch_function` at offsets +0x14/+0x18.

```
push  {r4, lr}                ; +0x00  ←
ldr   r4, [pc, #4]            ; +0x04  ← copied verbatim
blx   r4                      ; +0x08  ← into target[0..15]
pop   {r4, pc}                ; +0x0c  ←
nop   {0}                     ; +0x10  (NOT copied — target[+16] is set explicitly to replacement addr)
nop   {0}                     ; +0x14  (NOT copied)
```

The `ldr r4, [pc, #4]` on ARM means "load from PC + 8 + #4 = LDR_addr + 12".
At its eventual location inside the target (LDR_addr = target+4), that's
`target + 16` — exactly where `patch_function` writes the replacement
address. The `nop`s at +0x10/+0x14 are inert padding so that the symbol's
size and `.ARM.exidx` unwind metadata stay valid; they never execute and
they never get copied into the target.

HW writes: none. (Pure data masquerading as code.)

Sub-calls: none (and none are ever taken — this is never reached as code).

In mainline? **N/A**.

---

## [fn-10] `cleanup_module` @ patch.ko:.exit.text+0x0 — module exit

What it does: tail-calls `printk("bug!!!,patch module ,exit\n")` and
returns. **Does not undo the patches.** Once installed, the trampolines
stay in vmlinux's `.text` until reboot. The module can't actually be
unloaded safely while the kernel is calling the patched functions, which
matches the message ("bug!!!" — i.e. "if you got here you've done
something wrong").

```
movw/movt r0, =.LC0       ; "bug!!!,patch module ,exit\n" (rodata+0x00)
b     printk
```

HW writes: none.

Sub-calls: `printk`.

In mainline? **N/A**.

---

## Cross-references

### Patched targets in stock vmlinux

| Symbol | Addr | Patched-by | Role |
|---|---|---|---|
| `__l2c210_op_pa_range` | `0xc0014cc0` | [fn-04] `patch_op_pa_range` | PL310 PA-range cache op driver |
| `fixed_pci_read_u32`   | `0xc0014dec` | [fn-03] `patch_pci_read_u32` | vendor PCIe u32 accessor (ksymtab-exported) |
| `l2x0_lock`            | `0xc069e9c8` | (read only, via kallsyms) | shared raw spinlock |

### Stock-vs-mainline divergence on the patched functions

**`__l2c210_op_pa_range`**:
- **Mainline (v4.1 and v6.6)** `arch/arm/mm/cache-l2x0.c:178`: simple
  `while (start < end) { writel_relaxed(start, reg); start += 32; }`,
  no locking. Locking, if any, is done by the outer `l2c210_*_range`
  caller around unaligned head/tail writes only.
- **Stock ZTE 4.1.25**: per-line `raw_spin_lock_irqsave(&l2x0_lock)` /
  `_unlock_irqrestore` around each `writel`. About 64x more lock
  traffic than mainline.
- **patch.ko**: chunks the lock — one acquire per 2 KiB (64 lines)
  instead of per line, with a `pci_read_coming` doorbell to yield
  mid-chunk if a PCIe read is pending.

**`fixed_pci_read_u32`**:
- **Mainline**: doesn't exist. Drivers use `readl`/`pci_read_config_dword`
  directly.
- **Stock ZTE 4.1.25**: takes `l2x0_lock`, reads one u32, releases.
- **patch.ko**: same as stock, plus the `pci_read_coming = 1` /
  `... = 0` doorbell pair around the lock acquire/release.

### Mainline (v6.6) — does it need an equivalent fix?

**No.** Mainline `cache-l2x0.c` doesn't take `l2x0_lock` inside the PA-range
loop at all (lines 178-185 are still the simple no-lock variant), so there
is no perf regression to undo. Mainline also has no `fixed_pci_read_u32`
because PCIe drivers don't cross-coordinate with the L2 controller in
mainline-supported platforms.

The underlying race (L2C-310 PA-op vs. concurrent PCIe MMIO causing
deadlock or SLVERR on this SoC) is **not** an upstream ARM-published
PL310 erratum — it appears to be a ZXIC ZX279128S integration-specific
issue. If a mainline port of this SoC re-introduces the race, the fix
would need to live in either:
1. A DT property like `zte,errata-l2-pcie-serialization` on the
   `arm,pl310-cache` node that swaps in a chunked, doorbell-aware
   variant of `l2c210_*_range` and a wrapped PCIe accessor.
2. Or — more invasive — a board-specific outer cache fns struct that
   inherits from `l2c310_data.outer_cache` and overrides the three
   `*_range` functions.

The post-patch hot-path on this SoC is:
```
(some driver) -> l2c210_clean_range -> __l2c210_op_pa_range (trampoline) -> patch_op_pa_range
                                            ^                                    ^
                                        20-byte stub                         real impl in patch.ko's .text
```
which costs one extra `bl` per call. That's negligible compared to the
~62x lock-traffic reduction.

---

## Summary

`patch.ko` is a hot-patcher whose entire purpose is to install two
runtime trampolines in vmlinux:

1. Replace `__l2c210_op_pa_range` (the stock-kernel version of which
   takes `l2x0_lock` per cache line — a heavy perf regression vs.
   mainline) with a chunked-lock variant that holds the lock for up
   to 64 lines / 2 KiB at a time, and uses a `pci_read_coming`
   doorbell flag to yield mid-burst when a PCIe read is pending.

2. Replace `fixed_pci_read_u32` (the stock-kernel vendor PCIe accessor)
   with a near-identical body that also sets/clears the `pci_read_coming`
   doorbell so the new L2 op above knows when to yield.

The trampoline mechanism is a 5-instruction `push/ldr/blx/pop`+addr stub
written over the first 20 bytes of each target function. The template
comes from a never-called local function `hack_function0` whose body is
used purely as a byte-source. Post-patch, L1 D-cache is cleaned and L1
I-cache is globally invalidated (inner shareable) to make the new code
visible to all CPUs.

Mainline v6.6 has **no equivalent need** — its `__l2c210_op_pa_range`
is already the simple no-lock variant, and it has no
`fixed_pci_read_u32`. The underlying race is a ZXIC ZX279128S-specific
SoC integration issue, not a published ARM PL310 erratum.

Mainline severity verdict: 🟢 — informational only, mainline never
inherited the regression this module fixes.
