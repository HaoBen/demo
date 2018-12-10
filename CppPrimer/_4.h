#ifndef _4_H
#define _4_H

#include <iostream>
#include <string>

/*
 * 主要内容：复合类型
 *      数组
 *      结构体
 *      字符串
 *      枚举
 *      共用体
 * 易错点：
 *      getline(),get()
 */
void _4_1();
void _4_3();
void _4_4();

struct CandyBar {
    std::string brand;
    float weight;
    int calorie;
};
void _4_5();
void _4_6();

struct Pizza {
    std::string brand;
    float diameter;
    float weight;
};
void _4_7();
void _4_8();

void _4_9();
#endif // _4_H
