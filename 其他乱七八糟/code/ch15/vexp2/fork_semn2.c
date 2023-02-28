/*filename fork_semn2.c：*本程序演示了有名信号量用于父子进程间的互斥
*usage: $ gcc -o fork_semn2 fork_semn2.c -lpthread
*tested under Ubuntu 14.04LTS
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <errno.h>
//创建模式权限
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SEM_FORK   "fork"  /* 信号量fork */

int main(int argc,char **argv)  
{  
    sem_t *sem;  
    int val,i;
    
    
    //if((sem = sem_open(SEM_FORK,O_CREAT,FILE_MODE,0)) == SEM_FAILED) //用于同步
    if((sem = sem_open(SEM_FORK,O_CREAT,FILE_MODE,1)) == SEM_FAILED) //用于互斥
    {
	      printf("sem_open %s Error\n",argv[0]);
	      exit(-1);
    }
    	  

    if(fork()==0){  
       for (i=1;i<5;i++) 
       {
	       	sem_wait(sem);  
	        sleep(1);
        	printf("this is child\n");  	
	        sem_post(sem);  		
        }
	sem_close(sem);  
    }	  
   else 
   {
   	 for (i=1;i<5;i++) 
   	 {
	    sem_wait(sem);  
	    sleep(1);
	    printf("this is father\n");  	      
	    sem_post(sem);  	    	
   	 }
	sem_close(sem);  	
    }
    sem_unlink(SEM_FORK); 	
    return 0;  
}  

