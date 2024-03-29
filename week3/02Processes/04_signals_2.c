#define	_XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void sigusr1_handler(int num) {
    int i;

    fprintf(stdout, "Handling of signal %d (%s)\n", num, strsignal(num));
    for (i = 1; i < 4; i++) {
        fprintf(stdout, "%d\n", i);
        sleep(1);
    }
    fprintf(stdout, "End of handling of signal %d\n", num);
}

int main(void) {
    signal(SIGUSR1, sigusr1_handler);
    if (fork() == 0) {
        // I am the child
        // Let's send some signals to my parent!
		kill(getppid(), SIGUSR1);
        
        sleep(5);
        
        kill(getppid(), SIGUSR1);

    } else {
        while (1) {
            pause();
        }
    }

    return EXIT_SUCCESS;
}

