/* gcc XXXX.c -o XXXX -lpthread */

#define _XOPEN_SOURCE 500
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define XXXXXX

void * fn_thread(void * numero);

static int compteur = 0;

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

    while (compteur < 40) {
        fprintf(stdout, "main : compteur = %d\n", compteur);
        sleep(1);
    }

    for (i = 0; i < NB_THREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    return EXIT_SUCCESS;
}

void * fn_thread(void * num) {
    int numero = (int) num;
    while (compteur < 40) {
        usleep(numero * 100000);
        XXXXXX
        fprintf(stdout, "Thread %d : compteur = %d\n", numero, compteur);
    }
    pthread_exit(NULL);
}