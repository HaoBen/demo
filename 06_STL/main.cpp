//------------------------序列式容器------------------------------------
#if 0
//stl/vector1.cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> coll;           //vector container for integer elements

    //append elements with values 1 to 6
    for(int i = 0;i <= 6;i++) {
        coll.push_back(i);
    }

    //print all elements followed by a space
    for(int i = 0;i < coll.size();i++) {
        cout<<coll[i]<<" ";
    }
    cout<<endl;
}
#endif

#if 0
//stl/deque1.cpp
#include <deque>
#include <iostream>
using namespace std;

int main() {
    deque<float> coll;                      //deque container for float-point elements

    //insert elements from 1.1 to 6.6 each at the front
    for(int i = 1;i <= 6;i++) {
        coll.push_front(i*1.1);
    }

    //print all elements followed by space
    for(int i = 0;i < coll.size();i++) {
        cout<<coll[i]<<" ";
    }
    cout<<endl;
}
#endif


#if 0
//stl/array.cpp
#include <iostream>
#include <string>
#include <array>
using namespace std;

int main() {
    //array container with 5 string elements
    array<string,5> coll = {"hello","world"};

    //print each element with its index on a line
    for(int i = 0;i < coll.size();i++) {
        cout<<i<<": "<<coll[i]<<endl;
    }
}
#endif


#if 0
#include <list>
#include <iostream>
using namespace std;

template <typename T>
void printElements(const T& coll) {
    for(const auto& elem : coll) {
        cout<<elem<<endl;
        //elem = '@';
    }
}

int main() {
    list<char> coll;            //list container for char elements

    //append elements from 'a' to 'z'
    for(char c = 'a';c <= 'z';c++) {
        coll.push_back(c);
    }
    printElements(coll);
    //print all elements
    //use range-based for loop
    for(auto& elem : coll) {
        cout<<elem<<' ';
    }
    cout<<endl;
}
#endif

#if 0
//stl/list2.cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list <char> coll;           //list container for character elements

    //append elements from 'a' to 'z'
    for(char c = 'a';c <= 'z';c++) {
        coll.push_back(c);
    }

    //print all elements
    //while there are elements
    //print and remove the first element
    while(!coll.empty()) {
        cout<<coll.front()<<' ';
        coll.pop_front();
    }
    cout<<endl;
    cout<<coll.size()<<endl;
}
#endif

#if 0
#include <forward_list>
#include <iostream>
using namespace  std;

int main() {
    //create forward_list container for some prime elements
    forward_list<int> coll = {2,3,5,7,11,13,17};

    //resize two times
    //-note:poor performance
    coll.resize(9);
    coll.resize(10,99);

    //print all elements:
    for(auto elem : coll) {
        cout<<elem<<' ';
    }
    cout<<endl;
}
#endif

//--------------华--丽--的--分--割--线-----------------------------------

//--------------------关联式容器-----------------------------------
#if 0
//stl/mutiset1.cpp
#include <set>
#include <string>
#include <iostream>
using namespace std;

int main() {
    multiset<string> cities {
        "London","New York","Mosco","Chicago","Toronto","Paris"
    };

    //print each element:
    for(const auto& elem : cities) {
        cout<<elem<<" ";
    }
    cout<<endl;

    //insert additional values:
    cities.insert({"Beijing","Shanghai","Nanjing","Huaibei"});

    //print each element
    for(const auto& elem : cities) {
        cout<<elem<<" ";
    }
    cout<<endl;

}
#endif

#if 0
//stl/multimap1.cpp
#include <map>                        //------------------------------
#include <string>                     //-----mutimap-----------------
#include <iostream>                  //------可用作字典----------------
using namespace std;                //------------------------------

int main() {
    multimap<int,string> coll;      //map container for int/string values

    //insert some elements in arbitrary order
    // -a value with key 1 gets inserted twice
    coll = { {5,"tagged"},
             {1,"this"},
             {2,"a"},
             {4,"of"},
             {6,"strings"},
             {1,"is"},
             {3,"multimap"}
           };
    //print all elements
    //-element member second is value
    for(auto elem : coll) {
        cout<<elem.second<<" ";
    }
    cout<<endl;
}
#endif

//-----------------分割线-----------------------------

//-----------------无序容器---------------------------
#if 0
//stl/unordmultiset1.cpp
#include <unordered_set>
#include <string>
#include <iostream>
using namespace std;

int main() {
    unordered_multiset<string> cities {
        "London","New York","Paris","Tokyo","Beijing","Nanjing"
    };

    //print each element
    for(const auto& elem : cities) {
        cout<<elem<<" ";
    }
    cout<<endl;

    //insert addtioal element:
    cities.insert({"Huaibei","Hefei","Mosco","Munich"});

    //print all elements
    for(const auto& elem : cities) {
        cout<<elem<<" ";
    }
    cout<<endl;
}
#endif

//#if 0
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

int main() {
    unordered_multimap<string,double> coll { {"tim",9.9},
                                             {"struppi",11.77},
                                           };

    //square the value of each element:
    for(pair<const string,double>& elem : coll) {
        elem.second *= elem.second;
    }
    coll.insert({"C++",100});

    //print each element(key and value)
    for(const auto& elem : coll) {
        cout<<elem.first<<" : "<<elem.second<<endl;
    }
}





























