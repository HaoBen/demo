#include "utils.h"
#include <cstring>

using namespace std;

vector<string> Utils::splitString(string input,const char *delim) {
    vector<string> res;
    string::size_type start = 0,end;
    while(start < input.size()) {
        end = input.find_first_of(delim,start);
        res.push_back(input.substr(start,end-start));
        start = input.find_first_not_of(delim,end);
    }
    return res;
}

bool Utils::endWith(string &source, const char *end)
{
    size_t len1 = strlen(end);
    string::size_type len2 = source.size();
    if(len2 < len1)
        return false;
    while(1) {
        if(end[--len1] != source[--len2])
            return false;
        if(len1 == 0)
            break;
    }
    return true;
}
