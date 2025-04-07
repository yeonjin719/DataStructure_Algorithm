#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 20

int read_line(char str[], int limit);
int main(){
    char buffer[BUFFER_SIZE];
    while (1) {
        printf("$ ");
        // gets(buffer); // line 단위로 입력받음
        // fgets(buffer, BUFFER_SIZE, stdin);
        // buffer[strlen(buffer)-1]='\0';
        read_line(buffer, BUFFER_SIZE);
        printf("%s:%d\n", buffer, strlen(buffer));
    }
    return 0;
}

int read_line( char str[], int limit){
    int ch, i = 0;
    while ((ch=getchar()) != '\n'){
        if (i<limit){
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}