#include "sort.h"

// bubble sort

template<class T>
void bsort(T* a, int n){
    int i,j;
    T tmp;
    for(i=1;i<n;++i){
        for(j=0;j<n-i;++j){
            if(a[j]<a[j+1]){tmp=a[j];a[j]=a[j+1];a[j+1]=tmp;}
        }
    }
}
