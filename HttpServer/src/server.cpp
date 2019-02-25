#include "system.h"
#include "server.h"
#include "utils.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

/* 默认监听端口 */
#define DEFAULT_PORT 8080
/* 最大请求排队数 */
#define MAX_REQUEST_WAIT 20
/* 单个请求允许传送的最大数据量(1600B) */
#define MAX_LEN_PER_REQ 1600
/* 单个响应允许传送的最大数据量(1MB) */
#define MAX_LEN_PER_RES 1048576

/* 字符颜色代码 */
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

using namespace std;

/*----------------------------Server类----------start----------------------------------*/

/* 初始化服务器 */
Server::Server(int argc,char *argv[]) {
    /*　获取与系统交互的工具　*/
    sys = System::getSystemHandler();

    /* 默认监听端口80 */
    port = DEFAULT_PORT;
    /* 解析命令行参数 */
    if(argc > 1) {
        while(*argv) {
            if(string(*argv) == "-p") {
                port = stoi(string(*(++argv)));
                if(port < 0) port = DEFAULT_PORT;
            }
        }
    }

    /* 获取监听port端口的socket描述符 */
    listenfd = sys->open_listenfd(port,MAX_REQUEST_WAIT);

    cout<<"服务器初始化完毕,正在监听端口 : "<<port<<endl;
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
            cout<<RED<<"Log: 第 "<<++accept_lost_times<<" 次请求丢失!"<<RESET<<endl;
        } else {
            cout<<GREEN<<"Log: 成功接收来自 |"<<
                  inet_ntoa(clientaddr.sin_addr)<<
                   ":"<<
                   ntohs(clientaddr.sin_port)<<
                   "| 的请求"<<RESET<<endl;
            handleReq(connfd);
            sys->close_fd(connfd);
        }
    }
}

/* 处理HTTP请求 */
void Server::handleReq(int clientfd) {
    /* 将HTTP请求信息读到缓冲区 */
    char buf[MAX_LEN_PER_REQ];
    long rbs = sys->read_fd(clientfd,static_cast<void*>(buf),MAX_LEN_PER_REQ);
    if(rbs <= 0) return;
    buf[rbs-1] = 0;
    cout<<buf<<endl;

    /* 生成请求对象 */
    HttpRequest httpReq(buf);
    /* 生成响应对象 */
    HttpResponse httpRes;
    httpRes.setResponseBody("<html><body><h1>Hello,this is from server!</h1><h2>这是中文</h2></body></html>");
    httpRes.setContentType("text/html; charset=UTF-8");

    /* 将响应发回浏览器端 */
    string res = httpRes.toString();
    sys->write_fd(clientfd,res.c_str(),res.size());
}

/* 测试函数 */
void Server::testServer() {
    Server server(0,nullptr);
    server.startup();
}

/*----------------------------Server类----------end-----------------------------------------*/

/*----------------------------HttpRequest类----------start----------------------------------*/

/* 使用缓存的请求信息构造该类 */
HttpRequest::HttpRequest(string buf) {
    try {
        /* 解析请求方法 */
        string::size_type start = 0,end = 0;
        end = buf.find_first_of(" ",start);
        requestMethod.append(buf,start,end-start);
        /* 解析请求资源 */
        start = buf.find_first_not_of(" ",end);
        end = buf.find_first_of(" ",start);
        requestUrl.append(buf,start,end-start);
        /* 解析请求版本 */
        start = buf.find_first_not_of(" ",end);
        end = buf.find("\r\n",start);
        requestVersion.append(buf,start,end-start);
        /* 解析请求头 */
        start = buf.find_first_not_of("\r\n",end);
        end = buf.find("\r\n\r\n",start);
        vector<string> headers = Utils::splitString(buf.substr(start,end-start),"\r\n");
        for(vector<string>::iterator it = headers.begin(); it != headers.end(); ++it) {
            string::size_type s = 0,e = 0;
            string name,value;
            e = (*it).find_first_of(":",s);
            name.append((*it),s,e-s);
            s = (*it).find_first_not_of(": ",e);
            value.append((*it),s);
            requestHeaders.insert(pair<string,string>(name,value));
        }
        /* 解析请求正文 */
        start = buf.find_first_not_of("\r\n",end);
        if(start < buf.size()) {
            vector<string> params = Utils::splitString(buf.substr(start),"&");
            for(vector<string>::iterator it = params.begin(); it != params.end(); ++it) {
                vector<string> tmp = Utils::splitString((*it),"=");
                if(tmp.size() > 2) {
                    requestParams.insert(pair<string,string>(tmp[0],tmp[1]));
                }
            }
        }
    } catch(out_of_range err) {
        cout<<RED<<"Log: HTTP请求解析错误("<<err.what()<<")"<<RESET<<endl;
    }
}

/*----------------------------HttpRequest类----------end------------------------------------*/

/*----------------------------HttpResponse类---------start----------------------------------*/

/* 初始化一个基本的HttpResponse对象 */
HttpResponse::HttpResponse() {
    responseVersion.append("HTTP/1.1");
    responseCode = 200;
    responseStatus.append("OK");
    responseHeaders.insert(pair<string,string>("Date","2019.2.25"));
    responseHeaders.insert(pair<string,string>("Content-Type","plain/text"));
}

void HttpResponse::setResponseBody(const char *body)
{
    responseBody.append(body);
    responseHeaders.insert(pair<string,string>("Content-Length",to_string(responseBody.size())));
}

void HttpResponse::setContentType(string type)
{
    responseHeaders.at("Content-Type") = type;
}

string HttpResponse::toString()
{
    stringstream ss;
    ss<<responseVersion<<" "<<responseCode<<" "<<responseStatus<<"\r\n";
    for (map<string,string>::iterator it = responseHeaders.begin(); it != responseHeaders.end(); ++it) {
        ss<<it->first<<": "<<it->second<<"\r\n";
    }
    ss<<"\r\n"<<responseBody;
    return ss.str();
}

/*----------------------------HttpResponse类---------end------------------------------------*/
