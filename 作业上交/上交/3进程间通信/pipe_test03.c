/* pipe_test03.c */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE	25
#define READ_END	0
#define WRITE_END	1

int main(int argc, char *argv[])
{
	char	write_msg[BUFFER_SIZE];
	char	read_msg[BUFFER_SIZE];
	pid_t	pid;
	int	fd[2];

	if (pipe(fd) == -1) {		/* 创建管道 */
		fprintf(stderr, "Pipe failed!");
		return 1;
	}

	pid = fork();			/* 创建子进程 */
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	if (pid > 0) {			/* 父进程 */
		int	i;
		close(fd[READ_END]);	/* 关闭不使用的终端 */
		/* 向管道中写入数据 */
		for (i = 0; i < 5; i++) {
			snprintf(write_msg, BUFFER_SIZE, "Hello %d", i);
			write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
			sleep(1);
		}
		close(fd[WRITE_END]);
		wait(NULL);
	} else {			/* 子进程 */
		int	nstop	=	1;
		int	nread;
		close(fd[WRITE_END]);	/* 关闭管道的写端 */
		while (nstop) {
			nread = read(fd[READ_END], read_msg, BUFFER_SIZE);
			switch (nread) {
				case -1:
					if (errno == EAGAIN) {
						fprintf(stderr, "Pipe empty.\n");
						sleep(1);
					} else {
						fprintf(stderr, "Error no: %d", errno);
					}
					break;
				case 0:
					fprintf(stdout, "End of conversation.\n");
					nstop = 0;
					break;
				default:
					fprintf(stdout, "MSG: %s\n", read_msg);
					break;
			}
		}
		close(fd[READ_END]);	/* 关闭旧的读端 */
	}

	return 0;
}

