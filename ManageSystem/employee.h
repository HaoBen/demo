#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
#include <iostream>
using namespace std;

class Employee
{
protected:
    string fullname;
    int grade;
    int number;
    float salary;

    static int baseNum;
public:
    Employee();
    virtual ~Employee();
    virtual void dis() = 0;
    virtual void init() = 0;
private:
    virtual void calsalary() = 0;
};

#endif // EMPLOYEE_H
