# Kotrace iterative workflow (stock kernel)

Working as of 2026-05-25 (commits 13881faa2 + c6538cac6 + e4081d8cd).
Replaces the older "reflash to test kotrace" loop with a fast
insmod/rmmod cycle now that the .ko reverses all patches at exit.

## Prereq

- Stock kernel booted on slot A (`ext/extracted/uImage` +
  `tftp/rootfs_a_patched_enc.jffs2`).
- Device reachable: `ping 192.168.1.1` returns 0% loss.
- UART bridge running (`/tmp/uart_bridge.log` updating).

If any of those is wrong, DTR-reset and re-verify:

```bash
python3 -c "
import socket, time
s = socket.create_connection(('127.0.0.1', 9998), timeout=5)
s.sendall(b'DTR_HIGH\n'); time.sleep(2.0); s.sendall(b'DTR_LOW\n')
s.close()"
# wait ~90s, then:
ping -c 3 192.168.1.1
```

If the device is broken-broken (not booting), use the canonical-rootfs
flash:

```bash
python3 tasks/00.04.flash-tool/flash.py both \
    --kernel ext/extracted/uImage \
    --rootfs tftp/rootfs_a_patched_enc.jffs2
```

## Edit-build-test cycle (~30 sec)

```bash
# 1. edit kotrace.c (or kt_modules table via regenerate)
make -C tasks/00.01.eth-driver/kotrace
cp tasks/00.01.eth-driver/kotrace/kotrace.ko tftp/

# 2. push + load on device
python3 lib/ssh_shell.py "cd /tmp && busybox tftp -g -r kotrace.ko 192.168.1.50 \
    && rmmod kotrace 2>/dev/null; insmod /tmp/kotrace.ko"

# 3. (optional) confirm what got patched
grep -aE "v2 '|patched OK|skip:" /tmp/uart_bridge.log | tail -50
```

If you change the trace_target table (added new fn etc), regenerate
the header first:

```bash
python3 tasks/00.10.02.re-stock-kmods/scripts/generate_kotrace_targets.py
```

## Capture-around-event pattern

```bash
# clear ring
python3 lib/ssh_shell.py "echo > /proc/kotrace_dump"

# do the thing you want to capture
ping -c 5 192.168.1.1

# dump
python3 lib/ssh_shell.py "cat /proc/kotrace_dump" > /tmp/capture.txt

# resolve func_addr → symbol
python3 tasks/00.01.eth-driver/scripts/analyze_kotrace.py /tmp/capture.txt
```

## Filter for TX path

```bash
python3 tasks/00.01.eth-driver/scripts/analyze_kotrace.py /tmp/capture.txt \
    | grep -E "pon_tm_net_tx|pdt_ethdrv_send|soft_insert|bmu_alloc|raw_send|get_next_txdesc"
```

## Filter for RX path

```bash
python3 tasks/00.01.eth-driver/scripts/analyze_kotrace.py /tmp/capture.txt \
    | grep -E "pdt_ethdrv_recv|ethdrv_recv_fin|soft_release_rx_desc|pp_bmu_free_bp"
```

## Known stock TX baseline (5-ping, 0% loss)

Each ICMP echo reply emits exactly:

```
pdt_ethdrv_send(skb, dev, _, &pdt_ethdrv_send)
pon_tm_net_tx(skb, dev, _, &pon_tm_net_tx)
pon_tm_get_next_txdesc(1, 0, &out_desc_idx, &out_desc_idx)
pon_tm_data_raw_send(skb, &bp_buf, 1, &bp_buf)
pon_tm_bmu_alloc_bp(?, &bp_buf, 1, &bp_buf)
soft_insert_tx_1desc(&bp_buf, 1, _, tx_seq)
```

Then independently, from a ~10ms periodic timer:

```
pon_tm_timer_func(0, &pon_tm_timer_data, 0, …)
pon_tm_check_tx_done_nolock(direction, 0, _, _)
```

Use this as the reference when checking whether mainline driver
omits a step.

## Why this works post-boot (not at boot)

The first thunk-OOB hang we saw — when v2 (~2k patches) was baked
into the rootfs — was caused by the thunk computing
`ring_buf + idx*32` with unmasked idx. Past 16384 events that wrote
past `ring_buf`, corrupting whatever sat after our kzalloc. The
post-boot insmod hits the same code but the ring fills up much
slower (no init-storm), so the bug took longer to trigger and we
didn't notice. Fixed in commit 13881faa2 — the thunk now masks
idx via `lsl #18; lsr #13` before indexing.

If you want to verify the OOB fix at scale: insmod, then heavy-load
the device for >5 minutes. The pre-fix .ko would crash within 30s
on a busy network; the fixed one survives indefinitely.
