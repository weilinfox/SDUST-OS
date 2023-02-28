/*filename mythread_posix3_semn.c：使用有名信号量对临界区加锁；
*请对比mythread_posix3_semu.c程序理解并掌握无名和有名信号量的差异
*usage: $ gcc -o mythread_posix3_semn mythread_posix3_semn.c -lpthread
*usage: $ ./mythread_posix3_semn 100000000
*wirtten by Fang Sheng from SDUST, Oct.10 2014
*tested under Ubuntu 14.04LTS
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#define  THREADNO 4
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
pthread_t thread[THREADNO];
int counter=0; //the shared variable among threads
int upper;
int thread_id[THREADNO];
sem_t *lock; /* 信号量lock用于对缓冲区的互斥操作 */

void *my_thread(void *args)
{	
	int thread_arg;
	int	i, temp;
	thread_arg = *(int *)args;
	printf ("I'm thread %d\n",thread_arg);
	sem_wait(lock); //信号量加锁
	for (i = 0; i < upper; i++) 
	{
		temp = counter;
		temp += 1;
		counter = temp;
	}
	sem_post(lock);//信号量解锁
	printf("thread %d :Is Main function waiting for me ?\n",thread_arg);
	pthread_exit(NULL);
	

}
void thread_create(void)
{
	int i,temp;
	memset(&thread, 0, sizeof(thread)); 
	
	/*create new threads*/
	for(i=0; i<THREADNO;i++)
	{		
		if((temp = pthread_create(&thread[i], NULL, my_thread, (void*)(thread_id+i))) != 0) 
			printf("Creating thread %d has failed!\n",i);
		else
			printf("Thread %d has been created! \n",i);	
	}
	
}
void thread_wait(void)
{
	/*waiting for the thread finished*/
	int i;
	for(i=0; i<THREADNO;i++)
	{	
		if(thread[i] !=0) 
		{ 
			pthread_join(thread[i],NULL);
			printf("Theread %d has exited! \n",i);
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	if (argc != 2) 
	{
		fprintf(stderr,"usage: mythread_posix3_semn integer_value\n");			
		return -1;
	}
	if (atoi(argv[1]) < 0) 
	{
		fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));		
		return -1;
	}
	upper = atoi(argv[1]);
	printf("I am main function, I am creating the threads! \n");
      for(i=0; i<THREADNO; i++)
    	    thread_id[i] = i;
	lock= sem_open("lock",O_CREAT,FILE_MODE,1);//打开有名信号量
	thread_create();
	printf("I am main function , I am waiting the threads finished! \n");
	thread_wait();	
	printf("counter = %d\n",counter);
	sem_close(lock);  //关闭有名信号量
	sem_unlink("lock");	//撤销有名信号量
	return 0;
}
