//
//  HS_Define.h
//  Heaps
//
//  Created by 郝源顺 on 2021/1/2.
//

#ifndef HS_Define_h
#define HS_Define_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

typedef unsigned int HS_HEAP_SIZE;
typedef HS_HEAP_SIZE HS_HEAP_INDEX;

typedef int HS_ELEMENT_TYPE;

void hs_swap(HS_ELEMENT_TYPE* num1, HS_ELEMENT_TYPE* num2);

void hs_printArray(HS_ELEMENT_TYPE* elements, HS_HEAP_SIZE elementSize);



#endif /* HS_Define_h */
