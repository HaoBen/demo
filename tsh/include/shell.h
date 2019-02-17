#ifndef SHELL_H
#define SHELL_H

#include <map>
#include <string>
#include <vector>
#include "system.h"

/* 该类封装了shell程序的核心类
 * 主要功能:
 *  1. 与用户交互(解释用户的输入)
 *  2. 提供程序执行接口
 *  3. 提供脚本执行功能
 */
class Shell {
private:
    /* 保存执行程序时提供的环境变量,之所以在Shell类中保存,是为了避免程序修改环境变量对shell之外的程序造成影响 */
    std::map<std::string,std::string> env;
    System *sys;
private:

public:
    /* 构造函数 */
    Shell();

    /* shell程序入口 */
    void start();

    /* 封装之后的获取环境变量的方法
     * @param name(string) 需要获取的环境变量的名字
     * @return string 环境变量值,不存在返回空
     */
    std::string getEnv(std::string name);

    /* 封装之后的设置环境变量的方法
     * @param name(string) 需要设置的环境变量名
     * @param value(string) 需要设置的环境变量值(存在则修改,不存在则添加)
     * @return */
    void setEnv(std::string name,std::string value);

    std::string parseInput(std::string input);

    /* 测试函数 */
    static void testShell();
};

#endif // SHELL_H
