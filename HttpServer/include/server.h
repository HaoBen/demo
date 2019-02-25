#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <string>

class System;

/* 服务器运行核心类 */
class Server {
private:
    /* 与系统交互用到的工具　*/
    System *sys;
    /* 服务器正在监听的socket描述符 */
    int listenfd;
    /* 监听的端口 */
    int port;

private:
    /* 处理已经和服务器建立连接的请求
     * @param clientfd 客户端的socket描述符
     */
    void handleReq(int clientfd);

public:
    /* 构造函数,需要传命令行参数 */
    Server(int argc,char *argv[]);
    /* 清理资源 */
    ~Server();

    /* 启动服务器 */
    void startup();

    /* 测试函数 */
    static void testServer();
};

/* 该类封装了HTTP请求信息 */
class HttpRequest {
private:
    /* 请求方法 */
    std::string requestMethod;
    /* HTTP版本 */
    std::string requestVersion;
    /* 请求资源 */
    std::string requestUrl;
    /* 请求头 */
    std::map<std::string,std::string> requestHeaders;
    /* 请求主体 */
    std::map<std::string,std::string> requestParams;

public:
    /* 禁止隐式转换的发生 */
    explicit HttpRequest(std::string buf);

    /* 封装的get方法 */
    const std::string & getRequestMethod() { return requestMethod; }
    const std::string & getRequestVersion() { return requestVersion; }
    const std::string & getRequestUrl() { return requestUrl; }
    const std::map<std::string,std::string> & getRequestHeaders() { return requestHeaders; }
    const std::map<std::string,std::string> & getRequestParams() { return requestParams; }
};

/* 该类封装了HTTP响应信息 */
class HttpResponse {
private:
    /* 接下来三个为响应行信息: */
    /* 1. HTTP版本 */
    std::string responseVersion;
    /* 2. 响应状态码 */
    unsigned short responseCode;
    /* 3. 响应状态消息 */
    std::string responseStatus;
    /* 响应头信息 */
    std::map<std::string,std::string> responseHeaders;
    /* 响应主体 */
    std::string responseBody;

public:
    /* 构造函数,功能如下:
     * 1. 初始化响应行为 HTTP/1.1 200 OK
     * 2. 插入Date响应头
     * 3. 插入Content-Type: plain/text响应头
     */
    explicit HttpResponse();

    /* 设置响应内容
     * @param body 存放响应主体的缓冲区
     */
    void setResponseBody(const char *body);

    /* 设置Content-Type响应头
     * @param type Content-Type的值
     */
    void setContentType(std::string type);

    /* 将响应信息以string的形式返回 */
    std::string toString();
};

#endif // SERVER_H
