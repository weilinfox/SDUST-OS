#include "comm2.h"
//服务器处理函数---字符串翻转
void reverse(char str[]){
	int len = strlen (str);
	char tmpc;
	char *h,*t;	
	h = str; t = str + (len-1); 
	while(h < t){	
		tmpc = *h;
		*h = *t;
		*t = tmpc;
 
		h++;
		t--;
	}	
}
 
int main(){
	int server_pipe_fd, client_pipe_fd;
	struct data my_data;
	int count;
	char client[32]; 
	char *char_ptr;
 
	//创建server管道。
	mkfifo(SERVERFIFO,0666);
        while(1) {
		//打开服务器端口，等待读取。此时如果客户端还未写入数据服务器端会被阻塞。
		server_pipe_fd = open(SERVERFIFO , O_RDONLY);
		if( server_pipe_fd == -1 ){
			fprintf( stderr , "Server fifo failure\n" );
			exit(EXIT_FAILURE);
		}
		//从管道中读取数据。	
		count = read ( server_pipe_fd , &my_data , sizeof(my_data));
		if(count > 0){
			//将字符串翻转.	
			reverse ( my_data.buf );	
			//将客户端的pid号加入回送管道文件名中.	
			sprintf ( client, CLIENTFIFO , my_data.client_pid);
			//打开回送管道。	
			client_pipe_fd = open ( client , O_WRONLY );	
			if(client_pipe_fd != -1  ){
				//向管道中写入返回的数据.
				write ( client_pipe_fd , &my_data, sizeof(my_data));	
				close ( client_pipe_fd );
			}
		}	
		close(server_pipe_fd);	
         }	
	unlink(SERVERFIFO); 
	exit(EXIT_SUCCESS);
}

