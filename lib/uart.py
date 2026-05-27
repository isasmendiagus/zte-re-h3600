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
    For active-low RESET, we want DTR=False (HIGH) during normal operation.

    Transport selection via env vars:
      UART_TCP=1                  → go through the bridge daemon (see
                                    tasks/00.04.02.uart-bridge/). Lets other
                                    processes monitor UART concurrently via
                                    `nc localhost 9999` or
                                    `tail -f /tmp/uart_bridge.log`.
      UART_TCP_HOST=hostname      → default localhost
      UART_TCP_DATA_PORT=N        → default 9999
      UART_TCP_CTL_PORT=N         → default 9998

    Default (no UART_TCP) keeps the direct-pyserial path. The bridge daemon
    must be running for the TCP path to work; see the README in 00.04.02.
    """
    if os.environ.get("UART_TCP"):
        # Lazy import + sys.path push so we don't pollute the default path
        import sys as _sys
        _here = os.path.dirname(os.path.abspath(__file__))
        _bridge_dir = os.path.normpath(
            os.path.join(_here, "..", "tasks/00.04.02.uart-bridge"))
        if _bridge_dir not in _sys.path:
            _sys.path.insert(0, _bridge_dir)
        from lib_uart_tcp import open_port as _tcp_open  # type: ignore
        host = os.environ.get("UART_TCP_HOST", "localhost")
        dport = int(os.environ.get("UART_TCP_DATA_PORT", "9999"))
        cport = int(os.environ.get("UART_TCP_CTL_PORT",  "9998"))
        ser = _tcp_open(host=host, data_port=dport, ctl_port=cport,
                        timeout=0.1)
        ser.setDTR(False)   # release reset on the bridge side
        return ser

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

# In-memory mirror of the UART stream — populated by log_loop, consumed
# by wait_for_uboot_prompt_or_fail. Reading from this is ~zero-latency
# vs polling a flushed file; markers like '=>' or 'T T T...' are visible
# the moment log_loop's ser.read() returns. Each run_uboot_seq() can
# call _buf_snapshot_size() at the start to get a "start_offset" so its
# checks only see data appended AFTER its command was sent.
#
# TODO: consider a single-threaded refactor of run_uboot_seq that does
# ser.read + mirror + marker-check inline, removing the log_loop thread
# + _RX_BUF lock entirely. Cleaner architecturally but ~50 lines of
# refactor + risk to other lib callers (cmd_log, cmd_wait, _run_seq)
# that share log_loop. Worth doing if we add more inline-buffer
# detectors (e.g., kernel-panic watcher) and the thread coordination
# becomes annoying.
_RX_BUF = bytearray()
_RX_BUF_LOCK = threading.Lock()


def _buf_size():
    """Current size of the in-memory UART mirror."""
    with _RX_BUF_LOCK:
        return len(_RX_BUF)


def _buf_snapshot(start_offset=0):
    """Snapshot of the UART mirror from `start_offset` to end. Returns
    bytes (not a view, to keep callers race-free)."""
    with _RX_BUF_LOCK:
        return bytes(_RX_BUF[start_offset:])


def log_loop(ser, fout, stop_event, mirror=False):
    while not stop_event.is_set():
        try:
            data = ser.read(4096)
        except serial.SerialException:
            return
        if data:
            fout.write(data)
            fout.flush()
            with _RX_BUF_LOCK:
                _RX_BUF.extend(data)
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


def _log_size():
    """Current size of the bridge log file (0 if absent)."""
    try:
        with open(LOG, "rb") as f:
            f.seek(0, 2)
            return f.tell()
    except FileNotFoundError:
        return 0


def bridge_dtr_pulse(host="localhost", port=9998, hold_secs=2.0):
    """Pulse DTR via the uart-bridge daemon's ctl port — cold-boots the
    device. Same atomic operation tftp_boot_mainline used to do inline;
    extracted here so run_uboot_seq can invoke recovery transparently
    on terminal TFTP failures."""
    import socket as _socket
    s = _socket.create_connection((host, port), timeout=5)
    try:
        s.recv(1024)  # greeting
        s.sendall(b"DTR_HIGH\n")  # device OFF
        s.recv(1024)
        print(f"[bridge_dtr_pulse] DTR HIGH for {hold_secs}s (cold reset)")
        time.sleep(hold_secs)
        s.sendall(b"DTR_LOW\n")   # device ON
        resp = s.recv(1024)
        print(f"[bridge_dtr_pulse] DTR LOW → {resp.decode(errors='replace').strip()}")
    finally:
        s.close()


def drive_cspstart_to_uboot(ser, password="Boot4128s!", timeout=60):
    """After a DTR pulse, drive cspstart's interactive prompts to reach
    U-Boot. Returns True if '=>' prompt seen, False on timeout. Used by
    run_uboot_seq's TFTP failure recovery to re-reach U-Boot after a
    cold reset."""
    deadline = time.time() + timeout
    buf = b""
    sent_one = sent_pw = False
    while time.time() < deadline:
        data = ser.read(512)
        if data:
            sys.stdout.buffer.write(data); sys.stdout.buffer.flush()
            buf += data
            if not sent_one and b"Press 1" in buf:
                ser.write(b"1\r"); ser.flush()
                sent_one = True
                print("\n[drive_cspstart] sent '1'")
            if sent_one and not sent_pw and b"password" in buf:
                ser.write(password.encode() + b"\r"); ser.flush()
                sent_pw = True
                print("[drive_cspstart] sent password")
            if b"=>" in buf:
                return True
        else:
            time.sleep(0.05)
    return False


def wait_for_marker(marker, timeout=120, start_offset=0, log_path=None):
    """Poll the bridge log for a substring. Returns True if found within
    `timeout` seconds. Search begins at `start_offset` bytes into the log
    so callers can search only what appears AFTER they sent a command.

    If `log_path` is None, uses the module-global LOG (the bridge log)."""
    path = log_path if log_path is not None else LOG
    deadline = time.time() + timeout
    needle = marker.encode() if isinstance(marker, str) else marker
    while time.time() < deadline:
        try:
            with open(path, "rb") as f:
                f.seek(start_offset)
                if needle in f.read():
                    return True
        except FileNotFoundError:
            pass
        time.sleep(0.3)
    return False


def wait_for_uboot_prompt(timeout=180, start_offset=0):
    """Wait for the U-Boot '=>' prompt return marker in the bridge log.

    This is the generic command-completion detector for U-Boot — every
    successful command returns control to the '=>' prompt. Use this
    instead of fixed sleeps when command duration is variable (TFTP,
    erase, write).

    Returns True on success, False on timeout."""
    return wait_for_marker("=>", timeout=timeout, start_offset=start_offset)


# Failure markers that mean the command is hung or failing — we can
# abort early instead of waiting the full timeout. Specifically:
#   "Retry count exceeded" → U-Boot's TFTP gave up after N retries
#   "TIMEOUT_ERR"           → some U-Boot builds use this
# We also detect repeated "T " (timeout marker per packet) but only
# treat them as failure if they exceed a threshold — a few Ts on a
# normal transfer are tolerated.
UBOOT_FAIL_MARKERS = ("Retry count exceeded", "TIMEOUT_ERR")
UBOOT_T_THRESHOLD = 8   # consecutive 'T ' markers tolerated before declaring failure
                        # — 8 ≈ 8 seconds at U-Boot's 1s/retry default, fast
                        # enough to react before the 30s "Retry count exceeded"
                        # auto-restart adds another lap.


def _count_consecutive_ts(data: bytes) -> int:
    """Longest run of 'T ' tokens on any single line of `data`. U-Boot's
    TFTP failure prints 'T T T T T...' all on one line."""
    best = 0
    for line in data.split(b"\n"):
        c = line.count(b"T ")
        if c > best:
            best = c
    return best


def wait_for_uboot_prompt_or_fail(timeout=180, start_offset=0):
    """Poll the in-memory UART mirror (populated by log_loop directly
    from the socket — no file I/O race) for either the '=>' prompt OR a
    failure marker.

    Returns one of:
      'prompt'    — command completed, '=>' found
      'tftp_fail' — 'Retry count exceeded', 'TIMEOUT_ERR', or >= UBOOT_T_THRESHOLD
                    consecutive 'T ' markers on a single line
      'timeout'   — neither marker within the deadline

    The `start_offset` should be `_buf_size()` captured BEFORE sending
    the command — that way the search ignores stale prompts/markers
    from earlier output."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        data = _buf_snapshot(start_offset)
        if b"=>" in data:
            return "prompt"
        for fm in UBOOT_FAIL_MARKERS:
            if fm.encode() in data:
                return "tftp_fail"
        if _count_consecutive_ts(data) >= UBOOT_T_THRESHOLD:
            return "tftp_fail"
        time.sleep(0.1)
    return "timeout"

# Common preamble: set IPs + big TFTP blocksize (default 512B → 143 KiB/s; 1468 → >1 MiB/s)
_PREAMBLE = [
    ("",                                    1),  # newline to wake prompt
    ("setenv serverip 192.168.1.50",        1),
    ("setenv ipaddr 192.168.1.1",           1),
    ("setenv tftpblocksize 1468",           1),
]

def run_uboot_seq(ser, cmds, mirror=True, append=True, skip_preamble=False,
                  wait_for_prompt=False, prompt_timeout=180,
                  retry_on_tftp_fail=True, max_retries=3):
    """Run a list of (cmd, wait_seconds) tuples on a UART already at the
    U-Boot prompt. Caller is responsible for: opening `ser`, doing the
    DTR reset, and driving cspstart prompts to U-Boot.

    Prepends `_PREAMBLE` (the empty-newline wake + setenv ipaddr/serverip +
    tftpblocksize=1468) which:
      - fixes the "first command after U-Boot prompt is lost" race
      - configures network for TFTP
      - bumps TFTP throughput from ~146 KiB/s to ~1 MiB/s

    Set skip_preamble=True if the caller already programmed the env.

    If `wait_for_prompt=True`, after each non-empty command the function
    polls the bridge log for the '=>' prompt return (using
    `wait_for_uboot_prompt_or_fail`) instead of sleeping for the fixed
    `wait_seconds`. The per-command tuple's second element is still
    respected — if the prompt-wait succeeds we move on immediately; if
    the prompt-wait times out we fall back to the fixed wait. This makes
    the helper safe to use for variable-duration commands like `tftp` /
    `erase` / `nand write` without racing into the next command. Note:
    do NOT pass wait_for_prompt=True for `bootm` — that command doesn't
    return to a prompt.

    If `retry_on_tftp_fail=True` (default), commands that contain 'tftp'
    will be auto-re-sent up to `max_retries` times if a TFTP failure
    marker is detected (`Retry count exceeded`, excessive 'T '
    timeouts). Common cause: ARP not yet settled right after a DTR
    reset, or transient packet loss."""
    log_open_mode = "ab" if append else "wb"
    fout = open(LOG, log_open_mode)
    # Reset the in-memory UART mirror so this invocation sees a clean
    # slice. start_offset captures from _buf_size() *inside* this call
    # so unrelated cspstart output from before main() called us doesn't
    # match our prompt/fail patterns.
    with _RX_BUF_LOCK:
        _RX_BUF.clear()
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, mirror))
    t.start()
    time.sleep(0.5)

    def _send_and_wait(cmd, wait, attempt=1):
        """Send one command and (optionally) wait for prompt return.
        Returns 'ok' on success, 'tftp_fail' for caller-handled retry,
        or 'timeout' on giving up."""
        label = repr(cmd) if cmd else "<empty newline wake>"
        attempt_str = f" [attempt {attempt}]" if attempt > 1 else ""
        if wait_for_prompt and cmd:
            print(f">>> [uboot] {label}  (wait for '=>' prompt, up to {prompt_timeout}s){attempt_str}",
                  flush=True)
        else:
            print(f">>> [uboot] {label}  (wait {wait}s){attempt_str}", flush=True)

        offset_before = _buf_size() if wait_for_prompt and cmd else None
        send_slow(ser, cmd)

        if wait_for_prompt and cmd:
            time.sleep(0.5)
            status = wait_for_uboot_prompt_or_fail(timeout=prompt_timeout,
                                                   start_offset=offset_before)
            if status == "prompt":
                return "ok"
            if status == "tftp_fail":
                return "tftp_fail"
            print(f"[run_uboot_seq] timeout waiting for prompt after {cmd!r}, "
                  f"falling back to fixed sleep ({wait}s)", flush=True)
            return "timeout"

        time.sleep(wait)
        return "ok"

    full_cmds = (list(_PREAMBLE) if not skip_preamble else []) + list(cmds)

    def _run_preamble():
        """Re-issue _PREAMBLE on `ser`. Used after DTR cold-reset recovery
        — env is wiped, need to re-set ipaddr/serverip/tftpblocksize."""
        for pcmd, pwait in _PREAMBLE:
            _send_and_wait(pcmd, pwait)

    i = 0
    while i < len(full_cmds):
        cmd, wait = full_cmds[i]
        attempt = 1
        used_dtr_recovery = False
        while True:
            status = _send_and_wait(cmd, wait, attempt)
            if status == "ok" or status == "timeout":
                break

            if status == "tftp_fail" and retry_on_tftp_fail and "tftp" in cmd:
                # Tier 1: simple re-send up to max_retries.
                if attempt < max_retries:
                    attempt += 1
                    print(f"[run_uboot_seq] tftp failure marker detected — "
                          f"retrying ({attempt}/{max_retries})", flush=True)
                    time.sleep(3)
                    continue

                # Tier 2: simple re-sends exhausted. Try ONCE more after
                # a full DTR cold-reset + cspstart drive + preamble replay.
                # This handles the case where U-Boot itself got wedged
                # (e.g., its tftp engine is stuck) rather than just a
                # transient ARP miss.
                if not used_dtr_recovery:
                    print(f"[run_uboot_seq] tftp failed {max_retries}x — "
                          f"DTR cold-reset + replay cspstart→U-Boot + preamble",
                          flush=True)
                    try:
                        bridge_dtr_pulse()
                    except Exception as e:
                        print(f"[run_uboot_seq] bridge DTR_PULSE failed: {e}",
                              flush=True)
                        break
                    if not drive_cspstart_to_uboot(ser):
                        print("[run_uboot_seq] ERROR: could not reach U-Boot "
                              "after DTR — giving up", flush=True)
                        break
                    _run_preamble()
                    used_dtr_recovery = True
                    attempt = 1   # reset counter for one more round
                    continue

                # Tier 3: even DTR didn't help. Give up cleanly.
                print(f"[run_uboot_seq] tftp still failing after DTR recovery, "
                      f"giving up", flush=True)
                break
            break
        i += 1

    stop.set()
    t.join()
    fout.close()

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

def cmd_auto_stock_verbose(args):
    """DTR reset + intercept U-Boot + boot stock kernel from NAND with
    verbose printk so init function calls + module loads are visible on UART.

    Stock kernel is loaded by cspstart into RAM at 0x42020020 (per earlier
    capture). Default bootargs set console_loglevel ~7 which is silenced
    later by something. We force `ignore_loglevel` + `loglevel=15` +
    `keep_bootcon` so EVERY printk reaches UART through stock boot AND
    through the init.norm module load chain (shellproc, patch, zx_ponreg,
    plat, tm, switch, idmfdb)."""
    _do_reset_then(_PREAMBLE + [
        ("setenv bootargs 'console=ttyAMA0,115200n8 root=/dev/mtdblock8 ro rootfstype=jffs2 mem=256M ignore_loglevel loglevel=15 keep_bootcon earlyprintk'",
         (b"=>", 5)),
        ("bootm 0x42020020", 300),
    ])

def cmd_auto_stock(args):
    """DTR reset + DON'T intercept boot. Let device autoboot stock from flash.
    Stock 4.1.25 kernel + stock modules boot fully. Then we can interact via
    UART CLI to load our debug modules via tftp + insmod."""
    ser = open_port()
    fout = open(LOG, "wb")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    time.sleep(0.5)
    print("\n--- DTR reset, letting stock autoboot ---", flush=True)
    dtr_reset(ser)
    print("[autopilot] NOT intercepting. Streaming UART for 240s.", flush=True)
    time.sleep(240)
    stop.set()
    t.join()
    fout.close()

def cmd_auto_bootz(args):
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 zImage",    (b"Bytes transferred", 180)),
        ("tftp 0x44000000 h3600.dtb", (b"Bytes transferred", 30)),
        ("setenv bootargs 'console=ttyAMA0,115200n8 earlyprintk ignore_loglevel'", (b"=>", 5)),
        ("bootz 0x42000000 - 0x44000000", 300),
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

def cmd_auto_bootm_stockport(args):
    """Stockport kernel 4.1.25 (plain uImage with bundled initramfs + zte_shim).
    Entry=Load=0x40008000 stock convention.

    Boot architecture aligns with stock per /etc/autokernelconf:
      - ATAGs (NOT DTB): CONFIG_ARM_APPENDED_DTB not set, CMDLINE_FROM_BOOTLOADER=y
      - DEBUG_LL=y with pl01x.S (shifted offsets, requires ARCH_ZX279128S=y)
      - Static UART iomap virt=0xf0704000 phys=0x94404000 via mach-zx
    bootm is single-arg: ZTE U-Boot does not support the 3-arg form."""
    _do_reset_then(_PREAMBLE + [
        ("tftp 0x42000000 uImage_stockport", (b"Bytes transferred", 180)),
        ("setenv bootargs 'rdinit=/init console=ttyAMA0,115200n8 earlyprintk ignore_loglevel keep_bootcon loglevel=15 mem=256M cma=16M@0x4e800000'",
         (b"=>", 5)),
        ("bootm 0x42000000", 300),
    ])

def cmd_auto_bootm_dtb_appended(args):
    """zImage WITH DTB APPENDED + bootm SIN DTB-arg.
    bootm va por path patched ZTE (cap_poweron + start_cpucap_cores).
    Decompresor mainline encuentra el DTB al final del zImage (CONFIG_ARM_APPENDED_DTB)."""
    _do_reset_then(_PREAMBLE + [
        # Wait until U-Boot prints "Bytes transferred" (TFTP done) — variable timing
        ("tftp 0x42000000 zImage_dtb.uimg", (b"Bytes transferred", 180)),
        # rdinit FIRST (ZTE U-Boot appends "; U-Boot V1.0.0 ..." which would corrupt last param)
        ("setenv bootargs 'pci=nomsi pcie_aspm=off rdinit=/init console=ttyAMA0,115200n8 earlycon=pl011,0x94404000 earlyprintk ignore_loglevel keep_bootcon cma=16M@0x4e800000'",
         (b"=>", 5)),
        ("bootm 0x42000000", 300),  # streams output during sleep
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

def cmd_auto_bootm_stock_uart(args):
    """Boot stock kernel from NAND with `init=/bin/sh` on UART.

    BYPASSES cspstart because cspstart runs its OWN `setenv bootargs ...`
    internally, wiping our env-set bootargs. Seen in earlier log:
        zteboot_do_settings:417 >>s=setenv bootargs console=$(console)
                                  root=/dev/mtdblock8 ro rootfstype=jffs2
                                  mem=$(memsize);
    Our `init=/bin/sh` gets dropped → stock /sbin/init runs → cspd silences UART.

    Workaround: do `nand read` ourselves to load kernel into RAM, then `bootm`
    with our bootargs. ZTE 32-byte wrapper skipped via `+0x20` offset.

    Slot selection (default: B, since slot A's rootfs is known broken):
        ./uart.py auto_bootm_stock_uart           → slot B (kernel @ 0x2700000, mtd7)
        ./uart.py auto_bootm_stock_uart A          → slot A (kernel @ 0x700000, mtd6)

    Stock kernel's actual mtd partitions (per boot log, 2026-05-21):
        mtd0: Whole flash    0x0      .. 0x8000000
        mtd1: Bootloader     0x0      .. 0x100000
        mtd2: tag            0x100000 .. 0x200000
        mtd3: wifi           0x200000 .. 0x300000
        mtd4: usercfg        0x300000 .. 0x500000
        mtd5: defcfg         0x500000 .. 0x700000
        mtd6: kernel1        0x700000 .. 0x2700000   ← slot A (kernel + rootfs A)
        mtd7: kernel2        0x2700000.. 0x4700000   ← slot B (kernel + rootfs B)
        mtd8: rootfs         0x0      .. 0x8000000   ← WHOLE flash (jffs2 scans all)

    From the resulting `#` prompt we can:
      mount -t debugfs none /sys/kernel/debug
      ls /sys/kernel/debug/tracing/                  # check kprobes/ftrace
      echo 'p:foo chip_tm_init' > .../kprobe_events  # arm probes BEFORE insmod
      insmod /lib/modules/4.1.25/zx_ponreg.ko        # ABI matches stock perfectly
      insmod /lib/modules/4.1.25/plat-zxylzb_9128S.ko
      cat /sys/kernel/debug/tracing/trace            # captured init sequence"""
    slot = (args[0].upper() if args else 'A')
    if slot == 'A':
        kernel_off = 0x700000
        # Slot A's jffs2 mounts cleanly on mtdblock8 (whole flash partition).
        # jffs2 scans whole flash + finds the rootfs A magic section.
        rootfs_mtd = 'mtdblock8'
    else:
        kernel_off = 0x2700000
        rootfs_mtd = 'mtdblock7'   # slot B kernel+fs in mtd7 (UNTESTED — may need mtd8)
    print(f"[stock_uart] booting SLOT {slot}: kernel@0x{kernel_off:x}, root=/dev/{rootfs_mtd}")
    # Why getty -n -l /bin/sh instead of init=/bin/sh:
    # plain `init=/bin/sh` makes PID 1 a shell with NO controlling tty.
    # Busybox sh hits EOF on stdin → exits → kernel panic "Attempted to kill init".
    # getty does TIOCSCTTY to attach /dev/ttyAMA0 as controlling tty BEFORE exec'ing
    # the login program, so the spawned shell keeps reading from UART forever.
    # `-n` skips login prompt, `-l /bin/sh` uses sh as the login program.
    _do_reset_then(_PREAMBLE + [
        # Load slot's kernel from NAND into RAM at 0x42000000
        (f"nand read 0x42000000 0x{kernel_off:x} 0x400000",
         (b"=>", 60)),
        # ZTE U-Boot setenv has 16-arg max — quotes DON'T group args. Each
        # space-separated word counts. Required args:
        #   earlyprintk + keep_bootcon → MANDATORY for any post-"Starting kernel" output
        #   rootfstype=jffs2 → MANDATORY: kernel's auto-detect FAILS on mtdblock8
        #                      (it's the whole-flash partition, 128 MiB of mixed data)
        # Dropped vt100 (optional TERMTYPE for getty — busybox defaults are fine).
        # Arg count: setenv(1) + bootargs(1) + 13 cmdline tokens = 15 ✓
        (f"setenv bootargs 'console=ttyAMA0,115200n8 root=/dev/{rootfs_mtd} ro rootfstype=jffs2 earlyprintk keep_bootcon init=/sbin/getty -L -n -l /bin/sh 115200 ttyAMA0'",
         (b"=>", 5)),
        # bootm at +0x20 to skip 32-byte ZTE wrapper, exposing standard uImage
        ("bootm 0x42000020", 300),
    ])

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "log"
    rest = sys.argv[2:]
    handlers = {
        "log":          cmd_log,
        "send":         cmd_send,
        "wait":         cmd_wait,
        "auto_stock":   cmd_auto_stock,
        "auto_stock_verbose": cmd_auto_stock_verbose,
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
        "auto_bootm_stockport":    cmd_auto_bootm_stockport,
        "auto_bootm_stock_uart":   cmd_auto_bootm_stock_uart,
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
