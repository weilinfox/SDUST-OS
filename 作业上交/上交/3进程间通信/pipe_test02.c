/* pipe_test02.c */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE	25
#define READ_END	0
#define WRITE_END	1

int main(int argc, char *argv[])
{
	char	write_msg[BUFFER_SIZE]	=	"Hello pipe";
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
		close(fd[READ_END]);	/* 关闭不使用的终端 */
		/* 向管道中写入数据 */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		close(fd[WRITE_END]);
		wait(NULL);
	} else {			/* 子进程 */
		close(0);		/* 关闭标准输入 */
		close(fd[WRITE_END]);	/* 关闭管道的写端 */
		dup(fd[READ_END]);	/* 将标准输入作为管道的读端 */
		close(fd[READ_END]);	/* 关闭旧的读端 */

		execlp("/usr/bin/od", "od", "-c", NULL);
	}

	return 0;
}

