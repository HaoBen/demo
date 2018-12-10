#include "_4.h"
#include <cstring>

using namespace std;

void _4_1() {
    string first_name,last_name;
    char grade;
    int age;
    cout<<"What is your first name?";
    getline(cin,first_name);
    cout<<"What is your last name?";
    getline(cin,last_name);
    cout<<"What letter grade do you deserve?";
    cin>>grade;
    cout<<"What is your age?";
    cin>>age;

    cout<<"Name: "<<first_name<<","<<last_name<<endl;
    cout<<"Grade: "<<grade<<endl;
    cout<<"Age: "<<age<<endl;
}

void _4_3() {
    char first_name[20];
    char last_name[40];
    cout<<"Enter Your first name: ";
    cin>>first_name;
    cout<<"Enter Your last name: ";
    cin>>last_name;
    int len = strlen(last_name);
    last_name[len] = ',';
    last_name[len+1] = 0;
    strcat(last_name,first_name);
    cout<<"Here is the information in a single string: "<<last_name<<endl;
}

void _4_4() {
    string first_name,last_name;
    cout<<"Enter Your first name: ";
    cin>>first_name;
    cout<<"Enter Your last name: ";
    cin>>last_name;
    last_name += ",";
    last_name += first_name;
    cout<<"Here is the information in a single string: "<<last_name<<endl;
}

void _4_5() {
    CandyBar snack = {"Mocha Munch",2.3,350};
    cout<<"Brand: "<<snack.brand<<endl;
    cout<<"Weight: "<<snack.weight<<endl;
    cout<<"Calorie: "<<snack.calorie<<endl;
}

void _4_6() {
    CandyBar snacks[3] = {
        {"Mocha Munch",2.3,350},
        {"Rabit",2.0,100},
        {"Albeth",2.4,200}
    };
    for(int i = 0;i < 3;++i) {
        cout<<"Brand: "<<snacks[i].brand<<endl;
        cout<<"Weight: "<<snacks[i].weight<<endl;
        cout<<"Calorie: "<<snacks[i].calorie<<endl;
    }
}

void _4_7() {
    Pizza piz;
    cout<<"Enter pizza's brand: ";
    getline(cin,piz.brand);
    cout<<"Enter pizza's diameter: ";
    cin>>piz.diameter;
    cout<<"Enter pizza's weight: ";
    cin>>piz.weight;
    cout<<"BRAND: "<<piz.brand<<endl;
    cout<<"DIAMETER: "<<piz.diameter<<endl;
    cout<<"WEIGHT:"<<piz.weight<<endl;
}

void _4_8() {
    Pizza* ppiz = new Pizza;
    cout<<"Enter pizza's diameter: ";
    cin>>ppiz->diameter;
    cout<<"Enter pizza's brand: ";
    cin.get();
    getline(cin,ppiz->brand);
    cout<<"Enter pizza's weight: ";
    cin>>ppiz->weight;
    cout<<"BRAND: "<<ppiz->brand<<endl;
    cout<<"DIAMETER: "<<ppiz->diameter<<endl;
    cout<<"WEIGHT:"<<ppiz->weight<<endl;
    delete ppiz;
}

void _4_9() {
    CandyBar* snacks = new CandyBar[3];
    snacks[0] = {"Mocha Munch",2.3,350};
    snacks[1] = {"Rabit",2.0,100};
    snacks[2] =  {"Albeth",2.4,200};
    for(int i = 0;i < 3;++i) {
        cout<<"Brand: "<<snacks[i].brand<<endl;
        cout<<"Weight: "<<snacks[i].weight<<endl;
        cout<<"Calorie: "<<snacks[i].calorie<<endl;
    }
    delete[] snacks;
}
