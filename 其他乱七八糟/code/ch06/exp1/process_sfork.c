#include <unistd.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
    pid_t pid;
    int var = 0;
    pid = fork();
    if( pid<0 )
    {
        printf( "Error in fork!\n" );
    }
    else if( pid==0 )
    {
        printf( "This is the child process, pid is %d.\n", getpid() );
        var = 100;
    }
    else
    {
        printf( "This is the parent process, pid is %d.\n", getpid() );
        var = 50;
    }
    printf( "var is %d.\n", var );
    return 0;
}
