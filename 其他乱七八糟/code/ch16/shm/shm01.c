/*shm01.c  通过内存映射实现文件的读取、写入等。
       The  following  program  prints part of the file specified in its first
       command-line argument to standard output.  The range  of  bytes  to  be
       printed  is  specified  via  offset and length values in the second and
       third command-line arguments.  The program creates a memory mapping  of
       the  required  pages  of  the file and then uses write(2) to output the
       desired bytes.
编译命令： $ gcc -o shm01 shm01.c
使用例子： $ ./shm01 shm_usem02.c  0  100 
第一个命令行参数指明：要显示的文件名称；第二个、第三个参数指明显示开始位置和长度                     
*/

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int
main(int argc, char *argv[])
{
    char *addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length;
    ssize_t s;

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "%s file offset [length]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    offset = atoi(argv[2]);
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 4) {
        length = atoi(argv[3]);
        if (offset + length > sb.st_size)
            length = sb.st_size - offset;
                /* Can't display bytes past end of file */

    } else {    /* No length arg ==> display to end of file */
        length = sb.st_size - offset;
    }
    printf("the inputted offset is %d, and the length is %d\n", atoi(argv[2]),atoi(argv[3]));
    printf("the page size is %ld, the pa_offset is %ld, and the actual length is %ld\n\n", sysconf(_SC_PAGE_SIZE),  pa_offset, length + offset - pa_offset);

    addr = mmap(NULL, length + offset - pa_offset, PROT_READ,
                MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
    if (s != length) {
        if (s == -1)
            handle_error("write");

        fprintf(stderr, "partial write");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


