"""pyserial-compatible client for the uart_bridge daemon.

Drop-in replacement for `serial.Serial(...)` when you want flash.py /
lib/uart.py to go through the bridge instead of opening /dev/ttyUSB0
directly. Supports the subset that lib/uart.py actually uses:

    read(n)           — blocking read, honors timeout
    write(buf)        — synchronous write
    setDTR(bool)      — sends DTR_HIGH/DTR_LOW on the control port
    reset_input_buffer()
    close()

Doesn't try to be a fully-faithful pyserial impl. If you find lib/uart.py
calls something not implemented here, add it — pyserial's API is small
when you only need the data path.
"""

import socket
import time


class TcpSerial:
    def __init__(self, host="localhost", data_port=9999, ctl_port=9998,
                 timeout=0.1):
        self.host       = host
        self.data_port  = data_port
        self.ctl_port   = ctl_port
        self.timeout    = timeout

        self._data = socket.create_connection((host, data_port))
        self._data.settimeout(timeout)
        self._buf  = b""    # buffer for partial reads

        # Control socket — connect lazily, keep alive between commands
        self._ctl  = socket.create_connection((host, ctl_port))
        self._ctl.settimeout(2.0)
        # Drain the banner so it doesn't pollute later reads
        try: self._ctl.recv(1024)
        except: pass

    # -------- pyserial-compatible surface --------

    @property
    def is_open(self): return self._data is not None

    @property
    def dtr(self):
        """We don't track DTR here; the bridge does. Returns last set value
        if you've called setDTR; otherwise None."""
        return getattr(self, "_dtr_last", None)

    @dtr.setter
    def dtr(self, v): self.setDTR(v)

    def read(self, n):
        """Read up to n bytes, honoring self.timeout."""
        if len(self._buf) >= n:
            out, self._buf = self._buf[:n], self._buf[n:]
            return out

        deadline = time.time() + (self.timeout if self.timeout else 0)
        while len(self._buf) < n:
            remaining = max(0.0, deadline - time.time())
            self._data.settimeout(remaining if self.timeout else None)
            try:
                chunk = self._data.recv(4096)
            except socket.timeout:
                break
            except OSError:
                break
            if not chunk:
                break
            self._buf += chunk
            if self.timeout is not None and time.time() >= deadline:
                break

        out, self._buf = self._buf[:n], self._buf[n:]
        return out

    def write(self, buf):
        if isinstance(buf, str):
            buf = buf.encode()
        self._data.sendall(buf)
        return len(buf)

    def flush(self):
        """pyserial compat — TCP socket flushes on send; nothing to do."""
        pass

    def reset_input_buffer(self):
        # drain anything in flight on the data socket
        self._data.settimeout(0.01)
        try:
            while True:
                if not self._data.recv(4096):
                    break
        except (socket.timeout, OSError):
            pass
        self._data.settimeout(self.timeout)
        self._buf = b""

    def setDTR(self, level):
        cmd = b"DTR_HIGH\n" if level else b"DTR_LOW\n"
        self._ctl.sendall(cmd)
        try: self._ctl.recv(1024)   # ack
        except: pass
        self._dtr_last = bool(level)

    def dtr_pulse(self):
        """Bridge-specific shortcut: one round-trip DTR HIGH→LOW→HIGH."""
        self._ctl.sendall(b"DTR_PULSE\n")
        try: self._ctl.recv(1024)
        except: pass

    def close(self):
        try: self._data.close()
        except: pass
        try: self._ctl.close()
        except: pass
        self._data = None


def open_port(host="localhost", data_port=9999, ctl_port=9998, timeout=0.1):
    """Convenience factory mirroring lib/uart.py:open_port."""
    return TcpSerial(host=host, data_port=data_port, ctl_port=ctl_port,
                     timeout=timeout)
