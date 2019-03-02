#include "log.h"
#include <iostream>

using namespace std;

/* 默认的日志文件路径 */
#define DEFAULT_LOG_PATH "logs/server.log"

/* 字符颜色代码 */
#define RESET   "\033[0m"       /* Reset */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */

Log::Log(const char *logpath)
{
    if(!logpath)
        logpath = DEFAULT_LOG_PATH;
    logstream.open(logpath,ios_base::app);
    if(!logstream.is_open()) {
        perror("LOG ERROR");
    }
}

void Log::printLog(string con)
{
    cout<<GREEN<<"Log: "<<con<<RESET<<endl;
}

void Log::printWarn(string con)
{
    cout<<YELLOW<<"Warn: "<<con<<RESET<<endl;
}

void Log::printError(string con)
{
    cout<<RED<<"Error: "<<con<<RESET<<endl;
}

void Log::logLog(string con)
{
    if(logstream.is_open()) {
        logstream<<"Log: "<<con<<endl;
    } else {
        cout<<GREEN<<"Log: "<<con<<RESET<<endl;
    }
}

void Log::logWarn(string con)
{
    if(logstream.is_open()) {
        logstream<<"Warn: "<<con<<endl;
    } else {
        cout<<YELLOW<<"Warn: "<<con<<RESET<<endl;
    }
}

void Log::logError(string con)
{
    if(logstream.is_open()) {
        logstream<<"Error: "<<con<<endl;
    } else {
        cout<<RED<<"Error: "<<con<<RESET<<endl;
    }
}
