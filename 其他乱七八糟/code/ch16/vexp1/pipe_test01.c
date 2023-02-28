/**
 * Example program demonstrating UNIX pipes.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd[2];
	if (pipe(fd) == -1) { 	/* 创建管道 */
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	pid = fork();  /*创建子进程*/
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	if (pid > 0) {  /* 父进程*/
		close(fd[READ_END]); /* 关闭不使用的读端*/
		/*向管道中写入数据 */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1); 
		close(fd[WRITE_END]); /* 关闭管道的写端*/
		wait(NULL);
	}
	else { /* 子进程 */
		close(fd[WRITE_END]); /* 关闭不使用的写端*/
		/*从管道中读取数据 */
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("child read %s\n",read_msg);
		close(fd[READ_END]); /* 关闭管道的读端*/
	}
	return 0;
}

