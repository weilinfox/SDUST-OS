#include <unistd.h>
#include <stdio.h>
#include "stdlib.h"
#include <fcntl.h>
#include <errno.h>
#define MSGSIZE 64
int parent(int *);
int child(int *);
char *msg1="hello fs";
char *msg2="Goodbye!";

main()
{
    pid_t pid;	
     int fd[2],i;
     if(pipe(fd)==-1)   
		error("pipe call");
     //if(fcntl(fd[0],F_SETFL, O_NONBLOCK)==-1  //����Ϊ������ģʽ
     //    	error("fcntl call");
     //for(i=1;i<3;i++) {	
	pid = fork();	
	switch(pid)
	{
	   case -1: error("fork call");
           case 0: child(fd);
           default: parent(fd);
	}
     //}
}

int parent(int *p)
{
    int nread;  
    char buf[MSGSIZE];  
    close(p[1]);
    for(;;)
    {   
	nread=read(p[0],buf,MSGSIZE);//���ݶ�ȡ����ȷ����������
	switch(nread)
	{
	         case -1:  
			if(errno==EAGAIN) //������ģʽ�²Ż��еķ���ֵ
		        { 
				printf("pipe empty\n"); 
				sleep(1); 
				break; 
			}
                       else 
				error("read call");
         	 case 0:  
			printf("End of conversation\n");
	                exit(0);			
        	 default: 
			printf("MSG=%s\n",buf);
			if (strcmp(buf, msg2) ==0)
			{
				printf("the parent %d will exit\n",getpid());				
			}
		
	}
   }
}  
int child(int *p)
{
       int count;
       close(p[0]);
       for(count=0;count<3;count++)
       {
              write(p[1],msg1,MSGSIZE);
              sleep(2);
        }
        write(p[1],msg2,MSGSIZE);
	printf("Child %d will exit!\n",getpid());
        exit(0);
}

