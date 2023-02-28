/* fifo_client01.c */

#include "fifo_type.h"

int main(int argc, char *argv[])
{
	int	pipe_fd, sour_fd;
	int	count, bytes_sent, bytes_read;
	char	buffer[PIPE_BUF+1];

	if (access(NAMEDPIPE, F_OK) == -1) {	/* 不存在则创建 */
		mkfifo(NAMEDPIPE, 0777);
	}

	fprintf(stdout, "Process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(NAMEDPIPE, O_WRONLY);	/* 只写方式 */
	if (pipe_fd == -1)
		exit(EXIT_FAILURE);
	sour_fd = open(SOURTEXT, O_RDONLY);	/* 只读方式 */
	if (sour_fd == -1)
		exit(EXIT_FAILURE);
	fprintf(stdout, "Process %d result %d and %d\n", getpid(), pipe_fd, sour_fd);

	/* 读取数据文件并发送 */
	bytes_read = read(sour_fd, buffer, PIPE_BUF);
	buffer[bytes_read] = '\0';
	while (bytes_read > 0) {
		count = write(pipe_fd, buffer, bytes_read);
		bytes_sent += count;
		bytes_read = read(sour_fd, buffer, PIPE_BUF);
		buffer[bytes_read] = '\0';
	}

	close(pipe_fd); close(sour_fd);
	fprintf(stdout, "Process %d finished, %d bytes sent\n", getpid(), bytes_sent);


	return 0;
}

