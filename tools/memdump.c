/* memdump — bulk physical memory dump via /dev/mem mmap.
 * Usage: memdump <hex_phys_addr> <hex_size_bytes> > out.hex
 * Output: one line per dword "ADDR VAL\n" hex.
 *
 * Compile: arm-buildroot-linux-gnueabihf-gcc -O2 -static memdump.c -o memdump
 * Push to stock /tmp/memdump via tftp; run with elevated perms (root). */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s <hex_phys_addr> <hex_size_bytes>\n", argv[0]);
        return 2;
    }
    unsigned long addr = strtoul(argv[1], NULL, 16);
    unsigned long size = strtoul(argv[2], NULL, 16);
    if (size & 3) { fprintf(stderr, "size must be 4-byte aligned\n"); return 2; }

    int fd = open("/dev/mem", O_RDONLY | O_SYNC);
    if (fd < 0) { perror("/dev/mem"); return 1; }

    unsigned long pagesize = sysconf(_SC_PAGESIZE);
    unsigned long page_off = addr & (pagesize - 1);
    unsigned long map_addr = addr - page_off;
    unsigned long map_len  = (page_off + size + pagesize - 1) & ~(pagesize - 1);

    void *map = mmap(NULL, map_len, PROT_READ, MAP_SHARED, fd, map_addr);
    if (map == MAP_FAILED) { perror("mmap"); return 1; }

    volatile uint32_t *base = (volatile uint32_t *)((char *)map + page_off);
    unsigned long n = size / 4;
    for (unsigned long i = 0; i < n; i++) {
        printf("%08lx %08x\n", addr + i*4, base[i]);
    }

    munmap(map, map_len);
    close(fd);
    return 0;
}
