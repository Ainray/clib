#include "sort.h"

// selection sort
template<class T>
void ssort(T *a,int n){
    int i,j,k;
    T tmp;
    for(i=0;i<n-1;++i){
        k=i;
        for(j=i;j<n;++j)
            if(a[k]<a[j]) k=j;
        if(k!=i){tmp=a[k];a[k]=a[i];a[i]=tmp;}
    }
}

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
