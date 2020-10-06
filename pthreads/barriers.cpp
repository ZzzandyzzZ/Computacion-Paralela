#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <semaphore.h>
#define THREAD_COUNT 4
using namespace std;
/*
pthread_barrier_t mybarrier;
void* threadFn(void *id_ptr) {
    char print[100];
    int thread_id = *(int*)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 10;
    printf("thread %d: Espera por %d segundos.\n", thread_id, wait_sec);
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    printf("thread %d: Estoy listo...\n", thread_id);
    pthread_barrier_wait(&mybarrier);
    printf("thread %d: Ejecutando!\n", thread_id);
    return NULL;
}


int main() {
    int i;
    char print[100];
    pthread_t ids[THREAD_COUNT];
    int short_ids[THREAD_COUNT];
    pthread_barrier_init(&mybarrier, NULL,3);

    for (i=0; i < THREAD_COUNT; i++) {
        short_ids[i] = i;
        pthread_create(&ids[i], NULL, threadFn, &short_ids[i]);
    }

    printf("main() is ready.\n");
    pthread_barrier_wait(&mybarrier);
    printf("main() is going!\n");
    for (i=0; i < THREAD_COUNT; i++) {
        pthread_join(ids[i], NULL);
    }
    pthread_barrier_destroy(&mybarrier);
    return 0;
}
*/
/*
pthread_barrier_t mybarrier;

void* threadFn(void *id_ptr) {
    char print[100];
    int thread_id = (int)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 10;
    sprintf(print,"thread %d: Espera por %d segundos.\n", thread_id, wait_sec);cout<<print;
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    sprintf(print,"thread %d: Estoy listo...\n", thread_id);cout<<print;
    pthread_barrier_wait(&mybarrier);
    sprintf(print,"thread %d: Ejecutando!\n", thread_id);cout<<print;
    return NULL;
}

int main() {
    int thread;
    char print[100];
    pthread_t ids[THREAD_COUNT];
    pthread_barrier_init(&mybarrier, NULL,5);
    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_create(&ids[thread], NULL, threadFn, (void*) thread);
    }
    sprintf(print,"main() is ready.\n");cout<<print;
    pthread_barrier_wait(&mybarrier);

    sprintf(print,"main() is going!\n");cout<<print;
    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_join(ids[thread], NULL);
    }
    pthread_barrier_destroy(&mybarrier);
    return 0;
}
*/
/*
int counter=0;
int thread_count=4;
pthread_mutex_t barrier_mutex;

void* threadFn(void *id_ptr) {
    char print[100];
    int thread_id = (int)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 10;
    sprintf(print,"thread %d: Espera por %d segundos.\n", thread_id, wait_sec);
    cout<<print;
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    sprintf(print,"thread %d: Estoy listo...\n", thread_id);
    cout<<print;
    pthread_mutex_lock(&barrier_mutex);
    counter++;
    pthread_mutex_unlock(&barrier_mutex);
    while (counter < thread_count);
    sprintf(print,"thread %d: Ejecutando!\n", thread_id);
    cout<<print;
    return NULL;
}

int main() {
    int thread;
    char print[100];
    pthread_t ids[THREAD_COUNT];

    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_create(&ids[thread], NULL, threadFn, (void*) thread);
    }
    sprintf(print,"main() is ready.\n");
    cout<<print;
    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_join(ids[thread], NULL);
    }

    return 0;
}
*/
/*
int counter=0;
int thread_count=8;
sem_t count_sem;
sem_t barrier_sem;

void* threadFn(void *id_ptr) {
    char print[100];
    int thread_id = (int)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 10;
    sprintf(print,"thread %d: Espera por %d segundos.\n", thread_id, wait_sec);
    cout<<print;
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    sprintf(print,"thread %d: Estoy listo...\n", thread_id);
    cout<<print;
    sem_wait(&count_sem);
    if (counter == thread_count-1) {
        counter = 0;
        sem_post(&count_sem);
        for (int j = 0; j < thread_count-1; j++)
            sem_post(&barrier_sem);
    } else {
        counter++;
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
    }
    sprintf(print,"thread %d: Ejecutando!\n", thread_id);
    cout<<print;
    return NULL;
}

int main() {
    int thread;
    char print[100];
    pthread_t ids[THREAD_COUNT];

    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_create(&ids[thread], NULL, threadFn, (void*) thread);
    }
    sprintf(print,"main() is ready.\n");
    cout<<print;
    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_join(ids[thread], NULL);
    }

    return 0;
}
*/

int counter=0;
int thread_count=4;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

void* threadFn(void *id_ptr) {
    char print[100];

    int thread_id = (int)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 20;
    sprintf(print,"thread %d: Espera por %d segundos.\n", thread_id, wait_sec);
    cout<<print;
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    sprintf(print,"thread %d: Estoy listo...\n", thread_id);
    cout<<print;

    pthread_mutex_lock(&mutex);
    counter++;
    if (counter == thread_count) {
        counter = 0;
        cout<<"DESPIERTEN\n";
        pthread_cond_broadcast(&cond_var);

    } else {
        pthread_cond_wait(&cond_var, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    sprintf(print,"thread %d: Ejecutando!\n", thread_id);
    cout<<print;
    return NULL;
}

int main() {
    int thread;
    char print[100];
    pthread_t ids[THREAD_COUNT];

    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_create(&ids[thread], NULL, threadFn, (void*) thread);
    }
    sprintf(print,"main() is ready.\n");
    cout<<print;
    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_join(ids[thread], NULL);
    }

    return 0;
}

