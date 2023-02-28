//pipe_test04.c
//本程序用于诠释同步异步、阻塞非阻塞概念
//使用同步非阻塞,关键在于两点：
// 1）select函数
// 2）管道的操作符集合设置操作
//编译命令： $ gcc -o pipe_test04 pipe_test04.c
#include <unistd.h>
#include <stdio.h>
#include "stdlib.h"
#include <sys/time.h>
#include <sys/wait.h>
#define MSGSIZE 64
#define THREADNO 2
char *msg1="hello this msg is from child %d";
char *msg2="bye!!,this msg is from child %d";
void parent(int p[][2] );
int child(int *p);


main()
{
     int fd[THREADNO][2];    
     int i;
     for(i=0;i<THREADNO;i++)
     {    
	if(pipe(fd[i])==-1)  
	    error("pipe call");
          switch(fork())
          {   
		case -1: error("fork call");
                case 0:  child(fd[i]);
	}
     }
      parent(fd);
      exit(0);
}

void parent(int p[][2])
{
     char buf[MSGSIZE],ch;
     fd_set set,master;
     int i;
     for(i=0;i<THREADNO;i++)
           close(p[i][1]);
     FD_ZERO(&master);
     FD_SET(0,&master);
     for(i=0;i<THREADNO;i++)
           FD_SET(p[i][0],&master);
    
     while(1)
     {  
	set=master;
	select(p[THREADNO][0]+1,&set,NULL,NULL,NULL);	
	if(FD_ISSET(0,&set))
   	{  
	   printf("From standard input…");
           read(0,&ch,1); 
	   printf("%c\n",ch);   
	}
        for(i=0;i<THREADNO;i++)
    	{ 
	   if(FD_ISSET(p[i][0],&set))
	   {  
		if(read(p[i][0],buf,MSGSIZE)>0)
   	        {  
			printf("Message from child %d\n",i); 
			printf("MSG=%s\n",buf);   
		}  
	    }
        }
        if(waitpid(-1,NULL,WNOHANG)==-1) 
	  return;
     }
}
int child(int *p)
{
      int count;
      char buf[MSGSIZE];	
      close(p[0]);
      for(count=0;count<2;count++)
      {
	     sprintf (buf,msg1,getpid());
             write(p[1],buf,MSGSIZE);
             //usleep(getpid()%4);
	     sleep(2);	
       }
       sprintf (buf,msg2,getpid());
       write(p[1],buf,MSGSIZE);
       exit(0);
}

