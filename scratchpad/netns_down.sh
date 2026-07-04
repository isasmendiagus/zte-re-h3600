#!/bin/bash
# return enxc8a362e95900 to root ns @192.168.1.50 + restore TFTP route
# sudo password: $ZTE_SUDO_PW or the git-ignored scratchpad/.sudo_pw (see rig.py)
PW="${ZTE_SUDO_PW:-$(cat "$(dirname "$0")/.sudo_pw" 2>/dev/null)}"
S="echo $PW | sudo -S"
eval "$S ip netns exec client ip link set enxc8a362e95900 netns 1" 2>/dev/null
eval "$S ip netns del client" 2>/dev/null
sleep 1
eval "$S ip addr add 192.168.1.50/24 dev enxc8a362e95900" 2>/dev/null
eval "$S ip link set enxc8a362e95900 up"
sleep 1
eval "$S ip route replace 192.168.1.0/24 dev enxc8a362e95900 src 192.168.1.50"
echo "root-ns:"; ip -o addr show enxc8a362e95900 | sed 's/inet6.*//'
ip route get 192.168.1.1 2>&1 | head -1
