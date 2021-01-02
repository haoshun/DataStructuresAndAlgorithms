//
//  HS_String.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/15.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_String_h
#define HS_String_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HS_Deque.h"

char* validString(char* input, HS_STATUS* error);

int strToInt(char* str, unsigned long len);

char* intToStr(int val);

#endif /* HS_String_h */
