#include "server.h"

map<int,User>* Server::users = new map<int,User>();
int Server::m_sock = -1;
const char* SERV_IP = "192.168.231.129";      //服务器的IP地址
const in_port_t SERV_PORT = 60000;      //和端口

int Server::Init(const char *ip, in_port_t port) {
    int rlt = 0;

    //to store error message
    int errMsg;

    //create server's socket
    m_sock = socket(AF_INET,SOCK_DGRAM,0);
    if(m_sock == -1) {
        //exception happened while creating socket
        printf("failed to create socket with error : %s\n",strerror(errno));

        rlt = 1;
        return rlt;
    } else {
        printf("Server startup at %s:%d and fd is %d\n",ip,port,m_sock);
    }

    //server socket's sockaddr_in
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    //bind sockaddr with main sock
    errMsg = bind(m_sock,(sockaddr*)&serverAddr,sizeof(serverAddr));
    if(errMsg < 0) {
        //failed to bind
        printf("bind failed with error : %d\n",errMsg);
        rlt = 2;
        return rlt;
    }

    //Initialize users
    User user(467682352);
    users->insert(pair<int,User>(467682352,user));
    return rlt;
}


void Server::startup() {
    //initialize this server
    int iRlt = Init(SERV_IP,SERV_PORT);
    if(iRlt != 0) {
        printf("Init failed...\n");
        return;
    }

    //initialize sccessfully,and listen this socket
    printf("Init ok...\n");
    //listen(m_sock,5);     //TCP

    ClientInfo client;      //it's used to store information about the connected client
    socklen_t len = sizeof(sockaddr);
    //int clientSocket;        //this socket is used to communicate with the connected client

    Message buf;
    do {
        memset(&buf,0,sizeof(buf));
        //judge whether a client connects to server
        //client.client_socket = accept(m_sock,(sockaddr*)&(client.client_addr),&len);
        iRlt = recvfrom(m_sock,&buf,sizeof(buf),0,(sockaddr*)&(client.client_addr),&len);
        if(iRlt == -1) {
            fprintf(stderr,"recvfrom error : %s\n",strerror(errno));
            //No connection or failed to connect
        } else {
            switch (buf.commond) {
            case HELLO:
                hello(buf,client);
                break;
            case LOGIN:
                login(buf,client);
                break;
            case SEND_MESSAGE:
                send_message(buf,client);
                break;
            case GET_MESSAGE:
                get_message(buf);
                break;
            default:
                printf("%d\n",buf.commond);
                test(client);
                break;
            }
        }
    } while(1);
}


bool Server::hello(Message& mes,ClientInfo &client)
{
    int nums = sendto(m_sock,&mes,HEAD_LEN+strlen(mes.mess),0,(sockaddr*)&(client.client_addr),sizeof(sockaddr));
    printf("Request from %s:%d(HELLO)---------%s\n",
           inet_ntoa(client.client_addr.sin_addr),
           ntohs(client.client_addr.sin_port),
           mes.mess);

    if(nums > 0)
        return true;
    else {
        fprintf(stderr,"sendto error : %s\n",strerror(errno));
        return false;
    }
}

bool Server::login(Message &mes, ClientInfo &client)
{
    printf("Request from %s:%d(LOGIN)-----------%d:%s   ",
           inet_ntoa(client.client_addr.sin_addr),
            ntohs(client.client_addr.sin_port),
            mes.from,mes.mess);
    USER_ID id = mes.from;
    size_t head_len = 12;
    map<int,User>::iterator user = users->find(id);
    if(user == users->end()) {
        return false;
    } else {
        if(!strcmp(mes.mess,"login")) {
            user->second.login_device = client;
            user->second.online = true;
            printf("OK\n");
            strcpy(mes.mess,"OK");

            //start threads to send messages
            pthread_t pid;
            //map<int,User>::iterator iter = users->
            if(pthread_create(&pid,NULL,sendMesP,&(users->begin()->second)))
                strcpy(mes.mess,"FAIL");

        } else {
            printf("FAIL\n");
            strcpy(mes.mess,"FAIL");
        }
        sendto(m_sock,&mes,head_len+strlen(mes.mess),0,(sockaddr*)&(client.client_addr),sizeof(sockaddr));
        return true;
    }
    return false;
}

bool Server::test(ClientInfo &client)
{
    sendto(m_sock,"TEST\n",5,0,(sockaddr*)&(client.client_addr),sizeof(sockaddr));
    return false;
}

bool Server::send_message(Message &mes, ClientInfo &client)
{
    //to judge the mess wether is legal
    map<int,User>::iterator sendUser = users->find(mes.from);
    if(sendUser == users->end())
        return false;
    if(judgeEqual(sendUser->second.login_device,client))
        return false;

    //to push the mes into right queue
    map<int,User>::iterator recvUser = users->find(mes.to);
    if(recvUser == users->end()) {
        return false;
    } else {
        recvUser->second.messages->push(mes);
        return true;
    }
    return false;
}

bool Server::get_message(Message &mes)
{
    map<int,User>::iterator iter = users->find(mes.from);
    pthread_t pid;
    if(iter == users->end())
        return false;
    else {
        pthread_create(&pid,NULL,sendMesP,&(iter->second));
        return true;
    }
}

void* Server::handleMessage(void *arg) {
    bool flag = true;          //judging whether this thread should exist
    ClientInfo client = *(ClientInfo*)arg;      //recieve the information about client

    char clientip[16];      //store client's ip as string
    uint16_t port = ntohs(client.client_addr.sin_port);               //client's port
    inet_ntop(AF_INET, &client.client_addr.sin_addr.s_addr, clientip, sizeof(clientip));

    char buf[2048];         //buffer area;
    printf("New Client connect : %s:%d and fd is %d\n",
           clientip,port,client.client_socket);

    //recieving message from client
    int rval;
    //printf("The process of recieving message----------------------------------\n");
    do {
        memset(buf,0,sizeof(buf));
        rval = read(client.client_socket,buf,sizeof(buf));

        if(rval == -1) {
            printf("Recieving process breakdown!-----------------------------------\n");
            break;
        } else {
            //printf("%s",buf);
            vector<string> request = split(buf,"\r\n");
            flag = false;
        }
    } while(flag);
    //printf("End reieving normally--------------------------------------------\n");

    //send message to client
    const char *msg = "HTTP/1.1 200 OK\r\n"
                      "Server: Dinghao\r\n"
                      "\r\n"
                      "<HTML><body><h1>Hello,you can see me,right?</h1></body></HTML>";
    rval = write(client.client_socket,msg,strlen(msg));
    if(rval == -1)
        printf("Send error\n\n");
    else
        printf("Send OK!\n\n");

    //close client's socket
    printf("%d will be down!\n",client.client_socket);
    close(client.client_socket);
    return NULL;
}

void* Server::recieveMes(void *arg) {
    return arg;
}

void* Server::sendMesP(void *arg)
{
    User* user = (User*)arg;
    while(user->online) {
        //printf("%d",(int)user->messages->size());
        if(user->messages->empty())
            continue;
        else {
            Message *mes = &(user->messages->front());
            if(sendto(m_sock,mes,HEAD_LEN+strlen(mes->mess),0,
                      (sockaddr*)&(user->login_device.client_addr),sizeof(sockaddr))) {
                user->messages->pop();
            }
        }
        sleep(1);
    }
    return NULL;
}
