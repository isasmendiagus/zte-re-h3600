#!/usr/bin/env python3
"""Build a task-local rootfs that loads kotrace.ko at boot, BEFORE cspd.

Reads 00.02.stock-shell's staging/ READ-ONLY (the cspd+kmsg2uart patched
rootfs), copies it to our task-local out/, drops kotrace.ko into /kmodule,
and injects an `insmod /kmodule/kotrace.ko` line at the start of the
module-loading block in /etc/init.norm so our notifier is live by the
time switch.ko (and everything else) gets loaded.

Output: tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2 (22 MiB).

Flash with:
  python3 tasks/00.04.flash-tool/flash.py rootfs \\
      --src tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2

Revert (re-flash 00.02's canonical cspd rootfs, untouched):
  python3 tasks/00.04.flash-tool/flash.py rootfs \\
      --src tftp/rootfs_a_patched_enc.jffs2

Doesn't touch 00.02's staging/, out/, or tftp/. Everything we produce
lives in tasks/00.01.eth-driver/out/.
"""

import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent              # tasks/00.01.eth-driver/kotrace/
TASK = HERE.parent                                  # tasks/00.01.eth-driver/
REPO = TASK.parents[1]                              # ZTE/

# Inputs — both read-only
SRC_STAGING = REPO / "tasks/00.02.stock-shell/staging"
KOTRACE_KO  = HERE / "kotrace.ko"
DEVTABLE    = REPO / "tasks/00.02.stock-shell/devtable.txt"

# Outputs — task-local
OUR_OUT      = TASK / "out"
OUR_STAGING  = OUR_OUT / "rootfs_kotrace_staging"
JFFS2_PLAIN  = OUR_OUT / "rootfs_kotrace.jffs2"
JFFS2_ENC    = OUR_OUT / "rootfs_kotrace_enc.jffs2"

# Build parameters — must match prepare_slot_a.sh exactly
ROOTFS_SIZE     = 0x1620000             # 22 MiB
PAGESIZE        = 2048
ERASEBLOCK      = 131072                # 128 KiB
AES_KEY_ASCII   = b"H36000e71071c440"   # per device

# Init script we patch — we inject our insmod before the first stock insmod
INIT_NORM_REL   = "etc/init.norm"
# Marker line we look for to find the right insertion point
FIRST_INSMOD_MARKER = "/sbin/insmod /kmodule/shellproc.ko"
# What we inject (note trailing newline so the original line stays as-is)
INJECT_BLOCK = (
    "# kotrace — loader-notifier for module-state trace (Phase A2.5)\n"
    "/sbin/insmod /kmodule/kotrace.ko\n"
    "\n"
)


def must_exist(p: Path, desc: str):
    if not p.exists():
        sys.exit(f"ERROR: missing {desc}: {p}")


def run(cmd, **kw):
    print(f"  $ {' '.join(str(c) for c in cmd)}")
    return subprocess.run(cmd, check=True, **kw)


def patch_init_norm(staging: Path):
    """Insert `insmod /kmodule/kotrace.ko` before the first stock insmod.
    init.norm has non-UTF-8 bytes (Chinese comments in GB-something) so
    read+patch as bytes to preserve them byte-for-byte.
    """
    target = staging / INIT_NORM_REL
    blob = target.read_bytes()
    if b"/kmodule/kotrace.ko" in blob:
        print(f"  init.norm already references kotrace — leaving as-is")
        return
    marker = FIRST_INSMOD_MARKER.encode()
    if marker not in blob:
        sys.exit(f"ERROR: marker {FIRST_INSMOD_MARKER!r} not found in "
                 f"{target} — stock init.norm has changed, update the script")
    new_blob = blob.replace(
        marker,
        INJECT_BLOCK.encode() + marker,
        1,
    )
    target.write_bytes(new_blob)
    print(f"  patched {INIT_NORM_REL}: inserted kotrace insmod "
          f"before first stock insmod")


def main():
    print("==== Phase 0: pre-flight ====")
    must_exist(SRC_STAGING, "00.02 staging dir "
                            "(run tasks/00.02.stock-shell/prepare_slot_a.sh first)")
    must_exist(SRC_STAGING / "kmodule/switch.ko", "00.02 staging's /kmodule/switch.ko")
    must_exist(SRC_STAGING / INIT_NORM_REL,       f"00.02 staging's /{INIT_NORM_REL}")
    must_exist(KOTRACE_KO, "kotrace.ko (run `make` in this dir first)")
    must_exist(DEVTABLE, "00.02's devtable.txt")
    for tool in ("mkfs.jffs2", "openssl"):
        if shutil.which(tool) is None:
            sys.exit(f"ERROR: {tool} not in PATH (apt install mtd-utils openssl)")
    print("  ✓ all inputs and tools present")

    OUR_OUT.mkdir(parents=True, exist_ok=True)

    print()
    print(f"==== Phase 1: copy {SRC_STAGING.name}/ → "
          f"{OUR_STAGING.relative_to(REPO)}/ ====")
    if OUR_STAGING.exists():
        print(f"  removing existing {OUR_STAGING.relative_to(REPO)}/")
        shutil.rmtree(OUR_STAGING)
    shutil.copytree(SRC_STAGING, OUR_STAGING, symlinks=True)
    print(f"  ✓ task-local staging built (READ-ONLY use of 00.02's staging)")

    print()
    print(f"==== Phase 2: drop kotrace.ko into /kmodule ====")
    target = OUR_STAGING / "kmodule" / "kotrace.ko"
    shutil.copy(KOTRACE_KO, target)
    target.chmod(0o644)
    print(f"  {target.relative_to(REPO)}: {KOTRACE_KO.stat().st_size:,} B")

    print()
    print(f"==== Phase 3: patch init.norm ====")
    patch_init_norm(OUR_STAGING)

    print()
    print(f"==== Phase 4: mkfs.jffs2 → {JFFS2_PLAIN.relative_to(REPO)} ====")
    run([
        "mkfs.jffs2",
        "-r", str(OUR_STAGING),
        "-o", str(JFFS2_PLAIN),
        f"--pagesize={PAGESIZE}",
        f"--eraseblock={ERASEBLOCK}",
        "--no-cleanmarkers",
        f"--pad={ROOTFS_SIZE}",
        "--little-endian",
        "-m", "size",
        "--squash",
        f"--devtable={DEVTABLE}",
    ])
    out_size = JFFS2_PLAIN.stat().st_size
    if out_size != ROOTFS_SIZE:
        sys.exit(f"ERROR: JFFS2 size {out_size} != expected {ROOTFS_SIZE} — "
                 f"content may have grown past 22 MiB; trim staging")
    magic = JFFS2_PLAIN.read_bytes()[:4]
    if magic != b"\x85\x19\x01\xe0":
        sys.exit(f"ERROR: JFFS2 magic invalid: {magic.hex()}")
    print(f"  ✓ JFFS2 image: {out_size:,} bytes, magic 85 19 01 e0 ok")

    print()
    print(f"==== Phase 5: AES-128-ECB encrypt → {JFFS2_ENC.relative_to(REPO)} ====")
    key_hex = AES_KEY_ASCII.hex()
    run([
        "openssl", "enc", "-e", "-aes-128-ecb",
        "-K", key_hex,
        "-nopad",
        "-in",  str(JFFS2_PLAIN),
        "-out", str(JFFS2_ENC),
    ])
    enc_size = JFFS2_ENC.stat().st_size
    if enc_size != ROOTFS_SIZE:
        sys.exit(f"ERROR: encrypted size {enc_size} != {ROOTFS_SIZE}")

    # Round-trip check
    import tempfile
    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as tmp:
        tmp_path = Path(tmp.name)
    try:
        run([
            "openssl", "enc", "-d", "-aes-128-ecb",
            "-K", key_hex,
            "-nopad",
            "-in",  str(JFFS2_ENC),
            "-out", str(tmp_path),
        ])
        if tmp_path.read_bytes() != JFFS2_PLAIN.read_bytes():
            sys.exit("ERROR: encrypt+decrypt round-trip MISMATCH")
        print("  ✓ encrypted; round-trip decrypt matches original")
    finally:
        tmp_path.unlink(missing_ok=True)

    print()
    print("==== Done ====")
    print(f"  output: {JFFS2_ENC} ({enc_size:,} bytes)")
    print()
    print("Flash with:")
    print(f"  python3 tasks/00.04.flash-tool/flash.py rootfs --src "
          f"{JFFS2_ENC.relative_to(REPO)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
