//
//  main.c
//  Heaps
//
//  Created by 郝源顺 on 2021/1/2.
//

#include <stdio.h>
#include "HS_BinaryHeap.h"

void testBinaryHeap()
{
    HS_ELEMENT_TYPE test1[30] = {48, 117, 151, 87, 66, 46, 79, 177, 107, 104, 192, 12, 130, 133, 187, 50, 9, 32, 150, 131, 162, 51, 61, 198, 63, 118, 60, 72, 56,100};
    
    HS_BinaryHeap* pHeap = hs_binaryHeapNewWithElements(test1, 30);
    
    
    hs_printArray(*(HS_ELEMENT_TYPE**) pHeap, hs_binaryHeapSize(pHeap));
    
    hs_binaryHeapAdd(pHeap, 258);

    hs_printArray(*(HS_ELEMENT_TYPE**) pHeap, hs_binaryHeapSize(pHeap));

    printf("删除堆顶： %d\n", hs_binaryHeapRemove(pHeap));

    hs_printArray(*(HS_ELEMENT_TYPE**) pHeap, hs_binaryHeapSize(pHeap));
    
}

int main(int argc, const char * argv[]) {

    testBinaryHeap();
    
    
    return 0;
}
