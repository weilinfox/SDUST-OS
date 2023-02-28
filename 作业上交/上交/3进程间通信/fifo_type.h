/* fifo_type.h */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define	NAMEDPIPE	"test_fifo"
#define	DESTTEXT	"dest.txt"
#define	SOURTEXT	"sour.txt"

