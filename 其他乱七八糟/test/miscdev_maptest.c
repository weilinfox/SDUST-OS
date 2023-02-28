/*miscdev_maptest.c
本程序用于测试开发的miscdev_map内核模块，必须在miscdev_map内核模块编译、添加并修改设备权限后运行。。
程序编译命令： $ gcc -o miscdev_maptest miscdev_maptest.c
*/

#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <linux/fb.h>  
#include <sys/mman.h>  
#include <sys/ioctl.h>   
  
#define PAGE_SIZE 4096   
  
int main(int argc , char *argv[])  
{  
    int fd1;  
    unsigned char *p_map;  

    //打开设备  
    fd1 = open("/dev/mymap",O_RDWR);  
    if(fd1 < 0)  
    {  
        printf("open fail\n");  
        exit(1);  
    }  
  
    //内存映射  
    p_map = (unsigned char *)mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,fd1, 0);  
    if(p_map == MAP_FAILED)  
    {  
        printf("mmap fail\n");  
        goto out;  
    }  
  
    //打印映射后的内存中的内容      
    printf("%s\n",p_map);  
    //sleep(7);	
  
out:  
    munmap(p_map, PAGE_SIZE);  
    return 0;  
}  

