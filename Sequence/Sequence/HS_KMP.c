//
//  HS_KMP.c
//  Sequence
//
//  Created by 郝源顺 on 2021/1/23.
//

#include "HS_KMP.h"

int* hs_next(char* pattern, HS_LENGTH len)
{
    int* next = (int*)calloc(len, sizeof(int));
    next[0] = -1;
    int n = -1, i = 0;
    while (i < len - 1)
    {
        if(n < 0 || pattern[n] == pattern[i])
            next[++i] = ++n;
        else
            n = next[n];
    }
    return next;
}

/**
 * 字符串匹配
 * KMP
 * @param text 文本串
 * @param pattern 模式串
 * @return 匹配到的第一个模式串的起始索引，若无法匹配，返回-1
 */
HS_INDEX hs_kmp(char* text, char* pattern)
{
    if (!text || !pattern)
        return HS_NOTFOUND;
    
    HS_LENGTH t_len = (HS_LENGTH)strlen(text);
    if (!t_len)
        return HS_NOTFOUND;
    
    HS_LENGTH p_len = (HS_LENGTH)strlen(pattern);
    if (!p_len)
        return HS_NOTFOUND;
    
    if (p_len > t_len)
        return HS_NOTFOUND;
    
    int* next = hs_next(pattern, p_len);
        
    HS_INDEX ti = 0, pi = 0;
    HS_LENGTH delta = t_len - p_len;
    while (pi < p_len && ti - pi <= delta)
    {
        if(pi < 0 || text[ti] == pattern[pi])
        {
            ++pi;
            ++ti;
        }
        else
            pi = next[pi];
    }
    free(next);
    return (pi == p_len) ? ti - pi : HS_NOTFOUND;
}
