/* printok — write OK + optional arg to ZTE-shifted PL011. For init.norm bisect.
 * Build: arm-linux-gnueabi-gcc -static -O2 -Wall -o out/printok printok.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#define PL011_BASE 0x94404000u
#define PL011_SIZE 0x1000u
#define DR 0x04u
#define FR 0x14u
#define FR_TXFF (1u<<5)
int main(int argc, char **argv) {
    int fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (fd < 0) return 1;
    volatile unsigned char *b = mmap(NULL, PL011_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, PL011_BASE);
    if (b == MAP_FAILED) return 2;
    const char *prefix = "[printok]";
    const char *arg = (argc > 1) ? argv[1] : "OK";
    int timeout;
    while (*prefix) {
        timeout = 100000;
        while ((*(volatile unsigned int *)(b + FR) & FR_TXFF) && --timeout) ;
        *(volatile unsigned int *)(b + DR) = (unsigned int)(*prefix++ & 0xff);
    }
    timeout = 100000;
    while ((*(volatile unsigned int *)(b + FR) & FR_TXFF) && --timeout) ;
    *(volatile unsigned int *)(b + DR) = ' ';
    while (*arg) {
        timeout = 100000;
        while ((*(volatile unsigned int *)(b + FR) & FR_TXFF) && --timeout) ;
        *(volatile unsigned int *)(b + DR) = (unsigned int)(*arg++ & 0xff);
    }
    timeout = 100000; while ((*(volatile unsigned int *)(b + FR) & FR_TXFF) && --timeout) ; *(volatile unsigned int *)(b + DR) = '\r';
    timeout = 100000; while ((*(volatile unsigned int *)(b + FR) & FR_TXFF) && --timeout) ; *(volatile unsigned int *)(b + DR) = '\n';
    return 0;
}
