#include <iostream>
#include "manager.h"
#include "technician.h"
#include "salesman.h"
#include "salesmanager.h"
using namespace std;

int main(int argc, char *argv[])
{
    Employee* pe[4] = {new Manager(),new Salesman(),new Salesmanager,new Technician()};
    for(int i = 0;i<4;i++) {
        pe[i]->init();
        pe[i]->dis();
    }

    delete[] pe;
    return 0;
}
