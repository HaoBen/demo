#include "_6.h"

using namespace std;

void _6_1() {
    char ch;
    while(cin.get(ch) && ch != '@') {
        if(!isdigit(ch)) {
            if(isupper(ch)) ch = 'a'+ch-'A';
            else if(islower(ch)) ch = 'A'+ch-'a';
            cout<<ch;
        }
    }
}

void _6_2() {
    double donations[10];
    double sum = 0;
    double average = 0;
    int i = 0;
    for(i = 0;i < 10;++i) {
        if(cin>>donations[i]) {
            sum += donations[i];
        } else {
            break;
        }
    }
    average = sum / i;
    int count = 0;
    for(int j = 0;j < i;++j) {
        if(average-donations[j] < 0) ++count;
    }
    cout<<"Average: "<<average<<endl;
    cout<<"Number of bigger then average: "<<count<<endl;
}

void _6_3() {
    char ch;
    cout<<"Please enter one of the following choices:"<<endl;
    cout<<"c) carnivore\t\tp) pianist"<<endl;
    cout<<"t) tree\t\t\tg) game"<<endl;
    cin>>ch;
    while(ch != 'c' && ch != 'g' && ch != 'p' && ch != 't') {
        cout<<"Please enter c,p,t or g: ";
        cin>>ch;
    }
    switch (ch) {
    case 'c':
        cout<<"Carnivore was choosed"<<endl;
        break;
    case 'p':
        cout<<"Pianist was choosed"<<endl;
        break;
    case 't':
        cout<<"Tree was choosed"<<endl;
        break;
    case 'g':
        cout<<"Game was choosed"<<endl;
        break;
    default:
        break;
    }
}

void _6_4() {
    bop members[5] = {
        {"ding hao","a","dsad",0},
        {"ding hao yan","b","fsadsad",1},
        {"li kaifu","c","dfsafsad",2},
        {"alice","d","dsssad",0},
        {"David","a","dddddddsad",2}
    };
    char ch;
    cout<<"Benevolent Order Of Programmers Report"<<endl;
    cout<<"a. display by name         b. display by title"<<endl;
    cout<<"c. display by bopname   d. display by preference"<<endl;
    cout<<"q. quit"<<endl;
    do{
        cout<<"Enter your choice: "<<endl;
        cin>>ch;
        while(ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'q') {
            cout<<"Enter your choice: "<<endl;
            cin>>ch;
        }
        if(ch == 'q') {
            cout<<"Bye!"<<endl;
            break;
        }
        switch (ch) {
        case 'a':
            for(int i = 0;i < 5;++i) {
                cout<<members[i].fullname<<endl;
            }
            break;
        case 'b':
            for(int i = 0;i < 5;++i) {
                cout<<members[i].title<<endl;
            }
            break;
        case 'c':
            for(int i = 0;i < 5;++i) {
                cout<<members[i].bopname<<endl;
            }
            break;
        case 'd':
            for(int i = 0;i < 5;++i) {
                if(members[i].preference == 0) {
                    cout<<members[i].fullname<<endl;
                } else if(members[i].preference == 1) {
                    cout<<members[i].title<<endl;
                } else if(members[i].preference == 2) {
                    cout<<members[i].bopname<<endl;
                } else {
                    cout<<members[i].fullname<<endl;
                }
            }
            break;
        default:
            break;
        }
    } while(1);
}

void _6_5() {
    double salary;
    while(1) {
        cout<<"Enter your salary: ";
        if(cin>>salary && salary > 0) {
            double sax = 0;
            if(salary <= 5000) {
                sax = 0;
            } else if(salary > 5000 && salary <= 15000) {
                sax =( sax-5000)*0.1;
            } else if(salary > 15000 && salary <= 35000) {
                sax = 10000 * 0.1 + (salary-15000)*0.15;
            } else {
                sax = 10000*0.1 + 20000*0.15 + (salary-35000)*0.2;
            }
            cout<<"You have to pay $"<<sax<<" for the sax\n";
        } else {
            cout<<"Bye!"<<endl;
            break;
        }
    }
}

void _6_6() {
    int n;
    ifstream in;
    in.open("E:\\workspace\\CppPrimer\\6_9.txt");
    if(!in.is_open()) {
        cout<<"Failed to open file!!!"<<endl;
        return;
    }
    in>>n;in.get();
    Patron* patrons = new Patron[n];
    for(int i = 0;i < n;++i) {
        getline(in,patrons[i].name);
        in>>patrons[i].donation;in.get();
    }
    in.close();     //输入读取完毕

    int count = 0;
    cout<<"Grand Patrons:\n";
    for(int i = 0;i < n;++i) {
        if(patrons[i].donation > 10000) {
            cout<<'\t'<<patrons[i].name<<"-----"<<patrons[i].donation<<endl;
            ++count;
        }
    }
    if(count == 0) {
        cout<<"\tNone"<<endl;
    }

    count = 0;
    cout<<"Patrons:\n";
    for(int i = 0;i < n;++i) {
        if(patrons[i].donation <= 10000) {
            cout<<'\t'<<patrons[i].name<<"-----"<<patrons[i].donation<<endl;
            ++count;
        }
    }
    if(count == 0) {
        cout<<"\tNone"<<endl;
    }
    delete[] patrons;
}

void _6_7() {
    char word[20];
    int vowels = 0;
    int consonants = 0;
    int others = 0;
    cout<<"Enter words (q to quit):\n";
    while(cin>>word && strcmp(word,"q") != 0) {
        if(isalpha(word[0])) {
            switch (word[0]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                ++vowels;
                break;
            default:
                ++consonants;
                break;
            }
        } else {
            ++others;
        }
    }
    cout<<vowels<<" words beginning with vowels\n";
    cout<<consonants<<" words beginning with consonants\n";
    cout<<others<<" others\n";
}

void _6_8() {
    ifstream in;
    in.open("E:\\workspace\\CppPrimer\\6_8.txt");
    if(!in.is_open()) {
        cout<<"Falied to open file!!!"<<endl;
        return;
    }
    int count = 0;
    char ch;
    while(in.get(ch)) {
        ++count;
    }
    in.close();
    cout<<count<<endl;
}
