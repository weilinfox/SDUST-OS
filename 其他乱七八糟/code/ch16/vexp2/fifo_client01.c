//基于fifo的客户端，把从文件SOURTXT中读取的数据，写入到管道NAMEDPIPE中，直到SOURTXT中的数据读取完毕

#include "comm1.h"
  
int main()  
{  
    int pipe_fd, sour_fd;  
    int count = 0;  
    int bytes_sent = 0;   
    int bytes_read = 0; 
    char buffer[PIPE_BUF + 1];  
  
    if(access(NAMEDPIPE, F_OK) == -1)  
    {  
        //管道文件不存在, 创建命名管道  
        if(mkfifo(NAMEDPIPE, 0666) != 0)  
        {  
            fprintf(stderr, "Could not create fifo %s\n", NAMEDPIPE);  
            exit(EXIT_FAILURE);  
        }  
    }  
  
    printf("Process %d opening FIFO O_WRONLY\n", getpid());  
    //以只写阻塞方式打开FIFO文件，以只读方式打开数据文件  
    pipe_fd = open(NAMEDPIPE, O_WRONLY);  
    sour_fd = open(SOURTXT, O_RDONLY);  
    if(pipe_fd == -1) 
	exit(EXIT_FAILURE);
    if(sour_fd == -1) 
	exit(EXIT_FAILURE);	
    printf("Process %d result %d\n", getpid(), pipe_fd);  
    //从目标文件读取数据     
    bytes_read = read(sour_fd, buffer, PIPE_BUF);
    buffer[bytes_read] = '\0';  
    while( bytes_read > 0)  
    {  

           //向FIFO文件写数据  
            count = write(pipe_fd, buffer, bytes_read);  
            if(count == -1)  
            {  
                fprintf(stderr, "Write error on pipe\n");  
                exit(EXIT_FAILURE);  
            }  
            //累加写的字节数，并继续读取数据  
            bytes_sent += count;
    	    bytes_read = read(sour_fd, buffer, PIPE_BUF);
	    buffer[bytes_read] = '\0';    
    } 
 
    close(pipe_fd);  
    close(sour_fd);    
    printf("Process %d finished, %d bytes sent\n", getpid(), bytes_sent); 
    exit(EXIT_SUCCESS);  
}  


