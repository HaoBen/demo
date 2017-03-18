//-----------------------迭------代-------------器
#if 0
//stl/listold.cpp
#include <list>
//#include <cctype>
#include <iostream>
using namespace std;

int main() {
    list<char> coll;       //list container for character elements

    //append elements from 'a' to 'z'
    for(char c = 'a'; c <= 'z';++c) {
        coll.push_back(c);
    }                                                        //-------------------------------------
                                                             //----注意：----------------------------
    //print all elements:                                    //若无特殊要求，一般使用前置递增式
    //iterate over all elements                              //因为后置式递增需要一个临时对象，它必须存放迭代器的原本位置并返回之
    list<char>::const_iterator pos;                          //---------------------------------------
    for(pos = coll.begin();pos != coll.end();++pos) {
        cout<<*pos<<' ';
    }
    //pos = coll.begin();
    cout<<*pos<<endl;
    cout<<endl;

    //toupper
    list<char>::iterator _pos;
    for(_pos = coll.begin();_pos != coll.end();++_pos) {
        *_pos = toupper(*_pos);
        cout<<*_pos<<' ';
    }
    //_pos = coll.begin();
    cout<<endl;
}



// for (auto pos = coll.begin();pos != coll.end();++pos)
// for(list<char>::const_iterator pos = coll.begin();pos != coll.end();++pos)
//使用auto的优点是使程序比较浓缩精简，且万一容器类型有所变化程序整体仍能保持较佳的健壮性
//缺点是迭代器丧失常量性，可能引发”计划外的赋值“风险
//为确保仍可使用常量迭代器，自C++11起容器提供cbegin和cend，返回cont：：const_iterator的对象
//改善方案应如下：
// for(auto pos  = coll.cbegin();pos != coll.cend();++pos)


//for(type elem : coll) {
//      ...
//  }

//等同于
// for(auto pos = coll.begin(),end = coll.end();pos != end;++pos) {
//      type elem = *pos;
// }

//可以解释为什么声明elem为一个constant constant reference 可以避免非必要复制
#endif

//----------------------------------------------------------------
//---关联式及无序容器的的更多实例
#if 0
//stl/set1.cpp
#include <set>
#include <iostream>
using namespace std;

int main() {
    //type of the collection
    typedef set<int> IntSet;

    IntSet coll;        //set container for int values

    //inset elements from 1 to 6 in arbitrary order
    //-note there are two calls of insert() with 1
    coll.insert(3);
    coll.insert(1);
    coll.insert(5);
    coll.insert(4);
    coll.insert(1);
    coll.insert(6);
    coll.insert(2);

    //print all elements
    //-iterate over all elemments
    IntSet::const_iterator pos;
    for(pos = coll.begin();pos != coll.end();++pos) {
        cout<<*pos<<' ';
    }
    cout<<endl;
}
#endif

#if 0
//stl/unordmultiset2.cpp
#include <unordered_set>
#include <iostream>
using namespace std;

int main() {
    //unordered multiset container for int values
    unordered_multiset<int> coll;

    //insert some elemments
    coll.insert({1,1,3,5,7,9,111,24,25,36});

    //print all elements
    for(const auto& elem : coll) {
        cout<<elem<<' ';
    }
    cout<<endl;

    //insert one more element
    coll.insert(25);

    //print all elements again
    for(const auto& elem : coll) {
        cout<<elem<<' ';
    }
    cout<<endl;

    //print all elements with iterator
    for(unordered_multiset<int>::const_iterator pos = coll.begin();pos != coll.end();++pos) {
        cout<<*pos<<' ';
    }
    cout<<endl;
}
#endif

#if 0
迭代器种类：
1.向前迭代器（Forward iterator）
2.双向迭代器（Bidirectional iterator）
3.随机访问迭代器（Random-acess iterator）
//or
·输入型迭代器
·输出型迭代器
#endif
