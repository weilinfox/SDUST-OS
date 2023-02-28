/* fifo_server01.c */
#include "fifo_type.h"

int main(int argc, char *argv[])
{
	int	pipe_fd, dest_fd;
	int	count, bytes_read, bytes_write;
	char	buffer[PIPE_BUF+1];

	memset(buffer, '\0', sizeof(buffer));
	
	pipe_fd = open(NAMEDPIPE, O_RDONLY);			/* 只读阻塞方式 */
	if (pipe_fd == -1)
		exit(EXIT_FAILURE);
	fprintf(stdout, "Process %d opening FIFO O_RDONLY.\n", pipe_fd);

	dest_fd = open(DESTTEXT, O_WRONLY|O_CREAT, 0644);	/* 只写方式 */
	if (dest_fd == -1)
		exit(EXIT_FAILURE);
	fprintf(stdout, "Process %d result %d\n", getpid(), pipe_fd);
	
	bytes_read = 0;
	do {
		count = read(pipe_fd, buffer, PIPE_BUF);
		/* 保存 FIFO 中读取的数据保存在 dest_fd */
		bytes_write = write(dest_fd, buffer, count);
		bytes_read += count;
	} while (count > 0);

	close(pipe_fd); close(dest_fd);
	fprintf(stdout, "Process %d finished, %d bytes read.\n", getpid(), bytes_read);

	return 0;
}



