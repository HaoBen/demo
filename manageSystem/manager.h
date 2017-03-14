#ifndef MANAGER_H
#define MANAGER_H
#include "employee.h"

class Manager:public Employee
{
private:
    float baseSalary;
    void calsalary();
public:
    Manager();
    void init();
    void dis();

};

#endif // MANAGER_H
