/*
 * kmsg2uart — drain /dev/kmsg and emit to the ZTE-shifted PL011 UART.
 *
 * Why this exists: the stock H3600 kernel's pl011 console driver writes
 * to standard PL011 DR offset (+0x00), but on ZX279128S the real DR is
 * at +0x04. So printk-from-kernel never reaches the UART hardware.
 *
 * This daemon does it manually from userspace by mmap'ing /dev/mem at
 * the PL011 base, polling FR (TXFF) and pushing one byte at a time
 * to DR. Reads /proc/kmsg as the kernel emits messages.
 *
 * Limitations:
 *   - Misses any printk emitted before this daemon starts (early boot).
 *   - Slow (one byte per FR poll).
 *   - Requires root (for /dev/mem + /proc/kmsg).
 *   - /proc/kmsg may be drained by ZTE's logger kernel module (which
 *     pulls kernel data into /dev/logger_main). If so, this daemon
 *     won't see anything. Run with --test first to verify the UART
 *     write path is OK before debugging kmsg.
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

    /* /proc/kmsg: one printk per read (the legacy syslog(2) interface).
     * /dev/kmsg (modern devkmsg) is not available on this kernel build. */
    kmsg_fd = open("/proc/kmsg", O_RDONLY);
    if (kmsg_fd < 0) {
        fprintf(stderr, "kmsg2uart: open /proc/kmsg: %s\n", strerror(errno));
        const char *err = "[kmsg2uart] FAILED to open /proc/kmsg\r\n";
        uart_puts(err, strlen(err));
        return 1;
    }

    /* Main loop: blocking read on /proc/kmsg, push to UART.
     * /proc/kmsg format: "<N>message\n" where N is loglevel digit. */
    for (;;) {
        n = read(kmsg_fd, buf, sizeof(buf));
        if (n < 0) {
            if (errno == EINTR) continue;
            fprintf(stderr, "kmsg2uart: read /proc/kmsg: %s\n", strerror(errno));
            return 1;
        }
        if (n == 0) continue;
        uart_puts(buf, (size_t)n);
    }
}
