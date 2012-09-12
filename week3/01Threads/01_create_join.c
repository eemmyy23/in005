/* gcc XXXX.c -o XXXX -lpthread
gcc 01_create_join.c -o 01_create_join -lpthread
*/

#define _XOPEN_SOURCE 500
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//XXXXX
#define NB_THREADS 10

void * fn_thread(void * number);

static int counter = 0;

int main(void) {
    pthread_t thread[NB_THREADS];
    int i;
    int ret;

    for (i = 0; i < NB_THREADS; i++) {
        if ((ret = pthread_create(& thread[i], NULL, fn_thread, (void *) i)) != 0) {
            fprintf(stderr, "%d : %s", i, strerror(ret));
            exit(EXIT_FAILURE);
        }
    }

    while (counter < 40) {
        fprintf(stdout, "main : counter = %d\n", counter);
        sleep(1);
    }

    for (i = 0; i < NB_THREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    return EXIT_SUCCESS;
}

void * fn_thread(void * num) {
    int number = (int) num;
    while (counter < 40) {
        usleep(number * 100000);
        //XXXXXX
        counter++;
        fprintf(stdout, "Thread %d : counter = %d\n", number, counter);
    }
    pthread_exit(NULL);
}
