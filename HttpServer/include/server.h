#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <string>

class System;

/* 服务器运行核心类 */
class Server {
private:
    /* 与系统交互用到的工具　*/
    static System *sys;
    /* 服务器正在监听的socket描述符 */
    int listenfd;
    /* 监听的端口 */
    int port;
    /* 服务器的家目录 */
    std::string home_dir;

private:
    /* 处理已经和服务器建立连接的请求
     * @param clientfd 客户端的socket描述符
     */
    static void handleReq(int clientfd,Server* context);

public:
    /* 构造函数,需要传命令行参数 */
    Server(int argc,char *argv[]);
    /* 清理资源 */
    ~Server();

    /* 启动服务器 */
    void startup();

    /* 获取家目录的接口 */
    std::string getHomeDir() const { return home_dir; }

    /* 测试函数 */
    static void testServer();
};

#endif // SERVER_H
