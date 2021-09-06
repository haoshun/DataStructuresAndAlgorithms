//
//  HS_InsertionSort.c
//  Sorts
//
//  Created by 郝 源顺 on 2018/11/15.
//  Copyright © 2018年 Shun. All rights reserved.
//

#include "HS_InsertionSort.h"

//#define HS_SWAP


#ifdef HS_SWAP
//从关键值key往前遍历 边遍历边换位置
void insertionSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if(!nums || first >=end)
        return;

    for(int i = first+1 ; i <= end ; ++i)
        for(int j = i-1  ,  key = nums[i] ; j >= 0 ; --j)
            if (key < nums[j])
                hs_swap(nums + j, nums + j + 1);
}

#else

/*
 
算法导论（第三版）2.1章
 */
void insertionSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if(!nums || first >=end)
        return;
    
    HS_SIZE len = end - first + 1;
    for (int i = first + 1 , key , j ; i < len; ++i)
    {
        for(key = nums[i], j = i - 1 ; j >= 0 ; --j)
        {
            if(key < nums[j])
                nums[j + 1] = nums[j];
            else
                break;
        }
        nums[j + 1] = key;
    }
}
    
#endif



void hs_insertionSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    insertionSort(nums, first, end);
}
