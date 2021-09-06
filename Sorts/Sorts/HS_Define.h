//
//  HS_Define.h
//  Sorts
//
//  Created by 郝源顺 on 2021/1/6.
//  Copyright © 2021 Shun. All rights reserved.
//

#ifndef HS_Define_h
#define HS_Define_h

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef int HS_ELEMENT_TYPE;
typedef int HS_SIZE;
typedef HS_SIZE HS_INDEX;

void hs_swap(HS_ELEMENT_TYPE* num1, HS_ELEMENT_TYPE* num2);

void hs_printElements(HS_ELEMENT_TYPE* elements, HS_INDEX begin, HS_INDEX end);

#endif /* HS_Define_h */
