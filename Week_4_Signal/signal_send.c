#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count = 0;
void signal_hanlder(){
    count++;
    printf("SIGINT nhận %d lần\n", count);
    if(count == 3){
        printf("Đã nhận SIGINT 3 lần, kết thúc chương trình.\n");
        exit(0);
    }
}
int main(){
    signal(SIGINT, signal_hanlder);
    printf("Chạy chương trình. Nhấn Ctrl+C để gửi SIGINT.\n");
    while(1) {
        printf("Chương trình đang chạy...\n");
        sleep(1);
    }
    return 0;
}