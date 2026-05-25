/*
 * dumpkring — read a file (typically /proc/kotrace_dump) and stream every
 * byte DIRECTLY to the ZTE-shifted PL011 UART via /dev/mem mmap.
 *
 * Why this exists: at /etc/init.norm time we can't SSH in to cat
 * /proc/kotrace_dump (cspd-userspace start gets broken by our bypass
 * fix), but we CAN write to UART via mmap. This binary bridges that gap.
 *
 * Build:  arm-linux-gnueabi-gcc -static -O2 -Wall -o out/dumpkring dumpkring.c
 * Use:    /sbin/dumpkring /proc/kotrace_dump
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

#define PL011_BASE 0x94404000u
#define PL011_SIZE 0x1000u
#define DR  0x04u
#define FR  0x14u
#define FR_TXFF (1u << 5)

static volatile unsigned char *uart;

static inline void uart_putc(int c) {
    int timeout = 100000;
    while ((*(volatile unsigned int *)(uart + FR) & FR_TXFF) && --timeout) { }
    *(volatile unsigned int *)(uart + DR) = (unsigned int)(c & 0xff);
}

static void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 2;
    }
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0) return 1;
    uart = mmap(NULL, PL011_SIZE, PROT_READ | PROT_WRITE,
                MAP_SHARED, memfd, PL011_BASE);
    if (uart == MAP_FAILED) return 2;

    uart_puts("\n=== dumpkring: ");
    uart_puts(argv[1]);
    uart_puts(" ===\n");

    /* Sanity check: try /proc/cmdline first to confirm /proc is mounted */
    {
        int sfd = open("/proc/cmdline", O_RDONLY);
        if (sfd < 0) {
            uart_puts("=== dumpkring: /proc/cmdline open failed errno=");
            int e = errno;
            char d[16]; int k = 0;
            if (e == 0) d[k++] = '0';
            while (e > 0) { d[k++] = '0' + (e % 10); e /= 10; }
            while (k--) uart_putc(d[k]);
            uart_puts(" (/proc not mounted?) ===\n");
        } else {
            uart_puts("=== dumpkring: /proc/cmdline OK (/proc mounted) ===\n");
            close(sfd);
        }
        /* And /proc/modules as a sanity that kernel/proc machinery works */
        int mfd = open("/proc/modules", O_RDONLY);
        if (mfd >= 0) {
            uart_puts("=== /proc/modules: ");
            char b[512]; ssize_t nn;
            while ((nn = read(mfd, b, sizeof(b))) > 0)
                for (ssize_t i = 0; i < nn; i++) {
                    if (b[i] == '\n') uart_putc('\r');
                    uart_putc((unsigned char)b[i]);
                }
            uart_puts(" === (end /proc/modules)\n");
            close(mfd);
        }
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        int e = errno;
        uart_puts("=== dumpkring: open failed errno=");
        {
            char d[16]; int k = 0;
            if (e == 0) d[k++] = '0';
            while (e > 0) { d[k++] = '0' + (e % 10); e /= 10; }
            while (k--) uart_putc(d[k]);
        }
        uart_puts(" ===\n");
        return 3;
    }

    char buf[1024];
    ssize_t n;
    long total = 0;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            if (buf[i] == '\n') uart_putc('\r');
            uart_putc((unsigned char)buf[i]);
        }
        total += n;
    }
    close(fd);

    uart_puts("\n=== dumpkring: done (");
    /* write decimal */
    {
        char d[16]; int k = 0;
        if (total == 0) d[k++] = '0';
        while (total > 0) { d[k++] = '0' + (total % 10); total /= 10; }
        while (k--) uart_putc(d[k]);
    }
    uart_puts(" bytes) ===\n");
    return 0;
}
