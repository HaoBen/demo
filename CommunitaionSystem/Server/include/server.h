#ifndef SERVER_H
#define SERVER_H


#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <map>
#include "common.h"

using namespace std;
/*
 * This class implements server's functions
 */
class Server {
public:

private:
    /*
     * server's main socket,it exist while the server is running
     */
    static int m_sock;

    static map<int,User> *users;        //a map pointer for <id,user>
public:
    Server(){

    }
    ~Server() {
        if(m_sock != -1)
            close(m_sock);
    }

    void startup();                 //run server

private:
    int Init(const char* ip,in_port_t port);      //to initialize server

    bool hello(Message& mes,ClientInfo& client);         //it's called when HELLO request
    bool login(Message& mes,ClientInfo& client);        //it's called when LOGIN request
    bool test(ClientInfo& client);      //just for test
    bool send_message(Message& mes,ClientInfo& client);     //it's called when SEND_MESAAGE request
    bool get_message(Message& mes);            //it's called when GET_MESSAGE request

    static void* handleMessage(void* arg);               //to handle messages from client(TCP)
    static void* recieveMes(void* arg);     //to recieve message(UDP)
    static void* sendMesP(void* arg);         //to send message(UDP)(new pthread)

};


#endif // SERVER_H
