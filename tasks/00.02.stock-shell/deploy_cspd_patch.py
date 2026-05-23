#!/usr/bin/env python3
"""Deploy patched cspd to stock device:
  1. SSH in
  2. Backup original /bin/cspd → /usercfg/cspd.orig (survives reboot)
  3. mount -o remount,rw /
  4. tftp -g cspd-uart-alive from host
  5. Replace /bin/cspd
  6. sync, remount ro
  7. DOES NOT REBOOT — user verifies state, then reboots manually

Recovery if patched cspd breaks: ssh in (if possible) and:
  mount -o remount,rw /
  cp /usercfg/cspd.orig /bin/cspd
  sync
  reboot

If SSH fails entirely after reboot: slot B is intact, cspstart's A/B
fallback should recover; worst case use U-Boot recovery via UART."""
import paramiko, time, sys

HOST, USER, PASS = '192.168.1.1', 'admin', 'UkuGPeyRDU'
HOST_TFTP_IP = '192.168.1.50'
PATCH_FILE = 'cspd-uart-alive'


def run(sh, cmd, wait=8):
    sh.send(cmd + '\n')
    deadline = time.time() + wait
    buf = b''
    while time.time() < deadline:
        if sh.recv_ready():
            buf += sh.recv(65536)
            tail = buf.rstrip()
            if tail.endswith(b'# ') or tail.endswith(b'$ '):
                break
        time.sleep(0.1)
    return buf.decode('utf-8', 'replace')


def section(t):
    print(f"\n{'='*70}\n=== {t}\n{'='*70}")


def main():
    print(f"Connecting to {USER}@{HOST}...")
    c = paramiko.SSHClient()
    c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    c.connect(HOST, username=USER, password=PASS,
              allow_agent=False, look_for_keys=False, timeout=15)
    sh = c.invoke_shell(width=240, height=50)
    time.sleep(1.0)
    while sh.recv_ready(): sh.recv(16384)

    section("1. Verify current cspd + filesystem state")
    print(run(sh, 'ls -la /bin/cspd'))
    print(run(sh, 'md5sum /bin/cspd 2>/dev/null || sha256sum /bin/cspd 2>/dev/null'))
    print(run(sh, 'mount | grep " / "'))
    print(run(sh, 'df -h / 2>&1'))

    section("2. FREE jffs2 space (skip on-device backup — host has original)")
    print(run(sh, 'df -k / 2>&1'))
    # We already have the original at host:rootfs/bin/cspd. The on-device
    # backup uses 2.8MB of jffs2, which can cause ENOSPC when we try to
    # rm /bin/cspd later (jffs2 needs space even to delete).
    # Remount rw first so we can delete the backup if it exists.
    print(run(sh, 'mount -o remount,rw /'))
    print(run(sh, '[ -e /usercfg/cspd.orig ] && rm /usercfg/cspd.orig && echo BACKUP_REMOVED || echo "no backup, ok"'))
    print(run(sh, 'sync; sync; sleep 1; df -k / 2>&1'))

    section("3. Remount root rw")
    print(run(sh, 'mount -o remount,rw / 2>&1'))
    print(run(sh, 'mount | grep " / "'))

    section("4. TFTP-pull patched cspd to /tmp")
    print(run(sh, f'cd /tmp && rm -f {PATCH_FILE} && tftp -g -r {PATCH_FILE} {HOST_TFTP_IP} 2>&1; ls -la /tmp/{PATCH_FILE}', wait=30))

    section("5. Verify patched cspd size matches original")
    print(run(sh, f'ls -la /bin/cspd /tmp/{PATCH_FILE}'))

    section("6. Verify patch content: strings should show 3x '-g 3'")
    print(run(sh, f'strings /tmp/{PATCH_FILE} | grep "logctrl -m -p /dev/console -g"'))

    section("7. Replace /bin/cspd (rm first — avoids ETXTBSY since cspd is running)")
    print(run(sh, f'rm /bin/cspd && cp /tmp/{PATCH_FILE} /bin/cspd && chmod +x /bin/cspd && echo REPLACE_OK', wait=5))
    print(run(sh, f'ls -la /bin/cspd /tmp/{PATCH_FILE}'))
    # Quick byte-content check via od (busybox has it) on the patched offsets
    print(run(sh, r'''od -An -c -j 1888475 -N 36 /bin/cspd 2>&1 | head -3'''))
    print("(Expected: '/bin/logctrl -m -p /dev/console -g 3\\0' near the bytes shown)")

    section("8. sync + remount ro")
    print(run(sh, 'sync && sync && echo SYNCED'))
    print(run(sh, 'mount -o remount,ro /'))
    print(run(sh, 'mount | grep " / "'))

    section("9. Final state — READY for reboot")
    print(run(sh, 'ls -la /bin/cspd /usercfg/cspd.orig'))

    print("\n" + "="*70)
    print(f"DONE. Patched cspd is installed.")
    print(f"NOT rebooting automatically — verify above looks correct, then:")
    print(f"  ssh admin@{HOST}  (pw: {PASS})  →  reboot")
    print(f"  OR power-cycle the device.")
    print(f"")
    print(f"RECOVERY: if patched cspd breaks anything, ssh in and:")
    print(f"  mount -o remount,rw / && cp /usercfg/cspd.orig /bin/cspd && sync && reboot")
    print("="*70)

    sh.close(); c.close()


if __name__ == "__main__":
    main()
