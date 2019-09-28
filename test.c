#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* a = "HTTP/1.1";
    char* b = strcasestr(a, "HTTP");
    // printf("%s", a);
    printf("%s\n", b);
}