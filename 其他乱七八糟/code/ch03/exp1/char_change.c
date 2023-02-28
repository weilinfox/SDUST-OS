/***编译及运行步骤如下：
$gcc -o char_change char_change.c
$./char_change
**/
#include <stdio.h>
int main(void)
{
/***大小写字母转换**/
    char first,second;
    printf("please input a character\n");	
    first=getchar(); //从键盘获得字符
    if(first>='A' && first<='Z'){
	second=first+32;
	printf("your character is %c, ""changed character is %c\n",first,second);
    }
    else if(first>='a' && first<='z') {
        second=first-32;
	printf("your character is %c, ""changed character is %c\n",first,second);
    }
    else{
       	printf("your input is not a character  \n"); 
    }  
}
