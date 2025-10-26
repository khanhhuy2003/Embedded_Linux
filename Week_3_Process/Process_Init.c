#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>
#include <sys/wait.h>
int main(){
    int a = fork();
    int status;
    if (a < 0){
        perror("Can not create process");
        return 1;
    }
    if(a == 0){
        printf("This is the child process with %d \n", getpid());
        exit(10); 
    }
    else {
        printf("This is the parent process with  %d \n", getpid());
        printf("This is the child process with  %d \n", a);
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Parent: Child exited normally with status = %d\n",
                   WEXITSTATUS(status));
        } else {
            printf("Parent: Child did not exit normally\n");
        }
    }

    return 0;
}