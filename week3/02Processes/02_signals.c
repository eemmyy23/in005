
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int num) {
    fprintf(stdout, "Received signal %d\n", num);
}

int main(void) {
    int i;

    for (i = 1; i < NSIG; i++) {
        // signal(num, function) tries to set "function" as signal handler
        // for signal "num"
        if (signal(i, sig_handler) == SIG_ERR) {
            fprintf(stderr, "Signal %d cannot be captured\n", i);
        }
    }
    
    fprintf(stdout, "My PID=%ld", (long) getpid());
    
    // Signal handler is now installed
    // Open another terminal and try to send some signals to this process...
    
    while (1) {
        pause();
    }
}


