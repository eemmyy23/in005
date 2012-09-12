/* gcc sync01.c -o sync01 -lpthread */
#include <stdio.h>
#include <pthread.h>
#define NR_OF_THREADS 100
#define NR_OF_ITERATIONS 1000

long lCounter = 0;
XXXXXX

void threadCode(void *pvArg) {
    int i = 0;
    for (i = 0; i < NR_OF_ITERATIONS; i++) {
        XXXXXX
        lCounter = lCounter + 1;
        XXXXXX
    }
}

int main(void) {
    pthread_t sThread[NR_OF_THREADS];
    int i = 0;

    /* launch all the threads */
    for (i = 0; i < NR_OF_THREADS; i++) {
        pthread_create(&sThread[i], NULL, (void *) &threadCode, (void *) NULL);
    }

    /* wait for all the threads to finish */
    for (i = 0; i < NR_OF_THREADS; i++) {
        pthread_join(sThread[i], NULL);
    }

    /* show the final result */
    printf("\nresult: %ld\n", lCounter);
}
