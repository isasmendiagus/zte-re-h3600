#!/usr/bin/env python3
"""ko_printk_splice.py — splice printk calls into stock .ko modules at
function entries, so we can observe what stock does at runtime when we
have no source code.

Methodology + full design notes: see
  tasks/00.01.eth-driver/research/printk_injection_methodology.md

Workflow:
  splicer --src ext/kmodules_dump/switch.ko \\
          --out tasks/00.01.eth-driver/out/spliced/switch.scope-init.ko \\
          --scope init

After running, push the patched .ko to the device and load it:
  scp <out>.ko admin@192.168.1.1:/tmp/
  python3 lib/ssh_shell.py "rmmod switch; insmod /tmp/<out>.ko"

UART (via kmsg2uart) will then show one log line per spliced function entry
of the form:
  [STOCK 000036ac] called

The address is the function's offset within the module's .text. Resolve it
back to the symbol name post-hoc:
  arm-linux-gnueabi-nm <orig>.ko | grep <addr>

----------------------------------------------------------------------
v0 scope:
  - Single shared format string "[STOCK %08x] called\\n"
  - Per-function thunk passes the function's .text offset as printk arg
  - Skips functions where the first instruction is PC-relative
    (b, bl, ldr [pc,...], etc.) — those would break in the relocated thunk
  - Requires `printk` to already be an UND symbol in the input .ko
    (true for every stock module we care about; they all call printk)
  - ARM 32-bit only (no Thumb, no AArch64)
  - Uses LIEF for the ELF section/symbol/relocation surgery

Per-function thunk layout (44 bytes code + inline fmt string padded to 4):
  +0   push {r0-r3, r12, lr}              0xe92d500f
  +4   movw r1, #(func_addr & 0xffff)     pass func address as printk arg
  +8   movt r1, #(func_addr >> 16)
  +12  adr  r0, fmt_below                 PC-relative load of fmt string addr
  +16  bl   printk                        R_ARM_CALL → printk symbol
  +20  pop  {r0-r3, r12, lr}              0xe8bd500f
  +24  <displaced_insn>                   func's original first instruction
  +28  b    func+4                        R_ARM_JUMP24 → func symbol (addend=+4)
  +32  fmt: "[STOCK %08x] called\\n\\0"   inline (NUL terminated, padded to 4)
"""

import argparse
import re
import struct
import sys
from pathlib import Path

try:
    import lief
except ImportError:
    sys.exit("lief not installed. pip install lief")

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("pyelftools not installed. pip install pyelftools")


# ---------------------------------------------------------------------------
# Defaults
# ---------------------------------------------------------------------------

DEFAULT_INIT_PATTERN = (
    r"^(init_module|cleanup_module|"
    r"init_.+|.+_init|"
    r"chip_(tm_init|pp_init|init)|"
    r"sw_init.*|pdt_.*_init|"
    r"(.+_)?probe)$"
)

# MEMWRITE THUNK MODE (printk crashes the kernel from our hand-crafted thunk
# context — see PLAN_init_debug.md Phase 2 notes). Each thunk now writes a
# magic byte 0xFF to a unique slot in a new .data.splice section. After
# boot, retrieve via:
#   cat /sys/module/switch/sections/.data.splice  → runtime address
#   then dump that address via /dev/mem or memdump tool
# Any non-zero byte == that thunk ran.
THUNK_CODE_BYTES = 32   # 8 instructions × 4 bytes (see build_thunk_bytes)
THUNK_BYTES_TOTAL = THUNK_CODE_BYTES   # no inline fmt string in memwrite mode

# .data.splice layout: one byte per thunk slot. Padded to 4 for alignment.
def data_splice_size(n_thunks: int) -> int:
    return ((n_thunks + 3) // 4) * 4


# ---------------------------------------------------------------------------
# ARM A32 instruction encoders (little-endian when packed)
# ---------------------------------------------------------------------------

def insn_push_low_lr():
    """push {r0-r3, r12, lr} == stmdb sp!, {r0,r1,r2,r3,r12,lr}"""
    return 0xE92D500F


def insn_pop_low_lr():
    """pop {r0-r3, r12, lr} == ldmia sp!, {r0,r1,r2,r3,r12,lr}"""
    return 0xE8BD500F


def insn_push_r2_r3():
    """push {r2, r3} == stmdb sp!, {r2, r3}. 8 bytes — keeps 8-byte SP alignment."""
    return 0xE92D000C


def insn_pop_r2_r3():
    """pop {r2, r3} == ldmia sp!, {r2, r3}"""
    return 0xE8BD000C


def insn_movw(rd, imm16):
    """movw Rd, #imm16"""
    assert 0 <= imm16 <= 0xFFFF
    imm4 = (imm16 >> 12) & 0xF
    imm12 = imm16 & 0xFFF
    return 0xE3000000 | (imm4 << 16) | (rd << 12) | imm12


def insn_movt(rd, imm16):
    """movt Rd, #imm16 (set upper 16 bits)"""
    assert 0 <= imm16 <= 0xFFFF
    imm4 = (imm16 >> 12) & 0xF
    imm12 = imm16 & 0xFFF
    return 0xE3400000 | (imm4 << 16) | (rd << 12) | imm12


def insn_mov_imm8(rd, imm8):
    """mov Rd, #imm8 (no rotation)"""
    assert 0 <= imm8 <= 0xFF
    return 0xE3A00000 | (rd << 12) | imm8


def insn_strb_rd_at_rn(rd, rn):
    """strb Rd, [Rn] — store byte, no offset, no writeback."""
    # cond=AL(E) 0101 U=1 B=1 W=0 L=0, Rn(4), Rd(4), imm12=0
    # = E5CN R000  where N=Rn, R=Rd
    return 0xE5C00000 | (rn << 16) | (rd << 12)


def insn_adr_pc_imm8(rd, byte_offset_from_pc8):
    """add Rd, pc, #imm. ARM ADR pseudo-instruction. The offset is from
    PC+8 (ARM prefetch). Only 8-bit immediate (with rotation field 0) here.
    Caller passes byte offset from PC+8 to the target label."""
    assert 0 <= byte_offset_from_pc8 <= 0xFF
    # cond=AL(E) [31:28], op=001 [27:25], opcode=ADD=0100 [24:21], S=0 [20],
    # Rn=15(pc) [19:16], Rd [15:12], imm12 [11:0] (rotation_imm=0, imm8=val)
    return 0xE28F0000 | (rd << 12) | byte_offset_from_pc8


def insn_bl_placeholder():
    """bl . (== bl <self>). Standard placeholder before relocation;
    encoded addend = -8, which compensates ARM's +8 PC prefetch so the
    R_ARM_CALL formula resolves cleanly to the symbol's address."""
    return 0xEBFFFFFE


def insn_b_to_symbol_plus_4_placeholder():
    """b symbol+4 placeholder for R_ARM_JUMP24.

    Derivation:
       Runtime target = P + 8 + (sign_extend(imm24_final) << 2)
       Loader sets:    imm24_final = ((S + A) - P) >> 2
       So target = S + A + 8.
       We want target = S + 4  →  A = -4
       A = sign_extend(imm24_placeholder) << 2  →  imm24_placeholder = -1
       Encoded = 0xea000000 | 0xffffff = 0xeaffffff
    """
    return 0xEAFFFFFF


# ---------------------------------------------------------------------------
# Splice-candidate detection
# ---------------------------------------------------------------------------

def is_pc_relative(insn: int) -> bool:
    """Return True if the instruction reads PC or branches PC-relative —
    such instructions can't safely be displaced into a thunk."""
    cond = (insn >> 28) & 0xF
    if cond == 0xF:
        return True  # rare unconditional encoding, be safe

    # b / bl (immediate branch): bits 27-25 = 101
    if ((insn >> 25) & 0x7) == 0x5:
        return True

    # ldr/str with Rn=15 (pc): single-data-transfer (bits 27-26 = 01),
    # Rn at 19-16
    if ((insn >> 26) & 0x3) == 0x1:
        if ((insn >> 16) & 0xF) == 0xF:
            return True

    # add/sub Rd, pc, #imm (used by adr): bits 27-26 = 00, immediate operand
    # I bit = 25, Rn=15
    if ((insn >> 26) & 0x3) == 0x0:
        if ((insn >> 25) & 1) == 1:
            if ((insn >> 16) & 0xF) == 0xF:
                return True

    # bx: bits 27-4 = 0001 0010 1111 1111 1111 0001
    if (insn & 0x0FFFFFF0) == 0x012FFF10:
        return True

    return False


def find_candidates(src: Path, pattern: re.Pattern):
    """Use pyelftools (read-only is sufficient) to enumerate candidate
    functions. Returns (candidates, skipped, text_data_bytes) tuple."""
    with open(src, "rb") as fh:
        elf = ELFFile(fh)
        text = next((s for s in elf.iter_sections() if s.name == ".text"), None)
        if text is None:
            sys.exit("input .ko has no .text section")
        text_bytes = text.data()
        text_idx = list(elf.iter_sections()).index(text)
        symtab = next((s for s in elf.iter_sections() if s.name == ".symtab"), None)
        if symtab is None:
            sys.exit("input .ko has no .symtab section")

        # Collect all .rel.text offsets that have a relocation. We must
        # skip functions whose first instruction carries a reloc: if we
        # displace the bare instruction to the thunk without bringing
        # the reloc along, both sides break — the original .text offset
        # ends up with our `b thunk` branch corrupted by the lingering
        # MOVW/MOVT/ABS32 patch, AND the displaced insn in the thunk
        # still has its imm field = 0 because the reloc wasn't moved.
        rel_text = next(
            (s for s in elf.iter_sections() if s.name == ".rel.text"),
            None,
        )
        relocated_offsets: set[int] = set()
        if rel_text is not None:
            for rel in rel_text.iter_relocations():
                relocated_offsets.add(rel["r_offset"])

        candidates, skipped = [], []
        for sym in symtab.iter_symbols():
            if sym["st_info"]["type"] != "STT_FUNC":
                continue
            if sym["st_shndx"] != text_idx:
                continue
            if not pattern.match(sym.name):
                continue
            text_off = sym["st_value"]
            size = sym["st_size"]
            if size < 4:
                skipped.append((sym.name, "function < 4 bytes"))
                continue
            if text_off + 4 > len(text_bytes):
                skipped.append((sym.name, "function entry past .text end"))
                continue
            displaced = struct.unpack_from("<I", text_bytes, text_off)[0]
            if is_pc_relative(displaced):
                skipped.append(
                    (sym.name, f"first insn 0x{displaced:08x} is PC-relative")
                )
                continue
            if text_off in relocated_offsets:
                skipped.append(
                    (sym.name, f"first insn at .text+0x{text_off:x} carries a "
                     ".rel.text relocation (can't safely displace)")
                )
                continue
            candidates.append({
                "name": sym.name,
                "func_text_off": text_off,
                "size": size,
                "displaced_insn": displaced,
            })
        return candidates, skipped


# ---------------------------------------------------------------------------
# Thunk codegen
# ---------------------------------------------------------------------------

def build_thunk_bytes_naked(displaced_insn: int) -> bytes:
    """Diagnostic thunk: no memwrite, just NOPs + displaced + back-jump.
    Used to isolate: does the splice MECHANISM crash, or only the memwrite?"""
    NOP = 0xe1a00000   # mov r0, r0
    insns = [
        NOP, NOP, NOP, NOP, NOP, NOP,             # +0..+20 (6 NOPs)
        displaced_insn,                            # +24
        insn_b_to_symbol_plus_4_placeholder(),     # +28
    ]
    return b"".join(struct.pack("<I", x) for x in insns)


def build_thunk_bytes(displaced_insn: int) -> bytes:
    """Generate the 28-byte memwrite thunk code (no inline data).

    Layout (offsets within thunk):
      +0   push {r2, r3}                  save scratch (preserves 8-byte SP align)
      +4   movw r2, #0                    LO half of slot addr — R_ARM_MOVW_ABS_NC patches
      +8   movt r2, #0                    HI half of slot addr — R_ARM_MOVT_ABS patches
      +12  mov  r3, #0xFF                 magic "thunk ran" byte
      +16  strb r3, [r2]                  write magic to slot
      +20  pop  {r2, r3}                  restore
      +24  <displaced original insn>      execute the displaced first instruction
      +28  b    func+4                    R_ARM_JUMP24 to func+4 (no encoded data here)

    The displaced + back-jump take 8 bytes; total thunk = 32 bytes.
    The memwrite is 5 instructions (push + movw + movt + mov + strb + pop = 24 bytes).
    Total 28+4 = 32... wait, that doesn't match. Recompute:
      6 setup insns × 4 = 24 bytes (push + movw + movt + mov + strb + pop)
      1 displaced insn × 4 = 4 bytes
      1 back-jump × 4 = 4 bytes
      Total = 32 bytes  → so THUNK_CODE_BYTES should be 32.
    """
    insns = [
        insn_push_r2_r3(),                       # +0
        insn_movw(2, 0),                          # +4   (relocated R_ARM_MOVW_ABS_NC)
        insn_movt(2, 0),                          # +8   (relocated R_ARM_MOVT_ABS)
        insn_mov_imm8(3, 0xFF),                   # +12
        insn_strb_rd_at_rn(3, 2),                 # +16  strb r3, [r2]
        insn_pop_r2_r3(),                         # +20
        displaced_insn,                           # +24
        insn_b_to_symbol_plus_4_placeholder(),    # +28  R_ARM_JUMP24
    ]
    return b"".join(struct.pack("<I", x) for x in insns)


# ---------------------------------------------------------------------------
# ELF emission (LIEF)
# ---------------------------------------------------------------------------

def emit(src: Path, out: Path, candidates: list, verbose: bool = True,
         naked: bool = False) -> int:
    binary = lief.ELF.parse(str(src))
    if binary is None:
        sys.exit(f"LIEF failed to parse {src}")

    # Build the contiguous thunk blob; remember each func's offset within it.
    builder = build_thunk_bytes_naked if naked else build_thunk_bytes
    thunk_blob = bytearray()
    thunk_offsets = {}  # func_name -> byte offset of thunk start in blob
    for c in candidates:
        thunk_offsets[c["name"]] = len(thunk_blob)
        thunk_blob += builder(c["displaced_insn"])

    if verbose:
        print(f"  thunk blob: {len(thunk_blob)} bytes total "
              f"({len(candidates)} × {THUNK_BYTES_TOTAL}B)")

    # Add the new .text.splice section, executable + allocatable.
    splice_sec = lief.ELF.Section(".text.splice")
    splice_sec.content = list(thunk_blob)
    splice_sec.type = lief.ELF.Section.TYPE.PROGBITS
    splice_sec.flags = int(lief.ELF.Section.FLAGS.ALLOC) | int(
        lief.ELF.Section.FLAGS.EXECINSTR
    )
    splice_sec.alignment = 4
    # NOTE: requires the patched LIEF from
    # tasks/00.01.01.fix-lief-rel-sections/ — stock LIEF 0.17.6 silently
    # drops sections added to REL files (issue #661). Our patched LIEF
    # detects REL and routes through the no-segment path, and uses
    # last_offset_section as the floor instead of 0 (which would corrupt
    # the ELF header). `add()` may still return None — look up by name.
    binary.add(splice_sec, loaded=True)
    splice_sec = next((s for s in binary.sections if s.name == ".text.splice"),
                      None)
    if splice_sec is None:
        sys.exit("LIEF didn't add .text.splice (need patched LIEF — see "
                 "tasks/00.01.01.fix-lief-rel-sections/)")
    if verbose:
        print(f"  added section: {splice_sec.name} "
              f"(file offset {splice_sec.file_offset:#x}, "
              f"size {splice_sec.size:#x}, "
              f"vaddr {splice_sec.virtual_address:#x})")

    splice_idx = list(binary.sections).index(splice_sec)
    symtab_sec = next((s for s in binary.sections if s.name == ".symtab"), None)
    if symtab_sec is None:
        sys.exit(".symtab section not found in input .ko")
    symtab_idx = list(binary.sections).index(symtab_sec)

    # Add .data.splice section — one byte per thunk, initialized to 0.
    # Thunks will write 0xFF here when they run.
    data_size = data_splice_size(len(candidates))
    data_sec = lief.ELF.Section(".data.splice")
    data_sec.content = [0] * data_size
    data_sec.type = lief.ELF.Section.TYPE.PROGBITS
    data_sec.flags = int(lief.ELF.Section.FLAGS.ALLOC) | int(
        lief.ELF.Section.FLAGS.WRITE
    )
    data_sec.alignment = 4
    binary.add(data_sec, loaded=True)
    data_sec = next((s for s in binary.sections if s.name == ".data.splice"), None)
    if data_sec is None:
        sys.exit("LIEF didn't add .data.splice")
    data_idx = list(binary.sections).index(data_sec)
    if verbose:
        print(f"  added section: .data.splice "
              f"(size {data_sec.size:#x} = {data_size} byte slots)")

    # Pre-create .rel.text.splice (REL section for thunk relocations).
    rel_splice_sec = lief.ELF.Section(".rel.text.splice")
    rel_splice_sec.type = lief.ELF.Section.TYPE.REL
    rel_splice_sec.flags = 0
    rel_splice_sec.link = symtab_idx
    rel_splice_sec.information = splice_idx
    rel_splice_sec.alignment = 4
    rel_splice_sec.entry_size = 8  # sizeof(Elf32_Rel)
    rel_splice_sec.content = [0]
    binary.add(rel_splice_sec, loaded=False)
    if verbose:
        print(f"  added section: .rel.text.splice "
              f"(link={symtab_idx}=.symtab, info={splice_idx}=.text.splice)")

    # Add per-thunk slot symbols pointing into .data.splice.
    R_MOVW = lief.ELF.Relocation.TYPE.ARM_MOVW_ABS_NC
    R_MOVT = lief.ELF.Relocation.TYPE.ARM_MOVT_ABS
    R_JUMP24 = lief.ELF.Relocation.TYPE.ARM_JUMP24
    REL = lief.ELF.Relocation.ENCODING.REL

    sym_by_name = {s.name: s for s in binary.symbols}

    # NOTE on binding: LIEF appends new symbols at the END of the symtab
    # without reordering or updating .symtab's sh_info (= index of first
    # non-local). If we add LOCAL symbols here, they land AFTER sh_info,
    # which violates the ELF spec (locals must precede non-locals). The
    # kernel module loader uses sh_info as the boundary for several
    # operations and either drops these symbols or misroutes them — the
    # observable failure mode in our case was instant bootloop with no
    # panic message via UART. Using GLOBAL binding puts our symbols in
    # the correct zone of the symtab. They're internal to our patch
    # (names prefixed with _splice_), so cross-module collision risk is
    # negligible.
    slot_symbols = {}
    if not naked:
        for i, c in enumerate(candidates):
            ss = lief.ELF.Symbol()
            ss.name = f"_splice_slot_{c['name']}"
            ss.type = lief.ELF.Symbol.TYPE.OBJECT
            ss.binding = lief.ELF.Symbol.BINDING.GLOBAL
            ss.value = i                  # byte offset within .data.splice
            ss.size = 1
            ss.shndx = data_idx
            slot_symbols[c["name"]] = binary.add_symtab_symbol(ss)

    # Per-function relocations: MOVW/MOVT for slot addr + JUMP24 for back-jump.
    # In naked mode, skip MOVW/MOVT (no memwrite); only back-jump.
    # LIEF copies the input reloc and drops the symbol — must re-attach on
    # the binary-owned returned object.
    for c in candidates:
        thunk_off = thunk_offsets[c["name"]]
        movw_off  = splice_sec.virtual_address + thunk_off + 4
        movt_off  = splice_sec.virtual_address + thunk_off + 8
        b_back_off = splice_sec.virtual_address + thunk_off + 28

        if not naked:
            slot_sym = slot_symbols[c["name"]]
            rmw = lief.ELF.Relocation(movw_off, R_MOVW, REL)
            added_rmw = binary.add_object_relocation(rmw, splice_sec)
            added_rmw.symbol = slot_sym
            rmt = lief.ELF.Relocation(movt_off, R_MOVT, REL)
            added_rmt = binary.add_object_relocation(rmt, splice_sec)
            added_rmt.symbol = slot_sym

        # Back-jump to func+4
        func_sym = sym_by_name.get(c["name"])
        if func_sym is None:
            print(f"  WARN: no symbol object for {c['name']} — back-jump cannot "
                  "be relocated (will likely crash on insmod)")
            continue
        r2 = lief.ELF.Relocation(b_back_off, R_JUMP24, REL)
        added_r2 = binary.add_object_relocation(r2, splice_sec)
        added_r2.symbol = func_sym

    if verbose:
        n_relocs = (1 if naked else 3) * len(candidates)
        mode = "naked: only JUMP24 back-jump" if naked else \
               f"{len(candidates)} MOVW + {len(candidates)} MOVT + {len(candidates)} JUMP24"
        print(f"  added {n_relocs} relocations ({mode})")

    # Patch each original function entry with `b thunk`.
    # Also a cross-section reference → another R_ARM_JUMP24 against a per-thunk
    # symbol. We need symbols at each thunk's start. Add them.
    text_sec = next((s for s in binary.sections if s.name == ".text"), None)
    if text_sec is None:
        sys.exit(".text section disappeared after add (LIEF bug?)")

    for c in candidates:
        thunk_off = thunk_offsets[c["name"]]
        thunk_sym_name = f"_splice_thunk_{c['name']}"
        # Local function symbol pointing at the thunk's start in .text.splice
        ts = lief.ELF.Symbol()
        ts.name = thunk_sym_name
        ts.type = lief.ELF.Symbol.TYPE.FUNC
        # GLOBAL not LOCAL — see slot_symbols note above. LIEF appends
        # to symtab end without updating sh_info; LOCAL after sh_info is
        # malformed ELF and confuses the kernel module loader.
        ts.binding = lief.ELF.Symbol.BINDING.GLOBAL
        ts.value = thunk_off
        ts.size = THUNK_BYTES_TOTAL
        ts.shndx = list(binary.sections).index(splice_sec)
        thunk_sym = binary.add_symtab_symbol(ts)

        # Now place the `b thunk_sym` placeholder at the function's entry in
        # .text and add an R_ARM_JUMP24 relocation pointing at thunk_sym.
        # Placeholder = 0xeafffffe ("b ." for R_ARM_JUMP24 with addend = 0).
        # Hmm: addend for "b ." is sign_extend(0xfffffe)<<2 = -8.
        # We want runtime target = thunk (not thunk-8), so addend should be 0
        # in the formula target = S + A + 8.  That gives target = thunk + 8.
        # We actually want target = thunk + 0, so A = -8, which is what the
        # placeholder gives.  Match. ✓
        placeholder = 0xEAFFFFFE
        # text_sec content is a list of ints (bytes); patch 4 bytes at func_off
        text_content = bytearray(text_sec.content)
        struct.pack_into("<I", text_content, c["func_text_off"], placeholder)
        text_sec.content = list(text_content)

        r3 = lief.ELF.Relocation(text_sec.virtual_address + c["func_text_off"],
                                 R_JUMP24, REL)
        added_r3 = binary.add_object_relocation(r3, text_sec)
        added_r3.symbol = thunk_sym   # re-attach on the binary-owned reloc

    if verbose:
        print(f"  patched {len(candidates)} function entries in .text "
              f"(each: 4-byte `b` to its thunk + R_ARM_JUMP24 reloc)")

    binary.write(str(out))
    out_size = out.stat().st_size
    src_size = src.stat().st_size
    if verbose:
        print(f"  wrote {out} ({src_size:,} → {out_size:,} bytes, "
              f"+{out_size - src_size:,})")
    return 0


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n", 1)[0])
    ap.add_argument("--src", type=Path, required=True,
                    help="input stock .ko file")
    ap.add_argument("--out", type=Path, required=True,
                    help="output patched .ko file")
    ap.add_argument("--scope", default="init",
                    help="'init' (default; matches init-named funcs) OR a "
                         "regex matching function names to splice")
    ap.add_argument("--list", action="store_true",
                    help="just list candidates matching --scope, do not write")
    ap.add_argument("--naked", action="store_true",
                    help="DIAGNOSTIC: emit thunks with NOPs instead of memwrite, "
                         "no MOVW/MOVT relocs, no slot symbols. Tests if the splice "
                         "mechanism itself is sound vs whether the memwrite is the bug.")
    args = ap.parse_args()

    if not args.src.is_file():
        sys.exit(f"input not found: {args.src}")

    pattern = (re.compile(DEFAULT_INIT_PATTERN) if args.scope == "init"
               else re.compile(args.scope))
    candidates, skipped = find_candidates(args.src, pattern)

    print(f"Source: {args.src}")
    print(f"Scope:  {args.scope!r}")
    print(f"Found {len(candidates)} candidate function(s):")
    for c in candidates:
        print(f"  + {c['name']:40s} @ .text+0x{c['func_text_off']:08x} "
              f"(displaced insn: 0x{c['displaced_insn']:08x})")
    if skipped:
        print(f"\nSkipped {len(skipped)} function(s):")
        for n, why in skipped:
            print(f"  - {n}: {why}")

    if args.list or not candidates:
        return 0

    args.out.parent.mkdir(parents=True, exist_ok=True)
    print(f"\nEmitting patched .ko via LIEF...")
    return emit(args.src, args.out, candidates, naked=args.naked)


if __name__ == "__main__":
    sys.exit(main())
