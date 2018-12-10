#include "_8.h"

using namespace std;

void setCandyBar(CandyBar8& candy,char* brand,double weight,int calorie) {
    strcpy(candy.brand,brand)   ;
    candy.weight = weight;
    candy.calorie = calorie;
}
void showCandyBar(const CandyBar8& candy) {
    cout<<"Brand: "<<candy.brand<<endl;
    cout<<"Weight: "<<candy.weight<<endl;
    cout<<"Calorie: "<<candy.calorie<<endl;
}
void _8_2() {
    CandyBar8 c;
    char brand[] = "Millennium Munch";
    setCandyBar(c,brand,2.85,350);
    showCandyBar(c);
}
//------------------------------------------------------------
void helper_8_3(string& str) {
    for(size_t i = 0;i < str.length();++i) {
        str[i] = toupper(str[i]);
    }
}
void _8_3() {
    string str;
    do {
        cout<<"Enter a string (q to quit): ";
        getline(cin,str);
        if(str == "q") {
            cout<<"Bye.\n";
            break;
        } else {
            helper_8_3(str);
            cout<<str<<endl;
        }
    } while(1);
}
//-----------------------------------------------
void set(stringgy& beany,const char* str) {
    int len = strlen(str);
    char * tmp = new char[len];
    strcpy(tmp,str);
    beany.str = tmp;
    beany.ct = len;
}
void show(stringgy& beany,int n = 1) {
    if(n <= 1) {
        cout<<beany.str<<endl;
    } else {
        for(int i = 0;i < n;++i) {
            cout<<beany.str<<endl;
        }
    }
}
void show(const char* str,int n = 1) {
    if(n <= 1) {
        cout<<str<<endl;
    } else {
        for(int i = 0;i < n;++i) {
            cout<<str<<endl;
        }
    }
}
void _8_4() {
    stringgy beany;
    char testing[] = "Reality isn't what it used to be. ";
    set(beany,testing);
    show(beany);
    show(beany,2);
    testing[0] = 'D';
    testing[1] = 'u';
    show(testing);
    show(testing,3);
    show("Done! ");
    delete[] beany.str;
}
//--------------------------------------------------------
template<typename T>
T max5(T array[]) {
    T res = array[0];
    for(int i = 0;i < 5;++i) {
        if(res < array[i]) {
            res = array[i];
        }
    }
    return res;
}
void _8_5() {
    int ia[] = {1,2,3,4,5};
    double da[] = {5.5,4.4,3.3,2.2,1.1};
    cout<<max5(ia)<<" "<<max5(da)<<endl;
}
//-----------------------------------------------------------
template<typename T>
T maxn(T a[],size_t n) {
    T res = a[0];
    for(size_t i = 0;i < n;++i) {
        if(a[i] > res) {
            res = a[i];
        }
    }
    return res;
}
template<>
char* maxn(char * a[],size_t n) {
    char* res = a[0];
    for(size_t i = 0;i < n;++i) {
        if(strlen(res) < strlen(a[i])) {
            res = a[i];
        }
    }
    return res;
}
void _8_6() {
    int ia[] = {1,2,3,4,5,6};
    double da[] = {1.1,3.3,5.5,7.7};
    char *ca[3] = {
        "I",
        "love",
        "china"
    };
    cout<<maxn(ia,6)<<" "<<maxn(da,4)<<" "<<maxn(ca,3)<<endl;
}
