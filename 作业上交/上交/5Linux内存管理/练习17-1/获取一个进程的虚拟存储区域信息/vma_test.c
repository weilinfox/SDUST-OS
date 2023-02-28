#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 8192
int main() 
{ 
	int len; 
	int pid; 
	char buf[BUFSIZE];
	int fd;
	pid=fork(); 
	if(pid==0){
		fd = open("/proc/vma",O_RDONLY);
		if ( fd < 0 ) { perror( "/proc/vma" ); exit(1); }		
		printf("This is child pid %d\n",getpid());		 
		len = read(fd, buf, BUFSIZE);
		if ( len < 0 ) { perror( "read" ); exit(1); }
	        printf("%s\n",buf);fflush( stdout );
		close(fd);
		sleep(3);
	} 
	else if(pid>0){ 
		fd = open("/proc/vma",O_RDONLY);
		if ( fd < 0 ) { perror( "/proc/vma" ); exit(1); }
		printf("This is parent pid %d\n",getpid());
		len = read(fd, buf, BUFSIZE);
		if ( len < 0 ) { perror( "read" ); exit(1); }
	        printf("%s\n",buf);fflush( stdout );
		close(fd);
		sleep(3);
	}
	return 0; 

} 

