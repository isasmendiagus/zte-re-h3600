#!/usr/bin/env python3
"""ten - drive the FT232R TEN (TXDEN, CBUS2) pin via UART BREAK.

The TEN pin idles LOW and goes HIGH while the UART transmitter is active.
Linux can hold the UART in BREAK state indefinitely via TIOCSBRK / TIOCCBRK,
which keeps TEN HIGH for as long as we want.

  ten.py status                 read current modem lines (informational)
  ten.py high                   start BREAK -> TEN goes HIGH (sustained)
  ten.py low                    stop BREAK  -> TEN goes LOW
  ten.py pulse [ms]             TEN HIGH for ms (default 300), then LOW
  ten.py hold                   start BREAK and block until Ctrl-C (then LOW)

NB: while BREAK is asserted the TXD line is held LOW — don't run this on a
port that is concurrently doing real UART communication.
"""
import fcntl
import os
import signal
import sys
import termios
import time

PORT = '/dev/ttyUSB0'

# These constants aren't always exported in Python's termios on Linux.
TIOCSBRK = 0x5427  # turn break on
TIOCCBRK = 0x5428  # turn break off


def open_port():
    fd = os.open(PORT, os.O_RDWR | os.O_NOCTTY)
    # Make sure baud/format is sane; doesn't really matter for BREAK behaviour
    # but a known state helps. 9600 8N1.
    attrs = termios.tcgetattr(fd)
    attrs[4] = termios.B9600  # ispeed
    attrs[5] = termios.B9600  # ospeed
    termios.tcsetattr(fd, termios.TCSANOW, attrs)
    return fd


def break_on(fd):
    fcntl.ioctl(fd, TIOCSBRK)


def break_off(fd):
    fcntl.ioctl(fd, TIOCCBRK)


def cmd_status(fd):
    import struct
    bits = struct.unpack('I', fcntl.ioctl(fd, termios.TIOCMGET, struct.pack('I', 0)))[0]
    print(f"modem bits=0x{bits:x}  DTR={bool(bits & termios.TIOCM_DTR)} RTS={bool(bits & termios.TIOCM_RTS)} CTS={bool(bits & termios.TIOCM_CTS)} DSR={bool(bits & termios.TIOCM_DSR)} DCD={bool(bits & termios.TIOCM_CAR)}")
    print("(TEN/TXDEN is a CBUS pin — not visible via TIOCMGET; measure with a meter)")


def cmd_high(fd):
    break_on(fd)
    print("BREAK on -> TEN should be HIGH")


def cmd_low(fd):
    break_off(fd)
    print("BREAK off -> TEN should be LOW")


def cmd_pulse(fd, ms):
    break_on(fd)
    print(f"BREAK on -> TEN HIGH for {ms} ms")
    time.sleep(ms / 1000.0)
    break_off(fd)
    print("BREAK off -> TEN LOW")


def cmd_hold(fd):
    break_on(fd)
    print("BREAK on -> TEN HIGH.  Ctrl-C to release.")

    def release(*_):
        break_off(fd)
        print("\nBREAK off -> TEN LOW.")
        sys.exit(0)

    signal.signal(signal.SIGINT, release)
    signal.signal(signal.SIGTERM, release)
    signal.pause()


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    cmd = sys.argv[1]
    fd = open_port()
    try:
        if cmd == 'status':
            cmd_status(fd)
        elif cmd == 'high':
            cmd_high(fd)
        elif cmd == 'low':
            cmd_low(fd)
        elif cmd == 'pulse':
            ms = int(sys.argv[2]) if len(sys.argv) > 2 else 300
            cmd_pulse(fd, ms)
        elif cmd == 'hold':
            cmd_hold(fd)
        else:
            print(f"unknown command: {cmd}")
            print(__doc__)
            sys.exit(1)
    finally:
        # 'high' / 'low' / 'pulse' / 'status' all exit here.  'hold' exits via signal.
        os.close(fd)


if __name__ == '__main__':
    main()
