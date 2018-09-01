#ifndef SALESMANAGER_H
#define SALESMANAGER_H
#include "employee.h"

class Salesmanager:public Employee
{
private:
    float baseSalary;
    float percentage;
    float month_sale;
    void calsalary();
public:
    Salesmanager();
    void dis();
    void init();

};

#endif // SALESMANAGER_H
