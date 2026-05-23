#!/usr/bin/env bash
# tftpd_start.sh — start the in.tftpd daemon serving zxic/tftp/ on the host
#
# Why this script: every flash recipe, every kernel-iter loop, every
# `tftp -g` from the device pulls from the host's TFTP server. If it's
# not running, OR it's running with the wrong serve-dir, EVERYTHING
# silently fails (U-Boot logs "no response" or transfers garbage).
#
# Wrong serve-dir is a common gotcha — the daemon was historically
# started against the old H3600/ path; after the rename to zxic/ it
# kept running with cached args. Always restart after any rename.
#
# Requires sudo. Doesn't background detach — runs in the foreground so
# you can see request lines (`-L` for verbose). Ctrl-C to stop.
set -euo pipefail

TFTP_DIR=/home/ubuntu/Projects/MYSELF/ZTE/zxic/tftp
HOST_IP=192.168.1.50

# Kill any prior instance (regardless of which path it was serving)
sudo pkill -f 'in\.tftpd' 2>/dev/null || true

if [[ ! -d "$TFTP_DIR" ]]; then
    echo "ERROR: TFTP dir does not exist: $TFTP_DIR" >&2
    exit 1
fi

echo "Starting in.tftpd on $HOST_IP:69, serving $TFTP_DIR"
echo "(Ctrl-C to stop. Each request will print here.)"

# Flags:
#   -L       foreground, log to stderr (so we see requests live)
#   --secure chroot to serve dir
#   --create allow client uploads (creates new files; needed by some debug flows)
#   -a       bind to this host IP:port (avoid binding 0.0.0.0)
sudo in.tftpd -L --secure --create -a "$HOST_IP:69" "$TFTP_DIR"
