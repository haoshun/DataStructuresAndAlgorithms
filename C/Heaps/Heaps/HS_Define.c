//
//  HS_Define.c
//  Heaps
//
//  Created by 郝源顺 on 2021/1/2.
//

#include "HS_Define.h"

void hs_swap(HS_ELEMENT_TYPE* num1, HS_ELEMENT_TYPE* num2)
{
    HS_ELEMENT_TYPE tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void hs_printArray(HS_ELEMENT_TYPE* elements, HS_HEAP_SIZE elementSize)
{
    if(elements && elementSize)
    {
        for (HS_HEAP_INDEX index = 1, anotherLine = 2; index <= elementSize; ++index)
        {
            printf("%d, ", elements[index]);
            if (index == anotherLine - 1 ) {
                printf("\n");
                anotherLine <<= 1;
            }
        }
            
        printf("\n");
    }
}

