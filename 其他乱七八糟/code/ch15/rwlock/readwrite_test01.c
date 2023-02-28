/*
complie: gcc -o readwrite_test01 readwrite_test01.c -lpthread
创建读、写线程，读、写线程的数目随机分配；
读、写线程使用写锁、读锁来访问共享缓冲区；
写线程向共享缓冲区写入数据包括自己的线程编号，读线程从共享缓冲区读取数据；
实验中，读线程可以在缓冲区空的时候读；写线程也可以直接覆盖上一个写者写入的数据
*/
#include <stdio.h>
#define __USE_UNIX98
#include <pthread.h>
#include <stdlib.h>
#define WORK_SIZE 1024
#define THREADCOUNT 20
char buf[WORK_SIZE];
pthread_rwlock_t rwlock;

void *reader(void *pvoid)
{
   //int rand;
   //rand = random();
   //usleep(rand/RAND_MAX*10000);
   if(!pthread_rwlock_rdlock(&rwlock))  //获取读写锁的读锁
      printf("reader %d is waiting.\n",(int)pvoid);
   //usleep(10000);	
   printf("reader %d worked.\n",(int)pvoid);
   printf("the buffer is \"%s\" \n", buf);
   if(pthread_rwlock_unlock(&rwlock)) //释放读写锁的读锁
   {
	printf("reader %d unlock error!\n",(int)pvoid);       
   }
   return NULL;
}

void *writer(void *pvoid)
{   
   //int rand;
   //rand = random();
   //usleep(rand/RAND_MAX*10000);
   if(!pthread_rwlock_wrlock(&rwlock))//获取读写锁的写锁
      printf("writer %d is waiting.\n",(int)pvoid);
   //usleep(10000);
   sprintf(buf,"this is written by writer %d",(int)pvoid);	
   printf("writer %d worked.\n",(int)pvoid);
   if(pthread_rwlock_unlock(&rwlock)) //获取读写锁的写锁
   {
	printf("writer %d unlock error!\n",(int)pvoid);       
   }
   return NULL;
}

int main(void)
{
   pthread_t thread_id[THREADCOUNT];
   pthread_attr_t threadattr;
   int i, rand;
   int readcount =0, writecount=0;
   int halfmax = RAND_MAX/2;//最大随机值的一半
   
   if(pthread_rwlock_init(&rwlock,NULL))
   {
	printf("iniitializer rwlock error!\n");       
   }   	
   pthread_attr_init(&threadattr);   
   //pthread_attr_setdetachstate(&threadattr, PTHREAD_CREATE_DETACHED);   
   
   
   pthread_rwlock_rdlock(&rwlock);//获取读写锁的读锁；把线程创建放置在读锁的加锁、解锁之间，避免写线程先运行。
   //pthread_rwlock_wrlock(&rwlock); 如果把把线程创建放置在写锁的加锁、解锁之间，那么在主线程释放写锁之前，所有子线程均不能运行；
   for (i=0;i< THREADCOUNT ;i++)
   {
	rand = random();
	if(rand < halfmax)//小于该值，创建读线程； 保持读写线程数目分配的比例
	{
	   pthread_create(&thread_id[i],&threadattr,reader, (void*)readcount);
	   readcount++;
         }     
	else //大于该值，创建写线程
	{
	   pthread_create(&thread_id[i],&threadattr,writer, (void*)writecount);
	   writecount++;
         }		      	
   }
   printf("create readers %d and writers %d\n",readcount,writecount);
   pthread_rwlock_unlock(&rwlock);//获取读写锁的读锁
   for (i=0; i<THREADCOUNT;i++)
	pthread_join(thread_id[i], NULL);

   pthread_rwlock_destroy(&rwlock);
   pthread_exit(NULL);
   return 0;	  

}

