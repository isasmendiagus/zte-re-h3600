"""Read, patch, and write BootPara header bytes for the ZTE H3600.

The BootPara header is a 128 KiB partition (one per slot) that cspstart
reads at boot to validate a slot's kernel+rootfs before booting it. Only
the first ~0xa8 bytes are meaningful structured data; the rest is padding
plus a secondary 16-byte magic at 0xf4.

This module never opens UART or touches NAND — it operates purely on
bytes in memory. A typical flash workflow is:

    hdr = read_slot_header_from_file(Path("ext/h3600_nand_full.bin"), SLOT_A)
    new = patch_kernel(hdr, kernel_size=padded_size, kernel_crc=csp_crc(padded))
    # then write `new` to slot.header_offset via lib.uboot_flash

Layout reference: docs/NAND_LAYOUT_AND_BOOT.md
"""
import struct
import zlib
from pathlib import Path

import nand_layout as nl


# ---------------------------------------------------------------------------
# Header read
# ---------------------------------------------------------------------------

def read_slot_header(nand_dump: bytes, slot: nl.SlotLayout) -> bytes:
    """Slice the 128 KiB header partition for `slot` from a full-NAND dump."""
    end = slot.header_offset + slot.header_size
    if len(nand_dump) < end:
        raise ValueError(
            f"NAND dump too short: need {end:#x} bytes for slot {slot.name} "
            f"header, got {len(nand_dump):#x}"
        )
    return nand_dump[slot.header_offset:end]


def read_slot_header_from_file(nand_dump_path: Path, slot: nl.SlotLayout) -> bytes:
    return read_slot_header(Path(nand_dump_path).read_bytes(), slot)


# ---------------------------------------------------------------------------
# Header patch
# ---------------------------------------------------------------------------

def _patch_u32(hdr: bytearray, offset: int, value: int) -> None:
    struct.pack_into("<I", hdr, offset, value & 0xffffffff)


def _read_u32(hdr: bytes, offset: int) -> int:
    return struct.unpack_from("<I", hdr, offset)[0]


def recompute_self_crc(hdr: bytearray) -> int:
    """Recompute and store the self-CRC at 0xa4 over header[0..0xa4]. Returns the CRC."""
    crc = zlib.crc32(bytes(hdr[:nl.HDR_SELF_CRC_END])) & 0xffffffff
    _patch_u32(hdr, nl.HDR_SELF_CRC_OFF, crc)
    return crc


def patch_kernel(hdr: bytes, *, kernel_size: int, kernel_crc: int) -> bytes:
    """Return a copy of `hdr` with kernel size/CRC patched and self-CRC refreshed."""
    out = bytearray(hdr)
    _patch_u32(out, nl.HDR_KERNEL_SIZE_OFF, kernel_size)
    _patch_u32(out, nl.HDR_KERNEL_CRC_OFF,  kernel_crc)
    recompute_self_crc(out)
    return bytes(out)


def patch_rootfs(hdr: bytes, *, rootfs_crc: int) -> bytes:
    """Return a copy of `hdr` with rootfs CRC patched and self-CRC refreshed."""
    out = bytearray(hdr)
    _patch_u32(out, nl.HDR_ROOTFS_CRC_OFF, rootfs_crc)
    recompute_self_crc(out)
    return bytes(out)


def patch_both(hdr: bytes, *, kernel_size: int, kernel_crc: int,
               rootfs_crc: int) -> bytes:
    """Patch kernel size/CRC + rootfs CRC in one shot. Single self-CRC recompute."""
    out = bytearray(hdr)
    _patch_u32(out, nl.HDR_KERNEL_SIZE_OFF, kernel_size)
    _patch_u32(out, nl.HDR_KERNEL_CRC_OFF,  kernel_crc)
    _patch_u32(out, nl.HDR_ROOTFS_CRC_OFF,  rootfs_crc)
    recompute_self_crc(out)
    return bytes(out)


# ---------------------------------------------------------------------------
# CRC + padding helpers used by callers
# ---------------------------------------------------------------------------

def csp_crc(data: bytes) -> int:
    """CSP CRC = standard zlib.crc32 (= CRC32 IEEE).

    U-Boot's csp_crc log prints (A, ~A) — the value to STORE is A, not ~A.
    We've burned a full day on this exact gotcha; do not "fix" it.
    """
    return zlib.crc32(data) & 0xffffffff


def pad_with_ff(data: bytes, target_size: int) -> bytes:
    """Pad data with 0xff to exactly target_size.

    This is mandatory before computing the CRC that gets stored in the
    header. nand-write reads exactly `size` bytes from RAM regardless of
    what TFTP loaded; if you don't pre-pad, the trailing bytes on NAND
    are RAM garbage and the stored CRC won't match. See LEARNED.md.
    """
    if len(data) > target_size:
        raise ValueError(
            f"data ({len(data):#x} B) exceeds target ({target_size:#x} B)"
        )
    return data + b"\xff" * (target_size - len(data))


def round_up_to_erase_block(size: int) -> int:
    """Round size up to a NAND erase-block multiple (128 KiB)."""
    blk = nl.NAND_ERASE_BLOCK
    return ((size + blk - 1) // blk) * blk


# ---------------------------------------------------------------------------
# Debug/dry-run summary
# ---------------------------------------------------------------------------

def describe_header(hdr: bytes) -> str:
    """One-line summary of a header's key fields. For dry-run + debug output."""
    k_size = _read_u32(hdr, nl.HDR_KERNEL_SIZE_OFF)
    k_crc  = _read_u32(hdr, nl.HDR_KERNEL_CRC_OFF)
    r_size = _read_u32(hdr, nl.HDR_ROOTFS_SIZE_OFF)
    r_crc  = _read_u32(hdr, nl.HDR_ROOTFS_CRC_OFF)
    sc     = _read_u32(hdr, nl.HDR_SELF_CRC_OFF)
    return (f"kernel size=0x{k_size:08x} crc=0x{k_crc:08x}  "
            f"rootfs size=0x{r_size:08x} crc=0x{r_crc:08x}  "
            f"self=0x{sc:08x}")
