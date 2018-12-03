#include "common.h"

vector<string> split(const char *source,const char *spliter) {
    int len = strlen(source);
    vector<string> result;
    //int i = 0;
    const char* rel = strstr(source,spliter);
    const char* rel_old = source;
    while(1) {
        if(rel != NULL && rel != rel_old) {
            string tmp(rel_old,rel);
            result.push_back(tmp);
            rel_old = rel+strlen(spliter);
            rel = strstr(rel_old,spliter);
        } else if(rel == NULL && (rel_old-source < len)){
            string tmp(rel_old,source+len);
            result.push_back(tmp);
            break;
        } else {
            break;
        }
    }
    return result;
}

bool judgeEqual(const ClientInfo &old, const ClientInfo &now)
{
    char* oldstart = (char*)&old;
    char* nowstart = (char*)&now;
    for(size_t i = 0;i < sizeof(ClientInfo);++i) {
        if(*(oldstart+i) != *(nowstart+i))
            return false;
    }
    return true;
}
