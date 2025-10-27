#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;
int shared_data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    pthread_rwlock_rdlock(&lock);
    printf("Reader %d: read shared_data = %d\n", id, shared_data);
    pthread_rwlock_unlock(&lock);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    pthread_rwlock_wrlock(&lock);
    shared_data += 10;
    printf("Writer %d: wrote shared_data = %d\n", id, shared_data);
    pthread_rwlock_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t r1, r2, r3, r4, r5, w1, w2;
    int ids[7] = {1,2,3,4,5,1,2};

    pthread_create(&r1, NULL, reader, &ids[0]);
    pthread_create(&r2, NULL, reader, &ids[1]);
    pthread_create(&r3, NULL, reader, &ids[2]);
    pthread_create(&r4, NULL, reader, &ids[3]);
    pthread_create(&r5, NULL, reader, &ids[4]);    
    pthread_create(&w1, NULL, writer, &ids[5]);
    pthread_create(&w2, NULL, writer, &ids[6]);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(r4, NULL);
    pthread_join(r5, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);
    pthread_rwlock_destroy(&lock);
    return 0;
}