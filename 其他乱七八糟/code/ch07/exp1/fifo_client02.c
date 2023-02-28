#include "comm2.h"
  
int main()  
{  
    int server_pipe_fd, client_pipe_fd;  
    int count = 0;  
    int bytes_sent = 0;   
    int bytes_read = 0; 
    struct data mydata;
    char client[32];  
  
    printf("Process %d opening FIFO O_WRONLY\n", getpid());  
    //以只写阻塞方式打开SERVERFIFO文件  
    server_pipe_fd = open(SERVERFIFO, O_WRONLY);  
    if(server_pipe_fd == -1) 
	exit(EXIT_FAILURE);

    //创建命名管道 CLIENTFIFO
    mydata.client_pid = getpid();
    sprintf (client,CLIENTFIFO ,mydata.client_pid);
    if(mkfifo(client ,0777) == -1){
	fprintf(stderr , "Sorry ,can't make %s \n",client);
	exit(EXIT_FAILURE);
    } 
  
    sprintf(mydata.buf,"this is from client %d", mydata.client_pid);  
    write(server_pipe_fd , &mydata , sizeof(mydata));
    
    //打开回送管道，等待接受从服务器返回的数据。	
    client_pipe_fd = open(client,O_RDONLY);
	if(client_pipe_fd != -1){	
		count = read( client_pipe_fd  , &mydata , sizeof(mydata));			
		if( count > 0){
			printf("received : %s\n",mydata.buf);
		}
		close(client_pipe_fd);
	}
    close(server_pipe_fd);  
    close(client_pipe_fd);    
    unlink(client);    
    exit(EXIT_SUCCESS);  
}  


