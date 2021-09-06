//
//  HS_BubbleSort.c
//  Sorts
//
//  Created by 郝 源顺 on 2018/11/23.
//  Copyright © 2018年 Shun. All rights reserved.
//

#include "HS_BubbleSort.h"

/*
 优化
 添加提前退出标志位
 */
void bubbleSort(HS_ELEMENT_TYPE* nums, HS_INDEX first,HS_INDEX end)
{
    if(!nums || first >=end)
        return;

    for (HS_INDEX i = first ; i < end - 1; ++i)
    {
        bool flag = false;
        for (HS_INDEX j = end; j > i; --j)
        {
            if (nums[j - 1] > nums[j])
            {
                flag = true;
                hs_swap(nums + j, nums + j - 1);
            }
        }
        if (!flag)
            break;
    }
}

/*
 从后往前冒泡
 算法导论（第三版）第2章 思考题 2.2
 */
void hs_bubbleSort(HS_ELEMENT_TYPE* nums,HS_INDEX first,HS_INDEX end)
{
//    if(!nums || first >=end)
//        return;
//
//    for (HS_INDEX i = first ; i < end -1; ++i)
//        for (HS_INDEX j = end; j > i; --j)
//            if (nums[j] < nums[j - 1])
//                hs_swap(nums + j, nums + j - 1);
    bubbleSort(nums, first, end);
    
}


