
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"


long thread_count;
unsigned long long n=pow(10,9);
pthread_mutex_t mutex;
int flag=0;
double suma=0.0;

void* Thread_sum(void* rank) {
   long my_rank = (long) rank;
   double factor, my_suma = 0.0;
   long long i;
   long long my_n = n/thread_count;
   long long my_first_i = my_n*my_rank;
   long long my_last_i = my_first_i + my_n;

   if (my_first_i % 2 == 0) factor = 1.0;
   else factor = -1.0;

   for (i = my_first_i; i < my_last_i; i++, factor = -factor)
      my_suma += factor/(2*i+1);

   pthread_mutex_lock(&mutex);
   suma += my_suma;
   pthread_mutex_unlock(&mutex);
   return NULL;
}


int main(int argc, char* argv[]) {
  printf("| %8s | %8s|\n","Num_th","Tiempo");
    for(int i=0;i<=6;i++){

   long  thread;
   pthread_t* thread_handles;
   pthread_mutex_init(&mutex, NULL);
   double start, finish;
   double time;


   thread_count = pow(2,i);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));

   GET_TIME(start);

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Thread_sum, (void*)thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);
   GET_TIME(finish);

   time=finish-start;
   printf("| %8d | %8f |\n",thread_count ,time);
   pthread_mutex_destroy(&mutex);
   free(thread_handles);
    }
   return 0;
}





