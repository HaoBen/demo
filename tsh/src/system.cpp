#include "system.h"
#include <stdlib.h>

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

