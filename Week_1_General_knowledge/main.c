#include "bstrutils.h"
#include "stdio.h"
int main(){
    char s1[] = "Le Duong Khanh Huy"; //for reverse
    printf("After reverse: ");
    str_reverse(s1);

    char s2[] = "  Le Duong Khanh Huy  ";// for replacing whitespace in head and tail
    printf("After replacing whitespace in head and tail: ");
    printf("%s", str_trim(s2));
    printf("\n");
    
    char s3[] = "Le Duong Khanh Huy"; //for converting string to integer
    printf("After converting char string to integer: ");
    str_to_int(s3);
    return 0;
}