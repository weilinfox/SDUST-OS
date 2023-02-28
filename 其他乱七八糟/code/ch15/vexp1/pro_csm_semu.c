/*filename pro_csm_semu.c： 演示无名信号量解决生产者-消费者问题
* 无名信号量特点
* 注意其中信号量的使用： 两个狭义同步信号量+一个互斥信号量
* 注意分析狭义同步信号量的制约方向
*usage: $ gcc -o pro_csm_semu pro_csm_semu.c -lpthread
*usage: $ ./pro_csm_semu
*wirtten by Fang Sheng from SDUST, Oct.10 2014
*tested under Ubuntu 14.04LTS
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h>  
#define BUFFER_SIZE 16 // 缓冲区数量
#define PRO_NO 30 // PRODUCING NO
#define OVER ( - 1)
#define PSLEEP 10000  // 
#define CSLEEP 10000  // 
#define PPNO 2  // 
#define CPNO 2  // 
sem_t lock; /* 信号量lock用于对缓冲区的互斥操作 */
sem_t notempty; /* 缓冲区非空的信号量 */
sem_t notfull; /* 缓冲区未满的信号量 */

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
		 sem_wait(&notfull); 
		 sem_wait(&lock);
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
		sem_post(&notempty);
		sem_post(&lock);
	} 
	return NULL;
}

void *consumer(void *data)
{
	int d;
	while (1)
	{	
		/* 等待缓冲区非空*/
		 sem_wait(&notempty); 
		 sem_wait(&lock);
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
		sem_post(&notfull);
		sem_post(&lock);		
	}
	return NULL;
}

int main(void)
{
	pthread_t th_c, th_p;
	void *retval;
	int i;
	init(&buffer);
	//无名信号量初始化
	sem_init(&lock,0,1);
	sem_init(&notempty,0,0);
	sem_init(&notfull,0,BUFFER_SIZE);

	/* 创建生产者和消费者线程*/
	pthread_create(&th_c, NULL, producer, 0);
	pthread_create(&th_p, NULL, consumer, 0);
	/* 等待两个线程结束*/
	pthread_join(th_c, &retval);
	pthread_join(th_p, &retval);
	//销毁无名信号量	
	sem_destroy(&lock);
	sem_destroy(&notempty);
	sem_destroy(&notfull);
	return 0;
}
