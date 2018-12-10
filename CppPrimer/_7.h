#ifndef _7_H
#define _7_H
/*
 * 主要内容
 * 1. 函数原型（函数声明），函数声明，函数调用
 * 2. 函数参数的按值传递（包括以指针作为参数），函数参数的按引用传递
 * 3. 函数指针 typename (*pf)(args)
 */
#include <iostream>

void _7_1();
void _7_2();

struct box {
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};
void _7_3();

void _7_5();
void _7_6();
void _7_7();

void _7_9();
#endif // _7_H
