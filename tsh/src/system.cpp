#include "system.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

/* 系统的环境变量信息 */
extern char** environ;

System* System::singleton = nullptr;

System* System::getSystem() {
    if(singleton == nullptr) {
        singleton = new System();
    }
    return singleton;
}

vector<string> System::environments() {
    vector<string> res;
    int i = 0;
    while(environ[i]) {
        res.push_back(string(environ[i++]));
    }
    return res;
}

string System::getFullPath(string name,string Path) {
    string fullPath;
    if(name.empty()) return fullPath;
    /* 分割PATH环境变量 */
    vector<string> pathes = Utils::splitString(Path,":");

    string tmp;
    for(string::size_type i = 0;i < pathes.size();++i) {
        /* tmp = pathes[i]/name */
        tmp = pathes[i];
        tmp .append("/");
        tmp.append(name);

        /* 测试文件是否存在 */
        FILE *test = fopen(tmp.c_str(),"r");
        if(test) {
            fullPath.append(pathes[i]+"/"+name);
            fclose(test);
        }
    }
    return fullPath;
}
