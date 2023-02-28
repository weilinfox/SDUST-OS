//基于fifo的服务器端，把从管道NAMEDPIPE中获取的客户端发送来的数据，写入到DESTTXT中，直到管道中数据读取完毕
#include "comm1.h"
  
int main()  
{      
    int pipe_fd, dest_fd;  
    int count = 0;  
    int bytes_read = 0;  
    int bytes_write = 0;  
    char buffer[PIPE_BUF + 1];  

    //清空缓冲数组  
    memset(buffer, '\0', sizeof(buffer));    
    //以只读阻塞方式打开管道文件，注意与fifo_write01.c文件中的FIFO同名  
    pipe_fd = open(NAMEDPIPE, O_RDONLY);  
    if(pipe_fd == -1) 
	exit(EXIT_FAILURE);	
    printf("Process %d opening FIFO O_RDONLY\n", getpid());  
    //以只写方式创建保存数据的文件  
    dest_fd = open(DESTTXT, O_WRONLY|O_CREAT, 0644);  
    if(dest_fd == -1) 
	exit(EXIT_FAILURE);	
    printf("Process %d result %d\n",getpid(), pipe_fd);         

    do  
    {  
	 count = read(pipe_fd, buffer, PIPE_BUF);
         //把读取的FIFO中数据保存在文件DESTTXT中             
         bytes_write = write(dest_fd, buffer, count);  
         bytes_read += count;  
    }while(count >0) ;

	 
    close(pipe_fd);  
    close(dest_fd);   
    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);  
    exit(EXIT_SUCCESS);  
}  

