#!/usr/bin/env python3
"""flash.py — unified ZTE H3600 NAND flasher.

Subcommands:
  kernel  --src FILE                    flash a kernel binary; patches header
  rootfs  --src FILE                    flash a rootfs binary; patches header
  both    --kernel F --rootfs F         flash both in one session; one header
  header  --src FILE                    flash a pre-built header file as-is

For kernel/rootfs/both: the matching slot's BootPara header is read from
the full-NAND backup (default: ext/h3600_nand_full.bin), only the changed
fields are patched (kernel_size/kernel_crc and/or rootfs_crc), the self-CRC
at 0xa4 is recomputed, and the new header is flashed alongside the content
in a single U-Boot session.

For header: the file is written as-is (no patching, no CRC math). Used for
surgical fixes / restores.

Safety:
  - never touches the bootloader region (0x0..0xc0000)
  - refuses to write slot B without --allow-slot-b
  - --dry-run stages files + prints commands without opening UART

See: tasks/00.04.flash-tool/README.md for the full design rationale.
"""
import argparse
import os
import socket
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent           # tasks/00.04.flash-tool/
REPO = HERE.parents[1]                           # ZTE/ (repo root)
sys.path.insert(0, str(HERE))                    # for sibling modules
sys.path.insert(0, str(REPO / "lib"))            # for uart.py (used by uboot_flash)

BRIDGE_SCRIPT = REPO / "tasks/00.04.02.uart-bridge/uart_bridge.py"
BRIDGE_DATA_PORT = 9999
BRIDGE_CTL_PORT  = 9998


def _bridge_alive(host="localhost", port=BRIDGE_DATA_PORT):
    """Return True if the uart_bridge daemon is reachable on this host."""
    try:
        with socket.create_connection((host, port), timeout=0.5) as s:
            s.close()
        return True
    except (OSError, ConnectionRefusedError):
        return False


def _ensure_bridge_running():
    """If --uart-tcp is set but no bridge is up yet, spawn one detached.
    Idempotent: returns immediately if a bridge is already reachable.
    """
    if _bridge_alive():
        print("[flash] uart_bridge already running on tcp/9999 — using it")
        return
    if not BRIDGE_SCRIPT.is_file():
        sys.exit(f"--uart-tcp requested but bridge script not found at "
                 f"{BRIDGE_SCRIPT}")
    print(f"[flash] starting uart_bridge daemon ({BRIDGE_SCRIPT})...")
    # Spawn detached so it survives this flash invocation.
    log = open("/tmp/uart_bridge_daemon.log", "ab")
    proc = subprocess.Popen(
        [sys.executable, str(BRIDGE_SCRIPT)],
        stdout=log, stderr=subprocess.STDOUT,
        stdin=subprocess.DEVNULL,
        start_new_session=True,
    )
    # Wait up to ~3s for the bridge to bind its ports.
    for _ in range(30):
        if _bridge_alive():
            print(f"[flash] uart_bridge up (PID {proc.pid}); "
                  f"persistent for the rest of the session")
            print(f"[flash] live monitor:  tail -f /tmp/uart_bridge.log "
                  f"  OR  nc localhost {BRIDGE_DATA_PORT}")
            return
        time.sleep(0.1)
    sys.exit("[flash] uart_bridge didn't come up within 3s; see "
             "/tmp/uart_bridge_daemon.log")


import nand_layout as nl
import bootpara as bp
from uboot_flash import WriteStep, flash_steps


DEFAULT_TFTP_DIR  = REPO / "tftp"
DEFAULT_NAND_DUMP = REPO / "ext" / "h3600_nand_full.bin"


# ---------------------------------------------------------------------------
# Argparse setup
# ---------------------------------------------------------------------------

def _add_common_args(ap: argparse.ArgumentParser) -> None:
    ap.add_argument("--slot", choices=["A", "B"], default="A",
                    help="which slot to flash (default: A)")
    ap.add_argument("--allow-slot-b", action="store_true",
                    help="required for any slot B write (disables A/B recovery)")
    ap.add_argument("--tftp-dir", type=Path, default=DEFAULT_TFTP_DIR,
                    help=f"TFTP serve dir for staging (default: "
                         f"{DEFAULT_TFTP_DIR.relative_to(REPO)})")
    ap.add_argument("--nand-dump", type=Path, default=DEFAULT_NAND_DUMP,
                    help=f"full NAND backup used as BootPara header base "
                         f"(default: {DEFAULT_NAND_DUMP.relative_to(REPO)})")
    ap.add_argument("--dry-run", action="store_true",
                    help="stage files + print commands; do NOT open UART")
    ap.add_argument("--direct-uart", action="store_true",
                    help="bypass the uart_bridge daemon and open /dev/ttyUSB0 "
                         "directly. By default flash.py routes UART through the "
                         "bridge (auto-starting it if needed) so other tools can "
                         "monitor in parallel via `nc localhost 9999` or "
                         "`tail -f /tmp/uart_bridge.log`. Use this flag for "
                         "low-level debugging when the bridge itself is broken.")


# ---------------------------------------------------------------------------
# Subcommands
# ---------------------------------------------------------------------------

def _stage(tftp_dir: Path, name: str, data: bytes) -> Path:
    p = tftp_dir / name
    p.write_bytes(data)
    print(f"  staged: {p} ({len(data):,} bytes)")
    return p


def cmd_kernel(args) -> int:
    """Flash a kernel binary (ZTE-wrapped uImage) to a slot's kernel region.

    CRC scope (verified against stock NAND dump 2026-05-23):
      cspstart computes zlib.crc32(NAND[kernel_off + 32 : kernel_off + 32 + kernel_size]).
      i.e. it SKIPS the 32-byte ZTE wrapper, then CRCs exactly kernel_size bytes.

      To make our stored CRC match what cspstart will compute, we therefore:
        kernel_size = (full padded blob size) - 32
        kernel_crc  = zlib.crc32(padded[32 : padded_total])
      which means cspstart CRCs everything we wrote *except* the 32-byte wrapper.
    """
    slot = nl.get_slot(args.slot)
    src = args.src.read_bytes()

    wrapper_len = len(nl.ZTE_KERNEL_WRAPPER)  # 32
    if len(src) <= wrapper_len:
        raise SystemExit(
            f"src too small ({len(src)} B) — must include the {wrapper_len}-byte "
            f"ZTE wrapper at offset 0 followed by a uImage"
        )

    padded_total = bp.round_up_to_erase_block(len(src))
    if padded_total > slot.kernel_max_size:
        raise SystemExit(
            f"padded kernel ({padded_total:#x}) exceeds slot {slot.name} kernel "
            f"max ({slot.kernel_max_size:#x})"
        )
    padded = bp.pad_with_ff(src, padded_total)

    kernel_size = padded_total - wrapper_len            # bytes cspstart will CRC
    kernel_crc  = bp.csp_crc(padded[wrapper_len:padded_total])  # = csp_crc(padded[32:])

    print(f"  src: {len(src):,} B  →  padded to {padded_total:#x} ({padded_total:,} B)")
    print(f"  kernel_size  (= padded - 32): {kernel_size:#x}")
    print(f"  kernel_crc   (= csp_crc of padded[32:]): 0x{kernel_crc:08x}")

    base_hdr = bp.read_slot_header_from_file(args.nand_dump, slot)
    new_hdr  = bp.patch_kernel(base_hdr, kernel_size=kernel_size, kernel_crc=kernel_crc)
    print(f"  base hdr:   {bp.describe_header(base_hdr)}")
    print(f"  new  hdr:   {bp.describe_header(new_hdr)}")

    args.tftp_dir.mkdir(parents=True, exist_ok=True)
    kernel_name = f"slot{slot.name}_kernel.bin"
    header_name = f"slot{slot.name}_header.bin"
    _stage(args.tftp_dir, kernel_name, padded)
    _stage(args.tftp_dir, header_name, new_hdr)

    steps = [
        WriteStep(tftp_filename=kernel_name,
                  nand_offset=slot.kernel_offset,
                  write_size=padded_total),
        WriteStep(tftp_filename=header_name,
                  nand_offset=slot.header_offset,
                  write_size=slot.header_size),
    ]
    return flash_steps(steps, allow_slot_b=args.allow_slot_b, dry_run=args.dry_run)


def cmd_rootfs(args) -> int:
    slot = nl.get_slot(args.slot)
    src = args.src.read_bytes()

    if len(src) > slot.rootfs_size:
        raise SystemExit(
            f"rootfs ({len(src):#x}) exceeds slot {slot.name} rootfs region "
            f"({slot.rootfs_size:#x})"
        )
    if len(src) < slot.rootfs_size:
        print(f"  padding rootfs {len(src):#x} → {slot.rootfs_size:#x} with 0xff")
    padded = bp.pad_with_ff(src, slot.rootfs_size)
    rootfs_crc = bp.csp_crc(padded)
    print(f"  rootfs: {len(src):,} B → {slot.rootfs_size:,} B, crc=0x{rootfs_crc:08x}")

    base_hdr = bp.read_slot_header_from_file(args.nand_dump, slot)
    new_hdr  = bp.patch_rootfs(base_hdr, rootfs_crc=rootfs_crc)
    print(f"  base hdr:   {bp.describe_header(base_hdr)}")
    print(f"  new  hdr:   {bp.describe_header(new_hdr)}")

    args.tftp_dir.mkdir(parents=True, exist_ok=True)
    rootfs_name = f"slot{slot.name}_rootfs.bin"
    header_name = f"slot{slot.name}_header.bin"
    _stage(args.tftp_dir, rootfs_name, padded)
    _stage(args.tftp_dir, header_name, new_hdr)

    steps = [
        WriteStep(tftp_filename=rootfs_name,
                  nand_offset=slot.rootfs_offset,
                  write_size=slot.rootfs_size),
        WriteStep(tftp_filename=header_name,
                  nand_offset=slot.header_offset,
                  write_size=slot.header_size),
    ]
    return flash_steps(steps, allow_slot_b=args.allow_slot_b, dry_run=args.dry_run)


def cmd_both(args) -> int:
    slot = nl.get_slot(args.slot)
    wrapper_len = len(nl.ZTE_KERNEL_WRAPPER)

    # Kernel — same CRC scope rule as cmd_kernel (skip wrapper, kernel_size = padded - 32).
    k_src = args.kernel.read_bytes()
    if len(k_src) <= wrapper_len:
        raise SystemExit(
            f"kernel src too small ({len(k_src)} B) — must include the "
            f"{wrapper_len}-byte ZTE wrapper at offset 0"
        )
    k_padded_total = bp.round_up_to_erase_block(len(k_src))
    if k_padded_total > slot.kernel_max_size:
        raise SystemExit(
            f"padded kernel ({k_padded_total:#x}) exceeds slot {slot.name} kernel "
            f"max ({slot.kernel_max_size:#x})"
        )
    k_padded = bp.pad_with_ff(k_src, k_padded_total)
    k_size = k_padded_total - wrapper_len
    k_crc  = bp.csp_crc(k_padded[wrapper_len:k_padded_total])
    print(f"  kernel: {len(k_src):,} B → padded {k_padded_total:#x}, "
          f"kernel_size={k_size:#x}, crc=0x{k_crc:08x}")

    # Rootfs
    r_src = args.rootfs.read_bytes()
    if len(r_src) > slot.rootfs_size:
        raise SystemExit(
            f"rootfs ({len(r_src):#x}) exceeds slot rootfs region "
            f"({slot.rootfs_size:#x})"
        )
    r_padded = bp.pad_with_ff(r_src, slot.rootfs_size)
    r_crc = bp.csp_crc(r_padded)
    print(f"  rootfs: {len(r_src):,} B → {slot.rootfs_size:,} B, crc=0x{r_crc:08x}")

    # Header
    base_hdr = bp.read_slot_header_from_file(args.nand_dump, slot)
    new_hdr  = bp.patch_both(base_hdr, kernel_size=k_size,
                             kernel_crc=k_crc, rootfs_crc=r_crc)
    print(f"  base hdr:   {bp.describe_header(base_hdr)}")
    print(f"  new  hdr:   {bp.describe_header(new_hdr)}")

    args.tftp_dir.mkdir(parents=True, exist_ok=True)
    k_name = f"slot{slot.name}_kernel.bin"
    r_name = f"slot{slot.name}_rootfs.bin"
    h_name = f"slot{slot.name}_header.bin"
    _stage(args.tftp_dir, k_name, k_padded)
    _stage(args.tftp_dir, r_name, r_padded)
    _stage(args.tftp_dir, h_name, new_hdr)

    steps = [
        WriteStep(tftp_filename=k_name,
                  nand_offset=slot.kernel_offset,
                  write_size=k_padded_total),
        WriteStep(tftp_filename=r_name,
                  nand_offset=slot.rootfs_offset,
                  write_size=slot.rootfs_size),
        WriteStep(tftp_filename=h_name,
                  nand_offset=slot.header_offset,
                  write_size=slot.header_size),
    ]
    return flash_steps(steps, allow_slot_b=args.allow_slot_b, dry_run=args.dry_run)


def cmd_raw(args) -> int:
    """Write any file to any NAND offset. No header, no CRC math, no slot.

    The escape hatch for custom layouts (OpenWRT-style squashfs/UBIFS at
    arbitrary offsets, script-as-kernel staging, etc.). The other
    subcommands maintain cspstart's BootPara contract; this one does NOT.

    Safety:
      - Bootloader region (0x0..0xc0000) is UNCONDITIONALLY forbidden
        (brick risk).
      - Everything else is allowed without opt-in flags. The whole point
        of `raw` is full-NAND flexibility for custom layouts that don't
        use cspstart's A/B slot model.
      - This means raw CAN overwrite slot B (= sacrifices A/B recovery).
        Use deliberately.
    """
    src = args.src.read_bytes()
    padded_size = bp.round_up_to_erase_block(len(src))
    padded = bp.pad_with_ff(src, padded_size)

    if args.offset % nl.NAND_ERASE_BLOCK != 0:
        raise SystemExit(
            f"--offset 0x{args.offset:x} is not aligned to NAND erase block "
            f"({nl.NAND_ERASE_BLOCK:#x}). nand-erase only operates on full blocks."
        )

    print(f"  src: {len(src):,} B → padded to {padded_size:#x} ({padded_size:,} B)")
    print(f"  target NAND offset: 0x{args.offset:x}")
    print(f"  will erase + write {padded_size:#x} bytes at 0x{args.offset:x}")
    if args.offset >= nl.SLOT_B.kernel_offset:
        print(f"  ⚠ this write enters slot B region "
              f"({nl.SLOT_B.kernel_offset:#x}+) — A/B recovery affected")

    args.tftp_dir.mkdir(parents=True, exist_ok=True)
    name = f"raw_0x{args.offset:08x}.bin"
    _stage(args.tftp_dir, name, padded)

    steps = [
        WriteStep(tftp_filename=name,
                  nand_offset=args.offset,
                  write_size=padded_size),
    ]
    # raw unconditionally allows the slot B region. Bootloader guard in
    # _check_safety still blocks anything below 0xc0000.
    return flash_steps(steps, allow_slot_b=True, dry_run=args.dry_run)


def cmd_header(args) -> int:
    slot = nl.get_slot(args.slot)
    hdr = args.src.read_bytes()
    if len(hdr) != slot.header_size:
        raise SystemExit(
            f"header file size ({len(hdr):#x}) must equal slot header size "
            f"({slot.header_size:#x})"
        )

    args.tftp_dir.mkdir(parents=True, exist_ok=True)
    h_name = f"slot{slot.name}_header.bin"
    _stage(args.tftp_dir, h_name, hdr)
    print(f"  header:     {bp.describe_header(hdr)}")

    steps = [
        WriteStep(tftp_filename=h_name,
                  nand_offset=slot.header_offset,
                  write_size=slot.header_size),
    ]
    return flash_steps(steps, allow_slot_b=args.allow_slot_b, dry_run=args.dry_run)


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------

def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__.split("\n\n", 1)[0],
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    sub = ap.add_subparsers(dest="subcmd", required=True, metavar="SUBCMD")

    k = sub.add_parser("kernel", help="flash a kernel binary (patches header)")
    k.add_argument("--src", type=Path, required=True,
                   help="kernel binary (ZTE-wrapped uImage, NOT a raw zImage)")
    _add_common_args(k)
    k.set_defaults(func=cmd_kernel)

    r = sub.add_parser("rootfs", help="flash a rootfs binary (patches header)")
    r.add_argument("--src", type=Path, required=True,
                   help="rootfs binary (AES-128-ECB encrypted JFFS2 for AES slots)")
    _add_common_args(r)
    r.set_defaults(func=cmd_rootfs)

    b = sub.add_parser("both", help="flash kernel + rootfs (single header patch)")
    b.add_argument("--kernel", type=Path, required=True)
    b.add_argument("--rootfs", type=Path, required=True)
    _add_common_args(b)
    b.set_defaults(func=cmd_both)

    h = sub.add_parser("header", help="flash a pre-built BootPara header file as-is")
    h.add_argument("--src", type=Path, required=True,
                   help=f"header file (must be exactly {nl.NAND_ERASE_BLOCK:#x} bytes)")
    _add_common_args(h)
    h.set_defaults(func=cmd_header)

    rw = sub.add_parser("raw",
                        help="write any file to any NAND offset (no header, no CRC) — "
                             "for custom layouts that don't use cspstart's A/B model")
    rw.add_argument("--src", type=Path, required=True,
                    help="file to write (will be padded with 0xff to NAND erase block)")
    rw.add_argument("--offset", required=True,
                    type=lambda x: int(x, 0),
                    help="NAND target offset (hex or dec). Must be erase-block aligned. "
                         "Bootloader region (0x0..0xc0000) is forbidden.")
    rw.add_argument("--tftp-dir", type=Path, default=DEFAULT_TFTP_DIR,
                    help=f"TFTP serve dir (default: {DEFAULT_TFTP_DIR.relative_to(REPO)})")
    rw.add_argument("--dry-run", action="store_true",
                    help="stage file + print commands; do NOT open UART")
    rw.set_defaults(func=cmd_raw)

    args = ap.parse_args()

    # Bridge-by-default: set UART_TCP=1 so lib/uart.py routes through the
    # bridge daemon, auto-starting it if not running. Opt-out with
    # --direct-uart for low-level debugging.
    if not getattr(args, "direct_uart", False):
        os.environ["UART_TCP"] = "1"
        _ensure_bridge_running()

    try:
        return args.func(args) or 0
    except ValueError as e:
        # Safety guard rejection from lib.uboot_flash._check_safety
        print(f"\nrefused: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
