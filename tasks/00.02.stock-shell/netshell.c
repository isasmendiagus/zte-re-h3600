/*
 * netshell — TCP-listening raw shell. Bypasses dropbear/ssh/PTY entirely.
 *
 * Listens on a port, accepts ONE connection at a time, dupes the socket
 * to stdin/stdout/stderr, then fork+exec'd children inherit the socket.
 *
 * For each connection: simple line-based REPL like minishell. Built-ins:
 * cd, pwd, echo, exit. Everything else: fork+execvp.
 *
 * Build: arm-linux-gnueabi-gcc -static -Os -s -o out/netshell netshell.c
 * Run on device: /sbin/netshell 9001 &
 * Connect: nc 192.168.1.1 9001
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>

#define MAX_LINE  4096
#define MAX_ARGS  64

static int run_line(char *line) {
    /* Tokenize into argv with single + double quote support.
     * Output buffer is separate from input so we don't trash the input
     * with our in-place NUL terminators. Examples:
     *   echo hello                  -> ["echo", "hello"]
     *   echo "hello world"          -> ["echo", "hello world"]
     *   sh -c 'echo > /proc/x'      -> ["sh", "-c", "echo > /proc/x"]
     */
    static char buf[MAX_LINE];
    char *argv[MAX_ARGS];
    int argc = 0;
    char *p = line;
    char *w = buf;
    char *end = buf + sizeof(buf) - 1;
    while (*p && argc < MAX_ARGS - 1 && w < end) {
        while (*p == ' ' || *p == '\t') p++;
        if (!*p) break;
        argv[argc++] = w;
        while (*p && *p != ' ' && *p != '\t' && w < end) {
            if (*p == '\'' || *p == '"') {
                char q = *p++;
                while (*p && *p != q && w < end) *w++ = *p++;
                if (*p == q) p++;
            } else {
                *w++ = *p++;
            }
        }
        *w++ = 0;
    }
    argv[argc] = NULL;
    if (argc == 0) return 0;

    if (!strcmp(argv[0], "exit") || !strcmp(argv[0], "logout")) return 1;
    if (!strcmp(argv[0], "cd")) {
        const char *t = argv[1] ? argv[1] : getenv("HOME");
        if (t && chdir(t) < 0) {
            const char *e = strerror(errno);
            dprintf(STDERR_FILENO, "cd: %s: %s\n", t, e);
        }
        return 0;
    }
    if (!strcmp(argv[0], "pwd")) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd))) dprintf(STDOUT_FILENO, "%s\n", cwd);
        return 0;
    }
    if (!strcmp(argv[0], "reset")) {
        /* open(O_WRONLY|O_TRUNC) + write(0) → triggers kotrace's
         * write() handler which resets the ring buffer. */
        if (!argv[1]) { dprintf(2, "usage: reset <path>\n"); return 0; }
        int rfd = open(argv[1], O_WRONLY | O_TRUNC);
        if (rfd < 0) { dprintf(2, "reset: %s: %s\n", argv[1], strerror(errno)); return 0; }
        write(rfd, "", 0);
        close(rfd);
        return 0;
    }
    if (!strcmp(argv[0], "echo")) {
        for (int i = 1; i < argc; i++) {
            if (i > 1) write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        }
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 0; }
    if (pid == 0) {
        sigset_t all; sigfillset(&all);
        sigprocmask(SIG_UNBLOCK, &all, NULL);
        execvp(argv[0], argv);
        dprintf(STDERR_FILENO, "%s: %s\n", argv[0], strerror(errno));
        _exit(127);
    }
    int status;
    while (waitpid(pid, &status, 0) < 0 && errno == EINTR) {}
    return 0;
}

static void serve(int fd) {
    /* Re-direct stdin/stdout/stderr to the socket. */
    dup2(fd, 0); dup2(fd, 1); dup2(fd, 2);
    if (fd > 2) close(fd);

    /* Unblock signals (in case parent has any masked). */
    sigset_t all; sigfillset(&all);
    sigprocmask(SIG_UNBLOCK, &all, NULL);

    /* Env */
    setenv("HOME", "/root", 0);
    setenv("PATH", "/sbin:/bin:/usr/bin:/usr/sbin", 0);
    setenv("SHELL", "/sbin/netshell", 0);
    if (!getenv("TERM")) setenv("TERM", "vt100", 1);
    chdir("/root");

    const char banner[] =
        "netshell - raw TCP shell, ZTE H3600\r\n"
        "built-ins: cd, pwd, echo, exit. fork+exec everything else.\r\n\r\n";
    write(STDOUT_FILENO, banner, sizeof(banner) - 1);

    char line[MAX_LINE];
    while (1) {
        write(STDOUT_FILENO, "# ", 2);
        int n = 0;
        while (n < (int)sizeof(line) - 1) {
            char c;
            ssize_t r = read(STDIN_FILENO, &c, 1);
            if (r <= 0) return;
            if (c == '\n') break;
            if (c == '\r') continue;
            line[n++] = c;
        }
        line[n] = 0;
        if (run_line(line)) return;
    }
}

int main(int argc, char **argv) {
    int port = argc > 1 ? atoi(argv[1]) : 9001;

    /* Ignore SIGPIPE so client disconnect doesn't kill the daemon. */
    signal(SIGPIPE, SIG_IGN);
    /* Reap children so they don't zombie. */
    signal(SIGCHLD, SIG_IGN);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) { perror("socket"); return 1; }
    int one = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); return 2;
    }
    if (listen(s, 4) < 0) { perror("listen"); return 3; }

    dprintf(2, "netshell: listening on port %d\n", port);

    while (1) {
        struct sockaddr_in c;
        socklen_t cl = sizeof(c);
        int cfd = accept(s, (struct sockaddr *)&c, &cl);
        if (cfd < 0) {
            if (errno == EINTR) continue;
            perror("accept"); break;
        }
        pid_t pid = fork();
        if (pid == 0) {
            close(s);
            serve(cfd);
            _exit(0);
        }
        close(cfd);
    }
    return 0;
}
