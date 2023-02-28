/*filename fork_semu2.c 
* 本程序用于演示：父子进程之间使用无名信号量时的错误方法：
* sem_init把第二个参数置为1，并不能保证父子进程之间使用的是同一个信号量。
* 测试父子进程各有一个sem_id的方法是：把行A和行B注释掉，观察实验结果
*usage: $ gcc -o fork_semu2 fork_semu2.c -lpthread
*usage: $ ./fork_semu2
*wirtten by Fang Sheng from SDUST, Oct.10 2014
*tested under Ubuntu 14.04LTS
*/
#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
#include <semaphore.h>  

int main(void)  
{  char buf[128];
    sem_t sem_id;  
    int val;
    sem_init(&sem_id,1,1);  //第二个参数为1    
    if(fork()==0){  
        while(1){  
        	sem_wait(&sem_id);  //行A,此行注释掉、实现两个进程狭义同步
	        sleep(2);
		sem_getvalue(&sem_id,&val);		
		sprintf(buf,"this is child,the sem value is %d",val);  
        	printf("%s\n",buf);  	
	        sem_post(&sem_id);  		         		
        }  
    }    
     while(1){  
		sem_wait(&sem_id);  
		sem_getvalue(&sem_id,&val);		
		sprintf(buf,"this is fahter,the sem value is %d",val);  
        	printf("%s\n",buf);  
	        sleep(2);  
        	sem_post(&sem_id);  //行B,此行注释掉、实现两个进程狭义同步
    }    
    return 0;  
}  




























