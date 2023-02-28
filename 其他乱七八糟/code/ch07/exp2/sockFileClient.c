//-----------------------------------------------------------------
//sockFileClient.c: A client using file-system socket.
//compile using: $ gcc -o sockFileClient sockFileClient.c
//execute using: $ ./sockFileClient
//programmer: Li Xujian 
//written on: Feb. 2015
//-----------------------------------------------------------------
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    /* 创建套节字 */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);

    /* 将该套节字连接到服务器套节字 */
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    int len = sizeof(address);
    int result = connect(sock, (struct sockaddr *)&address, len);
    if(result == -1) {
        perror("连接服务器失败");
        exit(1);
    }

    /* 通过该套节字读写数据 */
    int a=100,b=200,c=0;
    write(sock, &a, sizeof(int));
    write(sock, &b, sizeof(int));
    read(sock, &c, sizeof(int));
    printf("来自服务器的数据为： %d\n", c);

    /* 关闭套接字 */
    close(sock);
    exit(0);
}
