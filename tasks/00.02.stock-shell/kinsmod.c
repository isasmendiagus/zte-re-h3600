/*
 * kinsmod — insmod wrapper that writes status DIRECTLY to ZTE-shifted PL011 UART.
 *
 * Problem this solves: at /etc/init.norm time, cspstart sometimes fails to
 * expand $(console) in bootargs, so the kernel boots with NO registered console.
 * Then /dev/console writes go to /dev/null and we can't see WHY busybox-insmod
 * fails (errno is silently lost). kmsg2uart with klogctl works for kernel
 * printk, but it can't capture insmod's STDERR (which is the failure reason).
 *
 * This wrapper:
 *   1. mmap's /dev/mem at PL011 base (0x94404000) using the ZTE-shifted layout
 *      (DR at +0x04, FR at +0x14). Same as kmsg2uart.
 *   2. Calls init_module(2) syscall directly with the .ko bytes.
 *   3. Writes the exact errno to the PL011 UART using busy-poll FR-TXFF.
 *
 * Build:
 *   arm-linux-gnueabi-gcc -static -O2 -Wall -o out/kinsmod kinsmod.c
 *
 * Use:
 *   /sbin/kinsmod /kmodule/kotrace.ko
 *
 * Output examples on UART:
 *   [kinsmod] try /kmodule/kotrace.ko (123456 bytes)
 *   [kinsmod] init_module() returned 0 (OK)
 *   OR
 *   [kinsmod] init_module() returned -1 errno=8 (ENOEXEC: invalid module format)
 *   [kinsmod] init_module() returned -1 errno=22 (EINVAL)
 *   [kinsmod] init_module() returned -1 errno=12 (ENOMEM)
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#define PL011_BASE   0x94404000u
#define PL011_SIZE   0x1000u
#define DR_OFFSET    0x04u    /* ZTE-shifted */
#define FR_OFFSET    0x14u    /* ZTE-shifted */
#define FR_TXFF      (1u << 5)

static volatile unsigned char *uart_base;

static void uart_putc(int c) {
    while (*(volatile unsigned int *)(uart_base + FR_OFFSET) & FR_TXFF) { }
    *(volatile unsigned int *)(uart_base + DR_OFFSET) = (unsigned int)(c & 0xff);
}
static void uart_puts(const char *s) {
    for (; *s; s++) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s);
    }
}
static void uart_putd(long v) {
    char buf[16]; int n = 0;
    if (v < 0) { uart_putc('-'); v = -v; }
    if (v == 0) { uart_putc('0'); return; }
    while (v > 0) { buf[n++] = '0' + (v % 10); v /= 10; }
    while (n--) uart_putc(buf[n]);
}

/* errno → human name. Small table for the ones we expect. */
static const char *errno_name(int e) {
    switch (e) {
    case 0:        return "OK";
    case EPERM:    return "EPERM (operation not permitted)";
    case ENOENT:   return "ENOENT (no such file)";
    case EIO:      return "EIO";
    case ENOMEM:   return "ENOMEM (out of memory)";
    case EACCES:   return "EACCES";
    case EFAULT:   return "EFAULT";
    case EBUSY:    return "EBUSY (already loaded)";
    case ENOEXEC:  return "ENOEXEC (invalid module format)";
    case EINVAL:   return "EINVAL (bad arg / unresolved symbol)";
    case ENFILE:   return "ENFILE";
    case ENOSYS:   return "ENOSYS (CONFIG_MODULES=n?)";
    case ELIBBAD:  return "ELIBBAD (wrong .ko format)";
    case EEXIST:   return "EEXIST (module already loaded)";
    default:       return "(unknown)";
    }
}

int main(int argc, char **argv) {
    int mem_fd;
    if (argc < 2) {
        fprintf(stderr, "usage: %s <module.ko> [params]\n", argv[0]);
        return 2;
    }
    /* mmap PL011 */
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) { fprintf(stderr, "open /dev/mem: %s\n", strerror(errno)); return 1; }
    uart_base = mmap(NULL, PL011_SIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED, mem_fd, PL011_BASE);
    if (uart_base == MAP_FAILED) {
        fprintf(stderr, "mmap PL011: %s\n", strerror(errno));
        return 1;
    }

    /* Load .ko into memory */
    int kofd = open(argv[1], O_RDONLY);
    if (kofd < 0) {
        uart_puts("[kinsmod] open(");
        uart_puts(argv[1]);
        uart_puts(") FAILED errno=");
        uart_putd(errno);
        uart_puts(" ");
        uart_puts(errno_name(errno));
        uart_puts("\n");
        return 1;
    }
    struct stat st;
    fstat(kofd, &st);
    void *buf = malloc(st.st_size);
    if (!buf) {
        uart_puts("[kinsmod] malloc failed\n");
        return 1;
    }
    ssize_t r = read(kofd, buf, st.st_size);
    close(kofd);
    if (r != st.st_size) {
        uart_puts("[kinsmod] short read\n");
        return 1;
    }

    uart_puts("[kinsmod] try ");
    uart_puts(argv[1]);
    uart_puts(" (");
    uart_putd(st.st_size);
    uart_puts(" bytes)\n");

    /* Build module params string from argv[2..] */
    char params[512] = "";
    for (int i = 2; i < argc; i++) {
        if (i > 2) strncat(params, " ", sizeof(params) - strlen(params) - 1);
        strncat(params, argv[i], sizeof(params) - strlen(params) - 1);
    }

    /* init_module(2) syscall — direct, no busybox layer */
    long ret = syscall(SYS_init_module, buf, (unsigned long)st.st_size, params);
    int saved_errno = errno;

    uart_puts("[kinsmod] init_module() returned ");
    uart_putd(ret);
    if (ret < 0) {
        uart_puts(" errno=");
        uart_putd(saved_errno);
        uart_puts(" ");
        uart_puts(errno_name(saved_errno));
    } else {
        uart_puts(" OK");
    }
    uart_puts("\n");

    free(buf);
    return ret < 0 ? 1 : 0;
}
