#include <iostream>
#include "server.h"

using namespace std;

/*
void *thread(void* arg) {
    for(int i = 0;i < 3;++i) {
        cout<<"child"<<*(int*)arg<<"'s No."<<i<<" print_out"<<endl;
        sleep(1);
    }
    return 0;
}*/
class A{

};
int main()
{
    Server *server = new Server();
    server->startup();
    return 0;
    /*
    pthread_t id1,id2;
    int a =1,b=2;
    int ret1 = pthread_create(&id1, NULL, thread,(void*)&a);
    int ret2 = pthread_create(&id2,NULL,thread,(void*)&b);
    if(ret1 && ret2) {
        cout << "Create pthread error!" << endl;
        return 1;
    }
    pthread_join(id1, NULL);
    pthread_join(id2,NULL);
    return 0;
    */
}
