#include "stdio.h"
#include "sys/stat.h"
#include "time.h"
#include <sys/types.h>
#include "string.h"


void print_permissions(mode_t mode); 
void print_permissions(mode_t mode) {
    char perm[11];

    perm[0] = S_ISDIR(mode) ? 'd' :
              S_ISLNK(mode) ? 'l' : '-';

    perm[1] = (mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (mode & S_IROTH) ? 'r' : '-';
    perm[8] = (mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (mode & S_IXOTH) ? 'x' : '-';
    perm[10] = '\0';

    printf("Permissions: %s\n", perm);
}
int main(){
    struct stat file_status;
    char path[256];
    printf("Please enter the file location: ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
        return 1; 
    }
    path[strcspn(path, "\n")] = 0; // xoa newline
    if(stat(path,&file_status) == -1){
        perror("Error");
        return 1;
    }
    print_permissions(file_status.st_mode);
    printf("The size of file is %ld (bytes)\n", file_status.st_size);
    if(S_ISREG(file_status.st_mode)){
        printf("This is a regular file\n");
    }
    else if(S_ISDIR(file_status.st_mode)){
        printf("This is a directory\n");
    }

    printf("The last time modified is %s \n", ctime(&file_status.st_mtime));
    return 0;
}