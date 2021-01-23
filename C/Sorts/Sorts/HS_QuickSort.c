//
//  HS_QuickSort.c
//  Sorts
//
//  Created by 郝 源顺 on 2018/12/11.
//  Copyright © 2018年 Shun. All rights reserved.
//

#include "HS_QuickSort.h"

#define HS_RANDOM




/*
 非随机划分
 取末尾元素作为主元
 算法导论（第三版）7.1章
 */
HS_INDEX partition(HS_ELEMENT_TYPE* nums, HS_INDEX head, HS_INDEX rear)
{
    HS_INDEX i = head - 1;
    
    for (HS_INDEX j = head ; j < rear ; ++j)
        if (nums[j] <= nums[rear])
            hs_swap(nums + (++i), nums + j);
        
    hs_swap(nums + (++i),  nums + rear);
    return i;
}


/*
 随机划分
 
 */
HS_INDEX randomPartition(HS_ELEMENT_TYPE* nums, HS_INDEX head, HS_INDEX rear)
{
    HS_INDEX r = head + rand() % (rear - head + 1);
    hs_swap(nums + r, nums + rear);
    return partition(nums, head, rear);
}


//快排递归实现
void hs_recursion(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if(first < end)
    {
#ifdef HS_RANDOM
        HS_INDEX p = randomPartition(nums, first, end);
#else
        HS_INDEX p = partition(nums, first, end);
#endif
        hs_recursion(nums, first, p - 1);
        hs_recursion(nums, p + 1, end);
    }
}


void hs_quickSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
#ifdef HS_RANDOM
    srand((unsigned int)time(NULL));
#endif
    hs_recursion(nums, first, end);
}

