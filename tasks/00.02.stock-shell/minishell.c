/*
 * minishell — a TINY interactive shell for the ZTE H3600 SSH path.
 *
 * Drop-in replacement for /bin/cliagent. Bypasses busybox-ash entirely
 * (which hangs after the ZTE-patched dropbear's exec for reasons we
 * haven't fully isolated — see kotrace_bake_in.md findings).
 *
 * What it does: prompt → read line → tokenize on whitespace → fork +
 * execvp → waitpid. That's it. No globbing, no quoting, no env
 * substitution. Use `sh -c '...'` for anything fancy.
 *
 * Build: arm-linux-gnueabi-gcc -static -O2 -Wall -o out/cliagent minishell.c
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

#define MAX_LINE   4096
#define MAX_ARGS   64

static void prompt(void) {
    /* Plain prompt; getuid==0 picks #, else $. */
    char p = (getuid() == 0) ? '#' : '$';
    char buf[3] = { p, ' ', 0 };
    write(STDOUT_FILENO, buf, 2);
}

static int run_line(char *line) {
    /* In-place tokenize on whitespace. */
    char *argv[MAX_ARGS];
    int argc = 0;
    char *p = line;
    while (*p && argc < MAX_ARGS - 1) {
        while (*p == ' ' || *p == '\t') *p++ = 0;
        if (!*p) break;
        argv[argc++] = p;
        while (*p && *p != ' ' && *p != '\t') p++;
    }
    argv[argc] = NULL;
    if (argc == 0) return 0;

    /* Built-ins. */
    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "logout") == 0) {
        _exit(0);
    }
    if (strcmp(argv[0], "cd") == 0) {
        const char *target = argv[1] ? argv[1] : getenv("HOME");
        if (target && chdir(target) < 0) perror("cd");
        return 0;
    }
    if (strcmp(argv[0], "pwd") == 0) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd))) {
            write(STDOUT_FILENO, cwd, strlen(cwd));
            write(STDOUT_FILENO, "\n", 1);
        }
        return 0;
    }
    if (strcmp(argv[0], "echo") == 0) {
        for (int i = 1; i < argc; i++) {
            if (i > 1) write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        }
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }

    /* Fork + execvp. */
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        /* Restore default signal handlers in case parent has some masked. */
        sigset_t all; sigfillset(&all);
        sigprocmask(SIG_UNBLOCK, &all, NULL);
        execvp(argv[0], argv);
        fprintf(stderr, "%s: %s\n", argv[0], strerror(errno));
        _exit(127);
    }
    int status;
    while (waitpid(pid, &status, 0) < 0) {
        if (errno != EINTR) { perror("waitpid"); break; }
    }
    return 0;
}

int main(int argc, char **argv) {
    /* Unblock all signals first thing — dropbear leaks them. */
    sigset_t all; sigfillset(&all);
    sigprocmask(SIG_UNBLOCK, &all, NULL);

    /* Env basics. */
    setenv("HOME", "/root", 0);
    setenv("PATH", "/sbin:/bin:/usr/bin:/usr/sbin", 0);
    setenv("SHELL", "/bin/cliagent", 0);
    if (!getenv("TERM")) setenv("TERM", "vt100", 1);

    /* Banner — proves we're alive on the user's terminal. */
    static const char banner[] =
        "\r\nminishell - ZTE H3600 SSH bypass shell\r\n"
        "type 'exit' to quit, 'sh -c \"...\"' for compound commands.\r\n\r\n";
    write(STDOUT_FILENO, banner, sizeof(banner) - 1);

    /* REPL — read line-by-line (one char at a time) so multi-line
     * buffered input works the same as line-buffered PTY input. */
    char line[MAX_LINE];
    while (1) {
        prompt();
        int n = 0;
        while (n < (int)sizeof(line) - 1) {
            char c;
            ssize_t r = read(STDIN_FILENO, &c, 1);
            if (r == 0) goto eof;
            if (r < 0) {
                if (errno == EINTR) continue;
                goto eof;
            }
            if (c == '\n') break;
            if (c == '\r') continue;
            line[n++] = c;
        }
        line[n] = 0;
        run_line(line);
    }
eof:
    return 0;
}
