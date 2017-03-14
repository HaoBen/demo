#include "salesman.h"


Salesman::Salesman()
{

}

void Salesman::init()
{
    grade = 4;
    number = ++baseNum;
    percentage = 0.05;
    cout<<"Please enter the salesman's name: ";
    cin>>fullname;
    cout<<"Please enter the salesman's month_sales: ";
    cin>>month_sale;
    calsalary();

}

void Salesman::calsalary()
{
    salary = month_sale*percentage;
}

void Salesman::dis()
{
    cout<<"Number: "<<number<<endl;
    cout<<"Name: "<<fullname<<endl;
    cout<<"Job: Salesman"<<endl;
    cout<<"Grade: "<<grade<<endl;
    cout<<"salary: "<<salary<<endl;
    cout<<"-------------------------"<<endl;
}
