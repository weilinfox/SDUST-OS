/***
编译执行：
$gcc -o hello_linux hello_linux.c
$./hello_linux

**/
#include "stdio.h"
#define  LEN  5
int main(void)
{
    printf("Hello Linux+%d\n", LEN);
    return 0;
}
