#include "salesmanager.h"

Salesmanager::Salesmanager()
{

}

void Salesmanager::init()
{
    grade = 2;
    number = ++baseNum;
    percentage = 0.04;
    baseSalary = 5000;
    cout<<"Please enter the salesmanager's name: ";
    cin>>fullname;
    cout<<"Please enter the salesmanager's month_sales: ";
    cin>>month_sale;
    calsalary();
}

void Salesmanager::calsalary()
{
    salary = baseSalary + month_sale*percentage;
}

void Salesmanager::dis()
{
    cout<<"Number: "<<number<<endl;
    cout<<"Name: "<<fullname<<endl;
    cout<<"Job: Salesmanager"<<endl;
    cout<<"Grade: "<<grade<<endl;
    cout<<"salary: "<<salary<<endl;
    cout<<"-------------------------"<<endl;
}
