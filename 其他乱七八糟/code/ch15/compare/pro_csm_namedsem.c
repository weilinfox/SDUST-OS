#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <errno.h>
//创建模式权限
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BUFFER_SIZE 16 // 缓冲区数量
#define PRO_NO 100 // PRODUCING NO
#define OVER ( - 1)
#define PSLEEP 10000  // 
#define CSLEEP 10000  // 
#define PPNO 2  // 
#define CPNO 2  // 
#define SEM_MUTEX   "lock"  /* 信号量lock用于对缓冲区的互斥操作 */
#define SEM_NEMPTY  "notempty" /* 缓冲区非空的信号量 */
#define SEM_NFULL   "notfull" /* 缓冲区未满的信号量 */
sem_t *lock; /* 信号量lock用于对缓冲区的互斥操作 */
sem_t *notempty; /* 缓冲区非空的信号量 */
sem_t *notfull; /* 缓冲区未满的信号量 */ 

struct prodcons
{// 缓冲区相关数据结构
	int buf[BUFFER_SIZE]; /* 实际数据存放的数组*/
	int readpos, writepos; /* 读写指针*/
};

struct prodcons buffer;

/* 初始化缓冲区结构 */
void init(struct prodcons *b)
{
	b->readpos = 0;
	b->writepos = 0;
}

/* 测试:生产者线程将0 到 PRO_NO的整数送入缓冲区,消费者线
程从缓冲区中获取整数,两者都打印信息*/

void *producer(void *data)
{
	int n;
	for (n = 0; n <= PRO_NO; n++)
	{	
		 sem_wait(notfull); 
		 sem_wait(lock);
		/* 写数据,并移动指针 */
		if (n < PRO_NO)
		{
			buffer.buf[buffer.writepos] = n;
			printf("%d --->\n", n);
			usleep(PSLEEP);
		}
		else
		{
			buffer.buf[buffer.writepos] = OVER;			
			printf("%d --->\n", OVER);
		}
		buffer.writepos++;
		if (buffer.writepos >= BUFFER_SIZE)
			buffer.writepos = 0;
		/* 设置缓冲区非空的条件变量*/
		sem_post(notempty);
		sem_post(lock);
	} 
	return NULL;
}

void *consumer(void *data)
{
	int d;
	while (1)
	{	
		/* 等待缓冲区非空*/
		 sem_wait(notempty); 
		 sem_wait(lock);
		/* 读数据,移动读指针*/
		d = buffer.buf[buffer.readpos];
		//usleep(CSLEEP);
		buffer.readpos++;
		if (buffer.readpos >= BUFFER_SIZE)
			buffer.readpos = 0;
		printf("--->%d \n", d);
		if (d == OVER)
			break;
		/* 设置缓冲区未满的条件变量*/
		sem_post(notfull);
		sem_post(lock);		
	}
	return NULL;
}

int main(void)
{
	pthread_t th_c, th_p;
	void *retval;
	int i;
	init(&buffer);
       //创建NAMED信号量
	if((lock = sem_open(SEM_MUTEX,O_CREAT,FILE_MODE,1)) == SEM_FAILED)
	{
	      perror("sem_open() error");
	      exit(-1);
	}    
	if((notempty =  sem_open(SEM_NEMPTY,O_CREAT,FILE_MODE,0)) == SEM_FAILED)
	{
	    perror("sem_open() error");
	    exit(-1);
	}
	if((notfull = sem_open(SEM_NFULL,O_CREAT,FILE_MODE,BUFFER_SIZE)) == SEM_FAILED)
	{
	    perror("sem_open() error");
	    exit(-1);
	}

	/* 创建生产者和消费者线程*/
	pthread_create(&th_c, NULL, producer, 0);
	pthread_create(&th_p, NULL, consumer, 0);
	/* 等待两个线程结束*/
	pthread_join(th_c, &retval);
	pthread_join(th_p, &retval);
	sem_close(lock);
	sem_close(notfull);
	sem_close(notempty);	
	sem_unlink(SEM_MUTEX);
	sem_unlink(SEM_NEMPTY);
	sem_unlink(SEM_NFULL);
	return 0;
}
