//
//  HS_String.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/15.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_String.h"

char* validString(char* input, HS_STATUS* error)
{
    *error = HS_INPUT_ERROR;
    char* result = NULL;
    if(input)
    {
        HS_TREE_SIZE i_len = strlen(input);
        
        if (i_len > 1)
        {
            unsigned long head = 0, rear = i_len - 1;
            while (input[head] == ' ') {
                head++;
            }
            while (input[rear] == ' ') {
                rear--;
            }
            if (input[head] == '[' && input[rear] == ']')
            {
                head++;
                if (rear >= head)
                {
                    char* validString = (char*)malloc((rear - head + 1) * sizeof(char));
                    memset(validString, '\0', (rear - head + 1));
                    unsigned long i = head, index = 0;
                    while ( i < rear )
                    {
                        if (input[i] == ' ' )
                        {
                            while (i < rear && input[i] == ' ' )
                            {
                                ++i;
                            }
                        }
                        else if ((input[i] >= '0' && input[i] <='9' ) || input[i] == '-')
                        {
                            int numLen = 0;
                            if (input[i] == '-') {
                                numLen++;
                            }
                            if (i + numLen == rear) {
                                break;
                            }
                            if (input[i + numLen] == '0') {
                                numLen++;
                            }
                            if (i + numLen < rear)
                            {
                                if (numLen && input[i + numLen - 1] == '0' && input[i + numLen] >='0' && input[i + numLen] <= '9') {
                                    break;
                                }
                                else
                                {
                                    while (i + numLen < rear && input[i + numLen] >= '0' && input[i + numLen] <= '9')
                                    {
                                        numLen++;
                                    }
                                }
                            }
                            if (numLen == 1 && input[i] == '-') {
                                break;
                            }
                            if (index && validString[index - 1] != ',') {
                                break;
                            }
                            strncpy(validString + index, input + i, numLen);
                            i += numLen;
                            index += numLen;
                        }
                        else if (input[i] == 'n')
                        {
                            if (!index) {
                                break;
                            }
                            if (i + 3 < rear)
                            {
                                if (!strncmp(input + i, "null", 4) )
                                {
                                    if (index && validString[index - 1] != ',') {
                                        break;
                                    }
                                    strncpy(validString + index, input + i, 4);
                                    index += 4;
                                    i += 4;
                                }
                                else
                                    break;
                            }
                        }
                        else if (input[i] == ',')
                        {
                            if (!index || validString[index - 1] == ',') {
                                break;
                            }
                            validString[index++] = ',';
                            ++i;
                        }
                        else
                            break;
                    }
                    if ( i == rear && (!index || (validString[index-1] >= '0' && validString[index - 1] <= '9')|| validString[index - 1] == 'l')) {
                        result = validString;
                        *error = HS_SUCCEED;
                    }
                    
                }
            }
        }
    }
    return result;
}

int strToInt(char* str, unsigned long len){
    int result = 0;
    if(str && len)
    {
        int leftIndex = 0, rightIndex = 0;
        int sign = str[leftIndex] == '-' ? -1 : 1;
        if(str[leftIndex] == '-')
            leftIndex = ++rightIndex;
        while(str[leftIndex] == '0')
            leftIndex = ++rightIndex;
        while(rightIndex < len && str[rightIndex] >= '0' && str[rightIndex] <= '9')
            rightIndex++;
        int numLen = rightIndex - leftIndex;
        if(numLen)
        {
            if(numLen > 10)
                result = sign > 0 ? INT_MAX : INT_MIN;
            else
            {
                if(numLen == 10 && strncmp(str + leftIndex, "2147483647",10) > 0)
                    result = sign > 0 ? INT_MAX : INT_MIN;
                else
                {
                    for(int i = rightIndex - 1, j = 1 ; i >= leftIndex ; --i)
                    {
                        result += (str[i] - '0')* j;
                        if(i > leftIndex)
                            j *= 10;
                    }
                    result *= sign;
                }
            }
        }
    }
    return result;
}


char* intToStr(int val)
{
    char* str = (char*) malloc(sizeof(char) * 12);
    memset(str , '\0', sizeof(char) *12);
    int index = 0, left = 0, add = 0;
    if(val == INT_MIN)
    {
        val++;
        add++;
    }
    if(val < 0)
    {
        str[index++] = '-';
        val *= -1;
        left++;
    }
    do{
        str[index++] = '0' + val % 10;
        val /= 10;
    }while(val);
    for(int i = left, j = index - 1 ; i < j; ++i, --j)
    {
        str[i] ^= str[j];
        str[j] ^= str[i];
        str[i] ^= str[j];
    }
    if(add)
        str[index - 1] += 1;
    return str;
}
