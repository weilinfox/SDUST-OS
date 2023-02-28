/***
单步编译执行：
$gcc -o main1 main.c sub.c sum.c
$./main1

分步编译执行：
$ gcc -c main.c
$ gcc -c sum.c
$ gcc -c sub.c
$ gcc -o main2 main.o sub.o sum.o
$ ./main2
**/
#include <stdio.h>
#include "head.h"
int main(void){
int first=0,second=0;
printf("please input two integer ,not too large\n");
scanf("%d,%d",&first,&second);
printf("the sum of %d and %d  is %d\n",first,second,sum(first,second));
printf("the sub of %d and %d  is %d\n",first,second,sub(first,second));
}
