#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    setvbuf(stdout,_IONBF,0,0);
    printf("Give me a string to echo back.\n");
    char str[20];
    fgets(str, 20, stdin);
    printf(str);
    exit(0);
}
