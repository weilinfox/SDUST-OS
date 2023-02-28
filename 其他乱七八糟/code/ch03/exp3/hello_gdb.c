/**
调试步骤：
$gcc -g -o hello_gdb hello_gdb.c
$gdb hello_gdb -q
进入gdb调试发现原因即可
***/

#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include <malloc.h>
void my_print(); //原样输出字符串
void my_print2();//逆序输出字符串
int
main (void){
  char hello_string[] = "Hello Linux";
  my_print(hello_string);
  my_print2(hello_string);
}
void my_print(char *string){
  printf ("the fisrt is %s\n", string);
}
void my_print2(char *string){
  char *string2;
  int size, i;
  size = strlen (string);
  string2 = (char *) malloc (size + 1);
  for (i = 0; i < size; i++)
  string2[size - i] = string[i];
  string2[size + 1] = '0';
  printf ("the second is $%s\n", string2);
  free(string2);
}

