/*readwrite_test02.c：
 *complie: gcc -o readwrite_test02 readwrite_test02.c -lpthread
 *使用读写锁实现四个线程读写一段程序的实例，共创建了四个新的线程，其中两个线程用来读取
 *数据，另外两个线程用来写入数据。在任意时刻，如果有一个线程在写数据，将阻塞所有其他线
 *程的任何操作.所以原则上，写线程的休眠时间要长于读线程，否则读线程总是会被阻塞
 * */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>

#define WORK_SIZE 1024
#define THREAD_READNO 2
#define THREAD_WRITENO 2

int thread_read[THREAD_READNO], thread_write[THREAD_WRITENO];
pthread_t threadt_read[THREAD_READNO], threadt_write[THREAD_WRITENO];
static pthread_rwlock_t rwlock;
char work_area[WORK_SIZE];
int time_to_exit;
void *thread_readp(void *arg);//读线程
void *thread_writep(void *arg);//写线程
int randsleep();

int main(int argc, char *argv[])
{
	int retval,i;	
	void *thread_result;

	retval = pthread_rwlock_init(&rwlock, NULL);
	if (retval != 0) 
	{
		perror("rwlock initialization failed\n");
		exit(EXIT_FAILURE);
	}
	for (i=0; i<THREAD_READNO;i++)
	{	
		thread_read[i] = i;
		retval = pthread_create(&threadt_read[i], NULL, thread_readp, thread_read+i);//创建一个新线程
		if (retval != 0) 
		{
			perror("thread create failed\n");
			exit(EXIT_FAILURE);
		}
	}
	for (i=0; i<THREAD_WRITENO;i++)
	{
		thread_write[i] = i;
		retval = pthread_create(&threadt_write[i], NULL, thread_writep, thread_write+i);//创建一个新线程
		if (retval != 0) 
		{
			perror("thread create failed\n");
			exit(EXIT_FAILURE);
		}
	}
	for (i=0; i<THREAD_READNO;i++)
	{
		retval = pthread_join(threadt_read[i], &thread_result);
		if (retval != 0) 
		{
			perror("thread join failed\n");
			exit(EXIT_FAILURE);
		}
	}
	for (i=0; i<THREAD_WRITENO;i++)
	{
		retval = pthread_join(threadt_write[i], &thread_result);
		if (retval != 0) 
		{
			perror("thread join failed\n");
			exit(EXIT_FAILURE);
		}
	}	
	pthread_rwlock_destroy(&rwlock); //销毁读写锁
	exit(EXIT_FAILURE);
}

void *thread_readp(void *arg)
{
	int thread_arg;
	thread_arg = *(int *)arg;
	printf("read thread %d try to read\n",thread_arg );

	pthread_rwlock_rdlock(&rwlock);//获取读锁
	while (strncmp("end", work_area, 3) != 0) 
	{
		printf("this is thread read %d\n",thread_arg );
		printf("the characters is %s", work_area);
		pthread_rwlock_unlock(&rwlock);
		//usleep(randsleep());
		sleep(1);
		pthread_rwlock_rdlock(&rwlock);
		while (work_area[0] == '\0') 
		{
			pthread_rwlock_unlock(&rwlock);
			//usleep(randsleep());
			sleep((thread_arg+1)*2);//根据线程编号来确定休眠时间
			pthread_rwlock_rdlock(&rwlock);
		}
	}
	printf("this is thread read %d will end\n",thread_arg );
	pthread_rwlock_unlock(&rwlock);
	time_to_exit = 1;
	pthread_exit(0);
}


void *thread_writep(void *arg)
{
	int thread_arg;
	thread_arg = *(int *)arg;
	printf("write thread %d try to write\n",thread_arg );

	while (!time_to_exit) 
	{
		pthread_rwlock_wrlock(&rwlock);
		printf("this is write thread %d\n. Input some text. Enter 'end' to finish\n",thread_arg );
		fgets(work_area, WORK_SIZE, stdin);
		pthread_rwlock_unlock(&rwlock);
		//usleep(randsleep());
		sleep((thread_arg+1)*4);//根据线程编号来确定休眠时间,时间是读线程的两倍或更多
	}
	pthread_rwlock_unlock(&rwlock);
	pthread_exit(0);
}

//未被使用
int randsleep()
{
   int rand,val;
   rand = random();
   val = rand/RAND_MAX*10000000000000;
}

