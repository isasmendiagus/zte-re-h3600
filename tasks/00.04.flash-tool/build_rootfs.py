#!/usr/bin/env python3
"""Build an AES-encrypted JFFS2 rootfs from a staging directory, with
loud warnings when the unpadded image gets close to the slot's
rootfs region size (the silent footgun that motivated this tool).

Why this exists: mkfs.jffs2 with --pad=N is happy to silently TRUNCATE
the JFFS2 image to exactly N bytes when the content actually wants
slightly more. The resulting image looks valid but is missing whatever
got cut from the tail — usually a couple of inodes you'll only notice
when something fails at runtime in a way that doesn't point back to
flash. This tool computes the unpadded size FIRST, refuses to build
when it would exceed the slot, and prints a clear warning when
headroom drops below 5 %.

Usage:
    python3 tasks/00.04.flash-tool/build_rootfs.py \\
        --staging tasks/00.02.stock-shell/staging \\
        --devtable tasks/00.02.stock-shell/devtable.txt \\
        --out tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2

The output is the AES-128-ECB encrypted JFFS2 (what flash.py rootfs
expects). Pass --plain to skip encryption (useful for debugging).

This is the canonical builder. The per-task wrappers (e.g.
build_rootfs_with_kotrace.py) prepare the staging tree and then call
this script.
"""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

import nand_layout as nl


PAGESIZE                = 2048
ERASEBLOCK              = 131072                  # 128 KiB
DEFAULT_AES_KEY_ASCII   = b"H36000e71071c440"     # this device's per-unit key
HEADROOM_WARN_FRACTION  = 0.05                    # warn under 5 % free
JFFS2_MAGIC             = b"\x85\x19\x01\xe0"


def _run(cmd: list[str | Path]) -> None:
    print(f"  $ {' '.join(str(c) for c in cmd)}")
    subprocess.run([str(c) for c in cmd], check=True)


def _measure_unpadded(staging: Path, devtable: Path) -> int:
    """Build a throwaway un-padded JFFS2 just to learn its true size."""
    with tempfile.NamedTemporaryFile(suffix=".jffs2", delete=False) as tmp:
        tmp_path = Path(tmp.name)
    try:
        subprocess.run(
            [
                "mkfs.jffs2",
                "-r", str(staging),
                "-o", str(tmp_path),
                f"--pagesize={PAGESIZE}",
                f"--eraseblock={ERASEBLOCK}",
                "--no-cleanmarkers",
                "--little-endian",
                "-m", "size",
                "--squash",
                f"--devtable={devtable}",
            ],
            check=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
        return tmp_path.stat().st_size
    finally:
        tmp_path.unlink(missing_ok=True)


def check_size(staging: Path, devtable: Path, slot_size: int) -> int:
    """Return the unpadded JFFS2 size. Fail loudly if it exceeds slot_size;
    warn loudly if headroom is below HEADROOM_WARN_FRACTION."""
    unpadded = _measure_unpadded(staging, devtable)
    headroom = slot_size - unpadded
    pct_free = (headroom / slot_size) * 100.0
    print(f"  unpadded JFFS2 size: {unpadded:,} B ({unpadded:#x})")
    print(f"  slot rootfs region:  {slot_size:,} B ({slot_size:#x})")
    print(f"  headroom:            {headroom:,} B ({pct_free:.2f} % free)")

    if unpadded > slot_size:
        sys.exit(
            f"ERROR: JFFS2 needs {unpadded:,} B but slot rootfs region is "
            f"{slot_size:,} B. mkfs.jffs2 --pad would silently truncate "
            f"the tail. Trim the staging tree or grow the slot."
        )
    if headroom < slot_size * HEADROOM_WARN_FRACTION:
        print(
            f"  !! WARNING: less than {HEADROOM_WARN_FRACTION*100:.0f} % "
            f"headroom — adding a few more files may push past the limit",
            file=sys.stderr,
        )
    return unpadded


def build_rootfs(
    staging: Path,
    devtable: Path,
    out_enc: Path,
    *,
    slot_size: int = nl.SLOT_A.rootfs_size,
    aes_key_ascii: bytes = DEFAULT_AES_KEY_ASCII,
    encrypt: bool = True,
) -> Path:
    """Build (and optionally encrypt) the JFFS2 rootfs.

    Returns the path of the final file (encrypted if encrypt=True,
    plain otherwise)."""
    out_enc.parent.mkdir(parents=True, exist_ok=True)
    out_plain = out_enc.with_suffix(".plain.jffs2") if encrypt else out_enc

    print(f"==== Phase 1: size check ====")
    check_size(staging, devtable, slot_size)

    print(f"\n==== Phase 2: mkfs.jffs2 (padded to slot) → {out_plain.name} ====")
    _run([
        "mkfs.jffs2",
        "-r", staging,
        "-o", out_plain,
        f"--pagesize={PAGESIZE}",
        f"--eraseblock={ERASEBLOCK}",
        "--no-cleanmarkers",
        f"--pad={slot_size}",
        "--little-endian",
        "-m", "size",
        "--squash",
        f"--devtable={devtable}",
    ])
    actual = out_plain.stat().st_size
    if actual != slot_size:
        sys.exit(f"ERROR: JFFS2 size {actual} != slot size {slot_size}")
    if out_plain.read_bytes()[:4] != JFFS2_MAGIC:
        sys.exit(f"ERROR: JFFS2 magic not found in {out_plain}")
    print(f"  ✓ {actual:,} B, magic ok")

    if not encrypt:
        return out_plain

    print(f"\n==== Phase 3: AES-128-ECB encrypt → {out_enc.name} ====")
    key_hex = aes_key_ascii.hex()
    _run([
        "openssl", "enc", "-e", "-aes-128-ecb",
        "-K", key_hex,
        "-nopad",
        "-in",  out_plain,
        "-out", out_enc,
    ])
    enc_size = out_enc.stat().st_size
    if enc_size != slot_size:
        sys.exit(f"ERROR: encrypted size {enc_size} != slot {slot_size}")

    # Round-trip check
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as tmp:
        check_path = Path(tmp.name)
    try:
        _run([
            "openssl", "enc", "-d", "-aes-128-ecb",
            "-K", key_hex,
            "-nopad",
            "-in",  out_enc,
            "-out", check_path,
        ])
        if check_path.read_bytes() != out_plain.read_bytes():
            sys.exit("ERROR: encrypt+decrypt round-trip MISMATCH")
        print("  ✓ round-trip decrypt matches plain image")
    finally:
        check_path.unlink(missing_ok=True)
        out_plain.unlink()       # plain image was only intermediate

    return out_enc


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--staging", type=Path, required=True,
                    help="Rootfs staging directory")
    ap.add_argument("--devtable", type=Path, required=True,
                    help="mkfs.jffs2 --devtable file")
    ap.add_argument("--out", type=Path, required=True,
                    help="Output path for the (encrypted) JFFS2 image")
    ap.add_argument("--slot", choices=["A", "B"], default="A",
                    help="Slot whose rootfs region size to use as cap (default A)")
    ap.add_argument("--plain", action="store_true",
                    help="Skip AES encryption (output will be plaintext JFFS2)")
    ap.add_argument("--check-only", action="store_true",
                    help="Just run the size check and exit (no build)")
    args = ap.parse_args()

    if not args.staging.is_dir():
        sys.exit(f"ERROR: --staging {args.staging} is not a directory")
    if not args.devtable.is_file():
        sys.exit(f"ERROR: --devtable {args.devtable} not found")
    for tool in ("mkfs.jffs2",) + (() if args.plain else ("openssl",)):
        if shutil.which(tool) is None:
            sys.exit(f"ERROR: {tool} not in PATH "
                     f"(apt install mtd-utils {'openssl' if tool == 'openssl' else ''})")

    slot = nl.get_slot(args.slot)

    if args.check_only:
        check_size(args.staging, args.devtable, slot.rootfs_size)
        return 0

    out = build_rootfs(
        staging=args.staging,
        devtable=args.devtable,
        out_enc=args.out,
        slot_size=slot.rootfs_size,
        encrypt=not args.plain,
    )

    print()
    print(f"==== Done ====")
    print(f"  output: {out} ({out.stat().st_size:,} B)")
    print()
    print(f"Flash with:")
    print(f"  python3 tasks/00.04.flash-tool/flash.py rootfs --src {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
