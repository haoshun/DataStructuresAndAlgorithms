//
//  HS_HeapSort.c
//  Sorts
//
//  Created by 郝源顺 on 2021/1/14.
//  Copyright © 2021 Shun. All rights reserved.
//

#include "HS_HeapSort.h"

void siftDown(HS_ELEMENT_TYPE* nums, HS_SIZE heapSize,  HS_INDEX index)
{
    HS_ELEMENT_TYPE value = nums[index];
    for (HS_INDEX maxIndex = index,  child;
         index >= 0 && index < heapSize;
         index = maxIndex)
    {
        child = (index << 1) + 1;
        if (child < heapSize && nums[child] > value)
            maxIndex = child;
        if(child + 1 < heapSize && nums[child + 1] > (maxIndex == index ? value: nums[maxIndex]))
            maxIndex = child + 1;
        if (maxIndex == index)
        {
            nums[index] = value;
            break;
        }
        else
            nums[index] = nums[maxIndex];
    }
}

void hs_heapify(HS_ELEMENT_TYPE* nums, HS_SIZE heapSize)
{
    for (HS_INDEX index = (heapSize >> 1) - 1 ; index >= 0 ; --index)
        siftDown(nums, heapSize, index);
}

void hs_heapSort(HS_ELEMENT_TYPE* nums, HS_INDEX first, HS_INDEX end)
{
    if(!nums || first >= end)
        return;
    
    nums += first;
    HS_SIZE heapSize = end - first + 1;
    
    hs_heapify(nums, heapSize);
    
    for (HS_INDEX index = heapSize - 1; index > 0; --index)
    {
        hs_swap(nums + index, nums);
        siftDown(nums,  index, 0);
    }
}
