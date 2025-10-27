#include <pthread.h>
#include <stdio.h>
#include "stdint.h"
void *myThreadFunc1(void *arg){
    pthread_t tid = pthread_self();
    printf("Hello from thread 1 with id %lu \n", (unsigned long)tid);
}
void *myThreadFunc2(void *arg){
    pthread_t tid = pthread_self();
    printf("Hello from thread 2 with id %lu \n", (unsigned long)tid);
} 
int main(){
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, myThreadFunc1, NULL);
    pthread_create(&t2, NULL, myThreadFunc2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}