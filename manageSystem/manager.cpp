#include "manager.h"

Manager::Manager()
{

}

void Manager::init()
{
    grade = 1;
    number = ++baseNum;
    cout<<"Please Enter the manager's name: ";
    cin>>fullname;
    cout<<"Please enter manager's baseSalary: ";
    cin>>baseSalary;
    calsalary();
}

void Manager::dis()
{
    cout<<"Number: "<<number<<endl;
    cout<<"Name: "<<fullname<<endl;
    cout<<"Job: Manager"<<endl;
    cout<<"Grade: "<<grade<<endl;
    cout<<"salary: "<<salary<<endl;
    cout<<"-------------------------"<<endl;
}

void Manager::calsalary()
{
    salary = baseSalary;
}
