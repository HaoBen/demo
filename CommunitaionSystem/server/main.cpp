#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT 8887
#define QUEUE 20
#define BUFFER_SIZE 1024

int main() {
    int server_sock = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serv_sock_addr;
    serv_sock_addr.sin_family = AF_INET;
    serv_sock_addr.sin_port = htons(MYPORT);
    serv_sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server_sock,(struct sockaddr*)&serv_sock_addr,sizeof(sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if(listen(server_sock,QUEUE) == -1) {
        perror("listen");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    int conn = accept(server_sock,(struct sockaddr*)&client_addr,&length);

    if(conn<0) {
        perror("connect");
        exit(1);
    }

    while(1) {
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn,buffer,sizeof(buffer),0);
        if(strcmp(buffer,"exit\n") == 0) {
            break;
        }
        fputs(buffer,stdout);
        send(conn,buffer,len,0);
    }
    close(conn);
    close(server_sock);
    return 0;
}
