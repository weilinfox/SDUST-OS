/*shm_usem02.c
*父、子进程都对一个名为count的全局变量进行加1操作
* 通过共享内存实现了信号量以及信号量保护对象在父子进程间的共享
*编译命令： $ gcc -o shm_usem02 shm_usem02.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

#define   SEM_NAME         "sem"
#define   FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define   COUNTNO 20
//共享内存结构
struct data
{
    sem_t sem;       //信号量
    int count;         //计数器
}data;

int main(int argc,char* argv[])
{
    int     fd,i,nloop;
    struct  data *pdata;
    if(argc == 2)
    {
	nloop = atoi(argv[1]);
    }
    else 
	nloop = COUNTNO;
    fd = open("shm_test01",O_RDWR|O_CREAT,FILE_MODE);
    write(fd,&data,sizeof(struct data));
    pdata = mmap(NULL,sizeof(struct data),PROT_READ| PROT_WRITE,MAP_SHARED,fd,0);
    if(pdata == MAP_FAILED)
    {
        error("mmap() error");
        exit(1);
    }
    close(fd);
    sem_init(&pdata->sem,1,1);
    setbuf(stdout,NULL);
    if(fork() == 0)
    {
        for(i = 0;i<nloop;++i)
        {
            sem_wait(&pdata->sem);
	    pdata->count++;	
            //printf("child: %d\n",pdata->count);
            sem_post(&pdata->sem);
        }
        exit(0);
    }
    for(i = 0;i<nloop;++i)
    {
        sem_wait(&pdata->sem);
	pdata->count++;	
        //printf("child: %d\n",pdata->count);
        sem_post(&pdata->sem);
    }    
    printf("the final result of count is %d\n",pdata->count);
    wait(NULL);
    printf("the final result of count is %d\n",pdata->count);
    exit(0);
}

