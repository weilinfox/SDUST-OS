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

	/* create the pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused end of the pipe */
		close(fd[READ_END]);

		/* write to the pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* close the write end of the pipe */
		close(fd[WRITE_END]);
		wait(NULL);
	}
	else { /* child process */
		//使标准输入指向fd[READ_END]  
 		close(0);
		dup(fd[READ_END]);  
		//关闭fd[WRITE_END],fd[READ_END]，只剩下标准输入  
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		//启动新进程od  
		execlp("/usr/bin/od", "od", "-c", NULL);  
 		return 0;  

	}

	return 0;
}

