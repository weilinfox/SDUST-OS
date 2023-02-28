//-----------------------------------------------------------------
//sockFileServer.c: A server using file-system socket.
//compile using: $ gcc -o sockFileServer sockFileServer.c
//execute using: $ ./sockFileServer
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
    unlink("server_socket");
    int server_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    /* 为套节字命名 */
    struct sockaddr_un server_address;
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    int server_len = sizeof(server_address);

    bind(server_sock, (struct sockaddr *)&server_address, server_len);

    /* 监听客户的连接请求（创建一个连接队列，等待客户的连接） */
    listen(server_sock, 5);

    /* 接受连接 */
    int client_sock, client_len;
    struct sockaddr_un client_address;
    int a,b,c;
    while(1) {
        printf("server waiting...\n");
        /* 接受一个连接 */
        client_len = sizeof(client_address);
        client_sock = accept(server_sock, (struct sockaddr *)&client_address, &client_len);
        /* 通过对client_sock套节字的读写操作与客户进行通信 */
        read(client_sock, &a, sizeof(int));
        read(client_sock, &b, sizeof(int));
        c=a+b;
        write(client_sock, &c, sizeof(int));
        close(client_sock);
    }
}

