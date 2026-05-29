# Live register poke/peek tool (reflash-free debugging)

Added 2026-05-28. Lets us read AND write SoC registers on the running mainline
device over the UART bridge socket — **no rebuild/reboot per experiment**. This
turned 5-minute build→reboot cycles into second-long live experiments.

## What's available on the device

Driver debugfs (mount once per boot: `mount -t debugfs none /sys/kernel/debug`):

| path | dir | what |
|---|---|---|
| `/sys/kernel/debug/zx_eth/stats` | r | driver counters (tm_rx_count, tm_rx_loopback_drops, tm_tx_count, TM[0x10058]/0x10054, rx_head…) + a pile of TM/PP/MAC/PHY regs |
| `/sys/kernel/debug/zx_eth/regdump` | r | hex-TEXT `<phys> <value>` for the forwarding windows (TM/MAC/PP_BRG). Robust over the glitchy UART (vs the binary `mem`). |
| `/sys/kernel/debug/zx_eth/mem` | r | binary 2 MiB dump of `e->base+0..0x200000` (raw; UART-fragile) |
| `/sys/kernel/debug/zx_eth/poke` | w | **write `"<phys> <val>"` (hex) → `writel`**. phys in `[0x921c0000, 0x923c0000)`, 4-aligned. |
| `memdump <hexphys> <hexlen>` | bin | custom busybox-dir binary: hex dump by PHYSICAL addr (e.g. `memdump 92280000 c`). No `/dev/mem` needed. |

Address mapping: **phys = 0x921c0000 + e->base offset.** PP regs are at
`e->base + PP_OFF(0x1c0000)`, so e.g. PP[0x8340] = phys 0x92388340; MAC[i] =
phys `0x921c0000 + (i+1)*0x40000` (MAC2/host port = 0x92280000); TM at low
offsets (TM[0x10054] = phys 0x921d0054).

## How to drive it (host side)

REPL over TCP socket `localhost:9999` (uart bridge). It execs ONE busybox
applet per line — **no `;`/`|`/redirect directly**, BUT `sh -c "..."` works
(busybox `sh` is present) and gives you redirects: that's how poke is written.

```python
import socket, time
s = socket.create_connection(("localhost", 9999), timeout=10); s.settimeout(2.0)
def run(cmd, w=1.2):
    s.sendall(cmd.encode()+b"\r"); time.sleep(w)
    o=b""
    try:
        while True:
            d=s.recv(8192)
            if not d: break
            o+=d
    except socket.timeout: pass
    return o.decode("utf-8","replace")
run("mount -t debugfs none /sys/kernel/debug")
print(run("memdump 92280000 c"))                       # peek MAC2 ctrl/mask/en
run('''sh -c "echo '92280008 80000001' > /sys/kernel/debug/zx_eth/poke"''')  # poke
print(run("cat /sys/kernel/debug/zx_eth/stats"))
```

Typical loop: poke regs → (host) `ping -c6 192.168.1.99` + `tcpdump -i enxc8a362e95900 -e -nn 'ether host f4:f6:47:0f:42:64 or arp'` → read stats.
tcpdump runs WITHOUT sudo (`/usr/bin/tcpdump` has `cap_net_admin,cap_net_raw=eip`).

## Gotchas learned the hard way
- **QMG block (e->base+0xc000) is DYNAMIC** — the HW rewrites it; pokes don't
  stick. Don't try to patch QMG by poke.
- **Storm guard**: enabling MAC[2] (`+0x08 ENABLE`) with an incomplete bring-up
  causes a packet STORM (frames loop hundreds of times). ALWAYS poke
  `<macbase>+0x08 = 0` to disable after a test.
- Binary `mem` reads over UART drift/zero-fill on long streams; prefer the
  hex-TEXT `regdump`/`memdump`, and for two captures keep only bytes that agree.
- Source: `regdump`/`poke` are in `zx-eth-main.c` (`zx_regdump_*`, `zx_poke_*`,
  registered in `zx_debugfs_init`). DEBUG ONLY — strip before upstreaming.
