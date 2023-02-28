#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#define BUFFER_SIZE 16
#define PRO_NO 30
#define OVER ( - 1)
#define PSLEEP 10000
#define CSLEEP 10000
#define PPNO 2
#define CPNO 2
pthread_mutex_t lock;
pthread_cond_t notempty;
pthread_cond_t notfull;

struct prodcons
{
	int buf[BUFFER_SIZE];
	int readpos, writepos;
};

struct prodcons buffer;


void init(struct prodcons *b)
{
	b->readpos = 0;
	b->writepos = 0;
}

void *producer(void *data)
{
	int n;
	for (n = 0; n <= PRO_NO; n++)
	{	
		pthread_mutex_lock(&lock);

		while ((buffer.writepos + 1) % BUFFER_SIZE == buffer.readpos)
		//if ((buffer.writepos + 1) % BUFFER_SIZE == buffer.readpos) //会产生虚假唤醒
		{	
			pthread_cond_wait(&notfull, &lock);
		}
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
		/* 等待缓冲区非空,应该用while判断，因为有可能发送虚假唤醒：期待的条件尚不成立的唤醒。*/
		while(buffer.writepos == buffer.readpos)
		//if(buffer.writepos == buffer.readpos) //会产生虚假唤醒
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
