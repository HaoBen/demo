#ifndef LOG_H
#define LOG_H

#include <fstream>

/* 日志模块 */
class Log {
private:
    /* 日志的文件输出流 */
    std::ofstream logstream;

public:
    /* 构造函数
     * @param logpath 日志文件路径,默认为空,为空的话表示输出到终端
     */
    Log(const char* logpath = nullptr);
    /* 析构函数 */
    ~Log() {}

    /* 输出到终端 */
    static void printLog(std::string con);
    static void printWarn(std::string con);
    static void printError(std::string con);

    /* 记录到文件 */
    void logLog(std::string con);
    void logWarn(std::string con);
    void logError(std::string con);
};

#endif // LOG_H
