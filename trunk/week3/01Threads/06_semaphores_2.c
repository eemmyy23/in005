/* gcc sync02.c -o sync02 -lpthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//XXXXXXX

#define NR_OF_ITEMS 10000
#define NR_OF_CONSUMERS 10

long lItem = 0;
long lItemLastReceived = 0;

// XXXXXXXXX

void threadProducer(void *pvArg) {
    int i = 0;
    for (i = 1; i < NR_OF_ITEMS; i++) {
        lItem = i;
        // XXXXXXXXX
        usleep(random() * 1000 / RAND_MAX);
    }
    lItem = -1;
}

void threadConsumer(void *pvArg) {
    while (lItem >= 0) {
        // XXXXXXXXX
        if (lItem > 0) {
            long lStep;
            lStep = lItem - lItemLastReceived;
            if (lStep != 1) {
                printf("step %ld instead of 1\n", lStep);
            }
            lItemLastReceived = lItem;
            lItem = 0;
        } else {
            usleep(random() * 10 / RAND_MAX);
        }
    }
}

int main(void) {
    pthread_t sThreadProducer;
    pthread_t sThreadConsumer[NR_OF_CONSUMERS];
    int i = 0;

    // XXXXXXXXX

    /* launch all the threads */
    pthread_create(&sThreadProducer, NULL, (void *) &threadProducer, (void *) NULL);
    for (i = 0; i < NR_OF_CONSUMERS; i++) {
        pthread_create(&sThreadConsumer[i], NULL, (void *) &threadConsumer, (void *) NULL);
    }

    /* wait for all the threads to finish */
    pthread_join(sThreadProducer, NULL);
    for (i = 0; i < NR_OF_CONSUMERS; i++) {
        pthread_join(sThreadConsumer[i], NULL);
    }
}
