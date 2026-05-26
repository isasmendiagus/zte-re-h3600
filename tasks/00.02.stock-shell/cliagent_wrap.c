/*
 * cliagent_wrap — drop-in /bin/cliagent that execs an interactive ash
 * AFTER unblocking SIGALRM that ZTE-patched dropbear leaks.
 *
 * Root cause (RE'd): dropbear's PtyCmdForShell sigprocmask(SIG_BLOCK,
 * SIGALRM, ...) before fork/execv and NEVER unblocks. The mask leaks
 * into the user shell across execve, and busybox-ash 1.17.2 hangs in
 * waitforjob() on every foreground command because SIGCHLD's wakeup
 * path interacts with the masked SIGALRM. Symptom: SSH login succeeds,
 * shell prompts, but typed commands echo and never execute.
 *
 * Fix: as the first thing this wrapper does, sigprocmask(SIG_UNBLOCK,
 * sigfillset, NULL) — restore the default signal mask — then exec ash.
 * The new ash inherits the clean mask, so fork+wait works normally.
 *
 * Build: arm-linux-gnueabi-gcc -static -O2 -Wall -o out/cliagent cliagent_wrap.c
 * Install: cp out/cliagent staging/bin/cliagent && chmod 755 ...
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

extern char **environ;

int main(int argc, char **argv) {
    sigset_t all;
    sigfillset(&all);
    sigprocmask(SIG_UNBLOCK, &all, NULL);   /* THE fix */

    /* Best-effort breadcrumb */
    int fd = open("/tmp/cliagent.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd >= 0) {
        const char msg[] = "cliagent_wrap: unblocked SIGALRM, exec /bin/ash\n";
        write(fd, msg, sizeof(msg) - 1);
        close(fd);
    }

    setenv("HOME",  "/root", 1);
    setenv("SHELL", "/bin/ash", 1);
    setenv("PATH",  "/sbin:/bin:/usr/bin:/usr/sbin", 1);
    if (!getenv("TERM")) setenv("TERM", "vt100", 1);
    chdir("/root");

    /* argv[0] = "-ash" so ash treats this as a login shell and runs
     * /etc/profile (which sets PS1, etc). */
    char *args[] = { (char *)"-ash", NULL };
    execve("/bin/ash", args, environ);

    /* exec failed */
    const char err[] = "cliagent_wrap: execve(/bin/ash) failed\n";
    write(2, err, sizeof(err) - 1);
    _exit(127);
}
