//
//  HS_Define.c
//  Sorts
//
//  Created by 郝源顺 on 2021/1/6.
//  Copyright © 2021 Shun. All rights reserved.
//

#include "HS_Define.h"

/*这里没有使用异或位运算交换数值
 若两个地址指向同一元素，则异或交换值后该元素被置为0
*/
void hs_swap(HS_ELEMENT_TYPE* num1, HS_ELEMENT_TYPE* num2)
{
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}


void hs_printElements(HS_ELEMENT_TYPE* elements, HS_INDEX begin, HS_INDEX end)
{
    for(HS_INDEX i = begin ; i <= end ; ++i)
        printf("%d, ", elements[i]);
    printf("\n");
}
