#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int a = fork();
    if(a == 0){
        printf("This is the child process with pid %d", getpid());
    }
    else if(a > 0){
        sleep(100000);
        printf("This is the parent process with pid %d", getpid());

    }
    else{
        perror("Can not create child process");
        return 1;
    }
    return 0;
}