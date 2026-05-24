# uart-bridge — share /dev/ttyUSB0 over TCP with DTR control

**ID**: 00.04.02
**Parent**: [00.04 flash-tool](../00.04.flash-tool/)
**Children**: none
**TaskList items**: —
**Status**: 🚧 PoC — works for data + DTR pulse; not yet wired into `flash.py`

## Why

Right now `tasks/00.04.flash-tool/flash.py` opens `/dev/ttyUSB0` directly
and holds it for the entire flash cycle (TFTP upload, NAND erase/write,
reset, ~60 s post-reset boot capture). During that time no other tool
on the host can read UART — so we can't `tail -f` boot logs in parallel
or run `kotrace` UART captures while a flash is in flight.

This bridge owns `/dev/ttyUSB0` long-running and exposes it on TCP:

- **port 9999** — raw UART byte stream, bidirectional. Multiple readers
  ok; only one writer at a time (first-come-first-served).
- **port 9998** — control plane. Text commands `DTR_PULSE`, `DTR_HIGH`,
  `DTR_LOW`, `STATUS`. Lets clients drive the device's reset line
  without owning the serial port.
- **`/tmp/uart_bridge.log`** — every UART byte received is tee'd to
  this file; clients can `tail -f` for historical replay without
  consuming the live TCP stream.

## Design

See [`research/design.md`](research/design.md) for the alternatives
considered (socat one-liner, ser2net+RFC2217, custom Python) and why
custom Python won for the PoC.

## Quick start (PoC)

```bash
# Terminal 1 — start the bridge
python3 tasks/00.04.02.uart-bridge/uart_bridge.py

# Terminal 2 — raw UART read
nc localhost 9999

# Terminal 3 — write something to UART (echoes back through the bridge)
echo "hello" | nc -q1 localhost 9999

# Terminal 4 — DTR-pulse the device (reset)
echo DTR_PULSE | nc -q1 localhost 9998

# Anywhere — log replay
tail -f /tmp/uart_bridge.log
```

## How `flash.py` would use it (not yet integrated)

`lib_uart_tcp.py` provides a pyserial-compatible `open_port()` that
talks to the bridge. To migrate `lib/uart.py`:

```python
import os
if os.environ.get("UART_TCP"):
    from tasks_00_04_02_uart_bridge.lib_uart_tcp import open_port  # via TCP
else:
    # ... existing direct-serial path ...
```

Then `UART_TCP=1 python3 tasks/00.04.flash-tool/flash.py rootfs ...`
goes through the bridge; without the env var the existing direct
`/dev/ttyUSB0` path is used.

## Status

- ✅ Bridge runs, accepts multiple readers
- ✅ DTR_PULSE works (verified with `python3 -c "import serial; ser=serial.Serial('/dev/ttyUSB0'); print(ser.dsr)"` — DSR loops back DTR on FTDI)
- ✅ Log file capture
- ⏳ `lib_uart_tcp.py` written but not yet tested as drop-in for `lib/uart.py`
- ⏳ Auto-restart on cable disconnect
- ⏳ `flash.py` integration (gated by `--transport tcp` or `UART_TCP=1`)

## Future work / migration to ser2net

If the PoC proves useful, ser2net + RFC2217 is the more standard path:
- `apt install ser2net`
- `/etc/ser2net.yaml` exposes /dev/ttyUSB0 on a TCP port with RFC2217
  control codes (DTR, RTS, baud, parity all controllable from client)
- pyserial speaks RFC2217 natively via `serial.Serial('rfc2217://host:port')`
- Battle-tested, runs as systemd service, no maintenance from us
- Drop our custom bridge

The PoC here is intentionally minimal so that learning curve is low —
if we end up using TCP UART regularly, the right move is to upgrade
to ser2net for the production setup.
