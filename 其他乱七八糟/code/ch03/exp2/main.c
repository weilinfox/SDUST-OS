/***
单步编译执行：
$gcc -o main main.c hello_fc.c
$./main

分步编译执行：
$ gcc -c main.c
$ gcc -c hello_fc.c
$ gcc -o main main.o hello_fc.o
$ ./main
**/
#include "hello.h"
int main(void)
{
    hello("Linux");
    return 0;
}
