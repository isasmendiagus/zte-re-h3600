# ITERATE — the dev loops

There are **3 distinct iteration cycles** in this project. Pick the right
one for what you're doing.

---

## Loop A: mainline-driver dev (most common)

You edit `zx279128-eth.c`, rebuild, test on real hardware.

```
edit C source                          (~minutes)
   │
   ▼
rebuild kernel + initramfs            (~30 s incremental)
   │
   ▼
rewrap uImage + stage in tftp/         (~3 s)
   │
   ▼
flash mainline (RAM mode, no NAND)     (~3 min — TFTP transfer dominates)
   │
   ▼
boot → UART REPL → run test commands   (~30 s to first useful output)
   │
   ▼
read driver debugfs / printk → diagnose
   ▲                                              │
   └──────────────────────────────────────────────┘
```

**Commands:**
```sh
cd ~/Projects/MYSELF/ZTE/zxic

# 1. Edit your .c file (e.g. linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c)

# 2. Rebuild driver + kernel + uimg
cd linux-v6.6 && make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build zImage -j8 && cd ..
cd build/arch/arm/boot && cat zImage dts/zte/zx279128s-h3600.dtb > ../../../../tftp/zImage_dtb.bin && \
  mkimage -A arm -O linux -T kernel -C none -a 0x42000000 -e 0x42000040 \
          -d ../../../../tftp/zImage_dtb.bin ../../../../tftp/zImage_dtb.uimg
cd ../../../..

# 3. Refresh initramfs staging if you changed the .ko
cp linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.ko /tmp/initramfs_extract/lib/modules/
# Re-make zImage so the new .ko is embedded:
cd linux-v6.6 && make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=../build zImage -j8 && cd ..
# (re-wrap uImage — same mkimage line as step 2)

# 4. Boot the new kernel via TFTP + bootm (no NAND write — temporary)
nohup python3 -u lib/uart.py auto_bootm_dtb_appended > /tmp/boot.log 2>&1 &

# 5. After ~3 min, kill logger, drop into REPL (the C init forks busybox per command)
pkill -f 'uart\.py log'
python3 -c "
import sys; sys.path.insert(0, 'lib')
from uart import open_port
import time
s = open_port(); time.sleep(0.5); s.reset_input_buffer()
s.write(b'\\necho HI\\r'); s.flush(); time.sleep(2)
s.write(b'cat /sys/kernel/debug/zx_eth/stats\\r'); s.flush(); time.sleep(3)
print(s.read(s.in_waiting).decode('utf-8','replace'))
"
```

**Per-iter cost**: ~3 min total. Most of that is TFTP (`set tftpblocksize 1468` already gives ~150 KB/s; bigger size doesn't help our U-Boot).

**When to use NAND-persistent instead of RAM**: when you want the device
to boot autonomously without your laptop. See `tasks/00.03.nand-flash/README.md`
"Mode 2: NAND-persistent".

---

## Loop B: stock-driver RE (printk-injection)

You add a `printk` to a stock `.ko` (e.g. `switch.ko`) to observe what it
does at runtime, then study the UART output.

```
pick target function in Ghidra                (~minutes, one-time per target)
   │
   ▼
splice BL printk into .ko at chosen offset    (~30 s with the splicer tool)
   │
   ▼
push patched .ko to device                    (~10 s via scp over SSH)
   │
   ▼
rmmod old + insmod patched                    (~5 s on device)
   │
   ▼
trigger the code path you want to observe     (depends — e.g. ifconfig eth0 up)
   │
   ▼
read UART output (kmsg2uart bridge)
   ▲                                                  │
   └─ refine offset / fmt-string / target ────────────┘
```

**Commands** (once we have a splicer):
```sh
# 1. Identify target offset in Ghidra. Example: chip_tm_init at +0x12a4 in switch.ko

# 2. Splice (TODO: tool not built yet — see ROADMAP step 2)
# Planned: python3 tools/ko_printk_splice.py \
#     --input ext/rootfs/kmodule/switch.ko \
#     --output /tmp/switch.ko \
#     --offset 0x12a4 --fmt 'chip_tm_init r0=%lx r1=%lx' --args r0,r1

# 3. Push + reload on device (stock kernel must be running with kmsg2uart)
scp /tmp/switch.ko admin@192.168.1.1:/tmp/switch.ko
ssh admin@192.168.1.1 'rmmod switch && insmod /tmp/switch.ko'

# 4. Trigger
ssh admin@192.168.1.1 'ifconfig eth0 down; ifconfig eth0 up'

# 5. Read UART — printk lines appear via kmsg2uart
python3 -u lib/uart.py log | grep chip_tm_init
```

**Per-iter cost**: ~30 s (vs 3 min for mainline-driver iter). The big win
is no kernel rebuild + no full reboot.

**When to use**: any time you need to know "what does the stock driver
actually DO in this code path?" Use it BEFORE writing speculative mainline
code — let stock tell you the answer.

---

## Loop C: stock-shell rootfs iteration (slow, only when changing rootfs)

You're modifying the slot-A rootfs (e.g. adding a new daemon, changing
`/etc/rc`).

```
edit files in tasks/00.02.stock-shell/staging/
   │
   ▼
mkfs.jffs2 + AES encrypt + CRC + flash       (~5 min — heavy)
   │
   ▼
reboot device → slot A boots → SSH         (~60 s)
   │
   ▼
verify new files / behavior
```

**Commands:**
```sh
cd ~/Projects/MYSELF/ZTE/zxic/tasks/00.02.stock-shell
./prepare_slot_a.sh --write   # builds rootfs, encrypts, flashes, reboots
```

**Per-iter cost**: ~7 min (TFTP transfer of 22 MiB JFFS2 dominates).

**When to use**: changing what's BAKED INTO the rootfs (binaries,
config files, init scripts). For just testing a userspace binary,
prefer SSH + scp + run (no reflash needed).

---

## Common pitfalls (full list in `LEARNED.md`)

- **Padding bug**: pad source file to NAND-write size with `0xff` BEFORE TFTP.
- **CRC complement**: store `A` from `csp_crc:103 ... crc=A, B` log — `B` is just `~A`.
- **Hard-float SIGILL**: any new ARM binary must use `arm-linux-gnueabi-gcc` (no `-hf`).
- **PL011 DR shift**: writes to standard offset `+0x00` are silent; real DR at `+0x04`.
- **Don't reflash slot B**: it's our recovery fallback.

## Where to log findings as you iterate

| What you found | Where it goes |
|---|---|
| A new symptom→cause→fix pattern | `LEARNED.md` (top-level) |
| A hardware fact (register layout, magic offset) | `docs/ARCHITECTURE.md` |
| Mid-research notes for an open question | `tasks/<task>/research/<topic>.md` (create if needed) |
| "Step N of M done" within a current task | TaskUpdate the matching task ID |
| Final write-up of a completed RE chain | `tasks/<task>/findings/<topic>.md` then summarize in `LEARNED.md` |
