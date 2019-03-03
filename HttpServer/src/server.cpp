#include "system.h"
#include "server.h"
#include "utils.h"
#include "http.h"
#include "handler.h"
#include "log.h"
#include <stdexcept>
#include <thread>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

/* 默认监听端口 */
#define DEFAULT_PORT 8080
/* 服务器默认的家目录 */
#define DEFAULT_HOME_DIR "/home/dinghao/www"
/* 最大请求排队数 */
#define MAX_REQUEST_WAIT 20
/* 单个请求允许传送的最大数据量(1600B) */
#define MAX_LEN_PER_REQ 1600
/* 单个响应允许传送的最大数据量(1MB) */
#define MAX_LEN_PER_RES 1048576

using namespace std;

/*----------------------------Server类----------start----------------------------------*/
System* Server::sys = nullptr;
/* 初始化服务器 */
Server::Server(int argc,char *argv[]) {
    /*　获取与系统交互的工具　*/
    if(!sys)
        sys = System::getSystemHandler();

    /* 默认监听端口80 */
    port = DEFAULT_PORT;
    home_dir = DEFAULT_HOME_DIR;

    /* 解析命令行参数 */
    if(argc > 1) {
        while(*argv) {
            if(string(*argv) == "-p") {
                if(argv[1]) {
                    port = stoi(string(*(++argv)));
                    if(port < 0) port = DEFAULT_PORT;
                }
            } else if(string(*argv) == "--home") {
                if(argv[1])
                    home_dir = *(++argv);
            }
        }
    }

    /* 获取监听port端口的socket描述符 */
    listenfd = sys->open_listenfd(port,MAX_REQUEST_WAIT);

    stringstream ss;
    ss<<"服务器初始化完毕,正在监听端口"<<port;
    Log::printLog(ss.str());
}

/* 析构函数,清理无用资源 */
Server::~Server() {
    sys->close_fd(listenfd);
}

/* 服务器启动入口 */
void Server::startup() {
    /* 客户端socket描述符 */
    int connfd;
    /* 客户端socket地址信息 */
    struct sockaddr_in clientaddr;

    /* 请求丢失次数 */
    unsigned int accept_lost_times = 0;
    /* 主线程循环接收请求 */
    while(1) {
        connfd = sys->accept_fd(listenfd,&clientaddr);
        if(connfd < 0) {
            stringstream ss;
            ss<<"第 "<<++accept_lost_times<<" 次请求丢失!";
            Log::printWarn(ss.str());
        } else {
            stringstream ss;
            ss<<"成功接收来自 |"<<inet_ntoa(clientaddr.sin_addr)<<":"<<ntohs(clientaddr.sin_port)<<"| 的请求";
            Log::printLog(ss.str());
            /* 创建一个新的线程处理请求 */
            thread handle_thread(handleReq,connfd,this);
            handle_thread.detach();
        }
    }
}

/* 处理HTTP请求 */
void Server::handleReq(int clientfd,Server* context) {
    /* 将HTTP请求信息读到缓冲区 */
    char buf[MAX_LEN_PER_REQ];
    long rbs = sys->read_fd(clientfd,static_cast<void*>(buf),MAX_LEN_PER_REQ);
    /* 如果请求为空,则直接关闭socket */
    if(rbs <= 0) {
        sys->close_fd(clientfd);
        return;
    }
    buf[rbs-1] = 0;

    /* 生成请求对象 */
    HttpRequest httpReq(buf,context);
    /* 生成响应对象 */
    HttpResponse httpRes;

    /* 将请求和响应对象转发给对应的Handler处理,转发细节由HandlerFactory决定
     */
    Handler* handler = HandlerFactory::getHandler(httpReq.getRequestUrl());
    handler->doGet(httpReq,httpRes);

    /* 将响应发回浏览器端 */
    string res = httpRes.toString();
    sys->write_fd(clientfd,res.c_str(),res.size());
    sys->close_fd(clientfd);
}

/* 测试函数 */
void Server::testServer() {
    Server server(0,nullptr);
    server.startup();
}

/*----------------------------Server类----------end-----------------------------------------*/
