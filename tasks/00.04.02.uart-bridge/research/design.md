# Research — sharing /dev/ttyUSB0 across host processes

## Problem

`tasks/00.04.flash-tool/flash.py` and any UART monitor (kotrace boot
trace capture, debug session, etc.) both want to read /dev/ttyUSB0
concurrently. Linux serial-port semantics are exclusive-open: whoever
holds the fd locks out everyone else with EBUSY.

Today's symptoms:
- `flash.py` holds UART for ~60s post-reset while listening to boot log
- Any parallel `python3 -c 'serial.Serial(...).read(...)'` fails with EBUSY
- Boot log captured by `flash.py` goes through `| tail -3` so we lose
  most of it; can't tee to a file without modifying flash.py per-call

## Alternatives evaluated

### A — `socat` one-liner

```bash
socat /dev/ttyUSB0,b115200,raw,echo=0 TCP-LISTEN:9999,reuseaddr,fork
```

Pros:
- Zero install (socat is on virtually every Ubuntu install)
- One line of config
- Multi-client read

Cons:
- **Cannot relay serial control lines** (DTR/RTS) from TCP. The
  device's reset mod uses DTR pulse — without that, the bridge is
  data-only and we'd still need raw access to /dev/ttyUSB0 for resets,
  which conflicts with socat owning it.
- No structured log file (would need a separate `| tee` consumer)
- Dies silently on cable disconnect; no auto-restart

Verdict: good as a 90% solution if we don't need DTR through TCP.
Useful for ad-hoc monitoring sessions.

### B — `ser2net` with RFC2217

```yaml
# /etc/ser2net.yaml
connection: &con01
  accepter: telnet,tcp,2000
  connector: serialdev,/dev/ttyUSB0,115200n81,local
```

Pros:
- **RFC2217** standard — Telnet COM Port Control extensions let the
  client toggle DTR, RTS, baud, parity over TCP
- `pyserial` has native `serial.Serial('rfc2217://host:port')` —
  literally a drop-in replacement for the direct serial path
- Battle-tested, runs as systemd service, handles disconnects
- Multi-client (with per-connection mode flags)
- Built-in logging via `--syslog` or `trace-{read,write}` directives

Cons:
- Requires `apt install ser2net` + writing a YAML config
- One more daemon to keep alive
- Slight learning curve for the YAML schema

Verdict: **the right long-term answer.** If we end up using TCP UART
in more than 2 places, do this. Pulling the trigger now is friction
without clear payback yet.

### C — Custom Python bridge

A ~100 LOC daemon that owns /dev/ttyUSB0 and exposes:
- **port 9999** — raw UART data (bidirectional, multi-client read,
  single-writer queue)
- **port 9998** — text control protocol (`DTR_PULSE`, `DTR_HIGH`,
  `DTR_LOW`, `STATUS`)
- **`/tmp/uart_bridge.log`** — append-only tee of all UART RX bytes,
  so `tail -f` always works

Pros:
- Full control over the protocol — exactly what our flash workflow
  needs, nothing more
- Easy to debug — pure Python, no opaque daemon
- Trivial to extend (add per-client filters, structured events, etc.)
- No additional system package required (just `pyserial`)

Cons:
- We maintain it. ~100 LOC isn't much, but every line of infrastructure
  is a line that can break at 3 AM during a debug session.
- Reinventing what ser2net already solved correctly.
- Disconnect/reconnect handling we have to write ourselves.

Verdict: **PoC choice.** Fast to validate end-to-end, easy to iterate.
If it earns its keep, the migration to ser2net is mechanical (replace
URL prefix in client; delete daemon).

## Decision

Build option C as the PoC under this task. Document the migration path
to option B in this folder's README.

Defer ser2net adoption until at least one of:
- a 2nd team member needs to attach UART
- the bridge crashes more than once a week
- we want to enable DTR/RTS/baud changes from remote
- we want to run the bridge as a systemd service

## DTR semantics for our device

The H3600 reset path:
1. Modified FTDI cable's DTR line is wired to the device's RESET pin
   (see `tools/dtr-mod/README.md`)
2. Driving DTR LOW asserts RESET; HIGH releases it
3. A reset pulse is: HIGH → LOW (~300 ms) → HIGH → (boot proceeds)

`pyserial`'s `setDTR(True)` sets DTR HIGH; `False` sets LOW. The
existing `lib/uart.py:_do_reset_then` does the pulse internally.

For the bridge:
- `DTR_HIGH` → `ser.setDTR(True)`
- `DTR_LOW`  → `ser.setDTR(False)`
- `DTR_PULSE` → composite: HIGH, sleep 0.3, LOW, sleep 0.3, HIGH

Only the bridge process holds the serial fd, so only the bridge can
issue these ioctls. Clients ask via TCP.

## Client API shape

For drop-in compatibility with existing `lib/uart.py` callers, the
bridge ships a tiny `lib_uart_tcp.py` that mimics pyserial:

```python
ser = serial_tcp.open(host='localhost', port=9999, control_port=9998)
ser.read(n)
ser.write(buf)
ser.setDTR(True)  # transparently sends DTR_HIGH on control_port
ser.reset_input_buffer()
ser.close()
```

A wrapper at the top of `lib/uart.py` picks transport by env var:
- `UART_TCP=1` → use lib_uart_tcp
- (default) → direct pyserial /dev/ttyUSB0

That makes the flash + monitor scripts trivially switchable per-run.

## Out of scope (for PoC)

- Authentication / TLS — local socket only
- Multi-writer arbitration — first writer queue, others see backpressure
- Cross-host bridging — single-host only
- Bandwidth metering / rate limiting
- Reconnect on cable USB plug-out (just die and `systemctl restart`-able)
