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

# Init script we patch — we inject our insmod AFTER zx_ponreg.ko so the
# platform IO/MMU state needed for kotrace's ioremap(PL011) is already set up
# (shellproc + patch + zx_ponreg between them establish the ZTE-private
# remappings; injecting before them caused silent kernel hangs at boot
# because ioremap returned an address that wasn't writable yet).
# We're still ahead of plat-zxylzb_9128S / tm / switch — the interesting ones.
INIT_NORM_REL   = "etc/init.norm"
# Marker line we look for to find the right insertion point.
INSERT_AFTER_MARKER = "/sbin/insmod /kmodule/zx_ponreg.ko"
# What we inject. 2026-05-25 footgun fix: redirect insmod stderr to /dev/kmsg
# so any kernel-side rejection of the .ko (vermagic, unknown symbol, invalid
# module format, etc.) actually shows up in UART via klogctl-kmsg2uart. Without
# this, init.norm's stderr at boot has no controlling tty — busybox-insmod's
# error message goes to the void, making bake-in failures look like silent
# hangs when they're really just unreported errors.
INJECT_BLOCK = (
    "\n"
    "# HW watchdog petter — cspd normally feeds /dev/FeedDog every few seconds,\n"
    "# but cspd doesn't start until pc& late in init.norm. With our thunks\n"
    "# adding overhead to every patched fn call, the gap before pc& exceeds\n"
    "# the watchdog timeout and the SoC resets silently. We pet it ourselves\n"
    "# in the background from BEFORE the kotrace insmod until cspd takes over.\n"
    "( while : ; do echo > /dev/FeedDog 2>/dev/null || echo > /dev/watchdog 2>/dev/null ; sleep 2 ; done ) &\n"
    "\n"
    "# kotrace bake-in — patch_modules whitelist EXCLUDES plat_zxylzb_9128S\n"
    "# and tm because patching their init paths trips cpu1 softlockup. With\n"
    "# only switch+idmfdb+mt7915 patched, init makes it through; once cspd is\n"
    "# up we can rmmod kotrace + reinsert with full patches via netshell.\n"
    "# Iter A: only small-fry modules (15 + 81 = 96 targets total).\n"
    "# Goal: verify the patching pipeline + see if box boots OK.\n"
    "# If yes, escalate (next iter adds switch at 50%, then plat, etc).\n"
    "# Iter A2: only idmfdb (no zx_ponreg). zx_ponreg=100% caused reset.\n"
    "# Try idmfdb at 100% alone (81 targets, isolated module).\n"
    "# Iter B: SAME load as iter A2 (idmfdb at 100%, ~49 patches) but with\n"
    "# stop_machine=1 (default in this kotrace build) which pauses cpu1\n"
    "# during each patch's instruction-write+flush_icache so cpu1 can't\n"
    "# read a half-written insn. If iter A2 reset was a race, this boots.\n"
    "/sbin/kinsmod /kmodule/kotrace.ko patch_pct=0 patch_pct_per=idmfdb:100 patch_skip=zx_mdio_read,zx_mdio_write\n"
)


def must_exist(p: Path, desc: str):
    if not p.exists():
        sys.exit(f"ERROR: missing {desc}: {p}")


def run(cmd, **kw):
    print(f"  $ {' '.join(str(c) for c in cmd)}")
    return subprocess.run(cmd, check=True, **kw)


def patch_init_norm(staging: Path):
    """Inject the kotrace insmod + BISECT PROBES at multiple points in
    init.norm. Each /sbin/printok PROBE_NAME writes "[printok] PROBE_NAME"
    DIRECTLY to PL011 (mmap /dev/mem), bypassing /dev/console (broken on
    boots where cspstart fails to expand $(console) bootarg).
    The probes tell us EXACTLY where init.norm hangs/aborts.
    """
    target = staging / INIT_NORM_REL
    blob = target.read_bytes()
    if b"/kmodule/kotrace.ko" in blob:
        print(f"  init.norm already references kotrace — leaving as-is")
        return

    # Probes to insert (marker_in_existing_init_norm  →  inject_AFTER)
    probes = [
        # Top of init.norm — confirms /etc/rc reached init.norm at all
        (b"# /etc/init.norm: system-wide  file for the Bourne shells\n",
         b"/sbin/printok BEGIN\n"),
        # Right before the first stock insmod
        (b"/sbin/insmod /kmodule/shellproc.ko",
         b"/sbin/printok BEFORE_SHELLPROC\n"),
        # Before patch.ko
        (b"/sbin/insmod /kmodule/patch.ko",
         b"/sbin/printok BEFORE_PATCH\n"),
        # Before zx_ponreg
        (b"/sbin/insmod /kmodule/zx_ponreg.ko",
         b"/sbin/printok BEFORE_ZXPONREG\n"),
    ]
    # Insert probes BEFORE their markers (so probe runs first)
    new_blob = blob
    for marker, probe in probes:
        if marker in new_blob:
            new_blob = new_blob.replace(marker, probe + marker, 1)
        else:
            print(f"  WARN: probe marker {marker[:40]!r}... not found")

    # Now inject the kotrace block AFTER zx_ponreg.ko (existing logic)
    marker = INSERT_AFTER_MARKER.encode()
    if marker not in new_blob:
        sys.exit(f"ERROR: marker {INSERT_AFTER_MARKER!r} not found")
    new_blob = new_blob.replace(
        marker,
        marker + INJECT_BLOCK.encode() +
        b"/sbin/printok AFTER_KOTRACE\n",  # probe AFTER kinsmod
        1,
    )
    # And before plat-zxylzb (to confirm we got past kotrace)
    plat_marker = b"/sbin/insmod /kmodule/plat-zxylzb_9128S.ko"
    new_blob = new_blob.replace(
        plat_marker,
        b"/sbin/printok BEFORE_PLAT\n" + plat_marker,
        1,
    )
    # Before switch
    sw_marker = b"/sbin/insmod /kmodule/switch.ko"
    new_blob = new_blob.replace(
        sw_marker,
        b"/sbin/printok BEFORE_SWITCH\n" + sw_marker,
        1,
    )

    # Dump kotrace ring → UART AFTER plat_zxylzb load, BEFORE tm.ko.
    # Rationale: tm.ko init reliably crashes the box (its init calls a
    # patched function whose thunk corrupts state). By dumping right
    # after plat-LIVE we capture all the plat init activity (the most
    # interesting register-write sequence) BEFORE the crash. cspd never
    # starts but we already have the data on UART.
    tm_marker = b"# tm sdk\n/sbin/insmod /kmodule/tm.ko"
    if tm_marker not in new_blob:
        sys.exit(f"ERROR: tm.ko marker not found in init.norm")
    # DIAGNOSTIC: also dump RIGHT AFTER kotrace load (ring nearly empty —
    # validates the binary works in isolation, before any patched-fn-call
    # corruption could destabilize the kernel).
    new_blob = new_blob.replace(
        b"/sbin/printok AFTER_KOTRACE\n",
        b"/sbin/printok AFTER_KOTRACE\n"
        b"/sbin/printok BEFORE_DUMPKRING_EARLY\n"
        b"/sbin/dumpkring /proc/kotrace_dump\n"
        b"/sbin/printok AFTER_DUMPKRING_EARLY\n",
        1,
    )

    # AUTO-START dropbear + debug shell BEFORE pc&. The stock firmware
    # doesn't auto-start any SSH daemon — historically it was bootstrapped
    # via a ROP exploit in httpd (see tasks/00.05.01.rop-no-uart/). For
    # the bake-in path we don't need the exploit: just spawn dropbear
    # straight from init.norm so SSH is available on port 22 right after
    # cspd's slow cascade catches up with network setup.
    #
    # Also keep a /bin/sh on ttyAMA0 as a fallback if dropbear fails to
    # bind: `nc 127.0.0.1 9999` from the host reaches that shell over
    # the UART bridge. /dev/console is broken when cspstart doesn't
    # expand $(console) in bootargs, so we pin stdin/stdout directly.
    pc_marker = b"# auto start cpsd\npc&"
    if pc_marker not in new_blob:
        sys.exit(f"ERROR: pc& marker not found for shell/dropbear injection")
    # dropbear in a RESPAWN LOOP on port 2222 (NOT 22). The stock
    # config.bin's SSHCfg.SSH_ProcType=1 makes cspd wrap port 22 logins
    # with a restricted-shell CLI ("Welcome to the world of CLI!" prompt
    # asking for username/password a second time). dropbear on port
    # 2222 is outside cspd's hook scope — gives a plain /bin/sh as
    # root. Same trick the historical httpd-ROP exploit used.
    #
    # Supervisor sleeps 30s so cspd's network reconfig settles, then
    # respawns dropbear if cspd ever kills it. `-F` keeps dropbear in
    # foreground so the while loop sees the exit.
    #
    # Connect from host: ssh -p 2222 admin@192.168.1.1 (or root@…)
    # TELNETD on port 23 (busybox built-in) — simplest path to a clean
    # /bin/sh on the device. No CLI wrapper (cspd only intercepts SSH
    # via SSHCfg.SSH_ProcType hook, not telnet). busybox telnetd has
    # been disabled in /etc/init.norm by ZTE (line 96: `#telnetd&`)
    # but the binary still lives in busybox.
    #
    # We also write the script as a tiny helper to /sbin/start_shells
    # and call it post-cspd so any teardown cspd does during its
    # cascade gets recovered. The 30s sleep lets cspd's first network
    # reconfig settle before we bind listening sockets.
    # SSH access plan (we control rootfs but not /usercfg/config.bin in mtdblock4):
    # 1. cspd starts its own dropbear on port 22 (no supervisor needed)
    # 2. /bin/cliagent symlinked to /bin/sh in staging -> SSH_ProcType=1 branch lands on sh
    # 3. cspd applies FWSC rules at startup via popen(/bin/iptables);
    #    Rule 8 lan_ssh DROP cuts LAN -> SSH. Periodic -D loop removes it
    #    after cspd commits, while leaving WAN-side rules intact.
    #    The loop wins because cspd never re-applies (no watchdog).
    # netshell raw TCP shell on port 9001 — backdoor that bypasses
    # dropbear's PTY entirely. Wrapped in a supervisor loop so if the
    # daemon dies (segfault, OOM, kill), it respawns every 2 s.
    # Internally netshell forks per client → multiple parallel
    # connections OK without restart. Connect: nc 192.168.1.1 9001
    new_blob = new_blob.replace(
        pc_marker,
        b"/sbin/printok BEFORE_NETSHELL\n"
        b"(while :; do /sbin/netshell 9001 >>/tmp/netshell.log 2>&1; sleep 2; done) &\n"
        b"/sbin/printok BEFORE_CSPD\n"
        b"# DUMP then strip cspd's LAN-SSH-DROP rule. 16 iter * 10 s = 160 s\n"
        b"# of coverage so we catch slow cspd init. Per-iter snapshot written\n"
        b"# to /tmp/fwiter.txt then concatenated into /tmp/fwdump.log AND\n"
        b"# pushed out the UART via /sbin/dumpkring (mmap PL011 directly,\n"
        b"# same path as kotrace; /dev/kmsg isn't writable on this kernel).\n"
        b"(i=0; while :; do\n"
        b"  i=$((i+1)); sleep 10\n"
        b"  {\n"
        b"    echo \"\"\n"
        b"    echo \"==== fwdump iter $i ====\"\n"
        b"    /bin/iptables  -L srvcntrl -v -n 2>&1\n"
        b"  } >/tmp/fwiter.txt 2>&1\n"
        b"  /sbin/dumpkring /tmp/fwiter.txt\n"
        b"  /bin/iptables  -F srvcntrl 2>/dev/null\n"
        b"  /bin/ip6tables -F srvcntrl 2>/dev/null\n"
        b"  # ensure netshell port stays reachable (idempotent insert at top)\n"
        b"  /bin/iptables -C INPUT -p tcp --dport 9001 -j ACCEPT 2>/dev/null \\\n"
        b"    || /bin/iptables -I INPUT 1 -p tcp --dport 9001 -j ACCEPT 2>/dev/null\n"
        b"  # dump cliagent.log if non-empty, then truncate to avoid re-dumping\n"
        b"  if [ -s /tmp/cliagent.log ]; then\n"
        b"    /sbin/dumpkring /tmp/cliagent.log\n"
        b"    : >/tmp/cliagent.log\n"
        b"  fi\n"
        b"done) &\n"
        + pc_marker,
        1,
    )
    new_blob = new_blob.replace(
        tm_marker,
        b"/sbin/printok BEFORE_DUMPKRING\n"
        b"/sbin/dumpkring /proc/kotrace_dump\n"
        b"/sbin/printok AFTER_DUMPKRING\n"
        + tm_marker,
        1,
    )

    target.write_bytes(new_blob)
    print(f"  patched {INIT_NORM_REL}: 7 bisect probes + kotrace inject + dumpkring")


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
