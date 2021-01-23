//
//  Shell_Sort.c
//  Sorts
//
//  Created by 郝 源顺 on 2018/11/15.
//  Copyright © 2018年 Shun. All rights reserved.
//

#include "Shell_Sort.h"

void shell_Sort(int* nums,int first,int end)
{
    if(!nums || first >=end)
        return;
    int increament = end - first + 1;
    while (increament>1)
    {
        increament = increament / 3 +1;
        
        for(int i = increament ; i <= end ; ++i)
        {
            for(int j = i-increament  ,  key = nums[i] ; j >= 0 ; j = j - increament)
            {
                if (key < nums[j])
                {
                    nums[j] = nums[j] ^ nums[j+increament];
                    nums[j+increament] = nums[j] ^ nums[j+increament];
                    nums[j] = nums[j] ^ nums[j+increament];
                }
            }
        }
        
    }
    
    
}

