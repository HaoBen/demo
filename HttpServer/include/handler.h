#ifndef HANDLER_H
#define HANDLER_H

#include <map>
#include <string>

class HttpRequest;
class HttpResponse;

/* 处理请求的Handler基类 */
class Handler {
protected:
    Handler() {}
    friend class HandlerFactory;

public:
    virtual ~Handler() {}

    virtual void doGet(HttpRequest& request, HttpResponse& response) = 0;

    virtual void doPost(HttpRequest& request, HttpResponse& response) = 0;
};
/* 默认的Handler,用于处理静态资源的请求 */
class StaticHandler : public Handler {
public:
    StaticHandler() {}
    ~StaticHandler() {}

    virtual void doGet(HttpRequest& request, HttpResponse& response);
    virtual void doPost(HttpRequest& request, HttpResponse& response);
};
/* cgi请求的handler,用于处理cgi请求 */
class CgiHandler : public Handler {
public:
    CgiHandler() {}
    ~CgiHandler() {}

    virtual void doGet(HttpRequest& request, HttpResponse& response);
    virtual void doPost(HttpRequest& request, HttpResponse& response);
};


/* handlers 的工厂类 */
class HandlerFactory {
private:
    /* 不允许实例化 */
    HandlerFactory() {}
public:
    /* 获取一个处理静态资源响应的handler指针
     *
     * @return handler对象的指针
     */
    static Handler* getStaticHandler();

    /* 获取一个处理cgi请求的handler指针 */
    static Handler* getCgiHandler();

    /* 根据请求决定要将哪一类handler返回
     * 1. 将(.js .png .html .khtml .css .jpg .ico /)结尾的请求转发到StaticHandler
     * 2. 将其余的请求转发到CgiHandler
     */
    static Handler* getHandler(std::string URL);
};
#endif // HANDLER_H
