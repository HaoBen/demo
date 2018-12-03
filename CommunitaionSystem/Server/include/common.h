#ifndef COMMON_H
#define COMMON_H

#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_LEN_PER_MESSAGE 1024
#define MAX_LEN_MES_QUEUE 100
#define HEAD_LEN 12
#define HELLO 0
#define LOGIN 1
#define SEND_MESSAGE 2
#define GET_MESSAGE 3

typedef int USER_ID;

using namespace std;

/*
 * This is used for handleMessage as a argument
 */
struct ClientInfo {
    int client_socket;
    sockaddr_in client_addr;
};


/*
 * each message come from this class
 */
class Message {
public:
    int commond;    //the type of this message
    USER_ID from;       //the senter's id
    USER_ID to;         //the reciever's id
    char mess[MAX_LEN_PER_MESSAGE];        //content of this message
};

/*
 * class User restore  a user's information
 * include
 *      account name(id)
 */
class User {
public:
    int id;
    bool online;        //online or offline
    ClientInfo login_device;    //information about the user's login device

    queue<Message>* messages;   //all messages is relatived to this user

public:
    User(int id) {
        this->id = id;
        online = false;
        messages = new queue<Message>();
    }
    /*
     * add a message to the queue,while
     *      the server recieved a request
     */
    void addMessage(Message* mes);

    /*
     * send all messages to relatived client user,while
     *      user login
     *      addMessgae() happened
     */
    void sendMessage();
};

//-------------------------------------
//the following all is util function
//-------------------------------------

//split the source str with spliter
vector<string> split(const char* source,const char* spliter);
bool judgeEqual(const ClientInfo& old,const ClientInfo& now);

#endif // COMMON_H
