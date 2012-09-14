/* gcc XXXX.c -o XXXX -lpthread 
gcc 02_join.c -o 02_join -lpthread
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void * fn_thread(void * inutile);

int main(void) {
    int i;
    int ret;
    pthread_t thread;
    void** retour;

    if ((ret = pthread_create(& thread, NULL, fn_thread, NULL)) != 0) {
        fprintf(stderr, "%s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    pthread_join(thread, retour);

    if (retour != PTHREAD_CANCELED) {
        i = (int) *retour;
        fprintf(stdout, "main : value = %d\n", i);
    }

    return EXIT_SUCCESS;
}

void * fn_thread(void * inutile) {
    char chaine[128];
    int i = 0;

    fprintf(stdout, "Thread : enter a number : ");
    while (fgets(chaine, 128, stdin) != NULL) {
        if (sscanf(chaine, "%d", & i) != 1) {
            fprintf(stdout, "a number please! :");
        } else {
            break;
        }
    }
    sleep(1);
    pthread_exit((void*) i);
}
