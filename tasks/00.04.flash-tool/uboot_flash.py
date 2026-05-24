"""Drive U-Boot via UART to TFTP + nand erase/write at given offsets.

Wraps lib/uart.py's `_do_reset_then` (the DTR-reset + boot-prompt drive
machinery already battle-tested by the 5+ existing flash scripts) so the
unified flasher doesn't re-implement that code.

A "step" is one (tftp_filename, nand_offset, write_size) triple. The
module composes a list of steps into the U-Boot command sequence:

    setenv ipaddr/serverip/tftpblocksize  (via _PREAMBLE)
    for each step:
        tftp <RAM_LOAD_ADDR> <filename>
        nand erase <offset> <size>
        nand write <RAM_LOAD_ADDR> <offset> <size>
    setenv autorun ""
    saveenv
    reset

Safety guards reject:
  - any write that overlaps the bootloader region
  - any write into slot B unless allow_slot_b=True
  - any write that runs past the end of NAND
"""
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Optional

# lib/uart.py is a sibling — assume it's on sys.path (callers add it).
import uart  # type: ignore

import nand_layout as nl


# ---------------------------------------------------------------------------
# A single TFTP-then-nand-write step
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class WriteStep:
    tftp_filename: str           # filename inside the TFTP serve dir
    nand_offset: int             # NAND offset to erase + write at
    write_size: int              # bytes to write (must be erase-block aligned)
    # Per-step timeouts — upper bounds for prompt-wait, NOT fixed sleeps.
    # If left None they're computed from write_size via nl.estimate_*().
    # Override only when you have device-specific knowledge.
    tftp_timeout:  Optional[int] = None
    erase_timeout: Optional[int] = None
    write_timeout: Optional[int] = None

    @property
    def tftp_t(self) -> int:
        return (self.tftp_timeout if self.tftp_timeout is not None
                else nl.estimate_tftp_seconds(self.write_size))

    @property
    def erase_t(self) -> int:
        return (self.erase_timeout if self.erase_timeout is not None
                else nl.estimate_erase_seconds(self.write_size))

    @property
    def write_t(self) -> int:
        return (self.write_timeout if self.write_timeout is not None
                else nl.estimate_write_seconds(self.write_size))


# ---------------------------------------------------------------------------
# Safety
# ---------------------------------------------------------------------------

def _check_safety(steps: Iterable[WriteStep], allow_slot_b: bool) -> None:
    bl_end = nl.BOOTLOADER_OFFSET + nl.BOOTLOADER_SIZE
    for s in steps:
        # 1. Bootloader is sacred.
        if s.nand_offset < bl_end:
            raise ValueError(
                f"refusing nand write at {s.nand_offset:#x}: overlaps bootloader "
                f"({nl.BOOTLOADER_OFFSET:#x}..{bl_end:#x}). Brick risk."
            )
        # 2. Slot B is the A/B recovery fallback. Opt-in only.
        if not allow_slot_b and s.nand_offset >= nl.SLOT_B.kernel_offset:
            raise ValueError(
                f"refusing nand write at {s.nand_offset:#x}: slot B region "
                f"({nl.SLOT_B.kernel_offset:#x}+). Pass allow_slot_b=True to "
                f"override — this disables A/B recovery."
            )
        # 3. Don't run off the end of NAND.
        if s.nand_offset + s.write_size > nl.NAND_SIZE:
            raise ValueError(
                f"write at {s.nand_offset:#x} + {s.write_size:#x} exceeds NAND "
                f"end ({nl.NAND_SIZE:#x})"
            )
        # 4. write_size must be erase-block aligned (else nand-erase complains).
        if s.write_size % nl.NAND_ERASE_BLOCK != 0:
            raise ValueError(
                f"write_size {s.write_size:#x} is not a multiple of "
                f"NAND_ERASE_BLOCK ({nl.NAND_ERASE_BLOCK:#x})"
            )


# ---------------------------------------------------------------------------
# Command sequence
# ---------------------------------------------------------------------------

def _build_sequence(steps: Iterable[WriteStep]) -> list:
    """Build the list of (cmd, wait) tuples for uart._do_reset_then.

    Wait values use the (pattern_bytes, timeout) form supported by
    _do_reset_then — we advance the moment U-Boot prints the `=>` prompt
    (= "ready for the next command"). Timeout is just an upper bound for
    the hang case; success advances instantly. Streaming output is
    mirrored to stdout the whole time so the user sees progress.

    Exception: `reset` doesn't print `=>` again (U-Boot reboots), so it
    uses a plain int (fixed-stream-window) wait to capture the post-reset
    boot log including cspstart's slot-validation verdict.
    """
    PROMPT_SHORT = (b"=>", 10)   # setenv / saveenv — finish in <1s normally
    cmds: list = []
    for s in steps:
        cmds.extend([
            (f"tftp 0x{nl.RAM_LOAD_ADDR:x} {s.tftp_filename}",
             (b"=>", s.tftp_t)),
            (f"nand erase 0x{s.nand_offset:x} 0x{s.write_size:x}",
             (b"=>", s.erase_t)),
            (f"nand write 0x{nl.RAM_LOAD_ADDR:x} 0x{s.nand_offset:x} "
             f"0x{s.write_size:x}",
             (b"=>", s.write_t)),
        ])
    # Clear any stray autorun, persist env, reboot.
    cmds.append(('setenv autorun ""', PROMPT_SHORT))
    cmds.append(("saveenv",           (b"=>", 15)))
    # Reset reboots U-Boot — no `=>` will reappear until the next prompt
    # cycle. Use a plain int wait to capture cspstart's verdict + early
    # boot. 60s covers cspstart + kernel + modules + early userspace on a
    # healthy boot; anything beyond that the caller verifies via SSH.
    cmds.append(("reset", 60))
    return cmds


# ---------------------------------------------------------------------------
# Top-level entry
# ---------------------------------------------------------------------------

def flash_steps(steps: list, *, allow_slot_b: bool = False,
                dry_run: bool = False) -> int:
    """Execute the given WriteSteps in one U-Boot session.

    Args:
      steps: list[WriteStep] in order.
      allow_slot_b: if False (default), refuse any write into slot B.
      dry_run: if True, print the command sequence and return without
               opening UART. Useful for verifying staged files before a
               real flash.

    Returns 0 on success, nonzero on failure.
    """
    _check_safety(steps, allow_slot_b)

    payload = _build_sequence(steps)
    full = uart._PREAMBLE + payload

    if dry_run:
        print("\nDRY RUN — would send the following after DTR reset + U-Boot prompt:\n")
        for cmd, wait in full:
            label = cmd if cmd else "(blank — wake prompt)"
            if isinstance(wait, tuple):
                pat, to = wait
                wlabel = f"wait pattern {pat!r} (≤{to:>3}s)"
            else:
                wlabel = f"stream {wait:>3}s"
            print(f"  [{wlabel:>30}]  {label}")
        print("\n(no UART opened, no bytes sent, no NAND touched)")
        return 0

    print(">>> Driving U-Boot. DTR-reset + watching for prompt...")
    return uart._do_reset_then(full) or 0
