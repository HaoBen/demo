#include "server.h"
#include <iostream>

using namespace std;

int main(int argc,char *argv[]) {
    Server server(argc,argv);
    server.startup();
}
