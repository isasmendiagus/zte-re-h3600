#!/usr/bin/env python3
"""Send shell commands to the H3600 via paramiko invoke_shell (router blocks `ssh user host cmd`).

Usage:
    ./ssh_shell.py "uname -a" "lspci -vv" ...    # one shot
    cat cmds.txt | ./ssh_shell.py -              # from stdin

Returns combined output of all commands (no banner suppression).
"""
import sys, time, paramiko

HOST, USER, PASS = "192.168.1.1", "admin", "UkuGPeyRDU"
SENTINEL = "@@DONE_$$_MARKER@@"

def run(cmds, timeout=15):
    cli = paramiko.SSHClient()
    cli.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    cli.connect(HOST, username=USER, password=PASS,
                allow_agent=False, look_for_keys=False, timeout=10)
    sh = cli.invoke_shell(width=200, height=50)
    out = bytearray()
    def drain():
        time.sleep(0.4)
        while sh.recv_ready():
            out.extend(sh.recv(65536))
            time.sleep(0.05)
    drain()  # eat banner / motd
    out.clear()
    for c in cmds:
        sh.send(c + f"; echo {SENTINEL}\n")
        deadline = time.time() + timeout
        while time.time() < deadline:
            if sh.recv_ready():
                out.extend(sh.recv(65536))
                if SENTINEL.encode() in out:
                    break
            time.sleep(0.05)
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
