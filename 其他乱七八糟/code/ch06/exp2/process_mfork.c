#include <unistd.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
    int i = 0;
    int root = 0;
    printf( "r\t i\t C/P\t ppid\t pid\n" );
    for( i=0; i<2; i++ )
    {
        if( fork()>0 )
        {
            printf( "%d\t %d\t parent\t %d\t %d\n", root, i, getppid(), getpid() );
            sleep(1);
        }
        else
        {
            root++;
            printf( "%d\t %d\t child\t %d\t %d\n", root, i, getppid(), getpid() );
        }
    }
    return 0;
}
