#include <stdio.h>
#include <math.h>
#include <sys/time.h>

void testFun()
{
    unsigned int i, j;
    double y;
    for( i=0; i<10000; i++ )
    {
        for( j=0; j<10000; j++ )
        {
            y = sin((double)i);  //time-consuming operation
        }
    }
}

int main()
{
    struct timeval tpstart, tpend;
    float  timeused;
    
    gettimeofday( &tpstart, NULL ); //record the start timestamp
    testFun();
    gettimeofday( &tpend, NULL );   //record the end timestamp
    // compute the used time
    timeused = 1000000 * ( tpend.tv_sec-tpstart.tv_sec) + (tpend.tv_usec-tpstart.tv_usec);
    timeused /= 1000000;
    printf( "Used Time: %f\n", timeused );
    return 0;
}
