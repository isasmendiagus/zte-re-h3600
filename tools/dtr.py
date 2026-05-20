#!/usr/bin/env python3
"""dtr - tiny CLI / REPL to control DTR, RTS, TEN and PWREN on an FT232 adapter.

USAGE
  dtr.py [-p /dev/ttyUSB0]                            # interactive REPL
  dtr.py [-p ...] status
  dtr.py [-p ...] <line> low|high|toggle|pulse [ms]
  dtr.py [-p ...] hold dtr=low rts=high pwren=high    # hold sustained, Ctrl-C to release

LINES
  dtr   TIOCM_DTR.  Idle HIGH, asserted LOW (on stock FT232 EEPROM).
  rts   TIOCM_RTS.  Same polarity as dtr.
  ten   TXDEN (CBUS2) driven via UART BREAK.  Idle LOW, HIGH while BREAK is held.
  pwren PWREN# (CBUS3) driven via USB authorize/de-authorize.  Idle LOW (device
        enumerated), HIGH while de-authorized.  NEEDS root or udev rule on
        /sys/bus/usb/devices/<X>/authorized -- script falls back to `sudo tee`
        automatically.  De-authorizing makes /dev/ttyUSB0 disappear until you
        bring pwren back LOW.

NOTES
  - DTR/RTS state is transient: when the process exits and hupcl is on, the
    kernel de-asserts both.  Use `hold` to sustain.
  - TEN HIGH (BREAK on) also holds TXD LOW -- don't combine with real UART TX.
  - PWREN HIGH suspends the device; ttyUSB0 vanishes.  This is the intended
    behavior for using PWREN# as an external control line.
"""
import argparse
import fcntl
import glob
import os
import signal
import struct
import subprocess
import sys
import termios
import time

# ----- DTR / RTS via TIOCM -----
TIOCM_BIT = {'dtr': termios.TIOCM_DTR, 'rts': termios.TIOCM_RTS}
INPUT_BITS = {
    'CTS': termios.TIOCM_CTS, 'DSR': termios.TIOCM_DSR,
    'DCD': termios.TIOCM_CAR, 'RNG': termios.TIOCM_RNG,
}
TIOCSBRK = 0x5427
TIOCCBRK = 0x5428

INVERTED = False  # via --invert; swaps assert/release for DTR & RTS only


def _ioget(fd):
    return struct.unpack('I', fcntl.ioctl(fd, termios.TIOCMGET, struct.pack('I', 0)))[0]


def _tiocm_set(fd, line, pin_low):
    """pin_low=True -> drive pin LOW (TIOCMBIS), False -> HIGH (TIOCMBIC).
    Inverted EEPROM flips the API call so user-facing meaning stays pin-level."""
    assert_call = pin_low
    if INVERTED:
        assert_call = not assert_call
    op = termios.TIOCMBIS if assert_call else termios.TIOCMBIC
    fcntl.ioctl(fd, op, struct.pack('I', TIOCM_BIT[line]))


def _tiocm_is_low(fd, line):
    asserted = bool(_ioget(fd) & TIOCM_BIT[line])
    return (not asserted) if INVERTED else asserted


# ----- TEN via UART BREAK -----
# BREAK on  -> TXD held LOW -> the UART transmitter is active -> TXDEN goes HIGH.
# BREAK off -> idle          -> TXDEN returns LOW.
def _ten_set(fd, pin_low):
    fcntl.ioctl(fd, TIOCCBRK if pin_low else TIOCSBRK)


# We can't read TXDEN back from the host, so track our last command.
_TEN_STATE = {'low': True}


def _ten_is_low():
    return _TEN_STATE['low']


# ----- PWREN# via USB authorize sysfs -----
def find_ftdi_sysfs(vid=0x0403, pid=0x6001):
    for vfile in glob.glob('/sys/bus/usb/devices/*/idVendor'):
        try:
            with open(vfile) as f:
                if int(f.read().strip(), 16) != vid:
                    continue
            with open(vfile.replace('idVendor', 'idProduct')) as f:
                if int(f.read().strip(), 16) != pid:
                    continue
            return os.path.dirname(vfile)
        except OSError:
            continue
    return None


def _sysfs_write(path, value):
    """Write `value` to `path`. Falls back to `sudo tee` if direct write is denied."""
    try:
        with open(path, 'w') as f:
            f.write(value)
        return
    except PermissionError:
        pass
    # fall back to sudo tee
    r = subprocess.run(
        ['sudo', 'tee', path],
        input=value.encode(), capture_output=True,
    )
    if r.returncode != 0:
        raise PermissionError(f"can't write {path} (even with sudo): {r.stderr.decode()}")


def _pwren_set(sysfs, pin_low):
    """pin_low=True -> authorized=1 (enumerated, PWREN# LOW).
       pin_low=False -> authorized=0 (de-authorized, PWREN# HIGH)."""
    if not sysfs:
        raise RuntimeError("FT232 USB device not found in sysfs")
    _sysfs_write(os.path.join(sysfs, 'authorized'), '1' if pin_low else '0')


def _pwren_is_low(sysfs):
    if not sysfs:
        return None
    try:
        with open(os.path.join(sysfs, 'authorized')) as f:
            return f.read().strip() == '1'
    except OSError:
        return None


# ----- unified line API -----
def set_line(fd, sysfs, line, level):
    """level in {low, high, toggle, 0, 1}."""
    if level in ('toggle', 't'):
        cur = is_low(fd, sysfs, line)
        if cur is None:
            raise RuntimeError(f"can't read current state of {line} to toggle")
        pin_low = not cur
    elif level in ('low', '0', 'l'):
        pin_low = True
    elif level in ('high', '1', 'h'):
        pin_low = False
    else:
        raise ValueError(f"unknown level {level!r}")
    apply_level(fd, sysfs, line, pin_low)


def apply_level(fd, sysfs, line, pin_low):
    if line in TIOCM_BIT:
        _tiocm_set(fd, line, pin_low)
    elif line == 'ten':
        _ten_set(fd, pin_low)
        _TEN_STATE['low'] = pin_low
    elif line == 'pwren':
        _pwren_set(sysfs, pin_low)
    else:
        raise ValueError(f"unknown line {line!r}")


def is_low(fd, sysfs, line):
    if line in TIOCM_BIT:
        return _tiocm_is_low(fd, line)
    if line == 'ten':
        return _ten_is_low()
    if line == 'pwren':
        return _pwren_is_low(sysfs)
    raise ValueError(line)


def status_str(fd, sysfs):
    b = _ioget(fd)
    out = []
    for name in TIOCM_BIT:
        pin = 'LOW' if _tiocm_is_low(fd, name) else 'HIGH'
        out.append(f"{name.upper()}={pin}")
    out.append(f"TEN={'LOW' if _ten_is_low() else 'HIGH'}")
    pwren = _pwren_is_low(sysfs)
    out.append(f"PWREN={'LOW' if pwren else ('HIGH' if pwren is False else '?')}")
    for name, mask in INPUT_BITS.items():
        out.append(f"{name}={'1' if b & mask else '0'}")
    polarity = " [DTR/RTS inverted]" if INVERTED else ""
    return f"bits=0x{b:x}{polarity}  " + "  ".join(out)


# default active state per line — used by `pulse` to know which direction is "active"
DEFAULT_IDLE_LOW = {'dtr': False, 'rts': False, 'ten': True, 'pwren': True}


def pulse(fd, sysfs, line, ms):
    """Briefly drive the line to its non-idle state for `ms` ms, then restore."""
    idle_low = DEFAULT_IDLE_LOW[line]
    active_low = not idle_low
    apply_level(fd, sysfs, line, idle_low)
    time.sleep(0.02)
    apply_level(fd, sysfs, line, active_low)
    time.sleep(ms / 1000.0)
    apply_level(fd, sysfs, line, idle_low)


# ----- REPL & hold mode -----
ALL_LINES = ('dtr', 'rts', 'ten', 'pwren')


def repl(fd, sysfs):
    print(f"dtr REPL.  port held open. lines: {', '.join(ALL_LINES)}.  type 'help' or 'q'.")
    print(status_str(fd, sysfs))
    help_text = (
        "  <line> low|high|toggle        set line state (lines: dtr rts ten pwren)\n"
        "  pulse [line] [ms]             pulse line to active state (default: dtr 300ms)\n"
        "  s | status                    show current state\n"
        "  q | quit | exit               restore idle states and close\n"
    )
    try:
        while True:
            try:
                raw = input('dtr> ').strip()
            except EOFError:
                print(); break
            if not raw:
                continue
            parts = raw.split()
            cmd = parts[0].lower()
            try:
                if cmd in ('q', 'quit', 'exit'):
                    break
                elif cmd in ('h', 'help', '?'):
                    print(help_text, end='')
                elif cmd in ('s', 'status'):
                    print(status_str(fd, sysfs))
                elif cmd in ALL_LINES:
                    if len(parts) < 2:
                        print("need level: low|high|toggle"); continue
                    set_line(fd, sysfs, cmd, parts[1].lower())
                    print(status_str(fd, sysfs))
                elif cmd == 'pulse':
                    rest = parts[1:]
                    line = 'dtr'
                    if rest and rest[0].lower() in ALL_LINES:
                        line = rest[0].lower(); rest = rest[1:]
                    ms = int(rest[0]) if rest else 300
                    pulse(fd, sysfs, line, ms)
                    print(f"pulsed {line.upper()} to active for {ms} ms")
                    print(status_str(fd, sysfs))
                else:
                    print(f"unknown: {cmd!r}.  type 'help'.")
            except Exception as e:
                print(f"error: {e}")
    finally:
        restore_idle(fd, sysfs)
        print("restored idle states, closing.")


def restore_idle(fd, sysfs):
    """Best-effort return all controllable lines to their idle state on exit."""
    for line, idle_low in DEFAULT_IDLE_LOW.items():
        try:
            apply_level(fd, sysfs, line, idle_low)
        except Exception:
            pass


def hold(fd, sysfs, spec):
    """spec like ['dtr=low','pwren=high'] -- apply then wait for signal."""
    for item in spec:
        if '=' not in item:
            raise SystemExit(f"bad hold spec {item!r}, want e.g. pwren=high")
        line, lvl = item.split('=', 1)
        set_line(fd, sysfs, line.lower(), lvl.lower())
    print(status_str(fd, sysfs))
    print("holding -- Ctrl-C to release and exit")

    def _release(*_):
        restore_idle(fd, sysfs)
        print("\nrestored idle states, closing.")
        sys.exit(0)

    signal.signal(signal.SIGINT, _release)
    signal.signal(signal.SIGTERM, _release)
    signal.pause()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('-p', '--port', default='/dev/ttyUSB0')
    ap.add_argument('--invert', action='store_true',
                    help='adapter has DTR/RTS inverted in EEPROM; keeps low/high meaning pin-level')
    ap.add_argument('cmd', nargs='?')
    ap.add_argument('args', nargs='*')
    a = ap.parse_args()

    global INVERTED
    INVERTED = a.invert

    sysfs = find_ftdi_sysfs()

    # `pwren` may be invoked when ttyUSB0 is gone (device de-authorized).
    needs_tty = (a.cmd != 'pwren') and (a.cmd != 'status' or os.path.exists(a.port))
    fd = -1
    if needs_tty:
        fd = os.open(a.port, os.O_RDWR | os.O_NOCTTY)

    try:
        if a.cmd is None:
            if fd < 0:
                fd = os.open(a.port, os.O_RDWR | os.O_NOCTTY)
            repl(fd, sysfs)
        elif a.cmd == 'status':
            if fd >= 0:
                print(status_str(fd, sysfs))
            else:
                pwren = _pwren_is_low(sysfs)
                print(f"(ttyUSB closed) PWREN={'LOW' if pwren else ('HIGH' if pwren is False else '?')}")
        elif a.cmd in ALL_LINES:
            if not a.args:
                ap.error(f"{a.cmd} needs a level: low|high|toggle|pulse [ms]")
            if a.args[0] == 'pulse':
                ms = int(a.args[1]) if len(a.args) > 1 else 300
                pulse(fd, sysfs, a.cmd, ms)
                print(f"pulsed {a.cmd.upper()} to active for {ms} ms")
            else:
                set_line(fd, sysfs, a.cmd, a.args[0].lower())
            if fd >= 0:
                print(status_str(fd, sysfs))
        elif a.cmd == 'hold':
            if fd < 0:
                fd = os.open(a.port, os.O_RDWR | os.O_NOCTTY)
            hold(fd, sysfs, a.args)
        else:
            ap.error(f"unknown command {a.cmd!r}")
    finally:
        if fd >= 0:
            try:
                os.close(fd)
            except OSError:
                pass


if __name__ == '__main__':
    main()
