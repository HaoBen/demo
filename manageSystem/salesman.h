#ifndef SALESMAN_H
#define SALESMAN_H
#include "employee.h"

class Salesman:public Employee
{
private:
    float percentage;
    float month_sale;
    void calsalary();
public:
    Salesman();
    void init();

    void dis();
};

#endif // SALESMAN_H
