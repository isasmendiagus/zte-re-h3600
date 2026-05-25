/*
 * kmsg2uart — drain the kernel printk ring buffer and emit to the
 * ZTE-shifted PL011 UART.
 *
 * Why this exists: the stock H3600 kernel's pl011 console driver writes
 * to standard PL011 DR offset (+0x00), but on ZX279128S the real DR is
 * at +0x04. So printk-from-kernel never reaches the UART hardware via
 * the kernel's own console driver.
 *
 * This daemon does it manually from userspace by mmap'ing /dev/mem at
 * the PL011 base, polling FR (TXFF) and pushing one byte at a time
 * to DR.
 *
 * Source of kernel printk: switched 2026-05-25 from open(/proc/kmsg) to
 * klogctl() syscall. /proc/kmsg has single-reader semantics — if cspd or
 * klogd opens it first, our open() returns EBUSY and the daemon dies
 * leaving every subsequent kernel printk (including bake-in panic
 * stacks) invisible. klogctl() reads the kernel ring buffer directly
 * with no single-reader restriction; any number of processes can call
 * it concurrently.
 *
 * Limitations:
 *   - Misses any printk emitted before this daemon starts (early boot
 *     pre-userspace — kernel hasn't even initialized printk subsystem
 *     yet). We DO catch anything still in the ring buffer at start via
 *     a one-shot klogctl(3, ...) drain.
 *   - Slow (one byte per FR poll).
 *   - Requires root / CAP_SYS_ADMIN (for /dev/mem + klogctl).
 *
 * Build (static, cross):
 *   arm-linux-gnueabi-gcc -static -O2 -Wall -o out/kmsg2uart kmsg2uart.c
 *
 * Run on device:
 *   /sbin/kmsg2uart --test     # writes a banner to UART and exits
 *   nohup /sbin/kmsg2uart >/dev/null 2>&1 &     # daemon mode
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/klog.h>     /* klogctl() — direct kernel-printk ring buffer access */

#define PL011_BASE   0x94404000u   /* /soc/serial@0x94404000 per /proc/iomem */
#define PL011_SIZE   0x1000u
#define DR_OFFSET    0x04u         /* ZTE-shifted; standard PL011 is 0x00 */
#define FR_OFFSET    0x14u         /* ZTE-shifted; standard PL011 is 0x18 */

/* Standard PL011 FR bits (layout appears unchanged on ZX279128S) */
#define FR_TXFF      (1u << 5)     /* TX FIFO full */
#define FR_BUSY      (1u << 3)     /* UART busy transmitting */

static volatile unsigned char *uart_base;

static inline unsigned int read32(unsigned offset) {
    return *(volatile unsigned int *)(uart_base + offset);
}

static inline void write32(unsigned offset, unsigned int val) {
    *(volatile unsigned int *)(uart_base + offset) = val;
}

static void uart_putc(int c) {
    /* Wait for room in TX FIFO */
    while (read32(FR_OFFSET) & FR_TXFF) {
        /* spin */
    }
    write32(DR_OFFSET, (unsigned int)(c & 0xff));
}

static void uart_puts(const char *s, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s[i] == '\n') uart_putc('\r');
        uart_putc((unsigned char)s[i]);
    }
}

int main(int argc, char **argv) {
    int mem_fd, kmsg_fd;
    char buf[8192];
    ssize_t n;
    int test_mode = (argc > 1 && strcmp(argv[1], "--test") == 0);

    /* mmap PL011 */
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        fprintf(stderr, "kmsg2uart: open /dev/mem: %s\n", strerror(errno));
        return 1;
    }
    uart_base = mmap(NULL, PL011_SIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED, mem_fd, PL011_BASE);
    if (uart_base == MAP_FAILED) {
        fprintf(stderr, "kmsg2uart: mmap PL011 0x%x: %s\n", PL011_BASE, strerror(errno));
        return 1;
    }

    /* Always emit a banner — if this shows on UART, write path works. */
    const char *banner = "\r\n[kmsg2uart] alive — DR=0x94404004 (ZTE-shifted PL011)\r\n";
    uart_puts(banner, strlen(banner));

    if (test_mode) {
        const char *msg = "[kmsg2uart] --test: wrote banner, exiting.\r\n";
        uart_puts(msg, strlen(msg));
        return 0;
    }

    /* Switched 2026-05-25: use syslog(2) syscall via klogctl() instead of
     * /proc/kmsg. Reason: /proc/kmsg has single-reader semantics — if cspd
     * or klogd opens it first, our open() returns EBUSY and the daemon
     * dies, leaving every subsequent kernel printk invisible (including
     * any panic). klogctl() reads the kernel ring buffer directly with no
     * single-reader restriction, and any number of processes can call it.
     *
     * klogctl actions used:
     *   2 = SYSLOG_ACTION_READ          — blocking; returns when bytes available
     *   3 = SYSLOG_ACTION_READ_ALL      — non-blocking; up to len bytes of stale
     *
     * We pre-flush ACTION_READ_ALL once so we see whatever's in the buffer
     * at daemon-start (early-boot printk), then loop on ACTION_READ for new
     * stuff. (void)kmsg_fd suppresses unused-var; we keep the symbol so
     * accidental references compile-fail.
     */
    (void)kmsg_fd;
    {
        const char *banner2 =
            "[kmsg2uart] using klogctl() syscall (not /proc/kmsg)\r\n";
        uart_puts(banner2, strlen(banner2));
    }

    /* One-shot drain of whatever printk already buffered (action 3). */
    n = klogctl(3 /*READ_ALL*/, buf, sizeof(buf));
    if (n > 0) {
        uart_puts(buf, (size_t)n);
    } else if (n < 0) {
        const char *err = "[kmsg2uart] klogctl(3) failed; permission? root?\r\n";
        uart_puts(err, strlen(err));
        fprintf(stderr, "kmsg2uart: klogctl(3): %s\n", strerror(errno));
        /* Don't exit — fall through and try ACTION_READ. */
    }

    /* Main loop: blocking SYSLOG_ACTION_READ for new printk lines. */
    for (;;) {
        n = klogctl(2 /*READ*/, buf, sizeof(buf));
        if (n < 0) {
            if (errno == EINTR) continue;
            const char *err =
                "[kmsg2uart] klogctl(2) read failed; exiting.\r\n";
            uart_puts(err, strlen(err));
            fprintf(stderr, "kmsg2uart: klogctl(2): %s\n", strerror(errno));
            return 1;
        }
        if (n == 0) continue;
        uart_puts(buf, (size_t)n);
    }
}
