#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#define BUFFER_SIZE 16 // 缓冲区数量
#define PRO_NO 100 // PRODUCING NO
#define OVER ( - 1)
#define PSLEEP 10000  // 
#define CSLEEP 10000  // 
#define PPNO 2  // 
#define CPNO 2  // 
pthread_mutex_t lock; /* 互斥体lock 用于对缓冲区的互斥操作 */
pthread_cond_t notempty; /* 缓冲区非空的条件变量 */
pthread_cond_t notfull; /* 缓冲区未满的条件变量 */

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
		pthread_mutex_lock(&lock);
		/* 等待缓冲区未满*/
		while ((buffer.writepos + 1) % BUFFER_SIZE == buffer.readpos)
		{	
			pthread_cond_wait(&notfull, &lock);
		}
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
		pthread_cond_signal(&notempty);
		pthread_mutex_unlock(&lock);
	} 
	return NULL;
}

void *consumer(void *data)
{
	int d;
	while (1)
	{	
		pthread_mutex_lock(&lock);
		/* 等待缓冲区非空*/
		while(buffer.writepos == buffer.readpos)
		{
			pthread_cond_wait(&notempty, &lock);
		}
		/* 读数据,移动读指针*/
		d = buffer.buf[buffer.readpos];
		//usleep(CSLEEP);
		buffer.readpos++;
		if (buffer.readpos >= BUFFER_SIZE)
			buffer.readpos = 0;
		/* 设置缓冲区未满的条件变量*/
		pthread_cond_signal(&notfull);
		pthread_mutex_unlock(&lock);
		printf("--->%d \n", d);
		if (d == OVER)
			break;
		
	}
	return NULL;
}

int main(void)
{
	pthread_t th_c, th_p;
	void *retval;
	int i;
	init(&buffer);
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&notempty, NULL);
	pthread_cond_init(&notfull, NULL);
	/* 创建生产者和消费者线程*/
	pthread_create(&th_c, NULL, producer, 0);
	pthread_create(&th_p, NULL, consumer, 0);
	/* 等待两个线程结束*/
	pthread_join(th_c, &retval);
	pthread_join(th_p, &retval);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&notempty);
	pthread_cond_destroy(&notfull);
	return 0;
}
