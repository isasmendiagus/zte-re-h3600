# Slot A boot iterations — diagnosis log

**Goal**: get slot A booting our modified rootfs such that SSH works.

## Hypotheses to test (in priority)

1. **Trim is the issue** — we removed something cspd needs. Test: use STOCK cspd + same trim. If it hangs, trim is the problem.
2. **Patch is the issue** — our 3-byte cspd patch breaks cspd. Test: same as above.
3. **Sink binaries** — replace removed daemons with sleep-loop scripts so cspd's spawn attempts return success.
4. **Minimal trim** — only drop /etc/dsl + /etc/usb_modeswitch (the BIG bulks), keep all binaries.

## Iterations

### Iter 0 (baseline) — DONE
- Built with patched cspd + aggressive trim (incl /home/httpd removal)
- Result: slot A boots cspstart-OK, but USERSPACE HANGS

### Iter 1 — DONE (FAILED) — stock cspd + safer trim
- Build: stock cspd (unmodified) in staging
- Trim: /etc/dsl, /etc/usb_modeswitch.d, /bin/smbd, /bin/smbpasswd, /bin/voip, /bin/mqtt, modules.*.bin, /etc/autokernelconf
- Result: slot A accepted (`select=0`, `verify fs success`), kernel started, **userspace hung**
- **Conclusion**: trim is the issue (patch is innocent). Something we removed is needed.

### Iter 2 (next) — stock cspd + MINIMAL trim (only /etc/dsl)
- Trim ONLY: /etc/dsl (4.5 MiB, DSL configs — H3600 is GPON, shouldn't be needed)
- Keep all binaries (smbd/voip/mqtt all present)
- Total saved: 4.5 MiB → ~40.5 MiB raw → ~20 MiB compressed → fits 22 MiB
- If BOOTS: we trim binaries we removed before, one at a time
- If HANGS: /etc/dsl removal is also problematic OR rebuilt-jffs2 format is the issue

### Iter 3+ — TBD based on iter 2

## Open hypotheses

- **Trim removal of /bin/voip /bin/smbd /bin/mqtt** → cspd might spawn these and hang waiting (try sink binaries next)
- **/etc/dsl removal** → maybe some startup script reads it (unlikely but possible)
- **mkfs.jffs2 version mismatch** → Ubuntu 24.04 mkfs.jffs2 produces nodes incompatible with stock ZTE-patched JFFS2 driver (would explain "every modification breaks" pattern)
- **/etc/usb_modeswitch.d removal** → init script may read these tables

---

## Iter 2 (DONE — FAILED) — stock cspd + ONLY /etc/dsl trim
- Same outcome as iter 1. Slot A accepted, kernel hangs.

## Iter 3 (DONE — BUILD FAILED) — /etc/dsl kept + safer trim
- Trim: `/home/httpd/public/img`, `/etc/usb_modeswitch.d`, `modules.*.bin`, `/etc/autokernelconf`
- jffs2 too big (>22 MiB) — needed more trim

## Iter 4 (DONE — FAILED) — added /bin/voip + /bin/mqtt to trim
- jffs2 OK 22 MiB, flash OK, slot A accepted, kernel hangs

## Iter 5 (DONE — FAILED) — added `--squash` to mkfs.jffs2
- Files now owned root:root (uid 0). Still hangs.

## ISOLATION test (DONE — SUCCESS!)
- Method: flash ORIGINAL slot A bytes from h3600_nand_full.bin + matching CRC header (no mkfs.jffs2 involved)
- Result: **slot A boots cleanly, SSH works**
- **Conclusion**: our flash mechanism is correct. The bug is in our `mkfs.jffs2` output.

## ROOT CAUSE FOUND

**Our extracted `rootfs/dev/` has only empty `input/` and `misc/` subdirs — NO device nodes.**

`/dev/console`, `/dev/null`, `/dev/tty*`, etc. don't exist in our staging because the JFFS2 extractor that produced `rootfs/` couldn't create char/block special files without root.

When mkfs.jffs2 builds from this `rootfs/`, no device nodes go into the output. On the device, `init` can't open `/dev/console` → silent boot hang.

**The running device confirms** `/dev/console` and `/dev/null` EXIST in the live filesystem. They're inside the original stock jffs2 image (which we flashed back via isolation test).

## Iter 6 plan (next)

Use `mkfs.jffs2 --devtable=DEVTABLE` with a manually crafted devtable listing the standard device nodes:

```
/dev/console c 600 0 0 5 1 - - -
/dev/null    c 666 0 0 1 3 - - -
/dev/tty     c 666 0 0 5 0 - - -
/dev/zero    c 666 0 0 1 5 - - -
/dev/ttyAMA0 c 600 0 0 204 64 - - -
/dev/mem     c 600 0 0 1 1 - - -
/dev/random  c 444 0 0 1 8 - - -
/dev/urandom c 444 0 0 1 9 - - -
/dev/kmem    c 600 0 0 1 2 - - -
/dev/ptmx    c 666 0 0 5 2 - - -
... (more for full coverage)
```

OR — dump `/dev/` contents from the running device via SSH and replicate exactly.

## SSH note

Stock firmware blocks LAN SSH via firewall rules in `/usercfg/config.bin`.
Need to verify SSH config is correctly set in /usercfg (separate mtdblock4 partition, untouched by our slot A writes).
If SSH still blocked, separate workstream: re-upload modified config.bin via web admin.

---

## Iter 6 (DONE — SLOT A BOOTS, SSH WORKS) — 2026-05-22

`prepare_slot_a.sh --write` with:
- `mkfs.jffs2 --squash --devtable=devtable.txt` (329 entries dumped from live device)
- Patched cspd: 3 bytes at 0x1cdeda/0x1cdf21/0x1ce161 → `0x33` ("g 3")
- `/etc/dsl` kept (switch FW for nfbi bootdownload)

Verified on running device:
- `/dev/root on / type jffs2 (ro,relatime)` — slot A mounted as /
- `/bin/cspd` byte at 0x1cdeda = `0x33` (patched, not stock 0x30)
- `/bin/cspd` timestamp `May 22 2026` (matches mkfs.jffs2 run)
- `/etc/dsl/{boot.bin,fw.bin}` present
- SSH on 192.168.1.1:22 OPEN, login `admin/UkuGPeyRDU` works
- 329 /dev nodes present via devtable

## Iter 7 — UART STILL SILENCED (cspd patch not enough)

**Critical finding**: even with our patched cspd running (`logctrl -m -p /dev/console -g 3`),
**UART is silent** because there's a SECOND silencing mechanism:

```
/ # cat /proc/sys/kernel/printk
0       4       1       7
```

`console_loglevel = 0` → only KERN_EMERG passes to console. Set elsewhere (not by cspd).

Manual fix via SSH works:
```
echo 7 > /proc/sys/kernel/printk
```
Then kernel printk goes to UART (subject to logctrl forwarding).

`/etc/rc` content: just `/bin/logctrl` (and more lines we may have truncated). Look elsewhere for `printk` write.

## logctrl `-g` flag semantics (from /bin/logctrl help)

| -g | Behavior |
|----|----------|
| 0 | receive Nothing |
| 1 | receive LOGGER + printk + log_printf |
| 2 | receive printf |
| 3 | receive ALL (LOGGER + printf + printk + log_printf) |

So our 3-byte patch (0→3, 1→3, 2→3) maximally opens UART forwarding. That part works.
The remaining gate is `/proc/sys/kernel/printk`.

## csp_crc is NOT zlib.crc32 (CONFIRMED 2026-05-22)

`csp_crc:103  >>csp_crc,  data addr:42000000, crc_len:0xa4`
`crc=0x25ef12be, 0xda10ed41`

Same data; computed (0x25ef12be) ≠ stored zlib-CRC (0xda10ed41). The orca.pet writeup is wrong about
this. Strict header CRC match is therefore impossible with zlib.crc32 — but it doesn't matter because
the **lenient** path (`use defualt jffs2 fs!!`) accepts based on JFFS2 magic detection in the decoded
mtdblock view. **Always rely on the lenient path; do not waste effort matching strict CRCs.**

## Slot selection rule observed

When both slots pass lenient check:
- `cspd flags=0xa3` in slot A header → slot A wins (`select=0`)
- `flags=0x00` in slot B header → fallback
- An empty/erased slot A → automatic `select=1` (slot B)

## REPRODUCIBLE BUILD PIPELINE

From a fresh tree to working slot-A flash:

1. **Stage rootfs** in `H3600/stock_traced/rootfs/` (extracted from h3600_nand_full.bin via `extract_jffs2.py` etc.)
2. **Generate devtable** (one-time, from any live device):
   ```python
   # SSH to device, `ls -la /dev/`, parse, emit lines like:
   # /dev/console  c  600  0  0  5  1  -  -  -
   ```
3. **Drop patched cspd** at `H3600/stock_traced/out/cspd-uart-alive` (3 bytes: 0x1cdeda, 0x1cdf21, 0x1ce161 → 0x33)
4. **Trim** to fit 22 MiB jffs2: drop `/home/httpd/public/img`, `/etc/usb_modeswitch.d`, `/bin/voip`, `/bin/mqtt`, `/lib/modules/4.1.25/modules.*.bin`, `/etc/autokernelconf`. KEEP `/etc/dsl`.
5. **Build**: `prepare_slot_a.sh --write`
   - mkfs.jffs2 `--pagesize=2048 --eraseblock=131072 --no-cleanmarkers --pad=0x1620000 --little-endian -m size --squash --devtable=$ROOT/devtable.txt`
   - AES-128-ECB encrypt with key `H36000e71071c440`
   - zlib.crc32 the encrypted bytes → write to header[0x48:0x4c] (LE, 4 bytes)
   - zlib.crc32(header[0:0xa4]) → write to header[0xa4:0xa8] (LE) — purely cosmetic, see csp_crc note
   - tftp + nand erase + nand write rootfs at 0xa60000
   - tftp + nand erase + nand write header at 0x2080000
6. **First boot** picks slot A via lenient path → SSH at 192.168.1.1:22 within ~60s.

## Open follow-ups

1. **UART** still silent — find what writes `printk=0`. Once found, patch it too OR add `echo 7 > /proc/sys/kernel/printk` early in `/etc/rc`.
2. **CRC drift across reboots** — the encrypted bytes on NAND apparently differ across boots (we saw cspstart compute 0xd4c2b8c5 then 0xf9467fa4 over the "same" flashed image). Likely JFFS2 wear/cleanmarker writes. Not blocking thanks to lenient path, but explains why ISOLATION test's exact-CRC-match was a one-shot.
3. **Document `select=` flag bits** — header[?] determines slot priority; need to find which offset.
