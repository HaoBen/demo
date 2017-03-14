#ifndef TECHNICIAN_H
#define TECHNICIAN_H
#include "employee.h"

class Technician:public Employee
{   
public:
    Technician();
    void dis();

    void init();
private:
    int work_hours;
    float hour_salary;
    void calsalary();
};

#endif // TECHNICIAN_H
