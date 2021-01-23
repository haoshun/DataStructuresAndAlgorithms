//
//  HS_SelectionSort.c
//  Sorts
//
//  Created by 郝 源顺 on 2018/11/16.
//  Copyright © 2018年 Shun. All rights reserved.
//

#include "HS_SelectionSort.h"

//另一种实现方式
void selectionSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if(!nums || first >=end)
        return;

    for (HS_INDEX i = first ; i < end; ++i)
        for (HS_INDEX j = i + 1; j <= end; ++j)
            if (nums[i] > nums[j])
                hs_swap(nums + i, nums + j);
}

void hs_selectionSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if(!nums || first >= end)
        return;

    for (HS_INDEX i = first ; i < end ; ++i)
    {
        HS_INDEX minIndex = i;

        for (HS_INDEX j =  i +1  ; j <= end; ++j)
            if (nums[minIndex] > nums[j])
                minIndex = j;

        hs_swap(nums + minIndex, nums + i);
    }
    //selectionSort(nums, first, end);
}






