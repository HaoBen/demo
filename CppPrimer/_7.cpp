#include "_7.h"

using namespace std;

float helper_7_1(float a,float b) {
    return 2.0*a*b/(a+b);
}
void _7_1() {
    float a,b;
    cout<<"Enter two numbers: ";
    while(cin>>a>>b && a != 0 && b != 0) {
        cout<<"harmonic mean: "<<helper_7_1(a,b)<<endl;
        cout<<"Enter two numbers: ";
    }
    cout<<"Bye!"<<endl;
}
//----------------------------------------------
int helper_7_2_input(float grades[],int count) {
    int i;
    cout<<"Please enter grades(max 10): ";
    for(i = 0;i < count;++i) {
        if(!(cin>>grades[i])) {
            break;
        }
    }
    cin.clear();
    return i;
}
void helper_7_2_display(float grades[],int count) {
    cout<<"All Grades: ";
    for(int i = 0;i < count;++i) {
        cout<<grades[i]<<" ";
    }
    cout<<endl;
}
float helper_7_2_average(float grades[],int count) {
    float res = 0;
    for(int i = 0;i < count;++i) {
        res += grades[i];
    }
    return res/count;
}
void _7_2() {
    float grades[10];
    int count = helper_7_2_input(grades,10);
    helper_7_2_display(grades,count);
    cout<<"Average Grade: "<<helper_7_2_average(grades,count)<<endl;
}
//---------------------------------------------------
void helper_7_3_a(box b) {
    cout<<"Maker: "<<b.maker<<endl;
    cout<<"Height: "<<b.height<<endl;
    cout<<"Width: "<<b.width<<endl;
    cout<<"Length: "<<b.length<<endl;
    cout<<"Volume: "<<b.volume<<endl;
}
void helper_7_3_b(box* pb) {
    pb->volume = pb->height * pb->width * pb->length;
}
void _7_3() {
    box b = {"I dont know",1.5,2.5,1.4};
    helper_7_3_b(&b);
    helper_7_3_a(b);
}
//-------------------------------------------------------
int helper_7_5(int n) {
    if(n == 0 || n == 1) {
        return 1;
    } else {
        return n*helper_7_5(n-1);
    }
}
void _7_5() {
    int n;
    while(cin>>n && n >= 0) {
        cout<<n<<"! = "<<helper_7_5(n)<<endl;
    }
    cout<<"Bye!"<<endl;
}
//-----------------------------------------------------
int helper_7_6_fill_array(double nums[],int size) {
    cout<<"Please enter most "<<size<<" double numbers: ";
    int i;
    for(i = 0;i < size;++i) {
        if(!(cin>>nums[i])) {
            break;
        }
    }
    cin.clear();
    return i;
}
void helper_7_6_show_array(double nums[],int count) {
    cout<<"All numbers: ";
    for(int i = 0;i < count;++i) {
        cout<<nums[i]<<" ";
    }
    cout<<endl;
}
void helper_7_6_reverse_array(double nums[], int count) {
    int start = 0;
    int end = count-1;
    double tmp;
    while(start < end) {
        tmp = nums[start];
        nums[start] = nums[end];
        nums[end] = tmp;
        ++start;
        --end;
    }
}
void _7_6() {
    double nums[10];
    int count = helper_7_6_fill_array(nums,10);
    helper_7_6_show_array(nums,count);
    helper_7_6_reverse_array(nums+1,count-2);
    helper_7_6_show_array(nums,count);
}
//------------------------------------------------------------
double* helper_7_7_fill_array(double* nums,int size) {
    cout<<"Please enter most "<<size<<" double numbers: ";
    int i;
    for(i = 0;i < size;++i) {
        if(!(cin>>nums[i])) {
            break;
        }
    }
    cin.clear();
    return &nums[i-1];
}
void helper_7_7_show_array(double *begin,double* end) {
    cout<<"All numbers: ";
    do {
        cout<<*begin<<" ";
        ++begin;
    } while(begin != end);
    cout<<*end<<endl;
}
void helper_7_7_reverse_array(double *begin,double* end) {
    double tmp;
    while(begin < end) {
        tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
        --end;
    }
}
void _7_7() {
    double nums[10];
    double* end = helper_7_7_fill_array(nums,10);
    helper_7_7_show_array(nums,end);
    helper_7_7_reverse_array(nums+1,end-1);
    helper_7_7_show_array(nums,end);
}
//-------------------------------------------------
double helper_7_9_calculate(double a,double b,double (*pf)(double,double)) {
    return pf(a,b);
}
double helper_7_9_add(double a,double b) {
    return a+b;
}
double helper_7_9_sub(double a,double b) {
    return a-b;
}
double helper_7_9_mul(double a,double b) {
    return a*b;
}
double helper_7_9_div(double a,double b) {
    return a/b;
}
void _7_9() {
    char op[4] = {'+','-','*','/'};
    double (*pf[4]) (double,double) = {helper_7_9_add,helper_7_9_sub,helper_7_9_mul,helper_7_9_div};
    double a,b;
    while(1) {
        cout<<"Enter two numbers: ";
        if(!(cin>>a>>b)) {
            break;
        }
        for(int i = 0;i < 4;++i) {
            cout<<"\t"<<a<<op[i]<<b<<" = "<<helper_7_9_calculate(a,b,pf[i])<<endl;
        }
    }
}
