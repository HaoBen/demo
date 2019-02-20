#include "utils.h"

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
