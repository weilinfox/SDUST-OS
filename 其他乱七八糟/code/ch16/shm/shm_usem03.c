/*shm_usem03.c
*ʹ�������ڴ�ӳ�䷽������ʵ��һ�������ź������ڴ�ӳ��
*������� $ gcc -o shm_usem03 shm_usem03.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#define COUNTNO 5
sem_t sem;
sem_t *psem = NULL;
int main(int argc, char *argv[])
{
    int pid,i;
    int val;

    psem = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);        
    if (psem == NULL)
    {
        printf("Share memory failed!\n");
        return -1;
    }   
    if (sem_init(psem, 1, 1) == -1)
    {
        printf("Init unamed sem failed!\n");
        return -1;
    }
    sem_getvalue(psem,&val);		
    printf("this is the main function the psem value is %d\n",val); 

    pid = fork();
    if(pid==0){  
        for (i=1;i<COUNTNO;i++) 
        {    
        	sem_wait(psem);  
	      	sem_getvalue(psem,&val);		
        	printf("this is child,the sem value is %d\n",val);	        	
	        sem_post(psem);  		
	        usleep(1000); 
        }  
    } 
    else { 
        for (i=1;i<COUNTNO;i++) 
	{	
	    sem_wait(psem);  
	    sem_getvalue(psem,&val);		
       	    printf("this is fahter,the sem value is %d\n",val);  	    
	    sem_post(psem);  
   	    usleep(3000);  
	}
    }	
    sem_destroy(psem);
    return 0;
}
