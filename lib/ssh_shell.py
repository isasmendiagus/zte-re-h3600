#!/usr/bin/env python3
"""Send shell commands to the H3600 via paramiko invoke_shell (router blocks `ssh user host cmd`).

Usage:
    ./ssh_shell.py "uname -a" "lspci -vv" ...    # one shot
    cat cmds.txt | ./ssh_shell.py -              # from stdin

Returns combined output of all commands.

NOTE on sentinel: previous version used literal "@@DONE_$$_MARKER@@" which
matched the terminal's echo of the SEND line and broke out before the command
actually ran. We now compute the shell PID once and wait for the expanded
form, which only appears after the command has finished executing.
"""
import sys, time, re, paramiko

HOST, USER, PASS = "192.168.1.1", "admin", "UkuGPeyRDU"
SENT_TEMPLATE = "DONE_$$_MARK_v2"          # literal text we send
SENT_REGEX    = rb"DONE_(\d+)_MARK_v2"     # what we read back after expansion

def run(cmds, timeout=90):
    cli = paramiko.SSHClient()
    cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    cli.connect(HOST, username=USER, password=PASS,
                allow_agent=False, look_for_keys=False, timeout=10)
    sh = cli.invoke_shell(width=200, height=50)

    # Eat banner/motd.
    time.sleep(0.5)
    while sh.recv_ready():
        sh.recv(65536); time.sleep(0.05)

    # Capture shell PID for the expanded sentinel.
    sh.send(f"echo READY_{SENT_TEMPLATE}\n")
    buf = bytearray()
    deadline = time.time() + 5
    pid = None
    while time.time() < deadline:
        if sh.recv_ready():
            buf.extend(sh.recv(65536))
            m = re.search(rb"READY_" + SENT_REGEX, bytes(buf))
            if m:
                pid = m.group(1).decode()
                break
        time.sleep(0.05)
    if not pid:
        raise RuntimeError("could not capture shell PID for sentinel")
    sentinel = f"DONE_{pid}_MARK_v2".encode()

    out = bytearray()
    for c in cmds:
        sh.send(c + f"; echo {SENT_TEMPLATE}\n")
        cmd_buf = bytearray()
        deadline = time.time() + timeout
        while time.time() < deadline:
            if sh.recv_ready():
                cmd_buf.extend(sh.recv(65536))
                # We need TWO copies of the expanded sentinel in the stream:
                # 1) the terminal echo of our SEND line (text contains "$$" so
                #    this never matches the expanded regex), and
                # 2) the actual echo from the shell (expanded PID, matches).
                # In practice the terminal echoes the literal command, then the
                # shell runs and emits the expanded form. So ONE match is enough.
                if sentinel in cmd_buf:
                    break
            time.sleep(0.05)
        out.extend(cmd_buf)
        out.extend(b"\n----\n")
    sh.close(); cli.close()
    return bytes(out).decode("utf-8", "replace")

if __name__ == "__main__":
    args = sys.argv[1:]
    if args == ["-"]:
        cmds = [l.rstrip() for l in sys.stdin if l.strip()]
    else:
        cmds = args
    sys.stdout.write(run(cmds))
