#!/usr/bin/env python3
"""Transfer arbitrary file from host to modem via UART using base64 + CRC chunks.

Workflow:
  - Read file, compute SHA256 + size
  - Base64 encode
  - Send in chunks (~1KB each) wrapped in: BEGIN <id> <crc> / data / END
  - On modem (busybox): we use a small shell-side decoder + cksum for CRC

Usage:
  python3 uart_transfer.py <local_file> <remote_path>

The modem must already be at a shell prompt (/bin/sh).
"""
import sys, os, time, base64, zlib, gzip, hashlib, threading
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from uart import open_port, send_slow, log_loop, LOG

CHUNK_SIZE = 128  # base64 line size — smaller chunks for big files
WAIT_PER_CHUNK = 0.20  # more buffer for big files (200KB+ gzipped)
GZIP_THRESHOLD = 30000  # gzip files larger than this (smaller transfer = less drop risk)

def main():
    if len(sys.argv) < 3:
        print("usage: uart_transfer.py <local_file> <remote_path>")
        return 1
    local, remote = sys.argv[1], sys.argv[2]
    raw_data = open(local, 'rb').read()
    sha = hashlib.sha256(raw_data).hexdigest()
    size = len(raw_data)
    use_gzip = size > GZIP_THRESHOLD
    if use_gzip:
        data = gzip.compress(raw_data, compresslevel=9)
        print(f"file: {local} ({size} bytes, gzipped to {len(data)} bytes = {100*len(data)//size}%)")
    else:
        data = raw_data
        print(f"file: {local} ({size} bytes)")
    b64 = base64.b64encode(data).decode()
    chunks = [b64[i:i+CHUNK_SIZE] for i in range(0, len(b64), CHUNK_SIZE)]
    print(f"file: {local} ({size} bytes) sha256={sha[:16]}...")
    print(f"chunks: {len(chunks)} x {CHUNK_SIZE}")

    ser = open_port()
    fout = open(LOG, "ab")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, False))
    t.start()
    time.sleep(0.5)

    # 1. clean any partial transfer
    send_slow(ser, f": > {remote}.b64")
    time.sleep(0.5)

    # 2. Use here-doc style: cat > file.b64 <<'EOF' ... EOF
    #    One single shell command, NO per-line parsing, much more reliable.
    print(f"sending {len(b64)} chars via heredoc...", end='', flush=True)
    log_size_at_start = os.path.getsize(LOG) if os.path.exists(LOG) else 0
    # Send the heredoc command + newline
    ser.write(f"cat > {remote}.b64 <<'EOFXFER'\r".encode())
    ser.flush()
    time.sleep(0.3)
    # Send all chunks (line-wrapped base64)
    for i, chunk in enumerate(chunks):
        ser.write(chunk.encode() + b"\r")
        ser.flush()
        time.sleep(WAIT_PER_CHUNK)
        if (i+1) % 50 == 0:
            print(f' {i+1}', end='', flush=True)
    # End heredoc
    time.sleep(0.5)
    ser.write(b"EOFXFER\r")
    ser.flush()
    print(' done')
    time.sleep(2)

    # 3. decode on target (optionally gunzip — try multiple decompressors)
    if use_gzip:
        # busybox provides gunzip as applet — try via busybox explicitly + fallbacks
        send_slow(ser, f"base64 -d {remote}.b64 | busybox gunzip > {remote} 2>/dev/null || "
                       f"base64 -d {remote}.b64 | gunzip > {remote} 2>/dev/null || "
                       f"base64 -d {remote}.b64 | zcat > {remote} 2>/dev/null || "
                       f"base64 -d {remote}.b64 | gzip -d > {remote}; "
                       f"rm {remote}.b64")
    else:
        send_slow(ser, f"base64 -d {remote}.b64 > {remote} && rm {remote}.b64")
    time.sleep(4)

    # 4. verify size + checksum — against RAW (uncompressed) since that's what's on disk
    send_slow(ser, f"echo TRANSFER_VERIFY: $(wc -c < {remote}) $(sha256sum {remote} | cut -c1-16)")
    time.sleep(3)

    # 5. cleanup and read log to verify
    stop.set()
    t.join()
    fout.close()

    log_tail = open(LOG, 'rb').read()[-4096:].decode(errors='replace')
    expected = f"TRANSFER_VERIFY: {size} {sha[:16]}"
    if expected in log_tail:
        print(f"✓ TRANSFER OK — file matched ({size} bytes, {sha[:16]})")
        return 0
    else:
        print(f"✗ Verification not found. Expected '{expected}'")
        print(f"Log tail:\n{log_tail[-1500:]}")
        return 1

if __name__ == "__main__":
    sys.exit(main())
