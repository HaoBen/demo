#include "server.h"
#include "thread_pool.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>

using namespace std;

class A {
public:
    A() {cout<<"C A"<<endl;}
    A(A&& a) {cout<<"M A"<<endl;}
    A(int a) {cout<<"int A"<<endl;}
    ~A() {cout<<"D A"<<endl;}
};
void test( A&& a)  {}
int main(int argc,char *argv[]) {
//    Server server(argc,argv);
//    server.startup();
//    A a = 3;
//    A b = move(a);
    test(3);
}

