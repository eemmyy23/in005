#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

static void * routine_thread(void * numero_thread);
static int aleatoire(int maximum);

int main(void) {
    int i;
    pthread_t thread;

    XXXXXX;

    for (i = 0; i < 10; i++) {
        pthread_create(& thread, NULL, routine_thread, (void *) i);
    }
    sleep(1);
    pthread_exit(NULL);
}

void * routine_thread(void * numero_thread) {
    int i;
    for (i = 0; i < 2; i++) {

        sem_wait(& semaphore);
        fprintf(stdout, "Thread %d is inside critical section\n", (int) numero_thread);
        sleep(aleatoire(4));

        fprintf(stdout, "Thread %d leaves critical section\n", (int) numero_thread);
        XXXXXX;
        sleep(aleatoire(4));
    }
    return NULL;
}

static int aleatoire(int maximum) {
    double d;
    d = (double) maximum * rand();
    d = d / (RAND_MAX + 1.0);
    return ((int) d);
}
