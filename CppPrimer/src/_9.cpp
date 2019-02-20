#include "_9.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void setgolf(golf &g, const char *name, int hc) {
    g.handicap = hc;
    if(strlen(name) < Len) {
        strcpy(g.fullname,name);
    } else {
        strncpy(g.fullname,name,Len-1);
    }
}
int setgolf(golf &g) {
    cout<<"Please enter fullname: ";
    cin.get(g.fullname,Len);
    if(!g.fullname[0]) {
        cin.sync();
        cin.clear();
        return 0;
    }       //如果输入了空串，则清除输入缓冲区并返回
    while(cin.get() != '\n'){
        ;
    }
    cout<<"Please enter handicap: ";
    cin>>g.handicap;
    cin.sync();
    cin.clear();        //防止本次的输入对下一次的输入产生影响，因此返回前清除输入缓冲区
    return 1;
}
void handicap(golf &g, int hc) {
    g.handicap = hc;
}
void showgolf(const golf &g) {
    cout<<"FULLNAME: "<<g.fullname<<endl;
    cout<<"HANDICAP: "<<g.handicap<<endl;
}
void _9_1() {
    golf ann[5];
    int i;
    for(i = 0;i < 5;++i) {
        if(!setgolf(ann[i])) {
            break;
        }
    }
    cout<<"---------------INPUT DONE------------------------\n";
    for(int j = 0;j < i;++j) {
        showgolf(ann[j]);
    }
}
//------------------------------------------------------------------------------
void strcount(const string &str) {
    static int total = 0;
    cout<<"\""<<str<<"\" contains ";
    total += str.length();
    cout<<str.length()<<" characters\n";
    cout<<total<<" characters total\n";
}
void _9_2() {
    string str;
    while(cin) {
        cout<<"Enter a line (empty to quit): \n";
        getline(cin,str);
        if(str == "") break;
        strcount(str);
    }
    cout<<"Bye!"<<endl;
}
//-----------------------------------------------------------------
void SALES::setSales(Sales &s, const double ar[], int n) {
    int i;
    double sum = 0;
    s.max = s.min = ar[0];
    for(i = 0;i < n && i < 4;++i){
        s.sales[i] = ar[i];
        sum += ar[i];
        if(s.max < ar[i]) s.max = ar[i];
        if(s.min > ar[i]) s.min = ar[i];
    }
    for(int j = i; j < 4;++j) {
        if(s.min > 0) s.min = 0;
        s.sales[j] = 0;
    }
    s.average = sum / QUARTERS;
}
void SALES::setSales(Sales &s) {
    double sum = 0;
    cout<<"Please enter sales data(most of 4): ";
    for(int i = 0;i < QUARTERS;++i) {
        cin>>s.sales[i];
        if(i == 0) {
            s.max = s.min = s.sales[i];
        } else {
            if(s.max < s.sales[i]) s.max = s.sales[i];
            if(s.min > s.sales[i]) s.min = s.sales[i];
        }
        sum += s.sales[i];
    }
    s.average = sum / QUARTERS;
}
void SALES::showSales(const Sales &s) {
    cout<<"All sales: ";
    for(int i = 0;i < QUARTERS;++i) {
        cout<<s.sales[i];
        if(i < QUARTERS-1) cout<<" | ";
        else cout<<endl;
    }
    cout<<"Max: "<<s.max<<endl;
    cout<<"Min: "<<s.min<<endl;
    cout<<"Average: "<<s.average<<endl;
}
void _9_4() {
    using namespace SALES;
    double da[] = {1,2,3,4};
    Sales s;
    setSales(s,da,4);
    showSales(s);
    cout<<"-------------------------\n";
    setSales(s);
    showSales(s);
}
