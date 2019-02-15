#include "shell.h"
#include <iostream>

using namespace std;

/* 构造函数,主要功能:
 *  1. 初始化环境变量信息
 */
Shell::Shell() {
    sys = System::getSystem();

    /* 获取环境变量信息 */
    vector<string> tmp = sys->environments();
    for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
        vector<string>::size_type delimiter = (*it).find("=");
        string name = (*it).substr(0,delimiter);
        string value = (*it).substr(++delimiter);
        env.insert(pair<string,string>(name,value));
    }
}

string Shell::getEnv(string name) {
    return env[name];
}

void Shell::setEnv(std::string name, std::string value) {
    map<string,string>::iterator it = env.find(name);
    if(it == env.end()) {
        /*环境变量中不存在name的变量*/
        if(!value.empty())
            env.insert(pair<string,string>(name,value));
    } else {
        it->second = value;
    }
}

void Shell::testShell()  {
    Shell shell;
//    for (map<string,string>::iterator it = shell.env.begin(); it != shell.env.end(); ++it) {
//        cout<<it->first<<"-->"<<it->second<<endl;
//    }
    cout<<shell.getEnv("PATH")<<endl;
    shell.setEnv("PATH","TEST");
    cout<<shell.getEnv("PATH")<<endl;
}
