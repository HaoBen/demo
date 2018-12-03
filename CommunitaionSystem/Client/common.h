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

//Message类，与服务器端相同
class Message {
public:
    int commond;
    USER_ID from;
    USER_ID to;
    char mess[MAX_LEN_PER_MESSAGE];
};
#endif // COMMON_H
