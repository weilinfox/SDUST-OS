#include <unistd.h>
#include <stdio.h>

int main( int argc, char *argv[], char *envp[] )
{
    char *newargv[] = {"ls", "-l", NULL};
    execve( "/bin/ls", newargv, envp );
    printf( "execve called!\n" );
    return 0;
}
