#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

uint8_t ready_flag = 0;
int number = 0;

void *producer(void* arg){
    pthread_mutex_lock(&mux);
    for(int i = 0; i < 10; i++){
        number++;
    }
    ready_flag = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mux);
    return NULL;
}

void* consumer(void* arg){
    pthread_mutex_lock(&mux);
    for(int i = 0; i < 10; i++){
        
        while (ready_flag == 0){
            pthread_cond_wait(&cond, &mux);
        }
        printf("%d", number);
        
        
    }
    ready_flag = 0;
    pthread_mutex_unlock(&mux);
    return NULL;
}

int main(){
    pthread_t t_c, t_p;

    pthread_create(&t_p, NULL, producer, NULL);
    for(int i = 0; i < 100000; i++);
    pthread_create(&t_c, NULL, consumer, NULL);


    pthread_join(t_c, NULL);
    pthread_join(t_p, NULL);

    return 0;
}
