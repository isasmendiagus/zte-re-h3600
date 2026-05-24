"""NAND layout + BootPara header constants for the ZTE H3600 (ZX279128S).

Single source of truth for NAND region offsets and BootPara header field
offsets. Anything that flashes the device should pull values from here
instead of hardcoding magic numbers.

Layout references:
  - docs/NAND_LAYOUT_AND_BOOT.md           (RE'd header layout + boot flow)
  - tasks/00.04.flash-tool/README.md       (recipes, safety invariants, primer on cspstart)
"""
from dataclasses import dataclass

# ---------------------------------------------------------------------------
# NAND geometry (ESMT F50L1G41LB SPI NAND, 128 MiB)
# ---------------------------------------------------------------------------

NAND_PAGE        = 0x800        # 2 KiB
NAND_ERASE_BLOCK = 0x20000      # 128 KiB
NAND_SIZE        = 0x08000000   # 128 MiB

# Forbidden region — bricking this needs an external SPI programmer.
BOOTLOADER_OFFSET = 0x00000000
BOOTLOADER_SIZE   = 0x000c0000  # U-Boot binary + ZTE pre-header (768 KiB)

# Standard scratch address used by U-Boot tftp + nand commands.
RAM_LOAD_ADDR = 0x42000000

# ---------------------------------------------------------------------------
# Timing estimators — for sizing prompt-wait timeouts in uboot_flash.py.
#
# These are upper-bound estimates only. The actual flow advances the moment
# U-Boot prints `=>`; the timeout only matters when something hangs. So we
# pad generously rather than tightly. Constants below come from observed
# behavior on this device with a margin for slow days.
# ---------------------------------------------------------------------------

# TFTP throughput floor. Observed ~1 MiB/s with tftpblocksize=1468; we use
# 100 KiB/s here so that timeout estimates survive a 10× slowdown.
_TFTP_FLOOR_KIB_PER_SEC  = 100
_TFTP_SETUP_OVERHEAD_SEC = 10

# NAND erase pace. Datasheet typ 2 ms per 128 KiB block, max 10 ms; U-Boot
# adds parser + prompt overhead. 100 ms/block is comfortable.
_ERASE_MS_PER_BLOCK = 100
_ERASE_OVERHEAD_SEC = 5

# NAND write pace. Datasheet typ 700 us per 2 KiB page; in practice
# `nand write` of ~11 MiB takes ~30 s end-to-end (~3 s/MiB). 5 s/MiB
# leaves margin.
_WRITE_SEC_PER_MIB  = 5
_WRITE_OVERHEAD_SEC = 10


def estimate_tftp_seconds(size_bytes: int) -> int:
    """Upper-bound seconds for a TFTP transfer of size_bytes."""
    return max(30, size_bytes // (_TFTP_FLOOR_KIB_PER_SEC * 1024)
               + _TFTP_SETUP_OVERHEAD_SEC)


def estimate_erase_seconds(size_bytes: int) -> int:
    """Upper-bound seconds for `nand erase` of size_bytes."""
    blocks = (size_bytes + NAND_ERASE_BLOCK - 1) // NAND_ERASE_BLOCK
    return max(10, (blocks * _ERASE_MS_PER_BLOCK + 999) // 1000
               + _ERASE_OVERHEAD_SEC)


def estimate_write_seconds(size_bytes: int) -> int:
    """Upper-bound seconds for `nand write` of size_bytes."""
    mib = (size_bytes + ((1 << 20) - 1)) >> 20
    return max(20, mib * _WRITE_SEC_PER_MIB + _WRITE_OVERHEAD_SEC)


# ---------------------------------------------------------------------------
# Per-slot layout
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class SlotLayout:
    name: str                    # "A" or "B"
    kernel_offset: int           # NAND offset where cspstart looks for the kernel
    kernel_max_size: int         # max writable region before bumping into header
    rootfs_offset: int           # NAND offset of the rootfs partition
    rootfs_size: int             # rootfs region size
    header_offset: int           # NAND offset of the 128 KiB BootPara header
    header_size: int             # always equal to NAND_ERASE_BLOCK


SLOT_A = SlotLayout(
    name            = "A",
    kernel_offset   = 0x00700000,
    kernel_max_size = 0x01980000,
    rootfs_offset   = 0x00a60000,
    rootfs_size     = 0x01620000,
    header_offset   = 0x02080000,
    header_size     = 0x00020000,
)

SLOT_B = SlotLayout(
    name            = "B",
    kernel_offset   = 0x02700000,
    kernel_max_size = 0x01900000,
    rootfs_offset   = 0x02a60000,
    rootfs_size     = 0x01620000,
    header_offset   = 0x04080000,
    header_size     = 0x00020000,
)


def get_slot(name: str) -> SlotLayout:
    n = name.upper()
    if n == "A":
        return SLOT_A
    if n == "B":
        return SLOT_B
    raise ValueError(f"slot must be A or B, got {name!r}")


# ---------------------------------------------------------------------------
# BootPara header field offsets (inside the 128 KiB header partition)
# ---------------------------------------------------------------------------

HDR_KERNEL_SIZE_OFF   = 0x34   # u32 LE — bytes cspstart will CRC starting at kernel_offset
HDR_KERNEL_CRC_OFF    = 0x3c   # u32 LE — zlib.crc32 of the CRC region (strict check)
HDR_ROOTFS_SIZE_OFF   = 0x40   # u32 LE — rootfs region size (stock = 0x01620000)
HDR_ROOTFS_CRC_OFF    = 0x48   # u32 LE — zlib.crc32 of rootfs (lenient w/ JFFS2 fallback)
HDR_KERNEL_OFF_A      = 0x4c   # u32 LE — slot A kernel base address
HDR_KERNEL_OFF_B      = 0x5c   # u32 LE — slot B kernel base address
HDR_BOARD_NAME_OFF    = 0x70   # 24-byte ASCII (e.g. " H1600V9\0...")
HDR_SELF_CRC_OFF      = 0xa4   # u32 LE — zlib.crc32(header[0:0xa4])
HDR_SELF_CRC_END      = 0xa4   # the self-CRC covers bytes [0, 0xa4)
HDR_SECONDARY_MAGIC_OFF = 0xf4 # 16 bytes — cspstart's header-locator magic

HDR_SECONDARY_MAGIC = bytes.fromhex(
    "33333333" "66666666" "99999999" "cccccccc"
)
assert len(HDR_SECONDARY_MAGIC) == 16

# ---------------------------------------------------------------------------
# Kernel region: 32-byte ZTE wrapper that lives at offset 0 of the kernel
# partition (NOT in the header). cspstart's NAND scan finds this magic to
# locate the kernel. Built by build_slotA.py and prepended to the uImage.
# Provided here only for documentation/reference; the flash tool does not
# build it.
# ---------------------------------------------------------------------------

ZTE_KERNEL_WRAPPER = bytes.fromhex(
    "33333333" "cccccccc" "88888888" "dddddddd"
) + b"\xff" * 16
assert len(ZTE_KERNEL_WRAPPER) == 32
