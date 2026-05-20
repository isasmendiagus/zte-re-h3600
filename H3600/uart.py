#!/usr/bin/env python3
"""Robust UART helper for H3600 boot tests.

Usage:
  uart.py log                       # tail UART output (Ctrl+C to stop)
  uart.py send "cmd to send"        # send slow (10ms/char)
  uart.py wait <seconds>            # wait + dump

  uart.py reset                     # DTR power-cycle → wait U-Boot prompt
                                    # (requires FTDI DTR wired to power-rail transistor)

Boot sequences (see BITACORA Cap 8 for context):
  uart.py aloop                     # bootm tiny payload (verified prints AAAA)
  uart.py bootz                     # bootz zImage in-place at 0x42000000
  uart.py bootm                     # bootm uImage with relocation (KNOWN BROKEN, here for diff)
  uart.py go                        # go 0x42000000 (no cleanup_before_linux, control test)

Full automated cycle (DTR reset is automatic — no manual power-cycle):
  uart.py auto_bootz                # DTR reset → drive U-Boot → bootz
  uart.py auto_bootm_dtb_appended   # DTR reset → drive U-Boot → bootm mainline zImage
  uart.py auto_aloop                # DTR reset → drive U-Boot → bootm aloop
  uart.py auto_go                   # DTR reset → drive U-Boot → go zImage
"""
import serial, sys, time, threading, os

import glob as _glob
_ports = sorted(_glob.glob("/dev/ttyUSB*"))
PORT = _ports[0] if _ports else "/dev/ttyUSB0"
BAUD = 115200
LOG  = "/tmp/uart.log"

def open_port():
    """Open the serial port and immediately release DTR so we don't hold the
    MCU in reset. DTR=True asserts (pin LOW); DTR=False de-asserts (pin HIGH).
    For active-low RESET, we want DTR=False (HIGH) during normal operation."""
    ser = serial.Serial()
    ser.port = PORT
    ser.baudrate = BAUD
    ser.timeout = 0.1
    ser.dtr = False       # release reset BEFORE opening (pyserial honors this)
    ser.rts = False       # also leave RTS de-asserted just in case
    ser.open()
    ser.dtr = False       # belt-and-suspenders: ensure released after open
    return ser

def send_slow(ser, cmd, delay=0.01):
    for ch in cmd:
        ser.write(ch.encode())
        ser.flush()
        time.sleep(delay)
    ser.write(b"\r")
    ser.flush()

def log_loop(ser, fout, stop_event, mirror=False):
    while not stop_event.is_set():
        try:
            data = ser.read(4096)
        except serial.SerialException:
            return
        if data:
            fout.write(data)
            fout.flush()
            if mirror:
                sys.stdout.buffer.write(data)
                sys.stdout.buffer.flush()

def cmd_log(args):
    ser = open_port()
    fout = open(LOG, "wb")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    try:
        while True: time.sleep(1)
    except KeyboardInterrupt:
        pass
    stop.set()
    t.join()
    fout.close()

def cmd_send(args):
    cmd = args[0] if args else ""
    ser = open_port()
    fout = open(LOG, "ab")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, False))
    t.start()
    time.sleep(0.5)
    send_slow(ser, cmd)
    time.sleep(1)
    stop.set()
    t.join()
    fout.close()

def cmd_wait(args):
    secs = float(args[0]) if args else 5
    ser = open_port()
    fout = open(LOG, "ab")
    deadline = time.time() + secs
    while time.time() < deadline:
        data = ser.read(4096)
        if data:
            fout.write(data); fout.flush()
            sys.stdout.buffer.write(data); sys.stdout.buffer.flush()
    fout.close()

def _run_seq(cmds):
    """Execute a list of (cmd, wait_seconds) tuples on the UART."""
    ser = open_port()
    fout = open(LOG, "wb")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    time.sleep(0.5)
    print("\n--- BOOT sequence ---", flush=True)
    for cmd, wait in cmds:
        send_slow(ser, cmd)
        time.sleep(wait)
    stop.set()
    t.join()
    fout.close()

# Common preamble: set IPs + big TFTP blocksize (default 512B → 143 KiB/s; 1468 → >1 MiB/s)
_PREAMBLE = [
    ("",                                    1),  # newline to wake prompt
    ("setenv serverip 192.168.1.50",        1),
    ("setenv ipaddr 192.168.1.1",           1),
    ("setenv tftpblocksize 1468",           1),
]

def cmd_aloop(args):
    """Tiny 116-byte payload — verified prints AAAA stream after bootm.
    Use this to confirm the cleanup→re-init UART sequence is working."""
    _run_seq(_PREAMBLE + [
        ("tftp 0x42000000 aloop.uimg",      4),
        ("bootm 0x42000000",                15),
    ])

def cmd_zlike(args):
    """Tiny 176-byte payload mimicking zImage layout: 8 nops + branch + magic + 'B' loop.
    Use to test if the zImage structure (not just instructions) breaks after cleanup."""
    _run_seq(_PREAMBLE + [
        ("tftp 0x42000000 zlike.uimg",      4),
        ("bootm 0x42000000",                15),
    ])

def cmd_auto_zlike(args):
    _do_reset_then(cmd_zlike)

def cmd_bootz(args):
    """bootz with zImage in-place at 0x42000000 — should NOT trigger overlap.
    Most likely path to a successful kernel boot per Hallazgo 7."""
    _run_seq(_PREAMBLE + [
        ("tftp 0x42000000 zImage",          16),
        ("tftp 0x44000000 h3600.dtb",       4),
        ("setenv bootargs 'console=ttyAMA0,115200n8 ignore_loglevel'", 1),
        ("bootz 0x42000000 - 0x44000000",   25),
    ])

def cmd_bootm(args):
    """bootm with uImage Load=0x40008000 — KNOWN BROKEN (overlap with decompressor dest).
    Kept for differential testing."""
    _run_seq(_PREAMBLE + [
        ("tftp 0x42000000 uImage",          16),
        ("tftp 0x44000000 h3600.dtb",       4),
        ("setenv bootargs 'console=ttyAMA0,115200n8 ignore_loglevel'", 1),
        ("bootm 0x42000000 - 0x44000000",   25),
    ])

def cmd_go(args):
    """go 0x42000000 — no cleanup_before_linux, no DTB.
    Control test: validates that the zImage instrumentation runs at all.
    Verified earlier to print AAAA stream."""
    _run_seq(_PREAMBLE + [
        ("tftp 0x42000000 zImage",          16),
        ("go 0x42000000",                   15),
    ])

# =====================================================================
# DTR-driven hardware reset
# =====================================================================

UBOOT_PASSWORD = "Boot4128s!"
DTR_HOLD_SECS = 2.0   # pulse width while DTR=True (modem powered off)

def dtr_reset(ser, hold_seconds=DTR_HOLD_SECS):
    """Hardware power-cycle via DTR (FTDI DTR drives a transistor cutting modem VCC).
       DTR=True  → FTDI pin LOW  → transistor OFF → modem unpowered
       DTR=False → FTDI pin HIGH → transistor ON  → modem powered
    First UART byte appears ~100ms after release."""
    print(f"[reset] DTR=True (modem off) for {hold_seconds}s...", flush=True)
    ser.dtr = True
    time.sleep(hold_seconds)
    ser.reset_input_buffer()   # discard any garbage from the power glitch
    print("[reset] DTR=False (modem on) — boot starting", flush=True)
    ser.dtr = False

def _wait_for_boot_and_drive_prompts(ser, total_timeout=120, do_reset=True):
    """Optional DTR reset, then listen on UART and drive boot prompts to U-Boot:
       1. "Press 1" → send '1'
       2. "Password" → send Boot4128s!
       3. '=>' → success.
    With DTR reset wired, this is fully automatic (no manual power-cycle).
    Pass do_reset=False to skip the pulse (e.g. if running on a host without the mod)."""
    if do_reset:
        dtr_reset(ser)
    else:
        print("Listening on UART. Power-cycle the box now to start the boot sequence.", flush=True)
    print(f"(Will wait up to {total_timeout}s for first byte.)", flush=True)
    fout = open(LOG, "wb")

    # Phase 1: wait for first byte (= box started booting)
    deadline = time.time() + total_timeout
    while time.time() < deadline:
        data = ser.read(512)
        if data:
            fout.write(data); fout.flush()
            sys.stdout.buffer.write(data); sys.stdout.buffer.flush()
            print("\n[autopilot] First byte detected — driving boot prompts.", flush=True)
            break
    else:
        print("\n[autopilot] TIMEOUT — no UART activity. Did you power-cycle?", flush=True)
        fout.close()
        return False

    deadline = time.time() + total_timeout
    buf = b""
    sent_one = False
    sent_pw = False
    seen_prompt = False
    while time.time() < deadline:
        data = ser.read(512)   # small reads for tight reaction loop
        if not data:
            continue
        fout.write(data); fout.flush()
        sys.stdout.buffer.write(data); sys.stdout.buffer.flush()
        buf += data

        # Stage 1: send '1' ONCE when "Press 1" appears
        if not sent_one and b"Press 1" in buf:
            ser.write(b"1"); ser.flush()
            sent_one = True
            print("\n[autopilot] >>> sent '1' (boot mode)", flush=True)
            buf = b""   # clear, future matches against fresh data

        # Stage 2: send password ONCE when prompted
        elif sent_one and not sent_pw and b"assword" in buf:
            time.sleep(0.2)
            ser.write(UBOOT_PASSWORD.encode() + b"\r"); ser.flush()
            sent_pw = True
            print(f"\n[autopilot] >>> sent password", flush=True)
            buf = b""

        # Stage 3: detect U-Boot prompt
        elif sent_pw and b"=>" in buf:
            seen_prompt = True
            time.sleep(1)
            tail = ser.read(2048)
            if tail:
                fout.write(tail); fout.flush()
            break

    fout.close()
    return seen_prompt

def cmd_wait_uboot(args):
    """Listen on UART (NO reset). Use this if you want to power-cycle by hand."""
    ser = open_port()
    ok = _wait_for_boot_and_drive_prompts(ser, do_reset=False)
    if ok:
        print("\n✓ U-Boot prompt reached.")
        return 0
    else:
        print("\n✗ Did not see U-Boot prompt within timeout.")
        return 1

def cmd_reset(args):
    """DTR hardware reset → wait for U-Boot prompt (no manual power-cycle)."""
    ser = open_port()
    ok = _wait_for_boot_and_drive_prompts(ser, do_reset=True)
    if ok:
        print("\n[OK] U-Boot prompt reached after DTR reset.")
        return 0
    print("\n[FAIL] Did not see U-Boot prompt within timeout.")
    return 1

def _wait_for_pattern(ser, fout, pattern, timeout, mirror=True):
    """Read UART until `pattern` (bytes) appears or timeout. Returns True if seen."""
    deadline = time.time() + timeout
    buf = b""
    while time.time() < deadline:
        data = ser.read(2048)
        if not data:
            continue
        fout.write(data); fout.flush()
        if mirror:
            sys.stdout.buffer.write(data); sys.stdout.buffer.flush()
        buf += data
        if pattern in buf:
            return True
        if len(buf) > 65536:    # keep last 32KB only
            buf = buf[-32768:]
    return False

def _do_reset_then(seq_cmds):
    """DTR-reset the modem, drive boot prompts to U-Boot, then run a sequence.
    All on the same open port (avoids DTR glitching from close/reopen).

    Each cmd tuple is (cmd, wait_pattern_or_seconds):
      - if int/float: sleep fixed
      - if bytes: wait until pattern appears (max 240s) then continue
      - if (pattern_bytes, timeout): wait pattern with custom timeout
    """
    ser = open_port()
    ok = _wait_for_boot_and_drive_prompts(ser, do_reset=True)
    if not ok:
        print("\n✗ U-Boot prompt not reached; aborting.")
        return 1
    print("\n--- BOOT sequence ---", flush=True)
    fout = open(LOG, "ab")
    for cmd, wait in seq_cmds:
        send_slow(ser, cmd)
        if isinstance(wait, (int, float)):
            # legacy fixed-sleep path — but stream output during the sleep
            deadline = time.time() + wait
            while time.time() < deadline:
                data = ser.read(2048)
                if data:
                    fout.write(data); fout.flush()
                    sys.stdout.buffer.write(data); sys.stdout.buffer.flush()
        elif isinstance(wait, bytes):
            _wait_for_pattern(ser, fout, wait, 240)
        elif isinstance(wait, tuple):
            pat, to = wait
            _wait_for_pattern(ser, fout, pat, to)
    fout.close()
    return 0

def cmd_auto_bootz(args):
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zImage",    16),
        ("tftp 0x44000000 h3600.dtb", 4),
        ("setenv bootargs 'console=ttyAMA0,115200n8 ignore_loglevel'", 1),
        ("bootz 0x42000000 - 0x44000000", 25),
    ])

def cmd_auto_bootz_high(args):
    """Test loading zImage at high address (0x46000000) to avoid potential
    overlap with U-Boot stack/heap that might live around 0x42xxxxxx."""
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x46000000 zImage",    16),
        ("tftp 0x44000000 h3600.dtb", 4),
        ("setenv bootargs 'console=ttyAMA0,115200n8 ignore_loglevel'", 1),
        ("bootz 0x46000000 - 0x44000000", 25),
    ])

def cmd_auto_bootm_xip(args):
    """zImage wrapped as uImage, bootm WITH DTB — fails because DTB code path
    skips ZTE's setup_versioninfo_tag."""
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zImage_xip.uimg", 16),
        ("tftp 0x44000000 h3600.dtb", 4),
        ("setenv bootargs 'console=ttyAMA0,115200n8 ignore_loglevel'", 1),
        ("bootm 0x42000000 - 0x44000000", 25),
    ])

def cmd_auto_bootm_nodtb(args):
    """zImage wrapped as uImage, bootm WITHOUT DTB — exercises ZTE's full
    setup_versioninfo_tag path. Kernel will panic later for lack of DTB
    but our infinite A-loop in head.S should run first."""
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zImage_xip.uimg", 16),
        ("setenv bootargs 'console=ttyAMA0,115200n8 ignore_loglevel'", 1),
        ("bootm 0x42000000", 25),
    ])

def cmd_auto_bootm_dtb_appended(args):
    """zImage WITH DTB APPENDED + bootm SIN DTB-arg.
    bootm va por path patched ZTE (cap_poweron + start_cpucap_cores).
    Decompresor mainline encuentra el DTB al final del zImage (CONFIG_ARM_APPENDED_DTB)."""
    _do_reset_then(_PREAMBLE + [
        # Wait until U-Boot prints "Bytes transferred" (TFTP done) — variable timing
        ("tftp 0x42000000 zImage_dtb.uimg", (b"Bytes transferred", 180)),
        # rdinit FIRST (ZTE U-Boot appends "; U-Boot V1.0.0 ..." which would corrupt last param)
        ("setenv bootargs 'pci=nomsi pcie_aspm=off rdinit=/init console=ttyAMA0,115200n8 earlycon=pl011,0x94404000 earlyprintk ignore_loglevel'",
         (b"=>", 5)),
        ("bootm 0x42000000", 90),  # streams output during sleep
    ])

def cmd_live_load_mod(args):
    """ASSUME kernel already at `~ #` shell. Just rmmod + transfer + insmod.
    No DTR reset, no boot. Iteration in ~15s vs ~3min full cycle.
    Usage: uart.py live_load_mod <local_ko> [insmod_args...]"""
    if not args:
        print("usage: live_load_mod <local_ko> [args...]")
        return 2
    local_ko = args[0]
    if not os.path.isfile(local_ko):
        print(f"missing: {local_ko}")
        return 2
    insmod_args = " ".join(args[1:])
    modname = os.path.basename(local_ko).replace(".ko", "").replace("-", "_")
    remote_ko = "/tmp/" + os.path.basename(local_ko)

    # 0. Verify shell is alive
    ser = open_port()
    ser.reset_input_buffer()
    fout = open(LOG, "ab")
    send_slow(ser, "echo @@ALIVE@@")
    if not _wait_for_pattern(ser, fout, b"@@ALIVE@@", 5):
        print("\n[FAIL] kernel not at shell prompt — try `auto_load_mod` for full boot")
        ser.close(); fout.close()
        return 1

    # 1. down all netdevs from this module then rmmod
    print(f"\n>>> downing netdevs + rmmod {modname}")
    send_slow(ser, "for d in idm0 idm1 wlan0; do ip link set $d down 2>/dev/null; done; "
                   f"rmmod {modname} 2>/dev/null; echo @@RMMOD_RC=$?@@")
    _wait_for_pattern(ser, fout, b"@@RMMOD_RC=", 8)
    ser.close()

    # 2. transfer .ko
    import subprocess
    print(f"\n>>> transferring {local_ko} → {remote_ko}")
    r = subprocess.run([sys.executable,
                        os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                     "uart_transfer.py"),
                        local_ko, remote_ko])
    if r.returncode != 0:
        fout.close()
        return r.returncode

    # 3. insmod + dmesg
    ser = open_port()
    cmd = (f"insmod {remote_ko} {insmod_args}; echo INSMOD_RC=$?; "
           f"dmesg | tail -40; ip -br link; echo @@DONE@@")
    print("\n>>> insmod + dmesg")
    send_slow(ser, cmd)
    _wait_for_pattern(ser, fout, b"@@DONE@@", 30)
    fout.close()
    return 0

def cmd_auto_load_mod(args):
    """boot kernel via TFTP → wait for `~ #` shell → transfer .ko → insmod → dmesg.
    Usage: uart.py auto_load_mod <local_ko_path> [insmod_args...]"""
    if not args:
        print("usage: auto_load_mod <local_ko> [args...]")
        return 2
    local_ko = args[0]
    if not os.path.isfile(local_ko):
        print(f"missing: {local_ko}")
        return 2
    insmod_args = " ".join(args[1:])
    remote_ko = "/tmp/" + os.path.basename(local_ko)

    # 1. Full boot cycle (kernel takes ~140s after bootm to reach shell)
    rc = _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zImage_dtb.uimg", (b"Bytes transferred", 180)),
        ("setenv bootargs 'pci=nomsi pcie_aspm=off rdinit=/init console=ttyAMA0,115200n8 earlycon=pl011,0x94404000 earlyprintk ignore_loglevel'",
         (b"=>", 5)),
        ("bootm 0x42000000", (b"~ #", 200)),    # wait until busybox prompt — kernel boot is slow
    ])
    if rc:
        print("\n[FAIL] boot did not reach shell")
        return rc

    # 2. Transfer the .ko via uart_transfer (bins are baked into kernel initramfs)
    import subprocess
    print(f"\n>>> transferring {local_ko} → {remote_ko}")
    r = subprocess.run([sys.executable,
                        os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                     "uart_transfer.py"),
                        local_ko, remote_ko])
    if r.returncode != 0:
        print("[FAIL] uart_transfer failed")
        return r.returncode

    # 3. insmod + dump dmesg/ip link
    ser = open_port()
    fout = open(LOG, "ab")
    print("\n>>> insmod + dmesg")
    cmd = f"insmod {remote_ko} {insmod_args}; echo INSMOD_RC=$?; dmesg | tail -40; ip -br link; echo @@DONE@@"
    send_slow(ser, cmd)
    _wait_for_pattern(ser, fout, b"@@DONE@@", 30)
    fout.close()
    return 0

def cmd_auto_aloop(args):
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 aloop.uimg", 4),
        ("bootm 0x42000000", 15),
    ])

def cmd_auto_zlike(args):
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zlike.uimg", 4),
        ("bootm 0x42000000", 15),
    ])

def cmd_auto_go(args):
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zImage", 16),
        ("go 0x42000000", 15),
    ])

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "log"
    rest = sys.argv[2:]
    handlers = {
        "log":          cmd_log,
        "send":         cmd_send,
        "wait":         cmd_wait,
        "aloop":        cmd_aloop,
        "bootz":        cmd_bootz,
        "bootm":        cmd_bootm,
        "go":           cmd_go,
        "zlike":        cmd_zlike,
        "wait_uboot":   cmd_wait_uboot,
        "reset":        cmd_reset,        # alias of wait_uboot (DTR reset disabled)
        "auto_bootz":              cmd_auto_bootz,
        "auto_bootz_high":         cmd_auto_bootz_high,
        "auto_bootm_xip":          cmd_auto_bootm_xip,
        "auto_bootm_nodtb":        cmd_auto_bootm_nodtb,
        "auto_bootm_dtb_appended": cmd_auto_bootm_dtb_appended,
        "auto_load_mod":           cmd_auto_load_mod,
        "live_load_mod":           cmd_live_load_mod,
        "auto_aloop":              cmd_auto_aloop,
        "auto_zlike":              cmd_auto_zlike,
        "auto_go":                 cmd_auto_go,
    }
    if cmd not in handlers:
        print(f"Unknown command: {cmd}\nUsage: {__doc__}", file=sys.stderr)
        sys.exit(2)
    handlers[cmd](rest)
