//-----------------------------------------------------------------
//sockNetServer.c: A server using network socket.
//compile using: $ gcc -o sockNetServer sockNetServer.c
//execute using: $ ./sockNetServer
//programmer: Li Xujian 
//written on: Feb. 2015
//-----------------------------------------------------------------
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    /* 创建套节字 */
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);

    /* 为套节字命名 */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr =inet_addr("127.0.0.1");  //或赋值为 htonl(INADDR_ANY)
    server_address.sin_port = htons(7000);
    int server_len = sizeof(server_address);

    bind(server_sock, (struct sockaddr *)&server_address, server_len);

    /* 监听客户的连接请求（创建一个连接队列，等待客户的连接） */
    listen(server_sock, 5);
    
    /* 接受连接 */
    int client_sock, client_len;
    struct sockaddr_in client_address;
    int a,b,c;
    while(1) {
        printf("server waiting\n");
        /* 接受一个连接（创建一个新套节字client_sockfd，用于与接受的这个客户进行通信） */
        client_len = sizeof(client_address);
        client_sock = accept(server_sock, (struct sockaddr *)&client_address, &client_len);

        /* 通过对client_sockfd套节字的读写操作与客户进行通信　*/
        read(client_sock, &a, sizeof(int));
        read(client_sock, &b, sizeof(int));
        c=a+b;
        write(client_sock, &c, sizeof(int));
        close(client_sock);
    }
}

