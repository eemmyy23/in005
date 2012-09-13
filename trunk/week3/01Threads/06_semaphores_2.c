// gcc 06_semaphores_2.c -o 06_semaphores_2 -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <semaphore.h>

#define NR_OF_ITEMS 10000
#define NR_OF_CONSUMERS 100

long lItem = 0;
long lItemLastReceived = 0;
int thisConsumer=0, lastConsumer=0;

sem_t filledSlots; 
sem_t emptySlots;

void threadProducer(void *pvArg) {
    int i = 0;
    for (i = 1; i < NR_OF_ITEMS; i++) {
		//sem_wait(&emptySlots);
        lItem = i;
        sem_post (&filledSlots);
        usleep(random() * 1000 / RAND_MAX);
    }
    lItem = -1;
}

void threadConsumer(void *pvArg) {
thisConsumer = (int) getpid ();
    while (lItem >= 0) {
        
        if (lItem > 0) {

        sem_wait(&filledSlots);
            long lStep;
            lStep = lItem - lItemLastReceived;
            if (lStep != 1) {
                printf("step %ld instead of 1\n", lStep);
            }
            lItemLastReceived = lItem;
            //printf("I've got item: %ld my id: %d\n", lItem,(int) getpid ()); 
			lItem = 0;
			//sem_post (&emptySlots);
        } else {
            usleep(random() * 10 / RAND_MAX);
        }
	//pthread_exit((void*) pvArg);    
	}
}

int main(void) {
    pthread_t sThreadProducer;
    pthread_t sThreadConsumer[NR_OF_CONSUMERS];
    int i = 0;

	 sem_init (&filledSlots, 0, 0);
	 sem_init (&emptySlots, 0, 0);
     sem_post (&emptySlots);

    /* launch all the threads */
    pthread_create(&sThreadProducer, NULL, (void *) &threadProducer, (void *) NULL);
    for (i = 0; i < NR_OF_CONSUMERS; i++) {
        pthread_create(&sThreadConsumer[i], NULL, (void *) &threadConsumer, (void *) NULL);
    }

while (1)
	if(thisConsumer != lastConsumer){
		printf("  -- >>  Consumer changed!");
		lastConsumer = thisConsumer;	
    }



    /* wait for all the threads to finish */
    pthread_join(sThreadProducer, NULL);
    for (i = 0; i < NR_OF_CONSUMERS; i++) {
        pthread_join(sThreadConsumer[i], NULL);
    }
}
