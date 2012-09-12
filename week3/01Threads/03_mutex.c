/* gcc XXXX.c -o XXXX -lpthread */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


static void* routine_threads(void* argument);
static int aleatoire(int maximum);

pthread_mutex_t mutex_stdout;

int main(void) {
    int i;
    pthread_t thread;
    
    XXXXXX

    for (i = 0; i < 10; i++) {
        pthread_create(& thread, NULL, routine_threads, (void*) i);
    }
    
    sleep(1);
    pthread_exit NULL;
}

static void* routine_threads(void* argument) {
    int numero = (int) argument;
    int nombre_iterations;
    int i;
    nombre_iterations = 1 + aleatoire(3);
    for (i = 0; i < nombre_iterations; i++) {
        sleep(aleatoire(3));
        
        pthread_mutex_lock(&mutex_stdout);
        fprintf(stdout, "Thread %d gained mutex\n", numero);
        sleep(aleatoire(3));
        fprintf(stdout, "Thread %d releases mutex\n", numero);
        XXXXXX
    }
    return NULL;
}

static int aleatoire(int maximum) {
    double d;
    d = (double) maximum * rand();
    d = d / (RAND_MAX + 1.0);
    return ((int) d);
}
