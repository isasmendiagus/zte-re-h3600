#!/usr/bin/env bash
# tcpdump_capture.sh — capture all packets on the host's link to the device
#
# Why this script: when debugging the eth-driver (TX path, RX path, ARP),
# we need to know what's actually on the wire between host and device.
# `cat /sys/class/net/sw/statistics/tx_packets` says "we sent N" but
# tcpdump tells us whether the device's PHY actually emitted those N
# frames. Often it didn't — see ETHERNET_DRIVER_DESIGN.md for the
# "TX-counter increments but wire stays silent" gotcha.
#
# Output: /tmp/capture.pcap (open in Wireshark or `tcpdump -r`)
#
# Flags chosen:
#   -i <iface>  the USB-Ethernet interface on host (configured at top below)
#   -nn         no DNS / port-name lookup (don't block on reverse DNS)
#   -e          show link-layer headers (we care about MAC addresses)
#   -v          verbose
#   -l          line-buffered (so stdout is live if you also want to watch)
#   -Z $USER    drop root privs to $USER after opening the socket
#   -w <path>   write raw pcap (lossless; you can also pass --immediate-mode)
#
# Requires sudo (only briefly — drops to $USER once the socket is open).
set -euo pipefail

# Host-side USB-Ethernet interface that talks to the device.
# If yours has a different MAC tail, check `ip -br link | grep en` and update.
IFACE="${ZXIC_NET_IFACE:-enxc8a362e95900}"
OUT="${1:-/tmp/capture.pcap}"

if ! ip link show "$IFACE" >/dev/null 2>&1; then
    echo "ERROR: interface $IFACE not found." >&2
    echo "  Set ZXIC_NET_IFACE=<your-iface> and retry." >&2
    echo "  Available USB-eth interfaces:" >&2
    ip -br link | awk '$1 ~ /^en/ {print "    " $1}' >&2
    exit 1
fi

echo "Capturing on $IFACE → $OUT"
echo "(Ctrl-C to stop. Open with: tcpdump -r $OUT  OR  wireshark $OUT)"

sudo tcpdump -i "$IFACE" -nn -e -v -l -Z "$USER" -w "$OUT"
