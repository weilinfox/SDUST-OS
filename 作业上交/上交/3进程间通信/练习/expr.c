/* expr.c */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define	BUFFER_SIZE	256
#define	WRITE_END	1
#define	READ_END	0

int main(int argc, char *argv[])
{
	char	write_msg[2][BUFFER_SIZE];
	char	read_msg[2][BUFFER_SIZE];
	pid_t	pid;
	int	fd[2][2];
	int	nums[]	=	{1, 2, 3, 4, 5};
	int	numlen;

	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1) {
		fprintf(stderr, "Pipe failed!\n");
		return 1;
	}

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed!\n");
		return 1;
	}

	numlen = sizeof(nums) / sizeof(int);

	if (pid > 0) {
		int	i;
		int	ans;
		close(fd[0][READ_END]);
		close(fd[1][WRITE_END]);
		
		for (i = 0; i < numlen; i++) {
			snprintf(write_msg[0], BUFFER_SIZE-1, " %d", nums[i]);
			fprintf(stdout, "Father write: %s\n", write_msg[0]);
			write(fd[0][WRITE_END], write_msg[0], strlen(write_msg[0])+1);
			read(fd[1][READ_END], read_msg[0], BUFFER_SIZE-1);
		}
		//wait(NULL);
		//sleep(1);

		//fscanf(fd[FATHER_END], "%d", &ans);
		read(fd[1][READ_END], read_msg[0], BUFFER_SIZE-1);
		fprintf(stdout, "Father read: %s\n", read_msg[0]);
		sscanf(read_msg[0], "%d", &ans);
		fprintf(stdout, "Father get ans: %d\n", ans);

		close(fd[0][READ_END]);
		close(fd[1][WRITE_END]);
	} else {
		int	sum	=	0;
		int	t;
		int	i;
		int	offset;
		char*	cp;

		close(fd[0][WRITE_END]);
		close(fd[1][READ_END]);
		//sleep(1);
		
		for (i = 0; i < numlen; i++) {
			read(fd[0][READ_END], read_msg[1], BUFFER_SIZE-1);
			//cp = read_msg[1];
			fprintf(stdout, "Child read %s\n", read_msg[1]);
			sscanf(read_msg[1], "%d", &t);
			write(fd[1][WRITE_END], "\n", 2);
			sum += t;
		}
		
		sleep(1);
		snprintf(write_msg[1], BUFFER_SIZE-1, " %d ", sum);
		fprintf(stdout, "Child write: %s\n", write_msg[1]);
		write(fd[1][WRITE_END], write_msg[1], strlen(write_msg[1])+1);
		//fprintf(stdout, "%d\n", sum);
		
		close(fd[1][WRITE_END]);
		close(fd[0][READ_END]);
	}


	return 0;
}



