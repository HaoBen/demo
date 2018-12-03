#ifndef CLIENT_H
#define CLIENT_H

#include <unistd.h>
#include "common.h"

using namespace std;

class Client {
private:
    USER_ID current_user;
    bool is_login;
public:
    sockaddr_in server_addr;
    int m_sock;

    Client(){}
    ~Client(){
        if(m_sock != -1)
            close(m_sock);
    }

    bool Init(const char* ip,in_port_t port);     //初始化工作
    void start();       //Client入口

    bool hello();       //向服务器打招呼

    bool login();       //登录函数
};
#endif // CLIENT_H
