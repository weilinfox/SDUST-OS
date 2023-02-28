/**
调试步骤：
$gcc -g -o hello_sample hello_sample.c
$gdb hello_smaple -q
进入gdb,观察程序执行过程
***/
#include <stdio.h>
int cnt=0;
void my_print();
int main(void)
{
	int i,j;
	for(i=1;i<=5;i++)
	{
		for(j=1;j<=5;j++)
			my_print(i,j);
	}
	return 0; 																
}
void  my_print(int a, int b){
	
	cnt++;	
	printf("本次操作外层循环为%d，内层循环为%d,总次数%d\n",a,b,cnt);
}
