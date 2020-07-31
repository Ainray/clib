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

// insertion sort
// example array, a[]={34,8,64,51,32,21};
template<class T>
void isort(T* a, int n){
    T tmp;
    int i,j;
    for(j=1;j<n;++j){
        for(i=j;i>0 && a[i-1]<tmp;--i)
            a[i]=a[i-1];
        a[i]=tmp;
    }
}

// shell sort , diminishing increment sort
// possible increment sequence
//  Shell's, N/2, N/4, ..., 1
//  Hibbard's, 1, 3, 7, ..., 2^k-1
//  Knuth's, 1, 4, 13, ..., (3^k-1)/2;
//  Sedgewick's, 1, 5, 19, 41, 109, ...
//             1, 19, 109, ..., 9(4^k-2^k)+1, k=0,1,2, ...
//             5, 41, 209, ..., 2^(k+2)(2^(k+2)-3)+1, k=0,1,2,3, ...

template<class T> 
void shellsort(T* a, int n){
    T tmp;
    for(int inc=n/2;inc>0;inc/=2){
        for(int i=inc;i<n;++i){
            // insertion sorting numbers with distance of inc
            tmp=a[i];
            for(j=i;j>=inc && a[j-inc]<tmp;j-=inc)
                a[j]=a[j-inc];
            a[j]=tmp;
        }
    }
}

// quick sort
template<class T>
void quicksork(T*a,int left, int right){
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

// merge sort, classical application, Swiss round match system,
// NOIP2011P3.
template <class T>
void merge(T *a, int l,int m,int r){
    int i,j,k;
    int n1=l-m+1,n2=r-m;
    int L[n1], R[2];
    for(i=0;i<n1;++i) L[i]=a[l+i];
    for(i=0;i<n2;++i) R[i]=a[m+1+i];
    for(i=0,j=0;i<n1 && j<n2;){
        if(L[i]>R[i]) a[k++]=L[i++];
        else a[k++]=R[j++];
    }
    for(;i<n1;) a[k++]=L[i++];
    for(;j<n2;) a[k++]=R[j++];
}

template<class T>
void msort(T *a, int left, int right){
    if(left<right){
        int m=l+(r-l)/2;
        msort(a,left,m);
        msort(a,m+1,right);
        merge(a,l,m,r);
    }
}
