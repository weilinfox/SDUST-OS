#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 4096
int main()
{
    int len;
    int pid;
    char buf[BUFSIZE];
    int fd = open("/proc/tasklist",O_RDONLY);

    if ( fd < 0 ) {
        perror( "/proc/tasklist" );
        exit(1);
    }

    len = read(fd, buf, BUFSIZE);
    if ( len < 0 ) {
        perror( "read" );
        exit(1);
    }
    printf("%s\n",buf);

    close(fd);

    return 0;
}


