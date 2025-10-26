#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

char **split_command(const char *cmd) {
    if (!cmd) return NULL;
    char *s = strdup(cmd);
    if (!s) return NULL;

    size_t capacity = 8;
    size_t count = 0;
    char **argv = malloc(sizeof(char *) * capacity);
    if (!argv) { 
        free(s); return NULL; 
    }

    char *token = strtok(s, " \t");
    while (token) {
        if (count + 1 >= capacity) {
            capacity *= 2;
            char **tmp = realloc(argv, sizeof(char *) * capacity);
            if (!tmp) break;
            argv = tmp;
        }
        argv[count++] = strdup(token); 
        token = strtok(NULL, " \t");
    }
    argv[count] = NULL;
    free(s);
    if (count == 0) {
        free(argv);
        return NULL;
    }
    return argv;
}

void free_argv(char **argv) {
    if (!argv) return;
    for (size_t i = 0; argv[i]; ++i) free(argv[i]);
    free(argv);
}

int main(void) {
    pid_t pid;
    int status;
    if (setenv("MY_COMMAND", "ls -l", 1) != 0) {
        perror("setenv");
        return 1;
    }

    printf("Parent: MY_COMMAND set to '%s'\n", getenv("MY_COMMAND"));

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        char *cmd = getenv("MY_COMMAND");
        if (!cmd) {
            fprintf(stderr, "Child: MY_COMMAND not set\n");
            exit(2);
        }

        printf("Child: read MY_COMMAND = '%s'\n", cmd);
        char **argv = split_command(cmd);
        if (!argv) {
            fprintf(stderr, "Child: failed to parse command or empty command\n");
            exit(3);
        }
        execvp(argv[0], argv);
        fprintf(stderr, "Child: execvp failed: %s\n", strerror(errno));
        free_argv(argv);
        exit(4);
    } else {
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("Parent: child exited with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent: child killed by signal %d\n", WTERMSIG(status));
        } else {
            printf("Parent: child ended unexpectedly\n");
        }
    }

    return 0;
}
