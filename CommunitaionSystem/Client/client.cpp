#include "client.h"

const char* SERV_IP = "192.168.231.129";      //服务器的Ip
const in_port_t SERV_PORT = 60000;      //  和端口

using namespace std;

bool Client::Init(const char *ip, in_port_t port) {
    current_user = -1;
    is_login = false;
    m_sock = socket(AF_INET,SOCK_DGRAM,0);
    int err_count = 0;

    //初始化并创建客户端socket
    while(m_sock < 0) {
        m_sock = socket(AF_INET,SOCK_DGRAM,0);
        fprintf(stderr,"socket error : %s\n",strerror(errno));
        if(err_count++ < 5) {
            sleep((err_count-1)*2);
        } else {
            printf("Init failed!\n");
            return false;
        }
    }

    //写入服务端详细地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    printf("Init OK!\n");
    return true;
}

void Client::start()
{
    if(!Init(SERV_IP,SERV_PORT))
        return;

    if(!hello()) return;
    if(login()) is_login = true;
}

bool Client::hello()
{
    Message mes;
    mes.commond = HELLO;
    mes.from = 0;
    mes.to = 0;
    socklen_t len = sizeof(sockaddr);
    strcpy(mes.mess,"Hello");

    int nums = sendto(m_sock,&mes,HEAD_LEN+strlen(mes.mess),0,(sockaddr*)&server_addr,sizeof(sockaddr));
    if(nums == -1) {
        fprintf(stderr,"send error : %s\n",strerror(errno));
        return false;
    } else {
        printf("say hello to server!\n");
    }

    memset(&mes,0,sizeof(mes));
    nums = recvfrom(m_sock,&mes,sizeof(mes),0,(sockaddr*)&server_addr,&len);
    if(nums <= 0) {
        fprintf(stderr,"recieve error : %s\n",strerror(errno));
        return false;
    } else {
        printf("OK!the server say hello to you!\n");
    }

    return true;
}

bool Client::login()
{
    Message mes;
    mes.commond = 1;
    mes.to = 0;
    printf("Please enter your id : ");
    scanf("%d",&(mes.from));
    printf("Please enter your password : ");
    scanf("%s",mes.mess);

    sendto(m_sock,&mes,HEAD_LEN+strlen(mes.mess),0,(sockaddr*)&server_addr,sizeof(sockaddr));
    memset(&mes,0,sizeof(mes));
    recvfrom(m_sock,&mes,sizeof(mes),0,(sockaddr*)&server_addr,NULL);
    if(mes.commond == LOGIN && !strcmp(mes.mess,"OK")) {
        current_user = mes.from;
        printf("Login Successfully!\n\n");
        return true;
    } else {
        printf("Login failed!\n\n");
    }
    return false;
}
