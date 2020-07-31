#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int weight2array(int *array, int length, int *limit, int weight);
int next_sameweight(int *array, int length, int *limit, int weight);
int next_permutation(int *array, int length, int *limit);
int next_permutation(int *array, int length);

int eleorder(int *array, int length, int *limit)
{
    int weightlimit=0;
    for(int i=0; i<length; ++i)
        weightlimit+=limit[i];

    int weight = 0;
    int cnt = 0;
    weight2array(array, length, limit, weight);
    while(weight <= weightlimit)
    {
        printf("%d, %d:", cnt++, weight);
        for(int i=0; i<length; ++i)
        {
            printf("%d%s", array[i], i<length-1?" ":"\n");
        }

        if(cnt > 14 )
            int a=1;

        if( next_permutation(array, length, limit) && 
                next_sameweight(array, length, limit, weight))
        {
            ++weight;
            if(weight>weightlimit)
                break;
            {
                weight2array(array, length, limit, weight);
            }
        }
    }
}
// <: -1, =:0, >:1
int comparearray(int *array1, int *array2, int length)
{
    int weight1 = 0, weight2 = 0, none1 = 0, none2 = 0;
    for(int i=0; i<length; ++i)
    {
        weight1 += array1[i];
        weight2 += array2[i];
        if(array1[i]>0)
            none1++;
        if(array2[i]>0)
            none2++;
    }
    if(weight1 < weight2)
        return -1;
    else if(weight1 > weight2)
        return 1;
    else
    {
        if(none1<none2)
            return 1;
        else if(none1>none2)
            return -1;
        else
        {
            for(int i=0; i<length; ++i)
            {
                if(array1[i]>array2[i])
                    return 1;
                else if(array1[i]<array2[i])
                    return -1;
            }
            return 0;
        }
    }
}

// get the least array with specified weight
int weight2array(int *array, int length, int *limit, int weight)
{
    int weightlimit=0;
    for(int i=0; i< length; ++i )
    {
        weightlimit += limit[i];
        array[i] = 0;
    }
    if(weight>weightlimit)
        return -1;

    int w=weight<length?weight:length;

    for(int i=0; i<length && i<weight; ++i)
    {
        array[length-1-i]=1;
    }

    while(w<weight)
    {
        for(int i=length-1; i>=0; --i)
        {
            if(array[i] <limit[i])
            {
                ++(array[i]);
                ++w;
                if(w>=weight)
                    break;
            }
        }
    }
    return 0;
}
// non-zero indicate no next array with same weight
int next_sameweight(int *array, int length, int *limit, int weight)
{
    int none, none0=0;
    for(int i=0; i<length; ++i)
    {
        if(array[i]>0)
            none0++;
    }
    for(int i=length-1; i>=0; --i)
    {
        if(array[i]<limit[i])
        {
            for(int j=0; j<length && j!=i; ++j) 
            {
                if(array[j]<=limit[j] && array[j]>0)
                {
                    ++array[i];
                    --array[j];

                    none=0;
                    for(int k=0; k<length;++k)
                    {
                        if(array[k]>0)
                            ++none;
                    }
                    if(none<none0)
                        return 0;
                }
            }
        } 
    }
    return -1;
}

int next_permutation(int *array, int length, int *limit)
{
    // limit check
    int state = 0;
    int *buf =(int *) calloc(length, sizeof(int));
    memcpy(buf, array, length*sizeof(int));
    while(!next_permutation(array, length))
    {
        state = 0;
        for(int i=0; i<length; ++i)
        {
            if(array[i]>limit[i])
            {
                state = 1;
                break;
            }
        }
        if(state == 0)
        {
            free(buf);
            return 0;
        }
    }
    memcpy(array, buf, length*sizeof(int));
    free(buf);
    return -1;
}

// next permutation
int next_permutation(int *array, int length)
{
	// Find non-increasing suffix
	if (length == 0)
		return -1;
	size_t i = length - 1;
	while (i > 0 && array[i - 1] >= array[i])
		i--;
	if (i == 0)
		return -1;
	
	// Find successor to pivot
	size_t j = length - 1;
	while (array[j] <= array[i - 1])
		j--;

	int temp = array[i - 1];

	array[i - 1] = array[j];
	array[j] = temp;
	
	// Reverse suffix
	j = length - 1;
	while (i < j) {
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
	return 0;
}
int main()
{
    const int length=3;
    int limit[]={1, 2, 2};
    int array[length];
    eleorder(array, length, limit);
}
