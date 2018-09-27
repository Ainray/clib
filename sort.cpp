#include "sort.h"

template <class T>
void swap(T *a, int i,int j){
    T tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
}

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

// quick sort
template<class T>
void qsork(T*a,int left, int right){
    int i,last;
    if(left>=right) return;
    last=left;
    swap(a,left, (left+right)/2);  //the center as partition element
    for(i=left+1;i<=right;++i)
        if(a[i]>a[left])
            swap(a,++last,i);
    swap(a,left,last);
    qsort(a,left,last-1);   // elements > partition element
    qsort(a,last+1,right);  // elements < partition element
}
