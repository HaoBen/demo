#include "sort.h"
using namespace std;

template <typename T>
static void __swap(T& a,T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
void heapSort(vector<T> &v) {
    /* 建堆 */
    int len = v.size();
    for(int i = len/2-1;i >= 0;--i) {
        /* 堆调整过程 */
        int tempi = i;
        T temp = v[i];
        for(int k = tempi*2+1;k < len;k = 2*k+1) {
            if(k+1<len && v[k] < v[k+1]) ++k;
            if(v[k] > temp) {
                v[tempi] = v[k];
                tempi = k;
            } else {
                break;
            }
        }
        v[tempi] = temp;
    }

    /* 交换堆顶元素与末尾元素,并重新调整堆 */
    for(int j = len-1;j > 0;--j) {
        /* 交换 */
        __swap(v[0],v[j]);
        /* 从堆顶开始调整堆 */
        int tempi = 0;
        T temp = v[tempi];
        for(int k = tempi*2+1;k < j;k = 2*k+1) {
            if(k+1<j && v[k] < v[k+1]) ++k;
            if(v[k] > temp) {
                v[tempi] = v[k];
                tempi = k;
            } else {
                break;
            }
        }
        v[tempi] = temp;
    }
}
/* 显示实例化模板 */
void __heapSortTemplateInstantiation() {
    vector<int> tmp;
    heapSort(tmp);
}

