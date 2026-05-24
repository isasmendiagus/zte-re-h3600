#!/usr/bin/env python3
"""Userspace simulator of the ARM Linux kernel module loader.

Reads a .ko, mimics what `kernel/module.c` (simplify_symbols + apply_relocations)
+ `arch/arm/kernel/module.c` (apply_relocate) would do at insmod time, and
reports any error the kernel would print and the resolved values of patched
instructions.

Goal: catch malformed-ELF / bad-relocation bugs WITHOUT a flash-cycle on the
device. Targeted at this kernel (Linux 4.1.25, ARMv7, little-endian, REL
encoding). Does NOT execute code — only resolves what insmod would do up
to the point of calling init_module().

Usage:
    python3 ko_loader_sim.py <path/to/module.ko>

Exit code 0 = clean load. Nonzero = at least one error (bug to fix).
"""
import struct
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection
from elftools.elf.relocation import RelocationSection
from elftools.elf.constants import SH_FLAGS


# ARM relocation types we care about (from arch/arm/include/asm/elf.h)
R_ARM_NONE          = 0
R_ARM_ABS32         = 2
R_ARM_PC24          = 5      # legacy, treated like CALL
R_ARM_CALL          = 28
R_ARM_JUMP24        = 29
R_ARM_TARGET1       = 38
R_ARM_V4BX          = 40
R_ARM_PREL31        = 42
R_ARM_MOVW_ABS_NC   = 43
R_ARM_MOVT_ABS      = 44

R_NAMES = {
    R_ARM_NONE: "R_ARM_NONE",
    R_ARM_ABS32: "R_ARM_ABS32",
    R_ARM_PC24: "R_ARM_PC24",
    R_ARM_CALL: "R_ARM_CALL",
    R_ARM_JUMP24: "R_ARM_JUMP24",
    R_ARM_TARGET1: "R_ARM_TARGET1",
    R_ARM_V4BX: "R_ARM_V4BX",
    R_ARM_PREL31: "R_ARM_PREL31",
    R_ARM_MOVW_ABS_NC: "R_ARM_MOVW_ABS_NC",
    R_ARM_MOVT_ABS: "R_ARM_MOVT_ABS",
}

PAGE_ALIGN = 4096        # arbitrary; only relative offsets matter
SECTION_GAP = 0x1000     # gap between sections in our fake layout


# ---------------------------------------------------------------------------

class LoaderError(Exception):
    pass


def simulate(ko_path: Path, verbose: bool = True) -> int:
    """Returns 0 on clean load, nonzero on first error."""
    errors = 0
    warnings = 0

    with open(ko_path, "rb") as fh:
        elf = ELFFile(fh)

        # --- Phase 1: assign fake runtime addresses to SHF_ALLOC sections ---
        # Mimics kernel's move_module() which allocates a single contiguous
        # region (separated into core/init halves) and assigns each section's
        # sh_addr to its slot.
        sec_base = {}      # section_idx -> fake runtime base
        next_addr = 0x80000000   # fake module-area base
        sections = list(elf.iter_sections())
        for i, sec in enumerate(sections):
            if sec["sh_flags"] & SH_FLAGS.SHF_ALLOC:
                align = max(sec["sh_addralign"], 1)
                next_addr = (next_addr + align - 1) & ~(align - 1)
                sec_base[i] = next_addr
                next_addr += sec["sh_size"]
                if verbose:
                    print(f"  alloc'd  [{i:2d}] {sec.name:25s} "
                          f"runtime=0x{sec_base[i]:08x} size=0x{sec['sh_size']:x}")
                next_addr += SECTION_GAP

        # Read the raw section contents so we can apply relocations
        sec_content = {}
        for i, sec in enumerate(sections):
            if sec["sh_type"] != "SHT_NOBITS":
                sec_content[i] = bytearray(sec.data())

        # --- Phase 2: simplify_symbols (resolve each symbol's runtime address) ---
        symtab = next((s for s in sections if isinstance(s, SymbolTableSection)
                       and s.name == ".symtab"), None)
        if symtab is None:
            raise LoaderError(".symtab missing")
        symtab_idx = sections.index(symtab)

        # Build a parallel list of resolved symbol entries
        resolved_syms = []      # list of (name, runtime_value, shndx, info)
        for i, sym in enumerate(symtab.iter_symbols()):
            name = sym.name
            shndx = sym["st_shndx"]
            value = sym["st_value"]

            # Special shndx values per ELF spec
            if isinstance(shndx, str):  # pyelftools returns 'SHN_*' as strings
                if shndx == "SHN_UNDEF":
                    # In real kernel: looked up in cross-module symtab.
                    # Here: leave value=0 and warn if it's a non-empty name.
                    if name and not name.startswith("$"):
                        warnings += 1
                        if verbose:
                            print(f"    [sym {i:4d} '{name}'] UND — "
                                  f"unresolved (real kernel would resolve via kallsyms)")
                    resolved_syms.append((name, 0, shndx, sym["st_info"]))
                    continue
                elif shndx == "SHN_ABS":
                    resolved_syms.append((name, value, shndx, sym["st_info"]))
                    continue
                elif shndx == "SHN_COMMON":
                    errors += 1
                    print(f"  ERROR: SHN_COMMON symbol '{name}' "
                          f"(real loader would reject; needs -fno-common)")
                    resolved_syms.append((name, 0, shndx, sym["st_info"]))
                    continue
                else:
                    resolved_syms.append((name, 0, shndx, sym["st_info"]))
                    continue
            # numeric shndx
            base = sec_base.get(shndx, 0)
            if shndx not in sec_base and shndx != 0:
                # symbol points into a section that wasn't SHF_ALLOC
                # That's actually fine for SECTION-type symbols pointing into
                # debug sections, but for FUNC/OBJECT symbols it'd be a bug.
                if sym["st_info"]["type"] in ("STT_FUNC", "STT_OBJECT"):
                    warnings += 1
                    if verbose:
                        print(f"    [sym {i:4d} '{name}'] points into non-ALLOC "
                              f"section {shndx} — st_value stays 0")
            resolved_syms.append((name, value + base, shndx, sym["st_info"]))

        # --- Phase 3: apply each .rel.* section ---
        for ri, relsec in enumerate(sections):
            if not isinstance(relsec, RelocationSection):
                continue
            target_idx = relsec["sh_info"]
            if target_idx >= len(sections):
                errors += 1
                print(f"  ERROR: rel section '{relsec.name}' sh_info={target_idx} "
                      f"out of range (e_shnum={len(sections)})")
                continue
            dstsec = sections[target_idx]
            dst_alloc = (dstsec["sh_flags"] & SH_FLAGS.SHF_ALLOC) != 0
            if not dst_alloc:
                # kernel skips rel sections targeting non-ALLOC sections — fine
                continue
            if target_idx not in sec_content:
                continue

            dstbuf = sec_content[target_idx]
            dst_base = sec_base[target_idx]
            dst_size = dstsec["sh_size"]

            if verbose:
                print(f"\n  Applying {relsec.name} ({relsec.num_relocations()} entries) "
                      f"-> {dstsec.name} @ 0x{dst_base:08x}")

            for k, rel in enumerate(relsec.iter_relocations()):
                r_offset = rel["r_offset"]
                r_info = rel["r_info"]
                r_type = rel["r_info_type"]
                sym_idx = rel["r_info_sym"]

                # bounds check (matches kernel apply_relocate)
                if r_offset > dst_size - 4:
                    errors += 1
                    print(f"  ERROR: {relsec.name}[{k}]: r_offset=0x{r_offset:x} "
                          f"> dstsec.size-4=0x{dst_size-4:x}")
                    continue

                # symbol index bounds check
                if sym_idx < 0 or sym_idx >= len(resolved_syms):
                    errors += 1
                    print(f"  ERROR: {relsec.name}[{k}]: bad sym idx {sym_idx}")
                    continue
                sym_name, sym_value, sym_shndx, sym_info = resolved_syms[sym_idx]

                # Skip unresolved UND symbols — would be an error if real
                # insmod, but we can't simulate cross-module lookup here.
                if sym_shndx == "SHN_UNDEF" and sym_value == 0 and sym_name:
                    # only warn; don't apply (would corrupt insn)
                    continue

                loc = dst_base + r_offset
                # read 4-byte instruction at loc
                opcode = struct.unpack_from("<I", dstbuf, r_offset)[0]

                err = apply_arm_reloc(
                    r_type, opcode, sym_value, loc,
                )

                if isinstance(err, str):
                    errors += 1
                    print(f"  ERROR: {relsec.name}[{k}] type={R_NAMES.get(r_type, r_type)} "
                          f"sym='{sym_name}'@0x{sym_value:08x} "
                          f"loc=0x{loc:08x}: {err}")
                    continue

                # err is the new opcode (or unchanged); write back
                struct.pack_into("<I", dstbuf, r_offset, err)

                if verbose:
                    rname = R_NAMES.get(r_type, f"type{r_type}")
                    print(f"    [{k:3d}] {rname:20s} +0x{r_offset:04x} "
                          f"sym='{sym_name}'@0x{sym_value:08x} "
                          f"insn 0x{opcode:08x} -> 0x{err:08x}")

        # --- Phase 4: dump the resolved .text.splice if present ---
        ts_sec = next((s for s in sections if s.name == ".text.splice"), None)
        if ts_sec is not None:
            ts_idx = sections.index(ts_sec)
            ts_base = sec_base.get(ts_idx, 0)
            print(f"\n  === Resolved .text.splice @ 0x{ts_base:08x} ===")
            buf = sec_content[ts_idx]
            for off in range(0, len(buf), 4):
                w = struct.unpack_from("<I", buf, off)[0]
                print(f"    +0x{off:04x}: 0x{w:08x}")

        # Dump .data.splice symbols + resolved addresses
        ds_sec = next((s for s in sections if s.name == ".data.splice"), None)
        if ds_sec is not None:
            ds_idx = sections.index(ds_sec)
            ds_base = sec_base.get(ds_idx, 0)
            print(f"\n  === .data.splice runtime base = 0x{ds_base:08x} ===")
            for i, (n, v, shx, _) in enumerate(resolved_syms):
                if n and "_splice_slot_" in n:
                    print(f"    {n:50s} -> 0x{v:08x}")

    print(f"\n=== Summary: {errors} error(s), {warnings} warning(s) ===")
    return errors


# ---------------------------------------------------------------------------
# ARM relocation application — mirrors arch/arm/kernel/module.c apply_relocate
# ---------------------------------------------------------------------------

def apply_arm_reloc(r_type: int, opcode: int, sym_value: int, loc: int):
    """Returns new opcode (int) on success, or an error string."""
    if r_type == R_ARM_NONE:
        return opcode

    if r_type in (R_ARM_ABS32, R_ARM_TARGET1):
        return (opcode + sym_value) & 0xffffffff

    if r_type in (R_ARM_PC24, R_ARM_CALL, R_ARM_JUMP24):
        if sym_value & 3:
            return f"unsupported interworking call (target not 4-byte aligned: 0x{sym_value:x})"
        # extract existing addend
        offset = (opcode & 0x00ffffff) << 2
        if offset & 0x02000000:
            offset -= 0x04000000
        # apply: offset = A + S - P
        offset = (offset + sym_value - loc) & 0xffffffff
        # sign-extend back into 32-bit signed
        if offset & 0x80000000:
            soffset = offset - 0x100000000
        else:
            soffset = offset
        if soffset <= -0x02000000 or soffset >= 0x02000000:
            return f"relocation out of range (offset=0x{soffset:x})"
        new_imm = (offset >> 2) & 0x00ffffff
        return (opcode & 0xff000000) | new_imm

    if r_type == R_ARM_V4BX:
        return (opcode & 0xf000000f) | 0x01a0f000

    if r_type == R_ARM_PREL31:
        offset = (opcode + sym_value - loc) & 0x7fffffff
        return offset

    if r_type in (R_ARM_MOVW_ABS_NC, R_ARM_MOVT_ABS):
        # extract existing 16-bit imm: top 4 bits at [19:16], low 12 at [11:0]
        tmp = opcode
        offset = ((tmp & 0xf0000) >> 4) | (tmp & 0xfff)
        # sign-extend
        offset = ((offset ^ 0x8000) - 0x8000) & 0xffffffff
        offset = (offset + sym_value) & 0xffffffff
        if r_type == R_ARM_MOVT_ABS:
            offset >>= 16
        tmp &= 0xfff0f000
        tmp |= ((offset & 0xf000) << 4) | (offset & 0x0fff)
        return tmp

    return f"unknown relocation type {r_type}"


# ---------------------------------------------------------------------------

def main():
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(2)
    ko = Path(sys.argv[1])
    if not ko.is_file():
        sys.exit(f"input not found: {ko}")
    errors = simulate(ko)
    sys.exit(1 if errors else 0)


if __name__ == "__main__":
    main()
