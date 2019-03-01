#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

/* 该类封装了一些通用的工具函数 */
class Utils {
public:
    /* 字符串分割函数
     * @param input(string) 待分割字符串
     * @param delim(const char*) 有效的分割符
     * @return 分割后的字符串向量
     */
    static std::vector<std::string> splitString(std::string input,const char *delim);

    /* 判断字符串是否以某个子串结尾
     * @param source 源字符串
     * @param end 子串
     * @return 成功为true
     */
    static bool endWith(std::string& source,const char* end);
};

#endif // UTILS_H
