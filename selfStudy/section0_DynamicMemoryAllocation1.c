#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p;
    p = (int *)malloc(40);
    if (p==NULL){
        /* 동적 메모리 할당이 실패 */
        /* 적절한 조치를 취한다 */
        return 0;
    }
    p[0] = 12;
    p[1] = 24;
    *(p+2) = 36;
    return 0;
}  