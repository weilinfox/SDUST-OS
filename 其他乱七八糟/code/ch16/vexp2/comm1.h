#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <limits.h>  
#include <string.h>  
#define NAMEDPIPE "my_fifo" 
#define DESTTXT  "dest.txt"
#define SOURTXT  "data.txt"
