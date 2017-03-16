#ifndef MYPAIR_H
#define MYPAIR_H

using namespace std;
namespace MYPAIR {
template <typename T1,typename T2>
struct pair {
    //memeber
    T1 first;
    T2 second;
    //function
    pair():first(),second(){}
    pair(const T1 val1,const T2 val2):first(val1),second(val2){}      //值初始化
    //template <typename U,typename V>
    /*pair(U&& rval1,V&& rval2){            //move initialize
        first = forward<U&>(rval1);
        second = forward<V&>(rval2);
    }*/

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

    bool operator==(const pair<T1,T2>& p) const {
        return (first == p.first && second == p.second);
    }
    bool operator!=(const pair<T1,T2>& p) const {
        return !(*this == p);
    }
    friend bool operator>(const pair<T1,T2>& left,const pair<T1,T2>& right) {
        if(left.first > right.first)
            return true;
        else if(left.first == right.first)
            return (left.second > right.second);
        else
            return false;
    }
    friend bool operator<(const pair<T1,T2>& left,const pair<T1,T2>& right) {
        return (right > left);
    }
    friend bool operator>=(const pair<T1,T2>& left,const pair<T1,T2>& right) {
        return !(left<right);
    }
    friend bool operator<=(const pair<T1,T2>& left,const pair<T1,T2>& right) {
        return !(left>right);
    }

    bool swap(pair<T1,T2>& p) {
        if(pair<T1,T2> temp = p) {
            p.first = first;
            p.second = second;
            first = temp.first;
            second = temp.second;
            return true;
        }
        else
            return false;
    }
    friend ostream& operator<<(ostream& os,const pair<T1,T2>& p) {
        os<<"["<<p.first<<","<<p.second<<"]";
        return os;
    }
};
template<typename T1,typename T2>
bool swap(struct pair<T1,T2> & left,struct pair<T1,T2> & right){
    if(left.swap(right))
        return true;
    else
        return false;
}
template<typename T1,typename T2>
pair<T1,T2> make_pair(T1 val1,T2 val2) {
    return pair<T1,T2>(val1,val2);
}

}

#endif // MYPAIR_H
