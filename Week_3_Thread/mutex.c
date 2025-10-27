#include <pthread.h>
#include <stdio.h>
#include "stdint.h"
/*
1) Semaphore (binary / counting)

Dùng để đồng bộ giữa các thread hoặc giới hạn số thread chạy song song

Có thể cho phép nhiều thread truy cập nếu là counting semaphore

2) Condition variable (pthread_cond_t)

Kết hợp với mutex

Cho phép một thread chờ một điều kiện xảy ra thay vì bận chờ (busy waiting)

Dùng trong bài toán Producer–Consumer rất phổ biến

3) Read-Write Lock (pthread_rwlock_t)

Cho phép nhiều thread đọc song song (shared read)

Nhưng chỉ 1 thread ghi (exclusive write)

Hiệu quả hơn mutex khi chủ yếu là đọc ít ghi

4) Spinlock (pthread_spinlock_t)

Giống mutex nhưng bận chờ (busy wait), không sleep

Dùng trong môi trường real-time hoặc critical section ngắn

5) Barrier (pthread_barrier_t)

Đồng bộ nhiều thread tại một điểm — tất cả dừng lại chờ cho đến khi đủ số thread tới cùng một điểm, rồi mới chạy tiếp

6) Atomic operations (stdatomic.h)

Đồng bộ cấp phần cứng (không cần mutex)

Dùng cho các thao tác đơn giản (increment, swap, compare-and-swap)

7) Futex (Fast Userspace Mutex) – low-level

Dùng trong Linux kernel và glibc để tối ưu mutex, cond,… ở mức người dùng
*/
int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *myThreadFunc1(void *arg){
    int a = *(uint32_t*)arg;
    pthread_mutex_lock(&lock);
    for(int i = 0; i < a; i++){
        printf("Thread 1 update counter: %d\n", count++);
        //pthread_mutex_unlock(&lock);
    }
    pthread_mutex_unlock(&lock);

}
void *myThreadFunc2(void *arg){
    int a = *(uint32_t*)arg;
    pthread_mutex_lock(&lock);
    for(int i = 0; i < a; i++){
        //pthread_mutex_lock(&lock);
        printf("Thread 2 update counter: %d\n", count++);
        // pthread_mutex_unlock(&lock);
    }
    pthread_mutex_unlock(&lock);
} 
void *myThreadFunc3(void *arg){
    int a = *(uint32_t*)arg;
    pthread_mutex_lock(&lock);
    for(int i = 0; i < a; i++){
        //pthread_mutex_lock(&lock);
        printf("Thread 3 update counter: %d\n", count++);
        //pthread_mutex_unlock(&lock);

    }
    pthread_mutex_unlock(&lock);
} 
int main(){
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    int a = 1000000;
    
    pthread_create(&t1, NULL, myThreadFunc1, &a);
    pthread_create(&t2, NULL, myThreadFunc2, &a);
    pthread_create(&t3, NULL, myThreadFunc3, &a);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    return 0;
}