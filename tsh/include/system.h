#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

/* 該類封装了一些需要进行系统调用的标准C库函数
 * 并且使用了单例模式 */
class System {
private:
    /* 该类的唯一实例,会在首次被使用时初始化 */
    static System *singleton;
public:
    /* 获取该类实例的唯一接口 */
    static System* getSystem();

    /* 获取系统的所有环境变量
     * @return vector<string> 将系统的环境变量信息以向量形式返回
     */
    std::vector<std::string> environments();

    /* 查找某个文件在给定的目录下是否存在,若存在则返回全路径,否则返回空
     * @param name 待查文件
     * @param Path 允许存在的路径
     * @return 全路径
     */
    std::string getFullPath(std::string name,std::string Path);

    /*HELLO WORLD*/
    void hello() {
        printf("Hello,World\n");
    }
private:
    /* 将构造函数声明为private,防止调用者自行初始化对象 */
    System() {}
};

#endif // SYSTEM_H
