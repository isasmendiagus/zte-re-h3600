#!/usr/bin/env python3
"""Build a task-local rootfs variant with our spliced switch.ko.

Reads 00.02.stock-shell's staging/ directory READ-ONLY (the cspd+kmsg2uart
patched stock rootfs), copies it to our task-local out/rootfs_staging/,
overlays our spliced switch.ko on /kmodule/switch.ko, then builds JFFS2 +
AES-128-ECB encrypts using the same parameters as
tasks/00.02.stock-shell/prepare_slot_a.sh.

Output: tasks/00.01.eth-driver/out/rootfs_eth_spliced_enc.jffs2 (22 MiB).
Flash via:
  python3 tasks/00.04.flash-tool/flash.py rootfs \\
      --src tasks/00.01.eth-driver/out/rootfs_eth_spliced_enc.jffs2

Revert:
  python3 tasks/00.04.flash-tool/flash.py rootfs \\
      --src tftp/rootfs_a_patched_enc.jffs2

Doesn't touch 00.02's staging/, out/, or tftp/. Everything we produce
lives in tasks/00.01.eth-driver/out/.
"""

import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent              # tasks/00.01.eth-driver/scripts/
TASK = HERE.parent                                  # tasks/00.01.eth-driver/
REPO = TASK.parents[1]                              # ZTE/

# Inputs — both read-only
SRC_STAGING = REPO / "tasks/00.02.stock-shell/staging"
SPLICED_KO  = TASK / "out/spliced/switch.scope-init.ko"
DEVTABLE    = REPO / "tasks/00.02.stock-shell/devtable.txt"

# Outputs — task-local
OUR_OUT      = TASK / "out"
OUR_STAGING  = OUR_OUT / "rootfs_staging"
JFFS2_PLAIN  = OUR_OUT / "rootfs_eth_spliced.jffs2"
JFFS2_ENC    = OUR_OUT / "rootfs_eth_spliced_enc.jffs2"

# Build parameters — must match prepare_slot_a.sh exactly
ROOTFS_SIZE     = 0x1620000             # 22 MiB
PAGESIZE        = 2048
ERASEBLOCK      = 131072                # 128 KiB
AES_KEY_ASCII   = b"H36000e71071c440"   # per device


def must_exist(p: Path, desc: str):
    if not p.exists():
        sys.exit(f"ERROR: missing {desc}: {p}")


def run(cmd, **kw):
    print(f"  $ {' '.join(str(c) for c in cmd)}")
    return subprocess.run(cmd, check=True, **kw)


def main():
    print("==== Phase 0: pre-flight ====")
    must_exist(SRC_STAGING, "00.02 staging dir "
                            "(run tasks/00.02.stock-shell/prepare_slot_a.sh first)")
    must_exist(SRC_STAGING / "kmodule/switch.ko", "00.02 staging's /kmodule/switch.ko")
    must_exist(SRC_STAGING / "bin/cspd",          "00.02 staging's /bin/cspd (patched)")
    must_exist(SRC_STAGING / "sbin/kmsg2uart",    "00.02 staging's /sbin/kmsg2uart")
    must_exist(SPLICED_KO, "spliced switch.ko "
                           "(run tasks/00.01.eth-driver/scripts/ko_printk_splice.py first)")
    must_exist(DEVTABLE, "00.02's devtable.txt")
    for tool in ("mkfs.jffs2", "openssl"):
        if shutil.which(tool) is None:
            sys.exit(f"ERROR: {tool} not in PATH (apt install mtd-utils openssl)")
    print("  ✓ all inputs and tools present")

    OUR_OUT.mkdir(parents=True, exist_ok=True)

    print()
    print(f"==== Phase 1: copy {SRC_STAGING.name}/ → {OUR_STAGING.relative_to(REPO)}/ ====")
    if OUR_STAGING.exists():
        print(f"  removing existing {OUR_STAGING.relative_to(REPO)}/")
        shutil.rmtree(OUR_STAGING)
    # symlinks=True preserves /etc/rc.d -> rc.d-like links etc.
    shutil.copytree(SRC_STAGING, OUR_STAGING, symlinks=True)
    print(f"  ✓ task-local staging built (READ-ONLY use of 00.02's staging)")

    print()
    print(f"==== Phase 2: overlay spliced switch.ko ====")
    target = OUR_STAGING / "kmodule" / "switch.ko"
    src_size = SPLICED_KO.stat().st_size
    dst_size_before = target.stat().st_size
    shutil.copy(SPLICED_KO, target)
    target.chmod(0o755)
    print(f"  {target.relative_to(REPO)}: {dst_size_before:,} B → {src_size:,} B")

    print()
    print(f"==== Phase 3: mkfs.jffs2 → {JFFS2_PLAIN.relative_to(REPO)} ====")
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
                 f"content may have grown past 22 MiB; trim 00.02's Phase 2 list")
    # Verify JFFS2 magic
    magic = JFFS2_PLAIN.read_bytes()[:4]
    if magic != b"\x85\x19\x01\xe0":
        sys.exit(f"ERROR: JFFS2 magic invalid: {magic.hex()}")
    print(f"  ✓ JFFS2 image: {out_size:,} bytes, magic 85 19 01 e0 ok")

    print()
    print(f"==== Phase 4: AES-128-ECB encrypt → {JFFS2_ENC.relative_to(REPO)} ====")
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
    print()
    print("Revert (re-flash 00.02's canonical cspd rootfs, untouched):")
    print(f"  python3 tasks/00.04.flash-tool/flash.py rootfs --src "
          f"tftp/rootfs_a_patched_enc.jffs2")
    return 0


if __name__ == "__main__":
    sys.exit(main())
