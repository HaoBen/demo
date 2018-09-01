#include "technician.h"

Technician::Technician()
{
}

void Technician::init()
{
    grade = 3;
    hour_salary = 35.0;
    cout<<"Please Enter the techbician's name: ";
    cin>>fullname;
    cout<<"please Enter his work hours: ";
    cin>>work_hours;
    calsalary();
    number = ++baseNum;
}

void Technician::calsalary()
{
    salary = work_hours*hour_salary;
}

void Technician::dis()
{
    cout<<"Number: "<<number<<endl;
    cout<<"Name: "<<fullname<<endl;
    cout<<"Job: Technician"<<endl;
    cout<<"Grade: "<<grade<<endl;
    cout<<"salary: "<<salary<<endl;
    cout<<"-------------------------"<<endl;
}


