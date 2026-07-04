#!/bin/bash
# move enxc8a362e95900 into netns 'client' on device lan2, 172.31.9.50/24
# sudo password: $ZTE_SUDO_PW or the git-ignored scratchpad/.sudo_pw (see rig.py)
PW="${ZTE_SUDO_PW:-$(cat "$(dirname "$0")/.sudo_pw" 2>/dev/null)}"
S="echo $PW | sudo -S"
eval "$S ip netns add client" 2>/dev/null
eval "$S ip link set enxc8a362e95900 netns client" 2>/dev/null
eval "$S ip netns exec client ip link set lo up"
eval "$S ip netns exec client ip addr add 172.31.9.50/24 dev enxc8a362e95900"
eval "$S ip netns exec client ip link set enxc8a362e95900 up"
sleep 2
eval "$S ip netns exec client ip route add default via 172.31.9.1 dev enxc8a362e95900" 2>/dev/null
echo "client route:"; eval "$S ip netns exec client ip route show table all" 2>/dev/null | grep -E "default|172.31" 
