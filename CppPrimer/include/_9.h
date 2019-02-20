#ifndef _9_H
#define _9_H
/*
 * 主要内容：
 * 1. 单独编译
 * 2. 存储持续性、作用域和连接性（自动变量，静态变量，寄存器变量；全局变量，局部变量；内部链接性，外部链接性,无连接性）
 *      2.1 在头文件中定义变量、常量时需要格外注意
 * 3. 布局new操作符
 * 4. 名称空间（相当于给在该名称空间下的所有变量、函数、类和结构的名称以该空间的名称作为前缀进行了扩展，其它的特性不变）
 */

const int Len = 40;     //Len是静态常量，仅有内部链接性，即仅在包含该文件的源文件中可见
struct golf {
    char fullname[Len];
    int handicap;
};
void _9_1();

void _9_2();

//9.3太简单了，不写了

namespace SALES {
    const int QUARTERS = 4;
    struct Sales {
        double sales[QUARTERS];
        double average;
        double max;
        double min;
    };
    void setSales(Sales& s,const double ar[],int n);
    void setSales(Sales& s);
    void showSales(const Sales& s);
}
void _9_4();
#endif // _9_H
