//
//  HS_MergeSort.c
//  Sorts
//
//  Created by 郝 源顺 on 2018/11/23.
//  Copyright © 2018年 Shun. All rights reserved.
//

#include "HS_MergeSort.h"

#define HS_RECURSION

void hs_merge(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX mid, HS_INDEX end)
{
    HS_SIZE l_len = mid - first + 1;
    
    HS_ELEMENT_TYPE* leftCopy = (HS_ELEMENT_TYPE*)malloc(sizeof(HS_ELEMENT_TYPE) * l_len);
    memcpy(leftCopy, nums + first, sizeof(HS_ELEMENT_TYPE) * l_len);
    
    HS_INDEX l_index = 0, r_index = mid + 1, index = first;
    while (l_index < l_len && r_index <= end)
    {
        if (leftCopy[l_index] <= nums[r_index])
            nums[index++] = leftCopy[l_index++];
        else
            nums[index++] = nums[r_index++];
    }
    
    if(l_index < l_len)
        memcpy(nums + index , leftCopy + l_index, sizeof(HS_ELEMENT_TYPE) * (l_len - l_index));
    
    free(leftCopy);
}


void hs_mergeSortIteration(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    HS_SIZE len = end - first + 1;
    HS_INDEX mid;
    for (HS_SIZE step = 1; step < len; step <<= 1)
    {
        HS_SIZE doubleStep = step << 1;
        HS_INDEX l_index = first, r_index = l_index + doubleStep - 1;
        for ( ;r_index <= end; l_index += doubleStep, r_index += doubleStep)
        {
            mid = (l_index >> 1) + (r_index >> 1);
            hs_merge(nums, l_index, mid, r_index);
        }
        if (l_index + step <= end)
            hs_merge(nums, l_index, l_index + step - 1, end);
    }
}

void hs_mergeSortRecursion(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if (end <= first)
        return;
    HS_INDEX mid = (first >> 1) + (end >> 1);
    
    hs_mergeSortRecursion(nums, first, mid);
    hs_mergeSortRecursion(nums, mid + 1, end);
    hs_merge(nums, first, mid, end);
}


void hs_mergeSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if (!nums || end <= first)
        return;
#ifdef HS_RECURSION
    hs_mergeSortRecursion(nums, first, end);
#else
    hs_mergeSortIteration(nums, first, end);
#endif

    
}
