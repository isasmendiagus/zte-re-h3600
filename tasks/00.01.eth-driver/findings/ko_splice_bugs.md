# Bugs found while building `ko_printk_splice.py`

Constraints discovered through iteration with the ZTE-stock kernel
(Linux 4.1.25, ARMv7, REL encoding). Each one bricked the device until
fixed.

---

## Bug 1: Displaced first instructions that carry a `.rel.text` relocation

**Symptom**: device bootloops after `switch.ko` load attempt. No panic
on UART (kmsg2uart hasn't started yet, or the panic is too deep).

**Cause**: the splicer overwrites a function's first instruction with
`b _splice_thunk_<name>` and copies the original instruction into the
thunk. But some functions begin with a `movw`/`movt`/`mov` that has an
`R_ARM_MOVW_ABS_NC` / `R_ARM_MOVT_ABS` / `R_ARM_ABS32` relocation
attached. The lingering reloc in `.rel.text` then gets applied to OUR
branch instruction at load time, corrupting it. AND the bare displaced
instruction in the thunk lacks the relocation it needs, so even if the
branch survived, the function's behavior would be wrong.

**Detection**: grep `.rel.text` for `r_offset == sym.st_value` of each
candidate.

**Fix**: in `find_candidates()`, skip any function whose first-insn
offset appears in `.rel.text`'s relocation list. See `relocated_offsets`
set built at the top of that function.

**Affected `switch.ko` functions (3 of 7 init-pattern candidates)**:
- `ethdrv_port_dev_init` @ .text+0x8 — `R_ARM_MOVT_ABS` to `.LC37`
- `pdt_ethdriver_init` @ .text+0x4b0 — `R_ARM_MOVW_ABS_NC` to `.LC26`
- `sw_qos_init` @ .text+0x8918 — `R_ARM_MOVW_ABS_NC` to `g_pon_work_mode`

---

## Bug 2: LIEF appends symbols past `.symtab`'s `sh_info` without updating it

**Symptom**: identical to Bug 1 — silent bootloop, no kernel error
message reaches UART.

**Cause**: ELF spec requires `.symtab.sh_info` = index of the first
non-local symbol; all symbols before it must have `STB_LOCAL` binding,
all after must be `STB_GLOBAL`/`STB_WEAK`. LIEF appends new symbols to
the END of `.symtab` (after the existing globals) without updating
`sh_info`. If the new symbols are created with `STB_LOCAL` binding,
they land in the "globals zone" and produce a malformed ELF.

`readelf -s` warns on this with:
```
local symbol N found at index >= .symtab's sh_info value of M
```

**Fix**: create the slot + thunk symbols with `STB_GLOBAL` binding
(prefixed `_splice_*` to avoid kallsyms collisions). They land in the
correct zone since they're at the tail.

This explanation is by inference — kernel module loader code path that
trips on this is not fully traced, but `readelf`'s warning is a strong
hint and the bootloop disappears under the fix (TBD verified).

---

## Bug 3 (open, abandoned): even a fully-naked thunk crashes the system

After fixing Bug 1 and Bug 2, a **naked thunk** (just 6 NOPs + the
displaced original prologue + `b func+4` back-jump, no memwrite, no
MOVW/MOVT relocations, GLOBAL bindings on all added symbols, only
chip_tm_init patched = 1 function) STILL bootloops on the device.

The userspace simulator (`ko_loader_sim.py`) confirms both the forward
branch (chip_tm_init+0 → thunk) and the back-jump (thunk+1c → func+4)
resolve to correct runtime addresses with no out-of-range condition.

Possible remaining hypotheses (untested):
- `.ARM.exidx` entry for `chip_tm_init` is stale w.r.t. our patched
  first instruction. The unwinder might choke during a stack walk
  triggered by something else, panicing the kernel.
- Symbol versioning / `__versions` CRC check excludes our added globals
  in some way that breaks module signing assumptions.
- The added `.text.splice` / `.data.splice` sections land at runtime
  addresses outside the module's expected memory layout (e.g. far from
  `.text`, breaking some implicit assumption).
- The function being patched (`chip_tm_init`) is called via a function
  pointer recorded elsewhere (e.g. in `__init_array` or a registration
  table). The pointer still goes to the right place, but maybe some
  ordering thing is off.

**Decision (2026-05-23)**: abandon the on-disk LIEF-based splice
approach. The on-disk patching pipeline is structurally too brittle
for this kernel — it bricks the device without leaving a panic message
even on a no-op-equivalent thunk. The cost of further debugging
exceeds the cost of switching strategies.

**Pivot — done, validated, working**: see
[[idea_a_kotrace]] for the full writeup. A separate `kotrace.ko`
module registers `register_module_notifier()`, intercepts switch.ko at
`MODULE_STATE_COMING`, and patches its `.text` in RAM with
pre-resolved instruction bytes. Doesn't touch the .ko on disk; lets
the kernel load switch.ko normally and only intervenes after that
succeeds. Avoids every bug class in this document. First trace
captured 2026-05-23 — the init order is in the idea_a_kotrace doc.

---

## Userspace validator: `scripts/ko_loader_sim.py`

Mirrors `kernel/module.c` + `arch/arm/kernel/module.c` apply_relocate.
Loads the .ko, assigns fake runtime addresses to SHF_ALLOC sections,
applies every relocation to the in-memory image, and reports out-of-
range, unsupported, or malformed conditions the real kernel would.

Catches: Bug 1 (now-correct after filter), Bug 2 (warning only via
`readelf`), most plain reloc bugs.

Does NOT catch: kallsyms / `__versions` / runtime-layout / unwinder
issues. Use the real device for those (TBD: spin up QEMU virt with a
matching kernel for a faster cycle on those failure modes).
