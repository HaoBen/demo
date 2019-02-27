#include "handler.h"
#include "http.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

/*--------------------------------------------------------------------------------*/
void StaticHandler::doGet(HttpRequest &request, HttpResponse &response)
{
    /* 根据URL和家目录信息,构造出本次请求资源在计算机上的绝对目录 */
    string filename = request.getServerContext()->getHomeDir();
    filename.append(request.getRequestUrl());
    if(filename[filename.size()-1] == '/') {
        filename.append("index.html");
    }

    /* 尝试打开请求资源 */
    ifstream source;
    stringstream buffer;
    source.open(filename);
    if(source.is_open()) {
        buffer<<source.rdbuf();
        response.setResponseBody(buffer.str());
        source.close();
    } else {
        /* 记录日志,并设响应状态 */
        response.setResponseCode(404);
    }
}

void StaticHandler::doPost(HttpRequest &request, HttpResponse &response)
{
    response.setResponseCode(501);
}


void CgiHandler::doGet(HttpRequest &request, HttpResponse &response)
{
    response.setResponseCode(501);
}

void CgiHandler::doPost(HttpRequest &request, HttpResponse &response)
{
    response.setResponseCode(501);
}
/*--------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------*/
Handler *HandlerFactory::getStaticHandler()
{
    static StaticHandler handler;
    return &handler;
}

Handler *HandlerFactory::getCgiHandler()
{
    static CgiHandler handler;
    return &handler;
}

Handler *HandlerFactory::getHandler(string URL)
{
    if(URL[URL.size()-1] == '/') {
        return HandlerFactory::getStaticHandler();
    }
    string::size_type tmp;
    string suffix;
    static string staticSourceFlag = "js html khtml css jpg png ico";
    tmp = URL.find_last_of(".");
    if(tmp != URL.size()) {
        tmp = staticSourceFlag.find(suffix);
        if(tmp != staticSourceFlag.size()) {
            return HandlerFactory::getStaticHandler();
        }
    }
    return HandlerFactory::getCgiHandler();
}
/*--------------------------------------------------------------------------------*/

