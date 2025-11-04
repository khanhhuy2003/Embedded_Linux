#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int count = 0;
void alarm_handler(int sig) {
    printf("Alarm %d\n", count++);
    if(count == 10){
        exit(0);
    }
    else{
        alarm(1);
    }

}

int main() {
    // Đăng ký handler cho SIGALRM
    signal(SIGALRM, alarm_handler);

    printf("Đặt alarm 10 giây...\n");
    alarm(1); 
    while(1) {

    }

    return 0;
}