#ifndef MYPAIR_H
#define MYPAIR_H

using namespace std;

template <typename T1,typename T2>
struct pair {
    //memeber
    T1 first;
    T2 second;
    //function
    pair():first(),second(){}
    pair(const T1 val1,const T2 val2):first(val1),second(val2){}      //值初始化
    pair(T1&& rval1,T2&& rval2){            //move initialize
        first = forward<T1>(rval1);
        second = forward<T2>(rval2);
    }

    pair(const pair<T1,T2>& p):first(p.first),second(p.second){}
    pair(pair<T1,T2>&& _p) {
        first = forward<T1>(_p.first);
        second = forward<T2>(_p.second);
    }

    pair<T1,T2>& operator=(const pair<T1,T2>& p) {
        first = p.first;
        second = p.second;
        return p;
    }                           //将p的值赋值给*this
    pair<T1,T2>& operator=(pair<T1,T2>&& _p) {
        first = forward<T1>(_p.first);
        second = forward<T2>(_p.second);
        return *this;
    }
};

/*typedef class F{} 0;
typedef calss S{} 1;
template <typename T1,typename T2>
T1 get(const pair<T1,T2>& p) {
    if(typeid(F).name = 0)
        return p.first;
    else if(typeif(S) = 1)
        return p.second;
    else
        return 0;
}*/

#endif // MYPAIR_H
