#include "system.h"
#include <iostream>
#include <cstring>

using namespace std;

System* System::singleton = nullptr;

System* System::getSystemHandler() {
    if(singleton == nullptr) {
        singleton = new System();
    }
    return singleton;
}

int System::open_listenfd(int port,int r_limit) {
    int listenfd,optval = 1;

    /* 服务器地址信息结构体 */
    struct sockaddr_in serveraddr;

    /* 创建一个socket描述符 */
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("create socket error");
        exit(1);
    }

    /* 消除绑定时的 "Address already in use" 错误 */
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,static_cast<const void *>(&optval), sizeof(int)) < 0) {
        perror("set socket option error");
        exit(1);
    }

    bzero(static_cast<void*>(&serveraddr),sizeof(serveraddr));
    /* IP地址协议簇设为IPV4 */
    serveraddr.sin_family = AF_INET;
    /* IP地址设为该该主机上的任意IP,htonl转换主机字节序为网络字节序 */
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* 端口设置为port htons转换主机字节序为网络字节序 */
    serveraddr.sin_port = htons(static_cast<unsigned short>(port));
    /* 绑定socket描述符到该地址 */
    if(bind(listenfd,reinterpret_cast<const struct sockaddr *>(&serveraddr),sizeof(serveraddr)) < 0) {
        perror("bind socket error");
        exit(1);
    }

    /* 开始监听打开的socket */
    if(listen(listenfd,r_limit) < 0) {
        perror("listen error");
        exit(1);
    }

    return listenfd;
}

int System::accept_fd(int _listenfd, struct sockaddr_in *clientaddr) {
    socklen_t len = sizeof (struct sockaddr);

    int clientfd = accept(_listenfd,reinterpret_cast<struct sockaddr*>(clientaddr),&len);
    if(clientfd < 0) {
        perror("accept error");
        return -1;
    }
    return clientfd;
}

long System::read_fd(int fd,void *buf,size_t nb) {
    long rbs = read(fd,buf,nb);
    if(rbs == -1) {
        perror("read error: ");
        return -1;
    }
    return rbs;
}

long System::write_fd(int fd,const void *buf,size_t count) {
    long rbs = write(fd,buf,count);
    if(rbs == -1) {
        perror("write error: ");
        return -1;
    }
    return rbs;
}

int System::close_fd(int _fd) {
    int flag = close(_fd);
    if(flag != 0) {
        perror("close error");
        return -1;
    }
    return flag;
}

unsigned int System::Sleep(unsigned int secs) {
    unsigned int left = sleep(secs);
    return left;
}

string System::getGMTime()
{
    struct tm gmt;
    time_t timep;
    timep = time(nullptr);
    gmtime_r(&timep,&gmt);
    char buf[128];
    asctime_r(&gmt,buf);
    return string(buf);
}
