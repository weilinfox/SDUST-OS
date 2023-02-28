#include <stdio.h>
#include <time.h>

int main()
{
    time_t time_raw_format;
    time( &time_raw_format); // Get the current time
    printf( "Time is [%ld]\n", (long)time_raw_format );
    // Convert the integer time to the fixed-format string
    printf( "The current local time is: %s\n", ctime(&time_raw_format) );
    return 0;
}
