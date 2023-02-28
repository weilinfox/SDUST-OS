#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <limits.h>  
#include <string.h>  
#define SERVERFIFO "server_fifo" 
#define CLIENTFIFO "client_%d_fifo" 
#define Bufsize 512
 
struct data{
	pid_t client_pid;	//保存客户端进程的PID。
	char buf[Bufsize];
};
