#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
pthread_t thread;
int counter=0;
int upper;

// 线程函数，功能是对counter数值进行累加；
void *my_thread()
{
	int	i, temp;
	printf ("I'm thread 1\n");
	for (i = 0; i < upper; i++)
	{
		temp = counter;
		temp += 1;
		counter = temp;
	}
	printf("thread1 :Is Main function waiting for me ?\n");
	pthread_exit(NULL);
}

void thread_create()
{
	int temp;
	memset(&thread, 0, sizeof(thread));

	if((temp = pthread_create(&thread, NULL, my_thread, NULL)) != 0)
		printf("Creating thread 1 has failed!\n");
	else
		printf("Thread 1 has been created! \n");
}

void thread_wait(void)
{
	if(thread !=0) 
	{
        //等待线程退出
		pthread_join(thread,NULL);
		printf("Theread 1 has exited! \n");
	}	
}

int main(int argc, char *argv[])
{
	if (argc != 2) 
	{
		fprintf(stderr,"usage: mythrd-posix1 integer_value\n");			
		return -1;
	}
	if (atoi(argv[1]) < 0) 
	{
		fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));		
		return -1;
	}
	upper = atoi(argv[1]);		
	printf("I am main function, I am creating the threads! \n");
	thread_create();
	printf("I am main function , I am waiting the threads finished! \n");
	thread_wait();
	printf("counter = %d\n",counter);
	return 0;
}
