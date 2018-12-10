#include "_5.h"

using namespace std;

void _5_1() {
    int a,b;
    cin>>a>>b;
    cout<<(b+a)*(b-a+1)/2<<endl;
}

void _5_2() {
    int sum = 0;
    cout<<"Current sum: "<<sum<<endl;
    int tmp;
    cout<<"Enter a num: ";
    cin>>tmp;
    while(tmp != 0) {
        sum += tmp;
        cout<<"Current sum: "<<sum<<endl;
        cout<<"Enter a num: ";
        cin>>tmp;
    }
}

void _5_3() {
    float Daphne = 100;
    float Cleo = 100;
    int year = 0;
    while(++year) {
        Daphne += 0.1*100;
        Cleo = 1.05 * Cleo;
        if(Cleo - Daphne > 0.001) {
            break;
        }
    }
    cout<<year<<" years later!!!!!!!!!!"<<endl;
    cout<<"Daphne: "<<Daphne<<endl;
    cout<<"Cleo: "<<Cleo<<endl;
}

void _5_4() {
    string month_name[12] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",
    };
    int sale_mount[3][12];
    for(int i = 0;i < 12;++i) {
        cout<<"Enter "<<month_name[i]<<"'s sales amount(1 2 3): ";
        cin>>sale_mount[0][i]>>sale_mount[1][i]>>sale_mount[2][i];
    }
    for(int i = 0;i < 3;++i) {
        cout<<"No. "<<i+1<<" Year:"<<endl;
        for(int j = 0;j < 12;++j) {
            cout<<"\t"<<month_name[j]<<" : "<<sale_mount[i][j]<<endl;
        }
    }
}

void _5_6() {
    int n;
    cout<<"How many cars do you wish to catalog? ";
    cin>>n;
    cin.get();
    car* cars = new car[n];
    for(int i = 0;i < n;++i) {
        cout<<"Car #"<<i+1<<":"<<endl;
        cout<<"Please enter the make: ";
        getline(cin,cars[i].brand);
        cout<<"Please enter the year make: ";
        cin>>cars[i].year_made;
        cin.get();
    }
    cout<<"Here is your collection:"<<endl;
    for(int i = 0;i < n;++i) {
        cout<<cars[i].year_made<<" "<<cars[i].brand<<endl;
    }
}

void _5_7() {
    cout<<"Enter words (to stop, type the word done): "<<endl;
    char words[100][25];
    char word[25];
    cin>>word;
    int count = 0;
    while(strcmp(word,"done") != 0) {
        ++count;
        cin>>word;
    }
    cout<<"You entered a total of "<<count<<" words."<<endl;
}

void _5_8() {
    cout<<"Enter words (to stop, type the word done): "<<endl;
    string words[100];
    string word;
    cin>>word;
    int count = 0;
    while(word != "done") {
        ++count;
        cin>>word;
    }
    cout<<"You entered a total of "<<count<<" words."<<endl;
}

void _5_9() {
    cout<<"Enter number of rows: ";
    int n;
    cin>>n;
    for(int i = 1;i <= n;++i) {
        int j;
        for(j = 1;j <= n-i;++j) {
            cout<<'.';
        }
        for(j = 1;j <= i;++j) {
            cout<<'*';
        }
        cout<<endl;
    }
}
