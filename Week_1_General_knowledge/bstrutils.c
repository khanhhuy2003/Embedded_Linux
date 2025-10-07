#include "bstrutils.h"
#include "stdlib.h"
#include "stdio.h"
#include <ctype.h>
void print_string(char *string){
    int i = 0;
    while(string[i] != '\0' ){
        printf("%c", string[i]);
        i++;
    }
}

void str_reverse(char string[]){
    int len = strlen(string);
    char *new_string = malloc(len + 1);
    int i = 0;
    for(int i = 0; i < len; i++){
        new_string[i] = string[len - 1 - i];
    }
    new_string[len] = '\0';

    print_string(new_string);
    printf("\n");

    free(new_string);
}
char *str_trim(char string[]){
    char *end;
    while(isspace((unsigned char)*string)){
        string++;
    }

    end = string + strlen(string) - 1;
    while(end > string && isspace((unsigned char)*end)) end--;

    *(end+1) = '\0';

    return string;
}
void str_to_int(char string[]){
    for(int i = 0; i < strlen(string); i++){
        if((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')){
            printf("%d ", (unsigned char)string[i]);
        }
    }
    printf("\n");
}