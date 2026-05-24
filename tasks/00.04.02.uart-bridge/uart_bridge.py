#!/usr/bin/env python3
"""PoC: bridge /dev/ttyUSB0 to TCP with separate data + control channels.

- Owns /dev/ttyUSB0 exclusively (so no other host process can EBUSY us).
- Streams UART RX bytes to:
    * every connected client on PORT_DATA (9999)
    * an append-only log at LOG_PATH (/tmp/uart_bridge.log)
- Forwards client→bridge writes on PORT_DATA back to UART TX (first-come
  first-served; we don't arbitrate, we just queue).
- Accepts text control commands on PORT_CTL (9998):
    DTR_PULSE       — HIGH→LOW(300ms)→HIGH (the device reset sequence)
    DTR_HIGH        — drive DTR high
    DTR_LOW         — drive DTR low
    STATUS          — dump current state
    QUIT            — close this control connection (bridge keeps running)

Stop the bridge with Ctrl-C (it will close /dev/ttyUSB0 cleanly).
"""

import argparse
import os
import select
import socket
import sys
import threading
import time
from pathlib import Path

try:
    import serial
except ImportError:
    sys.exit("install pyserial: pip install pyserial")


DEFAULT_DEVICE   = "/dev/ttyUSB0"
DEFAULT_BAUD     = 115200
DEFAULT_PORT_DATA = 9999
DEFAULT_PORT_CTL  = 9998
DEFAULT_LOG       = "/tmp/uart_bridge.log"
DTR_PULSE_SEC     = 0.30


class Bridge:
    """Single-process bridge: one serial port, multiple TCP fan-out."""

    def __init__(self, device, baud, port_data, port_ctl, log_path):
        self.device     = device
        self.baud       = baud
        self.port_data  = port_data
        self.port_ctl   = port_ctl
        self.log_path   = Path(log_path)

        self.ser = serial.Serial(device, baud, timeout=0.05)
        # IMPORTANT: this device's modded FTDI cable uses DTR to drive a
        # power relay (NOT a TTL reset line):
        #   DTR HIGH (=True)  → relay OPEN  → device POWERED OFF
        #   DTR LOW  (=False) → relay CLOSED → device POWERED ON
        # pyserial may pull DTR active when the port opens; that would
        # immediately power-off the device. Force LOW so the device stays
        # alive while the bridge owns the port.
        self.ser.setDTR(False)
        self.ser.reset_input_buffer()
        self.ser.reset_output_buffer()

        self.log_fh = open(self.log_path, "ab", buffering=0)

        self.data_clients = []      # list[socket]
        self.data_lock    = threading.Lock()

        self.running = True

        print(f"[bridge] owning {device} @ {baud}", flush=True)
        print(f"[bridge] data port  tcp/{port_data}", flush=True)
        print(f"[bridge] ctl  port  tcp/{port_ctl}", flush=True)
        print(f"[bridge] log file   {log_path}", flush=True)

    # -------- accept loops --------

    def serve_data(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(("0.0.0.0", self.port_data))
        s.listen(8)
        while self.running:
            try:
                cli, addr = s.accept()
            except OSError:
                break
            cli.setblocking(False)
            with self.data_lock:
                self.data_clients.append(cli)
            print(f"[bridge] data client connect {addr}", flush=True)

    def serve_ctl(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(("0.0.0.0", self.port_ctl))
        s.listen(8)
        while self.running:
            try:
                cli, addr = s.accept()
            except OSError:
                break
            threading.Thread(
                target=self._handle_ctl_client,
                args=(cli, addr),
                daemon=True,
            ).start()

    def _handle_ctl_client(self, cli, addr):
        cli.sendall(b"# uart_bridge ctl. commands: DTR_PULSE DTR_HIGH DTR_LOW STATUS QUIT\n")
        buf = b""
        while self.running:
            try:
                chunk = cli.recv(256)
            except OSError:
                break
            if not chunk:
                break
            buf += chunk
            while b"\n" in buf:
                line, buf = buf.split(b"\n", 1)
                cmd = line.strip().decode("ascii", errors="replace").upper()
                if not cmd:
                    continue
                reply = self._exec_ctl_cmd(cmd)
                try:
                    cli.sendall(reply + b"\n")
                except OSError:
                    return
                if cmd == "QUIT":
                    cli.close()
                    return
        try: cli.close()
        except: pass

    def _exec_ctl_cmd(self, cmd):
        # On this device DTR HIGH = power OFF (relay open),
        # DTR LOW = power ON (relay closed). A "reset" is power-cycle:
        # HIGH (off, hold) → LOW (on, settle). End in LOW so the device
        # actually boots after the pulse.
        if cmd == "DTR_PULSE":
            self.ser.setDTR(True)              # power OFF
            time.sleep(DTR_PULSE_SEC)
            self.ser.setDTR(False)             # power ON (leave on!)
            return b"OK pulse"
        if cmd == "DTR_HIGH":                  # = power OFF
            self.ser.setDTR(True);  return b"OK high (device off)"
        if cmd == "DTR_LOW":                   # = power ON
            self.ser.setDTR(False); return b"OK low (device on)"
        if cmd == "STATUS":
            return (
                f"device={self.device} baud={self.baud} "
                f"open={self.ser.is_open} dtr={self.ser.dtr} "
                f"data_clients={len(self.data_clients)} "
                f"log={self.log_path}"
            ).encode()
        if cmd == "QUIT":
            return b"OK bye"
        return b"ERR unknown command"

    # -------- main pump --------

    def pump(self):
        """Pump bytes UART→clients + log; pump client→UART writes."""
        # Use select for client write-readability
        while self.running:
            try:
                rx = self.ser.read(4096)
            except OSError as e:
                print(f"[bridge] serial read err: {e}", flush=True)
                break
            if rx:
                # tee to log + every data client
                try: self.log_fh.write(rx)
                except: pass
                self._fanout(rx)

            # check client writes
            self._drain_client_writes()

    def _fanout(self, data):
        dead = []
        with self.data_lock:
            for c in self.data_clients:
                try:
                    c.sendall(data)
                except OSError:
                    dead.append(c)
            for d in dead:
                self.data_clients.remove(d)
        for d in dead:
            try: d.close()
            except: pass

    def _drain_client_writes(self):
        with self.data_lock:
            clients = list(self.data_clients)
        if not clients:
            return
        readable, _, _ = select.select(clients, [], [], 0)
        for c in readable:
            try:
                chunk = c.recv(4096)
            except OSError:
                chunk = b""
            if not chunk:
                with self.data_lock:
                    if c in self.data_clients:
                        self.data_clients.remove(c)
                try: c.close()
                except: pass
                continue
            try:
                self.ser.write(chunk)
            except OSError as e:
                print(f"[bridge] serial write err: {e}", flush=True)

    def shutdown(self):
        self.running = False
        with self.data_lock:
            for c in self.data_clients:
                try: c.close()
                except: pass
            self.data_clients = []
        try: self.ser.close()
        except: pass
        try: self.log_fh.close()
        except: pass


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n", 1)[0])
    ap.add_argument("--device",    default=DEFAULT_DEVICE)
    ap.add_argument("--baud",      default=DEFAULT_BAUD, type=int)
    ap.add_argument("--port-data", default=DEFAULT_PORT_DATA, type=int)
    ap.add_argument("--port-ctl",  default=DEFAULT_PORT_CTL,  type=int)
    ap.add_argument("--log",       default=DEFAULT_LOG)
    args = ap.parse_args()

    b = Bridge(args.device, args.baud, args.port_data, args.port_ctl, args.log)

    threading.Thread(target=b.serve_data, daemon=True).start()
    threading.Thread(target=b.serve_ctl,  daemon=True).start()

    try:
        b.pump()
    except KeyboardInterrupt:
        print("\n[bridge] caught Ctrl-C, shutting down", flush=True)
    finally:
        b.shutdown()


if __name__ == "__main__":
    main()
