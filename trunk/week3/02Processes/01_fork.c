
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(void) {

    pid_t child_pid;

    do {
        child_pid = fork();

    } while ((child_pid == -1) && (errno == EAGAIN));


    if (child_pid == -1) {
        fprintf(stderr, "fork() impossible, errno=%d\n", errno);
        return 1;
    }

    if (child_pid == 0) {
        fprintf(stdout, "I am the XXXXXX : PID=%ld, PPID=%ld, Child PID=%ld\n", (long) getpid(), (long) getppid(), (long) child_pid);
        return 0;

    } else {
        fprintf(stdout, "I am the XXXXXX : PID=%ld, PPID=%ld, Child PID=%ld\n", (long) getpid(), (long) getppid(), (long) child_pid);
        wait(NULL);
        return 0;
    }
}
