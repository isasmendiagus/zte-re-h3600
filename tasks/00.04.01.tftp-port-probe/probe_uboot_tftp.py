#!/usr/bin/env python3
"""probe_uboot_tftp.py — discover if ZTE U-Boot supports a custom TFTP port.

Read-mostly probe. NEVER calls saveenv; setenv changes evaporate on next
power-cycle. NO NAND writes, NO bootm, NO flash.

Captures:
  - full `printenv` output (default env on this device)
  - `help tftp` output (whether the tftp command documents a port option)
  - whether `setenv tftpdstp 6969 ; printenv tftpdstp` round-trips
    (also tries `tftpdstport` and `tftp_port` as alternative names)

Output: <this_dir>/capture.log

Full design notes: tasks/00.04.01.tftp-port-probe/README.md
"""
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent           # tasks/00.04.01.tftp-port-probe/
REPO = HERE.parents[1]                           # ZTE/ (repo root)
sys.path.insert(0, str(REPO / "lib"))
import uart

CAPTURE = HERE / "capture.log"


# Wait pattern is (bytes, timeout_seconds). uart._do_reset_then will wait
# until the pattern appears in the stream before sending the next cmd.
# Using the `=>` prompt as the synchronizer means we never sleep longer
# than necessary and we don't race against U-Boot's reply.
WAIT_PROMPT = (b"=>", 10)
WAIT_PROMPT_LONG = (b"=>", 30)   # for printenv which dumps a lot of bytes


PROBE_SEQ = uart._PREAMBLE + [
    # Tag the log so we can find this section easily if uart.LOG is shared.
    ("# === PROBE: default env ===", WAIT_PROMPT),
    ("printenv", WAIT_PROMPT_LONG),

    ("# === PROBE: help for tftp command ===", WAIT_PROMPT),
    ("help tftp", WAIT_PROMPT),

    # Try the standard mainline name first.
    ("# === PROBE: try tftpdstp (mainline U-Boot's std name) ===", WAIT_PROMPT),
    ("setenv tftpdstp 6969", WAIT_PROMPT),
    ("printenv tftpdstp", WAIT_PROMPT),

    # Some forks use a longer name.
    ("# === PROBE: try tftpdstport (alternate spelling) ===", WAIT_PROMPT),
    ("setenv tftpdstport 6969", WAIT_PROMPT),
    ("printenv tftpdstport", WAIT_PROMPT),

    # And a third spelling seen in older trees.
    ("# === PROBE: try tftp_port (third candidate) ===", WAIT_PROMPT),
    ("setenv tftp_port 6969", WAIT_PROMPT),
    ("printenv tftp_port", WAIT_PROMPT),

    # Clean up — un-set the vars we created. (Belt-and-suspenders; nothing
    # was saved to NAND so this also evaporates on reset.)
    ("# === PROBE: cleanup (no saveenv called anywhere above) ===", WAIT_PROMPT),
    ("setenv tftpdstp",     WAIT_PROMPT),
    ("setenv tftpdstport",  WAIT_PROMPT),
    ("setenv tftp_port",    WAIT_PROMPT),

    ("# === PROBE: done; resetting ===", WAIT_PROMPT),
    ("reset", 5),
]


def main() -> int:
    # Redirect uart's log writes to our local capture file (default is
    # /tmp/uart.log which gets clobbered by every other UART tool run).
    uart.LOG = str(CAPTURE)
    print(f"[probe] capturing UART to {CAPTURE}")
    print(f"[probe] this run will: DTR-reset → U-Boot prompt → "
          f"~{len(PROBE_SEQ)} commands → reset")
    print(f"[probe] no saveenv, no nand-write, no bootm")
    return uart._do_reset_then(PROBE_SEQ) or 0


if __name__ == "__main__":
    sys.exit(main())
