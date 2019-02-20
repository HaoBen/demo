#ifndef SYSTEM_H
#define SYSTEM_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* 封装的System类,与系统交互 */
class System {
/* 以单例模式实现 */
private:
    static System *singleton;

private:
    /* 将构造函数声明为私有,防止外部初始化 */
    System() {}

public:
    static System *getSystemHandler();

    /* 打开一个需要被监听的socket描述符
     * @param port 需要监听的端口
     * @param r_limit 请求排队数限制
     * @return 成功返回打开的文件描述符,失败返回-1
     */
    int open_listenfd(int port,int r_limit);

    /* 接收一个在指定socket的请求队列中连接
     * @param _listenfd 被监听的socket描述符
     * @param clientaddr 保存客户socketaddr的指针
     * @return 成功返回建立连接的客户socket描述符,失败返回-1
     */
    int accept_fd(int _listenfd,struct sockaddr_in *clientaddr);

    /* 读取文件描述符fd对应设备中的内容
     * @param fd 待读取设备的文件描述符
     */
    long read_fd(int fd,void *buf,size_t nb);

    /* 关闭打开的文件描述符
     * @param _fd 需要关闭的文件描述符
     * @return 成功返回0,不成功返回 -1
     */
    int close_fd(int _fd);

    /* 休眠函数
     * @param sesc 休眠秒数
     * @return 剩余的休眠时间
     */
    unsigned int Sleep(unsigned int secs);

};

#endif // SYSTEM_H
