#include "handler.h"
#include "http.h"
#include "system.h"
#include "utils.h"
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

/*--------------------------------------------------------------------------------*/
void Handler::doGet(HttpRequest &request, HttpResponse &response)
{
    response.setResponseCode(501);

}

void Handler::doPost(HttpRequest &request, HttpResponse &response)
{
    response.setResponseCode(501);
}
/*--------------------------------------------------------------------------------*/


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

static char* argcopy(const string& input) {
    size_t len = input.size();
    char * res = new char[len];
    for(size_t i = 0;i < len;++i) {
        res[i] = input[i];
    }
    res[len] = 0;
    return res;
}
void CgiHandler::doGet(HttpRequest &request, HttpResponse &response)
{
    /* 根据URL和家目录信息,构造出本次请求资源在计算机上的绝对目录 */
    string filename = request.getServerContext()->getHomeDir();
    filename.append(request.getRequestUrl());

    /* 检查一下请求资源的信息 */
    if(access(filename.c_str(),X_OK) == -1) {
        response.setResponseCode(500);
        perror("ERROR: ");
        return;
    }

    /* 创建管道,[0]是用来读的,[1]是用来写的
     * 注意::::创建管道一定要在fork子进程之前,否则父子进程中创建出的管道是完全不同的
     * 而且如果在子进程中exec成功的话,子进程exec后面的代码就都不会执行了
     */
    int pipefd[2];
    if(pipe(pipefd) < 0) {
        response.setResponseCode(500);
        Log::printError(strerror(errno));
        return;
    }
    /* fork子进程执行cgi程序 */
    pid_t pid = fork();
    if(pid < 0) {
        response.setResponseCode(500);
        Log::printError(strerror(errno));
        return;
    } else if(pid == 0) {
        /* 子进程写管道,故关闭[0],并将其标准输出重定向到写管道 */
        close(pipefd[0]);
        if(dup2(pipefd[1],STDOUT_FILENO) == -1) {
            Log::printError(strerror(errno));
            exit(EXIT_FAILURE);
        }

        /* 判断可执行文件类型,脚本还是二进制文件 */
        string cmd;
        if(Utils::endWith(filename,".sh")) {
            cmd = "/bin/bash";
        } else if(Utils::endWith(filename,".py")) {
            cmd = "/bin/python";
        }
        size_t tmp = 0;
        char *argv[4];
        if(cmd.empty()) {
            argv[tmp++] = argcopy(filename);
            cmd = filename;
        } else {
            argv[tmp++] = argcopy(cmd);
            argv[tmp++] = argcopy(filename);
        }
        argv[tmp] = nullptr;
        /* 构造cgi程序的命令行参数,并执行cgi程序 */
        if(execv(cmd.c_str(),argv) == -1) {
            Log::printError(strerror(errno));
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
    } else {
        /* 父进程读管道,故关闭[1],并等子进程结束 */
        System::getSystemHandler()->close_fd(pipefd[1]);
        int status;
        waitpid(pid,&status,0);

        /* 读取管道里的内容 */
        stringstream buffer;
        ssize_t nbs;
        char buf[1024];
        while((nbs = read(pipefd[0],buf,1023)) > 0) {
            buf[nbs] = 0;
            buffer<<buf;
        }

        /* 设置响应主体并关闭读管道 */
        if(buffer.str().empty()) {
            response.setResponseCode(500);
        } else {
            response.setResponseBody(buffer.str());
        }
        System::getSystemHandler()->close_fd(pipefd[0]);
    }
}
/*--------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------*/
Handler *HandlerFactory::getStaticHandler()
{
    static StaticHandler static_handler;
    return &static_handler;
}

Handler *HandlerFactory::getCgiHandler()
{
    static CgiHandler cgi_handler;
    return &cgi_handler;
}

Handler *HandlerFactory::getHandler(string URL)
{
    if(URL[URL.size()-1] == '/') {
        return HandlerFactory::getStaticHandler();
    }
    string::size_type tmp;
    string suffix;
    static string staticSourceFlag = ".js .html .khtml .css .jpg .png .ico";
    tmp = URL.find_last_of(".");
    if(tmp != URL.npos) {
        suffix = URL.substr(tmp);
        tmp = staticSourceFlag.find(suffix);
        if(tmp != staticSourceFlag.npos) {
            return HandlerFactory::getStaticHandler();
        }
    }
    return HandlerFactory::getCgiHandler();
}
/*--------------------------------------------------------------------------------*/
