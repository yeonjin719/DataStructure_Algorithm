#include <stdio.h>
#include <stdlib.h>

int main(){
    int *array = (int*)malloc(4*sizeof(int));
    /* 배열 array의 크기가 부족한 상황 발생*/
    int *tmp = (int *)malloc(8*sizeof(int));
    int i;
    for (i=0; i<4; i++){
        tmp[i] = array[i];
    }
    array = tmp;
}  