/* /init: C binary as PID 1.
 *   - mount filesystems
 *   - insmod driver, bring up sw
 *   - REPL loop: read line from /dev/console, system(cmd), repeat
 * Avoids busybox-sh-as-PID-1 entirely.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/wait.h>

static int kmsg_fd = -1;
static void kmsg(const char *s) {
    if (kmsg_fd < 0) return;
    char b[512];
    int n = snprintf(b, sizeof b, "<5>[INIT] %s\n", s);
    write(kmsg_fd, b, n);
}

static int sh(const char *cmdline) {
    pid_t p = fork();
    if (p == 0) {
        execl("/bin/busybox", "busybox", "sh", "-c", cmdline, NULL);
        _exit(127);
    }
    int st = 0; waitpid(p, &st, 0); return st;
}

int main(void) {
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);
    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);
    mount("tmpfs", "/tmp", "tmpfs", 0, NULL);
    mount("debugfs", "/sys/kernel/debug", "debugfs", 0, NULL);

    kmsg_fd = open("/dev/kmsg", O_WRONLY);
    kmsg("==== C init alive ====");

    kmsg("insmod zx279128-eth.ko");
    sh("/bin/busybox insmod /lib/modules/zx279128-eth.ko");
    kmsg("ip link set sw up");
    sh("/bin/busybox ip link set sw up");
    kmsg("ip addr add 192.168.1.99/24 dev sw");
    sh("/bin/busybox ip addr add 192.168.1.99/24 dev sw");

    /* Router bring-up: run /etc/rc.router if present (LAN/WAN ifaces, udhcpd,
     * ip_forward, NAT rules). Config-as-data so we don't recompile PID 1 to
     * tweak the router setup. See tasks/00.01.eth-driver/configs/rc.router. */
    kmsg("running /etc/rc.router (router bring-up)");
    sh("[ -f /etc/rc.router ] && /bin/busybox sh /etc/rc.router");

    kmsg("=== entering REPL on /dev/console ===");

    /* Keep kernel log noise off the REPL input stream.
     * Single-byte read(fd0) treats every console byte (including
     * printk output) as user input → garbled commands. */
    sh("echo 3 4 1 7 > /proc/sys/kernel/printk");

    /* Open /dev/console for read+write, dup to stdio. */
    int fd = open("/dev/console", O_RDWR);
    if (fd >= 0) { dup2(fd, 0); dup2(fd, 1); dup2(fd, 2); if (fd>2) close(fd); }

    const char *prompt = "\r\n# ";
    write(1, "\r\n=== C-init REPL ready on UART ===\r\n", 38);
    write(1, prompt, 4);

    char line[1024];
    int len = 0;
    for (;;) {
        char c;
        int r = read(0, &c, 1);
        if (r <= 0) { sleep(1); continue; }
        write(1, &c, 1);  /* local echo */
        if (c == '\r') { write(1, "\n", 1); }
        if (c == '\r' || c == '\n') {
            line[len] = 0;
            if (len > 0) {
                int s_ = sh(line);
                char b[64]; int n = snprintf(b, sizeof b, "[exit=%d]\r\n", s_);
                write(1, b, n);
            }
            len = 0;
            write(1, prompt, 4);
        } else if (c == 0x7f || c == '\b') {
            if (len > 0) { len--; write(1, "\b \b", 3); }
        } else if (len < (int)sizeof(line) - 1) {
            line[len++] = c;
        }
    }
    return 0;
}
