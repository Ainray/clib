#include<stdio.h>
void swap(double *a, int i, int j)
{
    double tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void qsort(double *a,int left, int right){
    int i,last;
    if(left>=right) return;
    last=left;
    swap(a,left, (left+right)/2);  //the center as partition element
    for(i=left+1;i<=right;++i)     //last will stop at element which
                                   //is less than the partition element
                                   //when the next larger element is
                                   //found, switch them, last is agian
                                   //move ahead together with i, with
                                   //distance of number of lesser
                                   //elements.
                                   //At last, i move the rightmost, last
                                   //with position which is proper to 
                                   //partition element.
        if(a[i]>a[left])
        {
            swap(a,++last,i);
        }
    swap(a,left,last);
    qsort(a,left,last-1);   // elements > partition element
    qsort(a,last+1,right);  // elements < partition element
}

int main()
{
    double a[]={3, 5, 2, 1,4};
    qsort(a, 0, 4);
}

