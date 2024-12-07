#include <stdio.h>

int main(){
    int array[]={0,2,4,6,8,10,12};
    int *p;
    p=&array[2];
    printf("*p=%d\n",*p);
    printf("*++p=%d\n",*++p);
    printf("++*p=%d\n",++*p);
    printf("*p++=%d\n",*p++);
    printf("(*p)++=%d\n",(*p)++);
    printf("*p=%d\n",*p);
    printf("*--p=%d\n",*--p);
    printf("--*p=%d\n",--*p);
    printf("*p--=%d\n",*p--);
    printf("(*p)--=%d\n",(*p)--);
    printf("*p=%d\n",*p);
    return 0;
}